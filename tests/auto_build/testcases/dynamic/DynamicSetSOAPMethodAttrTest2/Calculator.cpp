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
 * This program tests setSOAPMethodAttribute() API in Call class
 */

#include "Calculator.hpp"
#include <axis/AxisWrapperAPI.hpp>

Calculator::Calculator(const char* pcEndpointUri, AXIS_PROTOCOL_TYPE eProtocol)
{
	m_pCall=new Call();
	m_pCall->setProtocol(eProtocol);
	m_pCall->setEndpointURI(pcEndpointUri);
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

	/* Adding a SOAP Method Attribute - Name. The namespaceURI is an existing one, so  prefix of the attribute should be
	the prefix associated with this namespaceURI*/
	m_pCall->setSOAPMethodAttribute("Name","","http://localhost/axis/Calculator","Axis");

	/* Checking whether API creates duplicate Attribute. An element cannot have two attributes with same name */ 
	// m_pCall->setSOAPMethodAttribute("Name","","http://localhost/axis/Calculator","Duplicate");

	/* Adding another SOAP Method Attribute - Type  */
	m_pCall->setSOAPMethodAttribute("Type","ns1","http://axis.apache.org","Open Source");

   /* Adding another SOAP Method Attribute - Lang. API will create a namespace prefix  */
	m_pCall->setSOAPMethodAttribute("Lang","","http://axis.apache.org","C++");

	/* Adding another SOAP Method Attribute - Lang. API will create a namespace prefix  */
	m_pCall->setSOAPMethodAttribute("Attr","","","withoutPrefix");

	/* Passing NULL as argument */
	//m_pCall->setSOAPMethodAttribute("NULLTest","","",NULL);

	/* Passing an undeclared namespace prefix as argument */
	//m_pCall->setSOAPMethodAttribute("Test","ns10","","Undefined Prefix");

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
	int i1=100, i2=20;
	int iResult;
	if(argc > 1){
		url=argv[1];
	}
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		iResult = ws.div(i1,i2);		
		cout << endl << iResult << endl;
	}
	catch(AxisException& e)
	{
	     cout << "AxisException : " <<  e.what()<< endl;		
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured : " << e.what() << endl;
	}
	catch(...)
	{
		 cout << "Unspecified exception has occured" << endl;
	}
	cout << "----------------------------TEST COMPLETE--------------------------------" << endl;
	return 0;
}




