/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

/* SoapDeSerializer.cpp: implementation of the SoapDeSerializer class. */

#include <axis/server/SoapDeSerializer.h>
#include "SoapEnvelope.h"
#include "SoapKeywordMapping.h"
#include "URIMapping.h"
#include <axis/server/SoapHeader.h>
#include "SoapMethod.h"
#include "SoapBody.h"
#include "SoapFault.h"
#include "ComplexElement.h"
#include <axis/server/CharacterElement.h>
#include <axis/server/GDefine.h>
#include <axis/server/Packet.h>
#include <axis/server/AxisTrace.h>
#include "apr_base64.h"
#include "HexCoder.h"
#include "../engine/XMLParserFactory.h"
#include <axis/server/XMLParser.h>
#include "../xml/QName.h"

extern AxisTrace* g_pAT;

#define INITIAL_ARRAY_SIZE 1

IWrapperSoapDeSerializerFunctions IWrapperSoapDeSerializer::ms_VFtable;

SoapDeSerializer::SoapDeSerializer()
{
	m_pParser = XMLParserFactory::getParserObject();
    m_pEnv = NULL;
    m_pHeader = NULL;
    m_pcFaultDetail = (char*) malloc(sizeof(char) * 100);
	m_pInputStream = 0;
	m_nStatus = AXIS_SUCCESS;
}

SoapDeSerializer::~SoapDeSerializer()
{
    if (m_pEnv)
	 delete m_pEnv;
    if(m_pHeader)
      delete m_pHeader;    
    if (m_pParser) delete m_pParser;
    free(m_pcFaultDetail);
}

int SoapDeSerializer::setInputStream(SOAPTransport* pInputStream)
{
    if (NULL == pInputStream)
        return AXIS_FAIL;
	m_pInputStream = pInputStream;
    return m_pParser->setInputStream(pInputStream);
}

SoapEnvelope* SoapDeSerializer::getEnvelope()
{
    Attribute *pAttr = NULL;    
    if (!m_pNode) m_pNode = m_pParser->next();
    if (!m_pNode || (START_ELEMENT != m_pNode->m_type)) return NULL;
    if (0 == strcmp(m_pNode->m_pchNameOrValue, 
        SoapKeywordMapping::map(SOAP_VER_1_2).pchWords[SKW_ENVELOPE]))
    {
        SoapEnvelope* m_pEnv = new SoapEnvelope();
        /* set all attributes of SoapEnvelope */
        pAttr = new Attribute();

        pAttr->setValue(m_pNode->m_pchNamespace);
        m_pEnv->addNamespaceDecl(pAttr);

        if (0 == strcmp(m_pNode->m_pchNamespace, 
            SoapKeywordMapping::map(SOAP_VER_1_1).pchNamespaceUri))
        {
            m_nSoapVersion = SOAP_VER_1_1;
        }
        else if (0 == strcmp(m_pNode->m_pchNamespace, 
            SoapKeywordMapping::map(SOAP_VER_1_2).pchNamespaceUri))
        {
            m_nSoapVersion = SOAP_VER_1_2;
        }
        else
        {
            m_nSoapVersion = VERSION_LAST;
        }

        /* Set Attributes */
        for (int i = 0; m_pNode->m_pchAttributes[i]; i += 3) 
        {
            pAttr = new Attribute();
            pAttr->setLocalName(m_pNode->m_pchAttributes[i]);
            pAttr->setUri(m_pNode->m_pchAttributes[i+1]);
            pAttr->setValue(m_pNode->m_pchAttributes[i+2]);
            m_pEnv->addAttribute(pAttr);
        }
        m_pNode = NULL; /* This is to indicate that node is identified 
                         * and used */
        return m_pEnv;
    }
    return NULL;
}

/*
 * Header block parsing should be done differently for different SOAP versions.
 * Since the Header blocks may be requested in a different order than it is in 
 * the SOAP stream there must be a mechanism to manage the situation. Possibly 
 * to re-parse the stream part which has unused header blocks.
 */
IHeaderBlock* SoapDeSerializer::getHeaderBlock(const AxisChar* pName, 
                                               const AxisChar* pNamespace)
{
    if (!m_pHeader) return NULL; /* there has been no <Header> element so there
                                  * can be no Header blocks */

    return m_pHeader->getHeaderBlock(pName, pNamespace);
}
                                               
int SoapDeSerializer::getHeader()
{
    if (m_pHeader) return m_nStatus;
    m_pNode = m_pParser->next();
    if (!m_pNode)  /* this means a SOAP error */
    {
        m_nStatus = AXIS_FAIL;
        return m_nStatus;
    }

    if ((START_ELEMENT == m_pNode->m_type) && 
        (0 == strcmp(m_pNode->m_pchNameOrValue, 
        SoapKeywordMapping::map(m_nSoapVersion).pchWords[SKW_HEADER])))
    {
       if(m_pHeader)
           delete m_pHeader;
        m_pHeader = new SoapHeader();
        /* Set any attributes/namspaces to the SoapHeader object */

        bool blnConStatus = true;
        int iLevel = HEADER_LEVEL;
        int iHeaderBlockStackLevel = 0;
        HeaderBlock* pHeaderBlock;
        ComplexElement* pComplexElement;
        CharacterElement* pCharacterElement;

        while (blnConStatus)
        {
            m_pNode = m_pParser->next();
            if (!m_pNode) 
            {
                m_nStatus = AXIS_FAIL;
                return m_nStatus;
            }
            if ((END_ELEMENT == m_pNode->m_type) && 
                (0 == strcmp(m_pNode->m_pchNameOrValue, 
                SoapKeywordMapping::map(m_nSoapVersion).pchWords[SKW_HEADER])))
            {
                m_pNode = NULL; /* This is to indicate that node is identified
                                 * and used */
                return m_nStatus;
                break;
            }
            else
            {
                if (START_ELEMENT == m_pNode->m_type)
                {
                    if (iLevel == HEADER_LEVEL)
                    {
                        pHeaderBlock = new HeaderBlock();
        
                        pHeaderBlock->setUri(m_pNode->m_pchNamespace);
                        pHeaderBlock->setLocalName(m_pNode->m_pchNameOrValue);

                        if ((m_pNode->m_pchAttributes[0]) != NULL)
                        {
                            int iAttributeArrayIndex = 0;
                            while (true)
                            {
                                Attribute* pAttribute = new Attribute();
                                pAttribute->setLocalName(m_pNode->
                                    m_pchAttributes[iAttributeArrayIndex++]);
                                pAttribute->setUri(m_pNode->
                                    m_pchAttributes[iAttributeArrayIndex++]);
                                pAttribute->setValue(m_pNode->
                                    m_pchAttributes[iAttributeArrayIndex++]);

                                pHeaderBlock->addAttribute(pAttribute);
                                
                                if (m_pNode->m_pchAttributes
                                    [iAttributeArrayIndex] == '\0')
                                {
                                    break;
                                }
                            }
                        }

                        iLevel = HEADER_BLOCK_LEVEL;
                    }
                    else if (iLevel == HEADER_BLOCK_LEVEL)
                    {
                        iHeaderBlockStackLevel++;

                        pComplexElement = new ComplexElement();
                        
                        pComplexElement->setURI(m_pNode->m_pchNamespace);
                        pComplexElement->setLocalName(m_pNode->
                                                      m_pchNameOrValue);

                        iLevel = HEADER_BLOCK_INSIDE_LEVEL;
                    }
                } else if (END_ELEMENT == m_pNode->m_type)
                {
                    if ((iLevel == HEADER_BLOCK_LEVEL) && 
                        (iHeaderBlockStackLevel==0))
                    {
                        m_pHeader->addHeaderBlock(pHeaderBlock);
                        iLevel = HEADER_LEVEL;
                    }
                    else if ((iLevel == HEADER_BLOCK_INSIDE_LEVEL) && 
                        (iHeaderBlockStackLevel>0))
                    {
                        pHeaderBlock->addChild(pComplexElement);
                        iHeaderBlockStackLevel--;
                        iLevel = HEADER_BLOCK_LEVEL;
                    }
                }
                else if (CHARACTER_ELEMENT == m_pNode->m_type)
                {
                    pCharacterElement = new CharacterElement(m_pNode->
                                                             m_pchNameOrValue);

                    if (iLevel == HEADER_BLOCK_LEVEL)
                    {
                        pHeaderBlock->addChild(pCharacterElement);
                    }
                    else
                    {
                        pComplexElement->addChild(pCharacterElement);
                    }
                }
            }
        }
    }

    return m_nStatus;
}

