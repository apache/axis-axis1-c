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

#include "test1.h"
#include <axis/GDefine.hpp>
#include <axis/IHandlerSoapSerializer.hpp>
#include <axis/IHandlerSoapDeSerializer.hpp>
#include <axis/BasicNode.hpp>
#include <iostream>



test1::test1()
{
}

test1::~test1()
{
}

int test1::invoke(void *pvIMsg)
{
	IMessageData *pIMsg = (IMessageData*) pvIMsg;
    AxisChar* pachTemp;
	
    IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();

		pIHeaderBlock->setLocalName("TestHeader");
		pIHeaderBlock->setURI("http://soapinterop.org/echoheader/");

//........ Creating the 1st Element Node.......

        BasicNode* pBasicNode = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode->setLocalName("User Name");
		
		pIHeaderBlock->addChild(pBasicNode);

//..........Creating the 1st Character Node.........

        BasicNode* pBasicNode1 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode1->setValue("TestName");
		
		pBasicNode->addChild(pBasicNode1);

//........ Creating the 2nd Element Node.......


        BasicNode* pBasicNode2 = pIHeaderBlock->createChild(ELEMENT_NODE);
		pBasicNode2->setLocalName("Password");
		
		pIHeaderBlock->addChild(pBasicNode2);

//.......Creating the 2nd Character Node.......

        BasicNode* pBasicNode3 = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode3->setValue("Testpw");
		
		pBasicNode2->addChild(pBasicNode3);
    	 

        //Getting the header block

        IHeaderBlock* pIHeaderBlock1= pISZ->getHeaderBlock("TestHeader","http://soapinterop.org/echoheader/"); 
	    
        //Getting the 1st child
        if (pIHeaderBlock1 != NULL) {

			 BasicNode* pBasicNode4= pIHeaderBlock1->getChild(1);
						
			const AxisChar* pachHeaderValue;

			if (pBasicNode4 != NULL) 
			{
				if((pBasicNode4->getNodeType()) == ELEMENT_NODE) {
                    
                    BasicNode* pBasicNode5 = pBasicNode4->getFirstChild();

                    if((pBasicNode5->getNodeType()) == CHARACTER_NODE){
                    pachHeaderValue= pBasicNode5->getValue();

                    
                    }


				} else {
					pachHeaderValue = "This was not the expected value Ros";
                    
                }
            }else 
			{
				pachHeaderValue = "pBascNode is NULL";
	
            }

// Getting the 2nd child

BasicNode* pBasicNode6= pIHeaderBlock1->getChild(2);
						
			const AxisChar* pachHeaderValue1;

			if (pBasicNode6 != NULL) 
			{
				if((pBasicNode6->getNodeType()) == ELEMENT_NODE) {
                    
                    BasicNode* pBasicNode7 = pBasicNode6->getFirstChild();

                    if((pBasicNode7->getNodeType()) == CHARACTER_NODE){
                    pachHeaderValue1= pBasicNode7->getValue();

                    
                    }


				} else {
					pachHeaderValue1 = "This was not the expected value Ros";
                    
                }
			} else 
			{
				pachHeaderValue1 = "pBascNode is NULL";
	
            }

            
 FILE *pFile = fopen("rangifile.txt", "a");
            fputs(pachHeaderValue, pFile);
            fputs("\n", pFile);
            fputs(pachHeaderValue1,pFile);
            fputs("\n", pFile);
            fclose(pFile);

return AXIS_SUCCESS;   

}
}		
void test1::onFault(void *pvIMsg)
{

}

int test1::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int test1::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
