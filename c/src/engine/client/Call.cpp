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

extern "C" int initialize_module(int bServer, const char * wsddPath);

Call::Call()
{
	m_pAxisEngine = NULL;
	m_pMsgData = NULL;
	m_pIWSSZ = NULL;
	m_pIWSDZ = NULL;
	m_Soap.so.http.ip_headercount = 0;
	m_Soap.so.http.ip_headers = NULL;
	initialize_module(0, "");
	m_pTransport = NULL;
	m_nReturnType = XSD_UNKNOWN;
	m_nArrayType = XSD_UNKNOWN;
	m_pReturnValue = NULL;
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

/**
 * Method used to add arrays of basic types as parameters
 */
void Call::AddBasicArrayParameter(Axis_Array* pArray, XSDTYPE nType, const char* pchName)
{
	m_pIWSSZ->AddOutputParam(pchName, pArray, nType);
}

void Call::AddCmplxArrayParameter(Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const char* pchTypeName, const char* pchURI, const char* pchName)
{
	m_pIWSSZ->AddOutputCmplxArrayParam(pchName, pArray, pSZFunct, pDelFunct, pSizeFunct, pchTypeName, pchURI);
}

void Call::AddCmplxParameter(void *pObject, void *pSZFunct, void *pDelFunct, const char* pchName)
{
	m_pIWSSZ->AddOutputCmplxParam(pchName, pObject, pSZFunct, pDelFunct);
}

/**
 * This function is used to set that the return type is a basic type
 */
void Call::SetReturnType(XSDTYPE nType)
{
	m_nReturnType = nType;
}

/**
 * This function is used to set that the return type is a complex type
 */
void Call::SetCmplxReturnType(void *pDZFunct, void* pCreFunct, void *pDelFunct, const char* pchTypeName, const char * pchUri)
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
void Call::SetCmplxArrayReturnType(Axis_Array* pArray, void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const char* pchTypeName, const char* pchUri)
{
	m_pArray = pArray;
	m_nReturnType = XSD_ARRAY;
	m_nArrayType = USER_TYPE;
	m_ReturnCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
	m_ReturnCplxObj.pCreFunct = (AXIS_OBJECT_CREATE_FUNCT)pCreFunct;
	m_ReturnCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
	m_ReturnCplxObj.pSizeFunct = (AXIS_OBJECT_SIZE_FUNCT)pSizeFunct;
	m_ReturnCplxObj.m_TypeName = pchTypeName;
	m_ReturnCplxObj.m_URI = pchUri;
}

/**
 * This function is used to set that the return type is an array of basic types.
 * @param pArray Array to which the deserialized object array is set an returned
 *				 to the client application.
 * @param nType Basic type of the array elements
 */
void Call::SetBasicArrayReturnType(Axis_Array* pArray, XSDTYPE nType)
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
		//Get return type if it returns
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
			m_ReturnCplxObj.pObject = m_ReturnCplxObj.pCreFunct(false, 0);
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
			if (SUCCESS == MakeArray()) //Array is allocated successfully
			{
				if (USER_TYPE == m_nArrayType)
					param0->SetArrayElements((void*)(m_pArray->m_Array), m_ReturnCplxObj.pDZFunct, m_ReturnCplxObj.pDelFunct, m_ReturnCplxObj.pSizeFunct);
				else
					param0->SetArrayElements((void*)(m_pArray->m_Array));
				m_pIWSDZ->Deserialize(param0,0);
			}
			else 
				return FAIL; //CF_ZERO_ARRAY_SIZE_ERROR
		}
		else if (XSD_UNKNOWN != m_nReturnType)//basic type
		{
			m_pReturnValue = (Param*)m_pIWSDZ->GetParam();
		}
		else if (!m_OutParams.empty()) //there are out parameters
		{
			OutParamHolder* pOutParam = NULL;
			// do for each parameter.
			for (list<OutParamHolder*>::iterator it = m_OutParams.begin(); it != m_OutParams.end(); it++)
			{
				pOutParam = (*it);
				if (USER_TYPE == pOutParam->m_nOutType)
				{
					/*
					If it is a custom type remove the wrapper element that describes 
					the type. Optionally you can check whether the returned type is of expected type
					*/
					pParam = (Param*)m_pIWSDZ->GetParam();
					/*
					Following lines check whether the returned type is expected type or not.
					But this type checking is optional. So commented.
					if (pParam && (pOutParam->m_OutCplxObj.m_TypeName == pParam->GetTypeName()))
					{
						pOutParam->m_OutCplxObj.pDZFunct(pOutParam->m_OutCplxObj.pObject, m_pMsgData->m_pDZ);
					}
					else
					{
						return FAIL;
					}
					*/
					if (!pOutParam->m_OutCplxObj.pCreFunct || !pOutParam->m_OutCplxObj.pDZFunct)
						return FAIL; 
					pOutParam->m_OutCplxObj.pObject = pOutParam->m_OutCplxObj.pCreFunct(false, 0);
					if (!pOutParam->m_OutCplxObj.pObject)
						return FAIL;
					pOutParam->m_OutCplxObj.pDZFunct(pOutParam->m_OutCplxObj.pObject, m_pMsgData->m_pDZ);

				}
				else if (XSD_ARRAY == pOutParam->m_nOutType)
				{
					IParam *param0 = m_pIWSDZ->GetParam(); 
					/* now we know that this is an array. if needed we can check that too */
					if (!pOutParam->m_pArray) return FAIL; //No array expected ?
					pOutParam->m_pArray->m_Size = param0->GetArraySize();
					if (pOutParam->m_pArray->m_Size < 1) return FAIL;
					if (USER_TYPE == pOutParam->m_nArrayType)
					{
						pOutParam->m_pArray->m_Array = pOutParam->m_OutCplxObj.pCreFunct(true, pOutParam->m_pArray->m_Size);
					}
					else
					{
						pOutParam->m_pArray->m_Array = m_pIWSDZ->CreateArray(pOutParam->m_nArrayType, pOutParam->m_pArray->m_Size); 
					}
					if (pOutParam->m_pArray->m_Array) //Array is allocated successfully
					{
						if (USER_TYPE == pOutParam->m_nArrayType)
							param0->SetArrayElements((void*)(pOutParam->m_pArray->m_Array), pOutParam->m_OutCplxObj.pDZFunct, pOutParam->m_OutCplxObj.pDelFunct, pOutParam->m_OutCplxObj.pSizeFunct);
						else
							param0->SetArrayElements((void*)(pOutParam->m_pArray->m_Array));
						m_pIWSDZ->Deserialize(param0,0);
					}
					else 
						return FAIL; //CF_ZERO_ARRAY_SIZE_ERROR
				}
				else if (XSD_UNKNOWN != pOutParam->m_nOutType)//basic type
				{
					pOutParam->m_pOutValue = (Param*)m_pIWSDZ->GetParam();
				}
				else // this is an unexpected situation
				{
					return FAIL;
				}			
			}
		}
		else //returns void
		{
			//nothing to do
		}
	}
	return nStatus;
}

