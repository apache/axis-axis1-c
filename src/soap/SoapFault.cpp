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

    if(!m_sDetail.empty())
    {        
        pSZ.serialize("<detail>", m_sDetail.c_str(), "</detail>", NULL);
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
        for (int sf=0; sf < FAULT_LAST; sf++)
        {
            m_sFaultMap[sf] = g_sObjSoapFaultStruct[sf];
        }
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
SoapFault* SoapFault::getSoapFault(int intFaultNo)
{    
    map<int, SoapFaultStruct>::iterator itSoapFault= m_sFaultMap.find(intFaultNo);
    SoapFault* pSoapFault= NULL;

    if(itSoapFault != m_sFaultMap.end())
    {
        /* fill the soap fault object */
        pSoapFault= new SoapFault();
        
        /* TO DO *********************************************** */
        /* the soap envelope namespace prefix to be obtained from 
         * gs_SoapEnvVersionsStruct shoud depend on the relavent SOAP VERSION
         */
        pSoapFault->m_sFaultcode= string(gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix) + ":" +(*itSoapFault).second.pchFaultcode;
        pSoapFault->m_sFaultstring= (*itSoapFault).second.pchFaultstring;
        pSoapFault->m_sFaultactor= (*itSoapFault).second.pchFaultactor;
        pSoapFault->m_sDetail= (*itSoapFault).second.pchDetail;        
    }
    else
    {
        /* throw exception */
    }
    
    return pSoapFault;
}

SoapFault::SoapFault(string sFaultcode, string sFaultstring, string sFaultactor, string sDetail) 
{
    m_sFaultcode= sFaultcode;
    m_sFaultstring= sFaultstring;
    m_sFaultactor= sFaultactor;
    m_sDetail= sDetail;    
}

bool SoapFault::operator ==(const SoapFault &objSoapFault)
{
    if ((m_sFaultcode == objSoapFault.m_sFaultcode) &&
        (m_sFaultstring == objSoapFault.m_sFaultstring) &&
        (m_sFaultactor == objSoapFault.m_sFaultactor) &&
        (m_sDetail == objSoapFault.m_sDetail))
    {
        return true;
    }

    return false;
}
