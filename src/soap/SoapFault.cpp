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
#include "SoapSerializer.h"
#include "SoapDeSerializer.h"
#include <axis/SoapEnvVersions.hpp>
#include <axis/GDefine.hpp>
#include "../common/AxisTrace.h"
#include "../common/AxisConfig.h"

extern AxisConfig* g_pConfig;
AXIS_CPP_NAMESPACE_START
extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];
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
    if(m_bIsSimpleDetail)
    {
        pSZ.setStyle(DOC_LITERAL);
    pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL); 
	
    m_pFaultcodeParam->serialize(pSZ);
    //pSZ.serialize("<faultcode>", m_sFaultcode.c_str(), "</faultcode>", NULL);
    m_pFaultstringParam->serialize(pSZ);
    //pSZ.serialize("<faultstring>", m_sFaultstring.c_str(), "</faultstring>", NULL);

    if(m_pFaultactorParam)
    {        
        m_pFaultactorParam->serialize(pSZ);
        //pSZ.serialize("<faultactor>", m_sFaultactor.c_str(), "</faultactor>", NULL);
    } 

    if(m_pFaultDetail)
    {
            m_pFaultDetail->serialize(pSZ);
    }
    
	pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
		gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL); 
    }
    else
    {
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL);

    m_pFaultcodeParam->serialize(pSZ);
    //pSZ.serialize("<faultcode>", m_sFaultcode.c_str(), "</faultcode>", NULL);
    m_pFaultstringParam->serialize(pSZ);
    //pSZ.serialize("<faultstring>", m_sFaultstring.c_str(), "</faultstring>", NULL);

    if(m_pFaultactorParam)
    {
        m_pFaultactorParam->serialize(pSZ);
        //pSZ.serialize("<faultactor>", m_sFaultactor.c_str(), "</faultactor>", NULL);
    }

    if(m_pFaultDetail)
    {
        /*if(m_bIsSimpleDetail)
        {
            m_pFaultDetail->serialize(pSZ);
        }
        else
        {*/
            pSZ.serialize("<detail>", NULL);
            m_pFaultDetail->serialize(pSZ);
            pSZ.serialize("</detail>\n", NULL);
        //}
    }

        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
                gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL);
    }
    return iStatus;
}



