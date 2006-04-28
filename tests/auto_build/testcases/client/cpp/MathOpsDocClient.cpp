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
#include <iostream>

void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/MathOps";
        const char* server="localhost";
        const char* port="80";
        const char* op = 0;
        const char* p1 = 0;
        const char* p2 = 0;
        int i1=0, i2=0;
        int iResult;

        url = argv[1];

                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                sprintf(endpoint, "%s", url);
                MathOps ws(endpoint);

                op = "div";/*Operation name*/
                i1 = 10;/*First parameter*/
                i2 = 5;/*Second parameter*/

                if (strcmp(op, "div") == 0)
                {
                        iResult = ws.div(i1, i2);               
                        cout << "Result is:" << iResult << endl;
                }
                else 
                {
                        cout << "Invalid operation "<< op<< endl<<endl;
                        PrintUsage();
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
            cout << "Unknown exception has occured" << e.what() << endl;
        }
        catch(...)
        {
            cout << "Unspecified exception has occured" << endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
        cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
        
        return 0;
}

void PrintUsage()
{
        cout << "Usage :\n MathOps <url>"<<endl<<endl;
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
