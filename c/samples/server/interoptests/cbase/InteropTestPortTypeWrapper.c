/*
 * This is the Wrapper implementation file genarated by WSDL2Ws tool
 *
 */

#include <string.h>
#include "InteropTestPortTypeWrapper.h"
#include "SOAPStruct.h"
#include "SOAPStruct_Array.h"

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct * param, bool bArray, int nSize);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStruct();

/*implementation of BasicHandler interface*/
void AXISCALL InteropTestPortTypeWrapper_OnFault(void*p, void *pMsg){
}

int AXISCALL InteropTestPortTypeWrapper_Init(void*p){
	return AXIS_SUCCESS;
}

int AXISCALL InteropTestPortTypeWrapper_Fini(void*p){
	return AXIS_SUCCESS;
}

int AXISCALL InteropTestPortTypeWrapper_GetType(void*p){
	return WEBSERVICE_HANDLER;
}

AXIS_BINDING_STYLE AXISCALL InteropTestPortTypeWrapper_GetBindingStyle(void*p){
	return RPC_ENCODED;
}


/*
 * This method invokes the right service method 
 */
int AXISCALL InteropTestPortTypeWrapper_Invoke(void*p, void *pMsg){
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar* method = 0;
	IWrapperSoapDeSerializer DZ = {0,0};
	IWrapperSoapSerializer SZ = {0,0};
	method = mc->_functions->GetOperationName(mc->_object);
	mc->_functions->GetSoapSerializer(mc->_object, &SZ);
	mc->_functions->GetSoapDeSerializer(mc->_object, &DZ);
	if (0 == strcmp(method, "echoString"))
		return echoStringWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoStringArray"))
		return echoStringArrayWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoInteger"))
		return echoIntegerWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoIntegerArray"))
		return echoIntegerArrayWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoFloat"))
		return echoFloatWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoFloatArray"))
		return echoFloatArrayWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoStruct"))
		return echoStructWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoStructArray"))
		return echoStructArrayWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoVoid"))
		return echoVoidWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoBase64"))
		return echoBase64Wrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoDate"))
		return echoDateWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoHexBinary"))
		return echoHexBinaryWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoDecimal"))
		return echoDecimalWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoBoolean"))
		return echoBooleanWrapped(DZ, SZ);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*forward declaration for the c method echoString */
extern xsd__string echoString(xsd__string);

/*
 * This method wrap the service method 
 */
int echoStringWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__string v0;
	xsd__string ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoString", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoStringResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsString(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoString(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoStringReturn", (void*)&ret, XSD_STRING);
}


/*forward declaration for the c method echoStringArray */
extern xsd__string_Array echoStringArray(xsd__string_Array);

/*
 * This method wrap the service method 
 */
int echoStringArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__string_Array v0;
	xsd__string_Array ret;
	Axis_Array array;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoStringArray", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoStringArrayResponse", "http://soapinterop.org/");
	array = DZ._functions->GetBasicArray(DZ._object, XSD_STRING, 0, 0);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoStringArray(v0);
	return SZ._functions->AddOutputBasicArrayParam(SZ._object, (Axis_Array*)(&ret),XSD_STRING, "echoStringArrayReturn");
}


/*forward declaration for the c method echoInteger */
extern int echoInteger(int);

/*
 * This method wrap the service method 
 */
int echoIntegerWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	int v0;
	int ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoInteger", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoIntegerResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsInt(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoInteger(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoIntegerReturn", (void*)&ret, XSD_INT);
}


/*forward declaration for the c method echoIntegerArray */
extern xsd__int_Array echoIntegerArray(xsd__int_Array);

/*
 * This method wrap the service method 
 */
int echoIntegerArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__int_Array v0;
	xsd__int_Array ret;
	Axis_Array array;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoIntegerArray", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoIntegerArrayResponse", "http://soapinterop.org/");
	array = DZ._functions->GetBasicArray(DZ._object, XSD_INT, 0, 0);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoIntegerArray(v0);
	return SZ._functions->AddOutputBasicArrayParam(SZ._object, (Axis_Array*)(&ret),XSD_INT, "echoIntegerArrayReturn");
}


/*forward declaration for the c method echoFloat */
extern float echoFloat(float);

/*
 * This method wrap the service method 
 */
int echoFloatWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	float v0;
	float ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoFloat", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoFloatResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsFloat(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoFloat(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoFloatReturn", (void*)&ret, XSD_FLOAT);
}


/*forward declaration for the c method echoFloatArray */
extern xsd__float_Array echoFloatArray(xsd__float_Array);

/*
 * This method wrap the service method 
 */
int echoFloatArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__float_Array v0;
	xsd__float_Array ret;
	Axis_Array array;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoFloatArray", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoFloatArrayResponse", "http://soapinterop.org/");
	array = DZ._functions->GetBasicArray(DZ._object, XSD_FLOAT, 0, 0);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoFloatArray(v0);
	return SZ._functions->AddOutputBasicArrayParam(SZ._object, (Axis_Array*)(&ret),XSD_FLOAT, "echoFloatArrayReturn");
}


/*forward declaration for the c method echoStruct */
extern SOAPStruct* echoStruct(SOAPStruct*);

/*
 * This method wrap the service method 
 */
int echoStructWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	SOAPStruct* v0;
	SOAPStruct* ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoStructResponse", "http://soapinterop.org/");
	v0 = (SOAPStruct*)DZ._functions->GetCmplxObject(DZ._object, (void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoStruct(v0);
	return SZ._functions->AddOutputCmplxParam(SZ._object, ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoStructReturn", Axis_URI_SOAPStruct);
}


/*forward declaration for the c method echoStructArray */
extern SOAPStruct_Array echoStructArray(SOAPStruct_Array);

/*
 * This method wrap the service method 
 */
int echoStructArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	SOAPStruct_Array v0;
	SOAPStruct_Array ret;
	Axis_Array array;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoStructArray", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoStructArrayResponse", "http://soapinterop.org/");
	array = DZ._functions->GetCmplxArray(DZ._object, (void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, (void*)Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoStructArray(v0);
	return SZ._functions->AddOutputCmplxArrayParam(SZ._object, (Axis_Array*)(&ret),(void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "echoStructArrayReturn", Axis_URI_SOAPStruct);
}


/*forward declaration for the c method echoVoid */
extern void echoVoid();

/*
 * This method wrap the service method 
 */
int echoVoidWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoVoid", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoVoidResponse", "http://soapinterop.org/");
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	echoVoid();
	return AXIS_SUCCESS;
}


/*forward declaration for the c method echoBase64 */
extern xsd__base64Binary echoBase64(xsd__base64Binary);

/*
 * This method wrap the service method 
 */
int echoBase64Wrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__base64Binary v0;
	xsd__base64Binary ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoBase64", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoBase64Response", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsBase64Binary(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoBase64(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoBase64Return", (void*)&ret, XSD_BASE64BINARY);
}


/*forward declaration for the c method echoDate */
extern xsd__dateTime echoDate(xsd__dateTime);

/*
 * This method wrap the service method 
 */
int echoDateWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__dateTime v0;
	xsd__dateTime ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoDate", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoDateResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsDateTime(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoDate(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoDateReturn", (void*)&ret, XSD_DATETIME);
}


/*forward declaration for the c method echoHexBinary */
extern xsd__hexBinary echoHexBinary(xsd__hexBinary);

/*
 * This method wrap the service method 
 */
int echoHexBinaryWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__hexBinary v0;
	xsd__hexBinary ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoHexBinary", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoHexBinaryResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsHexBinary(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoHexBinary(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoHexBinaryReturn", (void*)&ret, XSD_HEXBINARY);
}


/*forward declaration for the c method echoDecimal */
extern xsd__decimal echoDecimal(xsd__decimal);

/*
 * This method wrap the service method 
 */
int echoDecimalWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__decimal v0;
	xsd__decimal ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoDecimal", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoDecimalResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsDecimal(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoDecimal(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoDecimalReturn", (void*)&ret, XSD_DECIMAL);
}


/*forward declaration for the c method echoBoolean */
extern xsd__boolean echoBoolean(xsd__boolean);

/*
 * This method wrap the service method 
 */
int echoBooleanWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	xsd__boolean v0;
	xsd__boolean ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoBoolean", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoBooleanResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsBoolean(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoBoolean(v0);
	return SZ._functions->AddOutputParam(SZ._object, "echoBooleanReturn", (void*)&ret, XSD_BOOLEAN);
}

