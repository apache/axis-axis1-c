/*
 * This is the Service implementation CPP file genarated by theWSDL2Ws.
 * InteropTestPortTypeWrapper.cpp: implemtation for the InteropTestPortTypeWrapper.
 * 
 */

#include "InteropTestPortTypeWrapper.h"

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

InteropTestPortTypeWrapper::InteropTestPortTypeWrapper()
{
	pWs = new InteropTestPortType();
}

InteropTestPortTypeWrapper::~InteropTestPortTypeWrapper()
{
	delete pWs;
}

/*implementation of WrapperClassHandler interface*/
void InteropTestPortTypeWrapper::OnFault(void *pMsg)
{
}

int InteropTestPortTypeWrapper::Init()
{
	return AXIS_SUCCESS;
}

int InteropTestPortTypeWrapper::Fini()
{
	return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int InteropTestPortTypeWrapper::Invoke(void *pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->GetOperationName();
	if (0 == strcmp(method, "echoString"))
		return echoString(mc);
	else if (0 == strcmp(method, "echoStringArray"))
		return echoStringArray(mc);
	else if (0 == strcmp(method, "echoInteger"))
		return echoInteger(mc);
	else if (0 == strcmp(method, "echoIntegerArray"))
		return echoIntegerArray(mc);
	else if (0 == strcmp(method, "echoFloat"))
		return echoFloat(mc);
	else if (0 == strcmp(method, "echoFloatArray"))
		return echoFloatArray(mc);
	else if (0 == strcmp(method, "echoStruct"))
		return echoStruct(mc);
	else if (0 == strcmp(method, "echoStructArray"))
		return echoStructArray(mc);
	else if (0 == strcmp(method, "echoVoid"))
		return echoVoid(mc);
	else if (0 == strcmp(method, "echoBase64"))
		return echoBase64(mc);
	else if (0 == strcmp(method, "echoDate"))
		return echoDate(mc);
	else if (0 == strcmp(method, "echoHexBinary"))
		return echoHexBinary(mc);
	else if (0 == strcmp(method, "echoDecimal"))
		return echoDecimal(mc);
	else if (0 == strcmp(method, "echoBoolean"))
		return echoBoolean(mc);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoString(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoString", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStringResponse", "http://soapinterop.org/");
	xsd__string v0 = pIWSDZ->GetElementAsString("inputString",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__string ret = pWs->echoString(v0);
	return pIWSSZ->AddOutputParam("echoStringReturn", (void*)&ret, XSD_STRING);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoStringArray(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStringArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStringArrayResponse", "http://soapinterop.org/");
	xsd__string_Array v0 = (xsd__string_Array&)pIWSDZ->GetBasicArray(XSD_STRING, "inputStringArray",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__string_Array ret = pWs->echoStringArray(v0);
	return pIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&ret),XSD_STRING, "echoStringArrayReturn");
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoInteger(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoInteger", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoIntegerResponse", "http://soapinterop.org/");
	int v0 = pIWSDZ->GetElementAsInt("inputInteger",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	int ret = pWs->echoInteger(v0);
	return pIWSSZ->AddOutputParam("echoIntegerReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoIntegerArray(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoIntegerArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoIntegerArrayResponse", "http://soapinterop.org/");
	xsd__int_Array v0 = (xsd__int_Array&)pIWSDZ->GetBasicArray(XSD_INT, "inputIntegerArray",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__int_Array ret = pWs->echoIntegerArray(v0);
	return pIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&ret),XSD_INT, "echoIntegerArrayReturn");
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoFloat(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoFloat", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoFloatResponse", "http://soapinterop.org/");
	float v0 = pIWSDZ->GetElementAsFloat("inputFloat",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	float ret = pWs->echoFloat(v0);
	return pIWSSZ->AddOutputParam("echoFloatReturn", (void*)&ret, XSD_FLOAT);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoFloatArray(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoFloatArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoFloatArrayResponse", "http://soapinterop.org/");
	xsd__float_Array v0 = (xsd__float_Array&)pIWSDZ->GetBasicArray(XSD_FLOAT, "inputFloatArray",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__float_Array ret = pWs->echoFloatArray(v0);
	return pIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&ret),XSD_FLOAT, "echoFloatArrayReturn");
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoStruct(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStructResponse", "http://soapinterop.org/");
	SOAPStruct *v0 = (SOAPStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, "inputStruct", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	SOAPStruct* ret = pWs->echoStruct(v0);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoStructReturn", Axis_URI_SOAPStruct);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoStructArray(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStructArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStructArrayResponse", "http://soapinterop.org/");
	SOAPStruct_Array v0 = (SOAPStruct_Array&)pIWSDZ->GetCmplxArray((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, (void*)Axis_GetSize_SOAPStruct, "inputStructArray", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	SOAPStruct_Array ret = pWs->echoStructArray(v0);
	return pIWSSZ->AddOutputCmplxArrayParam((Axis_Array*)(&ret),(void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "echoStructArrayReturn", Axis_URI_SOAPStruct);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoVoid(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoVoid", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoVoidResponse", "http://soapinterop.org/");
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	pWs->echoVoid();
	return AXIS_SUCCESS;
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoBase64(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoBase64", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoBase64Response", "http://soapinterop.org/");
	xsd__base64Binary v0 = pIWSDZ->GetElementAsBase64Binary("inputBase64",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__base64Binary ret = pWs->echoBase64(v0);
	return pIWSSZ->AddOutputParam("echoBase64Return", (void*)&ret, XSD_BASE64BINARY);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoDate(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoDate", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoDateResponse", "http://soapinterop.org/");
	xsd__dateTime v0 = pIWSDZ->GetElementAsDateTime("inputDate",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__dateTime ret = pWs->echoDate(v0);
	return pIWSSZ->AddOutputParam("echoDateReturn", (void*)&ret, XSD_DATETIME);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoHexBinary(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoHexBinary", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoHexBinaryResponse", "http://soapinterop.org/");
	xsd__hexBinary v0 = pIWSDZ->GetElementAsHexBinary("inputHexBinary",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__hexBinary ret = pWs->echoHexBinary(v0);
	return pIWSSZ->AddOutputParam("echoHexBinaryReturn", (void*)&ret, XSD_HEXBINARY);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoDecimal(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoDecimal", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoDecimalResponse", "http://soapinterop.org/");
	xsd__decimal v0 = pIWSDZ->GetElementAsDecimal("inputDecimal",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__decimal ret = pWs->echoDecimal(v0);
	return pIWSSZ->AddOutputParam("echoDecimalReturn", (void*)&ret, XSD_DECIMAL);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoBoolean(void* pMsg)
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
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoBoolean", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoBooleanResponse", "http://soapinterop.org/");
	xsd__boolean v0 = pIWSDZ->GetElementAsBoolean("inputBoolean",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;
	xsd__boolean ret = pWs->echoBoolean(v0);
	return pIWSSZ->AddOutputParam("echoBooleanReturn", (void*)&ret, XSD_BOOLEAN);
}

