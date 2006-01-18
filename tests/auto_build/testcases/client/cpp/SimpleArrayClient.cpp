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
	int		x;
	char *	url="http://localhost:80/axis/MathOps";
	bool	bSuccess = false;
	int		iRetryIterationCount = 3;

	url = argv[1];

	do
	{
		try
        {
			ArrayTestPortType	ws( url);
			intArrayType		arrin;
			intArrayType *		arrout;
			xsd__int_Array		arrayInput;
			int **				array = new int*[ARRAYSIZE];

			for( x = 0; x < ARRAYSIZE; x++)
			{
				array[x] = new int(x + 1000);
			}

			arrayInput.set(array,ARRAYSIZE);
			arrin.setintItem(&arrayInput);

			cout << "invoking echoIntArray..." << endl;

			int		outputSize = 0;

			arrout = ws.echoIntArray( &arrin);

			for( x = 0; x < ARRAYSIZE; x++)
			{
				cout << *(arrout->intItem->get(outputSize)[x])<<endl;
			}

			// Clear up input array        
			for( int deleteIndex = 0; deleteIndex < ARRAYSIZE; deleteIndex++)
			{
				delete array[deleteIndex];
			}

			delete [] array;

			bSuccess = true;
		}
        catch( AxisException& e)
        {
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 1)
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
	            cout << "Exception : " << e.what() << endl;
			}
        }
        catch( exception& e)
        {
            cout << "Unknown exception has occurred : " << e.what() << endl;
        }
        catch(...)
        {
            cout << "Unknown exception has occurred" << endl;
        }

		iRetryIterationCount--;
	} while( iRetryIterationCount > 0 && !bSuccess);

	cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

	return 0;
}
