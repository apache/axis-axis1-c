/* This test tests the setEndPoint(const char * pcEndPointURI) method
 * in Stub class  
 */

#include "Calculator.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* bogus_url="http://no-one.home/rubbish";
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;

	if(argc>1)
		url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		Calculator* ws = new Calculator(bogus_url);
		ws->setEndPoint(url);

		iResult = ws->add(2,3);
		cout << iResult << endl;;
				bSuccess = true;
		delete ws;
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
				cout << "Exception : " << e.what() << endl;
			}
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
        {
	    cout << "Unpecified exception has occured" << endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	return 0;
}