int SoapDeSerializer::getBody()
{   
    if (!m_pNode) m_pNode = m_pParser->next();
    AXISTRACE1("came2", INFO); 
    /* previous header searching may have left a node unidentified */
    if (m_pNode) 
    {
        if ((START_ELEMENT == m_pNode->m_type) && 
            (0 == strcmp(m_pNode->m_pchNameOrValue, 
            SoapKeywordMapping::map(m_nSoapVersion).pchWords[SKW_BODY])))
        {
            /* Set any attributes/namspaces to the SoapBody object */
            m_pNode = NULL; /* This is to indicate that node is identified 
                             * and used */
            return AXIS_SUCCESS;
        }
    }
    m_nStatus = AXIS_FAIL;
    return AXIS_FAIL;
}

int SoapDeSerializer::checkMessageBody(const AxisChar* pName, 
                                       const AxisChar* pNamespace)
{
    int iResult;
    /* check and skip the soap body tag */
    if (AXIS_SUCCESS != getBody()) return AXIS_FAIL;    
    if (!m_pNode) m_pNode = m_pParser->next();
    if (!m_pNode || (START_ELEMENT != m_pNode->m_type)) return AXIS_FAIL;
    AXISTRACE2("pName", pName, INFO);
    AXISTRACE2("m_pChNameOrValue", m_pNode->m_pchNameOrValue, INFO);
    //if (0 != strcmp(m_pNode->m_pchNameOrValue, pName)) return AXIS_FAIL;
    if (0 != strcmp(m_pNode->m_pchNameOrValue, pName))
    {
        THROW_AXIS_EXCEPTION(AXISC_NODEVALUE_MISMATCH_EXCEPTION);    
    }
    /* we can check the namespace uri too here. Should we ?*/
    m_pNode = NULL; /*This is to indicate that node is identified and used */
    return AXIS_SUCCESS;
}

int SoapDeSerializer::getFault()
{
    /* TODO : */
    //if (!m_pNode) m_pNode = m_pParser->next();
    //if (m_pNode)
    //{
        AXISTRACE1("SOAP FAULT", INFO);
        m_pcFaultDetail = "This is a hard coded test error";

        return AXIS_SUCCESS;
    //}

}

int SoapDeSerializer::getFaultDetail(char** ppcDetail)
{
    *ppcDetail = m_pcFaultDetail;
    return AXIS_SUCCESS;
}

int SoapDeSerializer::init()
{
    m_pNode = 0;
    if (m_pEnv) 
    {
        delete m_pEnv;
        m_pEnv = NULL;
    }
    if (m_pHeader)
    {
        delete m_pHeader;
        m_pHeader = NULL;
    }
    m_nSoapVersion = VERSION_LAST;
	m_nStatus = AXIS_SUCCESS;
    return m_nStatus;
}

int SoapDeSerializer::getVersion()
{
    if (VERSION_LAST == m_nSoapVersion)
    {
	if (m_pEnv)
	    delete m_pEnv;
        m_pEnv = getEnvelope();
	
    }
    return m_nSoapVersion;    
}

/*
 * In rpc/encoded style the stream is as follows,
 * <abc:ArrayOfPoints xmlns:abc="http://www.opensource.lk/Points"
 *    xmlns:enc="http://www.w3.org/2001/06/soap-encoding"
 *    enc:arrayType="xsd:Point[2]">
 *    <abc:Point><x>5</x><y>6</y></abc:Point>
 *    <abc:Point><x>7</x><y>8</y></abc:Point>
 * </abc:ArrayOfPoints>
 * But in doc/literal style it is,
 *    <points><x>5</x><y>6</y></points>
 *    <points><x>7</x><y>8</y></points>
 *
 */
