///////////////////////////////////////////////////////////////////////
//This is the Service implementation CPP file genarated by theWSDL2Ws.
//		InteropTestPortTypeBWrapper.cpp: implemtation for the InteropTestPortTypeBWrapper.
//
//////////////////////////////////////////////////////////////////////

#include "InteropTestPortTypeBWrapper.h"

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(void* pObj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

extern int Axis_DeSerialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPArrayStruct(void* pObj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPArrayStruct(SOAPArrayStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPArrayStruct();

extern int Axis_DeSerialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStructStruct(void* pObj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStructStruct(SOAPStructStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStructStruct();

InteropTestPortTypeBWrapper::InteropTestPortTypeBWrapper()
{
	pWs = new InteropTestPortTypeB();
}

InteropTestPortTypeBWrapper::~InteropTestPortTypeBWrapper()
{
	delete pWs;
}

//implementation of WrapperClassHandler interface
void InteropTestPortTypeBWrapper::OnFault(void *pMsg)
{
}

int InteropTestPortTypeBWrapper::Init()
{
	return AXIS_SUCCESS;
}

int InteropTestPortTypeBWrapper::Fini()
{
	return AXIS_SUCCESS;
}


/////////////////////////////////////////////////////////////////
// This method invokes the right service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeBWrapper::Invoke(void *pMsg)
{
	IMessageData *mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->GetOperationName();
	if (0 == strcmp(method, "echoStructAsSimpleTypes"))
		return echoStructAsSimpleTypes(mc);
	else if (0 == strcmp(method, "echoSimpleTypesAsStruct"))
		return echoSimpleTypesAsStruct(mc);
	else if (0 == strcmp(method, "echo2DStringArray"))
		return echo2DStringArray(mc);
	else if (0 == strcmp(method, "echoNestedStruct"))
		return echoNestedStruct(mc);
	else if (0 == strcmp(method, "echoNestedArray"))
		return echoNestedArray(mc);
	else return AXIS_FAIL;
}


//Methods corresponding to the web service methods

/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeBWrapper::echoStructAsSimpleTypes(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStructAsSimpleTypes", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStructAsSimpleTypesResponse", "http://soapinterop.org/");
	SOAPStruct *v0 = (SOAPStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, "inputStruct", Axis_URI_SOAPStruct);
	AxisChar* outValue0;
	int outValue1;
	float outValue2;
	pWs->echoStructAsSimpleTypes(v0, &outValue0, &outValue1, &outValue2);
	if (AXIS_SUCCESS != pIWSSZ->AddOutputParam("String", (void*)&outValue0, XSD_STRING)) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSSZ->AddOutputParam("Int", (void*)&outValue1, XSD_INT)) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSSZ->AddOutputParam("Float", (void*)&outValue2, XSD_FLOAT)) return AXIS_FAIL;
	return AXIS_SUCCESS;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeBWrapper::echoSimpleTypesAsStruct(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoSimpleTypesAsStruct", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoSimpleTypesAsStructResponse", "http://soapinterop.org/");
	float v0 = pIWSDZ->GetElementAsFloat("inputFloat",0);
	int v1 = pIWSDZ->GetElementAsInt("inputInteger",0);
	AxisChar* v2 = pIWSDZ->GetElementAsString("inputString",0);
	SOAPStruct *ret = pWs->echoSimpleTypesAsStruct(v0,v1,v2);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoSimpleTypesAsStructReturn", "");
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeBWrapper::echo2DStringArray(IMessageData* mc)
{
	return AXIS_FAIL;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeBWrapper::echoNestedStruct(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoNestedStruct", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoNestedStructResponse", "http://soapinterop.org/");
	SOAPStructStruct *v0 = (SOAPStructStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPStructStruct
		, (void*)Axis_Create_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct
		, "inputStruct", Axis_URI_SOAPStructStruct);
	SOAPStructStruct *ret = pWs->echoNestedStruct(v0);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct, "outputStruct", "");
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeBWrapper::echoNestedArray(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoNestedArray", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoNestedArrayResponse", "http://soapinterop.org/");
	SOAPArrayStruct *v0 = (SOAPArrayStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPArrayStruct
		, (void*)Axis_Create_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct
		, "inputArrayStruct", Axis_URI_SOAPArrayStruct);
	SOAPArrayStruct *ret = pWs->echoNestedArray(v0);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "outputArrayStruct", "");
}

