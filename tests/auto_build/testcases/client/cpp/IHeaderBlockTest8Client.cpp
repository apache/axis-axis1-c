/* Tests createStdAttribute APIs for SOAPVER_1_1 in IHeaderBlock 
   Author @ James Jose
*/

#include "Calculator.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/AxisException.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int i1=0, i2=0;
	int iResult;

	if(argc>1)
		url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		i1 = 2;
		i2 = 3; 
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
		IAttribute *attr = phb->createStdAttribute(ACTOR,SOAP_VER_1_1);
		iResult=ws.add(i1, i2);	
		cout << iResult << endl;
		Calculator ws1(endpoint);
		IHeaderBlock *phb1 = ws1.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
		IAttribute *attr1 = phb1->createStdAttribute(MUST_UNDERSTAND_TRUE,SOAP_VER_1_1);
		iResult=ws1.add(i1, i2);	
		cout << iResult << endl;
		Calculator ws2(endpoint);
		IHeaderBlock *phb2 = ws2.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
		IAttribute *attr2 = phb2->createStdAttribute(MUST_UNDERSTAND_FALSE,SOAP_VER_1_1);
		iResult=ws2.add(i1, i2);	
		cout << iResult << endl;
		Calculator ws3(endpoint);
		IHeaderBlock *phb3 = ws3.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
		IAttribute *attr3 = phb3->createStdAttribute(ROLE_NEXT,SOAP_VER_1_1);
		iResult=ws3.add(i1, i2);	
		cout << iResult << endl;
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
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;	
	return 0;
}

