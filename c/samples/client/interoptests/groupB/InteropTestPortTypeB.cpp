/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortTypeB.cpp: implemtation for the InteropTestPortTypeB.
 *
 */

#include "InteropTestPortTypeB.h"

#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
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

InteropTestPortTypeB::InteropTestPortTypeB()
{
	m_pCall = new Call();
	m_pCall->SetProtocol(APTHTTP);
	m_pCall->SetEndpointURI("http://localhost/axis/groupB");
}

InteropTestPortTypeB::~InteropTestPortTypeB()
{
	delete m_pCall;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoStructAsSimpleTypes
 */
void InteropTestPortTypeB::echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM  float *OutValue0, AXIS_OUT_PARAM  int *OutValue1, AXIS_OUT_PARAM  xsd__string *OutValue2)
{
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return ;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropGroupB#echoStructAsSimpleTypes");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStructAsSimpleTypes", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoStructAsSimpleTypesResponse", ""))
		{
			*OutValue0 = m_pCall->GetElementAsFloat("outputFloat", 0);
			*OutValue1 = m_pCall->GetElementAsInt("outputInteger", 0);
			*OutValue2 = m_pCall->GetElementAsString("outputString", 0);
		}
	}
	m_pCall->UnInitialize();
}


/*
 * This method wrap the service methodechoSimpleTypesAsStruct
 */
SOAPStruct* InteropTestPortTypeB::echoSimpleTypesAsStruct(float Value0, int Value1, xsd__string Value2)
{
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropGroupB#echoSimpleTypesAsStruct");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoSimpleTypesAsStruct", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	m_pCall->AddParameter((void*)&Value1, "inputInteger", XSD_INT);
	m_pCall->AddParameter((void*)&Value2, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoSimpleTypesAsStructResponse", ""))
		{
			pReturn = (SOAPStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct,"return", 0);
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}


/*
 * This method wrap the service methodechoNestedStruct
 */
SOAPStructStruct* InteropTestPortTypeB::echoNestedStruct(SOAPStructStruct* Value0)
{
	SOAPStructStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropGroupB#echoNestedStruct");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoNestedStruct", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct, "inputStruct", Axis_URI_SOAPStructStruct);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoNestedStructResponse", ""))
		{
			pReturn = (SOAPStructStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPStructStruct, (void*) Axis_Create_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct,"return", 0);
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}


/*
 * This method wrap the service methodechoNestedArray
 */
SOAPArrayStruct* InteropTestPortTypeB::echoNestedArray(SOAPArrayStruct* Value0)
{
	SOAPArrayStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "InteropGroupB#echoNestedArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoNestedArray", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*)Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "inputStruct", Axis_URI_SOAPArrayStruct);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("echoNestedArrayResponse", ""))
		{
			pReturn = (SOAPArrayStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPArrayStruct, (void*) Axis_Create_SOAPArrayStruct, (void*) Axis_Delete_SOAPArrayStruct,"return", 0);
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}

