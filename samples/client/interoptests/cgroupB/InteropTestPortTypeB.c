/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortTypeB.c: implemtation for the InteropTestPortTypeB.
 *
 */

#include "InteropTestPortTypeB.h"

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(bool bArray, int nSize);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStruct();

extern int Axis_DeSerialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPArrayStruct(bool bArray, int nSize);
extern void Axis_Delete_SOAPArrayStruct(SOAPArrayStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPArrayStruct();

extern int Axis_DeSerialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStructStruct(bool bArray, int nSize);
extern void Axis_Delete_SOAPStructStruct(SOAPStructStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStructStruct();


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoStructAsSimpleTypes
 */
float echoStructAsSimpleTypes(SOAPStruct* Value0)
{
	int nStatus;
	CallX* pCall;
	float Ret;
	if (!g_pInteropTestPortTypeB) g_pInteropTestPortTypeB = GetCallObject(APTHTTP, "http://localhost/axis/InteropGroupB");
	if (!g_pInteropTestPortTypeB || !g_pInteropTestPortTypeB->__vfptr) return Ret;
	pCall = g_pInteropTestPortTypeB->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortTypeB)) return Ret;
	pCall->SetHeader(g_pInteropTestPortTypeB, "SOAPAction", "InteropGroupB");
	pCall->SetSOAPVersion(g_pInteropTestPortTypeB, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortTypeB, "echoStructAsSimpleTypes", "http://soapinterop.org/");
	pCall->AddCmplxParameter(g_pInteropTestPortTypeB, Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct");
	pCall->SetReturnType(g_pInteropTestPortTypeB, XSD_FLOAT);
	nStatus = pCall->Invoke(g_pInteropTestPortTypeB);
	if (AXIS_SUCCESS == nStatus)
	{
		Ret = pCall->GetFloat(g_pInteropTestPortTypeB);
	}
	pCall->UnInitialize(g_pInteropTestPortTypeB);
	return Ret;
}


/*
 * This method wrap the service methodechoSimpleTypesAsStruct
 */
SOAPStruct* echoSimpleTypesAsStruct(float Value0, int Value1, char* Value2)
{
	int nStatus;
	CallX* pCall;
	SOAPStruct* pReturn = NULL;
	if (!g_pInteropTestPortTypeB) g_pInteropTestPortTypeB = GetCallObject(APTHTTP, "http://localhost/axis/InteropGroupB");
	if (!g_pInteropTestPortTypeB || !g_pInteropTestPortTypeB->__vfptr) return pReturn;
	pCall = g_pInteropTestPortTypeB->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortTypeB)) return pReturn;
	pCall->SetHeader(g_pInteropTestPortTypeB, "SOAPAction", "InteropGroupB");
	pCall->SetSOAPVersion(g_pInteropTestPortTypeB, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortTypeB, "echoSimpleTypesAsStruct", "http://soapinterop.org/");
	pCall->AddParameter(g_pInteropTestPortTypeB, (void*)&Value0, "inputFloat", XSD_FLOAT);
	pCall->AddParameter(g_pInteropTestPortTypeB, (void*)&Value1, "inputInteger", XSD_INT);
	pCall->AddParameter(g_pInteropTestPortTypeB, (void*)&Value2, "inputString", XSD_STRING);
	pCall->SetCmplxReturnType(g_pInteropTestPortTypeB, (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	nStatus = pCall->Invoke(g_pInteropTestPortTypeB);
	if (AXIS_SUCCESS == nStatus)
	{
		pCall->GetCmplxResult(g_pInteropTestPortTypeB, (void**)&pReturn);
	}
	pCall->UnInitialize(g_pInteropTestPortTypeB);
	return pReturn;
}


/*
 * This method wrap the service methodecho2DStringArray
 */
ArrayOfString2D echo2DStringArray(ArrayOfString2D Value0)
{
	int nStatus;
	CallX* pCall;
	ArrayOfString2D RetArray = {NULL, 0};
	if (!g_pInteropTestPortTypeB) g_pInteropTestPortTypeB = GetCallObject(APTHTTP, "http://localhost/axis/InteropGroupB");
	if (!g_pInteropTestPortTypeB || !g_pInteropTestPortTypeB->__vfptr) return RetArray;
	pCall = g_pInteropTestPortTypeB->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortTypeB)) return RetArray;
	pCall->SetHeader(g_pInteropTestPortTypeB, "SOAPAction", "InteropGroupB");
	pCall->SetSOAPVersion(g_pInteropTestPortTypeB, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortTypeB, "echo2DStringArray", "http://soapinterop.org/");
	pCall->AddBasicArrayParameter(g_pInteropTestPortTypeB, (Axis_Array*)(&Value0), XSD_STRING, "input2DStringArray");
	pCall->SetBasicArrayReturnType(g_pInteropTestPortTypeB, (Axis_Array*)(&RetArray), XSD_STRING);
	nStatus = pCall->Invoke(g_pInteropTestPortTypeB);
	if (AXIS_SUCCESS != nStatus)
	{
		free(RetArray.m_Array);
		RetArray.m_Array = NULL;
		RetArray.m_Size = 0;
	}
	pCall->UnInitialize(g_pInteropTestPortTypeB);
	return RetArray;
}


