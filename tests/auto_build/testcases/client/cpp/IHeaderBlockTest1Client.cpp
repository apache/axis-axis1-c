/* Tests setLocalName() and getLocalName() APIs in IHeaderBlock 
  @ Author : James Jose
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
	const char* op = 0;
	int i1=0, i2=0;
	int iResult;
	url = argv[1];
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		const AxisChar *localname="TestHeader";
		op = "add";
		i1 = 2;
		i2 = 3; 
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("Test","http://ws.apache.org/axisCppTest/");		
		phb->setLocalName(localname);		
		IHeaderBlock *fhb=ws.getFirstSOAPHeaderBlock();	
		localname=fhb->getLocalName();
		cout << endl << "Local Name is " << localname;
		if (strcmp(op, "add") == 0)
		{
			iResult=ws.add(i1, i2);			
			cout << endl << iResult << endl;
		}
		
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

