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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

/*
 * Revision 1.1  2004/06/14 roshan
 * Removed the implementations of getOption(const string& sArg) and 
 *  setOptionList(const map<string, string>* OptionList), because these methods
 *  are not needed to be implemented by the users. These are generic methods.
 *  Added the implementations of these methods to the Handler base class.
 */

#include "ESHHandler.h"
#include <axis/server/GDefine.hpp>
#include <axis/server/IHandlerSoapSerializer.hpp>
#include <axis/server/IHandlerSoapDeSerializer.hpp>
#include <axis/server/BasicNode.hpp>
#include <iostream>



ESHHandler::ESHHandler()
{
}

ESHHandler::~ESHHandler()
{
}

int ESHHandler::invoke(void *pvIMsg)
{
	IMessageData *pIMsg = (IMessageData*) pvIMsg;
    AxisChar* pachTemp;
	if(pIMsg->isPastPivot()) {
		/*this is a response*/

		IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();

		pIHeaderBlock->setLocalName("echoMeStringResponse");
		pIHeaderBlock->setUri("http://soapinterop.org/echoheader/");

	        pachTemp = "EchoStringHeaderHandlerPr1.id";
        
		const AxisChar* pachHeaderVal = (AxisChar*)pIMsg->getProperty(pachTemp);
		printf("in the ESHHandler::Invoke : %s\n",pachHeaderVal);

		BasicNode* pBasicNode = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode->setValue(pachHeaderVal);
		
		pIHeaderBlock->addChild(pBasicNode);
		
	} else {
		/*this is a request*/
		
		IHandlerSoapDeSerializer* pIHandlerSoapDeSerializer;
		pIMsg->getSoapDeSerializer(&pIHandlerSoapDeSerializer);

		IHeaderBlock* pIHeaderBlock= pIHandlerSoapDeSerializer->getHeaderBlock("echoMeString", "http://soapinterop.org/echoheader/");
		
		if (pIHeaderBlock != NULL) {

			const BasicNode* pBasicNode= pIHeaderBlock->getFirstChild();
						
			const AxisChar* pachHeaderValue;

			if (pBasicNode != NULL) 
			{
				if((pBasicNode->getNodeType()) == CHARACTER_NODE) {
					pachHeaderValue= pBasicNode->getValue();
				} else {
					pachHeaderValue = "This was not the expected value Ros";
				}
			} else 
			{
				pachHeaderValue = "pBascNode is NULL";
			}

			AxisChar* pachTmpValue = (AxisChar*) malloc(strlen(pachHeaderValue) + 4);
			strcpy(pachTmpValue, pachHeaderValue);

			pachTemp = "EchoStringHeaderHandlerPr1.id";
			pIMsg->setProperty(pachTemp, pachTmpValue);

			free(pachTmpValue);
			
			
		} else {
			//do some thing
			//AxisChar* pachTmpValue = "Default values since no reqeust SOAP header";
			//pachTemp = "EchoStringHeaderHandlerPr1.id";
                        //pIMsg->setProperty(pachTemp, pachTmpValue);
                                                                                
                        //free(pachTmpValue);
		}
		
	}

	return AXIS_SUCCESS;
}

void ESHHandler::onFault(void *pvIMsg)
{

}

int ESHHandler::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int ESHHandler::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
