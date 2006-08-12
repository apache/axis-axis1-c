/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/* SoapDeSerializer.cpp: implementation of the SoapDeSerializer class. */

/*
 * Revision 1.1  2004/06/10 roshan
 * Fixed the bug AXISCPP-95 at JIRA.
 */

/*
 * Revision 1.2  2004/07/22 roshan
 * Changed code to support proper parsing of incoming SOAP Headers. The 
 *  SoapDeSerializer::getHeader() method was completely rewriten.
 */

/*
 * Revision 1.3  2004/11/27 roshan
 * Added the implementation of the setNewSoapBody() method.
 */

#ifdef WIN32
#pragma warning (disable : 4101)
#endif

#include "SoapDeSerializer.h"
#include "SoapEnvelope.h"
#include "SoapKeywordMapping.h"
#include "URIMapping.h"
#include "SoapHeader.h"
#include "SoapMethod.h"
#include "SoapBody.h"
#include "SoapFault.h"
#include "ComplexElement.h"
#include "CharacterElement.h"
#include <axis/GDefine.hpp>
#include "../common/AxisTrace.h"
#include "apr_base64.h"
#include "HexCoder.h"
#include "../engine/XMLParserFactory.h"
#include "../xml/XMLParser.h"
#include "../xml/QName.h"
#include "AxisSoapException.h"
#include "../common/AxisGenException.h"
#include "../common/AxisTrace.h"
#include <axis/Axis.hpp>

#include <list>
#include <iostream>
AxisChar * pBodyContent;

AXIS_CPP_NAMESPACE_START
#define INITIAL_ARRAY_SIZE 1

SoapDeSerializer::SoapDeSerializer ()
{
    m_pParser = XMLParserFactory::getParserObject ();
    m_pEnv = NULL;
    m_pHeader = NULL;
    m_pInputStream = 0;
    m_nStatus = AXIS_SUCCESS;
}

SoapDeSerializer::~SoapDeSerializer ()
{
    if (m_pEnv)
        delete m_pEnv;
    if (m_pHeader)
        delete m_pHeader;
    if (m_pParser)
        XMLParserFactory::destroyParserObject (m_pParser);
    if(pBodyContent)
        delete pBodyContent;
}

int
SoapDeSerializer::setInputStream (SOAPTransport * pInputStream)
{
    if (NULL == pInputStream)
        return AXIS_FAIL;

    m_pInputStream = pInputStream;

    return m_pParser->setInputStream (pInputStream);
}

SoapEnvelope *
SoapDeSerializer::getEnvelope ()
{
    Attribute *pAttr = NULL;

    if (!m_pNode)
        m_pNode = m_pParser->next ();

    if (!m_pNode || (START_ELEMENT != m_pNode->m_type))
        return NULL;

    if (0 == strcmp (m_pNode->m_pchNameOrValue,
                     SoapKeywordMapping::map (SOAP_VER_1_2).pchWords[SKW_ENVELOPE]))
    {
        SoapEnvelope *m_pEnvl = new SoapEnvelope ();
        /* set all attributes of SoapEnvelope */
        std::list<Attribute*> attributeList0;
        pAttr = new Attribute ( attributeList0);

        pAttr->setValue (m_pNode->m_pchNamespace);
        m_pEnvl->addNamespaceDecl (pAttr);

        if (0 == strcmp (m_pNode->m_pchNamespace,
                         SoapKeywordMapping::map (SOAP_VER_1_1).pchNamespaceUri))
            m_nSoapVersion = SOAP_VER_1_1;
        else if (0 == strcmp (m_pNode->m_pchNamespace,
                              SoapKeywordMapping::map (SOAP_VER_1_2).pchNamespaceUri))
            m_nSoapVersion = SOAP_VER_1_2;
        else
            m_nSoapVersion = VERSION_LAST;

        /* Set Attributes */
        for (int i = 0; m_pNode->m_pchAttributes[i]; i += 3)
        {
            std::list<Attribute*> attributeList1;
            pAttr = new Attribute (attributeList1);
            pAttr->setLocalName (m_pNode->m_pchAttributes[i]);
            pAttr->setURI (m_pNode->m_pchAttributes[i + 1]);
            pAttr->setValue (m_pNode->m_pchAttributes[i + 2]);
            m_pEnvl->addAttribute (pAttr);
        }

        m_pNode = NULL; /* This is to indicate that node is identified and used */
        return m_pEnvl;
    }

    return NULL;
}

/*
 * Header block parsing should be done differently for different SOAP versions.
 * Since the Header blocks may be requested in a different order than it is in 
 * the SOAP stream there must be a mechanism to manage the situation. Possibly 
 * to re-parse the stream part which has unused header blocks.
 */
IHeaderBlock *
SoapDeSerializer::getHeaderBlock (const AxisChar * pName,
                                  const AxisChar * pNamespace)
{
    if (!m_pHeader)
        return NULL; /* no <Header> element so there can be no Header blocks */

    return m_pHeader->getHeaderBlock (pName, pNamespace, true);
}

int
SoapDeSerializer::getHeader ()
{
    if (m_pHeader)
        return m_nStatus;

    m_pNode = m_pParser->next ();

    if (!m_pNode)        /* this means a SOAP error */
    {
        m_nStatus = AXIS_FAIL;
        return m_nStatus;
    }

    if ((START_ELEMENT == m_pNode->m_type) &&
        (0 == strcmp (m_pNode->m_pchNameOrValue,
                      SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_HEADER])))
    {
        if (m_pHeader)
            delete m_pHeader;

        m_pHeader = new SoapHeader ();
        
        /* Set any attributes/namspaces to the SoapHeader object */
        bool blnMainLoopContStatus = true;

        while (blnMainLoopContStatus)
        {
            m_pNode = m_pParser->next (true);
    
            if (!m_pNode)
            {
               m_nStatus = AXIS_FAIL;
               return m_nStatus;
            }
    
            if ((END_ELEMENT == m_pNode->m_type) &&
                (0 == strcmp (m_pNode->m_pchNameOrValue,
                              SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_HEADER])))
            {
                m_pNode = NULL; /* indicate that node is identified and used */
                return m_nStatus;
                break;
            }
    
            /* The following is done to ignore anything (eg : the toplevel 
               whitespaces) but a start element. */
            if (START_ELEMENT != m_pNode->m_type)
                continue;
    
            HeaderBlock *pHeaderBlock = new HeaderBlock ();
    
            if (m_pNode->m_pchNamespace)
                pHeaderBlock->setURI (m_pNode->m_pchNamespace);
    
            pHeaderBlock->setLocalName (m_pNode->m_pchNameOrValue);
    
            if ((m_pNode->m_pchAttributes[0]) != NULL)
            {
                int iAttributeArrayIndex = 0;
        
                while (true)
                {
                    std::list<Attribute*> attributeList2;
                    Attribute *pAttribute = new Attribute (attributeList2);
                    pAttribute->setLocalName (m_pNode->m_pchAttributes[iAttributeArrayIndex++]);
                    pAttribute->setURI (m_pNode->m_pchAttributes[iAttributeArrayIndex++]);
                    pAttribute->setValue (m_pNode->m_pchAttributes[iAttributeArrayIndex++]);
        
                    pHeaderBlock->addAttribute (pAttribute);
        
                    if (m_pNode->m_pchAttributes[iAttributeArrayIndex] == '\0')
                        break;
                }
            }
    
            BasicNode **pNodeList = new BasicNode *[10];
            int iListPos = 0;
            int iLevel = 0;
            bool bContinue = true;
    
            while (bContinue)
            {
                m_pNode = m_pParser->next (true);
        
                if (END_ELEMENT == m_pNode->m_type)
                {
                    if (iLevel == 0)
                    {
                        //do nothing
                        m_pHeader->addHeaderBlock (pHeaderBlock);
                        bContinue = false;
                    }
                    else if (iLevel == 1)
                    {
                        if ((pNodeList[0]) != NULL)
                        {
                            //addToHeaderBlock(pNodeList[0]);
                            pHeaderBlock->addChild (pNodeList[0]);
                            /* Commented by Rangika since with this part the logic is wrong
                            //m_pHeader->addHeaderBlock (pHeaderBlock);
                            //m_pParser->next (true);    //To skip the end element of the HeaderBlock
                            //bContinue = false;
                            */
                            iListPos--;
                            iLevel--;
                        }
                    }
                    else
                    {
                        //addToImmediateParent(pNodeList, iListPos);
                        (pNodeList[iListPos - 2])->
                            addChild (pNodeList[iListPos - 1]);
                        iListPos--;
                        iLevel--;
                    }
                }
                else if (START_ELEMENT == m_pNode->m_type)
                {
                    //createBaisNode and setValue
                    BasicNode *pComplexElement = new ComplexElement ();
        
                    if (m_pNode->m_pchNamespace)
                        pComplexElement->setURI (m_pNode->m_pchNamespace);
        
                    pComplexElement->setLocalName (m_pNode->m_pchNameOrValue);
        
                    //addtoList
                    pNodeList[iListPos] = pComplexElement;
                    iListPos++;
                    iLevel++;
                }
                else if (CHARACTER_ELEMENT == m_pNode->m_type)
                {
                    //createBasicNode and setValue
                    BasicNode *pBasicNode =
                    new CharacterElement (m_pNode->m_pchNameOrValue);
        
                    //addToImmidiateParent
                    if (iLevel == 0)
                        pHeaderBlock->addChild (pBasicNode);
                    else
                        (pNodeList[iListPos - 1])->addChild (pBasicNode);
                }
            } // end while
                
            // clean memory
            delete [] pNodeList;
        }
    }

    return m_nStatus;
}

