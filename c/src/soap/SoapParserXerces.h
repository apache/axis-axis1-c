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

#if !defined(__SoapParserXerces_H_INCLUDED__)
#define __SoapParserXerces_H_INCLUDED__

#include <axis/server/Packet.h>
#include "../xml/QName.h"
#include "../xml/Event.h"
#include <axis/server/AnyElement.h>
#include <axis/server/XMLParser.h>
#include "XercesHandler.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/framework/XMLPScanToken.hpp>
#include "SoapInputSource.h"
/* using namespace std; */
XERCES_CPP_NAMESPACE_USE

class SoapParserXerces: public XMLParser
{

public:
    SoapParserXerces();
    ~SoapParserXerces();

    int SetInputStream(const Ax_soapstream* pInputStream);
    const Ax_soapstream* GetInputStream(){return m_pInputStream;};
    int Init();
    const XML_Ch* GetNS4Prefix(const XML_Ch* prefix);
    int GetStatus();
    const AnyElement* Next(bool isCharData=false);
    AXIS_TRANSPORT_STATUS GetTransportStatus(){ return m_nTransportStatus;};
    void SetTransportStatus(AXIS_TRANSPORT_STATUS nStatus)
    { m_nTransportStatus = nStatus;};


    const Ax_soapstream* m_pInputStream;

private:
    int m_nStatus;
    SAX2XMLReader* m_pParser;
    /* SAXParser* m_pParser; */
    AXIS_TRANSPORT_STATUS m_nTransportStatus;
    XMLPScanToken token;
    XercesHandler Xhandler;
    bool firstParsed;
    SoapInputSource* is;


};

#endif