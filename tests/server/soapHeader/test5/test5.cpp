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

#include "test5.h"
#include <axis/GDefine.hpp>
#include <axis/IHandlerSoapSerializer.hpp>
#include <axis/IHandlerSoapDeSerializer.hpp>
#include <axis/BasicNode.hpp>
#include <iostream>



test5::test5()
{
}

test5::~test5()
{
}

int test5::invoke(void *pvIMsg)
{

    int iStatus = 0;
    
    IMessageData *pIMsg = (IMessageData*) pvIMsg;
    AxisChar* pachTemp;
	
    IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

//... Creating the 1st Header Block...........

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();

		pIHeaderBlock->setLocalName("FirstHeader");
		pIHeaderBlock->setURI("http://soapinterop.org/echoheader/");

//........ Creating the 1st Element Node.......

        	BasicNode* pBasicNode = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode->setLocalName("FirstElement");
		
		pIHeaderBlock->addChild(pBasicNode);

//.......Creating the 1st Character Node......
        

        BasicNode* pBasicNode1 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode1->setValue("FirstChild");
		
		pBasicNode->addChild(pBasicNode1);

//........ Creating the 2nd Element Node.......


        BasicNode* pBasicNode2 = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode2->setLocalName("SecondElement");
		
		pIHeaderBlock->addChild(pBasicNode2);

//.......Creating the 2nd  Character Node......

        BasicNode* pBasicNode3 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode3->setValue("SecondChild");
		
		pBasicNode2->addChild(pBasicNode3);
    	 


//.... Creating the 2nd Header Block............

		IHeaderBlock* pIHeaderBlock2= pISZ->createHeaderBlock();

		pIHeaderBlock2->setLocalName("SecondHeader");
		pIHeaderBlock2->setURI("http://soapinterop.org/echoheader/");

//........ Creating the 1st Element Node.......

        	BasicNode* pBasicNode8 = pIHeaderBlock2->createChild(ELEMENT_NODE);
		pBasicNode8->setLocalName("FirstElement");
		
		pIHeaderBlock2->addChild(pBasicNode8);

//..........Creating the 1st Character Node.......

        BasicNode* pBasicNode9 = pIHeaderBlock2->createChild(CHARACTER_NODE);
		pBasicNode9->setValue("FirstChild");
		
		pBasicNode8->addChild(pBasicNode9);

//........ Creating the 2nd Element Node.......


        BasicNode* pBasicNode10 = pIHeaderBlock2->createChild(ELEMENT_NODE);
		pBasicNode10->setLocalName("SecondElement");
		
		pIHeaderBlock2->addChild(pBasicNode10);

//.......Creating the 2nd Character Node........

        BasicNode* pBasicNode11 = pIHeaderBlock2->createChild(CHARACTER_NODE);
		pBasicNode11->setValue("SecondChild");
		
		pBasicNode10->addChild(pBasicNode11);

        iStatus = pISZ->removeSoapHeader();        
       
        return iStatus;
}		

void test5::onFault(void *pvIMsg)
{

}

int test5::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int test5::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
