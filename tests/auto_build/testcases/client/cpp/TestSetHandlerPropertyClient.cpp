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

/* 
 *****************************************************************************
 * This test tests the functionality of setHandlerProperty() of Stub class.
 * Test Logic
 * Set a value for a property and and get it's value in Handler and also
 * set the value for a property in handler and get that value in Client.
 *
 * The test is supposed to be passed when values set in client are 
 * received in handler and vice versa.
 *****************************************************************************
 */

#include "Calculator.hpp"
#include<iostream>

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";
        int iResult;
        

        url = argv[1];

                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                char buffer[100];
                char* pbuff=buffer; 
                
                ws.setHandlerProperty("prop1", (void*)"value1", 7);
                ws.setHandlerProperty("prop2", &pbuff, 100);
                
                iResult = ws.add(2,3);
                cout << iResult << endl;
                cout << "value of prop2 printed in client is = " << buffer << endl;

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
            printf("Unknown exception has occured\n" );
        }
        catch(...)
        {
            printf("Unknown exception has occured\n" );
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
        cout << "---------------- TEST COMPLETE ----------------" << endl;
        return 0;
}


