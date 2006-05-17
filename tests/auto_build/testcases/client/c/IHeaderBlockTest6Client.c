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


/*This program tests clone() API in the IHeaderBlock class
@ Author : James Jose
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "Calculator.h"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
        
    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";
    const char* op = 0;
    int i1=0, i2=0;
    int iResult;

    AXISCHANDLE phb;
    AXISCHANDLE cl;
    AXISCHANDLE bn, bn1, bn2;
    
    
    axiscAxisRegisterExceptionHandler(exceptionHandler);
 
    if (argc > 1)
        url = argv[1];
    sprintf(endpoint, "%s", url);
    ws = get_Calculator_stub(endpoint);
    phb=axiscStubCreateSOAPHeaderBlock(ws,"TestHeader","http://apache.com","np");
    axiscHeaderBlockCreateImmediateChildBasicNode(phb, CHARACTER_NODE,"","","","Test Message");
    cl=axiscHeaderBlockCloneHeaderBlock(phb);
    axiscHeaderBlockCreateImmediateChildBasicNode(cl,ELEMENT_NODE,"Name","","","");
    printf("No of Child in clone=%d\n", axiscHeaderBlockGetNoOfChildren(cl));
    printf("No of Child in original=%d\n", axiscHeaderBlockGetNoOfChildren(phb));
    bn=axiscHeaderBlockGetFirstChildBasicNode(phb);
    axiscBasicNodeSetValue(bn, "Axis");
    printf( "First Child Value=%s\n", axiscBasicNodeGetValue(bn));
    bn1=axiscHeaderBlockGetFirstChildBasicNode(cl);
    bn2=axiscHeaderBlockGetLastChildBasicNode(cl);
    printf( "First Child Value in clone=%s\n", axiscBasicNodeGetValue(bn1));
    printf( "Last Child Name in clone=%s\n", axiscBasicNodeGetLocalName(bn2));
    op = "add";
    i1 = 2;
    i2 = 3;
    if (strcmp(op, "add") == 0)
    {
        iResult = add(ws, i1, i2);
        printf("%d\n", iResult);
    }

    destroy_Calculator_stub(ws);
    
    printf("---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}
