
/* Tests setPrefix(),getPrefix(),setURI() and getURI() APIs in INamespace class  
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
		const AxisChar *pf="nsp";
		const AxisChar *uri="http://axis.apache.org";
		IHeaderBlock *phb=ws.createSOAPHeaderBlock("TestHeader","http://apache.org","ns");
		INamespace *nsp=phb->createNamespaceDecl("ns1","http://axis.org");
		nsp->setURI(uri);
		nsp->setPrefix(pf);
		const AxisChar *p=nsp->getPrefix();
		const AxisChar *u=nsp->getURI();
		cout << "Prefix = " << p;
		cout << endl << "Uri    = " << u;
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