/**
 * Used to get the corresponding Param when the return type is basic type
 */
Param* Call::GetResult()
{
	return m_pReturnValue;
}

/**
 * Used to get deserialized return object when the return type is complex type
 */
void Call::GetCmplxResult(void** pReturn)
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
	try {
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
			return FAIL;
		}
		return FAIL;
	}
	catch (ChannelException e)
	{
		printf(e.GetErr().c_str());
		return FAIL;
	}
	catch (...)
	{
		printf("Unknown exception occured in the client");
		return FAIL;
	}
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
	m_CurItr = NULL;
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
	if (m_pArray->m_Size < 1) return FAIL;

	if (USER_TYPE == m_nArrayType)
	{
		m_pArray->m_Array = m_ReturnCplxObj.pCreFunct(true, m_pArray->m_Size);
	}
	else
	{
		m_pArray->m_Array = m_pIWSDZ->CreateArray(m_nArrayType, m_pArray->m_Size); 
	}
	return (NULL != m_pArray->m_Array)?SUCCESS:FAIL;
}

Call::OutParamHolder::OutParamHolder()
{
	m_nOutType = XSD_UNKNOWN;
	m_nArrayType = XSD_UNKNOWN;
	m_pArray = NULL;
	m_pOutValue = NULL;
}

Call::OutParamHolder::~OutParamHolder()
{

}

