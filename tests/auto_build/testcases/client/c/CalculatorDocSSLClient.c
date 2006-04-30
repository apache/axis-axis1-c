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

/*****************************************************************************
* This test is written to test the functionality of SetSecure() API 
******************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>

#include "CommonClientTestCode.h"
#include "Calculator.h"

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    const char* sslkeyhome = 0;
    char keylocation[255];

    const char* url="https://localhost:80/axis/Calculator";
    int iResult;

    sslkeyhome=getenv("SSL_KEYS_HOME");
    if (!sslkeyhome)
    {
        printf("SSL_KEYS_HOME not set\n");
        return 1;
    }
    
    sprintf(keylocation,"%s/%s",sslkeyhome,"myKeyRing.kdb");

    if (argc>1)
        url = argv[1];

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    ws = get_Calculator_stub(url);
    axiscStubSetSecure(ws, keylocation, "axis4all", "AXIS", "NONE", "05", "NONE", 0);    
    iResult = add(ws, 2,3);
    
    if (exceptionOccurred == C_TRUE ||
        get_Calculator_Status(ws) == AXISC_FAIL)
        printf("FAILED\n");
    else
        printf("%i\n",iResult);

    destroy_Calculator_stub(ws);
    
    printf("---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}


