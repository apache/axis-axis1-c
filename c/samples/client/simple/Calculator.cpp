/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * Calculator.cpp: implemtation for the Calculator.
 *
 */

#include "Calculator.h"

#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
Calculator::Calculator(const char* pchEndpointUri)
{
	m_pCall = new Call();
	m_pCall->SetProtocol(APTHTTP);
	m_pCall->SetEndpointURI(pchEndpointUri);
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
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "Calculator#add");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("add", "http://localhost/axis/Calculator");
	m_pCall->AddParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->AddParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("addResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->GetElementAsInt("addReturn", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodsub
 */
int Calculator::sub(int Value0, int Value1)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "Calculator#sub");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("sub", "http://localhost/axis/Calculator");
	m_pCall->AddParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->AddParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("subResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->GetElementAsInt("subReturn", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodmul
 */
int Calculator::mul(int Value0, int Value1)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "Calculator#mul");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("mul", "http://localhost/axis/Calculator");
	m_pCall->AddParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->AddParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("mulResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->GetElementAsInt("addReturn", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methoddiv
 */
int Calculator::div(int Value0, int Value1)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER , "Calculator#div");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("div", "http://localhost/axis/Calculator");
	m_pCall->AddParameter((void*)&Value0, "in0", XSD_INT);
	m_pCall->AddParameter((void*)&Value1, "in1", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("divResponse", "http://localhost/axis/Calculator"))
		{
			Ret = m_pCall->GetElementAsInt("addReturn", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}

