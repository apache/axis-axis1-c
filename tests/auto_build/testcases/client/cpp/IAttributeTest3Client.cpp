
/* Tests setValue() and getValue()in IAttribute class
@ Author : James Jose
*/


#include "Calculator.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
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
		const char *Value="AXIS";
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/","ns");
		IAttribute *attr1=phb->createAttribute("Name","ns","axis");
		attr1->setValue(Value);
		BasicNode *bn=phb->createImmediateChild(ELEMENT_NODE,"Project","","","");
		IAttribute *attr2=bn->createAttribute("TYPE","OPEN SOURCE");
		attr2->setValue("Open Source");
		cout << endl << "Header Attribute Value = " << attr1->getValue();
		cout << endl << "Child Node Attribute Value = " << attr2->getValue();
		op = "add";
		i1 = 2;
		i2 = 3;
		if (strcmp(op, "add") == 0)
		{
			iResult = ws.add(i1, i2);
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

