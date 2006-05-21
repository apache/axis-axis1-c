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


/* Tests setPrefix() and getPrefix()in IAttribute class
@ Author : James Jose
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "Calculator.h"

void myExceptionHandler(int errorCode, const char *errorString)
{
    exceptionOccurred = C_TRUE;    
    printf("Exception : %s\n", errorString);
}


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";
    const char* op = 0;
    int i1=0, i2=0;
    int iResult;
    
    const char *prefix="nsp";
    
    AXISCHANDLE phb;
    AXISCHANDLE attr1, attr2;
    AXISCHANDLE bn;

    axiscAxisRegisterExceptionHandler(myExceptionHandler);
    
    if (argc > 1)
        url = argv[1];
    sprintf(endpoint, "%s", url);

    ws = get_Calculator_stub(endpoint);
    
    phb = axiscStubCreateSOAPHeaderBlock(ws, "TestHeader","http://ws.apache.org/","nsp");
    attr1=axiscHeaderBlockCreateAttribute(phb, "Name","ns", NULL, "AXIS");
    
    /* Tests for NULL Value */
    printf("%d\n", axiscAttributeSetPrefix(attr1, NULL));
    printf("%d\n", axiscAttributeSetPrefix(attr1, prefix));
    bn=axiscHeaderBlockCreateImmediateChildBasicNode(phb, ELEMENT_NODE,"Project","","","");
    attr2=axiscBasicNodeCreateAttribute(bn, "TYPE",NULL, NULL, "Open Source");
    
    /* Tests for non declared namespace prefix */
    printf("%d\n", axiscAttributeSetPrefix(attr2, "nd"));
    printf( "Header Attribute Prefix = %s\n" , axiscAttributeGetPrefix(attr1));
    printf( "Child Node Attribute Prefix = %s\n" , axiscAttributeGetPrefix(attr2));
    op = "add";
    i1 = 2;
    i2 = 3;
    if (strcmp(op, "add") == 0)
    {
        iResult = add(ws, i1, i2);
        if (!exceptionOccurred)
            printf("%d\n", iResult );
    }
    
    destroy_Calculator_stub(ws);
    
    printf("---------------------- TEST COMPLETE -----------------------------\n");
    
    return 0;
}

