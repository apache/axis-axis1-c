/* -*- C++ -*- */
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
 *
 * 
 * @author Sanjaya Singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */


#include <axis/client/Call.h>
#include <axis/server/AxisConfig.h>
#include "../../transport/axis/AxisTransport.h"
#include "../../transport/axis/Channel.hpp"
#include "ClientAxisEngine.h"
#include "../SOAPTransportFactory.h"
#include <axis/SOAPTransport.h>

extern "C" int initialize_module (int bServer);

bool CallBase::bInitialized = false;
CallFunctions CallBase::ms_VFtable;

Call::Call ()
:m_strProxyHost(""), m_uiProxyPort(0), m_bUseProxy(false)
{
    m_pAxisEngine = NULL;
    m_pMsgData = NULL;
    m_pIWSSZ = NULL;
    m_pIWSDZ = NULL;
    initialize_module (0);
    m_pTransport = NULL;
    m_nStatus = AXIS_SUCCESS;
	m_pcEndPointUri = 0;
}

Call::~Call ()
{
	
}

int Call::setEndpointURI (const char* pchEndpointURI)
{
    m_pcEndPointUri = strdup(pchEndpointURI);
    return AXIS_SUCCESS;
}

void Call::setOperation (const char* pchOperation, const char* pchNamespace)
{
    m_pIWSSZ->createSoapMethod (pchOperation, pchNamespace);
}

void Call::addParameter (void* pValue, const char* pchName, XSDTYPE nType)
{
     m_nStatus = m_pIWSSZ->addOutputParam (pchName, pValue, nType);
}

/*
 * Method used to add arrays of basic types as parameters
 */
void Call::addBasicArrayParameter (Axis_Array* pArray, XSDTYPE nType,
    const AxisChar* pName)
{
    m_nStatus = m_pIWSSZ->addOutputBasicArrayParam (pArray, nType, pName);
}

void Call::addCmplxArrayParameter (Axis_Array* pArray, void* pSZFunct,
    void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
    const AxisChar* pNamespace)
{
     m_nStatus = m_pIWSSZ->addOutputCmplxArrayParam (pArray, pSZFunct, pDelFunct, pSizeFunct,
        pName, pNamespace);
}

void Call::addCmplxParameter (void* pObject, void* pSZFunct, void* pDelFunct,
    const AxisChar* pName, const AxisChar* pNamespace)
{
     m_nStatus = m_pIWSSZ->addOutputCmplxParam (pObject, pSZFunct, pDelFunct, pName,
        pNamespace);
}

int Call::invoke ()
{
    try
    {
        m_nStatus =  m_pAxisEngine->process(m_pTransport);
    }
    catch(AxisException& e)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }

    return m_nStatus;
}

