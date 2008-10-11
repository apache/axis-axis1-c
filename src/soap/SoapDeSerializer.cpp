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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <list>
#include <iostream>

#include <axis/Axis.hpp>
#include <axis/GDefine.hpp>

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
#include "apr_base64.h"
#include "HexCoder.h"
#include "../engine/XMLParserFactory.h"
#include "../xml/XMLParser.h"
#include "../xml/QName.h"
#include "../xml/AxisParseException.h"
#include "AxisSoapException.h"
#include "../common/AxisGenException.h"

#include "../common/AxisTrace.h"



AxisChar * pBodyContent;

AXIS_CPP_NAMESPACE_START

SoapDeSerializer::
SoapDeSerializer ()
{
    m_pParser = XMLParserFactory::getParserObject ();
    m_pEnv = NULL;
    m_pHeader = NULL;
    m_pCurrNode = NULL;
    m_pNode = NULL;
    m_pInputStream = NULL;
    m_nStatus = AXIS_SUCCESS;
    m_nSoapVersion = VERSION_LAST;
}

SoapDeSerializer::
~SoapDeSerializer ()
{
    delete m_pEnv;
    delete m_pHeader;
    if (m_pParser)
        XMLParserFactory::destroyParserObject (m_pParser);
    delete pBodyContent;
}

int SoapDeSerializer::
setInputStream (SOAPTransport * pInputStream)
{
    if (NULL == pInputStream)
        return AXIS_FAIL;

    m_pInputStream = pInputStream;

    return m_pParser->setInputStream (pInputStream);
}

/*
 * Routine to help obtain parser information and throw it as an exception
 */
void SoapDeSerializer::
throwParserException()
{
    AxisParseException e;
    
    if (m_pParser->getStatus() != AXIS_SUCCESS)
        e.setMessage(m_pParser->getErrorCode(), "AxisParseException:", m_pParser->getErrorString());
    else
        e.setMessage(SERVER_PARSE_PARSER_FAILED, "AxisParseException:");
        
    throw e;
}

/*
 * Routine that handles getting next node, in the future when we sync
 * up rpc and doc processing and eliminate peek, we should be able to 
 * get rid of the first parameter!
 */
int SoapDeSerializer::
getNextNode(bool ifNotSet, bool characterMode, bool throwExcOnError)
{
    // If node pointer is set and user requested that we 
    // only get next element if not set, return.
    if (ifNotSet && m_pNode)
        return AXIS_SUCCESS;
    
    // Ensure m_pNode is NULL before calling parser in case of exceptions.
    m_pNode = NULL;
    
    // Just a sanity check
    if (!m_pParser)
        return AXIS_FAIL;       
    
    try
    { 
        m_pNode = m_pParser->next(characterMode);
    }
    catch (AxisException &e)
    {
        // Exception processing will be handled in subsequent code
    }
    
    // If no node obtained, either there is no more data to read (at this time
    // we treat this as an error but we do not throw an exception for this) or the 
    // parser had an exception, in which case we throw an exception if requested.
    if (!m_pNode)
    {
        m_nStatus = AXIS_FAIL;
        if (throwExcOnError && (AXIS_FAIL == m_pParser->getStatus()))
            throwParserException();
    }
    
    return m_pNode ? AXIS_SUCCESS : AXIS_FAIL;
}


/*
 * Routine that ensures we are actually skipping the expected node...usually an end node.
 */
int SoapDeSerializer::
skipNode(bool verifyIfEndNode, bool throwExcOnError)
{
    int rc = getNextNode(false, false, throwExcOnError);
    
    if (rc == AXIS_SUCCESS)
    {
        if (verifyIfEndNode)
        {
            // TODO add code to determine if in fact 
            // TODO the node we are about to skip is an end node. If not, we need 
            // TODO to throw an exception since there could be extra elements that 
            // TODO is due to server/client differences in wsdl being used, etc.  
            // TODO in addition, a check is another safeguard.            
        }
        
        m_pNode = NULL;
    }
    
    return rc;
}

SoapEnvelope *SoapDeSerializer::
getEnvelope ()
{
    if (AXIS_FAIL == getNextNode(true))     
        return NULL;
            
    // Better be a start-element.
    if (START_ELEMENT != m_pNode->m_type)
    {
        m_nStatus = AXIS_FAIL;
        throw AxisSoapException (CLIENT_SOAP_SOAP_CONTENT_ERROR, "Start-element for SOAP Envelope not found.");
    }
            
    // We are expecting a SOAP envelope.  
    if (0 != strcmp(m_pNode->m_pchNameOrValue,SoapKeywordMapping::map(SOAP_VER_1_2).pchWords[SKW_ENVELOPE]))
    {
        m_nStatus = AXIS_FAIL;
        throw AxisSoapException (CLIENT_SOAP_SOAP_CONTENT_ERROR, "Element is not a SOAP Envelope.");
    }
    
    // No try/catch block needed here since we already have the node
    SoapEnvelope *m_pEnvl = new SoapEnvelope ();
    
    // set all attributes of SoapEnvelope 
    std::list<Attribute*> attributeList0;
    Attribute * pAttr = new Attribute ( attributeList0);

    pAttr->setValue (m_pNode->m_pchNamespace);
    m_pEnvl->addNamespaceDecl (pAttr);

    if (0 == strcmp (m_pNode->m_pchNamespace, SoapKeywordMapping::map (SOAP_VER_1_1).pchNamespaceUri))
        m_nSoapVersion = SOAP_VER_1_1;
    else if (0 == strcmp (m_pNode->m_pchNamespace, SoapKeywordMapping::map (SOAP_VER_1_2).pchNamespaceUri))
        m_nSoapVersion = SOAP_VER_1_2;
    else
        m_nSoapVersion = VERSION_LAST;

    // Set Attributes 
    for (int i = 0; m_pNode->m_pchAttributes[i]; i += 3)
    {
        std::list<Attribute*> attributeList1;
        pAttr = new Attribute (attributeList1);
        pAttr->setLocalName (m_pNode->m_pchAttributes[i]);
        pAttr->setURI (m_pNode->m_pchAttributes[i + 1]);
        pAttr->setValue (m_pNode->m_pchAttributes[i + 2]);
        m_pEnvl->addAttribute (pAttr);
    }

    // indicate node consumed and return envelope
    m_pNode = NULL;  
    return m_pEnvl;
}

/*
 * Header block parsing should be done differently for different SOAP versions.
 * Since the Header blocks may be requested in a different order than it is in 
 * the SOAP stream there must be a mechanism to manage the situation. Possibly 
 * to re-parse the stream part which has unused header blocks.
 */
IHeaderBlock *SoapDeSerializer::
getHeaderBlock (const AxisChar * pName, const AxisChar * pNamespace)
{
    // if no <Header> element there can be no Header blocks 
    if (!m_pHeader)
        return NULL; 

    return m_pHeader->getHeaderBlock (pName, pNamespace, true);
}

