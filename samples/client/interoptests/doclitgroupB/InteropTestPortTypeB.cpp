///////////////////////////////////////////////////////////////////////
// This is the Client Stub implementation file genarated by WSDL2Ws tool.
// InteropTestPortTypeB.cpp: implemtation for the InteropTestPortTypeB.
//
//////////////////////////////////////////////////////////////////////

#include "InteropTestPortTypeB.h"

#include <axis/server/AxisWrapperAPI.hpp>

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


//Methods corresponding to the web service methods

/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStructAsSimpleTypes
//////////////////////////////////////////////////////////////////
void InteropTestPortTypeB::echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM AxisChar** outValue0, AXIS_OUT_PARAM int* outValue1, AXIS_OUT_PARAM float* outValue2)
{
	int nStatus;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER, 0)) return;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "groupBDL#echoStructAsSimpleTypes");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStructAsSimpleTypes", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, "inputStruct", "");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoStructAsSimpleTypesResponse", "http://soapinterop.org/"))
		{
			*outValue0 = m_pCall->getElementAsString("String",0);
			*outValue1 = m_pCall->getElementAsInt("Int",0);
			*outValue2 = m_pCall->getElementAsFloat("Float",0);
		}
	}
	m_pCall->unInitialize();
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoSimpleTypesAsStruct
//////////////////////////////////////////////////////////////////
SOAPStruct* InteropTestPortTypeB::echoSimpleTypesAsStruct(float Value0, int Value1, AxisChar* Value2)
{
	int nStatus;
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER, 0)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "groupBDL#echoSimpleTypesAsStruct");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoSimpleTypesAsStruct", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	m_pCall->addParameter((void*)&Value1, "inputInteger", XSD_INT);
	m_pCall->addParameter((void*)&Value2, "inputString", XSD_STRING);
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoSimpleTypesAsStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, "echoSimpleTypesAsStructReturn", Axis_URI_SOAPStruct);
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodecho2DStringArray
//////////////////////////////////////////////////////////////////
ArrayOfString2D InteropTestPortTypeB::echo2DStringArray(ArrayOfString2D Value0)
{
	ArrayOfString2D RetArray = {NULL, 0};
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoNestedStruct
//////////////////////////////////////////////////////////////////
SOAPStructStruct* InteropTestPortTypeB::echoNestedStruct(SOAPStructStruct* Value0)
{
	int nStatus;
	SOAPStructStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER, 0)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "groupBDL#echoNestedStruct");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoNestedStruct", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*) Axis_Serialize_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct, "inputStruct", "");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoNestedStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStructStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStructStruct, (void*) Axis_Create_SOAPStructStruct, (void*) Axis_Delete_SOAPStructStruct, "outputStruct", Axis_URI_SOAPStructStruct);
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoNestedArray
//////////////////////////////////////////////////////////////////
SOAPArrayStruct* InteropTestPortTypeB::echoNestedArray(SOAPArrayStruct* Value0)
{
	int nStatus;
	SOAPArrayStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER, 0)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER, "groupBDL#echoNestedArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoNestedArray", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*) Axis_Serialize_SOAPArrayStruct, (void*)Axis_Delete_SOAPArrayStruct, "inputArrayStruct", "");
	nStatus = m_pCall->invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->checkMessage("echoNestedArrayResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPArrayStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPArrayStruct, (void*) Axis_Create_SOAPArrayStruct, (void*) Axis_Delete_SOAPArrayStruct, "outputArrayStruct", Axis_URI_SOAPArrayStruct);
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}

