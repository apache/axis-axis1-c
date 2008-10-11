/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

#if !defined(_SOAPFAULT_H____OF_AXIS_INCLUDED_)
#define _SOAPFAULT_H____OF_AXIS_INCLUDED_

#include <axis/AxisException.hpp>
#include <axis/ISoapFault.hpp>
#include "../common/Param.h"
#include <axis/SoapEnvVersions.hpp>

#include <string>
#include <map>

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


/**
 *  @class SoapFault
 *  @brief interface for the SoapFault class.
 *
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *  @author damitha kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 */

AXIS_CPP_NAMESPACE_START

class SoapSerializer;
class SoapDeSerializer;

class SoapFault : public ISoapFault  
{
friend class SoapFaultsTestCase;

public:
    SoapFault();

    SoapFault(string m_sFaultcode, string m_sFaultstring, 
        string m_sFaultactor, string m_sDetail);

    bool operator ==(const SoapFault &objSoapFault);

    static SoapFault* getSoapFault(int);

    static void initialize();

    const char* getSoapString();

    int serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion);

    void setDeSerializer(SoapDeSerializer* pDZ);

    virtual ~SoapFault();

    int setFaultDetail(const AxisChar* sDetail);

    int setFaultDetail(const Param* pFaultDetail);

    int setFaultactor(const AxisChar* sFaultactor);

    int setFaultstring(const AxisChar* sFaultstring);

    int setFaultcode(const AxisChar* sFaultcode);

    const AxisChar* getFaultcode();

    const AxisChar* getFaultstring();

    const AxisChar* getFaultactor();

    const AxisChar* getSimpleFaultDetail();
    
    const AxisChar* getCmplxFaultObjectName();
 
    void* getCmplxFaultObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, 
        const AxisChar* pName, const AxisChar* pNamespace);

    const void* getCmplxFaultObject();

    int setCmplxFaultObjectName(const string& sCmplxFaultObjectName);

    int setCmplxFaultObject(const void* pCmplxFaultObject);

    void setURI(const AxisChar* uri);

    void setLocalName(const AxisChar* localname);

    void setPrefix(const AxisChar* prefix);

    int setParam(Param* pParam, const AxisChar* pchName, const void* pValue, XSDTYPE type);

private:
    string m_sFaultDetail;
    string m_sFaultactor;
    string m_sFaultstring;
    string m_sFaultcode;
    string m_sCmplxFaultObjectName;
    const void* m_pCmplxFaultObject;
    Param* m_pFaultcodeParam;
    Param* m_pFaultstringParam;
    Param* m_pFaultactorParam;
    Param* m_pFaultDetail;
    AxisString m_strPrefix;
    AxisString m_strLocalname;
    AxisString m_strUri;
    SoapDeSerializer* m_pDZ;
    bool m_bIsSimpleDetail;
    static volatile bool m_bInit;
};

AXIS_CPP_NAMESPACE_END

#endif 

