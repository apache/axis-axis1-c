/* Tests setLocalName() and getLocalName()in IAttribute class 
   @Author : James Jose
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
		const char *name="Name";
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/","ns");
		IAttribute *attr=phb->createAttribute("NAME","ns","AXIS");
		cout << attr->setLocalName(NULL)<<endl;
		cout << attr->setLocalName(name)<<endl;
		BasicNode *bn=phb->createImmediateChild(ELEMENT_NODE,"Project","","","");
		IAttribute *attr1=bn->createAttribute("TYPE","Open Source");
		attr1->setLocalName("Type");
		cout << "Header Attribute Name = " << attr->getLocalName()<< endl ;
		cout << "Child Node Attribute Name = " << attr1->getLocalName() << endl;
		op = "add";
		i1 = 2;
		i2 = 3;
		if (strcmp(op, "add") == 0)
		{
			iResult = ws.add(i1, i2);
			cout << iResult << endl;
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
	cout<< "---------------------- TEST COMPLETE -----------------------------" << endl;	
	return 0;
}