int Call::initialize (PROVIDERTYPE nStyle, int secure)
/* Does this mean that the stub that uses this Call object as well as all 
 * client side handlers have the same PROVIDERTYPE ? 
 */
{
    /* Initialize re-usable objects of this instance (objects may have been 
     * populated by the previous call.)
     */
    try
    {
        m_nStatus = AXIS_SUCCESS;
        // remove_headers(&m_Soap);
        if (AXIS_SUCCESS != openConnection (secure)) {
        	m_nStatus = AXIS_FAIL;
            return AXIS_FAIL;
        }
        if (m_pAxisEngine)
            delete m_pAxisEngine;
        m_pAxisEngine = new ClientAxisEngine ();
        if (!m_pAxisEngine) {
        	m_nStatus = AXIS_FAIL;
            return AXIS_FAIL;
        }
        if (AXIS_SUCCESS == m_pAxisEngine->initialize ())
        {
            m_pMsgData = m_pAxisEngine->getMessageData ();
            if (m_pMsgData)
            {
                m_pMsgData->getSoapSerializer ((IWrapperSoapSerializer**) 
                    (&m_pIWSSZ));
                m_pMsgData->getSoapDeSerializer ((IWrapperSoapDeSerializer**) 
                    (&m_pIWSDZ));
                if (m_pIWSSZ && m_pIWSDZ)
                {
                    m_pIWSSZ->setCurrentProviderType (nStyle);
                    m_pIWSDZ->setCurrentProviderType (nStyle);
                    switch (nStyle)
                    {
                        case C_RPC_PROVIDER:
                        case CPP_RPC_PROVIDER:
                            m_pIWSSZ->setStyle (RPC_ENCODED);
                            m_pIWSDZ->setStyle (RPC_ENCODED);
                            break;
                        case C_DOC_PROVIDER:
                        case CPP_DOC_PROVIDER:
                            m_pIWSSZ->setStyle (DOC_LITERAL);
                            m_pIWSDZ->setStyle (DOC_LITERAL);
                            break;
                        case COM_PROVIDER:
                            // TODO: ??
                            break;
                        default:;
                                //TODO: ??
                    }
                    return AXIS_SUCCESS;
                }
            }
            m_nStatus = AXIS_FAIL;
            return AXIS_FAIL;
        }
        m_nStatus = AXIS_FAIL;        
        return AXIS_FAIL;
    }
    catch (AxisException& e)
    {
        /* printf(e.GetErr().c_str()); */
        m_nStatus = AXIS_FAIL;
        throw;
    }
    catch (...)
    {
        /* printf("Unknown exception occured in the client"); */
        m_nStatus = AXIS_FAIL;        
        throw;
    }
}

int Call::unInitialize ()
{
    if (m_pAxisEngine)
    {
		/* Initialization,serialization, invokation or check message success */
		if ( m_nStatus == AXIS_SUCCESS &&  m_pIWSDZ != NULL ) 
		{
			/* Test if deserialization failed */
			m_nStatus = m_pIWSDZ->getStatus();
		}
			
        m_pAxisEngine->unInitialize ();
        delete m_pAxisEngine;
        m_pAxisEngine = NULL;
    }
    closeConnection ();
    return AXIS_SUCCESS;
}

int Call::setProtocol (AXIS_PROTOCOL_TYPE protocol)
{
	m_nTransportType = protocol;
    return AXIS_SUCCESS;
}

int Call::setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE type,
    const char* value)
{
    m_pTransport->setTransportProperty(type, value);
    return AXIS_SUCCESS;
}

/*
 * This method takes a look at the m_Soap structure and open 
 * transport layer connection to the server. Then this adds the 
 * relevant function pointers and streams to the m_Soap structure, 
 * which is given to the AxisEngine. AxisEngine can use those 
 * functions with those streams at any time it wants to send/receive
 * bytes to/from the server.
 */
int Call::openConnection(int secure)
{
    try
    {
    m_pTransport = SOAPTransportFactory::getTransportObject(m_nTransportType);
	if (!m_pTransport) return AXIS_FAIL;
	m_pTransport->setEndpointUri(m_pcEndPointUri);
  
    //if use proxy then set proxy
    if( m_bUseProxy )
    	m_pTransport->setProxy(m_strProxyHost.c_str(), m_uiProxyPort);
    m_nStatus = m_pTransport->openConnection();
    }
    catch(AxisException& e)
    {
        throw;
    }
    catch(...)
    {
        throw;
    }

    return m_nStatus;
}

/*
 * This method closes the connection of this object to the server
 */
void Call::closeConnection()
{
    m_pTransport->closeConnection();
	if (m_pTransport) SOAPTransportFactory::destroyTransportObject(m_pTransport);
}

void Call::setSOAPVersion (SOAP_VERSION version)
{
    m_pIWSSZ->setSoapVersion (version);
}

Axis_Array Call::getBasicArray (XSDTYPE nType, const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getBasicArray (nType, pName, pNamespace);
}

Axis_Array Call::getCmplxArray (void* pDZFunct, void* pCreFunct, 
    void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getCmplxArray (pDZFunct, pCreFunct, pDelFunct, pSizeFunct,
        pName, pNamespace);
}

