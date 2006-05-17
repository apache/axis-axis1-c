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


/* Tests createChild(),addChild(),getNoOfChildren() and getchild() APIs 
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
    AXISCHANDLE ch;
    AXISCHANDLE Bnode1, Bnode2, Bnode3, Bnode4,Bnode4a, Bnode5, Bnode6, Bnode7, Bnode8;
    AXISCHANDLE firstnode, secondnode, parentnode, childnode, lastnode;
    AXISCHANDLE a;
        
    AxiscChar *localname="Name";
    AxiscChar *prefix="np";
    AxiscChar *uri="http://ws.apache.org/";
    
    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc > 1)
        url = argv[1];
    sprintf(endpoint, "%s", url);
    ws = get_Calculator_stub(endpoint);
    op = "add";
    i1 = 2;
    i2 = 3;
    phb = axiscStubCreateSOAPHeaderBlock(ws, "TestHeader","http://ws.apache.org/", NULL);
    Bnode1=axiscHeaderBlockCreateChildBasicNode(phb, ELEMENT_NODE,localname,prefix,uri, NULL);
    /*Passing NULL as argument*/
    if(axiscHeaderBlockCreateChildBasicNode(phb,ELEMENT_NODE,NULL,NULL,NULL, NULL))
        printf("NULL Returned for Element_node\n");
    if(axiscHeaderBlockCreateChildBasicNode(phb,CHARACTER_NODE,NULL,NULL,NULL, NULL))
        printf("NULL Returned for Character_node\n");
    Bnode2=axiscHeaderBlockCreateChildBasicNode(phb,CHARACTER_NODE,NULL,NULL,NULL,"APACHE");
    Bnode3=axiscHeaderBlockCreateChildBasicNode(phb,ELEMENT_NODE,"FirstPart","np1","http://ws.apache.org/", NULL);
    Bnode4=axiscHeaderBlockCreateChildBasicNode(phb,ELEMENT_NODE,"LastPart","","http://ws.apache.org/", NULL);
    Bnode5=axiscHeaderBlockCreateChildBasicNode(phb,CHARACTER_NODE,"","","","APACHE");
    Bnode6=axiscHeaderBlockCreateChildBasicNode(phb,ELEMENT_NODE, NULL, NULL, NULL, NULL);
    axiscBasicNodeSetLocalName(Bnode6, "Project");
    a=axiscBasicNodeCreateAttribute(Bnode6, "Type",NULL, NULL, "Open Source");
    printf("Project Type=%s\n" , axiscAttributeGetValue(a) );
    Bnode7=axiscHeaderBlockCreateChildBasicNode(phb, CHARACTER_NODE, NULL, NULL, NULL, NULL);
    axiscBasicNodeSetValue(Bnode7, "AXISCPP");
    Bnode4a=axiscHeaderBlockCreateChildBasicNode(phb, ELEMENT_NODE,"LastPartChild","","http://ws.apache.org/", NULL);
    axiscBasicNodeAddChild(Bnode4, Bnode4a);
    axiscBasicNodeAddChild(Bnode6, Bnode7);
    axiscBasicNodeAddChild(Bnode3, Bnode2);
    axiscBasicNodeAddChild(Bnode4a, Bnode5);
    axiscBasicNodeAddChild(Bnode1, Bnode3);
    axiscBasicNodeAddChild(Bnode1, Bnode4);
    axiscHeaderBlockAddChild(phb,Bnode1);
    axiscHeaderBlockAddChild(phb,Bnode6);
    Bnode8=axiscHeaderBlockCreateChildBasicNode(phb, CHARACTER_NODE,"","","","This is a test message");
    printf("%d\n",  axiscHeaderBlockAddChild(phb, Bnode8));
    printf("AddChild returned %d For NULL Value \n", axiscHeaderBlockAddChild(phb,NULL));
    printf( "No Of Children = %d\n" , axiscHeaderBlockGetNoOfChildren(phb));
    firstnode=axiscHeaderBlockGetFirstChildBasicNode(phb);
    printf( "First Node Name = %s\n" , axiscBasicNodeGetLocalName(firstnode) );
    secondnode=axiscHeaderBlockGetChildBasicNode(phb,2);
    childnode=axiscBasicNodeGetFirstChildBasicNode(secondnode);
    printf( "Second Node Name=%s Value = %s\n" , axiscBasicNodeGetLocalName(secondnode), axiscBasicNodeGetValue(childnode)) ;
    printf( "Second Node Type = %d\n" , axiscBasicNodeGetNodeType(secondnode) );
    lastnode=axiscHeaderBlockGetLastChildBasicNode(phb);
    printf( "Last Node Value = %s\n" , axiscBasicNodeGetValue(lastnode) );
    printf( "Last Node Type = %d\n" , axiscBasicNodeGetNodeType(lastnode) );
    if (strcmp(op, "add") == 0)
    {
        iResult=add(ws, i1, i2);
        printf( "%d\n", iResult );
    }

    destroy_Calculator_stub(ws);

    printf( "---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}
