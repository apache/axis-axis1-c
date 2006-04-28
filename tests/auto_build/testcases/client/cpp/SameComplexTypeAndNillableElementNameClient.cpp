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

#include "SameComplexTypeAndNillableElementName.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";

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
                SameComplexTypeAndNillableElementName ws(endpoint);

                aType input;
                xsd__int* inputValue = NULL;
                input.setaType(inputValue);

                aType * output = ws.complexTypeAndNillableElement(&input);
                if (output != NULL)
                {
                        xsd__int * outputValue = output->getaType();
                        if (outputValue != NULL)
                        {
                                cout << "aType->aType = " << *outputValue << endl;
                        }
                        else
                        {
                                cout << "aType->aType = NULL" << endl;
                        }
                }
                else
                {
                        cout << "output is NULL" << endl;
                }
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
            cout << "Unknown exception has occured" << endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
  cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        
        return 0;
}

void PrintUsage()
{
        printf("Usage :\n Calculator <url>\n\n");
        exit(1);
}

bool IsNumber(const char* p)
{
        for (int x=0; x < strlen(p); x++)
        {
                if (!isdigit(p[x])) return false;
        }
        return true;
}

void sig_handler(int sig) {
        signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
        exit(1);
}

