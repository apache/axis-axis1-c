/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

// ESHHandler.cpp: implementation of the ESHHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "ESHHandler.h"
#include <axis/server/GDefine.h>
#include <axis/server/IHandlerSoapSerializer.h>
#include <axis/server/IHandlerSoapDeSerializer.h>
#include <axis/server/HeaderBlock.h>
#include <axis/server/SoapHeader.h>
#include <axis/server/BasicNode.h>
#include <axis/server/AxisTrace.h>
#include <iostream>

#include <axis/server/CharacterElement.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ESHHandler::ESHHandler()
{
    m_pOption = NULL;
    m_sEmpty = "";

}

ESHHandler::~ESHHandler()
{

}

const string& ESHHandler::GetOption(const string& sArg)
{
  map<string, string>::const_iterator it = m_pOption->find(sArg);
  if (it != m_pOption->end())
  {
      return (*it).second;
  }
  return m_sEmpty;	
}

void ESHHandler::SetOptionList(const map<string, string>* OptionList)
{
   m_pOption = OptionList;
}

int ESHHandler::Invoke(void *pvIMsg)
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
        
		const AxisChar* pachHeaderVal = pIMsg->getProperty(pachTemp);
		printf("in the ESHHandler::Invoke : %s\n",pachHeaderVal);

		BasicNode* pBasicNode = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode->setValue(pachHeaderVal);
		
		pIHeaderBlock->addChild(pBasicNode);
		
	} else {
		/*this is a request*/
		
		IHandlerSoapDeSerializer* pIHandlerSoapDeSerializer;
		pIMsg->getSoapDeSerializer(&pIHandlerSoapDeSerializer);

		IHeaderBlock* pIHeaderBlock= pIHandlerSoapDeSerializer->GetHeaderBlock("reservation", "http://travelcompany.example.org/reservation");
		
		if (pIHeaderBlock != NULL) {

			const BasicNode* pBasicNode= pIHeaderBlock->getFirstChild();
			const BasicNode* pBasicNode2= pBasicNode->getFirstChild();
						
			const AxisChar* pachHeaderValue;
			const AxisChar* pachHeaderValue2;
			if((pBasicNode2->getNodeType()) == CHARACTER_NODE) {
				pachHeaderValue= pBasicNode2->getValue();
			} else {
				pachHeaderValue = "This was not the expected value Ros";
			}

			const BasicNode* pBasicNode3= pIHeaderBlock->getLastChild();
			const BasicNode* pBasicNode4 =pBasicNode3->getFirstChild();
			if((pBasicNode4->getNodeType()) == CHARACTER_NODE) {
				pachHeaderValue2= pBasicNode4->getValue();
			} else {
				pachHeaderValue2= "This was not the expected value2 Ros";
			}

			AxisChar* pachTmpValue = (AxisChar*) malloc(strlen(pachHeaderValue)+ strlen(pachHeaderValue2) +4);
			strcpy(pachTmpValue, pachHeaderValue);
			strcat(pachTmpValue, " : ");
			strcat(pachTmpValue, pachHeaderValue2);

			pachTemp = "EchoStringHeaderHandlerPr1.id";
			pIMsg->setProperty(pachTemp, pachTmpValue);

			free(pachTmpValue);
			
			
		} else {
			//do some thing
		}
		
	}

	return AXIS_SUCCESS;
}

void ESHHandler::OnFault(void *pvIMsg)
{

}

int ESHHandler::Init()
{
	//do any initialization, resetting of values

	return AXIS_SUCCESS;
}

int ESHHandler::Fini()
{
	//do any finalizatoin

	return AXIS_SUCCESS;
}