Axis_Array SoapDeSerializer::getCmplxArray(void* pDZFunct, void* pCreFunct, 
                                           void* pDelFunct, void* pSizeFunct, 
                                           const AxisChar* pName, 
                                           const AxisChar* pNamespace)
{
    Axis_Array Array = {NULL, 0};
    int nIndex = 0;
    void* pItem;
    int itemsize;
    unsigned long ptrval;
    if (AXIS_SUCCESS != m_nStatus) return Array; /* if anything has gone wrong
                                                  * earlier just do nothing */
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();   
        /* just skip wrapper node with type info
         * Ex:<tns:QuoteInfoTypeArray xmlns:tns="http://www.getquote.org/test">
         */
        if (!m_pNode) return Array;
        Array.m_Size = getArraySize(m_pNode);
        if (Array.m_Size > 0)
        {
            Array.m_Array = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)
                (Array.m_Array, true, Array.m_Size);
            if (!Array.m_Array)
            {
                Array.m_Size = 0;
                m_nStatus = AXIS_FAIL;
                return Array;
            }
            itemsize = ((AXIS_OBJECT_SIZE_FUNCT)pSizeFunct)();
            ptrval = reinterpret_cast<unsigned long>(Array.m_Array);
            for (; nIndex < Array.m_Size; nIndex++)
            {
                m_pNode = m_pParser->next();
                /* wrapper node without type info  Ex: <item> */
                if (!m_pNode) 
                {
                    free(Array.m_Array);
                    Array.m_Size = 0;
                    return Array;
                }
                pItem = reinterpret_cast<void*>(ptrval+nIndex*itemsize);
                if (C_RPC_PROVIDER == getCurrentProviderType())
                {
                    IWrapperSoapDeSerializer_C cWSD;
                    cWSD._object = this;
                    cWSD._functions = &IWrapperSoapDeSerializer::ms_VFtable;
                    ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pItem, &cWSD);
                }
                else
                {
                    m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)
                        (pItem, this);
                }
                m_pNode = m_pParser->next(); /* skip end element node too */
                if (!m_pNode) 
                {
                    free(Array.m_Array);
                    Array.m_Size = 0;
                    return Array;
                }
            }
            return Array;
        }
    }
    else
    {
        Array.m_Array = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)(Array.m_Array,
            true, INITIAL_ARRAY_SIZE);
        if (!Array.m_Array) return Array;
        Array.m_Size = INITIAL_ARRAY_SIZE;
        itemsize = ((AXIS_OBJECT_SIZE_FUNCT)pSizeFunct)();
        while(true)
        {
            ptrval = reinterpret_cast<unsigned long>(Array.m_Array);
            for (; nIndex < Array.m_Size; nIndex++)
            {
                if (!m_pNode) /* if there is an unprocessed node that may be
                               * one left from last array deserialization 
                               */ 
                    m_pNode = m_pParser->next();
                    /* wrapper node without type info  Ex: <phonenumbers> */
                if (!m_pNode) 
                {
                    free(Array.m_Array);
                    Array.m_Size = 0;
                    return Array;
                }
                if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
                {
                    /* if this node contain attributes let them be used by the
                     * complex type's deserializer
                     */
                    if (0 != m_pNode->m_pchAttributes[0])
                    {
                        m_pCurrNode = m_pNode;
                    }
                    m_pNode = NULL; /* recognized and used the node */
                    pItem = reinterpret_cast<void*>(ptrval+nIndex*itemsize);
                    if (C_DOC_PROVIDER == getCurrentProviderType())
                    {
                        IWrapperSoapDeSerializer_C cWSD;
                        cWSD._object = this;
                        cWSD._functions = &IWrapperSoapDeSerializer::ms_VFtable;
                        m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)
                            (pItem, &cWSD);
                    }
                    else
                    {
                        m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)
                            (pItem, this);
                    }
                    if (AXIS_SUCCESS == m_nStatus)
                    {
                        m_pParser->next();
                        /* skip end element of the array item */
                        continue;
                    }
                }
                else
                {
                    if (nIndex > 0)
                    {
                        Array.m_Size = nIndex;
                        /* put the actual deserialized item size
                         * note we do not make m_pNode = NULL because this node
                         * doesnot belong to this array 
                         */
                        return Array;
                    }
                    /* error : no elements deserialized */
                }
            /* if we come here it is an error situation */
            /*
             * not an  error for self referenced array or empty array
             * TODO: Need to verify what WS-I 1.0 say
             * <xsd:complexType name="Type1">
             *  <xsd:sequence>
             *    <xsd:element name="types" maxOccurs="unbounded" minOccurs="0"
             *         type="tns:Type1"/>
             *    <xsd:element name="type" minOccurs="0" type="xsd:string"/>
             *  </xsd:sequence>
             * </xsd:complexType>        
             */
            ((AXIS_OBJECT_DELETE_FUNCT)pDelFunct)(Array.m_Array, true, Array.m_Size);
            Array.m_Array = 0;
            Array.m_Size = 0;
            return Array;
            }
            /* if we come here that means the array allocated is not enough.
             * So double it 
             */
            Array.m_Array = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)
                (Array.m_Array, true, Array.m_Size*2);
            if (!Array.m_Array) 
            {
                Array.m_Size = 0;
                return Array;
            }
            Array.m_Size *= 2;
            /* Array.m_RealSize = Array.m_Size; */
        }
    }
    m_nStatus = AXIS_FAIL;
    m_pNode = NULL;
    return Array;
}

/*
 * Get Size of the single dimension array from arrayType attribute
 * Ex : enc:arrayType="xs:string[6]"
 */
int SoapDeSerializer::getArraySize(const AnyElement* pElement)
{
    int nSize = 0;
    /* first check whether this is a start element node */
    if (START_ELEMENT != pElement->m_type) return nSize;
    for (int i=0; pElement->m_pchAttributes[i]; i+=3)
    {
        if (URI_ENC == URIMapping::map(pElement->m_pchAttributes[i+1]) &&
            (0 == strcmp(pElement->m_pchAttributes[i],
            SoapKeywordMapping::map(m_nSoapVersion).pchWords[SKW_ARRAYTYPE])))
        {
            QName qn;
            qn.splitQNameString(pElement->m_pchAttributes[i+2], '[');
            nSize = strtol(qn.localname, &m_pEndptr, 10);
            qn.mergeQNameString('[');
            return nSize;
        }
    }
    return nSize;
}

/*
 * In rpc/encoded style the stream is as follows,
 * <abc:ArrayOfPhoneNumbers xmlns:abc="http://example.org/2001/06/numbers"
 *    xmlns:enc="http://www.w3.org/2001/06/soap-encoding"
 *    enc:arrayType="xsd:string[2]">
 *    <item>+94-112-500500</item>
 *    <item>+94-112-500500</item>
 * </abc:ArrayOfPhoneNumbers>
 * But in doc/literal style it is,
 *    <phonenumbers>+94-112-500500</phonenumbers>
 *    <phonenumbers>+94-112-500500</phonenumbers> 
 *
 *
 */

/* Following macros are used just to shorten the coding */
#define CONV_STRTOL(str) strtol(str, &m_pEndptr, 10)
#define CONV_STRTOUL(str) strtoul(str, &m_pEndptr, 10)
#define CONV_STRTOD(str) strtod(str,  &m_pEndptr)
#define CONV_STRTODATETIME(str) AxisTime::deserialize(str, nType)
#define CONV_STRTODURATION(str) AxisTime::deserializeDuration(str, nType)
#define CONV_STRDUP(str) strdup(str)
#define CONV_STRTOBASE64BINARY(str) decodeFromBase64Binary(str)
#define CONV_STRTOHEXBINARY(str) decodeFromHexBinary(str)

#define INIT_VALUE_DATETIME {0,0,0,0,0,0,0,0,0}
#define INIT_VALUE_NUMBER 0
#define INIT_VALUE_XSDBINARY {0,0}

#define DESERIALIZE_ENCODED_ARRAY_BLOCK(cpp_type, conv_func) \
Array.m_Array = malloc(sizeof(cpp_type)*Array.m_Size);\
if (!Array.m_Array)\
{\
    Array.m_Size = 0;\
    m_nStatus = AXIS_FAIL;\
    return Array;\
}\
for (; nIndex < Array.m_Size; nIndex++)\
{\
    /* wrapper node without type info  Ex: <item>*/\
    m_pNode = m_pParser->next(); \
    m_pNode = m_pParser->next(true); /* charactor node */\
    if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))\
    {\
        ((cpp_type*)Array.m_Array)[nIndex] = \
        conv_func(m_pNode->m_pchNameOrValue);\
        m_pNode = m_pParser->next(); /* skip end element node too */\
        continue;\
    }\
    /* error : unexpected element type or end of stream */\
    m_nStatus = AXIS_FAIL;\
    free(Array.m_Array);\
    Array.m_Array = 0;\
    Array.m_Size = 0;\
    return Array;\
}\
return Array;

