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
 * This test is written to test the functionality of getNamespacePrefix() API
 * of Stub class.
 */ 

#include "MathOps.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";
        int iResult;
        int rc=1;
        const AxisChar *ch=NULL;

        url = argv[1];

                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                sprintf(endpoint, "%s", url);
                MathOps ws(endpoint);
                IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader1", "http://ws.apache.org/axisCppTest/","th1");
                phb->createNamespaceDecl("th1", "http://ws.apache.org/axisCppTest1/");
                
                
                iResult = ws.div(15,3);
                cout << "Result is = " << iResult << endl;
                //This method is no more defined in Stub API
                //cout << ws.getNamespacePrefix("http://ws.apache.org/axisCppTest1/") << endl;
                rc=0;

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
            cout << "Unknown exception2 has occured" <<endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
                
        return rc;
}
