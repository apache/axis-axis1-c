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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 */

#include <axis/server/SoapFault.h>
#include <axis/server/SoapSerializer.h>
#include <axis/server/SoapEnvVersions.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

map<int, SoapFaultStruct> SoapFault::m_sFaultMap;
volatile bool SoapFault::m_bInit = false;

SoapFault::SoapFault()
{

}

SoapFault::~SoapFault()
{

}

/*int SoapFault::setFaultcode(const string& sFaultcode)
{
    m_sFaultcode= sFaultcode;

    return AXIS_SUCCESS;
}*/

/*int SoapFault::setFaultstring(const string& sFaultstring)
{
    m_sFaultstring= sFaultstring;

    return AXIS_SUCCESS;
}*/

/*int SoapFault::setFaultactor(const string& sFaultactor)
{
    m_sFaultactor= sFaultactor;

    return AXIS_SUCCESS;
}*/

/*int SoapFault::setDetail(const string& sDetail)
{
    m_sDetail= sDetail;

    return AXIS_SUCCESS;
}*/

int SoapFault::serialize(SoapSerializer& pSZ)
{
    /* written according to SOAP Version 1.1 */

    int iStatus= AXIS_SUCCESS;
        
    pSZ.serialize("<SOAP-ENV:Fault>", NULL);    
    pSZ.serialize("<faultcode>", m_sFaultcode.c_str(), "</faultcode>", NULL);
    pSZ.serialize("<faultstring>", m_sFaultstring.c_str(), "</faultstring>", NULL);

    if(!m_sFaultactor.empty())
    {        
        pSZ.serialize("<faultactor>", m_sFaultactor.c_str(), "</faultactor>", NULL);
    }

    if(!m_sFaultDetail.empty())
    {        
        pSZ.serialize("<detail>", m_sFaultDetail.c_str(), "</detail>", NULL);
    }
    
    pSZ.serialize("</SOAP-ENV:Fault>", NULL);

    return iStatus;
}

/*
comm on 11/7/2003 at 9.30am
int SoapFault::serialize(string& sSerialized)
{
    // written according to SOAP Version 1.1

    int iStatus= AXIS_SUCCESS;
    
    sSerialized= sSerialized+ "<SOAP-ENV:Fault>" + "\n";
    sSerialized= sSerialized+ "<faultcode>"+ m_sFaultcode+ "</faultcode>"+ "\n";
    sSerialized= sSerialized+ "<faultstring>"+m_sFaultstring+"</faultstring>"+ "\n";

    if(!m_sFaultactor.empty()) {
        sSerialized= sSerialized+ "<faultactor>"+ m_sFaultactor +"</faultactor>"+ "\n";
    }

    if(!m_sDetail.empty()) {
        sSerialized= sSerialized+ "<detail>"+ m_sDetail +"</detail>"+ "\n";
    }

    sSerialized= sSerialized+ "</SOAP-ENV:Fault>" + "\n";

    return iStatus;
}
*/

