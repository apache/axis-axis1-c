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
#pragma warning (disable : 4786)
#endif

#if !defined(AXIS_URIMAPPING_H__OF_AXIS_INCLUDED_)
#define AXIS_URIMAPPING_H__OF_AXIS_INCLUDED_

enum URITYPE { URI_XSI, URI_XSD, URI_ENC, URI_ENVELOPE, URI_UNKNOWN};
#include <map>
#include <string>
#include <axis/server/GDefine.hpp>

AXIS_CPP_NAMESPACE_START

using namespace std;

/*
 * @class URIMapping
 * @brief interface for the URIMapping class.
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 */

class URIMapping  
{
public:
    static void initialize();
    static map<AxisXMLString, URITYPE> m_sURIMap;
    static volatile bool m_bInit;
    URIMapping();
    virtual ~URIMapping();
    static URITYPE getURI(const AxisXMLCh* uri);
};

AXIS_CPP_NAMESPACE_END

#endif
