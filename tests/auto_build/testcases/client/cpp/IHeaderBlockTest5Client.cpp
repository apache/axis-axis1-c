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
        url = argv[1];
                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                op = "add";
                i1 = 2;
                i2 = 3; 
                AxisChar *localname="Name";
                AxisChar *prefix="np";
                AxisChar *uri="http://ws.apache.org/";
                IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");

                
                /*An element node Bnoden1 is created  and set its name using setLocalName() */
                BasicNode * Bnoden=phb->createImmediateChild(ELEMENT_NODE,NULL,NULL,NULL,NULL);
                cout<<Bnoden->getNodeType()<<endl;
        Bnoden->setLocalName("Project");
                BasicNode *ch=phb->createChild(CHARACTER_NODE,NULL,NULL,NULL,"AXISCPP");
                Bnoden->addChild(ch);

                BasicNode * Bnoden2=phb->createImmediateChild(CHARACTER_NODE,NULL,NULL,NULL,NULL);
                if(Bnoden2==NULL)
                        cout << "Null returned for Character_node" << endl;
                else{
                        Bnoden2->setValue("AXISCPP");
                }


                BasicNode * Bnode1=phb->createImmediateChild(ELEMENT_NODE,localname,prefix,uri, NULL);  
        BasicNode * Bnode2=phb->createChild(CHARACTER_NODE,NULL,NULL,NULL,"AXIS");
                BasicNode * Bnode3=phb->createChild(ELEMENT_NODE,"FirstPart","np1","http://ws.apache.org/", NULL);
                BasicNode * Bnode4=phb->createImmediateChild(ELEMENT_NODE,"Location","","http://ws.apache.org/", NULL);
                BasicNode * Bnode5=phb->createChild(CHARACTER_NODE,"","","","Sri Lanka");               
                BasicNode * Bnode6=phb->createImmediateChild(ELEMENT_NODE);
                Bnode6->setLocalName("Project");
                IAttribute *a=Bnode6->createAttribute("Type","Open Source");                    
                        cout << "Project Type=" << a->getValue()<< endl ;
                BasicNode * Bnode7=phb->createChild(CHARACTER_NODE);
                Bnode7->setValue("AXISCPP");
                Bnode6->addChild(Bnode7);
                Bnode3->addChild(Bnode2);
                Bnode4->addChild(Bnode5);
                Bnode1->addChild(Bnode3);               
                BasicNode * Bnode8=phb->createImmediateChild(CHARACTER_NODE,"","","","This is a test ");
                BasicNode *Bnode9=phb->createImmediateChild(CHARACTER_NODE);
                Bnode9->setValue("message");
                cout << "No Of Children=" << phb->getNoOfChildren()<< endl ;
            BasicNode * firstnode=phb->getFirstChild();
                cout << "First Node Name = " << firstnode->getLocalName()<< endl ;
                BasicNode * parentnode=phb->getChild(5);
                BasicNode * childnode=parentnode->getFirstChild();              
                cout << "Parent Node Name = " << parentnode->getLocalName();
                cout <<  " Value =" << childnode->getValue() << endl;
                BasicNode * lastnode=phb->getLastChild();
                cout  << "Last Child Value=" << lastnode->getValue()<< endl;
                BasicNode *nullNode=phb->getChild(phb->getNoOfChildren()+1);
                if(nullNode!=NULL)
                        cout << "NULL is not returned for non existing node" << endl ;
                BasicNode *nullNode1=phb->getChild(0);
                if(nullNode1!=NULL)
                        cout << "NULL is not returned for child location 0"<< endl ;
                BasicNode *nullNode2=phb->getChild(-2);
                if(nullNode2!=NULL)
                        cout << "NULL is not returned for -ve  child location"<< endl;
                if (strcmp(op, "add") == 0)
                {
                        iResult=ws.add(i1, i2); 
                        cout << iResult << endl;
                }
            bSuccess = true;
        }
        catch(AxisException& e)
        {
                        bool bSilent = false;

                        if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
                        {
                                if( iRetryIterationCount > 0)
                                {
                                        bSilent = true;
                                }
                        }
                        else
                        {
                                iRetryIterationCount = 0;
                        }

            if( !bSilent)
                        {
                                cout << "Exception : " << e.what() << endl;
                        }
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
                } while( iRetryIterationCount > 0 && !bSuccess);
        cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;     
        return 0;
}
