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

#include "SoapParserXerces.h"
#include <xercesc/sax2/XMLReaderFactory.hpp>

SoapParserXerces::SoapParserXerces()
{
    m_nStatus = NULL;
    firstParsed = false;
    m_pParser = XMLReaderFactory::createXMLReader();

}

SoapParserXerces::~SoapParserXerces()
{
    m_nStatus = NULL;
}

int SoapParserXerces::setInputStream(const Ax_soapstream* pInputStream)
{
    m_pInputStream = pInputStream;
    is = new SoapInputSource(m_pInputStream->transport.pGetFunct,
        m_pInputStream);
    /* SoapInputSource is(m_pInputStream->transport.pGetFunct, 
    m_pInputStream->str.ip_stream); */
    m_pParser->setContentHandler(&Xhandler);
    /* return m_pHandler->Success(); */
    return AXIS_SUCCESS;
}

int SoapParserXerces::init()
{
    if (firstParsed)
    {
        m_pParser->parseReset(token);
        firstParsed = false;
    }
    return 0;
}

const XML_Ch* SoapParserXerces::getNS4Prefix(const XML_Ch* prefix)
{
    return Xhandler.NS4Prefix(prefix);
}

int SoapParserXerces::getStatus()
{
    m_nStatus = AXIS_SUCCESS; /*TODO:Check if an error occured in expat */
    return m_nStatus;
}

const AnyElement* SoapParserXerces::next(bool isCharData)
{

    if(!firstParsed)
    {
        m_pParser->parseFirst(*is, token);
        firstParsed = true;
    }

    Xhandler.freeElement();
    while (true)
    {
        m_pParser->parseNext(token);
        AnyElement* elem = Xhandler.getAnyElement();
        if (elem) 
		{
			if (!isCharData && (CHARACTER_ELEMENT == elem->m_type))
			{ /* ignorable white space */
				Xhandler.freeElement();
				continue;		
			}			
			return elem;
		}
        else if (AXIS_FAIL == Xhandler.GetStatus()) return NULL; 
    }
}
