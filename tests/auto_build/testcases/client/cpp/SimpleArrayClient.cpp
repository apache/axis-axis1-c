// ArrayClient.cpp : Defines the entry point for the console application.i
//
#include <string>
using namespace std;

#include "ArrayTestPortType.h"
#include <axis/AxisGenException.hpp>

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
	try
        {
	printf("Sending Requests to Server %s ........\n\n", url);
	sprintf(endpoint, "%s", url);
	ArrayTestPortType ws(endpoint);
	//testing echoIntArray
         IntArrayType arrin;
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
