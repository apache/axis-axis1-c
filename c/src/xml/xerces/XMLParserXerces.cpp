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
#endif

#include "XMLParserXerces.h"
#include <xercesc/sax2/XMLReaderFactory.hpp>

XERCES_CPP_NAMESPACE_USE

XMLParserXerces::XMLParserXerces()
{
    m_bFirstParsed = false;
    m_pParser = XMLReaderFactory::createXMLReader();
    m_pInputSource = NULL;
}

XMLParserXerces::~XMLParserXerces()
{
    if(m_pInputSource)
        delete m_pInputSource;
    delete m_pParser;
    
}

int XMLParserXerces::setInputStream(AxisIOStream* pInputStream)
{
    m_pInputStream = pInputStream;
    //check if memeory is already allocated for is
    if(m_pInputSource)
        delete m_pInputSource;
    
    m_pInputSource = new SoapInputSource(pInputStream);
    /* SoapInputSource is(m_pInputStream->transport.pGetFunct, 
    m_pInputStream->str.ip_stream); */
    m_pParser->setContentHandler(&m_Xhandler);
     if (m_bFirstParsed)
    {
        m_pParser->parseReset(m_ScanToken);
        m_bFirstParsed = false;
    }
   /* return m_pHandler->Success(); */
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
	bool bCanParseMore = false;
    if(!m_bFirstParsed)
    {
        m_pParser->parseFirst(*m_pInputSource, m_ScanToken);
        m_bFirstParsed = true;
    }

    m_Xhandler.freeElement();
    while (true)
    {
        AnyElement* elem = m_Xhandler.getAnyElement();
		if (!elem)
		{
			bCanParseMore = m_pParser->parseNext(m_ScanToken);
			elem = m_Xhandler.getAnyElement();
		}
        if (elem) 
		{
			if (!isCharData && (CHARACTER_ELEMENT == elem->m_type))
			{ /* ignorable white space */
				m_Xhandler.freeElement();
				continue;		
			}			
			return elem;
		}
        else if (AXIS_FAIL == m_Xhandler.getStatus()) return NULL;
		else if (!bCanParseMore) return NULL;
    }
}
