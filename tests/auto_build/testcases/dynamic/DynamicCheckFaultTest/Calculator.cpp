// Copyright 2003-2004 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*
 * This is a manually edited version of the Generated stub code for CaluclatorDoc.wsdl
 * to simplify the code to allow the cpp file to be edited to be used as a dynamic client.
 * This program tests checkFault API in Call class
 * @Author : James Jose
 */

#include "Calculator.hpp"
#include <axis/AxisWrapperAPI.hpp>
#include <string.h>
#include <axis/ISoapFault.hpp>

Calculator::Calculator(const char* pcEndpointUri, AXIS_PROTOCOL_TYPE eProtocol)
{
	m_pCall=new Call();
	m_pCall->setProtocol(eProtocol);
	m_pCall->setEndpointURI(pcEndpointUri);
}

Calculator::Calculator()
{
	m_pCall=new Call();
	m_pCall->setEndpointURI("http://localhost/axis/Calculator");
}

Calculator::~Calculator()
{
	delete m_pCall;
	m_pCall=NULL;
}


/*
 * This method wrap the service methoddiv
 */
xsd__int Calculator::div(xsd__int Value0, xsd__int Value1)
{
	xsd__int Ret = 0;
	const char* pcCmplxFaultName;
	try
	{	
	m_pCall->initialize(CPP_DOC_PROVIDER);
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#div");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("div", "http://localhost/axis/Calculator");
	includeSecure();
	char cPrefixAndParamName0[17];
	sprintf( cPrefixAndParamName0, "%s:arg_0_3", m_pCall->getNamespacePrefix("http://localhost/axis/Calculator"));
	m_pCall->addParameter((void*)&Value0, cPrefixAndParamName0, XSD_INT);
	char cPrefixAndParamName1[17];
	sprintf( cPrefixAndParamName1, "%s:arg_1_3", m_pCall->getNamespacePrefix("http://localhost/axis/Calculator"));
	m_pCall->addParameter((void*)&Value1, cPrefixAndParamName1, XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse", "http://localhost/axis/Calculator"))
		{
			Ret = *(m_pCall->getElementAsInt("divReturn", 0));
		}

	}
	m_pCall->unInitialize();
	return Ret;
	}
	catch(AxisException& e)
	{
		cout << "Exception : " << e.what()<< endl;
		try{ 
			ISoapFault * sf=(ISoapFault *)m_pCall->checkFault("Fault","");
			string s=sf->getFaultcode();
			string str=sf->getFaultstring();
			cout << "Fault Code = " << s.c_str() << endl;
			cout << "Fault String = " << str.c_str()<< endl;	  
		}catch(exception &e){
			cout << e.what();
		}catch(...){
			cout << "Unspecified exception has occured" << endl;
		}
		throw;
		
	}
}

/*Methods for supporting SecureChannel*/

void Calculator::SetSecure( char * pszArguments, ...)
{
	char **	ppszArgPtr = &pszArguments;
	int		iArgIndex = 0;

	while( *ppszArgPtr != NULL)
	{
		sArguments[iArgIndex] = *ppszArgPtr;
		iArgIndex++;
		ppszArgPtr++;
	}
}


void Calculator::includeSecure()
{
	m_pCall->setTransportProperty( SECURE_PROPERTIES, (const char *) &sArguments);
}


int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:9080/Calculator/services/Calculator";
	const char* op = 0;
	int i1=100, i2=0;
	int iResult;
	if(argc > 1){
		url=argv[1];
	}
	sprintf(endpoint, "%s", url);
	Calculator ws(endpoint);
	try
	{		
		iResult = ws.div(i1,i2);
		cout << endl << iResult << endl;		
	}
	catch(AxisException& e)
	{
	     /* We already printed this error message */
	     //cout << "Exception : " << e.what()<< endl;
		
	}
	catch(exception& e)
	{
	   cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		cout << "Unspecified exception has occured" << endl;
	}
	cout << "------------------------TEST COMPLETE----------------------------------" << endl;
	return 0;
}




