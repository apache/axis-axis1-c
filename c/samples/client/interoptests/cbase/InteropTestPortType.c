/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortType.c: implemtation for the InteropTestPortType.
 *
 */

#include "InteropTestPortType.h"

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(bool bArray, int nSize);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStruct();


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoString
 */
char* echoString(char* Value0)
{
	int nStatus;
	CallX* pCall;
	char* Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoString", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputString", XSD_STRING);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_STRING);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetString(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoStringArray
 */
ArrayOfstring echoStringArray(ArrayOfstring Value0)
{
	int nStatus;
	CallX* pCall;
	ArrayOfstring RetArray = {NULL, 0};
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return RetArray;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoStringArray", "http://soapinterop.org/");
	pCall->AddBasicArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
	pCall->SetBasicArrayReturnType(g_pInteropTestPortType, (Axis_Array*)(&RetArray), XSD_STRING);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS != nStatus)
	{
		free(RetArray.m_Array);
		RetArray.m_Array = NULL;
		RetArray.m_Size = 0;
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
	CallX* pCall;
	int Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoInteger", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputInteger", XSD_INT);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_INT);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetInt(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoIntegerArray
 */
ArrayOfint echoIntegerArray(ArrayOfint Value0)
{
	int nStatus;
	CallX* pCall;
	ArrayOfint RetArray = {NULL, 0};
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return RetArray;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoIntegerArray", "http://soapinterop.org/");
	pCall->AddBasicArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
	pCall->SetBasicArrayReturnType(g_pInteropTestPortType, (Axis_Array*)(&RetArray), XSD_INT);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS != nStatus)
	{
		free(RetArray.m_Array);
		RetArray.m_Array = NULL;
		RetArray.m_Size = 0;
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
	CallX* pCall;
	float Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoFloat", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputFloat", XSD_FLOAT);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_FLOAT);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetFloat(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoFloatArray
 */
ArrayOffloat echoFloatArray(ArrayOffloat Value0)
{
	int nStatus;
	CallX* pCall;
	ArrayOffloat RetArray = {NULL, 0};
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return RetArray;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoFloatArray", "http://soapinterop.org/");
	pCall->AddBasicArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
	pCall->SetBasicArrayReturnType(g_pInteropTestPortType, (Axis_Array*)(&RetArray), XSD_FLOAT);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS != nStatus)
	{
		free(RetArray.m_Array);
		RetArray.m_Array = NULL;
		RetArray.m_Size = 0;
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
	CallX* pCall;
	SOAPStruct* pReturn = NULL;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return pReturn;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return pReturn;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoStruct", "http://soapinterop.org/");
	pCall->AddCmplxParameter(g_pInteropTestPortType, Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct");
	pCall->SetCmplxReturnType(g_pInteropTestPortType, (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		pCall->GetCmplxResult(g_pInteropTestPortType, (void**)&pReturn);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return pReturn;
}


/*
 * This method wrap the service methodechoStructArray
 */
ArrayOfSOAPStruct echoStructArray(ArrayOfSOAPStruct Value0)
{
	int nStatus;
	CallX* pCall;
	ArrayOfSOAPStruct RetArray = {NULL, 0};
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return RetArray;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return RetArray;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoStructArray", "http://soapinterop.org/");
	pCall->AddCmplxArrayParameter(g_pInteropTestPortType, (Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct, "inputStructArray");
	pCall->SetCmplxArrayReturnType(g_pInteropTestPortType, (Axis_Array*)(&RetArray), (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS != nStatus)
	{
		free(RetArray.m_Array);
		RetArray.m_Array = NULL;
		RetArray.m_Size = 0;
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
	CallX* pCall;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return 	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return ;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoVoid", "http://soapinterop.org/");
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS != nStatus)
	{
		//What to do ? . Throw an exception ??? 
	}
	pCall->UnInitialize(g_pInteropTestPortType);
}


/*
 * This method wrap the service methodechoBase64
 */
Axis_Base64Binary echoBase64(Axis_Base64Binary Value0)
{
	int nStatus;
	CallX* pCall;
	Axis_Base64Binary Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoBase64", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputBase64", XSD_BASE64BINARY);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_BASE64BINARY);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetBase64String(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoDate
 */
Axis_DateTime echoDate(Axis_DateTime Value0)
{
	int nStatus;
	CallX* pCall;
	Axis_DateTime Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoDate", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputDate", XSD_DATETIME);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_DATETIME);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetDateTime(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoHexBinary
 */
Axis_HexBinary echoHexBinary(Axis_HexBinary Value0)
{
	int nStatus;
	CallX* pCall;
	Axis_HexBinary Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoHexBinary", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_HEXBINARY);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetHexString(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoDecimal
 */
Axis_Decimal echoDecimal(Axis_Decimal Value0)
{
	int nStatus;
	CallX* pCall;
	Axis_Decimal Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoDecimal", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputDecimal", XSD_DECIMAL);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_DECIMAL);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetDecimal(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}


/*
 * This method wrap the service methodechoBoolean
 */
Axis_Boolean echoBoolean(Axis_Boolean Value0)
{
	int nStatus;
	CallX* pCall;
	Axis_Boolean Ret;
	if (!g_pInteropTestPortType) g_pInteropTestPortType = GetCallObject(APTHTTP, "http://localhost/axis/InteropBase");
	if (!g_pInteropTestPortType || !g_pInteropTestPortType->__vfptr) return Ret;
	pCall = g_pInteropTestPortType->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortType)) return Ret;
	pCall->SetHeader(g_pInteropTestPortType, "SOAPAction", "InteropBase");
	pCall->SetSOAPVersion(g_pInteropTestPortType, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortType, "echoBoolean", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortType, (void*)&Value0, "inputBoolean", XSD_BOOLEAN);
	pCall->SetReturnType(g_pInteropTestPortType, XSD_BOOLEAN);
	nStatus = pCall->Invoke(g_pInteropTestPortType);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetInt(g_pInteropTestPortType);
	}
	pCall->UnInitialize(g_pInteropTestPortType);
	return Ret;
}