int SoapDeSerializer::
getHeader ()
{
    if (m_pHeader)
        return m_nStatus;

    if (AXIS_FAIL == getNextNode())       
        return m_nStatus;

    if ((START_ELEMENT == m_pNode->m_type) 
            && (m_nSoapVersion != VERSION_LAST)
            && (0 == strcmp (m_pNode->m_pchNameOrValue,
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_HEADER])))
    {
        delete m_pHeader;
        m_pHeader = new SoapHeader ();
        
        // Set any attributes/namspaces to the SoapHeader object
        while (true)
        {
            if (AXIS_FAIL == getNextNode(false, true, false))       
                return m_nStatus;
    
            if ((END_ELEMENT == m_pNode->m_type) &&
                (0 == strcmp (m_pNode->m_pchNameOrValue,
                              SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_HEADER])))
            {
                m_pNode = NULL; // indicate node consumed
                return m_nStatus;
            }
    
            // following is done to ignore anything (eg : the toplevel whitespaces) but a start element.
            if (START_ELEMENT != m_pNode->m_type)
            {
                m_pNode = NULL; // indicate node consumed
                continue;
            }
    
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
    
            BasicNode *pNodeList[10];
            pNodeList[0] = NULL;
            int iListPos = 0;
            int iLevel = 0;
    
            while (true)
            {
                if (AXIS_FAIL == getNextNode(false, true, false))
                    break;
        
                if (END_ELEMENT == m_pNode->m_type)
                {
                    if (iLevel == 0)
                    {
                        //do nothing
                        m_pHeader->addHeaderBlock (pHeaderBlock);
                        break;
                    }
                    else if (iLevel == 1)
                    {
                        if ((pNodeList[0]) != NULL)
                        {
                            pHeaderBlock->addChild (pNodeList[0]);
                            iListPos--;
                            iLevel--;
                        }
                    }
                    else
                    {
                        (pNodeList[iListPos - 2])->addChild (pNodeList[iListPos - 1]);
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
                    BasicNode *pBasicNode = new CharacterElement (m_pNode->m_pchNameOrValue);
        
                    //addToImmidiateParent
                    if (iLevel == 0)
                        pHeaderBlock->addChild (pBasicNode);
                    else
                        (pNodeList[iListPos - 1])->addChild (pBasicNode);
                }
            } // end while
        }
    }

    return m_nStatus;
}

// This method adds to allow "all" & "choice" constructs to peek head next element.
const char*SoapDeSerializer::
peekNextElementName ()
{ 
    if (m_pParser)
    {
        const char* name = m_pParser->peek ();
        return name;
    }
            
    return NULL;
}

int SoapDeSerializer::
getBody ()
{
    if (AXIS_FAIL == getNextNode(true))
        return m_nStatus;

    // previous header searching may have left a node unidentified
    if ((START_ELEMENT == m_pNode->m_type) 
            && (m_nSoapVersion != VERSION_LAST)
            && (0 == strcmp (m_pNode->m_pchNameOrValue,
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])))
    {
        // indicate node consumed
        m_pNode = NULL; 

        // peek for the method name
        m_strMethodNameToInvoke = m_pParser->peek();
        
        return AXIS_SUCCESS;
    }

    m_nStatus = AXIS_FAIL;
    return AXIS_FAIL;
}

int SoapDeSerializer::
checkMessageBody (const AxisChar * pName, const AxisChar * pNamespace)
{
	return validateMessageBody(pName, pNamespace, true);
}

