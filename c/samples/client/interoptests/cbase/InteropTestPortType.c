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

void* get_InteropTestPortType_stub(){
	return GetStubObject(APTHTTP, "http://localhost/axis/cbase");
}
void destroy_InteropTestPortType_stub(void* p){
	DestroyStubObject(p);
}

/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoString
 */
xsd__string echoString(void* pStub, xsd__string Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__string Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoString");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoString", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoStringResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsString(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}


/*
 * This method wrap the service methodechoStringArray
 */
xsd__string_Array echoStringArray(void* pStub, xsd__string_Array Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__string_Array RetArray = {NULL, 0};
	Axis_Array array;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoStringArray");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoStringArray", "http://soapinterop.org/");
	pCall->_functions->AddBasicArrayParameter(pCall->_object, (Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoStringArrayResponse", ""))
		{
			array = pCall->_functions->GetBasicArray(pCall->_object, XSD_STRING, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return RetArray;
}


/*
 * This method wrap the service methodechoInteger
 */
int echoInteger(void* pStub, int Value0)
{
	Call* pCall = (Call*)pStub;
	int Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoInteger");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoInteger", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputInteger", XSD_INT);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoIntegerResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsInt(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}


/*
 * This method wrap the service methodechoIntegerArray
 */
xsd__int_Array echoIntegerArray(void* pStub, xsd__int_Array Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__int_Array RetArray = {NULL, 0};
	Axis_Array array;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoIntegerArray");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoIntegerArray", "http://soapinterop.org/");
	pCall->_functions->AddBasicArrayParameter(pCall->_object, (Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoIntegerArrayResponse", ""))
		{
			array = pCall->_functions->GetBasicArray(pCall->_object, XSD_INT, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return RetArray;
}


/*
 * This method wrap the service methodechoFloat
 */
float echoFloat(void* pStub, float Value0)
{
	Call* pCall = (Call*)pStub;
	float Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoFloat");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoFloat", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputFloat", XSD_FLOAT);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoFloatResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsFloat(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}


/*
 * This method wrap the service methodechoFloatArray
 */
xsd__float_Array echoFloatArray(void* pStub, xsd__float_Array Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__float_Array RetArray = {NULL, 0};
	Axis_Array array;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoFloatArray");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoFloatArray", "http://soapinterop.org/");
	pCall->_functions->AddBasicArrayParameter(pCall->_object, (Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoFloatArrayResponse", ""))
		{
			array = pCall->_functions->GetBasicArray(pCall->_object, XSD_FLOAT, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return RetArray;
}


/*
 * This method wrap the service methodechoStruct
 */
SOAPStruct* echoStruct(void* pStub, SOAPStruct* Value0)
{
	Call* pCall = (Call*)pStub;
	SOAPStruct* pReturn = NULL;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoStruct");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoStruct", "http://soapinterop.org/");
	pCall->_functions->AddCmplxParameter(pCall->_object, Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", 0);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoStructResponse", ""))
		{
			pReturn = (SOAPStruct*)pCall->_functions->GetCmplxObject(pCall->_object, (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return pReturn;
}


/*
 * This method wrap the service methodechoStructArray
 */
SOAPStruct_Array echoStructArray(void* pStub, SOAPStruct_Array Value0)
{
	Call* pCall = (Call*)pStub;
	SOAPStruct_Array RetArray = {NULL, 0};
	Axis_Array array;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoStructArray");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoStructArray", "http://soapinterop.org/");
	pCall->_functions->AddCmplxArrayParameter(pCall->_object, (Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoStructArrayResponse", ""))
		{
			array = pCall->_functions->GetCmplxArray(pCall->_object, (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, 0, 0);
			memcpy(&RetArray, &array, sizeof(Axis_Array));
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return RetArray;
}


/*
 * This method wrap the service methodechoVoid
 */
void echoVoid(void* pStub)
{
	Call* pCall = (Call*)pStub;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return ;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoVoid");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoVoid", "http://soapinterop.org/");
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoVoidResponse", ""))
		{
			/*not successful*/
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
}


/*
 * This method wrap the service methodechoBase64
 */
xsd__base64Binary echoBase64(void* pStub, xsd__base64Binary Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__base64Binary Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoBase64");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoBase64", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputBase64", XSD_BASE64BINARY);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoBase64Response", ""))
		{
			Ret = pCall->_functions->GetElementAsBase64Binary(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}


/*
 * This method wrap the service methodechoDate
 */
xsd__dateTime echoDate(void* pStub, xsd__dateTime Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__dateTime Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoDate");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoDate", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputDate", XSD_DATETIME);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoDateResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsDateTime(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}


/*
 * This method wrap the service methodechoHexBinary
 */
xsd__hexBinary echoHexBinary(void* pStub, xsd__hexBinary Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__hexBinary Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoHexBinary");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoHexBinary", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoHexBinaryResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsHexBinary(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}


/*
 * This method wrap the service methodechoDecimal
 */
xsd__decimal echoDecimal(void* pStub, xsd__decimal Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__decimal Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoDecimal");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoDecimal", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputDecimal", XSD_DECIMAL);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoDecimalResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsDecimal(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}


/*
 * This method wrap the service methodechoBoolean
 */
xsd__boolean echoBoolean(void* pStub, xsd__boolean Value0)
{
	Call* pCall = (Call*)pStub;
	xsd__boolean Ret;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "InteropBase#echoBoolean");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoBoolean", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputBoolean", XSD_BOOLEAN);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoBooleanResponse", ""))
		{
			Ret = pCall->_functions->GetElementAsBoolean(pCall->_object, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return Ret;
}

