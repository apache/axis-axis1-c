// ArrayClient.cpp : Defines the entry point for the console application.i
//
#include <string>
using namespace std;

#include "ArrayTestPortType.hpp"
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
		sprintf(endpoint, "%s", url);
		ArrayTestPortType ws(endpoint);
	
	//testing echoIntArray
         intArrayType arrin;
         arrin.intItem.m_Array = new int*[ARRAYSIZE];
         arrin.intItem.m_Size = ARRAYSIZE;
         for (x=0;x<ARRAYSIZE;x++)
         {
			 arrin.intItem.m_Array[x] = new int;
			 *(arrin.intItem.m_Array[x]) = x;
         }
         printf("invoking echoIntArray...\n");
         if (ws.echoIntArray(&arrin)->intItem.m_Array != NULL)
	          printf("successful \n");
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
