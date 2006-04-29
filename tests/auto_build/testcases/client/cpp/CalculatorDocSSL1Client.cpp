// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

    bool bSuccess = false;
    int     iRetryIterationCount = 3;

    do
    {
        try
        {
            sprintf(endpoint, "%s", url);
            Calculator ws(endpoint);
            sslkeyhome=getenv("SSL_KEYS_HOME");

            if (!sslkeyhome)
            {
                cout << "SSL_KEYS_HOME not set" << endl;
                return 1;
            }

            sprintf(keylocation,"%s/%s",sslkeyhome,"myKeyRing.kdb");
            ws.SetSecure(keylocation, "axxxxis4all", "AXIS", "NONE", "05", "NONE", "false");

            iResult = ws.add(2,3);
            cout << iResult <<endl;
            bSuccess = true;
        }
        catch(AxisException& e)
        {
            bool bSilent = false;

            if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
            {
                if( iRetryIterationCount > 0)
                    bSilent = true;
            }
            else
                iRetryIterationCount = 0;

            if( !bSilent)
            {
                // Since OS400 error message is different, ensure that correct error message is returned and then return
                // what is expected to match verification file.
#ifdef __OS400__
                char *errorText = (char *)e.what();
                if (strstr(errorText, "GSKit Error 408") != NULL)
                    cout << "Exception : " << " (GSKit Error 408 - GSK_ERROR_BAD_KEYFILE_PASSWORD)" << endl;
                else
                    cout << "Exception : " << e.what() << endl;
#else
                cout << "Exception : " << e.what() << endl;
#endif
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
    }
    while( iRetryIterationCount > 0 && !bSuccess);
    
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
    return 0;
}

void sig_handler(int sig) {
    signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
    exit(1);
}

