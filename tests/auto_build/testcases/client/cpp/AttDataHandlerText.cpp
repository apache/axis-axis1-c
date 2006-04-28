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

/* This program sends some text to a web service. Service will echo the content 
   back to the program */ 

#include "DataHandlerService.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <signal.h>
#include "CommonClientTestCode.hpp"

void sig_handler(int);

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/DataHandlerService";  
        char *Result;
        url = argv[1];
        bool bSuccess = false;
        int     iRetryIterationCount = 3;

        signal(SIGILL, sig_handler);
        signal(SIGABRT, sig_handler);
        signal(SIGSEGV, sig_handler);
        //signal(SIGQUIT, sig_handler);
        //signal(SIGBUS, sig_handler);
        signal(SIGFPE, sig_handler);

        do
                {
                        try
                        {
                                sprintf(endpoint, "%s", url);
                                DataHandlerService ws(endpoint);
                                ISoapAttachment *att=ws.createSoapAttachment(); 
                        
                                char *text=stringToAscii("This is a test message for attachment");

                                //Adding the content type as text/plain
                                att->addHeader(AXIS_CONTENT_TYPE,"text/plain");
                                xsd__base64Binary b64b1;
                b64b1.set((xsd__unsignedByte *) text, strlen(text));
                                att->addBody(&b64b1);
                                //Calling the dataHandlerService, service will return content                   
                                Result=ws.echoContent(att);                             
                            cout<<Result<<endl; 
                                //Calling the dataHandlerService, service will return content type
                                Result=ws.getContentType(att);
                                cout<<Result<<endl;
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

void sig_handler(int sig) {
        signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
        exit(1);
}

