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
void AXISCALL OnFault(void*p, IMessageData *pMsg)
{
}

int AXISCALL Init(void*p)
{
	return AXIS_SUCCESS;
}

int AXISCALL Fini(void*p)
{
	return AXIS_SUCCESS;
}

AXIS_BINDING_STYLE AXISCALL GetBindingStyle(void*p)
{
	return RPC_ENCODED;
}


/*
 * This method invokes the right service method 
 */
int AXISCALL Invoke(void*p, IMessageData *mc)
{
	const AxisChar* method = 0;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	method = pmcX->GetOperationName(mc);
	if (0 == strcmp(method, "echoString"))
		return echoStringWrapped(mc);
	else if (0 == strcmp(method, "echoStringArray"))
		return echoStringArrayWrapped(mc);
	else if (0 == strcmp(method, "echoInteger"))
		return echoIntegerWrapped(mc);
	else if (0 == strcmp(method, "echoIntegerArray"))
		return echoIntegerArrayWrapped(mc);
	else if (0 == strcmp(method, "echoFloat"))
		return echoFloatWrapped(mc);
	else if (0 == strcmp(method, "echoFloatArray"))
		return echoFloatArrayWrapped(mc);
	else if (0 == strcmp(method, "echoStruct"))
		return echoStructWrapped(mc);
	else if (0 == strcmp(method, "echoStructArray"))
		return echoStructArrayWrapped(mc);
	else if (0 == strcmp(method, "echoVoid"))
		return echoVoidWrapped(mc);
	else if (0 == strcmp(method, "echoBase64"))
		return echoBase64Wrapped(mc);
	else if (0 == strcmp(method, "echoDate"))
		return echoDateWrapped(mc);
	else if (0 == strcmp(method, "echoHexBinary"))
		return echoHexBinaryWrapped(mc);
	else if (0 == strcmp(method, "echoDecimal"))
		return echoDecimalWrapped(mc);
	else if (0 == strcmp(method, "echoBoolean"))
		return echoBooleanWrapped(mc);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*forward declaration for the c method echoString */
extern xsd__string echoString(xsd__string);

/*
 * This method wrap the service method 
 */
int echoStringWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__string v0;
	xsd__string ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoString", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoStringResponse", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsString(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoString(v0);
	return pSZX->AddOutputParam(pSZ, "echoStringReturn", (void*)&ret, XSD_STRING);
}


/*forward declaration for the c method echoStringArray */
extern xsd__string_Array echoStringArray(xsd__string_Array);

/*
 * This method wrap the service method 
 */
int echoStringArrayWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__string_Array v0;
	xsd__string_Array ret;
	Axis_Array array;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoStringArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoStringArrayResponse", "http://soapinterop.org/");

	array = pDZX->GetBasicArray(pDZ, XSD_STRING, 0, 0);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoStringArray(v0);
	return pSZX->AddOutputBasicArrayParam(pSZ, (Axis_Array*)(&ret),XSD_STRING, "echoStringArrayReturn");
}


/*forward declaration for the c method echoInteger */
extern int echoInteger(int);

/*
 * This method wrap the service method 
 */
int echoIntegerWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	int v0;
	int ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoInteger", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoIntegerResponse", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsInt(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoInteger(v0);
	return pSZX->AddOutputParam(pSZ, "echoIntegerReturn", (void*)&ret, XSD_INT);
}


/*forward declaration for the c method echoIntegerArray */
extern xsd__int_Array echoIntegerArray(xsd__int_Array);

/*
 * This method wrap the service method 
 */
int echoIntegerArrayWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__int_Array v0;
	xsd__int_Array ret;
	Axis_Array array;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoIntegerArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoIntegerArrayResponse", "http://soapinterop.org/");

	array = pDZX->GetBasicArray(pDZ, XSD_INT, 0, 0);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoIntegerArray(v0);
	return pSZX->AddOutputBasicArrayParam(pSZ, (Axis_Array*)(&ret),XSD_INT, "echoIntegerArrayReturn");
}


/*forward declaration for the c method echoFloat */
extern float echoFloat(float);

/*
 * This method wrap the service method 
 */
int echoFloatWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	float v0;
	float ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoFloat", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoFloatResponse", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsFloat(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoFloat(v0);
	return pSZX->AddOutputParam(pSZ, "echoFloatReturn", (void*)&ret, XSD_FLOAT);
}


/*forward declaration for the c method echoFloatArray */
extern xsd__float_Array echoFloatArray(xsd__float_Array);

/*
 * This method wrap the service method 
 */
int echoFloatArrayWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__float_Array v0;
	xsd__float_Array ret;
	Axis_Array array;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoFloatArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoFloatArrayResponse", "http://soapinterop.org/");

	array = pDZX->GetBasicArray(pDZ, XSD_FLOAT, 0, 0);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoFloatArray(v0);
	return pSZX->AddOutputBasicArrayParam(pSZ, (Axis_Array*)(&ret),XSD_FLOAT, "echoFloatArrayReturn");
}


