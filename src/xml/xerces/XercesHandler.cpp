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
 *    @author sanjaya singharage (sanjayas@opensource.lk)
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
    Nelement = (AnyElement*)malloc(sizeof (AnyElement));
    m_bEndElementFollows = false;
}

XercesHandler::~XercesHandler()
{
}

void XercesHandler::startElement(const XMLCh *const uri,const XMLCh *const 
                                 localname,const XMLCh *const qname,
                                 const Attributes &attrs)
{
    m_pCurrElement = Nelement;
    Nelement->m_type = START_ELEMENT;
    Nelement->m_pchNameOrValue = XMLString::transcode(localname);
    Nelement->m_pchNamespace = XMLString::transcode(uri);
    
    unsigned int len = attrs.getLength();
    unsigned int index;
    unsigned int i = 0;
    for (index = 0; index < len*3; index+=3)
    {    
        Nelement->m_pchAttributes[index] = 
            XMLString::transcode(attrs.getLocalName(i));
        Nelement->m_pchAttributes[index+1] = 
            XMLString::transcode(attrs.getURI(i));
        Nelement->m_pchAttributes[index+2] = 
            XMLString::transcode(attrs.getValue(i));
        i++;
    }
    Nelement->m_pchAttributes[len*3]=NULL;
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
    for (map<AxisXMLString, AxisXMLString>::iterator it;
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
    m_pCurrElement = Nelement;
    Nelement->m_type = CHARACTER_ELEMENT;
    Nelement->m_pchNameOrValue = XMLString::transcode(chars);
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
        m_bEndElementFollows = true;
        return;
    }
    m_pCurrElement = Nelement;
    Nelement->m_type = END_ELEMENT;
    Nelement->m_pchNameOrValue = XMLString::transcode(localname);
    Nelement->m_pchNamespace = XMLString::transcode(uri);
    Nelement->m_pchAttributes[0] = NULL;
}

void XercesHandler::startPrefixMapping(const XMLCh* const prefix,
                                       const XMLCh* const uri)
{
    m_pCurrElement = Nelement;
    Nelement->m_type = START_PREFIX;
    Nelement->m_pchNameOrValue = XMLString::transcode(prefix);
    Nelement->m_pchNamespace = XMLString::transcode(uri);
    m_NsStack[XMLString::transcode(prefix)] = XMLString::transcode(uri);
}

void XercesHandler::endPrefixMapping(const XMLCh* const prefix)
{
    m_pCurrElement = Nelement;
    Nelement->m_type = END_PREFIX;
    Nelement->m_pchNameOrValue = XMLString::transcode(prefix);
    m_NsStack.erase(XMLString::transcode(prefix));
}

void XercesHandler::freeElement()
{
    if (m_pCurrElement)
    {
        if (m_bEndElementFollows)
            /* free only attributes list if available */
        {
            m_bEndElementFollows = false;
            Nelement->m_type = END_ELEMENT;
            Nelement->m_pchAttributes[0] = NULL;
        }
        else
            /* free all inner strings */
        {
            m_pCurrElement = 0;
        }
    }
}
