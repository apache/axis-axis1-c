/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 * @author Rangika Mendis (rangika@opensource.lk)
 *
 */

#include "test7.h"
#include <axis/GDefine.hpp>
#include <axis/IHandlerSoapSerializer.hpp>
#include <axis/IHandlerSoapDeSerializer.hpp>
#include <axis/BasicNode.hpp>
#include <iostream>



test7::test7()
{
}

test7::~test7()
{
}

int test7::invoke(void *pvIMsg)
{
    int iStatus = 0;
    
    IMessageData *pIMsg = (IMessageData*) pvIMsg;
    AxisChar* pachTemp;
	
    IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

//... Creating the Header Block...........

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();
		pIHeaderBlock->setLocalName("Student");
		pIHeaderBlock->setURI("http://soapinterop.org/echoheader/");

//........ Creating the 1st Element Node.......

        BasicNode* pBasicNode = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode->setLocalName("StudDetails");
		pIHeaderBlock->addChild(pBasicNode);

//.......Creating the 2nd Element Node......
        

        BasicNode* pBasicNode1 = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode1->setLocalName("StudNo");
        pBasicNode->addChild(pBasicNode1);

//........ Creating the 1st Character Node.......


        BasicNode* pBasicNode2 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode2->setValue("1111");
		pBasicNode1->addChild(pBasicNode2);

//.......Creating the 3rd Element Node......

        BasicNode* pBasicNode3 = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode3->setLocalName("StudName");
        pBasicNode->addChild(pBasicNode3);

//......Creating the 4th Element Node......

        BasicNode* pBasicNode4 = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode4->setLocalName("FirstName");
		pBasicNode3->addChild(pBasicNode4);
		

//........ Creating the 2nd Character Node....... 
        
        BasicNode* pBasicNode5 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode5->setValue("Keanu");	
		pBasicNode4->addChild(pBasicNode5);

//......Creating the 5th Element Node......

        BasicNode* pBasicNode6 = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode6->setLocalName("LastName");
        pBasicNode3->addChild(pBasicNode6);
        
//........ Creating the 3rd Character Node....... 


        BasicNode* pBasicNode7 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode7->setValue("Reeves");
		pBasicNode6->addChild(pBasicNode7);
        
    //Deleting the header block

	iStatus = pISZ->deleteHeaderBlock("Student","http://soapinterop.org/echoheader/");    

    return AXIS_SUCCESS; 
  
}	

void test7::onFault(void *pvIMsg)
{

}

int test7::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int test7::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
