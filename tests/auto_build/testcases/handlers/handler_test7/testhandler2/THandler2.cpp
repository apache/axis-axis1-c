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
 * @author Andrew Perry (perryan@uk.ibm.com)
 *
 *****************************************************************************
 * Test Logic.
 * Set a property in the request of the second handler in a chain and get the
 * property in the response in the first handler in a chain and make sure they
 * are the same.
 *
 * Test success is measured by comparing the actual response with an expected
 * response. So on failure just write anything to stdout and the test will 
 * fail.
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
	AxisChar* name="tp2";
	AxisChar* value="value2";

	if(pIMsg->isPastPivot()) {
		/*this is a response*/
	} else {
		/*this is a request*/
		pIMsg->setProperty(name, value);
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
