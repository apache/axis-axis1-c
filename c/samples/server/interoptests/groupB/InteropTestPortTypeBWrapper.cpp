/*
 * This is the Service implementation CPP file genarated by theWSDL2Ws.
 * InteropTestPortTypeBWrapper.cpp: implemtation for the InteropTestPortTypeBWrapper.
 * 
 */

#include "InteropTestPortTypeBWrapper.h"

extern int Axis_DeSerialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPArrayStruct(SOAPArrayStruct *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPArrayStruct(SOAPArrayStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPArrayStruct();

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

extern int Axis_DeSerialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStructStruct(SOAPStructStruct *Obj, bool bArray = false, int nSize=0);
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

/*implementation of WrapperClassHandler interface*/
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


/*
 * This method invokes the right service method 
 */
int InteropTestPortTypeBWrapper::Invoke(void *pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->GetOperationName();
	if (0 == strcmp(method, "echoStructAsSimpleTypes"))
		return echoStructAsSimpleTypes(mc);
	else if (0 == strcmp(method, "echoSimpleTypesAsStruct"))
		return echoSimpleTypesAsStruct(mc);
	else if (0 == strcmp(method, "echoNestedStruct"))
		return echoNestedStruct(mc);
	else if (0 == strcmp(method, "echoNestedArray"))
		return echoNestedArray(mc);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method 
 */
int InteropTestPortTypeBWrapper::echoStructAsSimpleTypes(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStructAsSimpleTypes", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStructAsSimpleTypesResponse", "http://soapinterop.org/");
	SOAPStruct *v0 = (SOAPStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, "inputStruct", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	float out0;
	int out1;
	xsd__string out2;
	pWs->echoStructAsSimpleTypes(v0,&out0,&out1,&out2);
	pIWSSZ->AddOutputParam("outputFloat", (void*)&out0, XSD_FLOAT);
	pIWSSZ->AddOutputParam("outputInteger", (void*)&out1, XSD_INT);
	pIWSSZ->AddOutputParam("outputString", (void*)&out2, XSD_STRING);
	return AXIS_SUCCESS;
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeBWrapper::echoSimpleTypesAsStruct(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoSimpleTypesAsStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoSimpleTypesAsStructResponse", "http://soapinterop.org/");
	float v0 = pIWSDZ->GetElementAsFloat("inputFloat",0);
	int v1 = pIWSDZ->GetElementAsInt("inputInteger",0);
	xsd__string v2 = pIWSDZ->GetElementAsString("inputString",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	SOAPStruct* ret = pWs->echoSimpleTypesAsStruct(v0,v1,v2);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoSimpleTypesAsStructReturn", 0);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeBWrapper::echoNestedStruct(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoNestedStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoNestedStructResponse", "http://soapinterop.org/");
	SOAPStructStruct *v0 = (SOAPStructStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPStructStruct
		, (void*)Axis_Create_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct
		, "inputStruct", Axis_URI_SOAPStructStruct);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	SOAPStructStruct* ret = pWs->echoNestedStruct(v0);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct, "echoNestedStructReturn", 0);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeBWrapper::echoNestedArray(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoNestedArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoNestedArrayResponse", "http://soapinterop.org/");
	SOAPArrayStruct *v0 = (SOAPArrayStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPArrayStruct
		, (void*)Axis_Create_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct
		, "inputStruct", Axis_URI_SOAPArrayStruct);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	SOAPArrayStruct* ret = pWs->echoNestedArray(v0);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "echoNestedArrayReturn", 0);
}

