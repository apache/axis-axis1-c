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
	m_nReturnType = XSD_UNKNOWN;
	m_nArrayType = XSD_UNKNOWN;
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

/**
 * Method used to add arrays of basic types as parameters
 */
void Call::AddParameter(Axis_Array* pArray, XSDTYPE nType)
{
	IArrayBean* pAb = m_pIWSSZ->makeArrayBean(nType, (void*)(pArray->m_Array));
	pAb->AddDimension(pArray->m_Size);
	pAb->SetItemName("item");
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pAb);
}

void Call::AddParameter(Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const char* pchTypeName)
{
	IArrayBean* pAb = m_pIWSSZ->makeArrayBean((void*)(pArray->m_Array), pSZFunct, pDelFunct, pDelFunct);
	pAb->AddDimension(pArray->m_Size);
	pAb->SetItemName("item");
	pAb->SetTypeName(pchTypeName);
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pAb);
	pRetParam->SetName(pchTypeName);
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

void Call::SetReturnType(void *pDZFunct, void* pCreFunct, void *pDelFunct, const char* pchTypeName, const char * pchUri)
{
	m_nReturnType = USER_TYPE;
	m_ReturnCplxObj.pObject = NULL;
	m_ReturnCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
	m_ReturnCplxObj.pCreFunct = (AXIS_OBJECT_CREATE_FUNCT)pCreFunct;
	m_ReturnCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
	m_ReturnCplxObj.m_TypeName = pchTypeName;
	m_ReturnCplxObj.m_URI = pchUri;
}

/**
 * This function is used to set that the return type is an array of complex types
 */
void Call::SetReturnType(Axis_Array* pArray, void* pDZFunct, void* pCreFunct, void* pDelFunct, const char* pchTypeName, const char* pchUri)
{
	m_pArray = pArray;
	m_nReturnType = XSD_ARRAY;
	m_nArrayType = USER_TYPE;
	m_ReturnCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
	m_ReturnCplxObj.pCreFunct = (AXIS_OBJECT_CREATE_FUNCT)pCreFunct;
	m_ReturnCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
	m_ReturnCplxObj.m_TypeName = pchTypeName;
	m_ReturnCplxObj.m_URI = pchUri;
}

/**
 * This function is used to set that the return type is an array of basic types.
 * @param pArray Array to which the deserialized object array is set an returned
 *				 to the client application.
 * @param nType Basic type of the array elements
 */
void Call::SetReturnType(Axis_Array* pArray, XSDTYPE nType)
{
	m_pArray = pArray;
	m_nReturnType = XSD_ARRAY;
	m_nArrayType = nType;
}

