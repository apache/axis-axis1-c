#include "MathOps.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <signal.h>
#include <iostream>

void sig_handler(int);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* server="localhost";
	const char* url="http://localhost:80/axis/MathOps";
	const char* port="80";
	const char* op = 0;
	const char* p1 = 0;
	const char* p2 = 0;
	int i1=0, i2=0;
	int iResult;
	char* pcDetail;

	signal(SIGILL, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSEGV, sig_handler);
	//signal(SIGQUIT, sig_handler);
	//signal(SIGBUS, sig_handler);
	signal(SIGFPE, sig_handler);

	url = argv[1];

	sprintf(endpoint, "%s", url);

	op = "div";

	if (strcmp(op, "div") == 0)
	{
	    for(int i = 0; i < 4; i++)
	    {
            cout << i << endl;

			switch(i)
			{
				case 0: i1 = 10; i2 = 5; break;
				case 1: i1 = 10; i2 = 0; break;
				case 2: i1 = 1000; i2 = 5; break;
				case 3: i1 = 10; i2 = -5; break;
			}
			try
			{
				MathOps ws(endpoint);
				cout << "Trying to " << op << " " << i1 << " by " << i2 << endl;
				iResult = ws.div(i1, i2);		
				cout << "Result is " << iResult << endl;
			}
			catch(MathOpsService_AxisClientException &me)
			{
				cout << "MathOpsService_AxisClientException: ";
				ISoapFault *fault = (ISoapFault *)me.getFault();
				const char* pcCmplxFaultName = fault->getCmplxFaultObjectName().c_str();
				if(0 == strcmp("DivByZeroStruct", pcCmplxFaultName))
				{
					DivByZeroStruct* p = (DivByZeroStruct *)fault->getCmplxFaultObject();
					cout << "DivByZeroStruct Fault: \"" << p->varString << "\", " << p->varInt << ", " << p->varFloat << endl;
            	}
				else if(0 == strcmp("SpecialDetailStruct", pcCmplxFaultName))
				{
					SpecialDetailStruct* p = (SpecialDetailStruct *)fault->getCmplxFaultObject();
					cout << "SpecialDetailStruct Fault: \"" << p->varString << "\"" << endl;
				}
				else if(0 == strcmp("OutOfBoundStruct", pcCmplxFaultName))
				{
					OutOfBoundStruct* p = (OutOfBoundStruct *)fault->getCmplxFaultObject();
					cout << "OutOfBoundStruct Fault: \"" << p->varString << "\", " << p->varInt << ", \"" << p->specialDetail->varString << "\"" << endl;
				}
			}
			catch(AxisException& e)
			{
                cout << "AxisException: " << e.what() << endl;
			}
			catch(exception& e)
			{
                cout << "Unknown Exception: " << endl;
			}
			catch(...)
			{
                cout << "Unspecified Exception: " << endl;
			}
	    }
	}
	else 
	{
		cout << "Invalid operation " << op << endl;
	}
	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}

void sig_handler(int sig) {
	signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}

