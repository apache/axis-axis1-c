// Copyright 2003-2004 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

///////////////////////////////////////////////////////////////////////
// This is the Client Stub implementation file genarated by WSDL2Ws tool.
// InteropTestPortType.cpp: implemtation for the InteropTestPortType.
//
//////////////////////////////////////////////////////////////////////

#include "InteropTestPortType.h"

#include <axis/AxisWrapperAPI.hpp>

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(void* pObj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

InteropTestPortType::InteropTestPortType(const char* pchEndPointUri)
{
	m_pCall = new Call();
	m_pCall->setProtocol(APTHTTP1_1);
	m_pCall->setEndpointURI(pchEndPointUri);
}

InteropTestPortType::~InteropTestPortType()
{
	delete m_pCall;
}


//Methods corresponding to the web service methods

/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoString
//////////////////////////////////////////////////////////////////
AxisChar* InteropTestPortType::echoString(AxisChar* Value0)
{
	int nStatus;
	AxisChar* Ret = '\0';
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoString");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoString", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputString", XSD_STRING);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoStringResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsString("echoStringReturn",0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStringArray
//////////////////////////////////////////////////////////////////
ArrayOfstring InteropTestPortType::echoStringArray(ArrayOfstring Value0)
{
	int nStatus;
	ArrayOfstring RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoStringArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStringArray", "http://soapinterop.org/");
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoStringArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOfstring&) m_pCall->getBasicArray(XSD_STRING,"echoStringArrayReturn",0);
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoInteger
//////////////////////////////////////////////////////////////////
int InteropTestPortType::echoInteger(int Value0)
{
	int nStatus;
	int Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoInteger");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoInteger", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputInteger", XSD_INT);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoIntegerResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsInt("echoIntegerReturn",0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoIntegerArray
//////////////////////////////////////////////////////////////////
ArrayOfint InteropTestPortType::echoIntegerArray(ArrayOfint Value0)
{
	int nStatus;
	ArrayOfint RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoIntegerArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoIntegerArray", "http://soapinterop.org/");
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoIntegerArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOfint&) m_pCall->getBasicArray(XSD_INT,"echoIntegerArrayReturn",0);
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoFloat
//////////////////////////////////////////////////////////////////
float InteropTestPortType::echoFloat(float Value0)
{
	int nStatus;
	float Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoFloat");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoFloat", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoFloatResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsFloat("echoFloatReturn",0);
		}
		else /* probably a fault returned */ 
		{
			
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoFloatArray
//////////////////////////////////////////////////////////////////
ArrayOffloat InteropTestPortType::echoFloatArray(ArrayOffloat Value0)
{
	int nStatus;
	ArrayOffloat RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoFloatArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoFloatArray", "http://soapinterop.org/");
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoFloatArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOffloat&)m_pCall->getBasicArray(XSD_FLOAT,"echoFloatArrayReturn",0);
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStruct
//////////////////////////////////////////////////////////////////
SOAPStruct* InteropTestPortType::echoStruct(SOAPStruct* Value0)
{
	int nStatus;
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoStruct");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStruct", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, "structInput", "");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, "structReturn", "");
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStructArray
//////////////////////////////////////////////////////////////////
ArrayOfSOAPStruct InteropTestPortType::echoStructArray(ArrayOfSOAPStruct Value0)
{
	int nStatus;
	ArrayOfSOAPStruct RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoStructArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStructArray", "http://soapinterop.org/");
	m_pCall->addCmplxArrayParameter((Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "structArray", "");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoStructArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOfSOAPStruct&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "structArrayReturn", "");
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoVoid
//////////////////////////////////////////////////////////////////
void InteropTestPortType::echoVoid()
{
	int nStatus;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoVoid");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoVoid", "http://soapinterop.org/");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS != m_pCall->checkMessage("echoVoidResponse", "http://soapinterop.org/"))
		{
			/* not successfull */
		}
	}
	m_pCall->unInitialize();
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoBase64
//////////////////////////////////////////////////////////////////
xsd__base64Binary InteropTestPortType::echoBase64(xsd__base64Binary Value0)
{
	int nStatus;
	xsd__base64Binary Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoBase64");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoBase64", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputBase64", XSD_BASE64BINARY);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoBase64Response", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsBase64Binary("echoBase64Return",0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoDate
//////////////////////////////////////////////////////////////////
xsd__dateTime InteropTestPortType::echoDate(xsd__dateTime Value0)
{
	int nStatus;
	xsd__dateTime Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoDate");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoDate", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputDate", XSD_DATETIME);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoDateResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsDateTime("echoDateReturn",0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoHexBinary
//////////////////////////////////////////////////////////////////
xsd__hexBinary InteropTestPortType::echoHexBinary(xsd__hexBinary Value0)
{
	int nStatus;
	xsd__hexBinary Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoHexBinary");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoHexBinary", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoHexBinaryResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsHexBinary("echoHexBinaryReturn",0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoDecimal
//////////////////////////////////////////////////////////////////
xsd__decimal InteropTestPortType::echoDecimal(xsd__decimal Value0)
{
	int nStatus;
	xsd__decimal Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoDecimal");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoDecimal", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputDecimal", XSD_DECIMAL);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoDecimalResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsDecimal("echoDecimalReturn",0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoBoolean
//////////////////////////////////////////////////////////////////
xsd__boolean InteropTestPortType::echoBoolean(xsd__boolean Value0)
{
	int nStatus;
	xsd__boolean Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "baseDL#echoBoolean");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoBoolean", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputBoolean", XSD_BOOLEAN);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoBooleanResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->getElementAsBoolean("echoBooleanReturn",0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}

