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

#include "SoapKeywordMapping.h"
#include <axis/server/Attribute.h>
#include "../common/AxisUtils.h"

map<int, SoapKeywordStruct> SoapKeywordMapping::m_Map;
volatile bool SoapKeywordMapping::m_bInit = false;

#define __TRC(X) AxisUtils::ToAxisXMLCh(X)

SoapKeywordMapping::SoapKeywordMapping()
{

}

SoapKeywordMapping::~SoapKeywordMapping()
{

}

void SoapKeywordMapping::Initialize()
{
    if (!m_bInit)
    {
        for (int sv = SOAP_VER_1_1; sv < VERSION_LAST; sv++)
        {
            m_Map[sv].pchNamespaceUri = 
                __TRC(gs_SoapEnvVersionsStruct[sv].pchNamespaceUri);
            m_Map[sv].pchPrefix = 
                __TRC(gs_SoapEnvVersionsStruct[sv].pchPrefix);
            for (int sw = SKW_ENVELOPE; sw < SOAP_WORDS_LAST; sw++)
            {
                m_Map[sv].pchWords[sw] = 
                    __TRC(gs_SoapEnvVersionsStruct[sv].pchWords[sw]);
            }
        }
        /* soap 1.1 envelop attributes */
        m_Map[SOAP_VER_1_1].pEnv = new Attribute("SOAP-ENV","xmlns","",
            "http://schemas.xmlsoap.org/soap/envelope/");
        m_Map[SOAP_VER_1_1].pXsi = new Attribute("xsi","xmlns","",
            "http://www.w3.org/2001/XMLSchema-instance");
        m_Map[SOAP_VER_1_1].pXsd = new Attribute("xsd","xmlns","",
            "http://www.w3.org/2001/XMLSchema");
        /* soap 1.2 envelop attributes */
        m_Map[SOAP_VER_1_2].pEnv = new Attribute("env","xmlns","",
            "http://www.w3.org/2003/05/soap-envelope");
        m_Map[SOAP_VER_1_2].pXsi = new Attribute("xsi","xmlns","",
            "http://www.w3.org/2001/XMLSchema-instance");
        m_Map[SOAP_VER_1_2].pXsd = new Attribute("xsd","xmlns","",
            "http://www.w3.org/2001/XMLSchema");
        m_bInit = true;
    }
}

const SoapKeywordStruct& SoapKeywordMapping::Map(int nVersion)
{
    return m_Map[nVersion];
}
