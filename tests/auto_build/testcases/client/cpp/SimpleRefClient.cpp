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

// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
using namespace std;

#include "RefTestPortType.hpp" 
#include <axis/AxisException.hpp>

#define ARRAYSIZE 2

int main( int argc, char * argv[])
{
	char *	url = "http://localhost:80/axis/MathOps";
	bool	bSuccess = false;
	int		iRetryIterationCount = 3;

	url = argv[1];

		do
		{
			try
			{
				RefTestPortType	ws( url);

				printf( "invoking echoInt..\n");

				intType	refint;

				refint.intItem = 56;

// The webservice call returns the following message (NB: The use of the
// unsupported 'multiRef' tag):-
// HTTP/1.1 200 OK
// Server: WebSphere Application Server/5.1
// Content-Type: text/xml; charset=utf-8
// Content-Language: en-GB
// Transfer-Encoding: chunked
// 
// 2fc
// <?xml version="1.0" encoding="utf-8"?>
// <soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/"
//                   xmlns:soapenc="http://schemas.xmlsoap.org/soap/encoding/"
//                       xmlns:xsd="http://www.w3.org/2001/XMLSchema"
//                       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
// <soapenv:Header/>
// <soapenv:Body soapenv:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/">
// <echoIntResponse xmlns="http://soapinterop.org/">
// <return href="#id0" xmlns=""/>
// </echoIntResponse>
// <multiRef id="id0" soapenc:root="0" soapenv:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"
//                                                  xsi:type="ns-73742416:intType"
//                                         xmlns:ns-73742416="http://soapinterop.org/xsd"
//                                                     xmlns="">
// <ns-73742416:intItem xsi:type="xsd:int">56</ns-73742416:intItem>
// </multiRef>
// </soapenv:Body>
// </soapenv:Envelope>
				if( (ws.echoInt( &refint))->intItem == 56)
				{
					printf( "successful\n");
				}
				else
				{
					printf( "failed \n");
				}

				bSuccess = true;
			}
			catch( AxisException& e)
			{
				bool	bSilent = false;

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
					printf( "Exception : %s\n", e.what());
				}
	        }
			catch( exception& e)
			{
				printf( "Unknown exception has occured : %s\n", e.what());
			}
			catch( ...)
			{
				printf( "Unknown exception has occured\n");
			}

			iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);

	return 0;
}
