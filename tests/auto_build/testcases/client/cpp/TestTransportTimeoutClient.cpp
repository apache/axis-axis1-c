#include "Timeout.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/TestTransportTimeout";
	int iResult;
	int rc=1;

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		Timeout ws(endpoint);
		ws.setTransportTimeout(2);	

		iResult = ws.add(2,3);
		printf("%d\n", iResult);
		rc=0;
	}
	catch(AxisException& e)
	{
	    cout << "in AxisException block"  << endl;
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

