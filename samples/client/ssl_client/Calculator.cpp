/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * Calculator.cpp: implemtation for the Calculator.
 *
 */

#include "Calculator.h"

#include <axis/AxisWrapperAPI.hpp>

AXIS_CPP_NAMESPACE_USE

bool CallBase::bInitialized;
//CallFunctions CallBase::ms_VFtable;
Calculator::Calculator(const char* pchEndpointUri)
{
	m_pCall = new Call();
	m_pCall->setProtocol(APTHTTP1_1);
	m_pCall->setEndpointURI(pchEndpointUri);
}

Calculator::~Calculator()
{
	delete m_pCall;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodadd
 */
int Calculator::add(int Value0, int Value1)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#add");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("add", "http://localhost/axis/Calculator");
	m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("addResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->getElementAsInt("addReturn", 0);
                        printf("Ret:%d\n", Ret);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodsub
 */
int Calculator::sub(int Value0, int Value1)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#sub");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("sub", "http://localhost/axis/Calculator");
	m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("subResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->getElementAsInt("subReturn", 0);
			printf("Ret:%d\n", Ret);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodmul
 */
int Calculator::mul(int Value0, int Value1)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#mul");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("mul", "http://localhost/axis/Calculator");
	m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("mulResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->getElementAsInt("addReturn", 0);
			printf("Ret:%d\n", Ret);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methoddiv
 */
int Calculator::div(int Value0, int Value1)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#div");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("div", "http://localhost/axis/Calculator");
	m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->getElementAsInt("addReturn", 0);
			printf("Ret:%d\n", Ret);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}

int Calculator::getFaultDetail(char** ppcDetail)
{
    m_pCall->getFaultDetail(ppcDetail);
	return 0;
}

