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

#include "Timeout.h"

void myExceptionHandler(int errorCode, const char *errorString, void *soapFault, void *faultDetail)
{
    exceptionOccurred = C_TRUE;    
    printf("in AxisException block\n");
    printf("Exception : %s\n",  errorString);
}


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/TestTransportTimeout";
    int iResult;
    int rc=1;

    axiscAxisRegisterExceptionHandler(myExceptionHandler);
    
    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_Timeout_stub(endpoint);
    axiscStubSetTransportTimeout(ws, 2);

    iResult = add(ws, 2,3);
    if (exceptionOccurred == C_FALSE)
        printf("%d\n", iResult );
    rc=0;
    destroy_Timeout_stub(ws);
    printf("---------------------- TEST COMPLETE -----------------------------\n");
    return rc;
}


