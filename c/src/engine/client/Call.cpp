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

#include "Call.h"
#include "../common/AxisConfig.h"
#include "transport/axis/AxisTransport.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern "C" int initialize_module(int bServer, const char * wsddPath);

Call::Call()
{
	m_pAxisEngine = NULL;
	m_pMsgData = NULL;
	m_pIWSSZ = NULL;
	m_pIWSDZ = NULL;
	m_Soap.so.http.ip_headercount = 0;
	m_Soap.so.http.ip_headers = NULL;
	initialize_module(0, WSDDFILEPATH);
	m_pTransport = NULL;
}

Call::~Call()
{

}

int Call::SetEndpointURI(const char *pchEndpointURI)
{
	m_Soap.so.http.uri_path = pchEndpointURI;
	return SUCCESS;
}

void Call::SetOperation(const char *pchOperation, const char* pchNamespace)
{
	ISoapMethod* pMethod= m_pIWSSZ->createSoapMethod();
	pMethod->setLocalName(pchOperation);
	pMethod->setPrefix(m_pIWSSZ->getNewNamespacePrefix());
	pMethod->setUri(pchNamespace);
}

void Call::AddParameter(int nValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(nValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned int unValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(unValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(short sValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(sValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned short usValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(usValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(long lValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(lValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned long ulValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(ulValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(char cValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(cValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned char ucValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(ucValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(float fValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(fValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(double dValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(dValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(struct tm tValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(tValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(const AxisChar* pStrValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pStrValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(IArrayBean *pArrayBean, const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pArrayBean);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(void *pObject, void *pSZFunct, void *pDelFunct, const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pObject, pSZFunct, pDelFunct);
	pRetParam->SetName(pchName);
}

void Call::SetReturnType(XSDTYPE nType)
{
	m_nReturnType = nType;
}

void Call::SetReturnType(void *pObject, void *pDZFunct, void *pDelFunct, const char* pchTypeName, const char * pchUri)
{
	m_nReturnType = USER_TYPE;
	m_ReturnCplxObj.pObject = pObject;
	m_ReturnCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
	m_ReturnCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
	m_ReturnCplxObj.m_TypeName = pchTypeName;
	m_ReturnCplxObj.m_URI = pchUri;
}

int Call::Invoke()
{
	int nStatus;
	Param *pParam = NULL;
	if (SUCCESS == (nStatus = m_pAxisEngine->Process(&m_Soap)))
	{
		if (m_nReturnType == USER_TYPE)
		{
			/*
			The first element of the soap message (after the soap			
			body element) is taken as a parameter itself so that
			the return type can be checked. So need to call GetParam
			on the deserializer before getting the actual params
			*/
			pParam = (Param*)m_pIWSDZ->GetParam();

//			if (pParam && (m_ReturnCplxObj.m_TypeName == pParam->GetTypeName()))
//			{
				m_ReturnCplxObj.pDZFunct(m_ReturnCplxObj.pObject, m_pMsgData->m_pDZ);
//			}
//			else
//			{
//				return FAIL;
//			}

		}
		else if (m_nReturnType == XSD_ARRAY)
		{
			
		}
		else //basic type
		{
			pParam = (Param*)m_pIWSDZ->GetParam();
			if (pParam) m_uReturnValue = pParam->GetValue();
		}
	}
	return nStatus;
}

uParamValue Call::GetResult()
{
	return m_uReturnValue;
}

int Call::Initialize()
{
	m_Soap.sessionid = "somesessionid1234";
	if (SUCCESS != OpenConnection()) return FAIL;
	if (m_pAxisEngine) delete m_pAxisEngine;
	m_pAxisEngine = new ClientAxisEngine();
	if (!m_pAxisEngine) return FAIL;
	if (SUCCESS == m_pAxisEngine->Initialize())
	{
		m_pMsgData = m_pAxisEngine->GetMessageData();
		if (m_pMsgData)
		{
			m_pMsgData->getSoapSerializer((IWrapperSoapSerializer**)(&m_pIWSSZ));
			m_pMsgData->getSoapDeSerializer((IWrapperSoapDeSerializer**)(&m_pIWSDZ));
			if (m_pIWSSZ && m_pIWSDZ)
			{
				return SUCCESS;
			}
		}
		return SUCCESS;
	}
	return FAIL;
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
	return SUCCESS;
}

int Call::SetProtocol(AXIS_PROTOCOL_TYPE protocol)
{
	m_Soap.trtype = protocol;
	return 0;
}

int Call::SetHeader(char *key, char *value)
{
	set_header(&m_Soap, key, value);
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