Call::OutParamHolder* Call::AddOutParam()
{
	OutParamHolder* pNew = new OutParamHolder();
	if (pNew)
		m_OutParams.push_back(pNew);
	return pNew;
}

/**
 * This function is used to set that the return type is a basic type
 */
void Call::AddOutParamType(XSDTYPE nType)
{
	OutParamHolder* pOPH = AddOutParam();
	if (pOPH)
	{
		pOPH->m_nOutType = nType;
	}
}

/**
 * This function is used to set that the return type is a complex type
 */
void Call::AddCmplxOutParamType(void *pDZFunct, void* pCreFunct, void *pDelFunct, const char* pchTypeName, const char * pchUri)
{
	OutParamHolder* pOPH = AddOutParam();
	if (pOPH)
	{
		pOPH->m_nOutType = USER_TYPE;
		pOPH->m_OutCplxObj.pObject = NULL;
		pOPH->m_OutCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
		pOPH->m_OutCplxObj.pCreFunct = (AXIS_OBJECT_CREATE_FUNCT)pCreFunct;
		pOPH->m_OutCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
		pOPH->m_OutCplxObj.m_TypeName = pchTypeName;
		pOPH->m_OutCplxObj.m_URI = pchUri;
	}
}

/**
 * This function is used to set that the return type is an array of complex types
 */
void Call::AddCmplxArrayOutParamType(Axis_Array* pArray, void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const char* pchTypeName, const char* pchUri)
{
	OutParamHolder* pOPH = AddOutParam();
	if (pOPH)
	{
		pOPH->m_pArray = pArray;
		pOPH->m_nOutType = XSD_ARRAY;
		pOPH->m_nArrayType = USER_TYPE;
		pOPH->m_OutCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
		pOPH->m_OutCplxObj.pCreFunct = (AXIS_OBJECT_CREATE_FUNCT)pCreFunct;
		pOPH->m_OutCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
		pOPH->m_OutCplxObj.pSizeFunct = (AXIS_OBJECT_SIZE_FUNCT)pSizeFunct;
		pOPH->m_OutCplxObj.m_TypeName = pchTypeName;
		pOPH->m_OutCplxObj.m_URI = pchUri;
	}
}

/**
 * This function is used to set that the return type is an array of basic types.
 * @param pArray Array to which the deserialized object array is set an returned
 *				 to the client application.
 * @param nType Basic type of the array elements
 */
void Call::AddBasicArrayOutParamType(Axis_Array* pArray, XSDTYPE nType)
{
	OutParamHolder* pOPH = AddOutParam();
	if (pOPH)
	{
		pOPH->m_pArray = pArray;
		pOPH->m_nOutType = XSD_ARRAY;
		pOPH->m_nArrayType = nType;
	}
}

/**
 * Used to get the corresponding Param when the out param type is basic type
 */
Param* Call::GetOutParam()
{
	if (m_CurItr == NULL) m_CurItr = m_OutParams.begin();
	else m_CurItr++;
	if (m_CurItr == m_OutParams.end()) return NULL; //something wrong
	OutParamHolder* pOutParam = (*m_CurItr);
	return pOutParam->m_pOutValue;
}

/**
 * Used to get the deserialized object when the out param type is of complex type
 */
void Call::GetCmplxOutParam(void** pOut)
{
	if (m_CurItr == NULL) m_CurItr = m_OutParams.begin();
	else m_CurItr++;
	if (m_CurItr == m_OutParams.end()) return; //something wrong
	OutParamHolder* pOutParam = (*m_CurItr);
	if (pOutParam->m_OutCplxObj.pObject)
	{
		*pOut = pOutParam->m_OutCplxObj.pObject;
		pOutParam->m_OutCplxObj.pObject = NULL; //note that returned object is handed over to the client.
	}
	else
	{
		*pOut = NULL;
	}
}

void AXISCALL Call::AddParameter(void* pValue,const char* pchName, XSDTYPE nType)
{
	m_pIWSSZ->AddOutputParam(pchName, pValue, nType);
}

