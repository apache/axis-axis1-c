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

#include "MathOps.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <signal.h>
#include <iostream>

void sig_handler(int);
using namespace std;

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
                // This test creates the service once and once only. It then repeatedly calls the operation on the service
                MathOps ws(endpoint);
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
                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
                        try
                        {
                                cout << "Trying to " << op << " " << i1 << " by " << i2 << endl;
                                iResult = ws.div(i1, i2);               
                                cout << "Result is " << iResult << endl;
                                bSuccess = true;
                        }
                        catch(DivByZeroStruct& dbzs)
                        {
                                cout << "DivByZeroStruct Fault: \"" 
                                        << dbzs.varString 
                                        << "\", " 
                                        << dbzs.varInt 
                                        << ", " 
                                        << dbzs.varFloat 
                                        << endl; 
                                bSuccess = true;
                        }
                        catch(SpecialDetailStruct& sds)
                        {
                                cout << "SpecialDetailStruct Fault: \"" 
                                        << sds.varString 
                                        << "\"" 
                                        << endl;
                                bSuccess = true;
                        }
                        catch(OutOfBoundStruct& oobs)
                        {
                                cout << "OutOfBoundStruct Fault: \"" 
                                        << oobs.varString 
                                        << "\", " 
                                        << oobs.varInt 
                                        << ", \"" 
                                        << oobs.specialDetail->varString 
                                        << "\"" 
                                        << endl;
                                bSuccess = true;
                        }
                        catch(SoapFaultException& sfe)
                        {
                                cout << "SoapFaultException: " << sfe.what() << endl;
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
                                cout << "AxisException : " << e.what() << endl;
                        }
                        }
                        catch(exception& e)
                        {
                cout << "Unknown Exception: " << endl;
                        }
                        catch(...)
                        {
                cout << "Unspecified Exception: " << endl;
                        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
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

