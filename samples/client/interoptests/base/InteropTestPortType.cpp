/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortType.cpp: implemtation for the InteropTestPortType.
 *
 */

#include "InteropTestPortType.h"

#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

InteropTestPortType::InteropTestPortType()
{
	m_pCall = new Call();
	m_pCall->SetProtocol(APTHTTP);
	m_pCall->SetEndpointURI("http://192.168.101.10/axis/base");
}

InteropTestPortType::~InteropTestPortType()
{
	delete m_pCall;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoString
 */
xsd__string InteropTestPortType::echoString(xsd__string Value0)
{
	xsd__string Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoString");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoString", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoStringResponse", ""))
		{
			Ret = m_pCall->GetElementAsString("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoStringArray
 */
xsd__string_Array InteropTestPortType::echoStringArray(xsd__string_Array Value0)
{
	xsd__string_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoStringArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStringArray", "http://soapinterop.org/");
	m_pCall->AddBasicArrayParameter((Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoStringArrayResponse", ""))
		{
			RetArray = (xsd__string_Array&)m_pCall->GetBasicArray(XSD_STRING, "return", 0);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoInteger
 */
int InteropTestPortType::echoInteger(int Value0)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoInteger");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoInteger", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputInteger", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoIntegerResponse", ""))
		{
			Ret = m_pCall->GetElementAsInt("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoIntegerArray
 */
xsd__int_Array InteropTestPortType::echoIntegerArray(xsd__int_Array Value0)
{
	xsd__int_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoIntegerArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoIntegerArray", "http://soapinterop.org/");
	m_pCall->AddBasicArrayParameter((Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoIntegerArrayResponse", ""))
		{
			RetArray = (xsd__int_Array&)m_pCall->GetBasicArray(XSD_INT, "return", 0);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoFloat
 */
float InteropTestPortType::echoFloat(float Value0)
{
	float Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoFloat");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoFloat", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoFloatResponse", ""))
		{
			Ret = m_pCall->GetElementAsFloat("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoFloatArray
 */
xsd__float_Array InteropTestPortType::echoFloatArray(xsd__float_Array Value0)
{
	xsd__float_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoFloatArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoFloatArray", "http://soapinterop.org/");
	m_pCall->AddBasicArrayParameter((Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoFloatArrayResponse", ""))
		{
			RetArray = (xsd__float_Array&)m_pCall->GetBasicArray(XSD_FLOAT, "return", 0);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoStruct
 */
SOAPStruct* InteropTestPortType::echoStruct(SOAPStruct* Value0)
{
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoStruct");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStruct", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoStructResponse", ""))
		{
			pReturn = (SOAPStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct,"return", 0);
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}


/*
 * This method wrap the service methodechoStructArray
 */
SOAPStruct_Array InteropTestPortType::echoStructArray(SOAPStruct_Array Value0)
{
	SOAPStruct_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoStructArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStructArray", "http://soapinterop.org/");
	m_pCall->AddCmplxArrayParameter((Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "inputStructArray", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoStructArrayResponse", ""))
		{
			RetArray = (SOAPStruct_Array&)m_pCall->GetCmplxArray((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "return", Axis_URI_SOAPStruct);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoVoid
 */
void InteropTestPortType::echoVoid()
{
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return ;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoVoid");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoVoid", "http://soapinterop.org/");
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoVoidResponse", ""))
		{
			/*not successful*/
		}
	}
	m_pCall->UnInitialize();
}


/*
 * This method wrap the service methodechoBase64
 */
xsd__base64Binary InteropTestPortType::echoBase64(xsd__base64Binary Value0)
{
	xsd__base64Binary Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoBase64");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoBase64", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputBase64", XSD_BASE64BINARY);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoBase64Response", ""))
		{
			Ret = m_pCall->GetElementAsBase64Binary("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoDate
 */
xsd__dateTime InteropTestPortType::echoDate(xsd__dateTime Value0)
{
	xsd__dateTime Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoDate");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoDate", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputDate", XSD_DATETIME);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoDateResponse", ""))
		{
			Ret = m_pCall->GetElementAsDateTime("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoHexBinary
 */
xsd__hexBinary InteropTestPortType::echoHexBinary(xsd__hexBinary Value0)
{
	xsd__hexBinary Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoHexBinary");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoHexBinary", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoHexBinaryResponse", ""))
		{
			Ret = m_pCall->GetElementAsHexBinary("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoDecimal
 */
xsd__decimal InteropTestPortType::echoDecimal(xsd__decimal Value0)
{
	xsd__decimal Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoDecimal");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoDecimal", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputDecimal", XSD_DECIMAL);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoDecimalResponse", ""))
		{
			Ret = m_pCall->GetElementAsDecimal("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoBoolean
 */
xsd__boolean InteropTestPortType::echoBoolean(xsd__boolean Value0)
{
	xsd__boolean Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropBase#echoBoolean");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoBoolean", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputBoolean", XSD_BOOLEAN);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoBooleanResponse", ""))
		{
			Ret = m_pCall->GetElementAsBoolean("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}

