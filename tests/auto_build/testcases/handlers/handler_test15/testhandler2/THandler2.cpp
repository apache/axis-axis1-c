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
 * @author Andrew Perry (perryan@uk.ibm.com)
 *
 *****************************************************************************
 * Test Logic.
 * Set a property in the request flow and get it in the response flow and 
 * make sure they are the same.
 *
 * Test success is measured by comparing the actual response with an expected
 * response. So on failure just write anything to stdout and the test will 
 * fail.
 *****************************************************************************
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
		IHandlerSoapSerializer* pISZ;

		// Get the IHandlerSoapSerializer from IMessageData
		pIMsg->getSoapSerializer(&pISZ);

		IHeaderBlock* pIHeaderBlock = pISZ->getFirstHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getFirstHeaderBlock()");

		pIHeaderBlock = pISZ->getNextHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getNextHeaderBlock()");

		pIHeaderBlock = pISZ->getNextHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getNextHeaderBlock()");

		pIHeaderBlock = pISZ->getNextHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getNextHeaderBlock()");

		pIHeaderBlock = pISZ->getHeaderBlock("hb2", "http://soapinterop.org/axis2/");
		printHeaderBlock(pIHeaderBlock, "getHeaderBlock(\"hb2\", namespace)");

		pIHeaderBlock = pISZ->getCurrentHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getCurrentHeaderBlock()");

		pIHeaderBlock = pISZ->getHeaderBlock("hb3", "http://soapinterop.org/axis3/");
		printHeaderBlock(pIHeaderBlock, "getHeaderBlock(\"hb3\", namespace)");

		pIHeaderBlock = pISZ->getHeaderBlock("hb1", "http://soapinterop.org/axis/");
		printHeaderBlock(pIHeaderBlock, "getHeaderBlock(\"hb1\", namespace)");

		pIHeaderBlock = pISZ->getFirstHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getFirstHeaderBlock()");

		pIHeaderBlock = pISZ->getCurrentHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getCurrentHeaderBlock()");

		pIHeaderBlock = pISZ->getNextHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getNextHeaderBlock()");

		pIHeaderBlock = pISZ->getCurrentHeaderBlock();
		printHeaderBlock(pIHeaderBlock, "getCurrentHeaderBlock()");

	}

	return AXIS_SUCCESS;
}

void THandler2::printHeaderBlock(IHeaderBlock* pHb, const char* text) {
	printf("%-32s - ", text);
	if(pHb) {
		int num_children = pHb->getNoOfChildren();
		for(int cnt=1; cnt<=num_children; cnt++) {
			BasicNode* pBn = pHb->getChild(cnt);
			if(pBn) {
				printf("%s:child(%d) - Value = %s\n", pHb->getLocalName(), cnt, pBn->getValue());
				fflush(stdout);
			}
		}
	} else {
		printf("HeaderBlock is NULL\n");
	}
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
