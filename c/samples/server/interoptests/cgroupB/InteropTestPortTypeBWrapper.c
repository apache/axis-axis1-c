/*
 * This is the Wrapper implementation file genarated by WSDL2Ws tool
 *
 */

#include <string.h>
#include "InteropTestPortTypeBWrapper.h"
#include "SOAPStruct.h"
#include "SOAPArrayStruct.h"
#include "SOAPStructStruct.h"

extern int Axis_DeSerialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPArrayStruct(SOAPArrayStruct * param, bool bArray, int nSize);
extern void Axis_Delete_SOAPArrayStruct(SOAPArrayStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPArrayStruct(SOAPArrayStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPArrayStruct();

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct * param, bool bArray, int nSize);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStruct();

extern int Axis_DeSerialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStructStruct(SOAPStructStruct * param, bool bArray, int nSize);
extern void Axis_Delete_SOAPStructStruct(SOAPStructStruct* param, bool bArray, int nSize);
extern int Axis_Serialize_SOAPStructStruct(SOAPStructStruct* param, IWrapperSoapSerializer* pSZ, bool bArray);
extern int Axis_GetSize_SOAPStructStruct();

/*implementation of BasicHandler interface*/
void AXISCALL InteropTestPortTypeBWrapper_OnFault(void*p, void *pMsg){
}

int AXISCALL InteropTestPortTypeBWrapper_Init(void*p){
	return AXIS_SUCCESS;
}

int AXISCALL InteropTestPortTypeBWrapper_Fini(void*p){
	return AXIS_SUCCESS;
}

int AXISCALL InteropTestPortTypeBWrapper_GetType(void*p){
	return WEBSERVICE_HANDLER;
}

AXIS_BINDING_STYLE AXISCALL InteropTestPortTypeBWrapper_GetBindingStyle(void*p){
	return RPC_ENCODED;
}


/*
 * This method invokes the right service method 
 */
int AXISCALL InteropTestPortTypeBWrapper_Invoke(void*p, void *pMsg){
	IMessageData* mc = (IMessageData*)pMsg;
	const AxisChar* method = 0;
	IWrapperSoapDeSerializer DZ = {0,0};
	IWrapperSoapSerializer SZ = {0,0};
	method = mc->_functions->GetOperationName(mc->_object);
	mc->_functions->GetSoapSerializer(mc->_object, &SZ);
	mc->_functions->GetSoapDeSerializer(mc->_object, &DZ);
	if (0 == strcmp(method, "echoStructAsSimpleTypes"))
		return echoStructAsSimpleTypesWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoSimpleTypesAsStruct"))
		return echoSimpleTypesAsStructWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoNestedStruct"))
		return echoNestedStructWrapped(DZ, SZ);
	else if (0 == strcmp(method, "echoNestedArray"))
		return echoNestedArrayWrapped(DZ, SZ);
	else return AXIS_FAIL;
}


/*Methods corresponding to the web service methods*/

/*forward declaration for the c method echoStructAsSimpleTypes */
extern void echoStructAsSimpleTypes(SOAPStruct*, AXIS_OUT_PARAM float*, AXIS_OUT_PARAM int*, AXIS_OUT_PARAM xsd__string*);

/*
 * This method wrap the service method 
 */
int echoStructAsSimpleTypesWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	SOAPStruct* v0;
	float out0;
	int out1;
	xsd__string out2;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoStructAsSimpleTypes", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoStructAsSimpleTypesResponse", "http://soapinterop.org/");
	v0 = (SOAPStruct*)DZ._functions->GetCmplxObject(DZ._object, (void*)Axis_DeSerialize_SOAPStruct
		, (void*)Axis_Create_SOAPStruct, (void*)Axis_Delete_SOAPStruct
		, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	echoStructAsSimpleTypes(v0,&out0,&out1,&out2);
	SZ._functions->AddOutputParam(SZ._object, "outputFloat", (void*)&out0, XSD_FLOAT);
	SZ._functions->AddOutputParam(SZ._object, "outputInteger", (void*)&out1, XSD_INT);
	SZ._functions->AddOutputParam(SZ._object, "outputString", (void*)&out2, XSD_STRING);
	return AXIS_SUCCESS;
}


/*forward declaration for the c method echoSimpleTypesAsStruct */
extern SOAPStruct* echoSimpleTypesAsStruct(float,int,xsd__string);

/*
 * This method wrap the service method 
 */
int echoSimpleTypesAsStructWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	float v0;
	int v1;
	xsd__string v2;
	SOAPStruct* ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoSimpleTypesAsStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoSimpleTypesAsStructResponse", "http://soapinterop.org/");
	v0 = DZ._functions->GetElementAsFloat(DZ._object, 0, 0);
	v1 = DZ._functions->GetElementAsInt(DZ._object, 0, 0);
	v2 = DZ._functions->GetElementAsString(DZ._object, 0, 0);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoSimpleTypesAsStruct(v0,v1,v2);
	return SZ._functions->AddOutputCmplxParam(SZ._object, ret, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "echoSimpleTypesAsStructReturn", 0);
}


/*forward declaration for the c method echoNestedStruct */
extern SOAPStructStruct* echoNestedStruct(SOAPStructStruct*);

/*
 * This method wrap the service method 
 */
int echoNestedStructWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	SOAPStructStruct* v0;
	SOAPStructStruct* ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoNestedStruct", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoNestedStructResponse", "http://soapinterop.org/");
	v0 = (SOAPStructStruct*)DZ._functions->GetCmplxObject(DZ._object, (void*)Axis_DeSerialize_SOAPStructStruct
		, (void*)Axis_Create_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct
		, Axis_TypeName_SOAPStructStruct, Axis_URI_SOAPStructStruct);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoNestedStruct(v0);
	return SZ._functions->AddOutputCmplxParam(SZ._object, ret, (void*)Axis_Serialize_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct, "echoNestedStructReturn", 0);
}


/*forward declaration for the c method echoNestedArray */
extern SOAPArrayStruct* echoNestedArray(SOAPArrayStruct*);

/*
 * This method wrap the service method 
 */
int echoNestedArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)
{
	int nStatus;
	SOAPArrayStruct* v0;
	SOAPArrayStruct* ret;
	if (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, "echoNestedArray", "http://soapinterop.org/")) return AXIS_FAIL;
	SZ._functions->CreateSoapMethod(SZ._object, "echoNestedArrayResponse", "http://soapinterop.org/");
	v0 = (SOAPArrayStruct*)DZ._functions->GetCmplxObject(DZ._object, (void*)Axis_DeSerialize_SOAPArrayStruct
		, (void*)Axis_Create_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct
		, Axis_TypeName_SOAPArrayStruct, Axis_URI_SOAPArrayStruct);
	if (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;
	ret = echoNestedArray(v0);
	return SZ._functions->AddOutputCmplxParam(SZ._object, ret, (void*)Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "echoNestedArrayReturn", 0);
}