// This method adds to allow "all" & "choice" constructs to peek head next element.
const char*
SoapDeSerializer::peekNextElementName ()
{ 
    if (m_pParser)
    {
        const char* name = m_pParser->peek ();
        return name;
    }
            
    return NULL;
}

int
SoapDeSerializer::getBody ()
{
    if (!m_pNode)
        m_pNode = m_pParser->next ();

    /* previous header searching may have left a node unidentified */
    if (m_pNode)
    {
        if ((START_ELEMENT == m_pNode->m_type) &&
            (0 == strcmp (m_pNode->m_pchNameOrValue,
                          SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])))
        {
            /* Set any attributes/namspaces to the SoapBody object */
            m_pNode = NULL;    /* indicate that node is identified and used */
    
            // peek for the method name
            m_strMethodNameToInvoke = m_pParser->peek();
            return AXIS_SUCCESS;
        }
    }

    m_nStatus = AXIS_FAIL;
    return AXIS_FAIL;
}

int
SoapDeSerializer::checkMessageBody (const AxisChar * pName,
                                    const AxisChar * pNamespace)
{
    if (!m_pNode)
        m_pNode = m_pParser->next ();

    if (!m_pNode || (START_ELEMENT != m_pNode->m_type))
        throw AxisGenException (SERVER_UNKNOWN_ERROR);

    if (0 != strcmp (m_pNode->m_pchNameOrValue, pName))
    {
        /* A soap fault has occurred. we will deserialize it as doc literal
         * So we set the style as doc literal. This way of doing things
         * is not so nice. I'll rectify this asap
         */
        setStyle (DOC_LITERAL);
        AXISTRACE1 ("AXISC_NODE_VALUE_MISMATCH_EXCEPTION", CRITICAL);
        throw AxisGenException (AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
    }

    /* we can check the namespace uri too here. Should we ? */
    m_pNode = NULL; /* indicate that node is identified and used */

    return AXIS_SUCCESS;
}

void *
SoapDeSerializer::checkForFault (const AxisChar * pName,
                                 const AxisChar * pNamespace)
{
    const char *pcCmplxFaultName;
    char *pcDetail;
    char *pcFaultCode;
    char *pcFaultstring;
    char *pcFaultactor;
    if (0 == strcmp ("Fault", pName))
    {
        if (0 != strcmp (m_pNode->m_pchNameOrValue, pName))
        {
            m_nStatus = AXIS_SUCCESS;
            m_pNode = NULL;
            AXISTRACE1 ("AXISC_NODE_VALUE_MISMATCH_EXCEPTION", CRITICAL);
            throw AxisGenException (AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
        }
    
        /* we can check the namespace uri too here. Should we ? */
        m_nStatus = AXIS_SUCCESS;
        m_pNode = NULL;  /* indicate that node is identified and used */
        SoapFault *pFault = new SoapFault ();
        pFault->setDeSerializer (this);
        m_nStyle = getStyle ();
    
        /*We deserialize fault code in doc literal. */
        setStyle (DOC_LITERAL);
        pcFaultCode = getElementAsString ("faultcode", 0);
        pFault->setFaultcode (pcFaultCode == NULL ? "" : pcFaultCode);
        if ( pcFaultCode )
            delete [] pcFaultCode;
        
        pcFaultstring = getElementAsString ("faultstring", 0);
        pFault->setFaultstring (pcFaultstring == NULL ? "" : pcFaultstring);
        if ( pcFaultstring )
            delete [] pcFaultstring;
     
        pcFaultactor = getElementAsString ("faultactor", 0);
        pFault->setFaultactor (pcFaultactor == NULL ? "" : pcFaultactor);
        if ( pcFaultactor )
            delete [] pcFaultactor;
    
        // FJP Changed the namespace from null to a single space (an impossible
        //     value) to help method know that it is parsing a fault message.
        pcDetail = getElementAsString ("detail", " ");
        
        if (pcDetail)
        {
            pFault->setFaultDetail (pcDetail);
            delete [] pcDetail;          
        }
        else
        {
            pcCmplxFaultName = getCmplxFaultObjectName ();
            pFault->setCmplxFaultObjectName (pcCmplxFaultName == NULL ? "" : pcCmplxFaultName);
            /*    if ( pcCmplxFaultName )
                    delete [] (reinterpret_cast <char *> (pcCmplxFaultName) );
            */
        }
    
        setStyle (m_nStyle);
        return pFault;
    }
    else
        throw AxisGenException (AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
}

int
SoapDeSerializer::init ()
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

int
SoapDeSerializer::getVersion ()
{
    if (VERSION_LAST == m_nSoapVersion)
    {
        if (m_pEnv)
            delete m_pEnv;
        m_pEnv = getEnvelope ();
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
 
void SoapDeSerializer::deserializeLiteralComplexArray(Axis_Array * pArray, 
                                                      void *pDZFunct,
                                                      void *pCreFunct, 
                                                      void *pDelFunct,
                                                      const AxisChar * pName, 
                                                      const AxisChar * pNamespace)
{
    while(true)
    {
        const char* elementName = peekNextElementName();
        if(strcmp(elementName, pName) == 0)
            pArray->addElement(getCmplxObject(pDZFunct, pCreFunct, pDelFunct, pName, pNamespace));
        else
            return;
    }
}

void SoapDeSerializer::deserializeEncodedComplexArray(Axis_Array * pArray, 
                                                      void *pDZFunct,
                                                      void *pCreFunct, 
                                                      void *pDelFunct, 
                                                      const AxisChar * pName, 
                                                      const AxisChar * pNamespace, 
                                                      int size)
{
    for (int count = 0 ; count < size; count++)
    {
        const char* elementName = peekNextElementName();
        if(strcmp(elementName, pName) != 0)
            pArray->addElement(getCmplxObject(pDZFunct, pCreFunct, pDelFunct, pName, pNamespace));
        else
            return;
    }
}

Axis_Array*
SoapDeSerializer::getCmplxArray ( Axis_Array* pArray, 
                                  void *pDZFunct,
                                  void *pCreFunct, 
                                  void *pDelFunct, 
                                  const AxisChar * pName, 
                                  const AxisChar * pNamespace)
{
    /* if anything has gone wrong earlier just do nothing */
    if (AXIS_SUCCESS != m_nStatus)
        return pArray;

    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next ();
        /* just skip wrapper node with type info
         * Ex:<tns:QuoteInfoTypeArray xmlns:tns="http://www.getquote.org/test">
         */
        if (!m_pNode)
            return pArray;
    
        // Look for an empty array
        if (END_ELEMENT == m_pNode->m_type)
            return pArray;
    
        int arraySize = getArraySize (m_pNode);
    
        if (arraySize == 0)
        {
            m_pNode = m_pParser->next ();   /* skip end element node too */
            return pArray;
        }
        else if (arraySize > 0)
        {
            deserializeEncodedComplexArray(pArray, pDZFunct, pCreFunct, pDelFunct,
                                           pName, pNamespace, arraySize);
            
            if (m_nStatus != AXIS_FAIL)
                return pArray;
            }
        }
    else
    {
        deserializeLiteralComplexArray(pArray, pDZFunct, pCreFunct, pDelFunct,
                                       pName, pNamespace);

        if (m_nStatus != AXIS_FAIL)
            return pArray;
    }
    
    m_nStatus = AXIS_FAIL;
    m_pNode = NULL;

    return pArray;
}


/*
 * Get Size of the single dimension array from arrayType attribute
 * Ex : enc:arrayType="xs:string[6]"
 */
int
SoapDeSerializer::getArraySize (const AnyElement * pElement)
{
    int nSize = -1;
    
    /* first check whether this is a start element node */
    if (START_ELEMENT != pElement->m_type)
        return nSize;

    for (int i = 0; pElement->m_pchAttributes[i]; i += 3)
    {
        if (URI_ENC == URIMapping::getURI (pElement->m_pchAttributes[i + 1])
            && (0 == strcmp (pElement->m_pchAttributes[i],
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_ARRAYTYPE])))
        {
            QName qn;
    
            qn.splitQNameString (pElement->m_pchAttributes[i + 2], '[');
            nSize = strtol (qn.localname, &m_pEndptr, 10);
            qn.mergeQNameString ('[');
    
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
void SoapDeSerializer::deserializeEncodedArray (Axis_Array* pArray, 
                                                IAnySimpleType* pSimpleType, 
                                                const AxisChar* pName, 
                                                const AxisChar* pNamespace, 
                                                int size)
{
    for (int count = 0 ; count < size; count++)
    {
        const char* elementName = peekNextElementName();
        if(strcmp(elementName, pName) != 0)
        {
            getElement(pName, pNamespace, pSimpleType, true);
            void * pValue = pSimpleType->getValue();
            pArray->addElement(pValue);
            Axis::AxisDelete(pValue, pSimpleType->getType());
        }
        else
            return;
    }
}

void SoapDeSerializer::deserializeLiteralArray (Axis_Array* pArray, 
                                                IAnySimpleType* pSimpleType, 
                                                const AxisChar* pName, 
                                                const AxisChar* pNamespace)
{
    while(true)
    {
        const char* elementName = peekNextElementName();
        if(strcmp(elementName, pName) == 0)
        {
            getElement(pName, pNamespace, pSimpleType);
            void * pValue = pSimpleType->getValue();
            pArray->addElement(pValue);
            Axis::AxisDelete(pValue, pSimpleType->getType());
        }
        else
            return;
    }
}

Axis_Array*
SoapDeSerializer::getBasicArray (XSDTYPE nType,
                                 const AxisChar * pName,
                                 const AxisChar * pNamespace)
{
    Axis_Array* Array = new Axis_Array();
    Array->m_Type = nType;

    /* if anything has gone wrong earlier just do nothing */
    if (AXIS_SUCCESS != m_nStatus)
        return Array;

    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next ();
    
        /* just skip wrapper node with type info  Ex: <tns:ArrayOfPhoneNumbers
         * xmlns:tns="http://www.getquote.org/test">
         */
        if (!m_pNode)
            return Array;
    
        int size = getArraySize (m_pNode);
    
        if (size == 0)
        {
            m_pNode = m_pParser->next ();    /* skip end element node too */
            return Array;
        }
        else if (size > 0)
        {
            IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(nType);
            deserializeEncodedArray(Array, pSimpleType, pName, pNamespace, size);
            delete pSimpleType;
            
            if ( m_nStatus != AXIS_FAIL)
                return Array;     
        }
    }
    else
    {
        IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(nType);
        deserializeLiteralArray(Array, pSimpleType, pName, pNamespace);
        delete pSimpleType;
        
        if ( m_nStatus != AXIS_FAIL)
            return Array;   
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
void *
SoapDeSerializer::getCmplxObject (void *pDZFunct, 
                                  void *pCreFunct,
                                  void *pDelFunct, 
                                  const AxisChar * pName,
                                  const AxisChar * pNamespace)
{
    /* if anything has gone wrong earlier just do nothing */
    if (AXIS_SUCCESS != m_nStatus)
        return NULL;

    if (RPC_ENCODED == m_nStyle)
    {
        m_pNode = m_pParser->next ();
        /* just skip wrapper node with type info
         * Ex: <tns:QuoteInfoType xmlns:tns="http://www.getquote.org/test"> */
        if (!m_pNode)
            return NULL;
        /* type  can be checked here */
        TRACE_OBJECT_CREATE_FUNCT_ENTRY(pCreFunct, 0);
        void *pObject = ((AXIS_OBJECT_CREATE_FUNCT) pCreFunct) (0);
        TRACE_OBJECT_CREATE_FUNCT_EXIT(pCreFunct, pObject);
        if (pObject && pDZFunct)
        {
            if (C_RPC_PROVIDER == getCurrentProviderType ())
            {
                // Disable C support
                //IWrapperSoapDeSerializer_C cWSD;
                //cWSD._object = this;
                //cWSD._functions = &IWrapperSoapDeSerializer::ms_VFtable;
                //m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pObject, &cWSD);
            }
            else
            {
                TRACE_DESERIALIZE_FUNCT_ENTRY(pDZFunct, pObject, this);
                m_nStatus =    ((AXIS_DESERIALIZE_FUNCT) pDZFunct) (pObject, this);
                TRACE_DESERIALIZE_FUNCT_EXIT(pDZFunct, m_nStatus);
            }
            
            if (AXIS_SUCCESS == m_nStatus)
            {
                m_pParser->next ();    /* skip end node too */
                return pObject;
            }
            else
            {
                TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, 0);
                ((AXIS_OBJECT_DELETE_FUNCT) pDelFunct) (pObject, 0);
                TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);
            }
        }
    }
    else
    {
        /* if there is an unprocessed node that may be one left from 
         * last array deserialization */
        if (!m_pNode)
            m_pNode = m_pParser->next ();
            
        /* wrapper node without type info  Ex: <result> */
        if (!m_pNode)
            return NULL;
            
        if (0 == strcmp (pName, m_pNode->m_pchNameOrValue))
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
                xsd__boolean * isNill = getAttributeAsBoolean("nil", 0);
                if (NULL != isNill)
                {
                    if(true_ == *isNill)
                    {
                        m_pParser->next ();
                        m_pNode = NULL;
                        delete isNill;
                        return NULL;
                    } 
                    else 
                        delete isNill; 
                }
            }
            
            m_pNode = NULL;    /* node identified and used */
    
            TRACE_OBJECT_CREATE_FUNCT_ENTRY(pCreFunct, 0);
            void *pObject = ((AXIS_OBJECT_CREATE_FUNCT) pCreFunct)(0);
            TRACE_OBJECT_CREATE_FUNCT_EXIT(pCreFunct, pObject);
    
            if (pObject && pDZFunct)
            {
                TRACE_DESERIALIZE_FUNCT_ENTRY(pDZFunct, pObject, this);
                m_nStatus =    ((AXIS_DESERIALIZE_FUNCT) pDZFunct) (pObject, this);
                TRACE_DESERIALIZE_FUNCT_EXIT(pDZFunct, m_nStatus);

                if (AXIS_SUCCESS == m_nStatus)
                {
                    m_pParser->next ();    /* skip end node too */
                    m_pNode = NULL;    /* AXISCPP-978 node identified and used */
                    return pObject;
                }
                else
                {
                    TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, 0);
                    ((AXIS_OBJECT_DELETE_FUNCT) pDelFunct) (pObject, 0);
                    TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);
                }
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
    
    m_nStatus = AXIS_FAIL;    /* unexpected SOAP stream */

    return NULL;
}

const char *
SoapDeSerializer::getCmplxFaultObjectName ()
{
    
    // Skip the faultdetail tag
    if (!m_pNode)
        m_pParser->next ();
        
    m_nStatus = AXIS_SUCCESS;

    if (AXIS_SUCCESS != m_nStatus)
        return NULL;
        
    /* if anything has gone wrong earlier just do nothing */
    if (RPC_ENCODED == m_nStyle)
    {
        m_pParser->next ();
        
        /* just skip wrapper node with type info
         * Ex: <tns:QuoteInfoType xmlns:tns="http://www.getquote.org/test"> 
         */
        if (!m_pNode)
            return NULL;
            
        return m_pNode->m_pchNameOrValue;
    }
    else
    {
        if (!m_pNode)
        {
            /* if there is an unprocessed node that may be one left from 
             * last array deserialization */
            m_pNode = m_pParser->next ();
            /* wrapper node without type info  Ex: <result> */
        }
    
        if (!m_pNode)
            return NULL;
            
        return m_pNode->m_pchNameOrValue;
    }
}

void *
SoapDeSerializer::getCmplxFaultObject (void *pDZFunct, 
                                       void *pCreFunct,
                                       void *pDelFunct,
                                       const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    if (RPC_ENCODED == m_nStyle)
    {
        /* type  can be checked here */
        TRACE_OBJECT_CREATE_FUNCT_ENTRY(pCreFunct,0);
        void *pObject = ((AXIS_OBJECT_CREATE_FUNCT) pCreFunct) (0);
        TRACE_OBJECT_CREATE_FUNCT_EXIT(pCreFunct, pObject);
    
        if (pObject && pDZFunct)
        {
            if (C_RPC_PROVIDER == getCurrentProviderType ())
            {
            // Disable C support
            //IWrapperSoapDeSerializer_C cWSD;
            //cWSD._object = this;
            //cWSD._functions = &IWrapperSoapDeSerializer::ms_VFtable;
            //m_nStatus = ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pObject, &cWSD);
            }
            else
            {
                TRACE_DESERIALIZE_FUNCT_ENTRY(pDZFunct, pObject, this);
                m_nStatus =    ((AXIS_DESERIALIZE_FUNCT) pDZFunct) (pObject, this);
                TRACE_DESERIALIZE_FUNCT_EXIT(pDZFunct, m_nStatus);
            }
            
            if (AXIS_SUCCESS == m_nStatus)
            {
                m_pParser->next ();    /* skip end node too */
                return pObject;
            }
            else
            {
                TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, 0);
                ((AXIS_OBJECT_DELETE_FUNCT) pDelFunct) (pObject, 0);
                TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);
            }
        }
    }
    else if (0 == strcmp (pName, m_pNode->m_pchNameOrValue))
    {
    /* if this node contain attributes let them be used by the complex
     * type's deserializer
     */
        if (0 != m_pNode->m_pchAttributes[0])
        {
            m_pCurrNode = m_pNode;
            xsd__boolean * isNill = getAttributeAsBoolean("nil", 0);
            if (NULL != isNill)
            {
                if(true_ == *isNill)
                {
                    m_pParser->next ();
                    m_pNode = NULL;
                    delete isNill;
                    return NULL;
                } 
                else
                    delete isNill;
            }
        }
        m_pNode = NULL;    /* node identified and used */

        TRACE_OBJECT_CREATE_FUNCT_ENTRY(pCreFunct,0);
        void *pObject = ((AXIS_OBJECT_CREATE_FUNCT) pCreFunct)(0);
        TRACE_OBJECT_CREATE_FUNCT_EXIT(pCreFunct, pObject);

        if (pObject && pDZFunct)
        {
            TRACE_DESERIALIZE_FUNCT_ENTRY(pDZFunct, pObject, this);
            m_nStatus =    ((AXIS_DESERIALIZE_FUNCT) pDZFunct) (pObject, this);
            TRACE_DESERIALIZE_FUNCT_EXIT(pDZFunct, m_nStatus);

            if (AXIS_SUCCESS == m_nStatus)
            {
                m_pParser->next ();    /* skip end node too */
                m_pNode = NULL;    /* AXISCPP-978 node identified and used */
                return pObject;
            }
            else
            {
                TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, 0);
                ((AXIS_OBJECT_DELETE_FUNCT) pDelFunct) (pObject, 0);
                TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);
            }
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

    m_nStatus = AXIS_FAIL;    /* unexpected SOAP stream */
    return NULL;
}

int
SoapDeSerializer::getElementForAttributes (const AxisChar * pName,
                                           const AxisChar * pNamespace)
{
    if (m_pCurrNode)
    {
        if (0 == strcmp (pName, m_pCurrNode->m_pchNameOrValue))
            return m_nStatus;
    }
    
    if (!m_pNode)
    {
        m_pNode = m_pParser->next ();
        m_pCurrNode = m_pParser->next ();
    }
    else            /* previous node not processed. So consider it */
        m_pCurrNode = m_pNode;

    if (0 == strcmp (pName, m_pNode->m_pchNameOrValue))
        m_pNode = NULL;
    else            /* error : current element is not the expected one */
    {
        m_nStatus = AXIS_FAIL;
        m_pCurrNode = NULL;
    }

    return m_nStatus;
}

void SoapDeSerializer::getAttribute(const AxisChar* pName, const AxisChar * pNamespace, IAnySimpleType * pSimpleType)
{
    if (m_pCurrNode)
    {
        if (START_ELEMENT == m_pCurrNode->m_type)
        {
            for (int i = 0 ; m_pCurrNode->m_pchAttributes[i]; i += 3)
            {
                if ( 0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))
                {
                    pSimpleType->deserialize(m_pCurrNode->m_pchAttributes[i+2]);
                    return;
                }
            }
        }
        else
            m_nStatus = AXIS_FAIL;
    }
    return;
}

/*
 * Before calling any of getAttributeAs... API functions the user should move 
 * current Element to the right Element by calling GetElementForAttributes(..)
 */
xsd__int *
SoapDeSerializer::getAttributeAsInt (const AxisChar * pName,
                                     const AxisChar * pNamespace)
{
    Int simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getInt();
}

xsd__boolean *
SoapDeSerializer::getAttributeAsBoolean (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    Boolean simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getBoolean();
}

xsd__unsignedInt *
SoapDeSerializer::getAttributeAsUnsignedInt (const AxisChar * pName,
                                             const AxisChar * pNamespace)
{
    UnsignedInt simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedInt();
}

xsd__short *
SoapDeSerializer::getAttributeAsShort (const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    Short simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getShort();
}

xsd__unsignedShort *
SoapDeSerializer::getAttributeAsUnsignedShort (const AxisChar * pName,
                                               const AxisChar * pNamespace)
{
    UnsignedShort simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedShort();
}

xsd__byte *
SoapDeSerializer::getAttributeAsByte (const AxisChar * pName,
                                      const AxisChar * pNamespace)
{
    Byte simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getByte();
}

xsd__unsignedByte *
SoapDeSerializer::getAttributeAsUnsignedByte (const AxisChar * pName,
                                              const AxisChar * pNamespace)
{
    UnsignedByte simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedByte();
}

xsd__long *
SoapDeSerializer::getAttributeAsLong (const AxisChar * pName,
                                      const AxisChar * pNamespace)
{
    Long simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getLong();
}

xsd__integer *
SoapDeSerializer::getAttributeAsInteger (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    Integer simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getInteger();
}

xsd__nonNegativeInteger *
SoapDeSerializer::getAttributeAsNonNegativeInteger (const AxisChar * pName,
                                                    const AxisChar * pNamespace)
{
    NonNegativeInteger simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNonNegativeInteger();
}

xsd__positiveInteger *
SoapDeSerializer::getAttributeAsPositiveInteger (const AxisChar * pName,
                                                 const AxisChar * pNamespace)
{
    PositiveInteger simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getPositiveInteger();
}

xsd__nonPositiveInteger *
SoapDeSerializer::getAttributeAsNonPositiveInteger (const AxisChar * pName,
                                                    const AxisChar * pNamespace)
{
    NonPositiveInteger simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNonPositiveInteger();
}

xsd__negativeInteger *
SoapDeSerializer::getAttributeAsNegativeInteger (const AxisChar * pName,
                                                 const AxisChar * pNamespace)
{
    NegativeInteger simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNegativeInteger();
}

xsd__unsignedLong *
SoapDeSerializer::getAttributeAsUnsignedLong (const AxisChar *pName,
                                              const AxisChar * pNamespace)
{
    UnsignedLong simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedLong();
}

xsd__float *
SoapDeSerializer::getAttributeAsFloat (const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    Float simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getFloat();
}

xsd__double *
SoapDeSerializer::getAttributeAsDouble (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    Double simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getDouble();
}

xsd__decimal *
SoapDeSerializer::getAttributeAsDecimal (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    Decimal simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getDecimal();
}

xsd__NOTATION
SoapDeSerializer::getAttributeAsNOTATION (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    NOTATION simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNOTATION();
}

xsd__string
SoapDeSerializer::getAttributeAsString (const AxisChar * pName, 
                                        const AxisChar * pNamespace)
{
    String simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getString();
}

xsd__normalizedString
SoapDeSerializer::getAttributeAsNormalizedString (const AxisChar * pName,
                                                  const AxisChar * pNamespace)
{
    NormalizedString simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNormalizedString();
}

xsd__token
SoapDeSerializer::getAttributeAsToken (const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    Token simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getToken();
}

xsd__language
SoapDeSerializer::getAttributeAsLanguage (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    Language simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getLanguage();
}

xsd__NMTOKEN
SoapDeSerializer::getAttributeAsNMTOKEN (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    NMTOKEN simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNMTOKEN();
}

xsd__NMTOKENS
SoapDeSerializer::getAttributeAsNMTOKENS (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    NMTOKENS simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNMTOKENS();
}

xsd__Name
SoapDeSerializer::getAttributeAsName (const AxisChar * pName,
                                      const AxisChar * pNamespace)
{
    Name simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getName();
}

xsd__NCName
SoapDeSerializer::getAttributeAsNCName (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    NCName simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getNCName();
}


xsd__ID
SoapDeSerializer::getAttributeAsID (const AxisChar * pName,
                                    const AxisChar * pNamespace)
{
    ID simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getID();
}

xsd__IDREF
SoapDeSerializer::getAttributeAsIDREF (const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    IDREF simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getIDREF();
}

xsd__IDREFS
SoapDeSerializer::getAttributeAsIDREFS (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    IDREFS simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getIDREFS();
}

xsd__ENTITY
SoapDeSerializer::getAttributeAsENTITY (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    ENTITY simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getENTITY();
}

xsd__ENTITIES
SoapDeSerializer::getAttributeAsENTITIES (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    ENTITIES simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getENTITIES();
}

xsd__anyURI
SoapDeSerializer::getAttributeAsAnyURI (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    AnyURI simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getAnyURI();
}

xsd__QName
SoapDeSerializer::getAttributeAsQName (const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    XSD_QName simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getQName();
}

xsd__hexBinary *
SoapDeSerializer::getAttributeAsHexBinary (const AxisChar * pName,
                                           const AxisChar * pNamespace)
{
    HexBinary simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getHexBinary();
}

xsd__base64Binary *
SoapDeSerializer::getAttributeAsBase64Binary (const AxisChar * pName,
                                              const AxisChar * pNamespace)
{
    Base64Binary simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getBase64Binary();
}

xsd__dateTime *
SoapDeSerializer::getAttributeAsDateTime (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    DateTime simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getDateTime();
}

xsd__date *
SoapDeSerializer::getAttributeAsDate (const AxisChar * pName,
                                      const AxisChar * pNamespace)
{
    Date simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getDate();
}

xsd__time *
SoapDeSerializer::getAttributeAsTime (const AxisChar * pName,
                                      const AxisChar * pNamespace)
{
    Time simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getTime();
}

xsd__gDay*
SoapDeSerializer::getAttributeAsGDay (const AxisChar * pName,
                                      const AxisChar * pNamespace)
{
    GDay simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getGDay();
}

xsd__gMonth*
SoapDeSerializer::getAttributeAsGMonth (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
 
    GMonth simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getGMonth();
}

xsd__gMonthDay*
SoapDeSerializer::getAttributeAsGMonthDay (const AxisChar * pName,
                                           const AxisChar * pNamespace)
{
    GMonthDay simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getGMonthDay();
}

xsd__gYear*
SoapDeSerializer::getAttributeAsGYear (const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    GYear simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getGYear();
}

xsd__gYearMonth*
SoapDeSerializer::getAttributeAsGYearMonth (const AxisChar * pName,
                                            const AxisChar * pNamespace)
{
    GYearMonth simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getGYearMonth();
}

xsd__duration *
SoapDeSerializer::getAttributeAsDuration (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    Duration simpleType;
    getAttribute(pName, pNamespace, &simpleType);
    return simpleType.getDuration();
}

void SoapDeSerializer::getElement (const AxisChar * pName,
                                   const AxisChar * pNamespace,
                                   IAnySimpleType * pSimpleType,
                                   bool isArrayElement)
{
    if (AXIS_SUCCESS != m_nStatus)
        return;

    if (RPC_ENCODED == m_nStyle)
    {
        bool    bNillFound = false;
        m_pNode = m_pParser->next ();
        
        // wrapper node with type info  Ex: <i xsi:type="xsd:int"> 
        if (!m_pNode)
           return;

        if (0 == strcmp (pName, m_pNode->m_pchNameOrValue))
        {
            for (int i = 0; m_pNode->m_pchAttributes[i] && !bNillFound; i += 3)
            {
                string sLocalName = m_pNode->m_pchAttributes[i];
                string sValue = m_pNode->m_pchAttributes[i + 2];
                
                if (strcmp( "nil", sLocalName.c_str()) == 0 &&
                    strcmp( "true", sValue.c_str()) == 0)
                    bNillFound = true;
            }
        }

        if (bNillFound || isArrayElement || (pSimpleType->getType() == getXSDType (m_pNode)))
        {
            m_pNode = m_pParser->next (true);   /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                const AxisChar* elementValue = m_pNode->m_pchNameOrValue;
                                    
                // FJP Added this code for fault finding.  If detail is
                //     followed by CR/LF or CR/LF then CR/LF then assume that
                //     it is not a simple object.  As added protection against
                //     false findings, the namespace has been set to an invalid
                //     value of a single space character.
                if (strlen (elementValue) < 3 && pNamespace != NULL)
                {
                    if (*pNamespace == ' ')
                    {
                        bool bReturn = false;
    
                        if (strlen (elementValue) == 0)
                            bReturn = true;

                        if (strlen (elementValue) == 1 && (*elementValue == '\n' || *elementValue == '\r'))
                            bReturn = true;
      
                        if (strlen (elementValue) == 2
                            && ((*elementValue == '\n' || *elementValue == '\r')
                            && (*(elementValue + 1) == '\n' || *(elementValue + 1) == '\r')))
                            bReturn = true;
    
                        if (bReturn)
                        {
                            m_pNode = m_pParser->next ();   /* skip end element node too */
                            return;
                        }
                    }
                }
                
                pSimpleType->deserialize(elementValue);
                m_pNode = m_pParser->next ();   /* skip end element node too */
                m_pNode = NULL;
                return;
            }
            else if (m_pNode && (END_ELEMENT == m_pNode->m_type) && bNillFound  ) //xsi:nil="true"
            {
                pSimpleType->deserialize(NULL);
                m_pNode = NULL;
                return;
            } 

            else if (m_pNode && (END_ELEMENT == m_pNode->m_type))    // We have an empty string - Jira AXISCPP-93
            {
                pSimpleType->deserialize("");
                m_pNode = NULL;
                return;
            }
            else
            {
                // simpleType may have xsi:nill="true" */
                //m_pNode = NULL;
                // this is important when deserializing 
                // arrays
                 
                return;
            }
        }
        else
        {
            
            /* it is an error if type is different or not present */
        }
    }
    else
    {
        //DOC_LITERAL    
    
        /* if there is an unprocessed node that may be one left from last 
         * array deserialization
         */
        if (!m_pNode)
            m_pNode = m_pParser->next ();
    
         /* wrapper node without type info  Ex: <i> */
         if (!m_pNode)
            return;
    
         if (0 == strcmp (pName, m_pNode->m_pchNameOrValue))
         {
            bool    bNillFound = false;
            for (int i = 0; m_pNode->m_pchAttributes[i] && !bNillFound; i += 3)
            {
                string sLocalName = m_pNode->m_pchAttributes[i];
                string sValue = m_pNode->m_pchAttributes[i + 2];
    
                if( strcmp( "nil", sLocalName.c_str()) == 0 &&
                    strcmp( "true", sValue.c_str()) == 0)
                    bNillFound = true;
            }
    
            m_pNode = m_pParser->next (true);   /* charactor node */
            if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
            {
                const AxisChar* elementValue = m_pNode->m_pchNameOrValue;
                   // FJP Added this code for fault finding.  If detail is
                //     followed by CR/LF or CR/LF then CR/LF then assume that
                //     it is not a simple object.  As added protection against
                //     false findings, the namespace has been set to an invalid
                //     value of a single space character.
                if (strlen (elementValue) < 3 && pNamespace != NULL)
                {
                    if (*pNamespace == ' ')
                    {
                        bool bReturn = false;
    
                        if (strlen (elementValue) == 0)
                            bReturn = true;
                            
                        if (strlen (elementValue) == 1 && (*elementValue == '\n' || *elementValue == '\r'))
                            bReturn = true;
      
                        if (strlen (elementValue) == 2
                            && ((*elementValue == '\n' || *elementValue == '\r')
                            && (*(elementValue + 1) == '\n' || *(elementValue + 1) == '\r')))
                            bReturn = true;
            
                        if (bReturn)
                        {
                            m_pNode = m_pParser->next ();   /* skip end element node too */
                            m_pNode = NULL;    /* AXISCPP-978 node identified and used */
                            return;
                        }
                    }
                }
                
                pSimpleType->deserialize(elementValue);
                m_pNode = m_pParser->next ();   /* skip end element node too */
                m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays
                 */
                return;
            }
            else if (m_pNode && (END_ELEMENT == m_pNode->m_type) && bNillFound ) //xsi:nil="true"
            {
                pSimpleType->deserialize(NULL);
                m_pNode = NULL;
                return;
            }        
            else if (m_pNode && (END_ELEMENT == m_pNode->m_type) ) // empty tag case <tag/>
            {
                pSimpleType->deserialize("");
                m_pNode = NULL;
                return;
            }
            else
            {
                /* simpleType may have xsi:nill="true" */
    //            m_pNode = NULL;
                /* this is important in doc/lit style when deserializing 
                 * arrays
                 */
                return;
            }
         }
        else
        {
            return;
            /* Not a must : m_nStatus = AXIS_FAIL; unexpected SOAP stream */
        }
    }
    
    m_nStatus = AXIS_FAIL;    /* unexpected SOAP stream */

    return;
}

