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

#include "test2.h"
#include <axis/GDefine.hpp>
#include <axis/IHandlerSoapSerializer.hpp>
#include <axis/IHandlerSoapDeSerializer.hpp>
#include <axis/BasicNode.hpp>
#include <iostream>



test2::test2()
{
}

test2::~test2()
{
}

int test2::invoke(void *pvIMsg)
{
    
    int iStatus = 0;

 IMessageData *pIMsg = (IMessageData*) pvIMsg;
    AxisChar* pachTemp;
	
    IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

// Setting a header block

        	IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();

		pIHeaderBlock->setLocalName("TestHeader");
		pIHeaderBlock->setURI("http://soapinterop.org/echoheader/");

//........ creating the User Name.......

        	BasicNode* pBasicNode = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode->setLocalName("User Name");
		
		pIHeaderBlock->addChild(pBasicNode);

        BasicNode* pBasicNode1 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode1->setValue("TestName");
		
		pBasicNode->addChild(pBasicNode1);

        //........ creating the Password.......


        BasicNode* pBasicNode2 = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode2->setLocalName("Password");
		
		pIHeaderBlock->addChild(pBasicNode2);

        BasicNode* pBasicNode3 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode3->setValue("Testpw");
		
		pBasicNode2->addChild(pBasicNode3);
    	 
//Deleting a header block

	iStatus = pISZ->deleteHeaderBlock("TestHeader","http://soapinterop.org/echoheader/");    

    return iStatus;
}

void test2::onFault(void *pvIMsg)
{

}

int test2::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int test2::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
