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
 
/*
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */

#include "SoapFault.h"
#include "SoapSerializer.h"
#include "SoapDeSerializer.h"
#include <axis/SoapEnvVersions.hpp>
#include <axis/GDefine.hpp>
#include "../common/AxisTrace.h"
#include "../common/AxisConfig.h"


// This array of structure is used to store all the soap faults
// which are used in Axis C++. Each time a fault object is needed it is
// created using this array, in SoapFault class.

static SoapFaultStruct* s_parrSoapFaultStruct;

extern AxisConfig* g_pConfig;
AXIS_CPP_NAMESPACE_START
extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];
volatile bool SoapFault::m_bInit = false;

SoapFault::SoapFault()
{
    m_bIsSimpleDetail = false;
    m_pFaultDetail = NULL;
}

SoapFault::~SoapFault()
{
    delete m_pFaultcodeParam;
    delete m_pFaultstringParam;
    delete m_pFaultactorParam;
    if (NULL!=m_pFaultDetail) delete m_pFaultDetail;
    m_pFaultcodeParam = NULL;
    m_pFaultstringParam = NULL;
    m_pFaultactorParam = NULL;
    m_pFaultDetail = NULL;
}

int SoapFault::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{
    // written according to SOAP Version 1.1
    int iStatus= AXIS_SUCCESS;
    pSZ.setStyle(DOC_LITERAL);
    pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL);

    m_pFaultcodeParam->serialize(pSZ);
    m_pFaultstringParam->serialize(pSZ);

    if(m_pFaultactorParam)
    {
        m_pFaultactorParam->serialize(pSZ);
    }

    if(m_pFaultDetail)
    {
        pSZ.serialize("<detail>", NULL);

        if(m_bIsSimpleDetail) // Fix for AXISCPP-706
        {
            pSZ.serialize("<appSpecific>", NULL);
        }
        m_pFaultDetail->serialize(pSZ);
        if(m_bIsSimpleDetail) // Fix for AXISCPP-706
        {
            pSZ.serialize("</appSpecific>", NULL);
        }
        pSZ.serialize("</detail>\n", NULL);
    }

    pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL);

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
        /*7*/    {"Client", "Requested service is not registered at the server", "", ""},
        /*8*/    {"Client", "Soap method is not allowed to invoke", "", ""},
        /*9*/    {"Client", "Parameter type mismatch", "", ""},
        /*10*/    {"Client", "A client handler failed", "", ""},
        /*11*/    {"Client", "Client transport exception", "", ""},
        /*12*/    {"Client", "Client transport open connection failed", "", ""},
        /*13*/    {"Client", "Client transport type mismatch", "", ""},
        /*14*/    {"Client", "Client transport has no unsecure transport layer", "", ""},
        /*15*/    {"Client", "Client transport has no secure transport layer", "", ""},
        /*16*/    {"Client", "Client SSL channel reception error", "", ""},
        /*17*/    {"Client", "Client SSL channel sending error", "", ""},
        /*18*/    {"Client", "Client SSL channel init error", "", ""},
        /*19*/    {"Client", "Client SSL channel socket create error", "", ""},
        /*20*/    {"Client", "Client SSL channel socket connect error", "", ""},
        /*21*/    {"Client", "Client SSL channel invalid socket error", "", ""},
        /*22*/    {"Client", "Client SSL channel context create error", "", ""},
        /*23*/    {"Client", "Client SSL channel error", "", ""},
        /*24*/    {"Client", "Client MIME content ID not unique", "", ""},

            /*Server faults */
        /*25*/    {"Server", "Unknown Server Engine Exception", "", ""},
        /*26*/    {"Server", "Cannot load web service", "", ""},
        /*27*/    {"Server", "Cannot load service handlers", "", ""},
        /*28*/    {"Server", "DLOPEN FAILED in loading transport library", "", ""},
        /*29*/    {"Server", "DLOPEN FAILED in loading parser library", "", ""},
        /*30*/    {"Server", "A service handler failed", "", ""},
        /*31*/    {"Server", "Webservice failed", "", ""},
        /*32*/    {"Server", "Handler initialization failed", "", ""},
        /*33*/    {"Server", "Handler creation failed", "", ""},
        /*34*/    {"Server", "Library loading failed", "", ""},
        /*35*/    {"Server", "Handler not loaded", "", ""},
        /*36*/    {"Server", "Handler is being used", "", ""},
        /*37*/    {"Server", "Get hander failed", "", ""},
        /*38*/    {"Server", "Wrong handler type", "", ""},
        /*39*/    {"Server", "Unknown Axis Configuration Exception", "", ""},
        /*40*/    {"Server", "Transport configuration error", "", ""},
        /*41*/    {"Server", "Library path is empty", "", ""},
        /*42*/    {"Server", "Wsdd file not found", "", ""},
        /*43*/    {"Server", "Unknown Wsdd Exception", "", ""},
        /*44*/    {"Server", "No handlers configured", "", ""},
        /*45*/    {"Server", "Unknown Soap Exception", "", ""},
        /*46*/    {"Server", "Unknown Transport Exception", "", ""},
        /*47*/    {"Server", "Receive from transport failed", "", ""},
        /*48*/    {"Server", "Send to transport failed", "", ""},
        /*49*/    {"Server", "HTTP Error, cannot process response message", "", ""},
        /*50*/    {"Server", "Unnknown HTTP response, cannot process response message", "", ""},
        /*51*/    {"Server", "Http transport exception", "", ""},
        /*52*/    {"Server", "Unexpected string", "", ""},
        /*53*/    {"Server", "Cannot initialize a channel to the remote end", "", ""},
        /*54*/    {"Server", "Sockets error Couldn't create socket", "", ""},
        /*55*/    {"Server", "Cannot open a channel to the remote end, shutting down the channel", "", ""},
        /*56*/    {"Server", "Invalid socket. Socket may not be open", "", ""},
        /*57*/    {"Server", "Output streaming error on Channel while writing data", "", ""},
        /*58*/    {"Server", "Input streaming error while getting data", "", ""},
        /*59*/    {"Server", "Channel error while waiting for timeout", "", ""},
        /*60*/    {"Server", "Channel error connection timeout before receiving", "", ""},
        /*61*/    {"Server", "Loading SSL channel failed", "", ""},
        /*62*/    {"Server", "Loading channel failed", "", ""},
        /*63*/    {"Server", "Transport buffer is empty", "", ""},
        /*64*/    {"Server", "Buffer received from the parser is empty", "", ""},
        /*65*/    {"Server", "XML_STATUS_ERROR thrown from parser", "", ""},
        /*66*/    {"Server", "Error when getting the byte stream from the transport", "", ""},
        /*67*/    {"Server", "Test exception", "", ""},
        /*68*/    {"Server", "Unknown exception", "", ""},
        /*69*/    {"Server", "Server and Client engines mismatch", "", ""},
            
        /*70*/    {"AXISC", "Service thrown exception", "", ""},
        /*71*/    {"AXISC", "Unknown element exception", "", ""},
        /*72*/    {"AXISC", "Node value mismatch exception", "", ""},
        /*73*/    {"AXISC", "Configuration read exception", "", ""}
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

    // fill the soap fault object 
    pSoapFault= new SoapFault();
        
    /* TODO *********************************************** */
    /* the soap envelope namespace prefix to be obtained from 
     * gs_SoapEnvVersionsStruct should depend on the relevant SOAP VERSION
     */
     string strFaultcode = s_parrSoapFaultStruct[iFaultCode].pcFaultcode;
     string strSoapEnvVerStruct = gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix;
     pSoapFault->setFaultcode((strSoapEnvVerStruct + ":" + strFaultcode).c_str());
     pSoapFault->setFaultstring(s_parrSoapFaultStruct[iFaultCode].pcFaultstring);
     /* Fault actor should be set to the node url in which Axis C++ running.
      * Currently it is hardcoded to localhost
      */

    char* pcNodeName = g_pConfig->getAxisConfProperty(AXCONF_NODENAME);
    char* pcPort = g_pConfig->getAxisConfProperty(AXCONF_LISTENPORT);
    string strUrl = pcNodeName;
    strUrl += ":";
    strUrl += string(pcPort);
    pSoapFault->setFaultactor(strUrl.c_str());			 
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
    pParam->m_sName = pchName;
    pParam->setValue( type , (IAnySimpleType*) pValue);
    return AXIS_SUCCESS;
}

