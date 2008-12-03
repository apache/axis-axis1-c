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

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include <string>
#include "XMLParserXerces.h"
#include "../AxisParseException.h"
#include "../../transport/axis3/HTTPTransportException.hpp"

#include <xercesc/sax2/XMLReaderFactory.hpp>

#include "../../common/AxisTrace.h"

XERCES_CPP_NAMESPACE_USE
using namespace std;

XMLParserXerces::
XMLParserXerces() : XMLParser()
{
    logEntryParser("XMLParserXerces::XMLParserXerces")

    m_pInputSource = NULL;
    m_bFirstParsed = false;
    m_bPeeked = false;
    m_bStartEndElement = false;
    m_pParser = XMLReaderFactory::createXMLReader();
    m_pParser->setErrorHandler(&m_Xhandler);
    
    logExit()
}

XMLParserXerces::
~XMLParserXerces()
{
    logEntryParser("XMLParserXerces::~XMLParserXerces")

    // Parser has memory allocated with the last AnyElement parsed; clean that
    m_Xhandler.freeElement();

    delete m_pInputSource;
    delete m_pParser;
    
    logExit()
}

int XMLParserXerces::
setInputStream(AxisIOStream* pInputStream)
{
    logEntryParser("XMLParserXerces::setInputStream")

    m_pInputStream = pInputStream;
    
    delete m_pInputSource;
    m_pInputSource = new SoapInputSource(pInputStream);
    m_Xhandler.reset();
    m_pParser->setContentHandler(&m_Xhandler);
    if (m_bFirstParsed)
        m_pParser->parseReset(m_ScanToken);

    m_bFirstParsed = false;
    m_bPeeked = false;
    m_bCanParseMore = true;
    m_iStatus = AXIS_SUCCESS;
    m_sErrorString = "";
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

const XML_Ch* XMLParserXerces::
getNS4Prefix(const XML_Ch* prefix)
{
    return m_Xhandler.ns4Prefix(prefix);
}

const AnyElement* XMLParserXerces::
parse(bool ignoreWhitespace, bool peekIt)
{
    logEntryParser("XMLParserXerces::parse")

    try 
    {
        // Need to do a parseFirst() to kick off parsing
        if (!m_bFirstParsed) 
        {
            // if exception is thrown on parseFirst()
            m_bCanParseMore = false;
             
            m_bCanParseMore = m_pParser->parseFirst( *m_pInputSource, m_ScanToken);
            
            m_bFirstParsed = true;
            if (!m_bCanParseMore)
            {
                logExitWithPointer(NULL)

                return (const AnyElement*)NULL;
            }
        }

        // release any element that has been consumed
        if(!m_bPeeked) 
            m_Xhandler.freeElement();
       
        // Get element
        AnyElement* elem = m_Xhandler.getAnyElement();
        
        // Since we consumed element set peek to false
        m_bPeeked = false;

        // set flag to false since we are going to read next node
        if (!peekIt)
            m_bStartEndElement = false;          

        // If element not obtained and no previous parsing error?
        if (!elem && m_bCanParseMore)
        {   
            // get next token, possibly ignoring whitespace
            while (m_bCanParseMore && m_iStatus == AXIS_SUCCESS)
            {            
                // if exception is thrown on parseNext()
                m_bCanParseMore = false; 
            
                // parse next token
                m_bCanParseMore = m_pParser->parseNext(m_ScanToken);
                
                // if we cannot parse anymore, break out!
                if (!m_bCanParseMore)
                    break;
                
                // Get parsed element
                elem = m_Xhandler.getAnyElement();
                if (!elem)
                    continue;   
                                 
                // Ignore whitespace?
                if (ignoreWhitespace && (CHARACTER_ELEMENT == elem->m_type))
                {
                    elem = NULL;
                    m_Xhandler.freeElement();
                }
                else
                    break;
            }          
        }
        
        // Set some state flags
        if (elem)
        {
            // Keep track of when we give back a start-end element in order to ensure
            // that peek() - which is used to determine optional elements or elements 
            // that are not in order (e.g. xsd:all support) - returns a null string 
            if (!peekIt && elem->m_type == START_ELEMENT && elem->m_type2 == START_END_ELEMENT)
               m_bStartEndElement = true;          
            
            // Set peek flag if we are doing a peek
            if (peekIt)
                m_bPeeked = true;
        }
        
        // Return element
        logExitWithPointer(elem)

        return (const AnyElement*)elem;
    } 
    catch( const SAXParseException& e) 
    {
        char *message = XMLString::transcode( e.getMessage());
        m_sErrorString = message;
        m_iErrorCode = SERVER_PARSE_PARSER_FAILED;
        m_iStatus = AXIS_FAIL;
        XMLString::release( &message);
        
        logThrowExceptionWithData("AxisParseException", m_sErrorString.c_str())
        
        throw AxisParseException(m_iErrorCode, m_sErrorString.c_str());
    } 
    catch( const XMLException& e)
    {
        char *message = XMLString::transcode( e.getMessage());
        m_sErrorString = message;
        m_iErrorCode = SERVER_PARSE_PARSER_FAILED;
        m_iStatus = AXIS_FAIL;
        XMLString::release( &message);
        
        logThrowExceptionWithData("AxisParseException", m_sErrorString.c_str())

        throw AxisParseException(m_iErrorCode, m_sErrorString.c_str());        
    }    
    catch( HTTPTransportException & e)
    {
        m_sErrorString = e.what();
        m_iErrorCode = SERVER_PARSE_TRANSPORT_FAILED;
        m_iStatus = AXIS_FAIL;
        
        logThrowExceptionWithData("AxisParseException", m_sErrorString.c_str())

        throw AxisParseException(m_iErrorCode, m_sErrorString.c_str());        
    }    
    catch(...) 
    {
        m_sErrorString = "Unexpected exception in parser.";
        m_iErrorCode = SERVER_PARSE_PARSER_FAILED;
        m_iStatus = AXIS_FAIL;
        
        logThrowExceptionWithData("AxisParseException", m_sErrorString.c_str())

        throw AxisParseException(m_iErrorCode, m_sErrorString.c_str());         
    }
    
    logExitWithPointer(NULL)

    return (const AnyElement*)NULL;
}

const AnyElement* XMLParserXerces::
next(bool isCharData)
{    
    logEntryParser("XMLParserXerces::next")

    const AnyElement* returnValue = parse(isCharData ? false : true);
    
    logExitWithPointer(returnValue)

    return returnValue;
}

// New method which peek a head next element 
// Here always Peek() will call after the first pase done
const char* XMLParserXerces::
peek()
{   
    logEntryParser("XMLParserXerces::peek")

    const char* returnValue = "";

    // peek() is used to determine optional elements or elements 
    // that are not in order (e.g. xsd:all support) - return a null string if 
    // the last node processed was a start/end element
    if (!m_bStartEndElement)
    {
        // get element, ignoring whitespace and indicating this is a peek operation   
        const AnyElement* elem = parse(true, true);
        if (elem)
        {
            // We return null string if end-element or unknown type is encountered
            const XML_NODE_TYPE type = m_Xhandler.peekNextElementType();
            if(type != END_ELEMENT && type != END_PREFIX && type != UNKNOWN)
                returnValue = m_Xhandler.peekNextElementName();
        }
    }
    
    logExitWithString(returnValue)

    return returnValue;
}

const AnyElement* XMLParserXerces::
anyNext()
{
    logEntryParser("XMLParserXerces::anyNext")

    // Say the SAX event handler to record prefix mappings too 
    // By default the event handler do not record them.
    m_Xhandler.setGetPrefixMappings(true);
    
    // get element, ensuring that whitespace is not ignored
    const AnyElement* elem = parse(false);
    
    // Reset prefix mapping
    m_Xhandler.setGetPrefixMappings(false);
    
    logExitWithPointer(elem)

    return elem;
}

const XML_Ch* XMLParserXerces::
getPrefix4NS(const XML_Ch* pcNS)
{
    return m_Xhandler.prefix4NS(pcNS);
}

void XMLParserXerces::
enableTrace(const char* logFilePath, const char *filters)
{
    AxisTrace::setLogFilter(filters);
    AxisTrace::startTrace(logFilePath, false);
}