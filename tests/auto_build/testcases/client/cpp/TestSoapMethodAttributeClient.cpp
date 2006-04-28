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
 * This is written to test the functionality of setSOAPMethodAttribute() API 
 * in Stub class.
 */

#include "MathOps.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
        char endpoint[256];
    const char* url="http://localhost:80/axis/MathOps";
    int iResult=0;

    url = argv[1];
    sprintf(endpoint, "%s", url);
    

                MathOps ws(endpoint);
                //setSOAPMethodAttribute call does not belong to Stub class any more
                //ws.setSOAPMethodAttribute("div","ns5","10");
                //ws.setSOAPMethodAttribute("add", "", "http://soapinteroptest.org", "value");
                

    cout << "invoking MathOps div..." << endl;
    
                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                
                        iResult = ws.div(15,5);
                        cout << "Result is = " << iResult << endl;
                
                bSuccess = true;
        }
        catch (AxisException& e)
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
        catch(...)
        {
                cout << "Unknown exception" << endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);

    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;

    return 0;
}
                                                          
