// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
using namespace std;

#include "RefTestPortType.h" 
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | service_url] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL
	<<
	"\n    Could use http://localhost:8080/axis/services/echo to test with Axis Java."
	<< endl;
}

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];

    // Set default service URL
    sprintf (endpoint, "http://localhost/axis/ref");
    // Could use http://localhost:8080/axis/services/echo to test with Axis Java

    try
        {
	if (argc > 1)
	{
	    // Watch for special case help request
	    if (!strncmp (argv[1], "-", 1)) // Check for - only so that it works for 
                                            //-?, -h or --help; -anything 
	    {
		usage (argv[0], endpoint);
		return 2;
	    }
	    sprintf (endpoint, argv[1]);
	}
	cout << endl << " Using service at " << endpoint << endl << endl;
	
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