void SoapFault::initialize()
{
    if (!m_bInit)
    {
        static SoapFaultStruct s_arrLocalFaultStruct[FAULT_LAST] = 
        {
            /*VersionMismatch faults */
        /*0*/    {"VersionMismatch", "Soap Version Mismatch error", "", ""},
            /*MustUnderstand faults */ 
        /*1*/    {"MustUnderstand", "Soap Must Understand  error", "", ""},
            /*Client faults */
        /*2*/    {"Client", "Soap message is incorrect or incomplete", "", ""},
        /*3*/    {"Client", "Soap Action header empty", "", ""},
        /*4*/    {"Client", "Soap content is not valid", "", ""},
        /*5*/    {"Client", "No method to invoke", "", ""},
        /*6*/    {"Client", "Content is not Soap", "", ""},
        /*7*/    {"Client", "Requested service is not registerd at the server", "", ""},
        /*8*/    {"Client", "Soap method is not allowed to invoke", "", ""},
        /*9*/    {"Client", "Parameter type mismatch", "", ""},
        /*10*/    {"Client", "WSDD file loading failed", "", ""},
        /*11*/    {"Client", "A client handler failed", "", ""},

            /*Server faults */
        /*12*/    {"Server", "Unknown Engine Exception", "", ""},
        /*13*/    {"Server", "Cannot load web service", "", ""},
        /*14*/    {"Server", "Cannot load service handlers", "", ""},
        /*15*/    {"Server", "DLOPEN FAILED in loading transport library", "", ""},
        /*16*/    {"Server", "DLOPEN FAILED in loading parser library", "", ""},
        /*17*/    {"Server", "A service handler failed", "", ""},
        /*18*/    {"Server", "Webservice failed", "", ""},
        /*19*/    {"Server", "Handler initialization failed", "", ""},
        /*20*/    {"Server", "Handler creation failed", "", ""},
        /*21*/    {"Server", "Library loading failed", "", ""},
        /*22*/    {"Server", "Handler not loaded", "", ""},
        /*23*/    {"Server", "Handler is being used", "", ""},
        /*24*/    {"Server", "Get hander failed", "", ""},
        /*25*/    {"Server", "Wrong handler type", "", ""},
        /*26*/    {"Server", "Unknown Axis Configuration Exception", "", ""},
        /*27*/    {"Server", "Transport configuration error", "", ""},
        /*28*/    {"Server", "Library path is empty", "", ""},
        /*29*/    {"Server", "Unknown Wsdd Exception", "", ""},
        /*30*/    {"Server", "No handlers configured", "", ""},
        /*31*/    {"Server", "Unknown Soap Exception", "", ""},
        /*32*/    {"Server", "Unknown Transport Exception", "", ""},
        /*33*/    {"Server", "Receive from transport failed", "", ""},
        /*34*/    {"Server", "Send to transport failed", "", ""},
        /*35*/    {"Server", "HTTP Error, cannot process response message", "", ""},
        /*36*/    {"Server", "nknow HTTP response, cannot process response message", "", ""},
        /*37*/    {"Server", "Http transport exception", "", ""},
        /*38*/    {"Server", "Unexpected string", "", ""},
        /*39*/    {"Server", "Cannot initialize a channel to the remote end", "", ""},
        /*40*/    {"Server", "Sockets error Couldn't create socket", "", ""},
        /*41*/    {"Server", "Cannot open a channel to the remote end, shutting down the channel", "", ""},
        /*42*/    {"Server", "Invalid socket. Socket may not be open", "", ""},
        /*43*/    {"Server", "Output streaming error on Channel while writing data", "", ""},
        /*44*/    {"Server", "Input streaming error while getting data", "", ""},
        /*45*/    {"Server", "Channel error while waiting for timeout", "", ""},
        /*46*/    {"Server", "Channel error connection timeout before receving", "", ""},
        /*47*/    {"Server", "Transport buffer is empty", "", ""},
        /*48*/    {"Server", "Buffer received from the parser is empty", "", ""},
        /*49*/    {"Server", "XML_STATUS_ERROR thrown from parser", "", ""},
        /*50*/    {"Server", "Error when getting the byte stream from the transport", "", ""},
        /*51*/    {"Server", "Test exception", "", ""},
        /*52*/    {"Server", "Unknown exception", "", ""}
            
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
     /* Fault actor should be set to the node url in which Axis C++ running.
      * Currently it is hardcoded to localhost
      */

    char* pcNodeName = g_pConfig->getAxisConfProperty(AXCONF_NODENAME);
    char* pcPort = g_pConfig->getAxisConfProperty(AXCONF_LISTENPORT);
    string strUrl = pcNodeName;
    strUrl += ":";
    strUrl += string(pcPort);
    pSoapFault->setFaultactor(strUrl);			 
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
    pParam->m_Value.pStrValue = new char[strlen((const char*)pValue)+1];
    strcpy((char*)(pParam->m_Value.pStrValue),(const char*)pValue);
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
    setParam(m_pFaultDetail, "detail", sFaultDetail.c_str(), XSD_STRING);
    m_sFaultDetail = sFaultDetail;
    m_bIsSimpleDetail = true;

    return AXIS_SUCCESS;
}

int SoapFault::setFaultDetail(const Param* pFaultDetail)
{
    m_pFaultDetail = (Param*) pFaultDetail;

    return AXIS_SUCCESS;
}

int SoapFault::setCmplxFaultObjectName(const string& sCmplxFaultObjectName)
{
    m_sCmplxFaultObjectName = sCmplxFaultObjectName;
    return AXIS_SUCCESS;
}

int SoapFault::setCmplxFaultObject(const void* pCmplxFaultObject)
{
    m_pCmplxFaultObject = pCmplxFaultObject;

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

void SoapFault::setDeSerializer(SoapDeSerializer* pDZ)
{
    m_pDZ = pDZ;
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

string SoapFault::getSimpleFaultDetail()
{
    return m_sFaultDetail;
}

string SoapFault::getCmplxFaultObjectName()
{
    return m_sCmplxFaultObjectName;
}

void* SoapFault::getCmplxFaultObject(void* pDZFunct, void* pCreFunct, void* pDelFunct,
        const AxisChar* pName, const AxisChar* pNamespace)
{ 
    return m_pDZ->getCmplxFaultObject (pDZFunct, pCreFunct, pDelFunct, pName,
        pNamespace);
}

const void* SoapFault::getCmplxFaultObject()
{
	return m_pCmplxFaultObject;
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

AXIS_CPP_NAMESPACE_END
