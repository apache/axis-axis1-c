#include "Calculator.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;
	int rc=1;

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		ws.setTransportProtocol(APTHTTP1_0);
		cout << "Protocol used by the transport is  = " << ws.getTransportProtocol() << endl;
		iResult = ws.add(2,3);
		printf("Result is = %d\n", iResult);
		ws.setTransportProtocol(APTHTTP1_1);
		cout << "Protocol used by the transport is  = " << ws.getTransportProtocol() << endl;
		iResult = ws.add(5,6);
		printf("Result is = %d\n", iResult);
		rc=0;
	}
	catch(AxisException& e)
	{
	    printf("Exception : %s\n", e.what());
	}
	catch(exception& e)
	{
	    printf("Unknown exception has occured\n" );
	}
	catch(...)
	{
	    printf("Unknown exception has occured\n" );
	}
		
	return rc;
}