/*
 * Deserializing Elements as values directly. 
 */
xsd__boolean *
    SoapDeSerializer::getElementAsBoolean (const AxisChar * pName,
                                           const AxisChar * pNamespace)
{
    Boolean simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getBoolean();
}

xsd__int *
    SoapDeSerializer::getElementAsInt (const AxisChar * pName,
                                       const AxisChar * pNamespace)
{
    Int simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getInt();
}


xsd__unsignedInt *
    SoapDeSerializer::getElementAsUnsignedInt (const AxisChar * pName,
                                               const AxisChar * pNamespace)
{
    UnsignedInt simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedInt();
}

xsd__short *
    SoapDeSerializer::getElementAsShort (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    Short simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getShort();
}

xsd__unsignedShort *
    SoapDeSerializer::getElementAsUnsignedShort (const AxisChar * pName,
                                                 const AxisChar * pNamespace)
{
    UnsignedShort simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedShort();
}

xsd__byte *
    SoapDeSerializer::getElementAsByte (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    Byte simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getByte();
}

xsd__unsignedByte *
    SoapDeSerializer::getElementAsUnsignedByte (const AxisChar * pName,
                                                const AxisChar * pNamespace)
{
    UnsignedByte simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedByte();
}

xsd__long *
    SoapDeSerializer::getElementAsLong (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    Long simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getLong();
}

