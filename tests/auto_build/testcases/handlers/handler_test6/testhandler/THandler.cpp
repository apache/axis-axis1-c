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
 * Set a property in the request of the first handler in a chain and get the
 * property in the second handler in a chain and make sure they are the same.
 *
 * Test success is measured by comparing the actual response with an expected
 * response. So on failure just write anything to stdout and the test will 
 * fail.
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
	AxisChar* name="tp1";
	AxisChar* req_value="Set property in handler";

	if(pIMsg->isPastPivot()) {
		/*this is a response*/
	} else {
		/*this is a request*/
		pIMsg->setProperty(name, req_value);
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
