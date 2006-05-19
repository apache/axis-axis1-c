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

#include <stdlib.h>
#include <stdio.h>

#include "CommonClientTestCode.h"

#include "Calculator.h"

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
    axiscStubSetTransportProtocol(ws, AXISC_APTHTTP1_0);
    printf( "Protocol used by the transport is  = %d\n", axiscStubGetTransportProtocol(ws) );
    iResult = add(ws, 2,3);
    printf( "Result is = %d\n", iResult );
    axiscStubSetTransportProtocol(ws, AXISC_APTHTTP1_1);
    printf( "Protocol used by the transport is  = %d\n" , axiscStubGetTransportProtocol(ws) );
    iResult = add(ws, 5,6);
    printf( "Result is = %d\n", iResult );
    rc=0;

    destroy_Calculator_stub(ws);    
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n");
    return rc;
}
