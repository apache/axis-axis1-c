/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortTypeB.cpp: implemtation for the InteropTestPortTypeB.
 *
 */

#include "InteropTestPortTypeB.h"

#include <axis/server/AxisWrapperAPI.h>

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

InteropTestPortTypeB::InteropTestPortTypeB(const char* pchEndPointUri)
{
	m_pCall = new Call();
	m_pCall->setProtocol(APTHTTP);
	m_pCall->setEndpointURI(pchEndPointUri);
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
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return ;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "groupB#echoStructAsSimpleTypes");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStructAsSimpleTypes", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoStructAsSimpleTypesResponse", ""))
		{
			*OutValue0 = m_pCall->getElementAsFloat("outputFloat", 0);
			*OutValue1 = m_pCall->getElementAsInt("outputInteger", 0);
			*OutValue2 = m_pCall->getElementAsString("outputString", 0);
		}
	}
	m_pCall->unInitialize();
}


/*
 * This method wrap the service methodechoSimpleTypesAsStruct
 */
SOAPStruct* InteropTestPortTypeB::echoSimpleTypesAsStruct(float Value0, int Value1, xsd__string Value2)
{
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "groupB#echoSimpleTypesAsStruct");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoSimpleTypesAsStruct", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	m_pCall->addParameter((void*)&Value1, "inputInteger", XSD_INT);
	m_pCall->addParameter((void*)&Value2, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoSimpleTypesAsStructResponse", ""))
		{
			pReturn = (SOAPStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct,"return", 0);
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}


/*
 * This method wrap the service methodechoNestedStruct
 */
SOAPStructStruct* InteropTestPortTypeB::echoNestedStruct(SOAPStructStruct* Value0)
{
	SOAPStructStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "groupB#echoNestedStruct");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoNestedStruct", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStructStruct, (void*)Axis_Delete_SOAPStructStruct, "inputStruct", Axis_URI_SOAPStructStruct);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoNestedStructResponse", ""))
		{
			pReturn = (SOAPStructStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStructStruct, (void*) Axis_Create_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct,"return", 0);
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}


/*
 * This method wrap the service methodechoNestedArray
 */
SOAPArrayStruct* InteropTestPortTypeB::echoNestedArray(SOAPArrayStruct* Value0)
{
	SOAPArrayStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "groupB#echoNestedArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoNestedArray", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*)Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "inputStruct", Axis_URI_SOAPArrayStruct);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoNestedArrayResponse", ""))
		{
			pReturn = (SOAPArrayStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPArrayStruct, (void*) Axis_Create_SOAPArrayStruct, (void*) Axis_Delete_SOAPArrayStruct,"return", 0);
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}

