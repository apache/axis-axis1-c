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
 * Create a SOAP Header block with the localname and URI specified in the 
 * constructor.
 *
 * Test success is measured by comparing the actual request with an expected
 * request.
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

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock("chbTest", "http://soapinterop.org/echoheader/");

		const AxisChar* pachHeaderVal = "createHeaderBlock with localName and URI";
		BasicNode* pBasicNode = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode->setValue(pachHeaderVal);
		pIHeaderBlock->addChild(pBasicNode);
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
