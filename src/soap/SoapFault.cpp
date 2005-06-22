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
    if(m_bIsSimpleDetail)
    {
        pSZ.setStyle(DOC_LITERAL);
    pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL); 
	
    m_pFaultcodeParam->serialize(pSZ);
    m_pFaultstringParam->serialize(pSZ);

    if(m_pFaultactorParam)
    {        
        m_pFaultactorParam->serialize(pSZ);
    } 

	//Chinthana:Changed the code to solved Issue AXISCPP-706.
    /*if(m_pFaultDetail)
    {
            m_pFaultDetail->serialize(pSZ);
    }*/
	if(m_pFaultDetail) 
	{ 
		pSZ.serialize("<detail><appSpecific>", NULL); 
		m_pFaultDetail->serialize(pSZ); 
		pSZ.serialize("</appSpecific></detail>\n", NULL); 
	} 
	//22/06/2005.............................................
    
	pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
		gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL); 
    }
    else
    {
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":",
        gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_FAULT], ">\n", NULL);

    m_pFaultcodeParam->serialize(pSZ);
    m_pFaultstringParam->serialize(pSZ);

    if(m_pFaultactorParam)
    {
        m_pFaultactorParam->serialize(pSZ);
    }

	//Chinthana:Changed the code to solved Issue AXISCPP-706. 
    /*if(m_pFaultDetail)
    {
         pSZ.serialize("<detail>", NULL);
            m_pFaultDetail->serialize(pSZ);
            pSZ.serialize("</detail>\n", NULL);
    }*/
	if(m_pFaultDetail) 
	{ 
		pSZ.serialize("<detail><appSpecific>", NULL); 
		m_pFaultDetail->serialize(pSZ); 
		pSZ.serialize("</appSpecific></detail>\n", NULL); 
	} 
	//22/06/2005.........................................

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

int SoapFault::setParam(Param* pParam, const AxisChar* pchName, const AxisChar* pValue, XSDTYPE type)
{
    if (!pParam) return AXIS_FAIL;
    pParam->m_sName = pchName;
    pParam->setValue(type, new String((xsd__string) pValue));
    return AXIS_SUCCESS;
}

int SoapFault::setFaultcode(const AxisChar* sFaultcode)
{
    m_pFaultcodeParam = new Param();
	setParam(m_pFaultcodeParam, "faultcode", sFaultcode, XSD_STRING); 
    m_sFaultcode= sFaultcode;

    return AXIS_SUCCESS;
}

int SoapFault::setFaultstring(const AxisChar* sFaultstring)
{
    m_pFaultstringParam = new Param();
    setParam(m_pFaultstringParam, "faultstring", sFaultstring, XSD_STRING); 
    m_sFaultstring= sFaultstring;

    return AXIS_SUCCESS;
}
int SoapFault::setFaultactor(const AxisChar* sFaultactor)
{
    m_pFaultactorParam = new Param();
    setParam(m_pFaultactorParam, "faultactor", sFaultactor, XSD_STRING); 
    m_sFaultactor = sFaultactor;
    
    return AXIS_SUCCESS;
}

int SoapFault::setFaultDetail(const AxisChar* sFaultDetail)
{
    m_pFaultDetail = new Param();
    setParam(m_pFaultDetail, "detail", sFaultDetail, XSD_STRING);
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
