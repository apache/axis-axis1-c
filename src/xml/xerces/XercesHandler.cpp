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

#include "XercesHandler.h"
#include <xercesc/sax2/Attributes.hpp>
#include <stdio.h>


XercesHandler::XercesHandler()
{
    m_nStatus = AXIS_SUCCESS;
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

XercesHandler::~XercesHandler()
{
	delete m_pNextElement;
	delete m_pPrefixMappingElement;
}

void XercesHandler::startElement(const XMLCh *const uri,const XMLCh *const 
                                 localname,const XMLCh *const qname,
                                 const Attributes &attrs)
{
    m_pCurrElement = m_pNextElement;
    m_pNextElement->m_type = START_ELEMENT;
    m_pNextElement->m_pchNameOrValue = XMLString::transcode(localname);
    m_pNextElement->m_pchNamespace = XMLString::transcode(uri);
    
    unsigned int len = attrs.getLength();
    unsigned int index;
    unsigned int i = 0;
    for (index = 0; index < len*3; index+=3)
    {    
        m_pNextElement->m_pchAttributes[index] = 
            XMLString::transcode(attrs.getLocalName(i));
        m_pNextElement->m_pchAttributes[index+1] = 
            XMLString::transcode(attrs.getURI(i));
        m_pNextElement->m_pchAttributes[index+2] = 
            XMLString::transcode(attrs.getValue(i));
        i++;
    }
    m_pNextElement->m_pchAttributes[len*3]=NULL;
}

const XML_Ch* XercesHandler::ns4Prefix(const XML_Ch* prefix)
{
    if (m_NsStack.find(prefix) != m_NsStack.end())
    {
        return m_NsStack[prefix].c_str();
    }
    return NULL;
}

const XML_Ch* XercesHandler::prefix4NS(const XML_Ch* pcNS)
{
    for (map<AxisXMLString, AxisXMLString>::iterator it=m_NsStack.begin();
         it!=m_NsStack.end(); it++)
    {
        if ((*it).second == pcNS)
        {
            return (*it).first.c_str();
        }
    }
    return 0;
}
    
void XercesHandler::characters(const XMLCh* const chars, 
                               const unsigned int length)
{
    const char* cp_PreviousNameOrValue = NULL;
    if( m_pCurrElement && m_pCurrElement->m_pchNameOrValue)
    {
        if (m_pCurrElement->m_type == CHARACTER_ELEMENT)
            cp_PreviousNameOrValue = m_pCurrElement->m_pchNameOrValue;
    }
    m_pCurrElement = m_pNextElement;
    m_pNextElement->m_type = CHARACTER_ELEMENT;
    
    if (cp_PreviousNameOrValue)
    {
        char* cp_CurrentNameOrValue = XMLString::transcode(chars);
        char* cp_FullNameOrValue  = (char*) malloc(strlen(cp_PreviousNameOrValue) + strlen(cp_CurrentNameOrValue) + 1);
        cp_FullNameOrValue[0] = '\0'; 
        strcat(cp_FullNameOrValue, cp_PreviousNameOrValue);
        strcat(cp_FullNameOrValue, cp_CurrentNameOrValue);
        m_pNextElement->m_pchNameOrValue = (const char*)cp_FullNameOrValue;
        free(const_cast <char*> (cp_PreviousNameOrValue));
        free(cp_CurrentNameOrValue);
    }
    else
        m_pNextElement->m_pchNameOrValue = XMLString::transcode(chars);
    
}
void XercesHandler::ignorableWhitespace(const XMLCh* const chars, 
                                        const unsigned int length)
{}
void XercesHandler::resetDocument()
{}


void XercesHandler::warning(const SAXParseException& exception)
{}
void XercesHandler::error(const SAXParseException& exception)
{
    m_nStatus = AXIS_FAIL;
}
void XercesHandler::fatalError(const SAXParseException& exception)
{
    m_nStatus = AXIS_FAIL;
}

void XercesHandler::endElement (const XMLCh *const uri,
                                const XMLCh *const localname,
                                const XMLCh *const qname)
{
    if (m_pCurrElement && (START_ELEMENT == m_pCurrElement->m_type))
    /* it seems that both startElement and endElemen events fired within a
    single parseNext call */
    {
        m_pCurrElement->m_type2 = END_ELEMENT;
        m_bEndElementFollows = true;
        return;
    }
    m_pCurrElement = m_pNextElement;
    m_pNextElement->m_type = END_ELEMENT;
    m_pNextElement->m_pchNameOrValue = XMLString::transcode(localname);
    m_pNextElement->m_pchNamespace = XMLString::transcode(uri);
    m_pNextElement->m_pchAttributes[0] = NULL;
}

void XercesHandler::startPrefixMapping(const XMLCh* const prefix,
                                       const XMLCh* const uri)
{
	char* pchPrefix = XMLString::transcode(prefix);
	char* pchUri = XMLString::transcode(uri);
    m_NsStack[pchPrefix] = pchUri;
	/* Store only if interested in prefix mappings */
	if (m_bGetPrefixMappings)
	{
		m_CurrPrefixMappings[pchPrefix] = pchUri;
	}
	else
	{
		XMLString::release(&pchPrefix);
		XMLString::release(&pchUri);
	}
}

void XercesHandler::endPrefixMapping(const XMLCh* const prefix)
{
	/* we are not interested in end prefix mapping events in any case */
    char* pchPrefix = XMLString::transcode(prefix);
    m_NsStack.erase(pchPrefix);
	XMLString::release(&pchPrefix);
}

void XercesHandler::freeElement()
{
    if (m_pCurrElement)
    {
        if (m_bEndElementFollows)
        /* free only attributes list if available. Next time 
		 * the same m_pNextElement is freed.
		 */
        {
            m_bEndElementFollows = false;
            m_pCurrElement->m_type = END_ELEMENT;
			freeAttributes();
            m_pCurrElement->m_pchAttributes[0] = NULL;
        }
        else
        /* free all inner strings */
        {
			if (m_pCurrElement->m_pchNameOrValue)
			{
				XMLString::release(const_cast<char**>(&(m_pCurrElement->
					m_pchNameOrValue)));
				m_pCurrElement->m_pchNameOrValue = 0;
			}
			if (m_pCurrElement->m_pchNamespace)
			{
				XMLString::release(const_cast<char**>(&(m_pCurrElement->
					m_pchNamespace)));
				m_pCurrElement->m_pchNamespace = 0;
			}
			freeAttributes();
            m_pCurrElement = 0;
        }
    }
}

void XercesHandler::freeAttributes()
{
	for (int x=0; m_pCurrElement->m_pchAttributes[x]; x+=3)
	{
		if (m_pCurrElement->m_pchAttributes[x])
		{
			XMLString::release(const_cast<char**>(&(m_pCurrElement->
				m_pchAttributes[x])));
			m_pCurrElement->m_pchAttributes[x] = 0;
			if (m_pCurrElement->m_pchAttributes[x+1])
				XMLString::release(const_cast<char**>(&(m_pCurrElement->
				m_pchAttributes[x+1])));
			if (m_pCurrElement->m_pchAttributes[x+2])
				XMLString::release(const_cast<char**>(&(m_pCurrElement->
				m_pchAttributes[x+2])));
		}
	}
}

AnyElement* XercesHandler::getAnyElement()
{
	if (m_bGetPrefixMappings)
	{
		if (m_CurrPrefixMappings.size() > 0)
		{
			map<const AxisChar*, const AxisChar*>::iterator it = 
				m_CurrPrefixMappings.begin();
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

void XercesHandler::setGetPrefixMappings(bool bValue)
{
	m_bGetPrefixMappings = bValue;
}


void XercesHandler::reset()
{
    m_nStatus = AXIS_SUCCESS;
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
		map<const AxisChar*, const AxisChar*>::iterator it = 
			m_CurrPrefixMappings.begin();
		XMLString::release(const_cast<char**>(&((*it).first)));
		XMLString::release(const_cast<char**>(&((*it).second)));
		m_CurrPrefixMappings.erase(it);
	}
}


