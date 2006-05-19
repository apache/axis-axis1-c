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

/* This test tests the setEndPoint(const char * pcEndPointURI) method
 * in Stub class  
 */

#include <stdlib.h>
#include <stdio.h>

#include "CommonClientTestCode.h"

#include "Calculator.h"

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    char endpoint[256];
    const char* bogus_url="http://no-one.home/rubbish";
    const char* url="http://localhost:80/axis/Calculator";
    int iResult;

    if(argc>1)
        url = argv[1];

    ws = get_Calculator_stub(bogus_url);
    axiscStubSetEndPoint(ws, url);

    iResult = add(ws, 2,3);
    printf("%d\n",  iResult );

    destroy_Calculator_stub(ws);
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n" );
    return 0;
}

