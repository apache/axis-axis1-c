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
 * Add a SOAP header element in each handler in a handler chain.
 *
 * Test success is measured by comparing the actual request with an expected
 * resquest.
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
		
		IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();

		pIHeaderBlock->setLocalName("echoMeString2");
		pIHeaderBlock->setURI("http://soapinterop.org/echoheader/");

		const AxisChar* pachHeaderVal = "Header Value2";

		BasicNode* pBasicNode = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode->setValue(pachHeaderVal);
		
		pIHeaderBlock->addChild(pBasicNode);
		
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
