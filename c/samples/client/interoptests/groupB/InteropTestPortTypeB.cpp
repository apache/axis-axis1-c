///////////////////////////////////////////////////////////////////////
// This is the Client Stub implementation file genarated by WSDL2Ws tool.
// InteropTestPortTypeB.cpp: implemtation for the InteropTestPortTypeB.
//
//////////////////////////////////////////////////////////////////////

#include "InteropTestPortTypeB.h"

#include <axis/common/AxisWrapperAPI.h>

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

InteropTestPortTypeB::InteropTestPortTypeB()
{
	m_pCall = new Call();
	m_pCall->SetProtocol(APTHTTP);
	m_pCall->SetEndpointURI("http://localhost/axis/InteropGroupB");
}

InteropTestPortTypeB::~InteropTestPortTypeB()
{
	delete m_pCall;
}


//Methods corresponding to the web service methods

/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStructAsSimpleTypes
//////////////////////////////////////////////////////////////////
void InteropTestPortTypeB::echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM AxisChar** outValue0, AXIS_OUT_PARAM int* outValue1, AXIS_OUT_PARAM float* outValue2)
{
	int nStatus;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER)) return;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "InteropGroupB#echoStructAsSimpleTypes");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStructAsSimpleTypes", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, "inputStruct", "");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoStructAsSimpleTypesResponse", "http://soapinterop.org/"))
		{
			*outValue0 = m_pCall->GetElementAsString(0,0);
			*outValue1 = m_pCall->GetElementAsInt(0,0);
			*outValue2 = m_pCall->GetElementAsFloat(0,0);
		}
	}
	m_pCall->UnInitialize();
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoSimpleTypesAsStruct
//////////////////////////////////////////////////////////////////
SOAPStruct* InteropTestPortTypeB::echoSimpleTypesAsStruct(float Value0, int Value1, AxisChar* Value2)
{
	int nStatus;
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "InteropGroupB#echoSimpleTypesAsStruct");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoSimpleTypesAsStruct", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	m_pCall->AddParameter((void*)&Value1, "inputInteger", XSD_INT);
	m_pCall->AddParameter((void*)&Value2, "inputString", XSD_STRING);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoSimpleTypesAsStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, Axis_TypeName_SOAPStruct, Axis_URI_SOAPStruct);
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodecho2DStringArray
//////////////////////////////////////////////////////////////////
ArrayOfString2D InteropTestPortTypeB::echo2DStringArray(ArrayOfString2D Value0)
{
	int nStatus;
	ArrayOfString2D RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "InteropGroupB#echo2DStringArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echo2DStringArray", "http://soapinterop.org/");
	m_pCall->AddBasicArrayParameter((Axis_Array*)(&Value0), XSD_STRING, "input2DStringArray");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS != nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echo2DStringArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOfString2D&) m_pCall->GetBasicArray(XSD_STRING,0,0);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoNestedStruct
//////////////////////////////////////////////////////////////////
SOAPStructStruct* InteropTestPortTypeB::echoNestedStruct(SOAPStructStruct* Value0)
{
	int nStatus;
	SOAPStructStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "InteropGroupB#echoNestedStruct");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoNestedStruct", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*) Axis_Serialize_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct, "inputStruct", "");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoNestedStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStructStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPStructStruct, (void*) Axis_Create_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct, Axis_TypeName_SOAPStructStruct, Axis_URI_SOAPStructStruct);
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoNestedArray
//////////////////////////////////////////////////////////////////
SOAPArrayStruct* InteropTestPortTypeB::echoNestedArray(SOAPArrayStruct* Value0)
{
	int nStatus;
	SOAPArrayStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "InteropGroupB#echoNestedArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoNestedArray", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*) Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "inputStruct", "");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoNestedArrayResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPArrayStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPArrayStruct, (void*) Axis_Create_SOAPArrayStruct, (void*) Axis_Delete_SOAPArrayStruct, Axis_TypeName_SOAPArrayStruct, Axis_URI_SOAPArrayStruct);
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}

