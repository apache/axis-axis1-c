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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */

/*
 * Revision 1.1  2004/June/02 roshan
 * The following changes were done during correcting a Runtime error in the
 *  windows platform.
 * Added deletion of pointers to the Destrutor
 * Added "pParam->m_Value.pStrValue = strdup((char*)(pValue));" to the setParam
 *  method and removed the line
 *   "pParam->m_Value.pStrValue = *((char**)(pValue));".
 * Changed setFaultcode, setFaultstring, setFaultactor, setFaultDetail methods
 *  to send a char pointer to the setParam method.
 *  eg: In the setFaultcode method, changed passing of &sFaultcode to 
 *  sFaultcode.c_str()
 *  i.e Before change:
 *      setParam(m_pFaultcodeParam, "faultcode", &sFaultcode, XSD_STRING); 
 *      After change:
 *      setParam(m_pFaultcodeParam, "faultcode", sFaultcode.c_str(), XSD_STRING); 
 *
 * Changed. The "SOAP-ENV" prefix was hard-coded in the "serialize" method.
 *  Corrected it to serialize the correct prefix.
 */

#include "SoapFault.h"
#include <axis/server/SoapSerializer.h>
#include <axis/server/SoapEnvVersions.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

volatile bool SoapFault::m_bInit = false;

SoapFault::SoapFault()
{
    m_bIsSimpleDetail = false;
}

SoapFault::~SoapFault()
{
	delete m_pFaultcodeParam;
	delete m_pFaultstringParam;
    delete m_pFaultactorParam;
    delete m_pFaultDetail;

	m_pFaultcodeParam = NULL;
	m_pFaultstringParam = NULL;
    m_pFaultactorParam = NULL;
    m_pFaultDetail = NULL;
}

int SoapFault::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{
    /* written according to SOAP Version 1.1 */

    int iStatus= AXIS_SUCCESS;
	
	pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
		gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">", NULL); 
	
    m_pFaultcodeParam->serialize(pSZ);
    //pSZ.serialize("<faultcode>", m_sFaultcode.c_str(), "</faultcode>", NULL);
    m_pFaultstringParam->serialize(pSZ);
    //pSZ.serialize("<faultstring>", m_sFaultstring.c_str(), "</faultstring>", NULL);

    if(m_pFaultactorParam)
    {        
        m_pFaultactorParam->serialize(pSZ);
        //pSZ.serialize("<faultactor>", m_sFaultactor.c_str(), "</faultactor>", NULL);
    } 

    /*if(!m_sFaultDetail.empty())
    {        
        pSZ.serialize("<detail>", m_sFaultDetail.c_str(), "</detail>", NULL);
    }*/

    if(m_pFaultDetail)
    {
        if(m_bIsSimpleDetail)
        {
            m_pFaultDetail->serialize(pSZ);
        }
        else
        {
            pSZ.serialize("<faultdetail>", NULL);
            m_pFaultDetail->serialize(pSZ);
            pSZ.serialize("</faultdetail>", NULL);
        }
    }
    
	pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
		gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">", NULL); 

    return iStatus;
}


void SoapFault::initialize()
{
    if (!m_bInit)
    {
        static SoapFaultStruct s_arrLocalFaultStruct[FAULT_LAST] = 
        {
            /*VersionMismatch faults */
            {"VersionMismatch", "Soap Version Mismatch error", "", ""},
            /*MustUnderstand faults */ 
            {"MustUnderstand", "Soap Must Understand  error", "", ""},
            /*Client faults */
            {"Client", "Soap message is incorrect or incomplete", "", ""},
            {"Client", "Soap Action header empty", "", ""},
            {"Client", "Soap content is not valid", "", ""},
            {"Client", "No method to invoke", "", ""},
            {"Client", "Content is not Soap", "", ""},
            {"Client", "Requested service is not registerd at the server", "", ""},
            {"Client", "Soap method is not allowed to invoke", "", ""},
            {"Client", "Parameter type mismatch", "", ""},
            {"Client", "A client handler failed", "", ""},

            /*Server faults */
            {"Server", "Unknown Engine Exception", "", ""},
            {"Server", "Cannot load web service", "", ""},
            {"Server", "Cannot load service handlers", "", ""},
            {"Server", "A service handler failed", "", ""},
            {"Server", "Webservice failed", "", ""},
            {"Server", "Handler initialization failed", "", ""},
            {"Server", "Handler creation failed", "", ""},
            {"Server", "Library loading failed", "", ""},
            {"Server", "Handler not loaded", "", ""},
            {"Server", "Handler is being used", "", ""},
            {"Server", "Get hander failed", "", ""},
            {"Server", "Wrong handler type", "", ""},
            {"Server", "Unknown Axis Configuration Exception", "", ""},
            {"Server", "Transport configuration error", "", ""},
            {"Server", "Library path is empty", "", ""},
            {"Server", "Unknown Wsdd Exception", "", ""},
            {"Server", "No handlers configured", "", ""},
            {"Server", "Unknown Soap Exception", "", ""},
            {"Server", "Unknown Transport Exception", "", ""},
            {"Server", "Receive from transport failed", "", ""},
            {"Server", "Send to transport failed", "", ""},
            {"Server", "HTTP Error, cannot process response message", "", ""},
            {"Server", "nknow HTTP response, cannot process response message", "", ""},
            {"Server", "Http transport exception", "", ""},
            {"Server", "Unexpected string", "", ""},
            {"Server", "Cannot initialize a channel to the remote end", "", ""},
            {"Server", "Sockets error Couldn't create socket", "", ""},
            {"Server", "Cannot open a channel to the remote end, shutting down the channel", "", ""},
            {"Server", "Invalid socket. Socket may not be open", "", ""},
            {"Server", "Output streaming error on Channel while writing data", "", ""},
            {"Server", "Input streaming error while getting data", "", ""},
            {"Server", "Channel error while waiting for timeout", "", ""},
            {"Server", "Channel error connection timeout before receving", "", ""},
            {"Server", "Transport buffer is empty", "", ""},
            {"Server", "Buffer received from the parser is empty", "", ""},
            {"Server", "XML_STATUS_ERROR thrown from parser", "", ""},
            {"Server", "Error when getting the byte stream from the transport", "", ""},
            {"Server", "Test exception", "", ""},
            {"Server", "Unknown exception", "", ""}
            
        };
        s_parrSoapFaultStruct = s_arrLocalFaultStruct;
        m_bInit = true;
    }
}

