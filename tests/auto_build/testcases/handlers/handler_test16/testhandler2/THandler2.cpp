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

#include "THandler2.h"
#include <axis/GDefine.hpp>
#include <axis/IHandlerSoapSerializer.hpp>
#include <axis/IHandlerSoapDeSerializer.hpp>
#include <axis/BasicNode.hpp>
#include <iostream>

THandler2::THandler2()
{
    m_pOption = NULL;
    m_sEmpty = "";
}

THandler2::~THandler2()
{

}

const string& THandler2::getOption(const string& sArg)
{
  map<string, string>::const_iterator it = m_pOption->find(sArg);
  if (it != m_pOption->end())
  {
      return (*it).second;
  }
  return m_sEmpty;	
}

void THandler2::setOptionList(const map<string, string>* OptionList)
{
   m_pOption = OptionList;
}

int THandler2::invoke(void *pvIMsg)
{
	IMessageData *pIMsg = (IMessageData*) pvIMsg;

	if(pIMsg->isPastPivot()) {
		/*this is a response*/

		
		
	} else {
		/*this is a request*/
		char api[25];
		
		IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

		IHeaderBlock* pIHeaderBlock = pISZ->getHeaderBlock("basicNodeTest", "http://soapinterop.org/basicNodeTest/");

		int num_kids = pIHeaderBlock->getNoOfChildren();
		cout << "Number of children in header block = " << num_kids << endl;

		BasicNode* pBasicNode = pIHeaderBlock->getFirstChild();
		if(pBasicNode) {

			num_kids = pBasicNode->getNoOfChildren();
			cout << "Number of children in node = " << num_kids << endl;

			/* Get the first attribute of the complex node */
			IAttribute* pIAttribute = pBasicNode->getFirstAttribute();
			if(pIAttribute) {
				strcpy(api, "getFirstAttribute() ");

				/* loop through all the attribute of the complex node */
				do {
					cout << api << pIAttribute->getLocalName() << "=" << pIAttribute->getValue() << endl;
					strcpy(api, "getNextAttribute() ");
				} while( ( pIAttribute = pBasicNode->getNextAttribute() ) );

				/* get a specific attribute */
				pIAttribute = pBasicNode->getAttribute(NULL, NULL, "attr3");
				if(pIAttribute)
					cout << "getAttribute() " << pIAttribute->getLocalName() << "=" << pIAttribute->getValue() << endl;
				else cout << "could not getAttribute(NULL, NULL, \"attr1\")" << endl;

				/* get the last attribute */
				pIAttribute = pBasicNode->getLastAttribute();
				if(pIAttribute)
					cout << "getLastAttribute() " << pIAttribute->getLocalName() << "=" << pIAttribute->getValue() << endl;
				else cout << "could not getLastAttribute" << endl;

				pIAttribute = pBasicNode->getFirstAttribute();
				if(pIAttribute)
					cout << "getFirstAttribute() " << pIAttribute->getLocalName() << "=" << pIAttribute->getValue() << endl;
				else cout << "could not getFirstAttribute" << endl;

				/* get the current node. should be the last one */
				pIAttribute = pBasicNode->getCurrentAttribute();
				if(pIAttribute)
					cout << "getCurrentAttribute() " << pIAttribute->getLocalName() << "=" << pIAttribute->getValue() << endl;
				else cout << "could not getCurrentAttribute" << endl;


			} else {
				cout << "cannot find first attribute" << endl;
			}

			BasicNode* pChildNode = pBasicNode->getFirstChild();
			cout << "BasicNode first child type = " << pChildNode->getNodeType() << endl;
			BasicNode* pGrandChildNode = pChildNode->getFirstChild();
			cout << "BasicNode child of child type = " << pGrandChildNode->getNodeType() << endl;
			cout << "BasicNode child of child value = " << pGrandChildNode->getValue() << endl;

			pChildNode = pBasicNode->getLastChild();
			cout << "BasicNode last child type = " << pChildNode->getNodeType() << endl;
			pGrandChildNode = pChildNode->getFirstChild();
			cout << "BasicNode child of child type = " << pGrandChildNode->getNodeType() << endl;
			cout << "BasicNode child of child value = " << pGrandChildNode->getValue() << endl;

			pChildNode = pBasicNode->getChild(1);
			cout << "BasicNode child(1) child type = " << pChildNode->getNodeType() << endl;
			pGrandChildNode = pChildNode->getFirstChild();
			cout << "BasicNode child of child type = " << pGrandChildNode->getNodeType() << endl;
			cout << "BasicNode child of child value = " << pGrandChildNode->getValue() << endl;

		} else {
			cout << "Cannot find Basic Node" << endl;
		}

	}

	return AXIS_SUCCESS;
}

void THandler2::onFault(void *pvIMsg)
{

}

int THandler2::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int THandler2::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
