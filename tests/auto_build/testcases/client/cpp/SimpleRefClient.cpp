// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
using namespace std;

#include "RefTestPortType.h" 
#include <axis/AxisGenException.h>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];
	const char* server="localhost";
	const char* port="80";
	try
        {
	printf("Sending Requests to Server http://%s:%s ........\n\n", server, port);
	sprintf(endpoint, "http://%s:%s/axis/ref", server, port);
	//endpoint for Axis Java sample
	//sprintf(endpoint, "http://%s:%s/axis/services/echo", server, port);
	
	RefTestPortType ws(endpoint);

	printf("invoking echoInt..\n");
	intType refint;
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
