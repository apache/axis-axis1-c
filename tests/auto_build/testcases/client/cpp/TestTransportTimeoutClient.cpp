#include "Timeout.hpp"
#include <axis/Axis.hpp>
#include <stdio.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/TestTransportTimeout";
	int iResult;
	int rc=1;

	signal(SIGILL, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGFPE, sig_handler);

	if(argc>1)
		url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		Timeout ws(endpoint);
		ws.setTransportTimeout(2);	

		iResult = ws.add(2,3);
		cout << iResult << endl;
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
				cout << "in AxisException block" << endl;
				cout << "Exception : " << e.what() << endl;
			}
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" << endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);

	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;	
	return rc;
}

void sig_handler(int sig) {
	signal(sig, sig_handler);
	cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}


