// ArrayClient.cpp : Defines the entry point for the console application.i
//
#include <string>
using namespace std;

#include "ArrayTestPortType.hpp"
#include <axis/AxisException.hpp>
#include <iostream>


#define ARRAYSIZE 100

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
		intArrayType* arrout;
		xsd__int_Array arrayInput;		
        int ** array= new int*[ARRAYSIZE];		
		for (x=0;x<ARRAYSIZE;x++)
		{
            array[x] = new int(x + 1000);
			//arrin.intItem.m_Array[x] = &intArray[x];
		}
		arrayInput.set(array,ARRAYSIZE);
		arrin.setintItem(&arrayInput);		
		cout << "invoking echoIntArray..."<<endl;
		int outputSize=0;
		arrout=ws.echoIntArray(&arrin);
		for(x=0;x<ARRAYSIZE;x++)
		   cout << *(arrout->intItem->get(outputSize)[x])<<endl;		
		 // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;
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
	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
	return 0;
}
