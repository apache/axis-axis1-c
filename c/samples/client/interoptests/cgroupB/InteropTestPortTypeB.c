/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortTypeB.c: implemtation for the InteropTestPortTypeB.
 *
 */

#include "InteropTestPortTypeB.h"

extern int Axis_DeSerialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPArrayStruct(SOAPArrayStruct *Obj, bool bArray, int nSize);
extern void Axis_Delete_SOAPArrayStruct(SOAPArrayStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPArrayStruct();

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct *Obj, bool bArray, int nSize);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStruct();

extern int Axis_DeSerialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStructStruct(SOAPStructStruct *Obj, bool bArray, int nSize);
extern void Axis_Delete_SOAPStructStruct(SOAPStructStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStructStruct();

void* get_InteropTestPortTypeB_stub(const char* pchEndPointUri){
	return GetStubObject(APTHTTP, pchEndPointUri);
}
void destroy_InteropTestPortTypeB_stub(void* p){
	DestroyStubObject(p);
}

/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoStructAsSimpleTypes
 */
void echoStructAsSimpleTypes(void* pStub, SOAPStruct* Value0, AXIS_OUT_PARAM  float *OutValue0, AXIS_OUT_PARAM  int *OutValue1, AXIS_OUT_PARAM  xsd__string *OutValue2)
{
	Call* pCall = (Call*)pStub;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return ;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "cgroupB#echoStructAsSimpleTypes");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoStructAsSimpleTypes", "http://soapinterop.org/");
	pCall->_functions->AddCmplxParameter(pCall->_object, Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", 0);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoStructAsSimpleTypesResponse", "http://soapinterop.org/"))
		{
			*OutValue0 = pCall->_functions->GetElementAsFloat(pCall->_object, "outputFloat", 0);
			*OutValue1 = pCall->_functions->GetElementAsInt(pCall->_object, "outputInteger", 0);
			*OutValue2 = pCall->_functions->GetElementAsString(pCall->_object, "outputString", 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
}


/*
 * This method wrap the service methodechoSimpleTypesAsStruct
 */
SOAPStruct* echoSimpleTypesAsStruct(void* pStub, float Value0, int Value1, xsd__string Value2)
{
	Call* pCall = (Call*)pStub;
	SOAPStruct* pReturn = NULL;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "cgroupB#echoSimpleTypesAsStruct");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoSimpleTypesAsStruct", "http://soapinterop.org/");
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value0, "inputFloat", XSD_FLOAT);
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value1, "inputInteger", XSD_INT);
	pCall->_functions->AddParameter(pCall->_object, (void*)&Value2, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoSimpleTypesAsStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStruct*)pCall->_functions->GetCmplxObject(pCall->_object, (void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return pReturn;
}


/*
 * This method wrap the service methodechoNestedStruct
 */
SOAPStructStruct* echoNestedStruct(void* pStub, SOAPStructStruct* Value0)
{
	Call* pCall = (Call*)pStub;
	SOAPStructStruct* pReturn = NULL;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "cgroupB#echoNestedStruct");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoNestedStruct", "http://soapinterop.org/");
	pCall->_functions->AddCmplxParameter(pCall->_object, Value0, (void*)Axis_Serialize_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct, "inputStruct", 0);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoNestedStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStructStruct*)pCall->_functions->GetCmplxObject(pCall->_object, (void*) Axis_DeSerialize_SOAPStructStruct, (void*) Axis_Create_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return pReturn;
}


/*
 * This method wrap the service methodechoNestedArray
 */
SOAPArrayStruct* echoNestedArray(void* pStub, SOAPArrayStruct* Value0)
{
	Call* pCall = (Call*)pStub;
	SOAPArrayStruct* pReturn = NULL;
	/* Following will establish the connections with the server too */
	if (AXIS_SUCCESS != pCall->_functions->Initialize(pCall->_object, C_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	pCall->_functions->SetTransportProperty(pCall->_object,SOAPACTION_HEADER , "cgroupB#echoNestedArray");
	pCall->_functions->SetSOAPVersion(pCall->_object, SOAP_VER_1_1);
	pCall->_functions->SetOperation(pCall->_object, "echoNestedArray", "http://soapinterop.org/");
	pCall->_functions->AddCmplxParameter(pCall->_object, Value0, (void*)Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "inputStruct", 0);
	if (AXIS_SUCCESS == pCall->_functions->Invoke(pCall->_object))
	{
		if(AXIS_SUCCESS == pCall->_functions->CheckMessage(pCall->_object, "echoNestedArrayResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPArrayStruct*)pCall->_functions->GetCmplxObject(pCall->_object, (void*) Axis_DeSerialize_SOAPArrayStruct, (void*) Axis_Create_SOAPArrayStruct, (void*) Axis_Delete_SOAPArrayStruct, 0, 0);
		}
	}
	pCall->_functions->UnInitialize(pCall->_object);
	return pReturn;
}

