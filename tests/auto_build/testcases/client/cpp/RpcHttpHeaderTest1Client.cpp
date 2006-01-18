/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */

#include <string>
using namespace std;

#include "InteropTestPortType.hpp"
#include <axis/AxisException.hpp>
#include <stdio.h>

#define ARRAYSIZE 2

int
main(int argc, char *argv[])
{
    int x;
    char buffer1[100];
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    
    //endpoint for Axis CPP sample
    sprintf(endpoint, "http://%s:%s/axis/base", server, port);

	// Set the endpoint from command line argument if set
	if (argc > 1)
		strcpy(endpoint, argv[1]);

    /*Set for HTTP transport */
    InteropTestPortType ws(endpoint, APTHTTP1_1);

    //set HTTP headers
    ws.setTransportProperty("Accept-Language", " da, en-gb;q=0.8, en;q=0.7");

    printf("invoking echoString...\n");
    //testing echoString 
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
    try {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
	printf("successful\n");
    else
	printf("failed\n");

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
        printf("%s\n", e.what());
			}
    }
    catch(...)
    {
        printf("Unknown exception\n");
    }
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);

    printf("Test transport property accessors\n");
    printf("First transport key = %s\n", ws.getFirstTransportPropertyKey(false));
    printf("First transport value = %s\n",
           ws.getCurrentTransportPropertyValue(false));

    //test removing HTTP headers
    ws.deleteTransportProperty("Accept-Language");

    //now the request should not have these removed headers
		bSuccess = false;
		iRetryIterationCount = 3;

		do
		{
    try
    {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
        printf("successful\n");
    else
        printf("failed\n");

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
        printf("%s\n", e.what());
			}
    }
    catch(...)
    {
        printf("unknown exception\n");
    }
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);

    printf("HTTP Header test end\n");
    return 0;
}