int Call::getElementAsInt (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsInt (pName, pNamespace);
}

int Call::getFaultDetail(char** ppcDetail)
{
    return m_pIWSDZ->getFaultDetail(ppcDetail);
}

xsd__boolean Call::getElementAsBoolean (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsBoolean (pName, pNamespace);
}

unsigned int Call::getElementAsUnsignedInt (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedInt (pName, pNamespace);
}

short Call::getElementAsShort (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsShort (pName, pNamespace);
}

unsigned short Call::getElementAsUnsignedShort (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedShort (pName, pNamespace);
}

char Call::getElementAsByte (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsByte (pName, pNamespace);
}
unsigned char Call::getElementAsUnsignedByte (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedByte (pName, pNamespace);
}

long Call::getElementAsLong (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsLong (pName, pNamespace);
}

long Call::getElementAsInteger (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsInteger (pName, pNamespace);
}

unsigned long Call::getElementAsUnsignedLong (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedLong (pName, pNamespace);
}

float Call::getElementAsFloat (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsFloat (pName, pNamespace);
}

double Call::getElementAsDouble (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDouble (pName, pNamespace);
}

double Call::getElementAsDecimal (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDecimal (pName, pNamespace);
}

AxisChar* Call::getElementAsString (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsString (pName, pNamespace);
}

AxisChar* Call::getElementAsAnyURI (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsAnyURI (pName, pNamespace);
}

AxisChar* Call::getElementAsQName (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsQName (pName, pNamespace);
}

xsd__hexBinary Call::getElementAsHexBinary (const AxisChar* pName, 
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getElementAsHexBinary (pName, pNamespace);
}

xsd__base64Binary Call::getElementAsBase64Binary (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsBase64Binary (pName, pNamespace);
}

struct tm Call::getElementAsDateTime (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDateTime (pName, pNamespace);
}

struct tm Call::getElementAsDate (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDate (pName, pNamespace);
}

struct tm Call::getElementAsTime (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsTime (pName, pNamespace);
}

long Call::getElementAsDuration (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDuration (pName, pNamespace);
}

int Call::getAttributeAsInt (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsInt (pName, pNamespace);
}

xsd__boolean Call::getAttributeAsBoolean (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsBoolean (pName, pNamespace);
}
unsigned int Call::getAttributeAsUnsignedInt (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedInt (pName, pNamespace);
}

short Call::getAttributeAsShort (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsShort (pName, pNamespace);
}

unsigned short Call::getAttributeAsUnsignedShort (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedShort (pName, pNamespace);
}

char Call::getAttributeAsByte (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsByte (pName, pNamespace);
}
unsigned char Call::getAttributeAsUnsignedByte (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedByte (pName, pNamespace);
}

long Call::getAttributeAsLong (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsLong (pName, pNamespace);
}

long Call::getAttributeAsInteger (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getAttributeAsInteger (pName, pNamespace);
}
unsigned long Call::getAttributeAsUnsignedLong (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedLong (pName, pNamespace);
}

float Call::getAttributeAsFloat (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsFloat (pName, pNamespace);
}

double Call::getAttributeAsDouble (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDouble (pName, pNamespace);
}

double Call::getAttributeAsDecimal (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDecimal (pName, pNamespace);
}

AxisChar* Call::getAttributeAsString (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsString (pName, pNamespace);
}

AxisChar* Call::getAttributeAsAnyURI (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsAnyURI (pName, pNamespace);
}

AxisChar* Call::getAttributeAsQName (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsQName (pName, pNamespace);
}

xsd__hexBinary Call::getAttributeAsHexBinary (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsHexBinary (pName, pNamespace);
}

xsd__base64Binary Call::getAttributeAsBase64Binary (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getAttributeAsBase64Binary (pName, pNamespace);
}
struct tm Call::getAttributeAsDateTime (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getAttributeAsDateTime (pName, pNamespace);
}
struct tm Call::getAttributeAsDate (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDate (pName, pNamespace);
}
struct tm Call::getAttributeAsTime (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsTime (pName, pNamespace);
}

