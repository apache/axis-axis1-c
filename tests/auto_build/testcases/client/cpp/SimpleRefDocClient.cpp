// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
using namespace std;

#include "RefTestPortType.hpp" 
#include <axis/AxisException.hpp>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];
	const char* url="http://localhost:80/axis/RefTest";
	const char* server="localhost";
	const char* port="80";
	url = argv[1];
	try
	{
		sprintf(endpoint, "%s", url);
		RefTestPortType ws(endpoint);

		printf("invoking echoInt..\n");
		IntType refint;
		refint.intItem =56;

		if ((ws.echoInt(&refint))->intItem == 56)
			printf("successful\n");
		else
			printf("failed \n");

	}
	catch(AxisException& e)
	{
	    printf("Exception : %s\n", e.what());
	}
	catch(exception& e)
	{
	    printf("Unknown exception has occured\n");
	}
	catch(...)
	{
	    printf("Unknown exception has occured\n");
	}
	return 0;
}