#define DESERIALIZE_LITERAL_ARRAY_BLOCK(cpp_type, conv_func) \
            Array.m_Array = malloc(sizeof(cpp_type)*INITIAL_ARRAY_SIZE);\
            if (!Array.m_Array) return Array;\
            Array.m_Size = INITIAL_ARRAY_SIZE;\
            while(true)\
            {\
                for (; nIndex < Array.m_Size; nIndex++)\
                {\
                    if (!m_pNode) \
                    /* if there is an unprocessed node that may be one left */\
                    /* from last array deserialization */\
                        m_pNode = m_pParser->next();\
                        /* wrapper node without type info Ex: <phonenumbers>*/\
                    if (!m_pNode)\
                    {\
                        m_nStatus = AXIS_FAIL;\
                        free(Array.m_Array);\
                        Array.m_Array = 0;\
                        Array.m_Size = 0;\
                        return Array;\
                    }\
                    if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))\
                    {\
                        m_pNode = m_pParser->next(true); /* charactor node */\
                        if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))\
                        {\
                            ((cpp_type*)Array.m_Array)[nIndex] = \
                            conv_func(m_pNode->m_pchNameOrValue);\
                            m_pNode = m_pParser->next(); \
                            /* skip end element node too */\
                            m_pNode = NULL; \
                            /* this is important in doc/lit style when */\
                            /* deserializing arrays */\
                            continue;\
                        }\
                        /* error : unexpected element type or */\
                        /* end of the stream */\
                    }\
                    else\
                    {\
                        if (nIndex > 0)\
                        {\
                            Array.m_Size = nIndex; \
                            /* put the actual deserialized item size */\
                            /* note we do not make m_pNode = NULL because */\
                            /* this node doesnot belong to this array */\
                            return Array;\
                        }\
                        /* error : no elements deserialized */\
                    }\
                    /* if we come here it is an error situation */\
                    m_nStatus = AXIS_FAIL;\
                    m_pNode = NULL;\
                    free(Array.m_Array);\
                    Array.m_Array = 0;\
                    Array.m_Size = 0;\
                    return Array;\
                }\
                /* if we come here that means the array allocated is */\
                /* not enough. So double it */\
                Array.m_Array = realloc(Array.m_Array, \
                    sizeof(cpp_type)*(Array.m_Size*2));\
                if (!Array.m_Array) \
                {\
                    Array.m_Size = 0;\
                    return Array;\
                }\
                Array.m_Size *= 2;\
                /*Array.m_RealSize = Array.m_Size;*/\
            }\
            break;

Axis_Array SoapDeSerializer::getBasicArray(XSDTYPE nType,
                                           const AxisChar* pName,
                                           const AxisChar* pNamespace)
{
    Axis_Array Array = {NULL, 0};
    int nIndex = 0;
    if (AXIS_SUCCESS != m_nStatus) return Array;
    /* if anything has gone wrong earlier just do nothing */
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* just skip wrapper node with type info  Ex: <tns:ArrayOfPhoneNumbers
         * xmlns:tns="http://www.getquote.org/test">
         */ 
        if (!m_pNode) return Array;
        Array.m_Size = getArraySize(m_pNode);
        if (Array.m_Size > 0)
        {
            switch(nType)
            {
            case XSD_INT:
                Array.m_Array = malloc(sizeof(int)*Array.m_Size);
                if (!Array.m_Array)
                {
                    Array.m_Size = 0;
                    m_nStatus = AXIS_FAIL;
                    return Array;
                }
                for (; nIndex < Array.m_Size; nIndex++)
                {
                    m_pNode = m_pParser->next();
                    /* wrapper node without type info  Ex: <item>*/
                    m_pNode = m_pParser->next(true); /* charactor node */
                    if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
                    {
                        ((int*)Array.m_Array)[nIndex] = strtol(m_pNode->
                            m_pchNameOrValue, &m_pEndptr, 10);
                        m_pNode = m_pParser->next();
                        /* skip end element node too */
                        continue;
                    }
                    /* error : unexpected element type or end of stream */
                    m_nStatus = AXIS_FAIL;
                    free(Array.m_Array);
                    Array.m_Array = 0;
                    Array.m_Size = 0;
                    return Array;
                }
                return Array;
            case XSD_UNSIGNEDINT:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned int, CONV_STRTOUL)
            case XSD_SHORT:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(short, CONV_STRTOL)
            case XSD_UNSIGNEDSHORT:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned short, CONV_STRTOUL)
            case XSD_BYTE:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(char, CONV_STRTOL)
            case XSD_UNSIGNEDBYTE:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned char, CONV_STRTOUL)
            case XSD_LONG:
            case XSD_INTEGER:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(long, CONV_STRTOL)
            case XSD_UNSIGNEDLONG:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned long, CONV_STRTOUL)
            case XSD_FLOAT:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(float, CONV_STRTOD)
            case XSD_DOUBLE:
            case XSD_DECIMAL:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(double, CONV_STRTOD)
            case XSD_STRING:
            case XSD_HEXBINARY:
            case XSD_BASE64BINARY:
            case XSD_ANYURI:
            case XSD_QNAME:
            case XSD_NOTATION:            
                DESERIALIZE_ENCODED_ARRAY_BLOCK(char*, CONV_STRDUP)
            case XSD_DATETIME:
            case XSD_DATE:
            case XSD_TIME:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(struct tm, CONV_STRTODATETIME)
            case XSD_DURATION:
                DESERIALIZE_ENCODED_ARRAY_BLOCK(long, CONV_STRTODURATION)
            default:;
            }
        }
    }
    else
    {
        switch(nType)
        {
        case XSD_INT:
            Array.m_Array = malloc(sizeof(int)*INITIAL_ARRAY_SIZE);
            if (!Array.m_Array) return Array;
            Array.m_Size = INITIAL_ARRAY_SIZE;
            while(true)
            {
                for (; nIndex < Array.m_Size; nIndex++)
                {
                    if (!m_pNode)
                        /* if there is an unprocessed node that may be one 
                         * left from last array deserialization
                         */ 
                        m_pNode = m_pParser->next();
                    /* wrapper node without type info  Ex: <phonenumbers>*/
                    if (!m_pNode) 
                    {
                        m_nStatus = AXIS_FAIL;
                        free(Array.m_Array);
                        Array.m_Array = 0;
                        Array.m_Size = 0;
                        return Array;
                    }
                    if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
                    {
                        m_pNode = m_pParser->next(true); /* charactor node */
                        if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
                        {
                            ((int*)Array.m_Array)[nIndex] = strtol(m_pNode->
                                m_pchNameOrValue, &m_pEndptr, 10);
                            m_pNode = m_pParser->next();
                            /* skip end element node too */
                            m_pNode = NULL; /* this is important in doc/lit 
                                             * style when deserializing arrays
                                             */
                            continue;
                        }
                    /* error : unexpected element type or end of the stream */
                    }
                    else
                    {
                        if (nIndex > 0)
                        {
                            Array.m_Size = nIndex;
                            /* put the actual deserialized item size
                             * note we do not make m_pNode = NULL because this
                             * node doesnot belong to this array
                             */
                            return Array;
                        }
                        /* error : no elements deserialized */
                    }
                    /* if we come here it is an error situation */
                    m_nStatus = AXIS_FAIL;
                    m_pNode = NULL;
                    free(Array.m_Array);
                    Array.m_Array = 0;
                    Array.m_Size = 0;
                    return Array;
                }
                /* if we come here that means the array allocated is not enough
                 * So double it
                 */
                Array.m_Array = realloc(Array.m_Array, 
                    sizeof(int)*(Array.m_Size*2));
                if (!Array.m_Array) 
                {
                    Array.m_Size = 0;
                    return Array;
                }
                Array.m_Size *= 2;
                /* Array.m_RealSize = Array.m_Size;*/
            }
            break;
        case XSD_UNSIGNEDINT:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned int, CONV_STRTOUL)
        case XSD_SHORT:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(short, CONV_STRTOL)
        case XSD_UNSIGNEDSHORT:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned short, CONV_STRTOUL)
        case XSD_BYTE:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(char, CONV_STRTOL)
        case XSD_UNSIGNEDBYTE:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned char, CONV_STRTOUL)
        case XSD_LONG:
        case XSD_INTEGER:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(long, CONV_STRTOL)
        case XSD_UNSIGNEDLONG:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned long, CONV_STRTOUL)
        case XSD_FLOAT:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(float, CONV_STRTOD)
        case XSD_DOUBLE:
        case XSD_DECIMAL:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(double, CONV_STRTOD)
        case XSD_STRING:
        case XSD_HEXBINARY:
        case XSD_BASE64BINARY:
        case XSD_ANYURI:
        case XSD_QNAME:
        case XSD_NOTATION:            
            DESERIALIZE_LITERAL_ARRAY_BLOCK(char*, CONV_STRDUP)
        case XSD_DATETIME:
        case XSD_DATE:
        case XSD_TIME:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(struct tm, CONV_STRTODATETIME)     
        case XSD_DURATION:
            DESERIALIZE_LITERAL_ARRAY_BLOCK(long, CONV_STRTODURATION)
        default:;
        }
    }
    m_nStatus = AXIS_FAIL;
    m_pNode = NULL;
    return Array;
}

