/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 * @author Sanjaya Singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

// Call.cpp: implementation of the Call class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/client/Call.h>
#include <axis/common/AxisConfig.h>
#include <axis/client/transport/AxisTransport.h>
#include <axis/client/transport/axis/Channel.hpp>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern "C" int initialize_module(int bServer);

Call::Call()
{
	m_pAxisEngine = NULL;
	m_pMsgData = NULL;
	m_pIWSSZ = NULL;
	m_pIWSDZ = NULL;
	initialize_module(0);
	m_pTransport = NULL;
}

Call::~Call()
{
	switch(m_Soap.trtype)
	{
	case APTHTTP:
		delete m_Soap.so.http;
		/* do for other protocols too */
	}
}

int Call::SetEndpointURI(const char *pchEndpointURI)
{
	m_Soap.so.http->uri_path = pchEndpointURI;
	return AXIS_SUCCESS;
}

void Call::SetOperation(const char *pchOperation, const char* pchNamespace)
{
	m_pIWSSZ->createSoapMethod(pchOperation, m_pIWSSZ->getNewNamespacePrefix(), pchNamespace);
}

void Call::AddParameter(int nValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, nValue, nType);
}

void Call::AddParameter(unsigned int unValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, unValue, nType);
}

void Call::AddParameter(short sValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, sValue, nType);
}

void Call::AddParameter(unsigned short usValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, usValue, nType);
}

void Call::AddParameter(long lValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, lValue, nType);
}

void Call::AddParameter(unsigned long ulValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, ulValue, nType);
}

void Call::AddParameter(char cValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, cValue, nType);
}

void Call::AddParameter(unsigned char ucValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, ucValue, nType);
}

void Call::AddParameter(float fValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, fValue, nType);
}

void Call::AddParameter(double dValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, dValue, nType);
}

void Call::AddParameter(struct tm tValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, tValue, nType);
}

void Call::AddParameter(const AxisChar* pStrValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, pStrValue, nType);
}

void Call::AddParameter(const AxisString& sStrValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, sStrValue.c_str(), nType);	
}

void Call::AddParameter(void* pValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, pValue, nType);
}

/**
 * Method used to add arrays of basic types as parameters
 */
void Call::AddBasicArrayParameter(Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
{
	m_pIWSSZ->AddOutputBasicArrayParam(pArray, nType, pName);
}

void Call::AddCmplxArrayParameter(Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	m_pIWSSZ->AddOutputCmplxArrayParam(pArray, pSZFunct, pDelFunct, pSizeFunct, pName, pNamespace);
}

void Call::AddCmplxParameter(void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	m_pIWSSZ->AddOutputCmplxParam(pObject, pSZFunct, pDelFunct, pName, pNamespace);
}

int Call::Invoke()
{
	return m_pAxisEngine->Process(&m_Soap);
}

int Call::Initialize(AXIS_BINDING_STYLE nStyle)
{
	/* 
	   Initialize re-usable objects of this instance (objects may have been populated by
	   the previous call.
	 */
	try {
		m_Soap.sessionid = "somesessionid1234";
		//remove_headers(&m_Soap);
		if (AXIS_SUCCESS != OpenConnection()) return AXIS_FAIL;
		if (m_pAxisEngine) delete m_pAxisEngine;
		m_pAxisEngine = new ClientAxisEngine();
		if (!m_pAxisEngine) return AXIS_FAIL;
		if (AXIS_SUCCESS == m_pAxisEngine->Initialize())
		{
			m_pMsgData = m_pAxisEngine->GetMessageData();
			if (m_pMsgData)
			{
				m_pMsgData->GetSoapSerializer((IWrapperSoapSerializer**)(&m_pIWSSZ));
				m_pMsgData->GetSoapDeSerializer((IWrapperSoapDeSerializer**)(&m_pIWSDZ));
				if (m_pIWSSZ && m_pIWSDZ)
				{
					m_pIWSSZ->SetStyle(nStyle);
					m_pIWSDZ->SetStyle(nStyle);
					return AXIS_SUCCESS;
				}
			}
			return AXIS_FAIL;
		}
		return AXIS_FAIL;
	}
	catch (ChannelException e)
	{
		/*printf(e.GetErr().c_str());*/
		return AXIS_FAIL;
	}
	catch (...)
	{
		/*printf("Unknown exception occured in the client");*/
		return AXIS_FAIL;
	}
}

int Call::UnInitialize()
{
	if (m_pAxisEngine) 
	{
		m_pAxisEngine->UnInitialize();
		delete m_pAxisEngine;
		m_pAxisEngine = NULL;
	}
	CloseConnection();
	return AXIS_SUCCESS;
}

int Call::SetProtocol(AXIS_PROTOCOL_TYPE protocol)
{
	m_Soap.trtype = protocol;
	switch(protocol)
	{
	case APTHTTP:
		m_Soap.so.http = new Ax_stream_http; 
		m_Soap.so.http->ip_headercount = 0;
		m_Soap.so.http->ip_headers = NULL;
		m_Soap.so.http->op_headercount = 0;
		m_Soap.so.http->op_headers = NULL;
		break;
		/* do for other protocols too */
	}
	return 0;
}

int Call::SetTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
{
	m_pTransport->SetTransportInformation(type, value, &m_Soap);
	return 0;
}

/**
 * This method takes a look at the m_Soap structure and open 
 * transport layer connection to the server. Then this adds the 
 * relevant function pointers and streams to the m_Soap structure, 
 * which is given to the AxisEngine. AxisEngine can use those 
 * functions with those streams at any time it wants to send/receive
 * bytes to/from the server.
 */
int Call::OpenConnection()
{ 
    m_pTransport = new AxisTransport(&m_Soap);
    return m_pTransport->OpenConnection();
}

/**
 * This method closes the connection of this object to the server
 */
void Call::CloseConnection()
{
    m_pTransport->CloseConnection();
	delete m_pTransport;
}

void Call::SetSOAPVersion(SOAP_VERSION version)
{
	m_pIWSSZ->setSoapVersion(version);
}

Axis_Array Call::GetBasicArray(XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetBasicArray(nType, pName, pNamespace);
}

Axis_Array Call::GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetCmplxArray(pDZFunct, pCreFunct, pDelFunct, pSizeFunct, pName, pNamespace);
}

