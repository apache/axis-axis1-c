/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 * @author Andrew Perry (perryan@uk.ibm.com)
 *
 *****************************************************************************
 * Test Logic.
 *
 * Create the follow header block with a Complex Node with 5 attributes and 2 child
 * complex nodes, each of which has a child character node.
 *
 * <ns2:basicNodeTest xmlns:ns2="http://soapinterop.org/basicNodeTest/">
 *  <bntn:basicNodeTestNode xmlns:bntn="http://soapinterop.org/basicNodeTestNode/" 
 *        bntn:attr1="one" bntn:attr2="two" bntn:attr3="three"
 *        bntn:attr4="four" bntn:attr5="five">
 *   <bntc:basicNodeTestChild xmlns:bntc="http://soapinterop.org/basicNodeTestChild/">
 *    sub node value1
 *   </bntc:basicNodeTestChild>
 *   <bntc2:basicNodeTestChild xmlns:bntc2="http://soapinterop.org/basicNodeTestChild2/">
 *    sub node value2
 *   </bntc2:basicNodeTestChild>
 *  </bntn:basicNodeTestNode>
 * </ns2:basicNodeTest>
 * 
 * From this we are testing:
 *  - 2 different signitures of BasicNode->createAttribute
 *  - BasicNode->getNoOfChildren
 *  - BasicNode->getFirstChild
 *  - BasicNode->getLastChild
 *  - BasicNode->getChild(int)
 *  - BasicNode->getFirstAttribute()
 *  - BasicNode->getLastAttribute()
 *  - BasicNode->getCurrentAttribute()
 *  - BasicNode->getAttribute(AxisChar*, AxisChar*, AxisChar*)
 * 
 * This is not an ideal test as ideally the attributes would have been set by 
 * the server and the attribute retrieved in the response message. For simplicity
 * the items are set in 1 handler in a handler chain and retrieved in a second
 * handler.
 *
 * Test success is measured by comparing the actual output and request with an
 * expected request and output.
 *****************************************************************************
 *
 */

#include "THandler.h"
#include <axis/GDefine.hpp>
#include <axis/IHandlerSoapSerializer.hpp>
#include <axis/IHandlerSoapDeSerializer.hpp>
#include <axis/BasicNode.hpp>
#include <iostream>

THandler::THandler()
{
    m_pOption = NULL;
    m_sEmpty = "";
}

THandler::~THandler()
{

}

const string& THandler::getOption(const string& sArg)
{
  map<string, string>::const_iterator it = m_pOption->find(sArg);
  if (it != m_pOption->end())
  {
      return (*it).second;
  }
  return m_sEmpty;	
}

void THandler::setOptionList(const map<string, string>* OptionList)
{
   m_pOption = OptionList;
}

int THandler::invoke(void *pvIMsg)
{
	IMessageData *pIMsg = (IMessageData*) pvIMsg;

	if(pIMsg->isPastPivot()) {
		/*this is a response*/

		
		
	} else {
		/*this is a request*/
		
		IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();

		pIHeaderBlock->setLocalName("basicNodeTest");
		pIHeaderBlock->setURI("http://soapinterop.org/basicNodeTest/");


		BasicNode* pComplexNode = pIHeaderBlock->createChild(ELEMENT_NODE, "basicNodeTestNode", "bntn", "http://soapinterop.org/basicNodeTestNode/", NULL);

		pIHeaderBlock->addChild(pComplexNode);

		IAttribute* pIAttribute1 = pComplexNode->createAttribute("attr1", "bntn", "http://soapinterop.org/basicNodeTestNode/", "one");
		IAttribute* pIAttribute2 = pComplexNode->createAttribute("attr2", "bntn", "two");
		IAttribute* pIAttribute3 = pComplexNode->createAttribute("attr3", "bntn", "three");
		IAttribute* pIAttribute4 = pComplexNode->createAttribute("attr4", "bntn", "four");
		IAttribute* pIAttribute5 = pComplexNode->createAttribute("attr5", "bntn", "five");

		BasicNode* pChildNode1 = pIHeaderBlock->createChild(ELEMENT_NODE, "basicNodeTestChild", "bntc", "http://soapinterop.org/basicNodeTestChild/", NULL);
		BasicNode* pChildNode2 = pIHeaderBlock->createChild(ELEMENT_NODE, "basicNodeTestChild", "bntc2", "http://soapinterop.org/basicNodeTestChild2/", NULL);


		BasicNode* pBasicNode1 =  pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode1->setValue("sub node value1");

		BasicNode* pBasicNode2 =  pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode2->setValue("sub node value2");


		pChildNode1->addChild(pBasicNode1);
		pChildNode2->addChild(pBasicNode2);
		pComplexNode->addChild(pChildNode1);
		pComplexNode->addChild(pChildNode2);

	}

	return AXIS_SUCCESS;
}

void THandler::onFault(void *pvIMsg)
{

}

int THandler::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int THandler::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