int SoapFault::setFaultcode(const AxisChar* sFaultcode)
{
    m_pFaultcodeParam = new Param();
	setParam(m_pFaultcodeParam, "faultcode", new String((xsd__string)sFaultcode), XSD_STRING); 
    m_sFaultcode= sFaultcode;

    return AXIS_SUCCESS;
}

int SoapFault::setFaultstring(const AxisChar* sFaultstring)
{
    m_pFaultstringParam = new Param();
    setParam(m_pFaultstringParam, "faultstring", new String((xsd__string)sFaultstring), XSD_STRING); 
    m_sFaultstring= sFaultstring;

    return AXIS_SUCCESS;
}
int SoapFault::setFaultactor(const AxisChar* sFaultactor)
{
    m_pFaultactorParam = new Param();
    setParam(m_pFaultactorParam, "faultactor", new String((xsd__string)sFaultactor), XSD_STRING); 
    m_sFaultactor = sFaultactor;
    
    return AXIS_SUCCESS;
}

int SoapFault::setFaultDetail(const AxisChar* sFaultDetail)
{
    m_pFaultDetail = new Param();
    setParam(m_pFaultDetail, "appSpecific", new String((xsd__string)sFaultDetail), XSD_STRING);
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

void SoapFault::setURI(const AxisChar* uri)
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

const AxisChar* SoapFault::getFaultcode()
{
    return m_sFaultcode.c_str();
}

const AxisChar* SoapFault::getFaultstring()
{
    return m_sFaultstring.c_str();
}

const AxisChar* SoapFault::getFaultactor()
{
    return m_sFaultactor.c_str();
}

const AxisChar* SoapFault::getSimpleFaultDetail()
{
    return m_sFaultDetail.c_str();
}

const AxisChar* SoapFault::getCmplxFaultObjectName()
{
    return m_sCmplxFaultObjectName.c_str();
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
