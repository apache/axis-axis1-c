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

#if !defined(__XMLPARSEREXPAT_H_OF_AXIS_INCLUDED__)
#define __XMLPARSEREXPAT_H_OF_AXIS_INCLUDED__
#ifdef WIN32
#include <expat/expat.h>
#else
#include <expat.h>
#endif
//#include <axis/server/Packet.hpp>

#include "../QName.h"
#include "../AnyElement.h"
#include "../Event.h"
#include "../XMLParser.h"
#include "../AxisParseException.h"

#include <queue>
#include <map>
#include <string>

using namespace std;

class XMLParserExpat: public XMLParser
{
public:
    XMLParserExpat();
    ~XMLParserExpat();
    int setInputStream(AxisIOStream* pInputStream);
    const XML_Ch* getNS4Prefix(const XML_Ch* prefix);
    int getStatus();
    const AnyElement* next(bool isCharData=false);
    const AnyElement* anyNext();
    const XML_Ch* getPrefix4NS(const XML_Ch* pcNS);

private:
    XML_Parser m_Parser;
    char* m_pCurrentBuffer;
    Event* m_pLastEvent;
    AnyElement m_Element;
    queue<Event*> m_Events;
    map<AxisXMLString, AxisXMLString> m_NsStack;
    int m_nStatus;
    void startElement(const XML_Ch *qname,const XML_Ch **attrs);
    void endElement(const XML_Ch *qname);
    void characters(const XML_Ch *chars,int length);
    void startPrefixMapping(const XML_Ch *prefix, const XML_Ch *uri);
    void endPrefixMapping(const XML_Ch *prefix);
    int parseNext();

    inline static void XMLCALL s_startElement(void* p, const XML_Ch *qname,
        const XML_Ch **attrs)
    {((XMLParserExpat*)p)->startElement(qname,attrs);};
    inline static void XMLCALL s_endElement(void* p, const XML_Ch *qname)
    {((XMLParserExpat*)p)->endElement(qname);};
    inline static void XMLCALL s_characters(void* p, const XML_Ch *chars,
        int length)
    {((XMLParserExpat*)p)->characters(chars,length);};
    inline static void XMLCALL s_startPrefixMapping(void* p,
        const XML_Ch *prefix, const XML_Ch *uri)
    {((XMLParserExpat*)p)->startPrefixMapping(prefix, uri);};
    inline static void XMLCALL s_endPrefixMapping(void* p,
        const XML_Ch *prefix)
    {((XMLParserExpat*)p)->endPrefixMapping(prefix);};
};

#endif