xsd__integer *
    SoapDeSerializer::getElementAsInteger (const AxisChar * pName,
                                           const AxisChar * pNamespace)
{
    Integer simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getInteger();
}

xsd__unsignedLong *
    SoapDeSerializer::getElementAsUnsignedLong (const AxisChar * pName,
                                                const AxisChar * pNamespace)
{
    UnsignedLong simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedLong();
}

xsd__float *
    SoapDeSerializer::getElementAsFloat (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    Float simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getFloat();
}

xsd__double *
    SoapDeSerializer::getElementAsDouble (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    Double simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDouble();
}

xsd__decimal *
    SoapDeSerializer::getElementAsDecimal (const AxisChar * pName,
                                           const AxisChar * pNamespace)
{
    Decimal simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDecimal();
}

xsd__string
    SoapDeSerializer::getElementAsString (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    String simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getString();
}

xsd__anyURI
    SoapDeSerializer::getElementAsAnyURI (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    AnyURI simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getAnyURI();
}

xsd__QName
    SoapDeSerializer::getElementAsQName (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    XSD_QName simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getQName();
}

xsd__hexBinary *
    SoapDeSerializer::getElementAsHexBinary (const AxisChar * pName,
                                             const AxisChar * pNamespace)
{
    HexBinary simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getHexBinary();
}

