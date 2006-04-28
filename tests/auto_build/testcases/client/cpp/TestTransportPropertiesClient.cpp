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
 * This client tests setting and getting the transport properties.
 * The test framework also verify the message content on the wire.
 */

#include "Calculator.hpp"
#include <stdio.h>
#include <iostream>

void printProperties(Calculator *obj, bool response);
void printProperties(Calculator *obj);

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";
        int iResult;
        int rc=1;

        url = argv[1];

                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                ws.setTransportProtocol(APTHTTP1_1);
                ws.setTransportProperty("Accept-Language", " da, en-gb;q=0.8, en;q=0.7");
                ws.setTransportProperty("Accept-Language", "l1");
                ws.setTransportProperty("Date", "Mon Dec  6 13:37:06 GMT 2004");
                ws.setTransportProperty("Accept-Language", "l22");
                
                cout << "Full properties list " << endl;
                printProperties(&ws);

                //deleting the transport with specific key value
                ws.deleteTransportProperty("Accept-Language",2);

                cout << "After deleteTransportProperty(key,int) method  " << endl;
                printProperties(&ws);

                //Go to the last property and delete
                ws.getFirstTransportPropertyKey(false);
                ws.getNextTransportPropertyKey(false);
                ws.getNextTransportPropertyKey(false);
                ws.deleteCurrentTransportProperty(false);
                cout << "After deleteCurrentProperty method " << endl;
                printProperties(&ws);
                
                iResult = ws.add(2,3);
                cout << iResult << endl;
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
                cout << "Unknown exception has occured: "<< e.what() << endl;
        }
        catch(...)
        {
                cout << "Unspecified exception has occured" << endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
  cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;  
        return rc;
}

void printProperties(Calculator *obj)
{
        cout << " ** Request Properties **" << endl;
        printProperties(obj, false);

        cout << " ** Response Properties **" << endl;
        printProperties(obj, true);
        cout << " ****************************************************** " << endl;
}

void printProperties(Calculator *obj, bool response)
{
        const char* transprop1;
        transprop1 = obj->getFirstTransportPropertyKey(response);
        do
        {
                transprop1 = obj->getCurrentTransportPropertyKey(response);
                cout << "     current transport property key = ";
                if (transprop1)
                {
                        cout  << transprop1 ;
                }
                else
                {
                        cout << "<NULL>";
                }

                transprop1 = obj->getCurrentTransportPropertyValue(response);
                cout << " value = ";
                if (transprop1)
                {
                        cout << transprop1;
                }
                else
                {
                        cout << "<NULL>";
                }
                cout << endl;
        }
        while ( (transprop1 = obj->getNextTransportPropertyKey(response)) != NULL);
        return ;        
}
