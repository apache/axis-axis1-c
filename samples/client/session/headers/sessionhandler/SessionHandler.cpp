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
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 *
 */

#include "SessionHandler.hpp"
#include <axis/GDefine.hpp>
#include <axis/IHandlerSoapSerializer.hpp>
#include <axis/IHandlerSoapDeSerializer.hpp>
#include <axis/BasicNode.hpp>
#include <iostream>

SessionHandler::SessionHandler()
{
    m_pOption = NULL;
    m_sEmpty = "";
}

SessionHandler::~SessionHandler()
{

}

const string& SessionHandler::getOption(const string& sArg)
{
  map<string, string>::const_iterator it = m_pOption->find(sArg);
  if (it != m_pOption->end())
  {
      return (*it).second;
  }
  return m_sEmpty;	
}

void SessionHandler::setOptionList(const map<string, string>* OptionList)
{
   m_pOption = OptionList;
}

int SessionHandler::invoke(void *pvIMsg)
{
    IMessageData *pIMsg = (IMessageData*) pvIMsg;
    AxisChar * sessionid = NULL;
    const AxisChar * pachSessionHeaderLocalName = "sessionID";

	if(pIMsg->isPastPivot()) {
		/* Called on the client response path */

		IHandlerSoapDeSerializer* pIHandlerSoapDeSerializer;
		pIMsg->getSoapDeSerializer(&pIHandlerSoapDeSerializer);

		IHeaderBlock* pIHeaderBlock = pIHandlerSoapDeSerializer->
                                        getHeaderBlock("sessionID", 
                                        "http://xml.apache.org/axis/session");
		
		if (pIHeaderBlock != NULL)
        {

            if(strcmp(pachSessionHeaderLocalName,pIHeaderBlock->getLocalName())==0)
            {
                const BasicNode* pBasicNode= pIHeaderBlock->getFirstChild();
                if(CHARACTER_NODE == pBasicNode->getNodeType())
                {
                    pIMsg->setProperty("sessionid",pBasicNode->getValue());
                }
            }
 
        }
		
	} 
    else 
    {
		/* Called on the client request path */
        sessionid = (AxisChar *)pIMsg->getProperty("sessionid");
        if(strcmp("", sessionid)!=0)
        {
            IHandlerSoapSerializer* pISZ;
		    pIMsg->getSoapSerializer(&pISZ);

		    IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();


		    pIHeaderBlock->setLocalName("sessionID");
            pIHeaderBlock->setUri("http://xml.apache.org/axis/session");
            pIHeaderBlock->createStdAttribute(MUST_UNDERSTAND_FALSE, 
                                                SOAP_VER_1_1);
            pIHeaderBlock->createStdAttribute(ACTOR, SOAP_VER_1_1);
            pIHeaderBlock->createAttribute("type", "xsi", "soapenc:long");
            pIHeaderBlock->createNamespaceDecl("soapenc", 
                                "http://schemas.xmlsoap.org/soap/encoding/");
       	    const AxisChar* pachHeaderVal = sessionid;

		    BasicNode* pBasicNode = pIHeaderBlock->createChild(CHARACTER_NODE);
		    pBasicNode->setValue(pachHeaderVal);
		    
		    pIHeaderBlock->addChild(pBasicNode);
        }
		
	}

	return AXIS_SUCCESS;
}

void SessionHandler::onFault(void *pvIMsg)
{

}

int SessionHandler::init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int SessionHandler::fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