/*the caller of the SoapFault::getSoapFault(int) has to delete the 
 * returned SoapFault pointer
 */
SoapFault* SoapFault::getSoapFault(int iFaultCode)
{   
    SoapFault* pSoapFault= NULL;

    /* fill the soap fault object */
    pSoapFault= new SoapFault();
        
    /* TODO *********************************************** */
    /* the soap envelope namespace prefix to be obtained from 
     * gs_SoapEnvVersionsStruct should depend on the relevant SOAP VERSION
     */
     string strFaultcode = s_parrSoapFaultStruct[iFaultCode].pcFaultcode;
     string strSoapEnvVerStruct = gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix;
     pSoapFault->setFaultcode(strSoapEnvVerStruct + ":" + strFaultcode);
     //pSoapFault->setFaultcode(string(gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix) + 
     //    ":" + s_parrSoapFaultStruct[iFaultCode].pcFaultcode);
     pSoapFault->setFaultstring(s_parrSoapFaultStruct[iFaultCode].pcFaultstring);
     //pSoapFault->setFaultactor(s_parrSoapFaultStruct[iFaultCode].pcFaultactor);
     pSoapFault->setFaultactor("http://endpoint/url");
     pSoapFault->setFaultDetail(s_parrSoapFaultStruct[iFaultCode].pcFaultDetail);
    
    return pSoapFault;
}

SoapFault::SoapFault(string sFaultcode, string sFaultstring, string sFaultactor, string sDetail) 
{
    m_sFaultcode= sFaultcode;
    m_sFaultstring= sFaultstring;
    m_sFaultactor= sFaultactor;
    m_sFaultDetail= sDetail;    
}

int SoapFault::setParam(Param* pParam, const AxisChar* pchName, const void* pValue, XSDTYPE type)
{
    if (!pParam) return AXIS_FAIL;
    pParam->m_Type = type;
    pParam->m_sName = pchName;
    //pParam->m_Value.pStrValue = *((char**)(pValue));
	pParam->m_Value.pStrValue = strdup((char*)(pValue));
    return AXIS_SUCCESS;
}

int SoapFault::setFaultcode(const string& sFaultcode)
{
    m_pFaultcodeParam = new Param();
    //setParam(m_pFaultcodeParam, "faultcode", &sFaultcode, XSD_STRING); 
	setParam(m_pFaultcodeParam, "faultcode", sFaultcode.c_str(), XSD_STRING); 
    m_sFaultcode= sFaultcode;

    return AXIS_SUCCESS;
}

int SoapFault::setFaultstring(const string& sFaultstring)
{
    m_pFaultstringParam = new Param();
    setParam(m_pFaultstringParam, "faultstring", sFaultstring.c_str(), XSD_STRING); 
    m_sFaultstring= sFaultstring;

    return AXIS_SUCCESS;
}
int SoapFault::setFaultactor(const string& sFaultactor)
{
    m_pFaultactorParam = new Param();
    setParam(m_pFaultactorParam, "faultactor", sFaultactor.c_str(), XSD_STRING); 
    m_sFaultactor = sFaultactor;
    
    return AXIS_SUCCESS;
}

int SoapFault::setFaultDetail(const string& sFaultDetail)
{
    m_pFaultDetail = new Param();
    setParam(m_pFaultDetail, "faultdetail", sFaultDetail.c_str(), XSD_STRING);
    m_sFaultDetail = sFaultDetail;
    m_bIsSimpleDetail = true;

    return AXIS_SUCCESS;
}

int SoapFault::setFaultDetail(const Param* pFaultDetail)
{
    m_pFaultDetail = (Param*) pFaultDetail;

    return AXIS_SUCCESS;
}

void SoapFault::setPrefix(const AxisChar* prefix)
{
    m_strPrefix = prefix;
}

void SoapFault::setLocalName(const AxisChar* localname)
{
    m_strLocalname = localname;
}

void SoapFault::setUri(const AxisChar* uri)
{
    m_strUri = uri;
}

const char* SoapFault::getSoapString()
{
    return m_sFaultstring.c_str(); 
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

