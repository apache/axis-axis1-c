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

#if !defined(__XMLPARSERXERCES_H_OF_AXIS_INCLUDED__)
#define __XMLPARSERXERCES_H_OF_AXIS_INCLUDED__

#include "../QName.h"
#include "../Event.h"
#include "../XMLParser.h"
#include "XercesHandler.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/framework/XMLPScanToken.hpp>
#include "SoapInputSource.h"
#include "../AxisParseException.h"
#include "../../transport/axis3/HTTPTransportException.hpp"

XERCES_CPP_NAMESPACE_USE

class XMLParserXerces: public XMLParser
{

public:
    XMLParserXerces();
    ~XMLParserXerces();

    int setInputStream(AxisIOStream* pInputStream);
    const XML_Ch* getNS4Prefix(const XML_Ch* pcPrefix);
    int getStatus();
    const AnyElement* next(bool bIsCharData=false);//Chinthana:change to accept "all" construct 27/04/2005
    const AnyElement* anyNext();
	const char* peek(); //Chinthana:Add the method to peek head and find the next element 27/04/2005.
    const XML_Ch* getPrefix4NS(const XML_Ch* pcNS);

private:
    SAX2XMLReader* m_pParser;
    XMLPScanToken m_ScanToken;
    XercesHandler m_Xhandler;
    bool m_bFirstParsed;
    SoapInputSource* m_pInputSource;
	bool m_bPeeked;


};

#endif
