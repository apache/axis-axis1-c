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

#ifdef WIN32
#pragma warning(disable : 4786)
#endif

#if !defined(__WSDDDOCUMENTEXPAT_H_OF_AXIS_INCLUDED__)
#define __WSDDDOCUMENTEXPAT_H_OF_AXIS_INCLUDED__

#include "WSDDDocument.h"
#include <expat/expat.h>
#include <string>
#include <map>

using namespace std;

/*
 *  @class WSDDDocumentExpat
 *  @brief
 *  @author sanjaya sinharage(sanjaya@opensource.lk)
 *  @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 */
class WSDDDocumentExpat : public WSDDDocument
{
private:
    void processAttributes(WSDDLevels ElementType, const XML_Ch **attrs);
    void getParameters(WSDDLevels ElementType, const XML_Ch **attrs);
    void addAllowedRolesToService(const AxisXMLCh* value);
    void addAllowedMethodsToService(const AxisXMLCh* value);
    int parseDocument(const AxisChar* sWSDD);

public:
    WSDDDocumentExpat(map<AxisString, int>* pLibNameIdMap);
    ~WSDDDocumentExpat();
    int getDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment);
    int updateDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment);

    void startElement(const XML_Ch *qname,const XML_Ch **attrs);
    void endElement(const XML_Ch *qname);
    void characters(const XML_Ch *chars,int length);
    void startPrefixMapping(const XML_Ch *prefix, const XML_Ch *uri);
    void endPrefixMapping(const XML_Ch *prefix);

    inline static void XMLCALL s_startElement(void* p, const XML_Ch *qname,
        const XML_Ch **attrs)
    {((WSDDDocumentExpat*)p)->startElement(qname,attrs);};
    inline static void XMLCALL s_endElement(void* p, const XML_Ch *qname)
    {((WSDDDocumentExpat*)p)->endElement(qname);};
    inline static void XMLCALL s_characters(void* p, const XML_Ch *chars,
        int length)
    {((WSDDDocumentExpat*)p)->characters(chars,length);};
    inline static void XMLCALL s_startPrefixMapping(void* p, 
        const XML_Ch *prefix, const XML_Ch *uri)
    {((WSDDDocumentExpat*)p)->startPrefixMapping(prefix, uri);};
    inline static void XMLCALL s_endPrefixMapping(void* p, 
        const XML_Ch *prefix)
    {((WSDDDocumentExpat*)p)->endPrefixMapping(prefix);};
};

#endif
 