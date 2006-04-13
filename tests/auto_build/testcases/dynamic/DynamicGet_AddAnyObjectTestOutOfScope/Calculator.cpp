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
 * This program tests getAnyObject() and addAnyObject() API in Call class
 * @ Author : James Jose
 */

#include "Calculator.hpp"
#include <axis/AxisWrapperAPI.hpp>
#include <axis/AxisUserAPI.hpp>
#include <stdio.h>
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

/**
 * This method is written to step over any returned AnyObject containing just whitespace.
 */
AnyType * Calculator::getNextAnyTag(void)
{
	AnyType * any = NULL;
	bool foundStart = false;
	while (!foundStart)
	{
		any = (AnyType*)m_pCall->getAnyObject();
		if (any!= NULL && any->_size > 0 && any->_array[0][0] != '<')
		{
			continue;
		}
		
		foundStart = true;
	}
	return any;
}

xsd__int Calculator::div(xsd__int Value0, xsd__int Value1)
{
	xsd__int Ret = 0;
	AnyType * any;
	AnyType* pAny = new AnyType();
    pAny->_size = 2;
    pAny->_array = new char*[2];
	char *p=new char[100];
	sprintf(p,"<ns1:arg_0_3>%d</ns1:arg_0_3>",Value0);
	pAny->_array[0]=strdup(p);
	sprintf(p,"<ns1:arg_1_3>%d</ns1:arg_1_3>",Value1);
	//pAny->_array[1]=strdup("<ns1:arg_1_3>0</ns1:arg_1_3>");
	pAny->_array[1]=strdup(p);
	const char* pcCmplxFaultName;
	try
	{	
		m_pCall->initialize(CPP_DOC_PROVIDER);
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#div");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("div", "http://localhost/axis/Calculator");
		includeSecure();
		char cPrefixAndParamName0[17];	
		cout<<endl<<m_pCall->addAnyObject(pAny)<<endl;	
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("divResponse", "http://localhost/axis/Calculator"))
		{
			any = this->getNextAnyTag();
			
			if(any!=NULL){
				cout << any->_size<<endl;
				cout << any->_array[0]<<endl;
			}

			any = this->getNextAnyTag();	// Skip past </divResponse> tag
//			any = this->getNextAnyTag();	// Skip past </Body> tag
//			any = this->getNextAnyTag();	// Skip past </Envelope> tag

			if( any != NULL)
			{
				if( any->_size > 0 && strcmp( any->_array[0], "</divResponse>"))
				{
					cout << "Error - Unexpected tag in buffer." << endl;
					cout << any->_size << endl;
					cout << any->_array[0] << endl;
				}
			}
			else
			{
				cout << "Error - No tags left in buffer." << endl;
			}
		}

	}
	
	}
	catch(AxisException& e)
	{
		any = (AnyType*)m_pCall->getAnyObject();
		if(any!=NULL){
				cout << any->_size<<endl;
				cout << any->_array[0]<<endl;
		}
		throw;
	}
	m_pCall->unInitialize();
	delete pAny;
	delete p;
	return Ret;
	
}



void Calculator::includeSecure()
{
	m_pCall->setTransportProperty( SECURE_PROPERTIES, (const char *) &sArguments);
}

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:9080/Calculator/services/Calculator";
	int iResult;
	if(argc > 1){
		url=argv[1];
	}
	try
	{
		sprintf(endpoint, "%s", url);
	    Calculator ws(endpoint);		
		ws.div(10,2);		
	}
	catch(AxisException& e)
	{
	    cout << "Exception : " << e.what() << endl;
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		cout << "Unspecified exception has occured" << endl;
	}
	cout << "----------------------------TEST COMPLETE------------------------------------" << endl;
	return 0;
}




