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
void InteropTestPortTypeWrapper::onFault(void *pMsg)
{
}

int InteropTestPortTypeWrapper::init()
{
	return AXIS_SUCCESS;
}

int InteropTestPortTypeWrapper::fini()
{
	return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int InteropTestPortTypeWrapper::invoke(void *pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar *method = mc->getOperationName();
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
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoString", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoStringResponse", "http://soapinterop.org/");
	xsd__string v0 = pIWSDZ->getElementAsString("inputString",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__string ret = pWs->echoString(v0);
	return pIWSSZ->addOutputParam("echoStringReturn", (void*)&ret, XSD_STRING);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoStringArray(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoStringArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoStringArrayResponse", "http://soapinterop.org/");
	xsd__string_Array v0 = (xsd__string_Array&)pIWSDZ->getBasicArray(XSD_STRING, "inputStringArray",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__string_Array ret = pWs->echoStringArray(v0);
	return pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&ret),XSD_STRING, "echoStringArrayReturn");
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoInteger(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoInteger", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoIntegerResponse", "http://soapinterop.org/");
	int v0 = pIWSDZ->getElementAsInt("inputInteger",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	int ret = pWs->echoInteger(v0);
	return pIWSSZ->addOutputParam("echoIntegerReturn", (void*)&ret, XSD_INT);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoIntegerArray(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoIntegerArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoIntegerArrayResponse", "http://soapinterop.org/");
	xsd__int_Array v0 = (xsd__int_Array&)pIWSDZ->getBasicArray(XSD_INT, "inputIntegerArray",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__int_Array ret = pWs->echoIntegerArray(v0);
	return pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&ret),XSD_INT, "echoIntegerArrayReturn");
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoFloat(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoFloat", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoFloatResponse", "http://soapinterop.org/");
	float v0 = pIWSDZ->getElementAsFloat("inputFloat",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	float ret = pWs->echoFloat(v0);
	return pIWSSZ->addOutputParam("echoFloatReturn", (void*)&ret, XSD_FLOAT);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoFloatArray(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoFloatArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoFloatArrayResponse", "http://soapinterop.org/");
	xsd__float_Array v0 = (xsd__float_Array&)pIWSDZ->getBasicArray(XSD_FLOAT, "inputFloatArray",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__float_Array ret = pWs->echoFloatArray(v0);
	return pIWSSZ->addOutputBasicArrayParam((Axis_Array*)(&ret),XSD_FLOAT, "echoFloatArrayReturn");
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoStruct(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoStructResponse", "http://soapinterop.org/");
	SOAPStruct *v0 = (SOAPStruct*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, "inputStruct", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	SOAPStruct* ret = pWs->echoStruct(v0);
	return pIWSSZ->addOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoStructReturn", Axis_URI_SOAPStruct);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoStructArray(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoStructArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoStructArrayResponse", "http://soapinterop.org/");
	SOAPStruct_Array v0 = (SOAPStruct_Array&)pIWSDZ->getCmplxArray((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, (void*)Axis_GetSize_SOAPStruct, "inputStructArray", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	SOAPStruct_Array ret = pWs->echoStructArray(v0);
	return pIWSSZ->addOutputCmplxArrayParam((Axis_Array*)(&ret),(void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "echoStructArrayReturn", Axis_URI_SOAPStruct);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoVoid(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoVoid", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoVoidResponse", "http://soapinterop.org/");
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
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
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoBase64", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoBase64Response", "http://soapinterop.org/");
	xsd__base64Binary v0 = pIWSDZ->getElementAsBase64Binary("inputBase64",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__base64Binary ret = pWs->echoBase64(v0);
	return pIWSSZ->addOutputParam("echoBase64Return", (void*)&ret, XSD_BASE64BINARY);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoDate(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoDate", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoDateResponse", "http://soapinterop.org/");
	xsd__dateTime v0 = pIWSDZ->getElementAsDateTime("inputDate",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__dateTime ret = pWs->echoDate(v0);
	return pIWSSZ->addOutputParam("echoDateReturn", (void*)&ret, XSD_DATETIME);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoHexBinary(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoHexBinary", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoHexBinaryResponse", "http://soapinterop.org/");
	xsd__hexBinary v0 = pIWSDZ->getElementAsHexBinary("inputHexBinary",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__hexBinary ret = pWs->echoHexBinary(v0);
	return pIWSSZ->addOutputParam("echoHexBinaryReturn", (void*)&ret, XSD_HEXBINARY);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoDecimal(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoDecimal", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoDecimalResponse", "http://soapinterop.org/");
	xsd__decimal v0 = pIWSDZ->getElementAsDecimal("inputDecimal",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__decimal ret = pWs->echoDecimal(v0);
	return pIWSSZ->addOutputParam("echoDecimalReturn", (void*)&ret, XSD_DECIMAL);
}


/*
 * This method wrap the service method 
 */
int InteropTestPortTypeWrapper::echoBoolean(void* pMsg)
{
	IMessageData* mc = (IMessageData*)pMsg;
	int nStatus;
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->getSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->getSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->checkMessageBody("echoBoolean", "http://soapinterop.org/")) return AXIS_FAIL;
	pIWSSZ->createSoapMethod("echoBooleanResponse", "http://soapinterop.org/");
	xsd__boolean v0 = pIWSDZ->getElementAsBoolean("inputBoolean",0);
	if (AXIS_SUCCESS != (nStatus = pIWSDZ->getStatus())) return nStatus;
	xsd__boolean ret = pWs->echoBoolean(v0);
	return pIWSSZ->addOutputParam("echoBooleanReturn", (void*)&ret, XSD_BOOLEAN);
}