/*
 * In doc/lit style pName is the name of the type instance "result"
 *  <result>
 *        <name>Widgets Inc.</name> 
 *        <symbol>WID</symbol> 
 *        <public>true</public> 
 *  </result>
 * But in rpc/encoded style pName is the name of the type "QuoteInfoType"
 *  <tns:QuoteInfoType xmlns:tns="http://www.getquote.org/test">
 *        <name xsi:type="xsd:string">Widgets Inc.</name> 
 *        <symbol xsi:type="xsd:string">WID</symbol> 
 *        <public xsi:type="xsd:boolean">true</public> 
 *  </tns:QuoteInfoType>
 *
 */
void* SoapDeSerializer::getCmplxObject(void* pDZFunct, void* pCreFunct,
                                       void* pDelFunct, const AxisChar* pName,
                                       const AxisChar* pNamespace)
{
    if (AXIS_SUCCESS != m_nStatus) return NULL;
    /* if anything has gone wrong earlier just do nothing */
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* just skip wrapper node with type info
         * Ex: <tns:QuoteInfoType xmlns:tns="http://www.getquote.org/test"> */ 
        if (!m_pNode) return NULL;
        /* type  can be checked here */
        void* pObject = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)(NULL, false, 0);
        if (pObject && pDZFunct)
        {
            if (C_RPC_PROVIDER == getCurrentProviderType())
            {
                IWrapperSoapDeSerializer_C cWSD;
                cWSD._object = this;
                cWSD._functions = &IWrapperSoapDeSerializer::ms_VFtable;
                m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pObject, &cWSD);
            }
            else
            {
                m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pObject, this);
            }
            if (AXIS_SUCCESS == m_nStatus)
            {
                m_pParser->next(); /* skip end node too */
                return pObject;
            }
            else
            {
                ((AXIS_OBJECT_DELETE_FUNCT)pDelFunct)(pObject, false, 0);
            }
        }
    }
    else
    {
        if (!m_pNode)
        /* if there is an unprocessed node that may be one left from 
         * last array deserialization */ 
            m_pNode = m_pParser->next();
        /* wrapper node without type info  Ex: <result> */
        if (!m_pNode) return NULL;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            /* if this node contain attributes let them be used by the complex
             * type's deserializer
             */
            if (0 != m_pNode->m_pchAttributes[0])
            {
                m_pCurrNode = m_pNode;
                /*
                 * Need to verify if the return value is NULL.
                 */
                if ( getAttributeAsBoolean("nil",0) == true_ )
                {
                    m_pParser->next();
                    m_pNode = NULL;
                    return NULL;
                }
            }
            m_pNode = NULL; /* node identified and used */
            void* pObject = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)
                (NULL, false, 0);
            if (pObject && pDZFunct)
            {
                if (C_DOC_PROVIDER == getCurrentProviderType())
                {
                    IWrapperSoapDeSerializer_C cWSD;
                    cWSD._object = this;
                    cWSD._functions = &IWrapperSoapDeSerializer::ms_VFtable;
                    m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)
                        (pObject, &cWSD);
                }
                else
                {
                    m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)
                        (pObject, this);                }
                if (AXIS_SUCCESS == m_nStatus)
                {
                    m_pParser->next(); /* skip end node too */
                    return pObject;
                }
                else
                {
                    ((AXIS_OBJECT_DELETE_FUNCT)pDelFunct)(pObject, false, 0);                }
            }
        }
        else
        {
          /*
           * TODO: Need to verify what WS-I 1.0 say
           * about the mandatory of all the elements in the response in case of
           * null value or none filled value. Some Web services servers work
           * like this. This apply for all the rest of the deserializer.
           */
            return NULL;
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return NULL;
}

int SoapDeSerializer::getElementForAttributes(const AxisChar* pName,
                                              const AxisChar* pNamespace)
{
    if (m_pCurrNode) 
    {
        if (0 == strcmp(pName, m_pCurrNode->m_pchNameOrValue))
            return m_nStatus;
    }
    if (!m_pNode)
    {
        m_pNode = m_pParser->next();
        m_pCurrNode = m_pParser->next();
    }
    else /* previous node not processed. So consider it */
    {
        m_pCurrNode = m_pNode;
    }
    if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
    {
        m_pNode = NULL;
    }
    else /* error : current element is not the expected one */
    {
        m_nStatus = AXIS_FAIL;
        m_pCurrNode = NULL;
    }
    return m_nStatus;
}

#define DESERIALIZE_GET_ATTRIBUTE_AS(cpp_type, conv_func, init_value) \
    cpp_type ret = init_value;\
    if(!m_pCurrNode) \
    {\
        /**\
         * Not a failure for optional attributes\
         */\
        return ret;\
    }\
    if (START_ELEMENT == m_pCurrNode->m_type)\
    {\
        for (int i=0; m_pCurrNode->m_pchAttributes[i]; i+=3)\
        {\
            if (0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))\
            {\
                ret = conv_func(m_pCurrNode->m_pchAttributes[i+2]);\
                return ret;\
            }\
        }\
    }\
    else\
    {\
        m_nStatus = AXIS_FAIL;\
        return ret;\
    }\
    return ret;

/*
 * Before calling any of getAttributeAs... API functions the user should move 
 * current Element to the right Element by calling GetElementForAttributes(..)
 */