xsd__base64Binary *
    SoapDeSerializer::getElementAsBase64Binary (const AxisChar * pName,
                                                const AxisChar * pNamespace)
{
    Base64Binary simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getBase64Binary();
}

xsd__dateTime *
    SoapDeSerializer::getElementAsDateTime (const AxisChar * pName,
                                            const AxisChar * pNamespace)
{
    DateTime simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDateTime();
}

xsd__date *
    SoapDeSerializer::getElementAsDate (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    Date simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDate();
}

xsd__time *
    SoapDeSerializer::getElementAsTime (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    Time simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getTime();
}

xsd__duration *
    SoapDeSerializer::getElementAsDuration (const AxisChar * pName,
                                            const AxisChar * pNamespace)
{
    Duration simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDuration();
}

xsd__gYearMonth *
    SoapDeSerializer::getElementAsGYearMonth (const AxisChar * pName,
                                              const AxisChar * pNamespace)
{
    GYearMonth simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGYearMonth();
}

xsd__gYear *
    SoapDeSerializer::getElementAsGYear (const AxisChar * pName,
                                         const AxisChar * pNamespace)
{
    GYear simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGYear();
}

xsd__gMonthDay *
    SoapDeSerializer::getElementAsGMonthDay (const AxisChar * pName,
                                             const AxisChar * pNamespace)
{
    GMonthDay simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGMonthDay();
}

