
/* Tests setURI() and getURI()in IAttribute Class
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
		const char *uri="http://axis.apache.com";
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/","ns");
		INamespace *nsp=phb->createNamespaceDecl("nsp","http://apache.com");
		IAttribute *attr1=phb->createAttribute("Name","nsp","axis");
		attr1->setURI(uri);
		BasicNode *bn=phb->createImmediateChild(ELEMENT_NODE,"Project","","","");
		IAttribute *attr2=bn->createAttribute("TYPE","OPEN SOURCE");
		attr2->setURI(uri);
		cout << endl << "Header Attribute Uri = " << attr1->getURI();
		cout << endl << "Child Node Attribute Uri = " << attr2->getURI();
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

