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

#include "URIMapping.h"
#include "../common/AxisUtils.h"

#define __TRC(X) AxisUtils::Convert(X)

map<AxisXMLString, URITYPE> URIMapping::m_sURIMap;
volatile bool URIMapping::m_bInit = false;

URIMapping::URIMapping()
{

}

URIMapping::~URIMapping()
{

}

void URIMapping::initialize()
{
    if (!m_bInit)
    {
        m_sURIMap[__TRC("http://www.w3.org/2001/XMLSchema")] = URI_XSD;
        m_sURIMap[__TRC("http://www.w3.org/2001/XMLSchema-instance")] = 
            URI_XSI;
        m_sURIMap[__TRC("http://www.w3.org/2001/06/soap-encoding")] = URI_ENC;
		m_sURIMap[__TRC("http://schemas.xmlsoap.org/soap/encoding/")] = URI_ENC;
        m_sURIMap[__TRC("http://schemas.xmlsoap.org/soap/envelope/")] = 
            URI_ENVELOPE;
        m_bInit = true;
    }
}

URITYPE URIMapping::map(const AxisXMLCh* uri)
{
    if (m_sURIMap.find(uri) != m_sURIMap.end())
    {
        return m_sURIMap[uri];
    }
    return URI_UNKNOWN;
}