int Call::GetElementAsInt(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsInt(pName, pNamespace);
}
unsigned int Call::GetElementAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsUnsignedInt(pName, pNamespace);
}
short Call::GetElementAsShort(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsShort(pName, pNamespace);
}
unsigned short Call::GetElementAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsUnsignedShort(pName, pNamespace);
}
char Call::GetElementAsByte(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsByte(pName, pNamespace);
}
unsigned char Call::GetElementAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsUnsignedByte(pName, pNamespace);
}
long Call::GetElementAsLong(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsLong(pName, pNamespace);
}
long Call::GetElementAsInteger(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsInteger(pName, pNamespace);
}
unsigned long Call::GetElementAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsUnsignedLong(pName, pNamespace);
}
float Call::GetElementAsFloat(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsFloat(pName, pNamespace);
}
double Call::GetElementAsDouble(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsDouble(pName, pNamespace);
}
double Call::GetElementAsDecimal(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsDecimal(pName, pNamespace);
}
AxisChar* Call::GetElementAsString(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsString(pName, pNamespace);
}
AxisChar* Call::GetElementAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsAnyURI(pName, pNamespace);
}
AxisChar* Call::GetElementAsQName(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsQName(pName, pNamespace);
}
AxisChar* Call::GetElementAsHexString(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsHexString(pName, pNamespace);
}
AxisChar* Call::GetElementAsBase64String(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsBase64String(pName, pNamespace);
}
struct tm Call::GetElementAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsDateTime(pName, pNamespace);
}
struct tm Call::GetElementAsDate(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsDate(pName, pNamespace);
}
struct tm Call::GetElementAsTime(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsTime(pName, pNamespace);
}
long Call::GetElementAsDuration(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetElementAsDuration(pName, pNamespace);
}
int Call::CheckMessage(const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->CheckMessageBody(pName, pNamespace);
}
void* Call::GetCmplxObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	return m_pIWSDZ->GetCmplxObject(pDZFunct, pCreFunct, pDelFunct, pName, pNamespace);
}

/*global function to be used in C stubs */
extern "C" Call* GetCallObject(AXIS_PROTOCOL_TYPE nProtocol, AxisChar* pchEndpointURI)
{
	Call* pCall = new Call();
	pCall->SetProtocol(nProtocol);
	pCall->SetEndpointURI(pchEndpointURI);
	return pCall;
}

