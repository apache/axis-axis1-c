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


/* Tests createNamespaceDecl(),createAttribute() and getAttributeValue() APIs in IHeaderBlock 
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
    
    const AxiscChar *prefix="np";
    const AxiscChar *uri="http://ws.apache.org/";
    const AxiscChar *temp="apache";
    const AxiscChar *localname="name";

    AXISCHANDLE phb;
    AXISCHANDLE Insp1, Insp2;
    AXISCHANDLE attr1, attr2;
    AXISCHANDLE Iattr1, Iattr2, Iattr3;
    
    if (argc > 1)
        url = argv[1];
    sprintf(endpoint, "%s", url);
    ws = get_Calculator_stub(endpoint);
    op = "add";
    i1 = 2;
    i2 = 3;
    phb = axiscStubCreateSOAPHeaderBlock(ws, "TestHeader","http://ws.apache.org/", NULL);
    Insp1=axiscHeaderBlockCreateNamespaceDeclINamespace(phb, prefix,uri);
    Insp2=axiscHeaderBlockCreateNamespaceDeclINamespace(phb, "np1","http://axis.apache.org/");

    attr1=axiscHeaderBlockCreateAttribute(phb, NULL,NULL,NULL,NULL);
    attr2=axiscHeaderBlockCreateAttribute(phb, NULL,NULL,NULL,NULL);
    if(attr1 || attr2)
        printf( "Attribute returned for NULL arguments in createAttribute\n");

    Iattr1=axiscHeaderBlockCreateAttribute(phb, localname,prefix,NULL,temp);
    Iattr2=axiscHeaderBlockCreateAttribute(phb, localname,"np1","","Axis");
    Iattr3=axiscHeaderBlockCreateAttribute(phb, localname,"","","");

    printf( "np:name=%s\n" , axiscHeaderBlockGetAttributeValue(phb, localname,prefix));
    printf( "np1:name=%s\n" , axiscHeaderBlockGetAttributeValue(phb, "name","np1"));
    printf("name=%s\n" , axiscHeaderBlockGetAttributeValue(phb, "name",""));
    if(axiscHeaderBlockGetAttributeValue(phb, NULL,NULL)!=NULL)
        printf("NULL is not returned for NULL argumets in getAttributeValue\n");
    if(axiscHeaderBlockGetAttributeValue(phb, "name","nm")!=NULL)
        printf("NULL is not returned for Non existing attribute\n");
    if(axiscHeaderBlockGetAttributeValue(phb, "NAME","np1")!=NULL)
        printf("NULL is not returned for Non existing Attribute\n");
    if (strcmp(op, "add") == 0)
    {
        iResult=add(ws, i1, i2);
        printf( "%d\n", iResult );
    }

    destroy_Calculator_stub(ws);
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}