int Call::Invoke()
{
	int nStatus;
	Param *pParam = NULL;
	if (SUCCESS == (nStatus = m_pAxisEngine->Process(&m_Soap)))
	{
		if (USER_TYPE == m_nReturnType)
		{
			/*
			The second element of the soap message (after the method element) 
			is taken as a parameter. But if it is a custom type remove the 
			wrapper element that describes the type. Optionally you can check
			whether the returned type is of expected type.
			on the deserializer before getting the actual params
			*/
			pParam = (Param*)m_pIWSDZ->GetParam();
			/*
			Following lines check whether the returned type is expected type or not.
			But this type checking is optional. So commented.
			if (pParam && (m_ReturnCplxObj.m_TypeName == pParam->GetTypeName()))
			{
				m_ReturnCplxObj.pDZFunct(m_ReturnCplxObj.pObject, m_pMsgData->m_pDZ);
			}
			else
			{
				return FAIL;
			}
			*/
			if (!m_ReturnCplxObj.pCreFunct || !m_ReturnCplxObj.pDZFunct)
				return FAIL; 
			m_ReturnCplxObj.pObject = m_ReturnCplxObj.pCreFunct();
			if (!m_ReturnCplxObj.pObject)
				return FAIL;
			m_ReturnCplxObj.pDZFunct(m_ReturnCplxObj.pObject, m_pMsgData->m_pDZ);

		}
		else if (XSD_ARRAY == m_nReturnType)
		{
			IParam *param0 = m_pIWSDZ->GetParam(); 
			/* now we know that this is an array. if needed we can check that too */
			if (!m_pArray) return FAIL; //No array expected ?
			m_pArray->m_Size = param0->GetArraySize();
			if (m_pArray->m_Size > 0)
			{
				if (SUCCESS == MakeArray()) //Array is allocated successfully
				{
					if (USER_TYPE == m_nArrayType)
						param0->SetArrayElements((void*)(m_pArray->m_Array), m_ReturnCplxObj.pDZFunct, m_ReturnCplxObj.pDelFunct, m_ReturnCplxObj.pSizeFunct);
					else
						param0->SetArrayElements((void*)(m_pArray->m_Array));
					m_pIWSDZ->Deserialize(param0,0);
				}
			}
			else 
				return FAIL; //CF_ZERO_ARRAY_SIZE_ERROR
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

void Call::GetResult(void** pReturn)
{
	if (m_ReturnCplxObj.pObject)
	{
		*pReturn = m_ReturnCplxObj.pObject;
		m_ReturnCplxObj.pObject = NULL; //note that returned object is handed over to the client.
	}
	else
	{
		*pReturn = NULL;
	}
}

int Call::Initialize()
{
	/* 
	   Initialize re-usable objects of this instance (objects may have been populated by
	   the previous call.
	 */
	InitializeObjects();
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

void Call::InitializeObjects()
{
	m_nReturnType = XSD_UNKNOWN;
	m_pArray = NULL;
	m_nArrayType = XSD_UNKNOWN;
	m_ReturnCplxObj.m_TypeName = "";
	m_ReturnCplxObj.m_URI = "";
	m_ReturnCplxObj.pCreFunct = NULL;
	m_ReturnCplxObj.pDelFunct = NULL;
	m_ReturnCplxObj.pObject = NULL;
	m_ReturnCplxObj.pSizeFunct = NULL;
	m_ReturnCplxObj.pSZFunct = NULL;
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

/**
 * This function will create (allocate memory) to an array of objects depending on
 * the information available in m_pArray and m_nArrayType. Basically it gets the 
 * array size from m_pArray->m_Size and element type from m_nArrayType. In case of 
 * complex types it uses the Create function provided in m_ReturnCplxObj structure
 */
int Call::MakeArray()
{
	if (USER_TYPE == m_nArrayType)
	{
		m_pArray->m_Array = m_ReturnCplxObj.pCreFunct(true, m_pArray->m_Size);
	}
	else
	{
		switch (m_nArrayType)
		{
		case XSD_INT:
		case XSD_UNSIGNEDINT:
			m_pArray->m_Array = new int[m_pArray->m_Size];
			break;
		case XSD_FLOAT:
			m_pArray->m_Array = new float[m_pArray->m_Size];
			break;
		case XSD_STRING:
		case XSD_HEXBINARY:
		case XSD_BASE64BINARY:
		case XSD_ANYURI:
		case XSD_QNAME:
		case XSD_NOTATION:
			m_pArray->m_Array = new AxisString[m_pArray->m_Size];
			break;
		case XSD_LONG:
		case XSD_UNSIGNEDLONG:
		case XSD_INTEGER:
		case XSD_DURATION:
			m_pArray->m_Array = new long[m_pArray->m_Size];
			break;
		case XSD_SHORT:
		case XSD_UNSIGNEDSHORT:
			m_pArray->m_Array = new short[m_pArray->m_Size];
			break;
		case XSD_BYTE:
		case XSD_UNSIGNEDBYTE:
			m_pArray->m_Array = new char[m_pArray->m_Size];
			break;
		case XSD_DOUBLE:
		case XSD_DECIMAL:
			m_pArray->m_Array = new double[m_pArray->m_Size];
			break;
		case XSD_DATETIME:
		case XSD_TIME:
		case XSD_DATE:
		case XSD_YEARMONTH:
		case XSD_YEAR:
		case XSD_MONTHDAY:
		case XSD_DAY:
		case XSD_MONTH:
			m_pArray->m_Array = new tm[m_pArray->m_Size];
			break;
		default:
			return FAIL;
		}
	}
	return SUCCESS;
}