int Call::GetInt()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetInt();
}
unsigned int Call::GetUnsignedInt()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetUnsignedInt();
}
short Call::GetShort()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetShort();
}
unsigned short Call::GetUnsignedShort()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetUnsignedShort();
}
char Call::GetByte()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetByte();
}
unsigned char Call::GetUnsignedByte()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetUnsignedByte();
}
long Call::GetLong()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetLong();
}
long Call::GetInteger()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetInteger();
}
unsigned long Call::GetUnsignedLong()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetUnsignedLong();
}
float Call::GetFloat()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetFloat();
}
double Call::GetDouble()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetDouble();
}
double Call::GetDecimal()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetDecimal();
}
const AxisChar* Call::GetString()
{
	if (!m_pReturnValue) return NULL; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetString();
}
const AxisChar* Call::GetAnyURI()
{
	if (!m_pReturnValue) return NULL; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetAnyURI();
}
const AxisChar* Call::GetQName()
{
	if (!m_pReturnValue) return NULL; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetQName();
}
const AxisChar* Call::GetHexString()
{
	if (!m_pReturnValue) return NULL; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetHexString();
}
const AxisChar* Call::GetBase64String()
{
	if (!m_pReturnValue) return NULL; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetBase64String();
}
struct tm Call::GetDateTime()
{
	return m_pReturnValue->GetDateTime();
}
struct tm Call::GetDate()
{
	return m_pReturnValue->GetDate();
}
struct tm Call::GetTime()
{
	return m_pReturnValue->GetTime();
}
long Call::GetDuration()
{
	if (!m_pReturnValue) return 0; //TODO this is an error situation. Should be handled.
	return m_pReturnValue->GetDuration();
}

/* Methods used by stubs to get a deserialized value of basic type out params */
int Call::GetIntOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetInt();
}
unsigned int Call::GetUnsignedIntOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetUnsignedInt();
}
short Call::GetShortOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetShort();
}
unsigned short Call::GetUnsignedShortOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetUnsignedShort();
}
char Call::GetByteOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetByte();
}
unsigned char Call::GetUnsignedByteOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetUnsignedByte();
}
long Call::GetLongOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetLong();
}
long Call::GetIntegerOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetInteger();
}
unsigned long Call::GetUnsignedLongOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetUnsignedLong();
}
float Call::GetFloatOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetFloat();
}
double Call::GetDoubleOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetDouble();
}
double Call::GetDecimalOutParam()
{
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetDecimal();
}
const AxisChar* Call::GetStringOutParam()
{
	Param* param = GetOutParam();
	if (!param) return NULL; //TODO this is an error situation. Should be handled.
	return param->GetString();
}
const AxisChar* Call::GetAnyURIOutParam()
{
	Param* param = GetOutParam();
	if (!param) return NULL; //TODO this is an error situation. Should be handled.
	return param->GetAnyURI();
}
const AxisChar* Call::GetQNameOutParam()
{
	Param* param = GetOutParam();
	if (!param) return NULL; //TODO this is an error situation. Should be handled.
	return param->GetQName();
}
const AxisChar* Call::GetHexStringOutParam()
{
	Param* param = GetOutParam();
	if (!param) return NULL; //TODO this is an error situation. Should be handled.
	return param->GetHexString();
}
const AxisChar* Call::GetBase64StringOutParam()
{
	Param* param = GetOutParam();
	if (!param) return NULL; //TODO this is an error situation. Should be handled.
	return param->GetBase64String();
}
struct tm Call::GetDateTimeOutParam()
{
	struct tm zero;
	Param* param = GetOutParam();
	if (!param) return zero; //TODO this is an error situation. Should be handled.
	return param->GetDateTime();
}
struct tm Call::GetDateOutParam()
{
	struct tm zero;
	Param* param = GetOutParam();
	if (!param) return zero; //TODO this is an error situation. Should be handled.
	return param->GetDate();
}
struct tm Call::GetTimeOutParam()
{
	struct tm zero;
	Param* param = GetOutParam();
	if (!param) return zero; //TODO this is an error situation. Should be handled.
	return param->GetTime();
}
long Call::GetDurationOutParam()
{
	struct tm zero;
	Param* param = GetOutParam();
	if (!param) return 0; //TODO this is an error situation. Should be handled.
	return param->GetDuration();
}