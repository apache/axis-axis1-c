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
	const char* url="http://localhost:80/axis/MathOps";
	const char* server="localhost";
	const char* port="80";
	url = argv[1];
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
        {
	printf("Sending Requests to Server %s ........\n\n", url);
	sprintf(endpoint, "%s", url);
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
            printf("Unknown exception has occured\n");
        }
        catch(...)
        {
            printf("Unknown exception has occured\n");
        }
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	return 0;
}
