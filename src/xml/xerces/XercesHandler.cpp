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
 * @author sanjaya singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#endif
#include "../../platforms/PlatformAutoSense.hpp"

#include "XercesHandler.h"
#include <xercesc/sax2/Attributes.hpp>
#include <stdio.h>


XercesHandler::
XercesHandler()
{
    m_pCurrElement = 0;
    m_pNextElement = new AnyElement;
    m_pPrefixMappingElement = new AnyElement;
    m_bEndElementFollows = false;
    m_pNextElement->m_pchNameOrValue = 0;
    m_pNextElement->m_pchNamespace = 0;
    m_pNextElement->m_pchAttributes[0] = 0;
    m_pPrefixMappingElement->m_pchNameOrValue = 0;
    m_pPrefixMappingElement->m_pchNamespace = 0;
    m_pPrefixMappingElement->m_pchAttributes[0] = 0;
    m_bGetPrefixMappings = false;
    m_bStartElementWaiting = false;
}

XercesHandler::
~XercesHandler()
{
    delete m_pNextElement;
    delete m_pPrefixMappingElement;
}

void XercesHandler::
startElement(const XMLCh *const uri,const XMLCh *const 
             localname,const XMLCh *const qname,
             const Attributes &attrs)
{
    m_pCurrElement = m_pNextElement;
    m_pNextElement->m_type = START_ELEMENT;
    m_pNextElement->m_type2 = END_ELEMENT;
    m_pNextElement->m_pchNameOrValue = XMLString::transcode(localname);
    m_pNextElement->m_pchNamespace = XMLString::transcode(uri);
    
    unsigned int len = attrs.getLength();
    unsigned int index;
    unsigned int i = 0;
    for (index = 0; index < len*3; index+=3)
    {    
        m_pNextElement->m_pchAttributes[index]   = XMLString::transcode(attrs.getLocalName(i));
        m_pNextElement->m_pchAttributes[index+1] = XMLString::transcode(attrs.getURI(i));
        m_pNextElement->m_pchAttributes[index+2] = XMLString::transcode(attrs.getValue(i));
        i++;
    }
    m_pNextElement->m_pchAttributes[len*3]=NULL;
}

const XML_Ch* XercesHandler::
ns4Prefix(const XML_Ch* prefix)
{
    if (prefix && m_NsStack.find(prefix) != m_NsStack.end())
        return m_NsStack[prefix].c_str();

    return NULL;
}

const XML_Ch* XercesHandler::
prefix4NS(const XML_Ch* pcNS)
{
    if (pcNS)
    {
        map<AxisXMLString, AxisXMLString>::iterator it;
        
        for (it=m_NsStack.begin(); it!=m_NsStack.end(); it++)
            if ((*it).second == pcNS)
                return (*it).first.c_str();
    }

    return NULL;
}
    
void XercesHandler::
characters(const XMLCh* const chars, const unsigned int length)
{
    const char *    cp_PreviousNameOrValue = NULL;

    if( m_pCurrElement && m_pCurrElement->m_pchNameOrValue)
        if (m_pCurrElement->m_type == CHARACTER_ELEMENT)
            cp_PreviousNameOrValue = m_pCurrElement->m_pchNameOrValue;

    m_pCurrElement = m_pNextElement;
    m_pNextElement->m_type = CHARACTER_ELEMENT;

    // The following code is necessary as it is important to get the correct heap
    // (i.e the one that XMLString is using!) when creating a memory object to put
    // back into 'm_pNextElement->m_pchNameOrValue'.  By using the XMLString
    // function, we can ensure that only the memory belonging to (and thus able to
    // destroy) the same segment as XMLString is used.  If you don't understand
    // what is going on, don't change it!
    if (cp_PreviousNameOrValue)
    {
        // Get a pointer to the transcoded character.
        char *pTransChar = XMLString::transcode( chars);

        // Create a dummy string and populate.
        char *psDummy = new char[ strlen( m_pNextElement->m_pchNameOrValue) +
                                    strlen( pTransChar) + 1];
        strcpy( psDummy, m_pNextElement->m_pchNameOrValue);
        strcat( psDummy, pTransChar);

        // Create pointer to new Name or Value string.
        char *pNewNameOrValue = XMLString::replicate( psDummy);

        // Delete the old Name and Value string.
        XMLString::release( const_cast<char**> (&(m_pCurrElement->m_pchNameOrValue)));

        // Assign the new value of Name or Value string.
        m_pNextElement->m_pchNameOrValue = pNewNameOrValue;

        // Clean up.
        delete [] psDummy;
        XMLString::release( &pTransChar);
    }
    else
        m_pNextElement->m_pchNameOrValue = XMLString::transcode( chars);
}

void XercesHandler::
ignorableWhitespace(const XMLCh* const chars, const unsigned int length)
{}

void XercesHandler::
resetDocument()
{}

void XercesHandler::
warning(const SAXParseException& exc)
{}

void XercesHandler::
error(const SAXParseException& exc)
{
    throw exc;    
}

void XercesHandler::
fatalError(const SAXParseException& exc)
{
    throw exc;
}

