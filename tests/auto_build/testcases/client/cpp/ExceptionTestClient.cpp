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
#include <axis/Axis.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);

void PrintUsage();

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* server="localhost";
	const char* port="80";
	const char* url="http://localhost:80/axis/MathOps";
	const char* op = 0;
	char* p1 = 0;
	const char* p2 = 0;
	int p3 = 0;
	int i1=0, i2=0;
	int iResult;
	char* pcDetail;

	signal(SIGILL, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGFPE, sig_handler);

	if(argc>1)
		url = argv[1];

	op = "div";
	
	i1 = 10;
	i2 = 5;

	if (strcmp(op, "div") == 0)
	{
	    for(p3 = 0; p3 < 3; p3++)
	    {
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
		try
		{     
		    switch(p3)
		    {
			case 0:
			    /* Sends a normal request. the result should be the division of
			     *  two numbers the user has provided
			     */
			    //sprintf(endpoint, "http://%s:%s/axis/MathOps", server, port);
			    sprintf(endpoint, "%s", url);
			    break;
	    
			case 1:
			    /* Service name is missing. The message
			     *  Exception : AxisSoapException:Soap action is empty
			     *  should be returned to the user.
			     */
			    //sprintf(endpoint, "http://%s:%s/axis", server, port);
			    sprintf(endpoint, "%s", url);
			    p1 = strrchr(endpoint, '/');
			    *p1 = (char)NULL; // Set a NULL at the last '/' char to strip the service endpoint interface
			    break;
	  
		       case 2: 
			   /* Service name is wrong. The message
			    * Exception : AxisWsddException:Requested service not found
			    * should be returned to the user.
			    */
			    //sprintf(endpoint, "http://%s:%s/axis/Math", server, port);
			    sprintf(endpoint, "%s", url);
			    p1 = endpoint + (strlen(endpoint) - 3);
			    *p1 = (char)NULL; // Set a NULL to strip the last 3 chars
			    break;

		       case 3:
			     /* Service path is empty. The message  
			      * The corresponding http fail message
			      * should be returned to the user.
			      */
			    /*sprintf(endpoint, "http://%s:%s/", server, port);*/
			    cout << "This test has been temporarily terminated"  
			    << " due to an unresolved bug"<< endl;
			    exit(0); /* This is temporary code*/
			    break;

		       case 4:
			    /* Exception : AxisTransportException:Unexpected string
			     * received. Most probably server returned an empty stream
			     */
			    sprintf(endpoint, "", server, port);
			    //sprintf(endpoint, "http://%s:%s", server, port);
			    break;
		 
		       default:
			    cout << "Invalid option for the last parameter"<<endl<<endl;
			    return 0;
		    }
		    //sprintf(endpoint, "http://%s:%s/axis/MathOps", server, port);
		    MathOps ws(endpoint);
		    iResult = ws.div(i1, i2);		
		    cout << "Result is:" << iResult << endl;
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
				cout << "AxisException has occured: " << e.what() << endl;
			}
		}
		catch(exception& e)
		{
		    cout << "Unknown exception has occured"<< endl;
		}
		catch(...)
		{
		    cout << "Unspecified exception has occured" << endl;
		}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	    }
	}
	else 
	{
		cout << "Invalid operation " << op <<endl<<endl;
		PrintUsage();
	}

	cout << "---------------------- TEST COMPLETE -----------------------------" << endl;
	return 0;
}

void PrintUsage()
{
	printf("Usage :\n MathOps <url>\n\n");
	exit(1);
}

void sig_handler(int sig) {
	signal(sig, sig_handler);
	cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}