xsd__gDay *
    SoapDeSerializer::getElementAsGDay (const AxisChar * pName,
                                        const AxisChar * pNamespace)
{
    GDay simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGDay();
}

xsd__gMonth *
    SoapDeSerializer::getElementAsGMonth (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    GMonth simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGMonth();
}

xsd__nonPositiveInteger *
    SoapDeSerializer::getElementAsNonPositiveInteger (const AxisChar * pName,
                                                      const AxisChar * pNamespace)
{
    NonPositiveInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNonPositiveInteger();
}

xsd__negativeInteger *
    SoapDeSerializer::getElementAsNegativeInteger (const AxisChar * pName,
                                                   const AxisChar * pNamespace)
{
    NegativeInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNegativeInteger();
}

xsd__nonNegativeInteger *
    SoapDeSerializer::getElementAsNonNegativeInteger (const AxisChar * pName,
                                                      const AxisChar * pNamespace)
{
    NonNegativeInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNonNegativeInteger();
}

xsd__positiveInteger *
    SoapDeSerializer::getElementAsPositiveInteger (const AxisChar * pName,
                                            const AxisChar * pNamespace)
{
    PositiveInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getPositiveInteger();
}

xsd__normalizedString
    SoapDeSerializer::getElementAsNormalizedString (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    NormalizedString simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNormalizedString();
}

xsd__token
    SoapDeSerializer::getElementAsToken (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    Token simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getToken();
}

xsd__language
    SoapDeSerializer::getElementAsLanguage (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    Language simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getLanguage();
}

xsd__Name
    SoapDeSerializer::getElementAsName (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    Name simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getName();
}

xsd__NCName
    SoapDeSerializer::getElementAsNCName (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    NCName simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNCName();
}

xsd__ID
    SoapDeSerializer::getElementAsID (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    ID simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getID();
}

xsd__IDREF
    SoapDeSerializer::getElementAsIDREF (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    IDREF simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getIDREF();
}

xsd__IDREFS
    SoapDeSerializer::getElementAsIDREFS (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    IDREFS simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getIDREFS();
}

xsd__ENTITY
    SoapDeSerializer::getElementAsENTITY (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    ENTITY simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getENTITY();
}

xsd__ENTITIES
    SoapDeSerializer::getElementAsENTITIES (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    ENTITIES simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getENTITIES();
}

xsd__NMTOKEN
    SoapDeSerializer::getElementAsNMTOKEN (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    NMTOKEN simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNMTOKEN();
}

xsd__NMTOKENS
    SoapDeSerializer::getElementAsNMTOKENS (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    NMTOKENS simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNMTOKENS();
}

xsd__NOTATION
    SoapDeSerializer::getElementAsNOTATION (const AxisChar * pName,
                                          const AxisChar * pNamespace)
{
    NOTATION simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNOTATION();
}

xsd__base64Binary
    SoapDeSerializer::decodeFromBase64Binary (const AxisChar * pValue)
{
    xsd__base64Binary value;
    xsd__int size = apr_base64_decode_len (pValue);
    xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
    size = apr_base64_decode_binary (pTemp, pValue);
    pTemp[size] = 0; // Null terminate so it could used as a string
    value.set(pTemp, size);
    delete [] pTemp;
    return value;
}

