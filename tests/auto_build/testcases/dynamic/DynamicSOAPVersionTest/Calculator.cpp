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
 * This program tests setSOAPVersion() and createHeaderBlock() API in Call class
 */

#include "Calculator.hpp"
#include <axis/AxisWrapperAPI.hpp>

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


void Calculator::setSOAPVersion(SOAP_VERSION version){
	m_pCall->initialize(CPP_DOC_PROVIDER);
	m_pCall->setSOAPVersion(version);
}

IHeaderBlock * Calculator::createHeaderBlock(){
	IHeaderBlock *phb=m_pCall->createHeaderBlock();
	phb->setLocalName("TestHeader");
	phb->setURI("http://apache.axis.com");
	return phb;
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
	//m_pCall->initialize(CPP_DOC_PROVIDER);
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "Calculator#div");
	//m_pCall->setSOAPVersion(SOAP_VER_1_1);
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
	int i1=100, i2=20;
	int iResult;
	if(argc > 1){
		url=argv[1];
	}
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		ws.setSOAPVersion(SOAP_VER_1_1);
		iResult = ws.div(i1,i2);
		cout << endl << iResult << endl;
		ws.setSOAPVersion(SOAP_VER_1_2);
		IHeaderBlock *phb=ws.createHeaderBlock();
		IAttribute *attr=phb->createStdAttribute(ROLE_NEXT,SOAP_VER_1_2);
		cout << attr->getLocalName() << endl;
		cout << attr->getPrefix() << endl;
		IHeaderBlock *phb1=ws.createHeaderBlock();
		IAttribute *attr1=phb1->createStdAttribute(ROLE_NONE,SOAP_VER_1_2);
		IHeaderBlock *phb2=ws.createHeaderBlock();
		IAttribute *attr2=phb2->createStdAttribute(ROLE_ULTIMATE_RECEIVER,SOAP_VER_1_2);
		IHeaderBlock *phb3=ws.createHeaderBlock();
		IAttribute *attr3=phb3->createStdAttribute(MUST_UNDERSTAND_TRUE,SOAP_VER_1_2);
		IHeaderBlock *phb4=ws.createHeaderBlock();
		IAttribute *attr4=phb4->createStdAttribute(MUST_UNDERSTAND_FALSE,SOAP_VER_1_2);
		IHeaderBlock *phb5=ws.createHeaderBlock();
		IAttribute *attr5=phb5->createStdAttribute(ACTOR,SOAP_VER_1_2);
		if(attr5==NULL)
			cout << "NULL returned" << endl;		
		iResult = ws.div(i1,i2);
		cout << endl << iResult << endl;
	}
	catch(AxisException& e)
	{
	     cout << "Exception : " <<  e.what()<< endl;		
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		 cout << "Unspecified exception has occured" << endl;
	}
	cout << "----------------------------TEST COMPLETE--------------------------------" << endl;
	return 0;
}




