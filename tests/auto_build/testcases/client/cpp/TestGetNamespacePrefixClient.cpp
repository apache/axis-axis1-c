/* 
 * This test is written to test the functionality of getNamespacePrefix() API
 * of Stub class.
 */ 

#include "MathOps.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;
	int rc=1;
	const AxisChar *ch=NULL;

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		MathOps ws(endpoint);
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader1", "http://ws.apache.org/axisCppTest/","th1");
		phb->createNamespaceDecl("th1", "http://ws.apache.org/axisCppTest1/");
		
		
		iResult = ws.div(15,3);
		cout << "Result is = " << iResult << endl;
	
		cout << ws.getNamespacePrefix("http://ws.apache.org/axisCppTest1/") << endl;
		rc=0;
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
	    cout << "Unknown exception2 has occured" <<endl;
	}
		
	return rc;
}