int SoapDeSerializer::
validateMessageBody(const AxisChar * pName, const AxisChar * pNamespace, bool consumeIt)
{
    // Will throw exception if failure in parser
    if (AXIS_FAIL == getNextNode(true))
        return AXIS_FAIL;
        
    if (START_ELEMENT != m_pNode->m_type)
        throw AxisSoapException (CLIENT_SOAP_SOAP_CONTENT_ERROR, "Start-element was not found.");

    // If a fault has occurred or the node name is unexpected, throw exception
    // deserialize it as doc literal by setting style. 
    if (0 != strcmp (m_pNode->m_pchNameOrValue, pName))
    {
        setStyle (DOC_LITERAL);
        AXISTRACE1 ("AXISC_NODE_VALUE_MISMATCH_EXCEPTION", CRITICAL);
        throw AxisGenException (AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
    }

    // indicate node consumed
    if (consumeIt)
    	m_pNode = NULL; 
    
    return AXIS_SUCCESS;
}

// Used for one-way message processing, to initiate a fault.
void SoapDeSerializer::
initiateFault (const AxisChar * pNamespace)
{
    // Will throw exception if failure in parser
    if (AXIS_FAIL == getNextNode(true))
        return;
        
    if (START_ELEMENT != m_pNode->m_type)
        throw AxisSoapException (CLIENT_SOAP_SOAP_CONTENT_ERROR, "Start-element was not found.");

    setStyle (DOC_LITERAL);
    throw AxisGenException (AXISC_NODE_VALUE_MISMATCH_EXCEPTION);    
}

void *SoapDeSerializer::
checkForFault (const AxisChar * pName, const AxisChar * pNamespace)
{
    if (0 != strcmp ("Fault", pName))
        throw AxisGenException (AXISC_NODE_VALUE_MISMATCH_EXCEPTION, 
                                "Fault element name not valid.");
        
    if (0 != strcmp (m_pNode->m_pchNameOrValue, pName))
    {
        m_nStatus = AXIS_SUCCESS;
        m_pNode = NULL;
        throw AxisGenException (AXISC_NODE_VALUE_MISMATCH_EXCEPTION);
    }

    char *pcDetail = NULL;
    char *pcFaultCode = NULL;
    char *pcFaultstring = NULL;
    char *pcFaultactor = NULL;
    
    SoapFault *pFault = new SoapFault ();
    pFault->setDeSerializer (this);

    // indicate node consumed
    m_nStatus = AXIS_SUCCESS;
    m_pNode = NULL;  

    // We deserialize fault code in doc literal. 
    m_nStyle = getStyle ();
    setStyle (DOC_LITERAL);
    
    // getElement or peek will throw exceptions, so need to clean up memory allocations
    try
    {
        // Get fault code
        pcFaultCode = getElementAsString ("faultcode", 0);
        pFault->setFaultcode (pcFaultCode == NULL ? "" : pcFaultCode);
        delete [] pcFaultCode;
        
        // Get fault string
        pcFaultstring = getElementAsString ("faultstring", 0);
        pFault->setFaultstring (pcFaultstring == NULL ? "" : pcFaultstring);
        delete [] pcFaultstring;
     
        // faultactor is optional
        const char* elementName = peekNextElementName();
        if (strcmp(elementName, "faultactor") == 0)
        {
            pcFaultactor = getElementAsString ("faultactor", 0);
            pFault->setFaultactor (pcFaultactor == NULL ? "" : pcFaultactor);
            delete [] pcFaultactor;
        }      
         
        // detail is optional.   
        // Changed the namespace from null to a single space (an impossible
        // value) to help method know that it is parsing a fault message.
        elementName = peekNextElementName();
        if (strcmp(elementName, "detail") == 0)
        {
            pcDetail = getElementAsString ("detail", " ");
            
            if (pcDetail)
            {
                pFault->setFaultDetail (pcDetail);
                delete [] pcDetail;          
            }
            else
            {
                const char *pcCmplxFaultName = "";
                
                if ((AXIS_SUCCESS == getNextNode(true)) && m_pNode->m_pchNameOrValue)
                    pcCmplxFaultName = m_pNode->m_pchNameOrValue;
                    
                pFault->setCmplxFaultObjectName (pcCmplxFaultName);
            }
        }
    }
    catch ( ... )
    {
        setStyle (m_nStyle);
        
        delete [] pcFaultCode;
        delete [] pcFaultstring;
        delete [] pcFaultactor;
        delete [] pcDetail;
        delete pFault;
        
        throw;
    }

    setStyle (m_nStyle);
    return pFault;
}

int SoapDeSerializer::
init ()
{
    m_pNode = NULL;
    m_pCurrNode = NULL;

    delete m_pEnv;
    m_pEnv = NULL;

    delete m_pHeader;
    m_pHeader = NULL;

    m_nSoapVersion = VERSION_LAST;
    m_nStatus = AXIS_SUCCESS;

    return m_nStatus;
}

int SoapDeSerializer::
getVersion ()
{
    if (VERSION_LAST == m_nSoapVersion)
    {
        delete m_pEnv;
        m_pEnv = NULL;
        m_pEnv = getEnvelope ();
    }

    return m_nSoapVersion;
}

/*
 * Get Size of the single dimension array from arrayType attribute
 * Ex : enc:arrayType="xs:string[6]"
 * RPC/Encoded only processing.
 */
int SoapDeSerializer::
getArraySize ()
{
    int nSize = 0;
    
    // If not RPC or failure in getNextNode, return zero.
    if (RPC_ENCODED != m_nStyle || (AXIS_FAIL == getNextNode()))
      return nSize;
    
    // first check whether this is a start element node
    if (START_ELEMENT == m_pNode->m_type)
    {
        // If start-end element, then empty array
        if (START_END_ELEMENT == m_pNode->m_type2)
        {
            skipNode();
            return nSize;
        }
    }
    else if (END_ELEMENT == m_pNode->m_type)
        return nSize;

    for (int i = 0; m_pNode->m_pchAttributes[i]; i += 3)
    {
        if (URI_ENC == URIMapping::getURI (m_pNode->m_pchAttributes[i + 1])
            && (0 == strcmp (m_pNode->m_pchAttributes[i],
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_ARRAYTYPE])))
        {
            QName qn;
    
            qn.splitQNameString (m_pNode->m_pchAttributes[i + 2], '[');
            nSize = strtol (qn.localname, &m_pEndptr, 10);
            qn.mergeQNameString ('[');
    
            if (nSize == 0)
                skipNode();
                
            return nSize;
        }
    }

    return nSize;
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

Axis_Array *SoapDeSerializer::
getCmplxArray (Axis_Array* pArray, 
               void *pDZFunct, void *pCreFunct, void *pDelFunct, 
               const AxisChar * pName, const AxisChar * pNamespace)
{
    // if anything has gone wrong earlier just do nothing 
    if (AXIS_SUCCESS != m_nStatus)
        return pArray;

    // Loop through the array adding elements.
    int arraySize = getArraySize ();    
    int count = 0;
    const char* elementName;
    
    while(RPC_ENCODED != m_nStyle || count < arraySize)
    {
        // For RPC-encoded arrays, the element name in array cannot be derived - 
        // within an array value element names are not significant - so  
        // we read until end-of-element is encountered (i.e. null string 
        // is returned from peek()). 
        elementName = m_pParser->peek();
        if ((RPC_ENCODED == m_nStyle && 0x00 != *elementName) || strcmp(elementName, pName) == 0)
            pArray->addElement(getCmplxObject(pDZFunct, pCreFunct, pDelFunct, pName, pNamespace));
        else
            break;    
            
        ++count;    
    }
    
    if (AXIS_FAIL == m_nStatus) // TODO - not sure this line is needed
        m_pNode = NULL;         // TODO - not sure this line is needed
    else if (arraySize > 0)
        skipNode();
        
    return pArray;
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

Axis_Array*SoapDeSerializer::
getBasicArray (XSDTYPE nType, const AxisChar * pName, const AxisChar * pNamespace)
{
    int size = 0;      
    Axis_Array* Array = new Axis_Array();
    Array->m_Type = nType;

    // if anything has gone wrong earlier just do nothing
    if (AXIS_SUCCESS != m_nStatus)
        return Array;

    // Loop through the array adding elements.
    IAnySimpleType* pSimpleType = NULL;
    void * pValue = NULL;
    
    try
    {
        size = getArraySize ();
        const char* elementName;
        int count = 0;
                
        while(RPC_ENCODED != m_nStyle || count < size)
        {
            // For RPC-encoded arrays, the element name in array cannot be derived - 
            // within an array value element names are not significant -   
            // so we read until end-of-element is encountered (i.e. null string 
            // is returned from peek()). 
            elementName = m_pParser->peek();
            if ((RPC_ENCODED == m_nStyle && 0x00 != *elementName) || strcmp(elementName, pName) == 0)
            {
            	// TODO instead of deleting the pointer use it by by-passing addElement().
            	if (XSD_ANYTYPE != nType)
            	{
	                if (0 == count)
	                    pSimpleType = AxisUtils::createSimpleTypeObject(nType);
	                getElement(pName, pNamespace, pSimpleType, (bool)(RPC_ENCODED == m_nStyle));
	                pValue = pSimpleType->getValue();
	                Array->addElement(pValue);
	                Axis::AxisDelete(pValue, pSimpleType->getType());
            	}
            	else
            	{
            		pValue = getElementAsAnyType(pName, pNamespace);
            		Array->addElement(pValue);
            		Axis::AxisDelete(pValue, XSD_ANYTYPE);
            	}
            	
                pValue = NULL;
            }
            else
                break;
                
            ++count;
        }             
    }
    catch ( ... )
    {
        if (pSimpleType)
        { 
            if (pValue)
                Axis::AxisDelete(pValue, pSimpleType->getType());
            delete pSimpleType;
        }
        
        delete Array;
        
        throw;
    }
    
    delete pSimpleType;
    
    if (AXIS_FAIL == m_nStatus) // TODO - not sure this line is needed
        m_pNode = NULL;         // TODO - not sure this line is needed
    else if (size > 0)
        skipNode();
                
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
void *SoapDeSerializer::
getCmplxObject (void *pDZFunct, void *pCreFunct, void *pDelFunct, 
                const AxisChar * pName, const AxisChar * pNamespace, bool isFault)
{
    if (!isFault)
    {
        if (AXIS_SUCCESS != m_nStatus)
            return NULL;
    
        if (AXIS_FAIL == getNextNode(RPC_ENCODED != m_nStyle))
            return NULL;  
    }
    
    if (RPC_ENCODED != m_nStyle) // TODO - why do we selectively do this check and not for all?
        if (0 != strcmp (pName, m_pNode->m_pchNameOrValue))
        {
            /*
             * TODO: Need to verify what WS-I 1.0 says
             * about the mandatory of all the elements in the response in case of
             * null value or none filled value. Some Web services servers work
             * like this. This apply for all the rest of the deserializer.
             */
            return NULL;            
        }
    
    // TODO - even if node is nil, there may be attributes associated with the element that 
    // TODO - need to be deserialized - thus in the generated code we need to get the nil 
    // TODO - attribute if element is nillable and check if it is true or false, in which case
    // TODO - we would short-circuit the deserialization after any other attributes have been 
    // TODO - obtained. Thus changes will need to be made here and in the code generator.             
    // if node contain attributes let them be used by the complex type's deserializer
    if (isNilValue())
    {
        skipNode();
        return NULL;
    }
    
    // Make attributes available to code that deserializes the attributes
    m_pCurrNode = NULL;
    if (0 != m_pNode->m_pchAttributes[0])
        m_pCurrNode = m_pNode;    
    
    // indicate node consumed
    m_pNode = NULL; 
    
    if (!isFault && AXIS_FAIL == m_nStatus)  
        return NULL;  
        
    // Call the Axis-generated routine that will deserialize complex object,
    // including any attributes.
    
    TRACE_OBJECT_CREATE_FUNCT_ENTRY(pCreFunct, 0);
    void *pObject = ((AXIS_OBJECT_CREATE_FUNCT) pCreFunct) (0);
    TRACE_OBJECT_CREATE_FUNCT_EXIT(pCreFunct, pObject);
    
    if (pObject && pDZFunct)
    {
        try 
        {        
            TRACE_DESERIALIZE_FUNCT_ENTRY(pDZFunct, pObject, this);
            m_nStatus =    ((AXIS_DESERIALIZE_FUNCT) pDZFunct) (pObject, this);
            TRACE_DESERIALIZE_FUNCT_EXIT(pDZFunct, m_nStatus);
        
            if (AXIS_SUCCESS == m_nStatus)
                skipNode();
            else
            {
                TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, 0);
                ((AXIS_OBJECT_DELETE_FUNCT) pDelFunct) (pObject, 0);
                TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);
            
                pObject = NULL;
            }
        }
        catch ( ... )
        {
            TRACE_OBJECT_DELETE_FUNCT_ENTRY(pDelFunct, pObject, 0);
            ((AXIS_OBJECT_DELETE_FUNCT) pDelFunct) (pObject, 0);
            TRACE_OBJECT_DELETE_FUNCT_EXIT(pDelFunct);

            throw;
        }
    }

    return pObject;
}

void * SoapDeSerializer::
getAttribute(const AxisChar* pName, const AxisChar * pNamespace, IAnySimpleType * pSimpleType)
{
    if (m_pCurrNode)
        for (int i=0; m_pCurrNode->m_pchAttributes[i]; i += 3)
            if (0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))
            {
                pSimpleType->deserialize(m_pCurrNode->m_pchAttributes[i+2]);
                return pSimpleType->getValue();
            }
    
    return NULL;
}

