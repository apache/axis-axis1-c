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
		cout << "Result is = " << iResult << endl;
		ws.setTransportProtocol(APTHTTP1_1);
		cout << "Protocol used by the transport is  = " << ws.getTransportProtocol() << endl;
		iResult = ws.add(5,6);
		cout << "Result is = " << iResult << endl;
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
	    cout << "Unknown exception has occured" <<endl;
	}
		
	return rc;
}