/*forward declaration for the c method echoStruct */
extern SOAPStruct* echoStruct(SOAPStruct*);

/*
 * This method wrap the service method 
 */
int echoStructWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	SOAPStruct* v0;
	SOAPStruct* ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoStructResponse", "http://soapinterop.org/");

	v0 = (SOAPStruct*)pDZX->GetCmplxObject(pDZ, (void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoStruct(v0);
	return pSZX->AddOutputCmplxParam(pSZ, ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoStructReturn", 0);
}


/*forward declaration for the c method echoStructArray */
extern SOAPStruct_Array echoStructArray(SOAPStruct_Array);

/*
 * This method wrap the service method 
 */
int echoStructArrayWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	SOAPStruct_Array v0;
	SOAPStruct_Array ret;
	Axis_Array array;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoStructArray", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoStructArrayResponse", "http://soapinterop.org/");

	array = pDZX->GetCmplxArray(pDZ, (void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, (void*)Axis_GetSize_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	memcpy(&v0, &array, sizeof(Axis_Array));
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoStructArray(v0);
	return pSZX->AddOutputCmplxArrayParam(pSZ, (Axis_Array*)(&ret),(void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "echoStructArrayReturn", 0);
}


/*forward declaration for the c method echoVoid */
extern void echoVoid();

/*
 * This method wrap the service method 
 */
int echoVoidWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoVoid", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoVoidResponse", "http://soapinterop.org/");

	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	echoVoid();
	return AXIS_SUCCESS;
}


/*forward declaration for the c method echoBase64 */
extern xsd__base64Binary echoBase64(xsd__base64Binary);

/*
 * This method wrap the service method 
 */
int echoBase64Wrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__base64Binary v0;
	xsd__base64Binary ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoBase64", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoBase64Response", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsBase64Binary(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoBase64(v0);
	return pSZX->AddOutputParam(pSZ, "echoBase64Return", (void*)&ret, XSD_BASE64BINARY);
}


/*forward declaration for the c method echoDate */
extern xsd__dateTime echoDate(xsd__dateTime);

/*
 * This method wrap the service method 
 */
int echoDateWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__dateTime v0;
	xsd__dateTime ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoDate", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoDateResponse", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsDateTime(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoDate(v0);
	return pSZX->AddOutputParam(pSZ, "echoDateReturn", (void*)&ret, XSD_DATETIME);
}


/*forward declaration for the c method echoHexBinary */
extern xsd__hexBinary echoHexBinary(xsd__hexBinary);

/*
 * This method wrap the service method 
 */
int echoHexBinaryWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__hexBinary v0;
	xsd__hexBinary ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoHexBinary", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoHexBinaryResponse", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsHexBinary(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoHexBinary(v0);
	return pSZX->AddOutputParam(pSZ, "echoHexBinaryReturn", (void*)&ret, XSD_HEXBINARY);
}


/*forward declaration for the c method echoDecimal */
extern xsd__decimal echoDecimal(xsd__decimal);

/*
 * This method wrap the service method 
 */
int echoDecimalWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__decimal v0;
	xsd__decimal ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoDecimal", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoDecimalResponse", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsDecimal(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoDecimal(v0);
	return pSZX->AddOutputParam(pSZ, "echoDecimalReturn", (void*)&ret, XSD_DECIMAL);
}


/*forward declaration for the c method echoBoolean */
extern xsd__boolean echoBoolean(xsd__boolean);

/*
 * This method wrap the service method 
 */
int echoBooleanWrapped(IMessageData* mc)
{
	int nStatus;
	IMessageDataFunctions* pmcX = mc->__vfptr;
	IWrapperSoapDeSerializer* pDZ = 0;
	IWrapperSoapDeSerializerFunctions* pDZX = 0;
	IWrapperSoapSerializer* pSZ = 0;
	IWrapperSoapSerializerFunctions* pSZX = 0;
	xsd__boolean v0;
	xsd__boolean ret;
	pmcX->GetSoapSerializer(mc, &pSZ);
	if (!pSZ) return AXIS_FAIL;
	pSZX = pSZ->__vfptr;
	if (!pSZX) return AXIS_FAIL;
	pmcX->GetSoapDeSerializer(mc, &pDZ);
	if (!pDZ) return AXIS_FAIL;
	pDZX = pDZ->__vfptr;
	if (!pDZX) return AXIS_FAIL;
	if (AXIS_SUCCESS != pDZX->CheckMessageBody(pDZ, "echoBoolean", "http://soapinterop.org/")) return AXIS_FAIL;
	pSZX->CreateSoapMethod(pSZ, "echoBooleanResponse", "http://soapinterop.org/");

	v0 = pDZX->GetElementAsBoolean(pDZ, 0, 0);
	if (AXIS_SUCCESS != (nStatus = pDZX->GetStatus(pDZ))) return nStatus;
	ret = echoBoolean(v0);
	return pSZX->AddOutputParam(pSZ, "echoBooleanReturn", (void*)&ret, XSD_BOOLEAN);
}