long Call::getAttributeAsDuration (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDuration (pName, pNamespace);
}

int Call::checkMessage (const AxisChar* pName, const AxisChar* pNamespace)
{
	 m_nStatus = m_pIWSDZ->checkMessageBody (pName, pNamespace);
    return m_nStatus;
}

int Call::checkFault (const AxisChar* pName, const AxisChar* pNamespace)
{
	 m_nStatus = m_pIWSDZ->checkForFault (pName, pNamespace);
    return m_nStatus;
}

void* Call::getCmplxObject (void* pDZFunct, void* pCreFunct, void* pDelFunct,
    const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getCmplxObject (pDZFunct, pCreFunct, pDelFunct, pName,
        pNamespace);
}

int Call::setSoapHeader (SoapHeader* pSoapHeader)
{
	m_nStatus = (m_pIWSSZ->setSoapHeader (pSoapHeader));
    return m_nStatus;
}

IHeaderBlock* Call::createHeaderBlock ()
{
    return (m_pIWSSZ->createHeaderBlock ());
}

IHeaderBlock* Call::createHeaderBlock(AxisChar* pachLocalName, 
                                       AxisChar* pachUri)
{
    return (m_pIWSSZ->createHeaderBlock (pachLocalName, pachUri));
}

int Call::getStatus() 
{
	return m_nStatus;
}

void Call::setProxy(const char* pcProxyHost, unsigned int uiProxyPort)
{
    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;    
}

AnyType* Call::getAnyObject()
{
	return m_pIWSDZ->getAnyObject();
}

int Call::addAnyObject(AnyType* pAnyObject)
{
	return m_pIWSSZ->addOutputAnyObject(pAnyObject);
}

const AxisChar* Call::getNamespacePrefix(const AxisChar* pNamespace)
{
    return m_pIWSSZ->getNamespacePrefix(pNamespace);
}

HeaderBlock_C CallBase::s_CreateHeaderBlock(void *pObj, 
    AxisChar *pachLocalName, AxisChar *pachUri)
{
	HeaderBlock_C blk;
	blk._functions = &(IHeaderBlock::ms_VFtable);
	blk._object = ((CallBase*)pObj)->createHeaderBlock(pachLocalName,
		pachUri);
	return blk;
}

