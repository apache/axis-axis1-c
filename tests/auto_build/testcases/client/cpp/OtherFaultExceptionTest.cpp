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

/* ----------------------------------------------------------------------------------------
   This program tests OtherFaultException. Server sends exceptions and client application
      catches this exceptions using OtherFaultException Object                                    
   ----------------------------------------------------------------------------------------*/

#include "MathOps.hpp"
#include <axis/AxisException.hpp>
#include <axis/OtherFaultException.hpp>
#include <ctype.h>
#include <signal.h>
#include <iostream>

void sig_handler(int);
using namespace std;

int main( int argc, char * argv[])
{
	char			endpoint[256];
	const char *	server = "localhost";
	const char *	url = "http://localhost:80/axis/MathOps";
	const char *	port = "80";
	const char *	op = 0;
	const char *	p1 = 0;
	const char *	p2 = 0;
	int				i1 = 0;
	int				i2 = 0;
	int				iResult;

	signal( SIGILL, sig_handler);
	signal( SIGABRT, sig_handler);
	signal( SIGSEGV, sig_handler);
	//signal( SIGQUIT, sig_handler);
	//signal( SIGBUS, sig_handler);
	signal( SIGFPE, sig_handler);

	url = argv[1];

	sprintf( endpoint, "%s", url);

	op = "div";

	if( strcmp( op, "div") == 0)
	{
	    for( int i = 1; i < 4; i++)
	    {
			switch( i)
			{
				case 1:
				{
					i1 = 10;
					i2 = 0;
					break;
				}

				case 2:
				{
					i1 = 1000;
					i2 = 5;
					break;
				}

				case 3:
				{
					i1 = 10;
					i2 = -5;
					break;
				}
			}
            
			bool	bSuccess = false;
			int		iRetryIterationCount = 3;

			do
			{
				try
				{
					MathOps	ws( endpoint);

					if( iRetryIterationCount == 3)
					{
						cout << endl << endl << "Trying to " << op << " " << i1 << " by " << i2 << endl;

						iResult = ws.div( i1, i2);

						cout << "Result is " << iResult << endl;
				
						bSuccess = true;
					}
				}
				catch( OtherFaultException& ofe)
				{
                    const char *    pszDetail = ofe.getFaultDetail();

                    string detail = pszDetail;
                    int startOfDetailMessage = detail.find("varString>", 0);
                    if (startOfDetailMessage != string::npos)
                    {
                        startOfDetailMessage += strlen("varString>");
                        int endOfDetailMessage = detail.find("</", startOfDetailMessage);

                        cout << "Fault Detail - "<< detail.substr(startOfDetailMessage, endOfDetailMessage - startOfDetailMessage).c_str() << endl;
                    }
                    
                    bSuccess = true;
                }	
				catch( SoapFaultException& sfe)
				{
					cout << "SoapFaultException: " << sfe.what() << endl;
				}
				catch( AxisException& e)
				{
					bool bSilent = false;

					if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
					{
						if( iRetryIterationCount > 1)
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
				catch( exception& e)
				{
					cout << "Unknown Exception: " << e.what() << endl;
				}
				catch( ...)
				{
					cout << "Unspecified Exception: " << endl;
				}
			
				iRetryIterationCount--;

			} while( iRetryIterationCount > 0 && !bSuccess);
		}
	}
	else 
	{
		cout << "Invalid operation " << op << endl;
	}
	
	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;	
	
	return 0;
}

void sig_handler(int sig) {
	signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}

