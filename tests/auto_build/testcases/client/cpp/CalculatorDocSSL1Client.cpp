/*****************************************************************************
* This test is written to test the functional behaviour of SetSecure() API when 
* wrong keyRingPassword is supplied
*****************************************************************************
*/


#include "Calculator.hpp"
#include <iostream>
#include <signal.h>

void sig_handler(int);

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="https://localhost:80/axis/Calculator";
        int iResult;
	const char* sslkeyhome = 0;
        char keylocation[255];

	signal(SIGILL, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSEGV, sig_handler);
	//signal(SIGQUIT, sig_handler);
	//signal(SIGBUS, sig_handler);
	signal(SIGFPE, sig_handler);

        url = argv[1];

        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                //ws.SetSecure("/home/axistest/ssl/myKeyRing.kdb", "axxxis4all", "AXIS", "NONE", "05", "NONE", false);
		sslkeyhome=getenv("SSL_KEYS_HOME");

                if (!sslkeyhome)
                {       cout << "SSL_KEY_HOME not set" << endl;
                        return 1;
                }

                sprintf(keylocation,"%s/%s",sslkeyhome,"myKeyRing.kdb");
                ws.SetSecure(keylocation, "axxxxis4all", "AXIS", "NONE", "05", "NONE", false);


                iResult = ws.add(2,3);
                cout << iResult <<endl;
        }
        catch(AxisException& e)
        {
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
        cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        return 0;
}

void sig_handler(int sig) {
	signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}

