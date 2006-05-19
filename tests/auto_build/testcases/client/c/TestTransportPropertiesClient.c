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


#include <stdlib.h>
#include <stdio.h>

#include "CommonClientTestCode.h"

#include "Calculator.h"

void printProperties1(AXISCHANDLE obj, int response);
void printProperties(AXISCHANDLE obj);

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";
    int iResult;
    int rc=1;

    axiscAxisRegisterExceptionHandler(exceptionHandler);
    
    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_Calculator_stub(endpoint);
    
    axiscStubSetTransportProtocol(ws, AXISC_APTHTTP1_1);
    axiscStubSetTransportProperty(ws, "Accept-Language", " da, en-gb;q=0.8, en;q=0.7");
    axiscStubSetTransportProperty(ws, "Accept-Language", "l1");
    axiscStubSetTransportProperty(ws, "Date", "Mon Dec  6 13:37:06 GMT 2004");
    axiscStubSetTransportProperty(ws, "Accept-Language", "l22");

    printf( "Full properties list \n" );
    printProperties(ws);

    //deleting the transport with specific key value
    axiscStubDeleteTransportProperty(ws, "Accept-Language",2);

    printf( "After deleteTransportProperty(key,int) method  \n" );
    printProperties(ws);

    //Go to the last property and delete
    axiscStubGetFirstTransportPropertyKey(ws, 0);
    axiscStubGetNextTransportPropertyKey(ws, 0);
    axiscStubGetNextTransportPropertyKey(ws, 0);
    axiscStubDeleteCurrentTransportProperty(ws, 0);
    printf( "After deleteCurrentProperty method \n" );
    printProperties(ws);

    iResult = add(ws, 2,3);
    printf("%d\n", iResult );
    rc=0;
    
    destroy_Calculator_stub(ws);
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n");
    return rc;
}

void printProperties(AXISCHANDLE obj)
{
    printf( " ** Request Properties **\n" );
    printProperties1(obj, 0);

    printf( " ** Response Properties **\n" );
    printProperties1(obj, 1);
    printf( " ****************************************************** \n" );
}

void printProperties1(AXISCHANDLE obj, int response)
{
    const char* transprop1;
    transprop1 = axiscStubGetFirstTransportPropertyKey(obj, response);
    do
    {
        transprop1 = axiscStubGetCurrentTransportPropertyKey(obj, response);
        printf( "     current transport property key = %s", transprop1 ? transprop1 : "<NULL>");

        transprop1 = axiscStubGetCurrentTransportPropertyValue(obj, response);
        printf( " value = %s\n", transprop1 ? transprop1 : "<NULL>");
    }
    while ( (transprop1 = axiscStubGetNextTransportPropertyKey(obj, response)) != NULL);
    return ;
}
