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
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO THIS FILE MAY ALSO REQUIRE CHANGES TO THE               */
/* C-EQUIVALENT FILE. PLEASE ENSURE THAT IT IS DONE.                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#include "Calculator.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/IAttribute.hpp>
#include <axis/AxisException.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";
    const char* op = 0;
    int i1=0, i2=0;
    int iResult;

    bool bSuccess = false;
    int     iRetryIterationCount = 3;

    IHeaderBlock *phb;
    BasicNode *ch;
    BasicNode *Bnode1, *Bnode2, *Bnode3, *Bnode4,*Bnode4a, *Bnode5, *Bnode6, *Bnode7, *Bnode8;
    BasicNode * firstnode, *secondnode, *parentnode, *childnode, *lastnode;
    IAttribute *a;
        
    AxisChar *localname="Name";
    AxisChar *prefix="np";
    AxisChar *uri="http://ws.apache.org/";
    
    do
    {
        try
        {
            if (argc > 1)
                url = argv[1];
            sprintf(endpoint, "%s", url);
            Calculator ws(endpoint);
            op = "add";
            i1 = 2;
            i2 = 3;
            phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
            Bnode1=phb->createChild(ELEMENT_NODE,localname,prefix,uri, NULL);
            /*Passing NULL as argument*/
            if(phb->createChild(ELEMENT_NODE,NULL,NULL,NULL, NULL))
                cout<<"NULL Returned for Element_node"<<endl;
            if(phb->createChild(CHARACTER_NODE,NULL,NULL,NULL, NULL))
                cout<<"NULL Returned for Character_node"<<endl;
            Bnode2=phb->createChild(CHARACTER_NODE,NULL,NULL,NULL,"APACHE");
            Bnode3=phb->createChild(ELEMENT_NODE,"FirstPart","np1","http://ws.apache.org/", NULL);
            Bnode4=phb->createChild(ELEMENT_NODE,"LastPart","","http://ws.apache.org/", NULL);
            Bnode5=phb->createChild(CHARACTER_NODE,"","","","APACHE");
            Bnode6=phb->createChild(ELEMENT_NODE);
            Bnode6->setLocalName("Project");
            a=Bnode6->createAttribute("Type","Open Source");
            cout <<"Project Type=" << a->getValue() << endl;
            Bnode7=phb->createChild(CHARACTER_NODE);
            Bnode7->setValue("AXISCPP");
            Bnode4a=phb->createChild(ELEMENT_NODE,"LastPartChild","","http://ws.apache.org/", NULL);
            Bnode4->addChild(Bnode4a);
            Bnode6->addChild(Bnode7);
            Bnode3->addChild(Bnode2);
            Bnode4a->addChild(Bnode5);
            Bnode1->addChild(Bnode3);
            Bnode1->addChild(Bnode4);
            phb->addChild(Bnode1);
            phb->addChild(Bnode6);
            Bnode8=phb->createChild(CHARACTER_NODE,"","","","This is a test message");
            cout << phb->addChild(Bnode8)<<endl;
            cout<<"AddChild returned "<< phb->addChild(NULL) << " For NULL Value "<< endl;
            cout << "No Of Children = " << phb->getNoOfChildren()<<endl;
            firstnode=phb->getFirstChild();
            cout << "First Node Name = " << firstnode->getLocalName() << endl;
            secondnode=phb->getChild(2);
            childnode=secondnode->getFirstChild();
            cout << "Second Node Name=" << secondnode->getLocalName() << " Value = " << childnode->getValue()<< endl ;
            cout << "Second Node Type = " << secondnode->getNodeType() << endl;
            lastnode=phb->getLastChild();
            cout  << "Last Node Value = " << lastnode->getValue() << endl;
            cout  << "Last Node Type = " << lastnode->getNodeType() << endl;
            if (strcmp(op, "add") == 0)
            {
                iResult=ws.add(i1, i2);
                cout  << iResult << endl;
            }
            bSuccess = true;
        }
        catch(AxisException& e)
        {
            bool bSilent = false;

            if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
            {
                if( iRetryIterationCount > 0)
                    bSilent = true;
            }
            else
                iRetryIterationCount = 0;

            if( !bSilent)
                cout << "Exception : " << e.what() << endl;
        }
        catch(exception& e)
        {
            cout << "Unknown exception has occured" << endl;
        }
        catch(...)
        {
            cout << "Unspecified exception has occured" << endl;
        }
        iRetryIterationCount--;
    } 
    while( iRetryIterationCount > 0 && !bSuccess);
    
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
    return 0;
}
