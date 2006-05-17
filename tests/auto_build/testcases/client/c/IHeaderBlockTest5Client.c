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


/* Tests createImmdediateChild() APIs and getChild() API
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
    
    AxiscChar *localname="Name";
    AxiscChar *prefix="np";
    AxiscChar *uri="http://ws.apache.org/";

    AXISCHANDLE phb;
    AXISCHANDLE Bnoden, Bnoden2;
    AXISCHANDLE ch;
    AXISCHANDLE Bnode1, Bnode2, Bnode3, Bnode4, Bnode5, Bnode6, Bnode7, Bnode8, Bnode9;
    AXISCHANDLE firstnode, parentnode, childnode, lastnode;
    AXISCHANDLE nullNode, nullNode1, nullNode2;
    AXISCHANDLE a;
    
    
    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc > 1)
        url = argv[1];
    sprintf(endpoint, "%s", url);
    ws = get_Calculator_stub(endpoint);
    op = "add";
    i1 = 2;
    i2 = 3;
    phb = axiscStubCreateSOAPHeaderBlock(ws,"TestHeader","http://ws.apache.org/", NULL);

    /*An element node Bnoden1 is created  and set its name using setLocalName() */
    Bnoden=axiscHeaderBlockCreateImmediateChildBasicNode(phb, ELEMENT_NODE,NULL,NULL,NULL,NULL);
    printf("%d\n", axiscBasicNodeGetNodeType(Bnoden));
    axiscBasicNodeSetLocalName(Bnoden, "Project");
    ch=axiscHeaderBlockCreateChildBasicNode(phb, CHARACTER_NODE,NULL,NULL,NULL,"AXISCPP");
    axiscBasicNodeAddChild(Bnoden, ch);

    Bnoden2=axiscHeaderBlockCreateImmediateChildBasicNode(phb, CHARACTER_NODE,NULL,NULL,NULL,NULL);
    if(Bnoden2==NULL)
        printf( "Null returned for Character_node\n" );
    else
        axiscBasicNodeSetValue(Bnoden2, "AXISCPP");


    Bnode1=axiscHeaderBlockCreateImmediateChildBasicNode(phb, ELEMENT_NODE,localname,prefix,uri, NULL);
    Bnode2=axiscHeaderBlockCreateChildBasicNode(phb, CHARACTER_NODE,NULL,NULL,NULL,"AXIS");
    Bnode3=axiscHeaderBlockCreateChildBasicNode(phb, ELEMENT_NODE,"FirstPart","np1","http://ws.apache.org/", NULL);
    Bnode4=axiscHeaderBlockCreateImmediateChildBasicNode(phb, ELEMENT_NODE,"Location","","http://ws.apache.org/", NULL);
    Bnode5=axiscHeaderBlockCreateChildBasicNode(phb, CHARACTER_NODE,"","","","Sri Lanka");
    Bnode6=axiscHeaderBlockCreateImmediateChildBasicNode(phb, ELEMENT_NODE, NULL, NULL, NULL, NULL);
    axiscBasicNodeSetLocalName(Bnode6, "Project");
    a=axiscBasicNodeCreateAttribute(Bnode6, "Type",NULL, NULL, "Open Source");
    printf( "Project Type=%s\n",  axiscAttributeGetValue(a)) ;
    Bnode7=axiscHeaderBlockCreateChildBasicNode(phb, CHARACTER_NODE, NULL, NULL, NULL, NULL);
    axiscBasicNodeSetValue(Bnode7, "AXISCPP");
    axiscBasicNodeAddChild(Bnode6, Bnode7);
    axiscBasicNodeAddChild(Bnode3, Bnode2);
    axiscBasicNodeAddChild(Bnode4, Bnode5);
    axiscBasicNodeAddChild(Bnode1, Bnode3);
    Bnode8=axiscHeaderBlockCreateImmediateChildBasicNode(phb, CHARACTER_NODE,"","","","This is a test ");
    Bnode9=axiscHeaderBlockCreateImmediateChildBasicNode(phb, CHARACTER_NODE, NULL, NULL, NULL, NULL);
    axiscBasicNodeSetValue(Bnode9, "message");
    printf( "No Of Children=%d\n", axiscHeaderBlockGetNoOfChildren(phb)) ;
    firstnode=axiscHeaderBlockGetFirstChildBasicNode(phb);
    printf( "First Node Name = %s\n", axiscBasicNodeGetLocalName(firstnode)) ;
    parentnode=axiscHeaderBlockGetChildBasicNode(phb, 5);
    childnode=axiscBasicNodeGetFirstChildBasicNode(parentnode);
    printf( "Parent Node Name = %s", axiscBasicNodeGetLocalName(parentnode));
    printf(  " Value =%s\n", axiscBasicNodeGetValue(childnode) );
    lastnode=axiscHeaderBlockGetLastChildBasicNode(phb);
    printf("Last Child Value=%s\n", axiscBasicNodeGetValue(lastnode));
    nullNode=axiscHeaderBlockGetChildBasicNode(phb, axiscHeaderBlockGetNoOfChildren(phb)+1);
    if(nullNode!=NULL)
        printf( "NULL is not returned for non existing node\n" ) ;
    nullNode1=axiscHeaderBlockGetChildBasicNode(phb, 0);
    if(nullNode1!=NULL)
        printf( "NULL is not returned for child location 0\n") ;
    nullNode2=axiscHeaderBlockGetChildBasicNode(phb, -2);
    if(nullNode2!=NULL)
        printf( "NULL is not returned for -ve  child location\n");
    if (strcmp(op, "add") == 0)
    {
        iResult=add(ws, i1, i2);
        printf("%d\n", iResult );
    }

    destroy_Calculator_stub(ws);
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}