void CallBase::s_Initialize()
{	
	if (bInitialized) return;
	bInitialized = true;
	ms_VFtable.setSOAPVersion = s_SetSOAPVersion;
	ms_VFtable.setTransportProperty = s_SetTransportProperty;
	ms_VFtable.setProtocol = s_SetProtocol;
	ms_VFtable.initialize = s_InitializeCall;
	ms_VFtable.invoke = s_Invoke;
	ms_VFtable.unInitialize = s_UnInitialize;
	ms_VFtable.setOperation = s_SetOperation;
	ms_VFtable.setEndpointURI = s_SetEndpointURI;
	ms_VFtable.addParameter = s_AddParameter;
	ms_VFtable.addCmplxArrayParameter = s_AddCmplxArrayParameter;
	ms_VFtable.addBasicArrayParameter = s_AddBasicArrayParameter;
	ms_VFtable.addCmplxParameter = s_AddCmplxParameter;
	ms_VFtable.getCmplxArray = s_GetCmplxArray;
	ms_VFtable.getBasicArray = s_GetBasicArray;
	ms_VFtable.getCmplxObject = s_GetCmplxObject;
	ms_VFtable.getElementAsInt = s_GetElementAsInt;
	ms_VFtable.getElementAsBoolean = s_GetElementAsBoolean;
	ms_VFtable.getElementAsUnsignedInt = s_GetElementAsUnsignedInt;
	ms_VFtable.getElementAsShort = s_GetElementAsShort;
	ms_VFtable.getElementAsUnsignedShort = s_GetElementAsUnsignedShort;
	ms_VFtable.getElementAsByte = s_GetElementAsByte;
	ms_VFtable.getElementAsUnsignedByte = s_GetElementAsUnsignedByte;
	ms_VFtable.getElementAsLong = s_GetElementAsLong;
	ms_VFtable.getElementAsInteger = s_GetElementAsInteger;
	ms_VFtable.getElementAsUnsignedLong = s_GetElementAsUnsignedLong;
	ms_VFtable.getElementAsFloat = s_GetElementAsFloat;
	ms_VFtable.getElementAsDouble = s_GetElementAsDouble;
	ms_VFtable.getElementAsDecimal = s_GetElementAsDecimal;
	ms_VFtable.getElementAsString = s_GetElementAsString;
	ms_VFtable.getElementAsAnyURI = s_GetElementAsAnyURI;
	ms_VFtable.getElementAsQName = s_GetElementAsQName;
	ms_VFtable.getElementAsHexBinary = s_GetElementAsHexBinary;
	ms_VFtable.getElementAsBase64Binary = s_GetElementAsBase64Binary;
	ms_VFtable.getElementAsDateTime = s_GetElementAsDateTime;
	ms_VFtable.getElementAsDate = s_GetElementAsDate;
	ms_VFtable.getElementAsTime = s_GetElementAsTime;
	ms_VFtable.getElementAsDuration = s_GetElementAsDuration;
	ms_VFtable.getAttributeAsInt = s_GetAttributeAsInt;
	ms_VFtable.getAttributeAsBoolean = s_GetAttributeAsBoolean;
	ms_VFtable.getAttributeAsUnsignedInt = s_GetAttributeAsUnsignedInt;
	ms_VFtable.getAttributeAsShort = s_GetAttributeAsShort;
	ms_VFtable.getAttributeAsUnsignedShort = s_GetAttributeAsUnsignedShort;
	ms_VFtable.getAttributeAsByte = s_GetAttributeAsByte;
	ms_VFtable.getAttributeAsUnsignedByte = s_GetAttributeAsUnsignedByte;
	ms_VFtable.getAttributeAsLong = s_GetAttributeAsLong;
	ms_VFtable.getAttributeAsInteger = s_GetAttributeAsInteger;
	ms_VFtable.getAttributeAsUnsignedLong = s_GetAttributeAsUnsignedLong;
	ms_VFtable.getAttributeAsFloat = s_GetAttributeAsFloat;
	ms_VFtable.getAttributeAsDouble = s_GetAttributeAsDouble;
	ms_VFtable.getAttributeAsDecimal = s_GetAttributeAsDecimal;
	ms_VFtable.getAttributeAsString = s_GetAttributeAsString;
	ms_VFtable.getAttributeAsAnyURI = s_GetAttributeAsAnyURI;
	ms_VFtable.getAttributeAsQName = s_GetAttributeAsQName;
	ms_VFtable.getAttributeAsHexBinary = s_GetAttributeAsHexBinary;
	ms_VFtable.getAttributeAsBase64Binary = s_GetAttributeAsBase64Binary;
	ms_VFtable.getAttributeAsDateTime = s_GetAttributeAsDateTime;
	ms_VFtable.getAttributeAsDate = s_GetAttributeAsDate;
	ms_VFtable.getAttributeAsTime = s_GetAttributeAsTime;
	ms_VFtable.getAttributeAsDuration = s_GetAttributeAsDuration;
	ms_VFtable.checkMessage = s_CheckMessage;
	ms_VFtable.checkFault = s_CheckFault;
	ms_VFtable.getStatus = s_GetStatus;
	ms_VFtable.getAnyObject = s_GetAnyObject;
	ms_VFtable.addAnyObject = s_AddAnyObject;
    ms_VFtable.getNamespacePrefix = s_GetNamespacePrefix;
    ms_VFtable.createHeaderBlock = s_CreateHeaderBlock;
}