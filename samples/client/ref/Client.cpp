// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
using namespace std;

#include "RefTestPortType.hpp" 
#include <axis/AxisException.hpp>

#define ARRAYSIZE 2

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | service_url] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL << endl;
}

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/ref";
	sprintf(endpoint, "%s", url);

	if (argc > 1)
    {
	// Watch for special case help request
	if (!strncmp (argv[1], "-", 1))	// Check for - only so that it works for
	    //-?, -h or --help; -anything
	{
	    usage (argv[0], endpoint);
	    return 2;
	}
	sprintf (endpoint, argv[1]);
    }

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
        {
	printf("Sending Requests to Server %s ........\n\n", endpoint);
	
	
	
	RefTestPortType ws(endpoint);
	ws.setTransportProperty("SOAPAction" , "ref#echoInt");

	
	intType refint;
  	refint.intItem =56;

	printf("invoking echoInt..sending %d by reference\n", refint.intItem);

	intType *retVal = ws.echoInt(&refint);
    if (retVal->intItem == 56)
        printf("Invocation successful. Received %d\n", retVal->intItem);
    else
        printf("failed \n");


		bSuccess = true;
		}
        catch(AxisException& e)
        {
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 0)
				{
					bSilent = true;
				}
			}
			else
			{
				iRetryIterationCount = 0;
			}

            if( !bSilent)
			{
            printf("Exception : %s\n", e.what());
			}
        }
        catch(exception& e)
        {
            printf("Unknown exception has occurred: %s\n", e.what());
        }
        catch(...)
        {
            printf("Unknown exception has occurred\n");
        }
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	return 0;
}