void XercesHandler::
endElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname)
{
    // It seems that both startElement and endElement events fired within a single parseNext call
    if (m_pCurrElement && (START_ELEMENT == m_pCurrElement->m_type))
    {
        m_pCurrElement->m_type2 = START_END_ELEMENT;
        m_bEndElementFollows = true;
        return;
    }
    
    m_pCurrElement = m_pNextElement;
    m_pNextElement->m_type = END_ELEMENT;

    if( m_pNextElement->m_type2 == START_END_ELEMENT)
        m_pNextElement->m_type2 = END_ELEMENT;

    m_pNextElement->m_pchNameOrValue = XMLString::transcode(localname);
    m_pNextElement->m_pchNamespace = XMLString::transcode(uri);
    m_pNextElement->m_pchAttributes[0] = NULL;
}

void XercesHandler::
startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri)
{
    char* pchPrefix = XMLString::transcode(prefix);
    char* pchUri = XMLString::transcode(uri);
    m_NsStack[pchPrefix] = pchUri;
    
    // Store only if interested in prefix mappings 
    if (m_bGetPrefixMappings)
        m_CurrPrefixMappings[pchPrefix] = pchUri;
    else
    {
        XMLString::release(&pchPrefix);
        XMLString::release(&pchUri);
    }
}

void XercesHandler::
endPrefixMapping(const XMLCh* const prefix)
{
    // we are not interested in end prefix mapping events
    char* pchPrefix = XMLString::transcode(prefix);
    m_NsStack.erase(pchPrefix);
    XMLString::release(&pchPrefix);
}

void XercesHandler::
freeElement()
{
    if (m_pCurrElement)
    {
        if (m_bEndElementFollows)
        {
            // free only attributes list if available. Next time the same m_pNextElement is freed.
            m_bEndElementFollows = false;
            m_pCurrElement->m_type = END_ELEMENT;
            freeAttributes();
            m_pCurrElement->m_pchAttributes[0] = NULL;
        }
        else
        {
            // free all inner strings
            if (m_pCurrElement->m_pchNameOrValue)
            {
                XMLString::release(const_cast<char**>(&(m_pCurrElement->m_pchNameOrValue)));
                m_pCurrElement->m_pchNameOrValue = 0;
            }
            if (m_pCurrElement->m_pchNamespace)
            {
                XMLString::release(const_cast<char**>(&(m_pCurrElement->m_pchNamespace)));
                m_pCurrElement->m_pchNamespace = 0;
            }
            freeAttributes();
            m_pCurrElement = 0;
        }
    }
}

void XercesHandler::
freeAttributes()
{
    for (int x=0; m_pCurrElement->m_pchAttributes[x]; x+=3)
        if (m_pCurrElement->m_pchAttributes[x])
        {
            XMLString::release(const_cast<char**>(&(m_pCurrElement-> m_pchAttributes[x])));
            m_pCurrElement->m_pchAttributes[x] = 0;
            if (m_pCurrElement->m_pchAttributes[x+1])
                XMLString::release(const_cast<char**>(&(m_pCurrElement->m_pchAttributes[x+1])));
            if (m_pCurrElement->m_pchAttributes[x+2])
                XMLString::release(const_cast<char**>(&(m_pCurrElement->m_pchAttributes[x+2])));
        }
}

AnyElement* XercesHandler::
getAnyElement()
{
    if (m_bGetPrefixMappings)
    {
        if (m_CurrPrefixMappings.size() > 0)
        {
            map<const AxisChar*, const AxisChar*>::iterator it = m_CurrPrefixMappings.begin();
            m_pPrefixMappingElement->m_pchNameOrValue = (*it).first;
            m_pPrefixMappingElement->m_pchNamespace = (*it).second;
            m_pPrefixMappingElement->m_type = START_PREFIX;
            m_CurrPrefixMappings.erase(it);
            m_pCurrElement = m_pPrefixMappingElement;
            m_bStartElementWaiting = true;
        }
        else if (m_bStartElementWaiting)
        {
            m_pCurrElement = m_pNextElement;
            m_bStartElementWaiting = false;
        }
    }
    return m_pCurrElement;
}

const char* XercesHandler::
peekNextElementName()
{        
    if (m_pCurrElement)
        return m_pCurrElement->m_pchNameOrValue;
    else 
        return NULL;
}


const XML_NODE_TYPE XercesHandler::
peekNextElementType()
{
    if (m_pCurrElement)
        return (const XML_NODE_TYPE) m_pCurrElement->m_type;
    else
        return UNKNOWN;
}

void XercesHandler::
setGetPrefixMappings(bool bValue)
{
    m_bGetPrefixMappings = bValue;
}


void XercesHandler::
reset()
{
    m_bEndElementFollows = false;
    m_pCurrElement = m_pNextElement;
    freeElement();
    m_pCurrElement = m_pPrefixMappingElement;
    freeElement();
    m_bGetPrefixMappings = false;
    m_bStartElementWaiting = false;    
    m_pCurrElement = 0;
    if (m_CurrPrefixMappings.size() > 0)
    {
        map<const AxisChar*, const AxisChar*>::iterator it = m_CurrPrefixMappings.begin();
        XMLString::release(const_cast<char**>(&((*it).first)));
        XMLString::release(const_cast<char**>(&((*it).second)));
        m_CurrPrefixMappings.erase(it);
    }
}

