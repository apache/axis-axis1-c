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

#include "Calculator.hpp"
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
        const char* op = 0;
        int i1=0, i2=0;
        int iResult;

        signal(SIGILL, sig_handler);
        signal(SIGABRT, sig_handler);
        signal(SIGSEGV, sig_handler);
        //signal(SIGQUIT, sig_handler);
        //signal(SIGBUS, sig_handler);
        signal(SIGFPE, sig_handler);

        url = argv[1];

                bool bSuccess = false;
                int     iRetryIterationCount = 3;
        sprintf(endpoint, "%s", url);
     Calculator ws(endpoint);

                do
                {
        try
        {

                op = "add";
                i1 = 2;
                i2 = 3;

                if (strcmp(op, "add") == 0)
                {
                        iResult = ws.add(i1, i2);
                        cout << iResult << endl;
                        bSuccess = true;
                }
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
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0);
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

