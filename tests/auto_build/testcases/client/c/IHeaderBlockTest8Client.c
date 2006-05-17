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

/* Tests createStdAttribute APIs for SOAPVER_1_1 in IHeaderBlock 
   Author @ James Jose
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "Calculator.h"



int main(int argc, char* argv[])
{
    AXISCHANDLE ws, ws1, ws2, ws3;
        
    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";
    int i1=0, i2=0;
    int iResult;
    
    AXISCHANDLE phb, phb1, phb2, phb3;
    AXISCHANDLE attr, attr1, attr2, attr3;
    
    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1)
        url = argv[1];
    sprintf(endpoint, "%s", url);
    ws = get_Calculator_stub(endpoint);
    i1 = 2;
    i2 = 3;
    phb = axiscStubCreateSOAPHeaderBlock(ws,"TestHeader","http://ws.apache.org/", NULL);
    attr = axiscHeaderBlockCreateStdAttribute(phb, ACTOR,SOAP_VER_1_1);
    printf("%s = %s\n",  axiscAttributeGetLocalName(attr), axiscAttributeGetValue(attr));
    
    iResult=add(ws, i1, i2);
    printf("%d\n",  iResult );
    
    ws1 = get_Calculator_stub(endpoint);
    phb1 = axiscStubCreateSOAPHeaderBlock(ws1, "TestHeader","http://ws.apache.org/", NULL);
    attr1 = axiscHeaderBlockCreateStdAttribute(phb1, MUST_UNDERSTAND_TRUE,SOAP_VER_1_1);
    printf("%s = %s\n",  axiscAttributeGetLocalName(attr1), axiscAttributeGetValue(attr1));
    iResult=add(ws1, i1, i2);
    printf("%d\n",  iResult );
    
    ws2 = get_Calculator_stub(endpoint);
    phb2 = axiscStubCreateSOAPHeaderBlock(ws2, "TestHeader","http://ws.apache.org/", NULL);
    attr2 = axiscHeaderBlockCreateStdAttribute(phb2, MUST_UNDERSTAND_FALSE,SOAP_VER_1_1);
    printf("%s = %s\n",  axiscAttributeGetLocalName(attr2), axiscAttributeGetValue(attr2));
    iResult=add(ws2, i1, i2);
    printf("%d\n",  iResult );
    
    ws3 = get_Calculator_stub(endpoint);
    phb3 = axiscStubCreateSOAPHeaderBlock(ws3, "TestHeader","http://ws.apache.org/", NULL);
    attr3 = axiscHeaderBlockCreateStdAttribute(phb3, ROLE_NEXT,SOAP_VER_1_1);
    if(attr3==NULL)
        printf( "Null returned for non supporting standard attribute \n" );
    iResult=add(ws3, i1, i2);
    printf("%d\n",  iResult );
            
    destroy_Calculator_stub(ws);
    destroy_Calculator_stub(ws1);
    destroy_Calculator_stub(ws2);
    destroy_Calculator_stub(ws3);
                    
    printf("---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}

