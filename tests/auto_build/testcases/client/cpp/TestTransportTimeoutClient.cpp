#include "Timeout.hpp"
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

	try
	{
		sprintf(endpoint, "%s", url);
		Timeout ws(endpoint);
		ws.setTransportTimeout(2);	

		iResult = ws.add(2,3);
		cout << iResult << endl;
		rc=0;
	}
	catch(AxisException& e)
	{
	    cout << "in AxisException block"  << endl;
	    cout << "Exception : " << e.what() << endl;
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" << endl;
	}
  cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;	
	return rc;
}

void sig_handler(int sig) {
	signal(sig, sig_handler);
	cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}


