/* 
 * This test is written to test the functionality of getTransportProtocol() API
 * when a an unsupported protocl is set using setTransportProtocol() method.
 */ 

#include "Calculator.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;
	int rc=1;

	url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		ws.setTransportProtocol(APTFTP);
		cout << "Protocol used by the transport is  = " << ws.getTransportProtocol() << endl;
		iResult = ws.add(2,3);
		cout << "Result is = " << iResult << endl;
		rc=0;
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
				cout << "Exception : " << e.what() << endl;
			}
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" <<endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
		
	return rc;
}