xsd__hexBinary SoapDeSerializer::decodeFromHexBinary (const AxisChar * pValue)
{
    xsd__hexBinary value;
    xsd__int size = strlen (pValue) / 2;
    xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
    Hex_Decode (pTemp, pValue);
    pTemp[size] = 0; // Null terminate so it could be used as a string
    value.set(pTemp, size);
    delete [] pTemp;
    return value;
}

xsd__string
SoapDeSerializer::getFaultAsXMLString()
{
    if (AXIS_SUCCESS != m_nStatus || RPC_ENCODED == m_nStyle)
        return NULL;
    AnyType *any = getAnyObject();
    int len = 1, i; // Add 1 for the null terminator
    for (i=0; i<any->_size; i++)
        if (any->_array[i])
            len += strlen(any->_array[i]);

    xsd__string ret = new char[len];
    memset(ret,0,len);
    for (i=0; i<any->_size; i++) if (any->_array[i]) 
    {
        strcat(ret,any->_array[i]);
        delete [] any->_array[i];
    }
    delete any->_array;
    delete any;
    return ret;
}

/*
 * This method checks the attribute list of pElement node for the xsi:type 
 * attribute. If it is found then finds what the type is. Otherwise returns 
 * XSD_UNKNOWN.
 */
XSDTYPE SoapDeSerializer::getXSDType (const AnyElement * pElement)
{
    /* first check whether this is a start element node */
    if (START_ELEMENT != pElement->m_type)
        return XSD_UNKNOWN;

    for (int i = 0; pElement->m_pchAttributes[i]; i += 3)
    {
        if (URI_XSI == URIMapping::getURI (pElement->m_pchAttributes[i + 1]))
        {
            ::QName qn;
            XSDTYPE type = XSD_UNKNOWN;
            qn.splitQNameString (pElement->m_pchAttributes[i + 2], ':');
            const char * pNS = m_pParser->getNS4Prefix (qn.uri);
            if (pNS)
            {
                if (URI_XSD == URIMapping::getURI (pNS) || URI_ENC == URIMapping::getURI (pNS))
                    type = TypeMapping::map (qn.localname);
            }
            qn.mergeQNameString (':');
            return type;
        }
    }

    return XSD_UNKNOWN;
}

/*
 * Used by the Axis Engine to get any left header blocks in the deserializer 
 * even after the completion of message path. Then those headers will be added
 * to the serializer because they are probably headers targetted to nex soap 
 * processors.
 */
HeaderBlock *
SoapDeSerializer::getHeaderBlock ()
{
    if (!m_pHeader)
    return NULL;

    return (HeaderBlock *) m_pHeader->getHeaderBlock (true);
}

/*
 * Used probably by a handler to add a header block to the Deserializer.
 * Probably to be used by a subsequent handler in the request message path
 */
int AXISCALL
SoapDeSerializer::addHeaderBlock (IHeaderBlock * pBlk)
{
    if (!m_pHeader)
        m_pHeader = new SoapHeader ();
    m_pHeader->addHeaderBlock ((HeaderBlock *) pBlk);
    return AXIS_SUCCESS;
}

xsd__hexBinary SoapDeSerializer::getBodyAsHexBinary ()
{
    /* TODO */
    xsd__hexBinary hb;
    return hb;
}

xsd__base64Binary SoapDeSerializer::getBodyAsBase64Binary ()
{
    /* TODO */

    pBodyContent = new AxisChar[1000];
    pBodyContent[0] = '\0';

    m_pNode = m_pParser->next ();

    if ((START_ELEMENT == m_pNode->m_type) &&
    (0 == strcmp (m_pNode->m_pchNameOrValue,
                  SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])))
    {
        /* This is done to skip the BODY element declaration */
        m_pNode = m_pParser->next ();
    }

    while (!((END_ELEMENT == m_pNode->m_type) &&
           (0 == strcmp (m_pNode->m_pchNameOrValue,
                         SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY]))))
        strcat (pBodyContent, (AnyElemntUtils::toString (m_pNode)).c_str ());

    return decodeFromBase64Binary (pBodyContent);
}

AxisChar *
SoapDeSerializer::getBodyAsChar ()
{
    pBodyContent = new AxisChar[1000];
    pBodyContent[0] = '\0';

    m_pNode = m_pParser->next ();

    if ((START_ELEMENT == m_pNode->m_type) &&
        (0 == strcmp (m_pNode->m_pchNameOrValue,
                      SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])))
    {
        /* This is done to skip the BODY element declaration */
        m_pNode = m_pParser->next ();
    }

    while (!((END_ELEMENT == m_pNode->m_type) &&
           (0 == strcmp (m_pNode->m_pchNameOrValue,
                         SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY]))))
        strcat (pBodyContent, (AnyElemntUtils::toString (m_pNode)).c_str ());

    return pBodyContent;
}

int
SoapDeSerializer::setNewSoapBody (AxisChar * pNewSoapBody)
{
    DeSerializerMemBufInputStream stream (pNewSoapBody);
    return m_pParser->setInputStream (&stream);
}

bool SoapDeSerializer::isAnyMustUnderstandHeadersLeft ()
{
    /* TODO */
    return false;
}

int
SoapDeSerializer::flushInputStream ()
{
    int nChars = 100;
    char pBuffer[100];
    
    if (!m_pInputStream)
        return AXIS_FAIL;
    
    while (TRANSPORT_IN_PROGRESS == m_pInputStream->getBytes (pBuffer, &nChars));
    
    return AXIS_SUCCESS;
}

AnyType *
SoapDeSerializer::getAnyObject ()
{
    AnyType *pAny = new AnyType ();
    pAny->_array = 0;
    pAny->_size = 0;

    int tagCount = 0;
    int lstSize = 0;
    bool bContinue = false;

    AxisString xmlStr = "";
    AxisString nsDecls = "";

    list < AxisString > lstXML;

    if (!m_pNode)
        m_pNode = m_pParser->anyNext();

    while ((END_ELEMENT != m_pNode->m_type) || (tagCount >= 0) || bContinue)
    {
        // Continue if processing start prefix,
        // as we haven't yet found the true start of the tag
        if (START_PREFIX == m_pNode->m_type)
            bContinue = true;
        else
            bContinue = false;
        
        // Increment counter if entering new tag, Decrement counter if exiting tag
        if (START_ELEMENT == m_pNode->m_type && START_END_ELEMENT != m_pNode->m_type2)
            tagCount++;
        else if (END_ELEMENT == m_pNode->m_type)
            tagCount--;
        
        if (START_PREFIX == m_pNode->m_type)
        {
            nsDecls += " xmlns";
            /* why dont parser return null if there is no
             * prefix. Expat return null but not xerces.
             * TODO : will have to remove following strcmp s onece Xerces is 
             * corrected
             */
            if (m_pNode->m_pchNameOrValue
                && (strcmp (m_pNode->m_pchNameOrValue, "") != 0))
            {
                nsDecls += ":";
                nsDecls += m_pNode->m_pchNameOrValue;
            }
            nsDecls += "=\"";
            nsDecls += m_pNode->m_pchNamespace;
            nsDecls += "\"";
        }
        else if (CHARACTER_ELEMENT != m_pNode->m_type)
        {
            serializeTag (xmlStr, m_pNode, nsDecls);
            nsDecls = "";
        }
        else
            xmlStr += m_pNode->m_pchNameOrValue;
    
        if ( !bContinue && tagCount == 0 && (!xmlStr.empty ()))    /* copying the First level element into the list */
        {
            lstXML.push_back (xmlStr);
            xmlStr = "";
            m_pNode = NULL;
            break;
        }
    
        m_pNode = m_pParser->anyNext ();
    
        if (!m_pNode) // Samisa: there is something wrong in the XSD Any XML strean
        {          
            // Store whatever we have by now and break
            if (!xmlStr.empty ())
            {
                lstXML.push_back (xmlStr);
                xmlStr = "";
            }
            break;
        }
    }

    lstSize = lstXML.size ();
    pAny->_array = new char *[lstSize];
    pAny->_size = 0;

    list < AxisString >::iterator i;    /* Iterator for traversing the list */

    for (i = lstXML.begin (); i != lstXML.end (); i++)
    {
        const char *s = (*i).c_str ();
        pAny->_array[pAny->_size] = new char[strlen (s) + 1];
        strcpy (pAny->_array[pAny->_size], s);
        pAny->_size++;
    }

    return pAny;
}