/*
 * This method wrap the service methodechoNestedStruct
 */
SOAPStructStruct* echoNestedStruct(SOAPStructStruct* Value0)
{
	int nStatus;
	CallX* pCall;
	SOAPStructStruct* pReturn = NULL;
	if (!g_pInteropTestPortTypeB) g_pInteropTestPortTypeB = GetCallObject(APTHTTP, "http://localhost/axis/InteropGroupB");
	if (!g_pInteropTestPortTypeB || !g_pInteropTestPortTypeB->__vfptr) return pReturn;
	pCall = g_pInteropTestPortTypeB->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortTypeB)) return pReturn;
	pCall->SetHeader(g_pInteropTestPortTypeB, "SOAPAction", "InteropGroupB");
	pCall->SetSOAPVersion(g_pInteropTestPortTypeB, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortTypeB, "echoNestedStruct", "http://soapinterop.org/");
	pCall->AddCmplxParameter(g_pInteropTestPortTypeB, Value0, (void*)Axis_Serialize_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct, "inputStruct");
	pCall->SetCmplxReturnType(g_pInteropTestPortTypeB, (void*) Axis_DeSerialize_SOAPStructStruct, (void*) Axis_Create_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct, Axis_TypeName_SOAPStructStruct, Axis_URI_SOAPStructStruct);
	nStatus = pCall->Invoke(g_pInteropTestPortTypeB);
	if (AXIS_SUCCESS == nStatus)
	{
		pCall->GetCmplxResult(g_pInteropTestPortTypeB, (void**)&pReturn);
	}
	pCall->UnInitialize(g_pInteropTestPortTypeB);
	return pReturn;
}


/*
 * This method wrap the service methodechoNestedArray
 */
SOAPArrayStruct* echoNestedArray(SOAPArrayStruct* Value0)
{
	int nStatus;
	CallX* pCall;
	SOAPArrayStruct* pReturn = NULL;
	if (!g_pInteropTestPortTypeB) g_pInteropTestPortTypeB = GetCallObject(APTHTTP, "http://localhost/axis/cgroupb");
	if (!g_pInteropTestPortTypeB || !g_pInteropTestPortTypeB->__vfptr) return pReturn;
	pCall = g_pInteropTestPortTypeB->__vfptr;
/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->Initialize(g_pInteropTestPortTypeB)) return pReturn;
	pCall->SetHeader(g_pInteropTestPortTypeB, "SOAPAction", "InteropGroupB");
	pCall->SetSOAPVersion(g_pInteropTestPortTypeB, SOAP_VER_1_1);
	pCall->SetOperation(g_pInteropTestPortTypeB, "echoNestedArray", "http://soapinterop.org/");
	pCall->AddCmplxParameter(g_pInteropTestPortTypeB, Value0, (void*)Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "inputStruct");
	pCall->SetCmplxReturnType(g_pInteropTestPortTypeB, (void*) Axis_DeSerialize_SOAPArrayStruct, (void*) Axis_Create_SOAPArrayStruct, (void*) Axis_Delete_SOAPArrayStruct, Axis_TypeName_SOAPArrayStruct, Axis_URI_SOAPArrayStruct);
	nStatus = pCall->Invoke(g_pInteropTestPortTypeB);
	if (AXIS_SUCCESS == nStatus)
	{
		pCall->GetCmplxResult(g_pInteropTestPortTypeB, (void**)&pReturn);
	}
	pCall->UnInitialize(g_pInteropTestPortTypeB);
	return pReturn;
}

