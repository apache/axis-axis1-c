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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__SoapParserExpat_H_OF_AXIS_INCLUDED__)
#define __SoapParserExpat_H_OF_AXIS_INCLUDED__

#include <expat/expat.h>
#include <axis/server/Packet.h>

#include "../xml/QName.h"
#include <axis/server/AnyElement.h>
#include "../xml/Event.h"
#include <axis/server/XMLParser.h>

#include <queue>
#include <map>
#include <string>

using namespace std;

class SoapParserExpat: public XMLParser
{
private:
    XML_Parser m_Parser;
    const Ax_soapstream* m_pInputStream;
    const char* m_pCurrentBuffer;
    Event* m_pLastEvent;
    AnyElement m_Element;
    queue<Event*> m_Events;
    map<AxisXMLString, AxisXMLString> m_NsStack;
    int m_nStatus;
    AXIS_TRANSPORT_STATUS m_nTransportStatus;
public:
    SoapParserExpat();
    ~SoapParserExpat();
private:
    void startElement(const XML_Ch *qname,const XML_Ch **attrs);
    void endElement(const XML_Ch *qname);
    void characters(const XML_Ch *chars,int length);
    void startPrefixMapping(const XML_Ch *prefix, const XML_Ch *uri);
    void endPrefixMapping(const XML_Ch *prefix);
    int parseNext();

    inline static void XMLCALL s_startElement(void* p, const XML_Ch *qname,
        const XML_Ch **attrs)
    {((SoapParserExpat*)p)->startElement(qname,attrs);};
    inline static void XMLCALL s_endElement(void* p, const XML_Ch *qname)
    {((SoapParserExpat*)p)->endElement(qname);};
    inline static void XMLCALL s_characters(void* p, const XML_Ch *chars,
        int length)
    {((SoapParserExpat*)p)->characters(chars,length);};
    inline static void XMLCALL s_startPrefixMapping(void* p,
        const XML_Ch *prefix, const XML_Ch *uri)
    {((SoapParserExpat*)p)->startPrefixMapping(prefix, uri);};
    inline static void XMLCALL s_endPrefixMapping(void* p,
        const XML_Ch *prefix)
    {((SoapParserExpat*)p)->endPrefixMapping(prefix);};

public:
    int setInputStream(const Ax_soapstream* pInputStream);
    const Ax_soapstream* getInputStream(){return m_pInputStream;};
    int init();
    const XML_Ch* getNS4Prefix(const XML_Ch* prefix);
    int getStatus();
    const AnyElement* next(bool isCharData=false);
    AXIS_TRANSPORT_STATUS getTransportStatus(){ return m_nTransportStatus;};
    void setTransportStatus(AXIS_TRANSPORT_STATUS nStatus)
    { m_nTransportStatus = nStatus;};
};

#endif
