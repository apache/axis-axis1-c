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
 *
 */


#include <axis/client/Call.h>
#include <axis/server/AxisConfig.h>
#include "../../transport/axis/AxisTransport.h"
#include "../../transport/axis/Channel.hpp"
#include "ClientAxisEngine.h"

extern "C" int initialize_module (int bServer);

bool CallBase::bInitialized = false;
CallFunctions CallBase::ms_VFtable;

Call::Call ()
{
    m_pAxisEngine = NULL;
    m_pMsgData = NULL;
    m_pIWSSZ = NULL;
    m_pIWSDZ = NULL;
    initialize_module (0);
    m_pTransport = NULL;
    m_nStatus = AXIS_SUCCESS;
}

Call::~Call ()
{
    switch (m_Soap.trtype)
    {
        case APTHTTP:
        case APTHTTPS:
            free (m_Soap.so.http->uri_path);
            delete m_Soap.so.http;
    }
}

int Call::SetEndpointURI (const char* pchEndpointURI)
{
    m_Soap.so.http->uri_path = strdup (pchEndpointURI);
    return AXIS_SUCCESS;
}

void Call::SetOperation (const char* pchOperation, const char* pchNamespace)
{
    m_pIWSSZ->CreateSoapMethod (pchOperation, pchNamespace);
}

void Call::AddParameter (void* pValue, const char* pchName, XSDTYPE nType)
{
     m_nStatus = m_pIWSSZ->AddOutputParam (pchName, pValue, nType);
}

/*
 * Method used to add arrays of basic types as parameters
 */
void Call::AddBasicArrayParameter (Axis_Array* pArray, XSDTYPE nType,
    const AxisChar* pName)
{
    m_nStatus = m_pIWSSZ->AddOutputBasicArrayParam (pArray, nType, pName);
}

void Call::AddCmplxArrayParameter (Axis_Array* pArray, void* pSZFunct,
    void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
    const AxisChar* pNamespace)
{
     m_nStatus = m_pIWSSZ->AddOutputCmplxArrayParam (pArray, pSZFunct, pDelFunct, pSizeFunct,
        pName, pNamespace);
}

void Call::AddCmplxParameter (void* pObject, void* pSZFunct, void* pDelFunct,
    const AxisChar* pName, const AxisChar* pNamespace)
{
     m_nStatus = m_pIWSSZ->AddOutputCmplxParam (pObject, pSZFunct, pDelFunct, pName,
        pNamespace);
}

int Call::Invoke ()
{
     m_nStatus =  m_pAxisEngine->Process (&m_Soap);
     return m_nStatus;
}