void
SoapDeSerializer::serializeTag (AxisString & xmlStr, 
                                const AnyElement * node,
                                AxisString & nsDecls)
{
    /*
       Note that if this is an end tag and since m_pchNameOrValue doesn't give
       the "/" sign. So we have to add that sign as well in to the end tag
     */
    const XML_Ch *pchPrefix = 0;

    if (START_ELEMENT == node->m_type)
    {
        xmlStr += "<";
        /* why dont parser set null if there is no
         * namespace. Expat set null but not xerces.
         * TODO : will have to remove following strcmp's once Xerces is 
         * corrected
         */
        if (node->m_pchNamespace && (strcmp (node->m_pchNamespace, "") != 0))
        {
            pchPrefix = m_pParser->getPrefix4NS (node->m_pchNamespace);

            if (pchPrefix && (strcmp (pchPrefix, "") != 0))
            {
                xmlStr += pchPrefix;
                xmlStr += ":";
            }
        }
    
        xmlStr += node->m_pchNameOrValue;

        if (!nsDecls.empty ())
            xmlStr += nsDecls.c_str ();

        if (node->m_pchAttributes)
        {
            int j;
    
            /* structure of the m_pchAttributes[] array is,
             * sequence of (local_name, namespace_uri, value)
             */
    
            for (j = 0; j < 300; j += 3)    /* MAX_NO_OF_ATTRIBUTES = 100 */
            {
                if (node->m_pchAttributes[j])
                {
                    if (node->m_pchAttributes[j + 1])
                        pchPrefix = m_pParser->getPrefix4NS (node->m_pchAttributes[j + 1]);
                    else
                        pchPrefix = NULL;
                        
                    /* why dont parser return null if there is no
                     * prefix. Expat does but not xerces.
                     * TODO : will have to remove following strcmp s onece Xerces is 
                     * corrected
                     */
                    if (pchPrefix && (strcmp (pchPrefix, "") != 0))
                    {
                        xmlStr += " ";
                        xmlStr += pchPrefix;
                        xmlStr += ":";
                    }
                    else
                    {
                        // if there is no prefix then we need to add a space
                        xmlStr +=" ";
                    }
                    
                    xmlStr += node->m_pchAttributes[j];
                    xmlStr += "=\"";
                    xmlStr += node->m_pchAttributes[j + 2];
                    xmlStr += "\"";
                }
                else
                    break;
            }
        }

        if (START_END_ELEMENT == node->m_type2)
            xmlStr += "/>";
        else
            xmlStr += ">";
    }
    else if (END_ELEMENT == node->m_type)
    {
        xmlStr += "</";
        /* if (node->m_pchNamespace) why dont parser set null if there is no
         * namespace. Expat set null but not xerces.
         * TODO : will have to remove following strcmp s onece Xerces is 
         * corrected
         */
        if (node->m_pchNamespace && (strcmp (node->m_pchNamespace, "") != 0))
        {
            pchPrefix = m_pParser->getPrefix4NS (node->m_pchNamespace);
            /* why dont parser return null if there is no
             * prefix. Expat does but not xerces.
             * TODO : will have to remove following strcmp s onece Xerces is 
             * corrected
             */
            if (pchPrefix && (strcmp (pchPrefix, "") != 0))
            {
                xmlStr += pchPrefix;
                xmlStr += ":";
            }
            else
            {
                // This code is required because the namespace for the closing tag may have
                // been deleted before it can be checked (m_pParser->getPrefix4NS).  If it has
                // been deleted, then the code needs to look at the opening tag and use that
                // namespace for the closing tag.
                // This is because:-
                // [2511] m_pNode = m_pParser->anyNext() calls
                //   XercesHandler::endPrefixMapping() and this deletes the namespace before it
                //                                     can be looked up by m_pParser->getPrefix4NS!
                // Check if NameOrValue is the same as the tag name at the beginning of the XML
                // string.  If it is, check if it has a namespace.  If it has, then add the
                // same namespace to the XML string.  This test needs to be done because the
                // namespace is being deleted before it can be checked.
                //
                // There has got to be a better way of doing this, but it was not obvious at
                // the time!
                const char *    pszXML = xmlStr.c_str();
                char *            pNSEnd = (char *)strchr( pszXML, ':');
                char *            pTagEnd = (char *)strchr( pszXML, '>');

                if( pNSEnd && (pNSEnd < pTagEnd))
                {
                    int                iNSStart = 1;
                    int                iNSEnd = (int) (strchr( pszXML, ':') - pszXML) - iNSStart;
                    string            sNamespace = xmlStr.substr( iNSStart, iNSEnd);
                    int                iTagEnd = 0;
                    char *            pSpace = (char *)strchr( pszXML, ' ');
                    char *            pBrace = (char *)strchr( pszXML, '>');

                    if( pSpace == NULL)
                        iTagEnd = pSpace - pszXML;
                    else if( pBrace == NULL)
                        iTagEnd = pBrace - pszXML;
                    else if( pBrace < pSpace)
                        iTagEnd = pBrace - pszXML;
                    else if( pSpace <= pBrace)
                        iTagEnd = pSpace - pszXML;

                    string    sTag = xmlStr.substr( iNSEnd + iNSStart + 1, iTagEnd - (iNSEnd + iNSStart + 1));

                    if( !sTag.compare( node->m_pchNameOrValue))
                    {
                        xmlStr += sNamespace;
                        xmlStr += ":";
                    }
                }
            }
        }

        xmlStr += node->m_pchNameOrValue;
        if (START_END_ELEMENT == node->m_type2)
            xmlStr += "/>";
        else
            xmlStr += ">";
    }
}

void
SoapDeSerializer::getChardataAs (void **pValue, 
                                 XSDTYPE type)
{
    if (!m_pNode)
       m_pNode = m_pParser->next (true);    /* charactor node */
       
    if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
    {
        IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(type);
        pSimpleType->deserialize(m_pNode->m_pchNameOrValue);
        *pValue = pSimpleType->getValue();
        delete pSimpleType;
    }
}

LONGLONG
SoapDeSerializer::strtoll (const char *pValue)
{
    LONGLONG llRetVal = 0;
    LONGLONG llPowerOf10 = 1;
    int iLength = strlen (pValue);
    int iCountDownTo = 0;
    bool bMinus = false;

    if (*pValue == '-')
    {
        bMinus = true;
        iCountDownTo = 1;
    }

    if (iLength > 0)
        iLength--;

    for (int iCount = iLength; iCount >= iCountDownTo; iCount--)
    {
        llRetVal += (LONGLONG) (pValue[iCount] - '0') * llPowerOf10;
        llPowerOf10 *= (LONGLONG) 10;
    }

    if (bMinus)
        llRetVal = -llRetVal;

    return llRetVal;
}

/* This function is never called. */
AXIS_TRANSPORT_STATUS
SoapDeSerializer::DeSerializerMemBufInputStream::
sendBytes (const char *pcSendBuffer, const void *pBufferid)
{
    return TRANSPORT_FINISHED;
}

AXIS_TRANSPORT_STATUS
SoapDeSerializer::DeSerializerMemBufInputStream::
getBytes (char *pcBuffer,
          int *piRetSize)
{
    if (!m_pcDeSeriaMemBuffer)
        return TRANSPORT_FAILED;
    int nBufLen = strlen (m_pcDeSeriaMemBuffer);
    if (0 == nBufLen)
        return TRANSPORT_FINISHED;
    nBufLen = ((*piRetSize - 1) < nBufLen) ? (*piRetSize - 1) : nBufLen;
    strncpy (pcBuffer, m_pcDeSeriaMemBuffer, nBufLen);
    pcBuffer[nBufLen] = 0;
    m_pcDeSeriaMemBuffer += nBufLen;
    return TRANSPORT_IN_PROGRESS;
}

ISoapAttachment* SoapDeSerializer::getAttachment(const char* pcAttachmentid)    
{            
    return m_pInputStream->getAttachment(pcAttachmentid);         
}

ISoapAttachment** SoapDeSerializer::getAllAttachments(int *pAttchArraySize)
{
    return m_pInputStream->getAllAttachments(pAttchArraySize);
}

const char* SoapDeSerializer::getMethodNameToInvoke()
{
    return m_strMethodNameToInvoke.c_str();
}

void SoapDeSerializer::setMethodNameToInvoke(const char* methodName)
{
    m_strMethodNameToInvoke = methodName;
}

AXIS_CPP_NAMESPACE_END
