/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

#include "../../gen_src/rpc/InteropTestPortType.h"

#define ARRAYSIZE 2

int
main(int argc, char *argv[])
{
    int x;
    char buffer1[100];
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    if (argc == 3)
    {
	server = argv[1];
	port = argv[2];
    }
    printf("Usage :\n %s <server> <port>\n\n", argv[0]);
    //sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    //endpoint for Axis CPP sample
    sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    /*Set for HTTP transport */
    InteropTestPortType ws(endpoint, APTHTTP);

    //set HTTP headers
    ws.setTransportProperty("Accept-Language", " da, en-gb;q=0.8, en;q=0.7");
    ws.setTransportProperty("Accept-Language", "lang2");
    ws.setTransportProperty("Accept-Language", "lang3");
    ws.setTransportProperty("Date", "Sat, 26 Jun 2004 13:32:19 GMT");

    printf("Sending Requests to end point %s \n\n", endpoint);
    printf("invoking echoString...\n");
    //testing echoString 
    try {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
	printf("successful\n");
    else
	printf("failed\n");
    }
    catch(AxisException& e) 
    {
        printf("%s\n", e.what());
    }
    catch(...)
    {
        printf("Unknown exception\n");
    }

    printf("Test trasport property accessors\n");
    printf("First trasport key = %s\n", ws.getFirstTrasportPropertyKey());
    printf("First trasport value = %s\n",
           ws.getCurrentTrasportPropertyValue()); 
    char *key = NULL;
    int count = 1;
    while (key = ws.getNextTrasportPropertyKey())
    {
        printf("Next trasport key = %s\n", key);
        printf("Next trasport value = %s\n",
               ws.getCurrentTrasportPropertyValue());
        count++;
        //test removal of last trasport property
        if (count == 4)
            ws.deleteCurrentTrasportProperty();
    }

    //test removing HTTP headers
    ws.deleteTrasportProperty("Accept-Language", 1);
    ws.deleteTrasportProperty("Date");

    //now the request should not have these removed headers
    try
    {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
        printf("successful\n");
    else
        printf("failed\n");
    }
    catch(AxisException& e)
    {
        printf("%s\n", e.what());
    }
    catch(...)
    {
        printf("Unknown exception\n");
    }


    printf("HTTP Header test end\n");
    return 0;
}
