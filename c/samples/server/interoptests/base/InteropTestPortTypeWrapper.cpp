///////////////////////////////////////////////////////////////////////
//This is the Service implementation CPP file genarated by theWSDL2Ws.
//		InteropTestPortTypeWrapper.cpp: implemtation for the InteropTestPortTypeWrapper.
//
//////////////////////////////////////////////////////////////////////

#include "InteropTestPortTypeWrapper.h"

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(void* pObj, bool bArray = false, int nSize=0);
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

//implementation of WrapperClassHandler interface
static void InteropTestPortTypeWrapper_OnFault(InteropTestPortTypeWrapper* object, IMessageData *pMsg)
{
	object->OnFault(pMsg);
}

void InteropTestPortTypeWrapper::OnFault(void *pMsg)
{
}

static int InteropTestPortTypeWrapper_Init(InteropTestPortTypeWrapper* object)
{
	return object->Init();
}

int InteropTestPortTypeWrapper::Init()
{
	return AXIS_SUCCESS;
}

static int InteropTestPortTypeWrapper_Fini(InteropTestPortTypeWrapper* object)
{
	return object->Fini();
}

int InteropTestPortTypeWrapper::Fini()
{
	return AXIS_SUCCESS;
}

static int InteropTestPortTypeWrapper_Invoke(InteropTestPortTypeWrapper* object, IMessageData *mc)
{
	return object->Invoke(mc);
}

static AXIS_BINDING_STYLE AXISCALL InteropTestPortTypeWrapper_GetBindingStyle(InteropTestPortTypeWrapper* object)
{
	return object->GetBindingStyle();
}

AXIS_BINDING_STYLE AXISCALL InteropTestPortTypeWrapper::GetBindingStyle()
{
	return RPC_ENCODED;
}

/////////////////////////////////////////////////////////////////
// This method invokes the right service method 
//////////////////////////////////////////////////////////////////
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

//Methods corresponding to the web service methods

/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoString(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	/* check whether we have got correct message */
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoString", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStringResponse", "http://soapinterop.org/");
	AxisChar* v0 = pIWSDZ->GetElementAsString(0,0);
	AxisChar* ret = pWs->echoString(v0);
	return pIWSSZ->AddOutputParam("echoStringReturn", (void*)&ret, XSD_STRING);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoStringArray(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStringArray", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStringArrayResponse", "http://soapinterop.org/");
	ArrayOfstring v0 = (ArrayOfstring&)pIWSDZ->GetBasicArray(XSD_STRING,0,0);
	ArrayOfstring ret = pWs->echoStringArray(v0);
	return pIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&ret), XSD_STRING, "echoStringArrayReturn");
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoInteger(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoInteger", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoIntegerResponse", "http://soapinterop.org/");
	int v0 = pIWSDZ->GetElementAsInt(0,0);
	int ret = pWs->echoInteger(v0);
	return pIWSSZ->AddOutputParam("echoIntegerReturn", (void*)&ret, XSD_INT);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoIntegerArray(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoIntegerArray", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoIntegerArrayResponse", "http://soapinterop.org/");
	ArrayOfint v0 = (ArrayOfint&)pIWSDZ->GetBasicArray(XSD_INT,0,0);
	ArrayOfint ret = pWs->echoIntegerArray(v0);
	return pIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&ret), XSD_INT, "echoIntegerArrayReturn");
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoFloat(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoFloat", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoFloatResponse", "http://soapinterop.org/");
	float v0 = pIWSDZ->GetElementAsFloat(0,0);
	float ret = pWs->echoFloat(v0);
	return pIWSSZ->AddOutputParam("echoFloatReturn", (void*)&ret, XSD_FLOAT);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoFloatArray(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoFloatArray", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoFloatArrayResponse", "http://soapinterop.org/");
	ArrayOffloat v0 = (ArrayOffloat&)pIWSDZ->GetBasicArray(XSD_FLOAT,0,0);
	ArrayOffloat ret = pWs->echoFloatArray(v0);
	return pIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&ret), XSD_FLOAT, "echoFloatArrayReturn");
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoStruct(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStruct", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStructResponse", "http://soapinterop.org/");
	SOAPStruct *v0 = (SOAPStruct*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	SOAPStruct *ret = pWs->echoStruct(v0);
	return pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoStructReturn", "http://soapinterop.org/");
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoStructArray(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoStructArray", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoStructArrayResponse", "http://soapinterop.org/");
	ArrayOfSOAPStruct v0 = (ArrayOfSOAPStruct&)pIWSDZ->GetCmplxArray((void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, (void*)Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	ArrayOfSOAPStruct ret = pWs->echoStructArray(v0);
	return pIWSSZ->AddOutputCmplxArrayParam((Axis_Array*)(&ret),(void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoVoid(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoVoid", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoVoidResponse", "http://soapinterop.org/");
	pWs->echoVoid();
	return AXIS_SUCCESS;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoBase64(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoBase64", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoBase64Response", "http://soapinterop.org/");
	xsd__base64Binary v0 = pIWSDZ->GetElementAsBase64Binary(0,0);
	xsd__base64Binary ret = pWs->echoBase64(v0);
	return pIWSSZ->AddOutputParam("echoBase64Return", (void*)&ret, XSD_BASE64BINARY);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoDate(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoDate", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoDateResponse", "http://soapinterop.org/");
	xsd__dateTime v0 = pIWSDZ->GetElementAsDateTime(0,0);
	xsd__dateTime ret = pWs->echoDate(v0);
	return pIWSSZ->AddOutputParam("echoDateReturn", (void*)&ret, XSD_DATETIME);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoHexBinary(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoHexBinary", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoHexBinaryResponse", "http://soapinterop.org/");
	xsd__hexBinary v0 = pIWSDZ->GetElementAsHexBinary(0,0);
	xsd__hexBinary ret = pWs->echoHexBinary(v0);
	return pIWSSZ->AddOutputParam("echoHexBinaryReturn", (void*)&ret, XSD_HEXBINARY);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoDecimal(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoDecimal", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoDecimalResponse", "http://soapinterop.org/");
	xsd__decimal v0 = pIWSDZ->GetElementAsDecimal(0,0);
	xsd__decimal ret = pWs->echoDecimal(v0);
	return pIWSSZ->AddOutputParam("echoDecimalReturn", (void*)&ret, XSD_DECIMAL);
}


/////////////////////////////////////////////////////////////////
// This method wrap the service method 
//////////////////////////////////////////////////////////////////
int InteropTestPortTypeWrapper::echoBoolean(IMessageData* mc)
{
	IWrapperSoapSerializer *pIWSSZ = NULL;
	mc->GetSoapSerializer(&pIWSSZ);
	if (!pIWSSZ) return AXIS_FAIL;
	IWrapperSoapDeSerializer *pIWSDZ = NULL;
	mc->GetSoapDeSerializer(&pIWSDZ);
	if (!pIWSDZ) return AXIS_FAIL;
	if (AXIS_SUCCESS != pIWSDZ->CheckMessageBody("echoBoolean", "")) return AXIS_FAIL;
	pIWSSZ->CreateSoapMethod("echoBooleanResponse", "http://soapinterop.org/");
	xsd__boolean v0 = pIWSDZ->GetElementAsBoolean(0,0);
	xsd__boolean ret = pWs->echoBoolean(v0);
	return pIWSSZ->AddOutputParam("echoBooleanReturn", (void*)&ret, XSD_BOOLEAN);
}

