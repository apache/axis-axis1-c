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

#if !defined(AXIS_SOAPKEYWORDMAPPING_H__OF_AXIS_INCLUDED_)
#define AXIS_SOAPKEYWORDMAPPING_H__OF_AXIS_INCLUDED_

#include "../common/AxisUtils.h"
#include <axis/server/SoapEnvVersions.h>
#include <map>

using namespace std;

struct SoapKeywordStruct 
{    
    const AxisXMLCh* pchNamespaceUri;
    const AxisXMLCh* pchPrefix;
    const AxisXMLCh* pchWords[SOAP_WORDS_LAST];
    const Attribute* pEnv;
    const Attribute* pXsi;
    const Attribute* pXsd;
};

/*
 * @class SoapKeywordMapping
 * @brief interface for the SoapKeywordMapping class.
 * @author Susantha Kumara (skumara@virtusa.com)
 */
class SoapKeywordMapping  
{
public:
    SoapKeywordMapping();
    virtual ~SoapKeywordMapping();
private:
    //static map<int, SoapKeywordStruct> m_Map;
    static SoapKeywordStruct m_Map[VERSION_LAST];
    static volatile bool m_bInit;
public:
    static void initialize();
    static const SoapKeywordStruct& map(int nVersion);
    static void uninitialize();
};

#endif
