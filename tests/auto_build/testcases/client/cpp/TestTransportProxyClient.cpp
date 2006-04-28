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
 * This client tests setProxy() method in Stub class.
 * NOTE: To run this you must set all three input args -
 * <endpoint> <proxy> <proxy port>
 * 
 */

#include "Calculator.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
        char endpoint[256];
        char proxy[256];
        int proxyPort;
        const char* url="http://localhost:80/axis/Calculator";
        int iResult;
        int rc=1;

        if(argc>1) url = argv[1];
        if(argc>2)
        { 
            sprintf(proxy, "%s", argv[2]);
        }
        else
        {
            cout << "this test needs to set a url, proxy host and proxy port: TestTransportProxy <url> <proxy hostname> <proxy port>"<<endl;
            exit(-1);
        }
        if(argc>3)
        {
          proxyPort=atoi(argv[3]);
        }
        else
        {
            cout << "this test needs to set a url, proxy host and proxy port: TestTransportProxy <url> <proxy hostname> <proxy port>"<<endl;
            exit(-1);
        }
        
        

                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                ws.setProxy(proxy, proxyPort);
                iResult = ws.add(2,3);
                cout<<  iResult << endl;
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
                cout << "Inside AxisException block: " << e.what() << endl;
                        }
        }
        catch(exception& e)
        {
                cout << "Unknown exception has occured" << endl;
        }
        catch(...)
        {
                cout << "Unspecified exception has occured" << endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
        cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        return rc;
}