void SoapFault::initialize()
{
    if (!m_bInit)
    {
        /*VersionMismatch faults */
        s_arrSoapFaultStruct[SF_VERSION_MISMATCH] = (SoapFaultStruct) 
            {"VersionMismatch", "Soap Version Mismatch error", "", ""};
        /*MustUnderstand faults */
        s_arrSoapFaultStruct[SF_MUST_UNDERSTAND] = (SoapFaultStruct) 
            {"MustUnderstand", "Soap Must Understand  error", "", ""};
        /*Client faults */
        s_arrSoapFaultStruct[SF_MESSAGEINCOMPLETE] = (SoapFaultStruct) 
            {"Client", "Soap message is incorrect or incomplete", "", ""};
        s_arrSoapFaultStruct[SF_SOAPACTIONEMPTY] = (SoapFaultStruct)
            {"Client", "Soap Action header empty", "", ""};
        s_arrSoapFaultStruct[SF_SERVICENOTFOUND] = (SoapFaultStruct)
            {"Client", "Requested service is not registerd at the server", "", ""};
        s_arrSoapFaultStruct[SF_SOAPCONTENTERROR] = (SoapFaultStruct)
            {"Client", "Soap content is not valid", "", ""};
        s_arrSoapFaultStruct[SF_NOSOAPMETHOD] = (SoapFaultStruct)
            {"Client", "No method to invoke", "", ""};
        s_arrSoapFaultStruct[SF_METHODNOTALLOWED] = (SoapFaultStruct)
            {"Client", "Soap method is not allowed to invoke", "", ""};
        s_arrSoapFaultStruct[SF_PARATYPEMISMATCH] = (SoapFaultStruct)
            {"Client", "Parameter type mismatch", "", ""};
        s_arrSoapFaultStruct[SF_CLIENTHANDLERFAILED] = (SoapFaultStruct)
            {"Client", "A client handler failed", "", ""};

        /*Server faults */
        s_arrSoapFaultStruct[SF_COULDNOTLOADSRV] = (SoapFaultStruct)
            {"Server", "Cannot load web service", "", ""};
        s_arrSoapFaultStruct[SF_COULDNOTLOADHDL] = (SoapFaultStruct)
            {"Server", "Cannot load service handlers", "", ""};
        s_arrSoapFaultStruct[SF_HANDLERFAILED] = (SoapFaultStruct)
            {"Server", "A service handler failed", "", ""};
        s_arrSoapFaultStruct[SF_WEBSERVICEFAILED] = (SoapFaultStruct)
            {"Server", "Webservice failed", "", ""};
        s_arrSoapFaultStruct[AXISC_TRANSPORT_CONF_ERROR] = (SoapFaultStruct)
            {"Server", "Transport configuration error", "", ""};
        s_arrSoapFaultStruct[HANDLER_INIT_FAIL] = (SoapFaultStruct)
            {"Server", "Handler initialization failed", "", ""};
        s_arrSoapFaultStruct[HANDLER_CREATION_FAILED] = (SoapFaultStruct)
            {"Server", "Handler creation failed", "", ""};
        s_arrSoapFaultStruct[LOADLIBRARY_FAILED] = (SoapFaultStruct)
            {"Server", "Library loading failed", "", ""};
        s_arrSoapFaultStruct[LIBRARY_PATH_EMPTY] = (SoapFaultStruct)
            {"Server", "Library path is empty", "", ""};
        s_arrSoapFaultStruct[HANDLER_NOT_LOADED] = (SoapFaultStruct)
            {"Server", "Handler not loaded", "", ""};
        s_arrSoapFaultStruct[HANDLER_BEING_USED] = (SoapFaultStruct)
            {"Server", "Handler is being used", "", ""};
        s_arrSoapFaultStruct[GET_HANDLER_FAILED] = (SoapFaultStruct)
            {"Server", "Get hander failed", "", ""};
        s_arrSoapFaultStruct[WRONG_HANDLER_TYPE] = (SoapFaultStruct)
            {"Server", "Wrong handler type", "", ""};
        s_arrSoapFaultStruct[NO_HANDLERS_CONFIGURED] = (SoapFaultStruct)
            {"Server", "No handlers configured", "", ""};
        s_arrSoapFaultStruct[AXISC_UNKNOWN_ERROR] = (SoapFaultStruct)
            {"Server", "Unknown error", "", ""};

        m_bInit = true;
    }
}

const char* SoapFault::getSoapString()
{
    return m_sFaultstring.c_str(); 
}

/*the caller of the SoapFault::getSoapFault(int) has to delete the 
 * returned SoapFault pointer
 */
SoapFault* SoapFault::getSoapFault(int iFaultCode)
{    
    SoapFaultStruct objFaultStruct = s_arrSoapFaultStruct[iFaultCode];
    SoapFault* pSoapFault= NULL;

    /* fill the soap fault object */
    pSoapFault= new SoapFault();
        
    /* TODO *********************************************** */
    /* the soap envelope namespace prefix to be obtained from 
     * gs_SoapEnvVersionsStruct should depend on the relevant SOAP VERSION
     */
     pSoapFault->m_sFaultcode= string(gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix) + 
         ":" + objFaultStruct.pcFaultcode;
     pSoapFault->m_sFaultstring= objFaultStruct.pcFaultstring;
     pSoapFault->m_sFaultactor= objFaultStruct.pcFaultactor;
     pSoapFault->m_sFaultDetail= objFaultStruct.pcFaultDetail;        
    
    return pSoapFault;
}

SoapFault::SoapFault(string sFaultcode, string sFaultstring, string sFaultactor, string sDetail) 
{
    m_sFaultcode= sFaultcode;
    m_sFaultstring= sFaultstring;
    m_sFaultactor= sFaultactor;
    m_sFaultDetail= sDetail;    
}

void SoapFault::setFaultactor(const string& sFaultactor)
{
    m_sFaultactor = sFaultactor;
}

void SoapFault::setFaultDetail(const string& sFaultDetail)
{
    m_sFaultDetail = sFaultDetail;
}

string SoapFault::getFaultcode()
{
    return m_sFaultcode;
}

string SoapFault::getFaultstring()
{
    return m_sFaultstring;
}

string SoapFault::getFaultactor()
{
    return m_sFaultactor;
}

string SoapFault::getFaultDetail()
{
    return m_sFaultDetail;
}

bool SoapFault::operator ==(const SoapFault &objSoapFault)
{
    if ((m_sFaultcode == objSoapFault.m_sFaultcode) &&
        (m_sFaultstring == objSoapFault.m_sFaultstring) &&
        (m_sFaultactor == objSoapFault.m_sFaultactor) &&
        (m_sFaultDetail == objSoapFault.m_sFaultDetail))
    {
        return true;
    }

    return false;
}