int SoapDeSerializer::getAttributeAsInt(const AxisChar* pName, 
                                        const AxisChar* pNamespace)
{
    int ret = 0;
    if(!m_pCurrNode) 
    {
        /* Optional attributes :  _ m_nStatus = AXIS_FAIL; */
        return ret;
    }
    if (START_ELEMENT == m_pCurrNode->m_type)
    {
        for (int i=0; m_pCurrNode->m_pchAttributes[i]; i+=3) 
            /* browse through the attributes list */
        {
            if (0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))
            {
                ret = strtol(m_pCurrNode->m_pchAttributes[i+2], 
                    &m_pEndptr, 10);
                return ret;
            }
        }    
    }
    else
    {
        m_nStatus = AXIS_FAIL;
    }
    return ret;        
}

xsd__boolean SoapDeSerializer::getAttributeAsBoolean(const AxisChar* pName,
                                                     const AxisChar* pNamespace)
{
    xsd__boolean ret = false_;
    if(!m_pCurrNode) 
    {
        /* Optional attributes :  _ m_nStatus = AXIS_FAIL; */
        return ret;
    }
    if (START_ELEMENT == m_pCurrNode->m_type)
    {
        for (int i=0; m_pCurrNode->m_pchAttributes[i]; i+=3) 
            /* browse through the attributes list */
        {
            if (0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))
            {
                ret = (0 == strcmp(m_pCurrNode->m_pchAttributes[i+2], "true"))
                    ? true_: false_;
                return ret;
            }
        }    
    }
    else
    {
        m_nStatus = AXIS_FAIL;
    }
    return ret;        
}

unsigned int SoapDeSerializer::getAttributeAsUnsignedInt(const AxisChar* pName,
                                                         const AxisChar* 
                                                         pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(unsigned int,CONV_STRTOUL,INIT_VALUE_NUMBER)
}
short SoapDeSerializer::getAttributeAsShort(const AxisChar* pName, 
                                            const AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(short,CONV_STRTOL,INIT_VALUE_NUMBER)
}
unsigned short SoapDeSerializer::getAttributeAsUnsignedShort(const AxisChar* 
                                                             pName, 
                                                             const AxisChar* 
                                                             pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(unsigned short,CONV_STRTOUL,INIT_VALUE_NUMBER)
}
char SoapDeSerializer::getAttributeAsByte(const AxisChar* pName, const 
                                          AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(char,CONV_STRTOL,INIT_VALUE_NUMBER)
}
unsigned char SoapDeSerializer::getAttributeAsUnsignedByte(const AxisChar* 
                                                           pName, const 
                                                           AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(unsigned char,CONV_STRTOUL,INIT_VALUE_NUMBER)
}
long SoapDeSerializer::getAttributeAsLong(const AxisChar* pName, const 
                                          AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(long,CONV_STRTOL,INIT_VALUE_NUMBER)
}
long SoapDeSerializer::getAttributeAsInteger(const AxisChar* pName, const 
                                             AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(long,CONV_STRTOL,INIT_VALUE_NUMBER)
}
unsigned long SoapDeSerializer::getAttributeAsUnsignedLong(const AxisChar* 
                                                           pName, const 
                                                           AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(unsigned long,CONV_STRTOUL,INIT_VALUE_NUMBER)
}
float SoapDeSerializer::getAttributeAsFloat(const AxisChar* pName, const 
                                            AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(float,CONV_STRTOD,INIT_VALUE_NUMBER)
}
double SoapDeSerializer::getAttributeAsDouble(const AxisChar* pName, const 
                                              AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(double,CONV_STRTOD,INIT_VALUE_NUMBER)
}
double SoapDeSerializer::getAttributeAsDecimal(const AxisChar* pName, const 
                                               AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(double,CONV_STRTOD,INIT_VALUE_NUMBER)
}
AxisChar* SoapDeSerializer::getAttributeAsString(const AxisChar* pName, const 
                                                 AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(AxisChar*,CONV_STRDUP,INIT_VALUE_NUMBER)
}
AxisChar* SoapDeSerializer::getAttributeAsAnyURI(const AxisChar* pName, const 
                                                 AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(AxisChar*,CONV_STRDUP,INIT_VALUE_NUMBER)
}
AxisChar* SoapDeSerializer::getAttributeAsQName(const AxisChar* pName, const 
                                                AxisChar* pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(AxisChar*,CONV_STRDUP,INIT_VALUE_NUMBER)
}
xsd__hexBinary SoapDeSerializer::getAttributeAsHexBinary(const AxisChar* pName,
                                                         const AxisChar* 
                                                         pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(xsd__hexBinary,CONV_STRTOHEXBINARY, INIT_VALUE_XSDBINARY)
}
xsd__base64Binary SoapDeSerializer::getAttributeAsBase64Binary(const AxisChar* 
                                                               pName, const 
                                                               AxisChar* 
                                                               pNamespace)
{
    DESERIALIZE_GET_ATTRIBUTE_AS(xsd__base64Binary,CONV_STRTOBASE64BINARY, INIT_VALUE_XSDBINARY)
}
struct tm SoapDeSerializer::getAttributeAsDateTime(const AxisChar* pName, 
                                                   const AxisChar* pNamespace)
{
    XSDTYPE nType = XSD_DATETIME;
    DESERIALIZE_GET_ATTRIBUTE_AS(struct tm, CONV_STRTODATETIME, INIT_VALUE_DATETIME)
}
struct tm SoapDeSerializer::getAttributeAsDate(const AxisChar* pName, const 
                                               AxisChar* pNamespace)
{
    XSDTYPE nType = XSD_DATE;
    DESERIALIZE_GET_ATTRIBUTE_AS(struct tm, CONV_STRTODATETIME, INIT_VALUE_DATETIME)
}
struct tm SoapDeSerializer::getAttributeAsTime(const AxisChar* pName, const 
                                               AxisChar* pNamespace)
{
    XSDTYPE nType = XSD_DATE;
    DESERIALIZE_GET_ATTRIBUTE_AS(struct tm, CONV_STRTODATETIME, INIT_VALUE_DATETIME)
}
long SoapDeSerializer::getAttributeAsDuration(const AxisChar* pName, const 
                                              AxisChar* pNamespace)
{
    XSDTYPE nType = XSD_DURATION;
    DESERIALIZE_GET_ATTRIBUTE_AS(long, CONV_STRTODURATION,INIT_VALUE_NUMBER)
}

/*
 * Deserializing Elements as values directly. 
 */
xsd__boolean SoapDeSerializer::getElementAsBoolean(const AxisChar* pName,
                                                   const AxisChar* pNamespace)
{
    xsd__boolean ret = false_;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
        if (!m_pNode) return ret;
        if (XSD_BOOLEAN == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = (0 == strcmp(m_pNode->m_pchNameOrValue, "true")) 
                    ? true_: false_;
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                /* Some web services server returns 1 */
                ret = (0 == strcmp(m_pNode->m_pchNameOrValue, "true") || 
                    0 != strcmp(m_pNode->m_pchNameOrValue, "0" )) 
                    ? true_: false_;
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL; unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

int SoapDeSerializer::getElementAsInt(const AxisChar* pName, 
                                      const AxisChar* pNamespace)
{
    int ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_INT == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /*
                 * this is important in doc/lit style when deserializing 
                 * arrays
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL; unexpected SOAP stream */
        }
    }
    m_nStatus = ret; /* unexpected SOAP stream */
    return ret;
}