xsd__int *SoapDeSerializer::
getAttributeAsInt (const AxisChar * pName, const AxisChar * pNamespace)
{
    Int simpleType;
    return (xsd__int *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__boolean *SoapDeSerializer::
getAttributeAsBoolean (const AxisChar * pName, const AxisChar * pNamespace)
{
    Boolean simpleType;
    return (xsd__boolean *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__unsignedInt *SoapDeSerializer::
getAttributeAsUnsignedInt (const AxisChar * pName, const AxisChar * pNamespace)
{
    UnsignedInt simpleType;
    return (xsd__unsignedInt *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__short *SoapDeSerializer::
getAttributeAsShort (const AxisChar * pName, const AxisChar * pNamespace)
{
    Short simpleType;
    return (xsd__short *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__unsignedShort *SoapDeSerializer::
getAttributeAsUnsignedShort (const AxisChar * pName, const AxisChar * pNamespace)
{
    UnsignedShort simpleType;
    return (xsd__unsignedShort *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__byte *SoapDeSerializer::
getAttributeAsByte (const AxisChar * pName, const AxisChar * pNamespace)
{
    Byte simpleType;
    return (xsd__byte *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__unsignedByte *SoapDeSerializer::
getAttributeAsUnsignedByte (const AxisChar * pName, const AxisChar * pNamespace)
{
    UnsignedByte simpleType;
    return (xsd__unsignedByte *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__long *SoapDeSerializer::
getAttributeAsLong (const AxisChar * pName, const AxisChar * pNamespace)
{
    Long simpleType;
    return (xsd__long *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__integer *SoapDeSerializer::
getAttributeAsInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    Integer simpleType;
    return (xsd__integer *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__nonNegativeInteger *SoapDeSerializer::
getAttributeAsNonNegativeInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    NonNegativeInteger simpleType;
    return (xsd__nonNegativeInteger *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__positiveInteger *SoapDeSerializer::
getAttributeAsPositiveInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    PositiveInteger simpleType;
    return (xsd__positiveInteger *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__nonPositiveInteger *SoapDeSerializer::
getAttributeAsNonPositiveInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    NonPositiveInteger simpleType;
    return (xsd__nonPositiveInteger *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__negativeInteger *SoapDeSerializer::
getAttributeAsNegativeInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    NegativeInteger simpleType;
    return (xsd__negativeInteger *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__unsignedLong *SoapDeSerializer::
getAttributeAsUnsignedLong (const AxisChar *pName, const AxisChar * pNamespace)
{
    UnsignedLong simpleType;
    return (xsd__unsignedLong *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__float *SoapDeSerializer::
getAttributeAsFloat (const AxisChar * pName, const AxisChar * pNamespace)
{
    Float simpleType;
    return (xsd__float *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__double *SoapDeSerializer::
getAttributeAsDouble (const AxisChar * pName, const AxisChar * pNamespace)
{
    Double simpleType;
    return (xsd__double *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__decimal *SoapDeSerializer::
getAttributeAsDecimal (const AxisChar * pName, const AxisChar * pNamespace)
{
    Decimal simpleType;
    return (xsd__decimal *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__NOTATION SoapDeSerializer::
getAttributeAsNOTATION (const AxisChar * pName, const AxisChar * pNamespace)
{
    NOTATION simpleType;
    return (xsd__NOTATION)getAttribute(pName, pNamespace, &simpleType);
}

xsd__string SoapDeSerializer::
getAttributeAsString (const AxisChar * pName, const AxisChar * pNamespace)
{
    String simpleType;
    return (xsd__string)getAttribute(pName, pNamespace, &simpleType);
}

xsd__normalizedString SoapDeSerializer::
getAttributeAsNormalizedString (const AxisChar * pName, const AxisChar * pNamespace)
{
    NormalizedString simpleType;
    return (xsd__normalizedString)getAttribute(pName, pNamespace, &simpleType);
}

xsd__token SoapDeSerializer::
getAttributeAsToken (const AxisChar * pName, const AxisChar * pNamespace)
{
    Token simpleType;
    return (xsd__token)getAttribute(pName, pNamespace, &simpleType);
}

xsd__language SoapDeSerializer::
getAttributeAsLanguage (const AxisChar * pName, const AxisChar * pNamespace)
{
    Language simpleType;
    return (xsd__language)getAttribute(pName, pNamespace, &simpleType);
}

xsd__NMTOKEN SoapDeSerializer::
getAttributeAsNMTOKEN (const AxisChar * pName, const AxisChar * pNamespace)
{
    NMTOKEN simpleType;
    return (xsd__NMTOKEN)getAttribute(pName, pNamespace, &simpleType);
}

xsd__NMTOKENS SoapDeSerializer::
getAttributeAsNMTOKENS (const AxisChar * pName, const AxisChar * pNamespace)
{
    NMTOKENS simpleType;
    return (xsd__NMTOKENS)getAttribute(pName, pNamespace, &simpleType);
}

xsd__Name SoapDeSerializer::
getAttributeAsName (const AxisChar * pName, const AxisChar * pNamespace)
{
    Name simpleType;
    return (xsd__Name)getAttribute(pName, pNamespace, &simpleType);
}

xsd__NCName SoapDeSerializer::
getAttributeAsNCName (const AxisChar * pName, const AxisChar * pNamespace)
{
    NCName simpleType;
    return (xsd__NCName)getAttribute(pName, pNamespace, &simpleType);
}

xsd__ID SoapDeSerializer::
getAttributeAsID (const AxisChar * pName, const AxisChar * pNamespace)
{
    ID simpleType;
    return (xsd__ID)getAttribute(pName, pNamespace, &simpleType);
}

xsd__IDREF SoapDeSerializer::
getAttributeAsIDREF (const AxisChar * pName, const AxisChar * pNamespace)
{
    IDREF simpleType;
    return (xsd__IDREF)getAttribute(pName, pNamespace, &simpleType);
}

xsd__IDREFS SoapDeSerializer::
getAttributeAsIDREFS (const AxisChar * pName, const AxisChar * pNamespace)
{
    IDREFS simpleType;
    return (xsd__IDREFS)getAttribute(pName, pNamespace, &simpleType);
}

xsd__ENTITY SoapDeSerializer::
getAttributeAsENTITY (const AxisChar * pName, const AxisChar * pNamespace)
{
    ENTITY simpleType;
    return (xsd__ENTITY)getAttribute(pName, pNamespace, &simpleType);
}

xsd__ENTITIES SoapDeSerializer::
getAttributeAsENTITIES (const AxisChar * pName, const AxisChar * pNamespace)
{
    ENTITIES simpleType;
    return (xsd__ENTITIES)getAttribute(pName, pNamespace, &simpleType);
}

xsd__anyURI SoapDeSerializer::
getAttributeAsAnyURI (const AxisChar * pName, const AxisChar * pNamespace)
{
    AnyURI simpleType;
    return (xsd__anyURI)getAttribute(pName, pNamespace, &simpleType);
}

xsd__QName SoapDeSerializer::
getAttributeAsQName (const AxisChar * pName, const AxisChar * pNamespace)
{
    XSD_QName simpleType;
    return (xsd__QName)getAttribute(pName, pNamespace, &simpleType);
}

xsd__hexBinary *SoapDeSerializer::
getAttributeAsHexBinary (const AxisChar * pName, const AxisChar * pNamespace)
{
    HexBinary simpleType;
    return (xsd__hexBinary *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__base64Binary *SoapDeSerializer::
getAttributeAsBase64Binary (const AxisChar * pName, const AxisChar * pNamespace)
{
    Base64Binary simpleType;
    return (xsd__base64Binary *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__dateTime *SoapDeSerializer::
getAttributeAsDateTime (const AxisChar * pName, const AxisChar * pNamespace)
{
    DateTime simpleType;
    return (xsd__dateTime *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__date *SoapDeSerializer::
getAttributeAsDate (const AxisChar * pName, const AxisChar * pNamespace)
{
    Date simpleType;
    return (xsd__date *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__time *SoapDeSerializer::
getAttributeAsTime (const AxisChar * pName, const AxisChar * pNamespace)
{
    Time simpleType;
    return (xsd__time *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__gDay*SoapDeSerializer::
getAttributeAsGDay (const AxisChar * pName, const AxisChar * pNamespace)
{
    GDay simpleType;
    return (xsd__gDay *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__gMonth*SoapDeSerializer::
getAttributeAsGMonth (const AxisChar * pName, const AxisChar * pNamespace)
{
    GMonth simpleType;
    return (xsd__gMonth *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__gMonthDay*SoapDeSerializer::
getAttributeAsGMonthDay (const AxisChar * pName, const AxisChar * pNamespace)
{
    GMonthDay simpleType;
    return (xsd__gMonthDay *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__gYear*SoapDeSerializer::
getAttributeAsGYear (const AxisChar * pName, const AxisChar * pNamespace)
{
    GYear simpleType;
    return (xsd__gYear *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__gYearMonth*SoapDeSerializer::
getAttributeAsGYearMonth (const AxisChar * pName, const AxisChar * pNamespace)
{
    GYearMonth simpleType;
    return (xsd__gYearMonth *)getAttribute(pName, pNamespace, &simpleType);
}

xsd__duration *SoapDeSerializer::
getAttributeAsDuration (const AxisChar * pName, const AxisChar * pNamespace)
{
    Duration simpleType;
    return (xsd__duration *)getAttribute(pName, pNamespace, &simpleType);
}

bool SoapDeSerializer::
isNilValue()
{
    bool isNillResult = false;    

    // Go through the attributes looking for nil.  We consider
    // "true" or "1" to be equivalent.
    for (int i = 0; m_pNode->m_pchAttributes[i]; i += 3)
    {
        string sLocalName = m_pNode->m_pchAttributes[i];
        string sValue = m_pNode->m_pchAttributes[i + 2];

        if (strcmp("nil", sLocalName.c_str()) == 0 &&
            (strcmp("true", sValue.c_str()) == 0 || strcmp( "1", sValue.c_str()) == 0))
        {
            isNillResult = true;
            break;
        }
    }

    return isNillResult;
}

void SoapDeSerializer::
processFaultDetail(IAnySimpleType * pSimpleType, const AxisChar* elementValue)
{
    bool isWhiteSpace = true;
    
    int len = elementValue ? strlen(elementValue) : 0;
    
    // See if detail element character data is whitespace
    for (int i=0; i<len; ++i)
        if (!(*elementValue == '\r' || *elementValue == '\n' 
                || *elementValue == '\t' || *elementValue == ' '))
        {
            isWhiteSpace = false;
            break;
        }
    
    // If it is whitespace, peek to see if next element is the start of
    // a new element, in which case the fault detail is complex.  Peek()
    // return null string if end-element tag is encountered.
    char *workingString = (char *)elementValue;
    if (isWhiteSpace)
    {
        // Since we will be doing a peek, elementValue will no longer
        // be valid, so if we will deserialize null string if we need to.
        workingString = "";
        
        // if end tag not found, must be complex detail - fault handling code
        // will know what to do when we return with no deserialization
        const char* nextName = m_pParser->peek();
        if (nextName[0] != 0x00)
        {
            m_pNode = NULL; // node consumed
            return;
        }
    }
    
    // If here, detail is simple character data, deserialize simple string
    pSimpleType->deserialize(workingString);
    skipNode();        
    
    return;
}

void SoapDeSerializer::
getElement (const AxisChar * pName, const AxisChar * pNamespace,
            IAnySimpleType * pSimpleType,
            bool isArrayElement)
{   
    if (AXIS_SUCCESS != m_nStatus)
        return;
        
    if (AXIS_FAIL == getNextNode(RPC_ENCODED != m_nStyle))
        return;

    bool    bNillFound = false;
    if (0 == strcmp (pName, m_pNode->m_pchNameOrValue))
        bNillFound = isNilValue();

    if (RPC_ENCODED == m_nStyle)
    {
        // it is an error if type is different if the type exists
        bool foundType;
        if (!bNillFound && !isArrayElement 
                && (pSimpleType->getType() != getXSDType(m_pNode, foundType)) && foundType)
            m_nStatus = AXIS_FAIL;
    }
    else if (0 != strcmp (pName, m_pNode->m_pchNameOrValue))
       return;
    
    if (AXIS_FAIL == m_nStatus)
        return;
    
    // get next element, character mode 
    if (AXIS_FAIL == getNextNode(false, true))
       return;
      
    if (CHARACTER_ELEMENT == m_pNode->m_type)
    {
        const AxisChar* elementValue = m_pNode->m_pchNameOrValue;
                            
        // Code for fault finding.  As added protection against false findings, 
        // the namespace has been set to an invalid value of a single space character.
        if (pNamespace != NULL && *pNamespace == ' ')
            processFaultDetail(pSimpleType, elementValue);
        else
        {
            pSimpleType->deserialize(elementValue);
            skipNode();
        }
    }
    else if (END_ELEMENT == m_pNode->m_type)
    {
        // xsi:nil="true" OR empty tag case <tag/>
        pSimpleType->deserialize(bNillFound ? NULL : "");
        m_pNode = NULL;
    }

    return;
}

/*
 * Deserializing Elements as values directly. 
 */
xsd__boolean *SoapDeSerializer::
getElementAsBoolean (const AxisChar * pName, const AxisChar * pNamespace)
{
    Boolean simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getBoolean();
}

xsd__int *SoapDeSerializer::
getElementAsInt (const AxisChar * pName, const AxisChar * pNamespace)
{
    Int simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getInt();
}


xsd__unsignedInt *SoapDeSerializer::
getElementAsUnsignedInt (const AxisChar * pName, const AxisChar * pNamespace)
{
    UnsignedInt simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedInt();
}

xsd__short *SoapDeSerializer::
getElementAsShort (const AxisChar * pName, const AxisChar * pNamespace)
{
    Short simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getShort();
}

xsd__unsignedShort *SoapDeSerializer::
getElementAsUnsignedShort (const AxisChar * pName, const AxisChar * pNamespace)
{
    UnsignedShort simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedShort();
}

xsd__byte *SoapDeSerializer::
getElementAsByte (const AxisChar * pName, const AxisChar * pNamespace)
{
    Byte simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getByte();
}

xsd__unsignedByte *SoapDeSerializer::
getElementAsUnsignedByte (const AxisChar * pName, const AxisChar * pNamespace)
{
    UnsignedByte simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedByte();
}

xsd__long *SoapDeSerializer::
getElementAsLong (const AxisChar * pName, const AxisChar * pNamespace)
{
    Long simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getLong();
}

xsd__integer *SoapDeSerializer::
getElementAsInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    Integer simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getInteger();
}

xsd__unsignedLong *SoapDeSerializer::
getElementAsUnsignedLong (const AxisChar * pName, const AxisChar * pNamespace)
{
    UnsignedLong simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getUnsignedLong();
}

xsd__float *SoapDeSerializer::
getElementAsFloat (const AxisChar * pName, const AxisChar * pNamespace)
{
    Float simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getFloat();
}

xsd__double *SoapDeSerializer::
getElementAsDouble (const AxisChar * pName, const AxisChar * pNamespace)
{
    Double simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDouble();
}

xsd__decimal *SoapDeSerializer::
getElementAsDecimal (const AxisChar * pName, const AxisChar * pNamespace)
{
    Decimal simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDecimal();
}

xsd__string SoapDeSerializer::
getElementAsString (const AxisChar * pName, const AxisChar * pNamespace)
{
    String simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getString();
}

xsd__anyURI SoapDeSerializer::
getElementAsAnyURI (const AxisChar * pName, const AxisChar * pNamespace)
{
    AnyURI simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getAnyURI();
}

xsd__QName SoapDeSerializer::
getElementAsQName (const AxisChar * pName, const AxisChar * pNamespace)
{
    XSD_QName simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getQName();
}

xsd__hexBinary *SoapDeSerializer::
getElementAsHexBinary (const AxisChar * pName, const AxisChar * pNamespace)
{
    HexBinary simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getHexBinary();
}

xsd__base64Binary *SoapDeSerializer::
getElementAsBase64Binary (const AxisChar * pName, const AxisChar * pNamespace)
{
    Base64Binary simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getBase64Binary();
}

xsd__dateTime *SoapDeSerializer::
getElementAsDateTime (const AxisChar * pName, const AxisChar * pNamespace)
{
    DateTime simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDateTime();
}

xsd__date *SoapDeSerializer::
getElementAsDate (const AxisChar * pName, const AxisChar * pNamespace)
{
    Date simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDate();
}

xsd__time *SoapDeSerializer::
getElementAsTime (const AxisChar * pName, const AxisChar * pNamespace)
{
    Time simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getTime();
}

xsd__duration *SoapDeSerializer::
getElementAsDuration (const AxisChar * pName, const AxisChar * pNamespace)
{
    Duration simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getDuration();
}

xsd__gYearMonth *SoapDeSerializer::
getElementAsGYearMonth (const AxisChar * pName, const AxisChar * pNamespace)
{
    GYearMonth simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGYearMonth();
}

xsd__gYear *SoapDeSerializer::
getElementAsGYear (const AxisChar * pName, const AxisChar * pNamespace)
{
    GYear simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGYear();
}

xsd__gMonthDay *SoapDeSerializer::
getElementAsGMonthDay (const AxisChar * pName, const AxisChar * pNamespace)
{
    GMonthDay simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGMonthDay();
}

xsd__gDay *SoapDeSerializer::
getElementAsGDay (const AxisChar * pName, const AxisChar * pNamespace)
{
    GDay simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGDay();
}

xsd__gMonth *SoapDeSerializer::
getElementAsGMonth (const AxisChar * pName, const AxisChar * pNamespace)
{
    GMonth simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getGMonth();
}

xsd__nonPositiveInteger *SoapDeSerializer::
getElementAsNonPositiveInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    NonPositiveInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNonPositiveInteger();
}

xsd__negativeInteger *SoapDeSerializer::
getElementAsNegativeInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    NegativeInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNegativeInteger();
}

xsd__nonNegativeInteger *SoapDeSerializer::
getElementAsNonNegativeInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    NonNegativeInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNonNegativeInteger();
}

xsd__positiveInteger *SoapDeSerializer::
getElementAsPositiveInteger (const AxisChar * pName, const AxisChar * pNamespace)
{
    PositiveInteger simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getPositiveInteger();
}

xsd__normalizedString SoapDeSerializer::
getElementAsNormalizedString (const AxisChar * pName, const AxisChar * pNamespace)
{
    NormalizedString simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNormalizedString();
}

xsd__token SoapDeSerializer::
getElementAsToken (const AxisChar * pName, const AxisChar * pNamespace)
{
    Token simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getToken();
}

xsd__language SoapDeSerializer::
getElementAsLanguage (const AxisChar * pName, const AxisChar * pNamespace)
{
    Language simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getLanguage();
}

xsd__Name SoapDeSerializer::
getElementAsName (const AxisChar * pName, const AxisChar * pNamespace)
{
    Name simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getName();
}

xsd__NCName SoapDeSerializer::
getElementAsNCName (const AxisChar * pName, const AxisChar * pNamespace)
{
    NCName simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNCName();
}

xsd__ID SoapDeSerializer::
getElementAsID (const AxisChar * pName, const AxisChar * pNamespace)
{
    ID simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getID();
}

xsd__IDREF SoapDeSerializer::
getElementAsIDREF (const AxisChar * pName, const AxisChar * pNamespace)
{
    IDREF simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getIDREF();
}

xsd__IDREFS SoapDeSerializer::
getElementAsIDREFS (const AxisChar * pName, const AxisChar * pNamespace)
{
    IDREFS simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getIDREFS();
}

xsd__ENTITY SoapDeSerializer::
getElementAsENTITY (const AxisChar * pName, const AxisChar * pNamespace)
{
    ENTITY simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getENTITY();
}

xsd__ENTITIES SoapDeSerializer::
getElementAsENTITIES (const AxisChar * pName, const AxisChar * pNamespace)
{
    ENTITIES simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getENTITIES();
}

xsd__NMTOKEN SoapDeSerializer::
getElementAsNMTOKEN (const AxisChar * pName, const AxisChar * pNamespace)
{
    NMTOKEN simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNMTOKEN();
}

xsd__NMTOKENS SoapDeSerializer::
getElementAsNMTOKENS (const AxisChar * pName, const AxisChar * pNamespace)
{
    NMTOKENS simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNMTOKENS();
}

xsd__NOTATION SoapDeSerializer::
getElementAsNOTATION (const AxisChar * pName, const AxisChar * pNamespace)
{
    NOTATION simpleType;
    getElement(pName, pNamespace, &simpleType);
    return simpleType.getNOTATION();
}

xsd__anyType SoapDeSerializer::
getElementAsAnyType(const AxisChar* pName, const AxisChar* pNamespace)
{
    xsd__anyType ret = NULL;
    
    if (AXIS_SUCCESS != m_nStatus)
        return ret;
        
    if (AXIS_FAIL == getNextNode(RPC_ENCODED != m_nStyle))
        return ret;

    if (RPC_ENCODED != m_nStyle && (0 != strcmp (pName, m_pNode->m_pchNameOrValue)))
       return ret;
    
    AnyType *any = getAnyObject();
    if (NULL != any)
    {
	    if (any->_size != 0)
	    {
	    	ret = any->_array[0];
	    	any->_array[0] = NULL;
	        delete [] any->_array;
	    }
	    delete any;
    }
    
    return ret;
}

xsd__string SoapDeSerializer::
getFaultAsXMLString()
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
    for (i=0; i<any->_size; i++) 
    	if (any->_array[i]) 
	    {
	        strcat(ret,any->_array[i]);
	        delete [] any->_array[i];
	    }
    delete [] any->_array;
    delete any;
    return ret;
}

/*
 * This method checks the attribute list of pElement node for the xsi:type 
 * attribute. If it is found then finds what the type is. Otherwise returns 
 * XSD_UNKNOWN.
 */
XSDTYPE SoapDeSerializer::
getXSDType (const AnyElement * pElement, bool & foundType)
{
    foundType = false;
    
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
            foundType = true;
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
HeaderBlock * SoapDeSerializer::
getHeaderBlock ()
{
    if (!m_pHeader)
        return NULL;

    return (HeaderBlock *) m_pHeader->getHeaderBlock (true);
}

/*
 * Used probably by a handler to add a header block to the Deserializer.
 * Probably to be used by a subsequent handler in the request message path
 */
int AXISCALL SoapDeSerializer::
addHeaderBlock (IHeaderBlock * pBlk)
{
    if (!m_pHeader)
        m_pHeader = new SoapHeader ();
    m_pHeader->addHeaderBlock ((HeaderBlock *) pBlk);
    return AXIS_SUCCESS;
}

xsd__hexBinary SoapDeSerializer::
getBodyAsHexBinary ()
{
    /* TODO */
    getNextNode();
    
    // skip the BODY element declaration
    if ((START_ELEMENT == m_pNode->m_type)
            && (0 == strcmp (m_pNode->m_pchNameOrValue, 
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])))
        getNextNode();

    string bodyContent = "";
    
    if (m_pNode)
    {
        while (!((END_ELEMENT == m_pNode->m_type) &&
               (0 == strcmp (m_pNode->m_pchNameOrValue,
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY]))))
            bodyContent += AnyElemntUtils::toString(m_pNode);
    }
        
    xsd__hexBinary value;
    xsd__int size = bodyContent.length() / 2;
    xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
    Hex_Decode (pTemp, bodyContent.c_str());
    pTemp[size] = 0; // Null terminate so it could be used as a string
    value.set(pTemp, size);
    delete [] pTemp;

    return value;     
}

xsd__base64Binary SoapDeSerializer::
getBodyAsBase64Binary ()
{
    /* TODO */
    getNextNode();
    
    // skip the BODY element declaration
    if ((START_ELEMENT == m_pNode->m_type)
            && (0 == strcmp (m_pNode->m_pchNameOrValue, 
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])))
        getNextNode();

    string bodyContent = "";
    
    if (m_pNode)
    {
        while (!((END_ELEMENT == m_pNode->m_type) &&
               (0 == strcmp (m_pNode->m_pchNameOrValue,
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY]))))
            bodyContent += AnyElemntUtils::toString(m_pNode);
    }

    xsd__base64Binary value;
    xsd__int size = apr_base64_decode_len (bodyContent.c_str());
    xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
    size = apr_base64_decode_binary (pTemp, bodyContent.c_str());
    pTemp[size] = 0; // Null terminate so it could used as a string
    value.set(pTemp, size);
    delete [] pTemp;
    return value;
}

AxisChar *SoapDeSerializer::
getBodyAsChar ()
{
    if (AXIS_FAIL == getNextNode())
        return NULL;

    // skip the BODY element declaration 
    if ((START_ELEMENT == m_pNode->m_type)
            && (0 == strcmp (m_pNode->m_pchNameOrValue,
                             SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY])))
    {
        if (AXIS_FAIL == getNextNode())
            return NULL;
    }
    
    pBodyContent = new AxisChar[1000];
    pBodyContent[0] = '\0';

    while (!((END_ELEMENT == m_pNode->m_type) &&
           (0 == strcmp (m_pNode->m_pchNameOrValue,
                         SoapKeywordMapping::map (m_nSoapVersion).pchWords[SKW_BODY]))))
        strcat (pBodyContent, (AnyElemntUtils::toString (m_pNode)).c_str ());

    return pBodyContent;
}

int SoapDeSerializer::
setNewSoapBody (AxisChar * pNewSoapBody)
{
    DeSerializerMemBufInputStream stream (pNewSoapBody);
    return m_pParser->setInputStream (&stream);
}

bool SoapDeSerializer::
isAnyMustUnderstandHeadersLeft ()
{
    /* TODO */
    return false;
}

int SoapDeSerializer::
flushInputStream ()
{
    int nChars = 100;
    char pBuffer[100];
    
    if (!m_pInputStream)
        return AXIS_FAIL;
    
    while (TRANSPORT_IN_PROGRESS == m_pInputStream->getBytes (pBuffer, &nChars));
    
    return AXIS_SUCCESS;
}

AnyType * SoapDeSerializer::
getAnyObject ()
{
    // Parser will throw an exception on a parser exception, that is ok...
    if (!m_pNode)
        m_pNode = m_pParser->anyNext();
    if (!m_pNode)
        return NULL;
    
    int tagCount = 0;
    int lstSize = 0;
    bool bContinue = false;

    AxisString xmlStr = "";
    AxisString nsDecls = "";

    list < AxisString > lstXML;

	AxisString inValue = "";
	AxisString outValue = "";

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
            if (m_pNode->m_pchNameOrValue && (*(m_pNode->m_pchNameOrValue) != 0x00))
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
        {
        	inValue = m_pNode->m_pchNameOrValue;
        	IAnySimpleType::replaceReservedCharacters(inValue, outValue);
            xmlStr += outValue;
        }
    
        if ( !bContinue && tagCount == 0 && (!xmlStr.empty ()))    /* copying the First level element into the list */
        {
            lstXML.push_back (xmlStr);
            xmlStr = "";
            m_pNode = NULL;
            break;
        }
    
        m_pNode = m_pParser->anyNext ();
    
        if (!m_pNode) // there is something wrong in the XSD Any XML stream
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

    AnyType *pAny = new AnyType ();
    pAny->_array = 0;
    pAny->_size = 0;
    
    lstSize = lstXML.size ();
    
    if (lstSize > 0)
    {
        pAny->_array = new char *[lstSize];

        list < AxisString >::iterator i;    /* Iterator for traversing the list */
    
        for (i = lstXML.begin (); i != lstXML.end (); i++)
        {
            const char *s = (*i).c_str ();
            pAny->_array[pAny->_size] = new char[strlen (s) + 1];
            strcpy (pAny->_array[pAny->_size], s);
            pAny->_size++;
        }
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
                       
                    xmlStr += " ";

                    if (pchPrefix && (*pchPrefix != 0x00))
                    {
                        xmlStr += pchPrefix;
                        xmlStr += ":";
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

        if (node->m_pchNamespace && (*(node->m_pchNamespace) != 0x00))
        {
            pchPrefix = m_pParser->getPrefix4NS (node->m_pchNamespace);

            if (pchPrefix && (*pchPrefix != 0x00))
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
                const char *pszXML = xmlStr.c_str();
                char *      pNSEnd = (char *)strchr( pszXML, ':');
                char *      pTagEnd = (char *)strchr( pszXML, '>');

                if( pNSEnd && (pNSEnd < pTagEnd))
                {
                    int      iNSStart = 1;
                    int      iNSEnd = (int) (strchr( pszXML, ':') - pszXML) - iNSStart;
                    string   sNamespace = xmlStr.substr( iNSStart, iNSEnd);
                    int      iTagEnd = 0;
                    char *   pSpace = (char *)strchr( pszXML, ' ');
                    char *   pBrace = (char *)strchr( pszXML, '>');

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

void SoapDeSerializer::
getChardataAs (void **pValue, XSDTYPE type)
{  
    if (!pValue || AXIS_FAIL == getNextNode(true, true))
        return;
    
    *pValue = NULL;
    if (CHARACTER_ELEMENT == m_pNode->m_type)
    {
        IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(type);
        pSimpleType->deserialize(m_pNode->m_pchNameOrValue);
        *pValue = pSimpleType->getValue();
        delete pSimpleType;
    }
}

/* This function is never called. */
AXIS_TRANSPORT_STATUS SoapDeSerializer::
DeSerializerMemBufInputStream::
sendBytes (const char *pcSendBuffer, const void *pBufferid)
{
    return TRANSPORT_FINISHED;
}

AXIS_TRANSPORT_STATUS SoapDeSerializer::
DeSerializerMemBufInputStream::
getBytes (char *pcBuffer, int *piRetSize)
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

ISoapAttachment* SoapDeSerializer::
getAttachment(const char* pcAttachmentid)    
{            
    return m_pInputStream->getAttachment(pcAttachmentid);         
}

ISoapAttachment** SoapDeSerializer::
getAllAttachments(int *pAttchArraySize)
{
    return m_pInputStream->getAllAttachments(pAttchArraySize);
}

const char* SoapDeSerializer::
getMethodNameToInvoke()
{
    return m_strMethodNameToInvoke.c_str();
}

void SoapDeSerializer::
setMethodNameToInvoke(const char* methodName)
{
    m_strMethodNameToInvoke = methodName;
}

AXIS_CPP_NAMESPACE_END
