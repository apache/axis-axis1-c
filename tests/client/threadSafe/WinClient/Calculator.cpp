/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains Client Stub implementation for remote web service.
 */

#include <iostream.h>
#include "Calculator.h"
#include "stdafx.h"
#include <windows.h>
#include "Thread.h"
#include <axis/server/AxisWrapperAPI.h>

using namespace std;

 Calculator::Calculator(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol)
:Stub(pchEndpointUri, eProtocol)
{
}

Calculator::Calculator()
:Stub(" ", APTHTTP)
{
	m_pCall->setEndpointURI("http://localhost/axis/Calculator");
}

Calculator::~Calculator()
{
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method add
 */
int Calculator::add(int Value0, int Value1)
{
	int Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#add");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("add", "http://localhost/axis/Calculator");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
		m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("addResponse", "http://localhost/axis/Calculator"))
			{
				Ret = m_pCall->getElementAsInt("addReturn", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		int iExceptionCode = e.getExceptionCode();
		if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
		{
			throw;
		}
		else if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/Calculator" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisGenException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method sub
 */
int Calculator::sub(int Value0, int Value1)
{
	int Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#sub");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("sub", "http://localhost/axis/Calculator");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
		m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("subResponse", "http://localhost/axis/Calculator"))
			{
				Ret = m_pCall->getElementAsInt("subReturn", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		int iExceptionCode = e.getExceptionCode();
		if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
		{
			throw;
		}
		else if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/Calculator" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisGenException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method mul
 */
int Calculator::mul(int Value0, int Value1)
{
	int Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#mul");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("mul", "http://localhost/axis/Calculator");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
		m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("mulResponse", "http://localhost/axis/Calculator"))
			{
				Ret = m_pCall->getElementAsInt("addReturn", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		int iExceptionCode = e.getExceptionCode();
		if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
		{
			throw;
		}
		else if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/Calculator" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisGenException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method div
 */
int Calculator::div(int Value0, int Value1)
{
	int Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#div");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("div", "http://localhost/axis/Calculator");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "in0", XSD_INT);
		m_pCall->addParameter((void*)&Value1, "in1", XSD_INT);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse", "http://localhost/axis/Calculator"))
			{
				Ret = m_pCall->getElementAsInt("addReturn", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		int iExceptionCode = e.getExceptionCode();
		if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
		{
			throw;
		}
		else if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/Calculator" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisGenException(cFaultdetail);
		}
		else throw;
	}
}

int Calculator::getFaultDetail(char** ppcDetail)
{
	return m_pCall->getFaultDetail(ppcDetail);
}
		



DWORD WINAPI Threaded( LPVOID /* lpData */ )
{
	Calculator cal;

	for(;;)
	{
		
		int result = cal.add(22, 33);
		printf("The result is xxxx : %d", result);
		printf("\n");
		Sleep(1000);
	}

}

DWORD WINAPI Threaded1( LPVOID /* lpData */ )
{

	Calculator cal1;
	
	for(;;)
	{
		
		int result1 = cal1.add(22, 5);
		printf("The result is xxxx : %d", result1);
		printf("\n");
		Sleep(1000);
		
	}

	
}


void main( void )
{
	
	//	A Sample Code for porting existent code of Threaded function

	CThread t1(Threaded), t2(Threaded1);

	t1.Start();
	
	t2.Start();

	SleepEx(15 * 1000, FALSE);

	t2.Stop();

	t1.Stop();

	
}