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

#if !defined(_SOAPFAULT_H____OF_AXIS_INCLUDED_)
#define _SOAPFAULT_H____OF_AXIS_INCLUDED_

#include <string>
#include <map>
#include "SoapFaults.h"

class SoapSerializer;

using namespace std;
/*
 *  @class SoapFault
 *  @brief interface for the SoapFault class.
 *
 *
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 */
class SoapFault  
{
friend class SoapFaultsTestCase;

public:
    SoapFault(string m_sFaultcode, string m_sFaultstring, 
        string m_sFaultactor, string m_sDetail);
    bool operator ==(const SoapFault &objSoapFault);
    static SoapFault* getSoapFault(int);
    static void initialize();
    const char* getSoapString();    
    int serialize(SoapSerializer& pSZ);    
    /* int serialize(string&); */
    virtual ~SoapFault();
private:
    SoapFault();
    /* string m_sFaultSerialized; */
    string m_sDetail;
    string m_sFaultactor;
    string m_sFaultstring;
    string m_sFaultcode;
    static map<int, SoapFaultStruct> m_sFaultMap;
    static volatile bool m_bInit;
    /* int setDetail(const string& sDetail); */
    /* int setFaultactor(const string& sFaultactor); */
    /* int setFaultstring(const string& sFaultstring); */
    /* int setFaultcode(const string& sFaultcode); */
};

#endif 


