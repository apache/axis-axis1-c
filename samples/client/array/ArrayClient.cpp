// ArrayClient.cpp : Defines the entry point for the console application.i
//
#include <string>
using namespace std;

#include "ArrayTestPortType.h"
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
    sprintf (endpoint, "http://localhost/axis/array");
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

	ArrayTestPortType ws(endpoint);
	//testing echoIntArray
         intArrayType arrin;
         arrin.intItem.m_Array = new int[ARRAYSIZE];
         arrin.intItem.m_Size = ARRAYSIZE;
         for (x=0;x<ARRAYSIZE;x++)
         {
           arrin.intItem.m_Array[x] = x;
         }
         printf("invoking echoIntArray...\n");
         if (ws.echoIntArray(&arrin)->intItem.m_Array != NULL)
	          printf("successful \n");
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
