/* This test tests the setEndPoint(const char * pcEndPointURI) method
 * in Stub class  
 */

#include "Calculator.hpp"

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws;
		printf("EndPointURI is = %s \n", url);
		ws.setEndPoint(url);

		iResult = ws.add(2,3);
		printf("%d\n", iResult);
	}
	catch(AxisException& e)
	{
	    printf("in AxisException block \n");
	    printf("Exception : %s\n", e.what());
	}
	catch(exception& e)
	{
	    printf("Unknown exception has occured\n" );
	}
	catch(...)
        {
	    printf("Unpecified exception has occured \n" );
	}

	return 0;
}

