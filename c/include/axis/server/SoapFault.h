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
#include "AxisException.h"

class SoapSerializer;

using namespace std;
    
/**
 *    The structure which is used as a container for soap faults.
 */
typedef struct
{
    const char* pcFaultcode;
    const char* pcFaultstring;    
    const char* pcFaultactor;
    const char* pcFaultDetail;
} SoapFaultStruct;

/*
 * This array of structure is used to store all the soap faults
 * which are used in Axis C++. Each time a fault object is needed it is
 * created using this array, in SoapFault class.
 */
static SoapFaultStruct s_arrSoapFaultStruct[FAULT_LAST];

/**
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
    //void setSoapFaultactor(string sFaultactor);
    //void setSoapDetail(string sFaultDetail);
    /* int serialize(string&); */
    virtual ~SoapFault();
    void setFaultDetail(const string& sDetail);
    void setFaultactor(const string& sFaultactor);
    string getFaultcode();
    string getFaultstring();
    string getFaultactor();
    string getFaultDetail();
    /*void setFaultstring(const string& sFaultstring);*/
    /*void setFaultcode(const string& sFaultcode);*/ 

private:
    SoapFault();
    /* string m_sFaultSerialized; */
    string m_sFaultDetail;
    string m_sFaultactor;
    string m_sFaultstring;
    string m_sFaultcode;
    static map<int, SoapFaultStruct> m_sFaultMap;
    static volatile bool m_bInit;
};

#endif 

