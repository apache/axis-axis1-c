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
 */


#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4101)
#endif

#include "../../platforms/PlatformAutoSense.hpp"

#include "XMLParserXerces.h"
#include <xercesc/sax2/XMLReaderFactory.hpp>

XERCES_CPP_NAMESPACE_USE

XMLParserXerces::XMLParserXerces()
{
    m_bFirstParsed = false;
    m_bPeeked = false;
    m_pParser = XMLReaderFactory::createXMLReader();
    m_pInputSource = NULL;
    m_bCanParseMore = false;
}

XMLParserXerces::~XMLParserXerces()
{
    // Parser has memory allocated with the last AnyElement parsed; clean that
    m_Xhandler.freeElement();

    if(m_pInputSource)
        delete m_pInputSource;
    delete m_pParser;
    
}

int XMLParserXerces::setInputStream(AxisIOStream* pInputStream)
{
    m_pInputStream = pInputStream;
    
    // check if memory is already allocated for is
    if(m_pInputSource)
        delete m_pInputSource;
    
    m_pInputSource = new SoapInputSource(pInputStream);
    m_Xhandler.reset();
    m_pParser->setContentHandler(&m_Xhandler);
    if (m_bFirstParsed)
        m_pParser->parseReset(m_ScanToken);

    m_bFirstParsed = false;
    m_bPeeked = false;
    m_bCanParseMore = false;
    
    return AXIS_SUCCESS;
}

const XML_Ch* XMLParserXerces::getNS4Prefix(const XML_Ch* prefix)
{
    return m_Xhandler.ns4Prefix(prefix);
}

int XMLParserXerces::getStatus()
{
    return m_Xhandler.getStatus();
}

const AnyElement* XMLParserXerces::next(bool isCharData)
{
    if( !m_bFirstParsed)
    {
//    Try this again at some point in the future.  At the moment it works on
//    Windows, but Linux has a problem...will keep for OS/400
#ifndef __OS400__           
        m_bCanParseMore = m_pParser->parseFirst( *m_pInputSource, m_ScanToken);
#else
        try
        {
            m_bCanParseMore = m_pParser->parseFirst( *m_pInputSource, m_ScanToken);
        }
        catch( const XMLException& toCatch)
        {
            char *    message = XMLString::transcode( toCatch.getMessage());

            // Clone the error message before deleting it.
            char *    pErrorMsg = new char[strlen( message ) + 1];
            strcpy( pErrorMsg, message);
            XMLString::release( &message);

            throw AxisParseException( CLIENT_SOAP_CONTENT_NOT_SOAP, pErrorMsg);
        }
        catch( const SAXParseException& toCatch)
        {
            char *    message = XMLString::transcode( toCatch.getMessage());

            // Clone the error message before deleting it.
            char *    pErrorMsg = new char[strlen( message ) + 1];
            strcpy( pErrorMsg, message);
            XMLString::release( &message);

            throw AxisParseException( CLIENT_SOAP_CONTENT_NOT_SOAP, pErrorMsg);
        }
        catch( HTTPTransportException & e)
        {
            throw;
        }
        catch( ...)
        {
            char *pErrorMsg = "Unexpected Exception in SAX parser.  Probably no message or the message is not recognised as XML.";
            
            throw AxisParseException( CLIENT_SOAP_CONTENT_NOT_SOAP, pErrorMsg);
        }
#endif
        m_bFirstParsed = true;
    }

    if(!m_bPeeked) 
        m_Xhandler.freeElement();
    
    AnyElement* elem;
    while (m_bCanParseMore && AXIS_FAIL != m_Xhandler.getStatus())
    {
        // See if we have a token to consume
        elem = m_Xhandler.getAnyElement();
        
        // Since we have consumed whatever is there, ensure peek flag is set to false
        m_bPeeked = false;
        
        // If we do not have an element, then parse next token; else if
        // whitespace, ignore whitespace; else return token
        if (!elem)
            m_bCanParseMore = m_pParser->parseNext(m_ScanToken);
        else if (!isCharData && (CHARACTER_ELEMENT == elem->m_type))
            m_Xhandler.freeElement();
        else
            return elem;
    }
    
    return NULL;
}
// New method which peek a head next element 
// Here always Peek() will call after the first pase done
const char* XMLParserXerces::peek()
{
    if (!m_bPeeked)
    {
        if(!m_bFirstParsed)
        {
            m_bCanParseMore = m_pParser->parseFirst(*m_pInputSource, m_ScanToken);
            m_bFirstParsed = true;
        }
        
        m_Xhandler.freeElement();
        
        AnyElement* elem;
        while (m_bCanParseMore && AXIS_FAIL != m_Xhandler.getStatus())
        {
            // Attempt to get token
            m_bCanParseMore = m_pParser->parseNext(m_ScanToken);                            
            elem = m_Xhandler.getAnyElement();
            
            // we never peek for char data hence this is a white space - ignore it.
            if (m_bCanParseMore && elem && CHARACTER_ELEMENT == elem->m_type)
                m_Xhandler.freeElement();
            else
                break;
         }
    }

    m_bPeeked = true;
    
    const XML_NODE_TYPE type = m_Xhandler.peekNextElementType();
    if(type != END_ELEMENT && type != END_PREFIX && type != UNKNOWN)
    {
        const char* name = m_Xhandler.peekNextElementName();
        return name;
    }
    else
        return "";
}

const AnyElement* XMLParserXerces::anyNext()
{
    // Say the SAX event handler to record prefix mappings too 
    // By default the event handler do not record them.
    m_Xhandler.setGetPrefixMappings(true);
    if(!m_bFirstParsed)
    {
        m_bCanParseMore = m_pParser->parseFirst(*m_pInputSource, m_ScanToken);
        m_bFirstParsed = true;
    }

    if(!m_bPeeked) 
        m_Xhandler.freeElement();

    AnyElement* elem;
    while (m_bCanParseMore && AXIS_FAIL != m_Xhandler.getStatus())
    {
        // See if we have a token to consume
        elem = m_Xhandler.getAnyElement();
        
        // Since we have consumed whatever is there, ensure peek flag is set to false
        m_bPeeked = false;
        
        // If we do not have an element, then parse next token;  
        // else return token
        if (!elem)
            m_bCanParseMore = m_pParser->parseNext(m_ScanToken);
        else
        {
            m_Xhandler.setGetPrefixMappings(false);
            return elem;
        }
    }
    
    return NULL;
}

const XML_Ch* XMLParserXerces::getPrefix4NS(const XML_Ch* pcNS)
{
    return m_Xhandler.prefix4NS(pcNS);
}