unsigned int SoapDeSerializer::getElementAsUnsignedInt(const AxisChar* pName,
                                                       const AxisChar* 
                                                       pNamespace)
{
    unsigned int ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
        if (!m_pNode) return ret;
        if (XSD_UNSIGNEDINT == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays 
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL; unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

short SoapDeSerializer::getElementAsShort(const AxisChar* pName, 
                                          const AxisChar* pNamespace)
{
    short ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
        if (!m_pNode) return ret;
        if (XSD_SHORT == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
        /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays
                 */
                return ret;
            }            
        }
        else
        {
            m_pNode = NULL;
            /* this is important in doc/lit style when deserializing arrays */
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

unsigned short SoapDeSerializer::getElementAsUnsignedShort(const AxisChar* 
                                                           pName, const 
                                                           AxisChar* pNamespace)
{
    unsigned short ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_UNSIGNEDSHORT == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL; unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

char SoapDeSerializer::getElementAsByte(const AxisChar* pName,
                                        const AxisChar* pNamespace)
{
    char ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_BYTE == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

unsigned char SoapDeSerializer::getElementAsUnsignedByte(const AxisChar* pName,
                                                         const AxisChar* pNamespace)
{
    unsigned char ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_UNSIGNEDBYTE == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must :  m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

long SoapDeSerializer::getElementAsLong(const AxisChar* pName,
                                        const AxisChar* pNamespace)
{
    long ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
        if (!m_pNode) return ret;
        if (XSD_LONG == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

long SoapDeSerializer::getElementAsInteger(const AxisChar* pName, 
                                           const AxisChar* pNamespace)
{
    long ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_INTEGER == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays 
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

unsigned long SoapDeSerializer::getElementAsUnsignedLong(const AxisChar* pName,
                                                         const AxisChar* 
                                                         pNamespace)
{
    unsigned long ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_UNSIGNEDLONG == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

float SoapDeSerializer::getElementAsFloat(const AxisChar* pName,
                                          const AxisChar* pNamespace)
{
    float ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_FLOAT == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

double SoapDeSerializer::getElementAsDouble(const AxisChar* pName,
                                            const AxisChar* pNamespace)
{
    double ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_DECIMAL == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

double SoapDeSerializer::getElementAsDecimal(const AxisChar* pName, 
                                             const AxisChar* pNamespace)
{
    double ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
        if (!m_pNode) return ret;
        if (XSD_DECIMAL == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }                        
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

AxisChar* SoapDeSerializer::getElementAsString(const AxisChar* pName, 
                                               const AxisChar* pNamespace)
{
    AxisChar* ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_STRING == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strdup(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strdup(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            } 
            else 
            {
            /* Should be an empty string or simpleType with xsi:nil="true" */
            ret = strdup("");
            /* this is because the string may not be available later */
            m_pNode = NULL;
            /* this is important in doc/lit style when deserializing arrays */
            return ret;
            }
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

AxisChar* SoapDeSerializer::getElementAsAnyURI(const AxisChar* pName, 
                                               const AxisChar* pNamespace)
{
    AxisChar* ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_ANYURI == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strdup(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strdup(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

AxisChar* SoapDeSerializer::getElementAsQName(const AxisChar* pName, 
                                              const AxisChar* pNamespace)
{
    AxisChar* ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_QNAME == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strdup(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = strdup(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }            
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

xsd__hexBinary SoapDeSerializer::getElementAsHexBinary(const AxisChar* pName,
                                                       const AxisChar* 
                                                       pNamespace)
{
    xsd__hexBinary ret = {0,0};
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_HEXBINARY == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = decodeFromHexBinary(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = decodeFromHexBinary(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }            
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_pNode = NULL;/*m_nStatus = AXIS_FAIL;*/ /* unexpected SOAP stream */
    return ret;
}

xsd__base64Binary SoapDeSerializer::decodeFromBase64Binary(const AxisChar* 
                                                           pValue)
{
  xsd__base64Binary value;
  value.__size = apr_base64_decode_len(pValue);
  value.__ptr = (unsigned char*) malloc(value.__size+1);
  value.__size = apr_base64_decode_binary(value.__ptr, pValue);
  /* put null at the end because it enables the decoded string to be used
   * as a string 
   */
  value.__ptr[value.__size] = 0;
  return value;
}

xsd__hexBinary SoapDeSerializer::decodeFromHexBinary(const AxisChar* pValue)
{
  xsd__hexBinary value;
  value.__size = strlen(pValue)/2;
  value.__ptr = (unsigned char*) malloc(value.__size+1);
  Hex_Decode(value.__ptr, pValue);
  /* put null at the end because it enables the decoded string to be used
   * as a string 
   */
  value.__ptr[value.__size] = 0;
  return value;
}

xsd__base64Binary SoapDeSerializer::getElementAsBase64Binary(const AxisChar* pName, 
                                                             const AxisChar* 
                                                             pNamespace)
{
    xsd__base64Binary ret = {0,0};
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_BASE64BINARY == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = decodeFromBase64Binary(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = decodeFromBase64Binary(m_pNode->m_pchNameOrValue);
                /* this is because the string may not be available later */
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }            
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_pNode = NULL;/*    m_nStatus = AXIS_FAIL;*/ /* unexpected SOAP stream */
    return ret;
}

struct tm SoapDeSerializer::getElementAsDateTime(const AxisChar* pName, 
                                                 const AxisChar* pNamespace)
{
    struct tm ret = INIT_VALUE_DATETIME;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_DATETIME == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserialize(m_pNode->m_pchNameOrValue, XSD_DATETIME);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i>*/
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            if (0 != m_pNode->m_pchAttributes[0])
            {
                m_pCurrNode = m_pNode;
                /*
                 * Need to verify if the return value is NULL.
                 */
                if ( getAttributeAsBoolean("nil",0) == true_ )
                {
                    m_pParser->next();
                    m_pNode = NULL;
                    return ret;
                }
            }            
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserialize(m_pNode->m_pchNameOrValue, 
                    XSD_DATETIME);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }            
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

struct tm SoapDeSerializer::getElementAsDate(const AxisChar* pName, 
                                             const AxisChar* pNamespace)
{
    struct tm ret = INIT_VALUE_DATETIME;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_DATE == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserialize(m_pNode->m_pchNameOrValue, 
                    XSD_DATE);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            if (0 != m_pNode->m_pchAttributes[0])
            {
                m_pCurrNode = m_pNode;
                /*
                 * Need to verify if the return value is NULL.
                 */
                if ( getAttributeAsBoolean("nil",0) == true_ )
                {
                    m_pParser->next();
                    m_pNode = NULL;
                    return ret;
                }
            }            
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserialize(m_pNode->m_pchNameOrValue, 
                    XSD_DATE);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing
                 * arrays 
                 */
                return ret;
            }            
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

struct tm SoapDeSerializer::getElementAsTime(const AxisChar* pName, 
                                             const AxisChar* pNamespace)
{
    struct tm ret = INIT_VALUE_DATETIME;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_TIME == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserialize(m_pNode->m_pchNameOrValue, 
                    XSD_TIME);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            if (0 != m_pNode->m_pchAttributes[0])
            {
                m_pCurrNode = m_pNode;
                /*
                 * Need to verify if the return value is NULL.
                 */
                if ( getAttributeAsBoolean("nil",0) == true_ )
                {
                    m_pParser->next();
                    m_pNode = NULL;
                    return ret;
                }
            }            
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserialize(m_pNode->m_pchNameOrValue, 
                    XSD_TIME);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }            
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

long SoapDeSerializer::getElementAsDuration(const AxisChar* pName, 
                                            const AxisChar* pNamespace)
{
    long ret = 0;
    if (AXIS_SUCCESS != m_nStatus) return ret;
    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next();
        /* wrapper node with type info  Ex: <i xsi:type="xsd:int"> */
        if (!m_pNode) return ret;
        if (XSD_DURATION == getXSDType(m_pNode))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserializeDuration(m_pNode->m_pchNameOrValue, 
                    XSD_DURATION);
                m_pNode = m_pParser->next(); /* skip end element node too */
                return ret;
            }
        }
        else
        {
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        if (!m_pNode)
            /* if there is an unprocessed node that may be one left from last 
             * array deserialization 
             */
            m_pNode = m_pParser->next();
            /* wrapper node without type info  Ex: <i> */
        if (!m_pNode) return ret;
        if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
        {
            m_pNode = m_pParser->next(true); /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                ret = AxisTime::deserializeDuration(m_pNode->m_pchNameOrValue, 
                    XSD_DURATION);
                m_pNode = m_pParser->next(); /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays 
                 */
                return ret;
            }            
        }
        else
        {
            return ret;
            /* Not a must : m_nStatus = AXIS_FAIL;  unexpected SOAP stream */
        }
    }
    m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
    return ret;
}

/*
 * This method checks the attribute list of pElement node for the xsi:type 
 * attribute. If it is found then finds what the type is. Otherwise returns 
 * XSD_UNKNOWN.
 */
XSDTYPE SoapDeSerializer::getXSDType(const AnyElement* pElement)
{
    /* first check whether this is a start element node */
    if (START_ELEMENT != pElement->m_type) return XSD_UNKNOWN;
    for (int i=0; pElement->m_pchAttributes[i]; i+=3)
    {
        if (URI_XSI == URIMapping::map(pElement->m_pchAttributes[i+1]))
        {
            ::QName qn;
            XSDTYPE type = XSD_UNKNOWN;
            qn.splitQNameString(pElement->m_pchAttributes[i+2], ':');
            const char* pNS = m_pParser->getNS4Prefix(qn.uri);
            if (pNS)
            {
                if (URI_XSD == URIMapping::map(pNS))
                {
                    type = TypeMapping::map(qn.localname);
                }
            }
            qn.mergeQNameString(':');
            return type;
        }
    }
    return XSD_UNKNOWN;
}
/*
void* SoapDeSerializer::CreateArray(XSDTYPE nType, int nSize)
{
    switch (nType)
    {
    case XSD_INT:
    case XSD_UNSIGNEDINT:
    case XSD_BOOLEAN:
        return new xsd__boolean[nSize];
    case XSD_FLOAT:
        return new float[nSize];
    case XSD_STRING:
    case XSD_HEXBINARY:
    case XSD_BASE64BINARY:
    case XSD_ANYURI:
    case XSD_QNAME:
    case XSD_NOTATION:
        return new AxisString[nSize];
    case XSD_LONG:
    case XSD_UNSIGNEDLONG:
    case XSD_INTEGER:
    case XSD_DURATION:
        return new long[nSize];
    case XSD_SHORT:
    case XSD_UNSIGNEDSHORT:
        return new short[nSize];
    case XSD_BYTE:
    case XSD_UNSIGNEDBYTE:
        return new char[nSize];
    case XSD_DOUBLE:
    case XSD_DECIMAL:
        return new double[nSize];
    case XSD_DATETIME:
    case XSD_TIME:
    case XSD_DATE:
    case XSD_YEARMONTH:
    case XSD_YEAR:
    case XSD_MONTHDAY:
    case XSD_DAY:
    case XSD_MONTH:
        return new tm[nSize];
    default:
        return NULL;
    }
}

void SoapDeSerializer::DeleteArray(Axis_Array* pArray , XSDTYPE nType)
{
    switch (nType)
    {
    case XSD_INT:
    case XSD_UNSIGNEDINT:
    case XSD_BOOLEAN:
        delete [] ((int*)pArray->m_Array); break;
    case XSD_FLOAT:
        delete [] ((float*)pArray->m_Array); break;
    case XSD_STRING:
    case XSD_HEXBINARY:
    case XSD_BASE64BINARY:
    case XSD_ANYURI:
    case XSD_QNAME:
    case XSD_NOTATION:
        delete [] ((AxisString*)pArray->m_Array); break;
    case XSD_LONG:
    case XSD_UNSIGNEDLONG:
    case XSD_INTEGER:
    case XSD_DURATION:
        delete [] ((long*)pArray->m_Array); break;
    case XSD_SHORT:
    case XSD_UNSIGNEDSHORT:
        delete [] ((short*)pArray->m_Array); break;
    case XSD_BYTE:
    case XSD_UNSIGNEDBYTE:
        delete [] ((char*)pArray->m_Array); break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
        delete [] ((double*)pArray->m_Array); break;
    case XSD_DATETIME:
    case XSD_TIME:
    case XSD_DATE:
    case XSD_YEARMONTH:
    case XSD_YEAR:
    case XSD_MONTHDAY:
    case XSD_DAY:
    case XSD_MONTH:
        delete [] ((tm*)pArray->m_Array); break;
    default:
        break;
    }
    pArray->m_Array = NULL;
    pArray->m_Size = 0;
}
*/

/*
 * Used by the Axis Engine to get any left header blocks in the deserializer 
 * even after the completion of message path. Then those headers will be added
 * to the serializer because they are probably headers targetted to nex soap 
 * processors.
 */
HeaderBlock* SoapDeSerializer::getHeaderBlock()
{
    if (!m_pHeader) return NULL;

    return (HeaderBlock*)m_pHeader->getHeaderBlock();
}
/*
 * Used probably by a handler to add a header block to the Deserializer.
 * Probably to be used by a subsequent handler in the request message path
 */
int AXISCALL SoapDeSerializer::addHeaderBlock(IHeaderBlock* pBlk)
{
    if (!m_pHeader) m_pHeader = new SoapHeader();
    m_pHeader->addHeaderBlock((HeaderBlock*)pBlk);
    return AXIS_SUCCESS;
}

xsd__hexBinary SoapDeSerializer::getBodyAsHexBinary()
{
    /* TODO */
    xsd__hexBinary hb = {0,0};
    return hb;
}

xsd__base64Binary SoapDeSerializer::getBodyAsBase64Binary()
{
    /* TODO */
    xsd__base64Binary bb = {0,0};
    return bb;
}

int SoapDeSerializer::setNewSoapBody(AxisChar* pNewSoapBody)
{
    /* TODO */
    return 0;
}

bool SoapDeSerializer::isAnyMustUnderstandHeadersLeft()
{
    /* TODO */
    return false;
}

int SoapDeSerializer::flushInputStream()
{
    int nChars = 100;
    char pBuffer[100];
	if (!m_pInputStream) return AXIS_FAIL;
	while (TRANSPORT_IN_PROGRESS == m_pInputStream->getBytes(pBuffer, &nChars));
	return AXIS_SUCCESS;
}
