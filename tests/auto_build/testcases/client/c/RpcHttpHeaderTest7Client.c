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

#include <stdlib.h>
#include <stdio.h>

#include "CommonClientTestCode.h"
#include "InteropTestPortType.h"

#define ARRAYSIZE 2

int
main(int argc, char *argv[])
{
    AXISCHANDLE ws;
    
    int x;
    char buffer1[100];
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    const char *key = NULL;
    int count = 1;
    
    xsdc__string result;

    //endpoint for Axis CPP sample
    sprintf(endpoint, "http://%s:%s/axis/base", server, port);

    // Set the endpoint from command line argument if set
    if (argc > 1)
        strcpy(endpoint, argv[1]);

    /*Set for HTTP transport */
    ws = get_InteropTestPortType_stub(endpoint);

    //set HTTP headers
    axiscStubSetTransportProperty(ws, "Accept-Language", NULL);

    printf( "invoking echoString...\n" );

    result = echoString(ws, "hello world");
    if (result && 0 == strcmp(result, "hello world"))
        printf( "successful\n" );
    else
        printf( "failed\n" );
    axiscAxisDelete(result, XSDC_STRING);

    printf( "Test transport property accessors\n" );
    printf( "First transport key = %s\n", axiscStubGetFirstTransportPropertyKey(ws, 0) );
    printf( "First transport value = %s\n", axiscStubGetCurrentTransportPropertyValue(ws, 0) );

    while (key = axiscStubGetNextTransportPropertyKey(ws, 0))
    {
        printf( "Next transport key = %s\n", key );
        printf( "Next transport value = %s\n", axiscStubGetCurrentTransportPropertyValue(ws, 0) );
        count++;
    }

    //test removing HTTP headers
    axiscStubDeleteTransportProperty(ws, "Accept-Language", 1);

    //now the request should not have these removed headers

    result = echoString(ws, "hello world");
    if (result && 0 == strcmp(result, "hello world"))
        printf( "successful\n" );
    else
        printf( "failed\n" );
    axiscAxisDelete(result, XSDC_STRING);

    destroy_InteropTestPortType_stub(ws);

    printf( "HTTP Header test end\n" );

    return 0;
}