int Call::Initialize (PROVIDERTYPE nStyle, int secure)
/* Does this mean that the stub that uses this Call object as well as all 
 * client side handlers have the same PROVIDERTYPE ? 
 */
{
    /* Initialize re-usable objects of this instance (objects may have been 
     * populated by the previous call.
     */
    try
    {
        m_Soap.sessionid = "somesessionid1234";
        m_nStatus = AXIS_SUCCESS;
        // remove_headers(&m_Soap);
        if (AXIS_SUCCESS != OpenConnection (secure)) {
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
        if (AXIS_SUCCESS == m_pAxisEngine->Initialize ())
        {
            m_pMsgData = m_pAxisEngine->GetMessageData ();
            if (m_pMsgData)
            {
                m_pMsgData->GetSoapSerializer ((IWrapperSoapSerializer**) 
                    (&m_pIWSSZ));
                m_pMsgData->GetSoapDeSerializer ((IWrapperSoapDeSerializer**) 
                    (&m_pIWSDZ));
                if (m_pIWSSZ && m_pIWSDZ)
                {
                    m_pIWSSZ->SetCurrentProviderType (nStyle);
                    m_pIWSDZ->SetCurrentProviderType (nStyle);
                    switch (nStyle)
                    {
                        case C_RPC_PROVIDER:
                        case CPP_RPC_PROVIDER:
                            m_pIWSSZ->SetStyle (RPC_ENCODED);
                            m_pIWSDZ->SetStyle (RPC_ENCODED);
                            break;
                        case C_DOC_PROVIDER:
                        case CPP_DOC_PROVIDER:
                            m_pIWSSZ->SetStyle (DOC_LITERAL);
                            m_pIWSDZ->SetStyle (DOC_LITERAL);
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
    catch (ChannelException e)
    {
        /* printf(e.GetErr().c_str()); */
        m_nStatus = AXIS_FAIL;        
        return AXIS_FAIL;
    }
    catch (...)
    {
        /* printf("Unknown exception occured in the client"); */
        m_nStatus = AXIS_FAIL;        
        return AXIS_FAIL;
    }
}

int Call::UnInitialize ()
{
    if (m_pAxisEngine)
    {
		/* Initialization,serialization, invokation or check message success */
		if ( m_nStatus == AXIS_SUCCESS &&  m_pIWSDZ != NULL ) 
		{
			/* Test if deserialization failed */
			m_nStatus = m_pIWSDZ->GetStatus();
		}
			
        m_pAxisEngine->UnInitialize ();
        delete m_pAxisEngine;
        m_pAxisEngine = NULL;
    }
    CloseConnection ();
    return AXIS_SUCCESS;
}

int Call::SetProtocol (AXIS_PROTOCOL_TYPE protocol)
{
    m_Soap.trtype = protocol;
    switch (protocol)
    {
        case APTHTTP:
            m_Soap.so.http = new Ax_stream_http;
            m_Soap.so.http->ip_headercount = 0;
            m_Soap.so.http->ip_headers = NULL;
            m_Soap.so.http->op_headercount = 0;
            m_Soap.so.http->op_headers = NULL;
            break;
            /* do for other protocols too */
        case APTHTTPS:
            m_Soap.so.https = new Ax_stream_https;
            m_Soap.so.https->ip_headercount = 0;
            m_Soap.so.https->ip_headers = NULL;
            m_Soap.so.https->op_headercount = 0;
            m_Soap.so.https->op_headers = NULL;
            break;
    }
    return AXIS_SUCCESS;
}

int Call::SetTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE type,
    const char* value)
{
    m_pTransport->SetTransportInformation (type, value, &m_Soap);
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
int Call::OpenConnection (int secure)
{
    m_pTransport = new AxisTransport (&m_Soap);
    m_nStatus = m_pTransport->OpenConnection (secure);
    return m_nStatus;
}

/*
 * This method closes the connection of this object to the server
 */
void Call::CloseConnection ()
{
    m_pTransport->CloseConnection ();
    delete m_pTransport;
}

void Call::SetSOAPVersion (SOAP_VERSION version)
{
    m_pIWSSZ->setSoapVersion (version);
}

Axis_Array Call::GetBasicArray (XSDTYPE nType, const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetBasicArray (nType, pName, pNamespace);
}

Axis_Array Call::GetCmplxArray (void* pDZFunct, void* pCreFunct, 
    void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetCmplxArray (pDZFunct, pCreFunct, pDelFunct, pSizeFunct,
        pName, pNamespace);
}

int Call::GetElementAsInt (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsInt (pName, pNamespace);
}

xsd__boolean Call::GetElementAsBoolean (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsBoolean (pName, pNamespace);
}

unsigned int Call::GetElementAsUnsignedInt (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsUnsignedInt (pName, pNamespace);
}

short Call::GetElementAsShort (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsShort (pName, pNamespace);
}

unsigned short Call::GetElementAsUnsignedShort (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsUnsignedShort (pName, pNamespace);
}

char Call::GetElementAsByte (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsByte (pName, pNamespace);
}
unsigned char Call::GetElementAsUnsignedByte (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->GetElementAsUnsignedByte (pName, pNamespace);
}

long Call::GetElementAsLong (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsLong (pName, pNamespace);
}

long Call::GetElementAsInteger (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsInteger (pName, pNamespace);
}

unsigned long Call::GetElementAsUnsignedLong (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsUnsignedLong (pName, pNamespace);
}

float Call::GetElementAsFloat (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsFloat (pName, pNamespace);
}

double Call::GetElementAsDouble (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsDouble (pName, pNamespace);
}

double Call::GetElementAsDecimal (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsDecimal (pName, pNamespace);
}

AxisChar* Call::GetElementAsString (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsString (pName, pNamespace);
}

AxisChar* Call::GetElementAsAnyURI (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsAnyURI (pName, pNamespace);
}

AxisChar* Call::GetElementAsQName (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsQName (pName, pNamespace);
}

xsd__hexBinary Call::GetElementAsHexBinary (const AxisChar* pName, 
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->GetElementAsHexBinary (pName, pNamespace);
}

xsd__base64Binary Call::GetElementAsBase64Binary (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsBase64Binary (pName, pNamespace);
}

struct tm Call::GetElementAsDateTime (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsDateTime (pName, pNamespace);
}

struct tm Call::GetElementAsDate (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsDate (pName, pNamespace);
}

struct tm Call::GetElementAsTime (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsTime (pName, pNamespace);
}

long Call::GetElementAsDuration (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetElementAsDuration (pName, pNamespace);
}

int Call::GetAttributeAsInt (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsInt (pName, pNamespace);
}

xsd__boolean Call::GetAttributeAsBoolean (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsBoolean (pName, pNamespace);
}
unsigned int Call::GetAttributeAsUnsignedInt (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsUnsignedInt (pName, pNamespace);
}

short Call::GetAttributeAsShort (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsShort (pName, pNamespace);
}

unsigned short Call::GetAttributeAsUnsignedShort (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsUnsignedShort (pName, pNamespace);
}

char Call::GetAttributeAsByte (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsByte (pName, pNamespace);
}
unsigned char Call::GetAttributeAsUnsignedByte (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsUnsignedByte (pName, pNamespace);
}

long Call::GetAttributeAsLong (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsLong (pName, pNamespace);
}

long Call::GetAttributeAsInteger (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->GetAttributeAsInteger (pName, pNamespace);
}
unsigned long Call::GetAttributeAsUnsignedLong (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsUnsignedLong (pName, pNamespace);
}

float Call::GetAttributeAsFloat (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsFloat (pName, pNamespace);
}

double Call::GetAttributeAsDouble (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsDouble (pName, pNamespace);
}

double Call::GetAttributeAsDecimal (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsDecimal (pName, pNamespace);
}

AxisChar* Call::GetAttributeAsString (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsString (pName, pNamespace);
}

AxisChar* Call::GetAttributeAsAnyURI (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsAnyURI (pName, pNamespace);
}

AxisChar* Call::GetAttributeAsQName (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsQName (pName, pNamespace);
}

xsd__hexBinary Call::GetAttributeAsHexBinary (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsHexBinary (pName, pNamespace);
}

xsd__base64Binary Call::GetAttributeAsBase64Binary (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->GetAttributeAsBase64Binary (pName, pNamespace);
}
struct tm Call::GetAttributeAsDateTime (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->GetAttributeAsDateTime (pName, pNamespace);
}
struct tm Call::GetAttributeAsDate (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsDate (pName, pNamespace);
}
struct tm Call::GetAttributeAsTime (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsTime (pName, pNamespace);
}

long Call::GetAttributeAsDuration (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetAttributeAsDuration (pName, pNamespace);
}

int Call::CheckMessage (const AxisChar* pName, const AxisChar* pNamespace)
{
	 m_nStatus = m_pIWSDZ->CheckMessageBody (pName, pNamespace);
    return m_nStatus;
}

void* Call::GetCmplxObject (void* pDZFunct, void* pCreFunct, void* pDelFunct,
    const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->GetCmplxObject (pDZFunct, pCreFunct, pDelFunct, pName,
        pNamespace);
}

/* global function to be used in C stubs */
extern "C" void* GetStubObject (AXIS_PROTOCOL_TYPE nProtocol, 
    AxisChar* pchEndpointURI)
{
    Call_C* pCall = (Call_C*) malloc (sizeof (Call_C));
    pCall->_object = new Call ();
    pCall->_functions = &Call::ms_VFtable;
    ((Call*) pCall->_object)->SetProtocol (nProtocol);
    ((Call*) pCall->_object)->SetEndpointURI (pchEndpointURI);
    return pCall;
}

extern "C" void DestroyStubObject (void* pCall)
{
    Call* pObject = (Call*) ((Call_C*)pCall)->_object;
    delete pObject;
    free (pCall);
}

int Call::SetSoapHeader (SoapHeader* pSoapHeader)
{
	m_nStatus = (m_pIWSSZ->setSoapHeader (pSoapHeader));
    return m_nStatus;
}

IHeaderBlock* Call::createHeaderBlock ()
{
    return (m_pIWSSZ->createHeaderBlock ());
}

IHeaderBlock* Call::createHeaderBlock (AxisChar* pachLocalName, 
    AxisChar* pachPrefix, AxisChar* pachUri)
{
    return (m_pIWSSZ->createHeaderBlock (pachLocalName, pachPrefix, pachUri));
}

int Call::GetStatus() 
{
	return m_nStatus;
}
