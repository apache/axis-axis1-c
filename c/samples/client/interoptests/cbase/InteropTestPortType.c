/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortType.c: implemtation for the InteropTestPortType.
 *
 */

#include "InteropTestPortType.h"

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct *Obj, bool bArray, int nSize);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStruct();


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoString
 */
xsd__string echoString(xsd__string Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__string Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:80/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoString");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoString", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoStringResponse", ""))
		{
			Ret = pCall->GetElementAsString(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoStringArray
 */
xsd__string_Array echoStringArray(xsd__string_Array Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__string_Array RetArray = {NULL, 0};
	Axis_Array array;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return RetArray;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoStringArray");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoStringArray", "http://soapinterop.org/");
	pCall->AddBasicArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoStringArrayResponse", ""))
		{
			array = pCall->GetBasicArray(g_pInteropTestPortType, XSD_STRING, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return RetArray;
}


/*
 * This method wrap the service methodechoInteger
 */
int echoInteger(int Value0)
{
	int nStatus;
	CallFunctions* pCall;
	int Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoInteger");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoInteger", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputInteger", XSD_INT);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoIntegerResponse", ""))
		{
			Ret = pCall->GetElementAsInt(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoIntegerArray
 */
xsd__int_Array echoIntegerArray(xsd__int_Array Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__int_Array RetArray = {NULL, 0};
	Axis_Array array;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return RetArray;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoIntegerArray");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoIntegerArray", "http://soapinterop.org/");
	pCall->AddBasicArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoIntegerArrayResponse", ""))
		{
			array = pCall->GetBasicArray(g_pInteropTestPortType, XSD_INT, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return RetArray;
}


/*
 * This method wrap the service methodechoFloat
 */
float echoFloat(float Value0)
{
	int nStatus;
	CallFunctions* pCall;
	float Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoFloat");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoFloat", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputFloat", XSD_FLOAT);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoFloatResponse", ""))
		{
			Ret = pCall->GetElementAsFloat(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoFloatArray
 */
xsd__float_Array echoFloatArray(xsd__float_Array Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__float_Array RetArray = {NULL, 0};
	Axis_Array array;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return RetArray;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoFloatArray");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoFloatArray", "http://soapinterop.org/");
	pCall->AddBasicArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoFloatArrayResponse", ""))
		{
			array = pCall->GetBasicArray(g_pInteropTestPortType, XSD_FLOAT, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return RetArray;
}


/*
 * This method wrap the service methodechoStruct
 */
SOAPStruct* echoStruct(SOAPStruct* Value0)
{
	int nStatus;
	CallFunctions* pCall;
	SOAPStruct* pReturn = NULL;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return pReturn;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return pReturn;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoStruct");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoStruct", "http://soapinterop.org/");
	pCall->AddCmplxParameter(g_pInteropTestPortType, Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", 0);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoStructResponse", ""))
		{
			pReturn = (SOAPStruct*)pCall->GetCmplxObject(g_pInteropTestPortType, (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return pReturn;
}


/*
 * This method wrap the service methodechoStructArray
 */
SOAPStruct_Array echoStructArray(SOAPStruct_Array Value0)
{
	int nStatus;
	CallFunctions* pCall;
	SOAPStruct_Array RetArray = {NULL, 0};
	Axis_Array array;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return RetArray;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoStructArray");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoStructArray", "http://soapinterop.org/");
	pCall->AddCmplxArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoStructArrayResponse", ""))
		{
			array = pCall->GetCmplxArray(g_pInteropTestPortType, (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return RetArray;
}


/*
 * This method wrap the service methodechoVoid
 */
void echoVoid()
{
	int nStatus;
	CallFunctions* pCall;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return 	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return ;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoVoid");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoVoid", "http://soapinterop.org/");
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoVoidResponse", ""))
		{
			/*not successful*/
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
}


/*
 * This method wrap the service methodechoBase64
 */
xsd__base64Binary echoBase64(xsd__base64Binary Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__base64Binary Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoBase64");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoBase64", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputBase64", XSD_BASE64BINARY);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoBase64Response", ""))
		{
			Ret = pCall->GetElementAsBase64Binary(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoDate
 */
xsd__dateTime echoDate(xsd__dateTime Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__dateTime Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoDate");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoDate", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputDate", XSD_DATETIME);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoDateResponse", ""))
		{
			Ret = pCall->GetElementAsDateTime(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoHexBinary
 */
xsd__hexBinary echoHexBinary(xsd__hexBinary Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__hexBinary Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoHexBinary");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoHexBinary", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoHexBinaryResponse", ""))
		{
			Ret = pCall->GetElementAsHexBinary(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoDecimal
 */
xsd__decimal echoDecimal(xsd__decimal Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__decimal Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoDecimal");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoDecimal", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputDecimal", XSD_DECIMAL);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoDecimalResponse", ""))
		{
			Ret = pCall->GetElementAsDecimal(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoBoolean
 */
xsd__boolean echoBoolean(xsd__boolean Value0)
{
	int nStatus;
	CallFunctions* pCall;
	xsd__boolean Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost:5555/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType, C_RPC_PROVIDER)) return Ret;
	pCall->SetTransportProperty(g_pInteropTestPortType,SOAPACTION_HEADER , "InteropBase#echoBoolean");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoBoolean", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputBoolean", XSD_BOOLEAN);
	if (AXIS_SUCCESS == pCall->Invoke(g_pInteropTestPortType))
	{
		if(AXIS_SUCCESS == pCall->CheckMessage(g_pInteropTestPortType, "echoBooleanResponse", ""))
		{
			Ret = pCall->GetElementAsBoolean(g_pInteropTestPortType, 0, 0);
		}
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}

