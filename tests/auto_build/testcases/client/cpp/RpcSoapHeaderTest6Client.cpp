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

#include "InteropTestPortType.h"
#include <axis/server/IHeaderBlock.hpp>
#include <axis/server/AxisException.hpp>

#define ARRAYSIZE 2

int
main(int argc, char *argv[])
{
    int x;
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    //endpoint for Axis CPP sample
    sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    InteropTestPortType ws(endpoint, APTHTTP1_1);

    /*create a header of the form:
       <SOAP-ENV:Header>
       <th:newName xmlns:th="http://ws.apache.org/axisCppTest/">
       </th:newName>
       </SOAP-ENV:Header>
     */

    //set SOAP headers
    IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader", 
		"http://ws.apache.org/axisCppTest/");

    //buld node tree
    phb->addChild(NULL);

    //set second SOAP headers
    phb = ws.createSOAPHeaderBlock("TestHeader2",
                                   "http://ws.apache.org/axisCppTest/");
    phb->addChild(NULL);

    printf("invoking echoString...\n");
    //testing echoString
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
        printf("unknown exception\n");
    }


    //test removing SOAP header block using pointer
    IHeaderBlock *header = NULL;
    header = ws.getFirstSOAPHeaderBlock();
    ws.deleteSOAPHeaderBlock(header);
    //now the request should have no SOAP headers
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
        printf("unknown exception\n");
    }


    printf("Soap Header test end\n");
    return 0;
}
