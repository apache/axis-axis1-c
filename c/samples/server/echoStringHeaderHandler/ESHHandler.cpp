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
#include <axis/common/GDefine.h>
#include <axis/common/IHandlerSoapSerializer.h>
#include <axis/common/IHandlerSoapDeSerializer.h>
#include <axis/soap/HeaderBlock.h>
#include <axis/soap/SoapHeader.h>
#include <axis/soap/BasicNode.h>
#include <iostream>

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

int ESHHandler::Invoke(IMessageData *pIMsg)
{
    string strTemp;
    AxisChar* sHeaderVal;
	if(pIMsg->isPastPivot()) {
		//this is a response
		IHandlerSoapSerializer* pISZ;
		pIMsg->getSoapSerializer(&pISZ);

		IHeaderBlock* pIHeaderBlock= pISZ->createHeaderBlock();

		pIHeaderBlock->setLocalName("echoMeStringResponse");
		pIHeaderBlock->setUri("http://soapinterop.org/echoheader/");
		pIHeaderBlock->setPrefix("m");

        strTemp = "EchoStringHeaderHandlerPr1.id";
        size_t nSize = strlen(pIMsg->getProperty(strTemp).c_str()) + 30;
        sHeaderVal = (char*) malloc(nSize);
		strcpy(sHeaderVal, pIMsg->getProperty(strTemp).c_str());
        realloc(sHeaderVal, 30);
		strcpy(sHeaderVal," After Append by Handler");
		pIHeaderBlock->setValue(sHeaderVal);

		BasicNode* pBasicNode = pIHeaderBlock->createChild(CHARACTER_NODE);
		pBasicNode->setValue(sHeaderVal);
		pIHeaderBlock->addChild(pBasicNode);

		cout<<"in the header invoke"<<endl;
		
	} else {
		//this is a request
		IHandlerSoapDeSerializer* pIHandlerSoapDeSerializer;
		pIMsg->getSoapDeSerializer(&pIHandlerSoapDeSerializer);

		ISoapHeader* pISoapHeader= pIHandlerSoapDeSerializer->GetHeader();
		IHeaderBlock* pIHeaderBlock= pISoapHeader->getHeaderBlock();
		BasicNode* pBasicNode= pIHeaderBlock->getFirstChild();
		
		string sHeaderValue;
		if((pBasicNode->getNodeType()) == CHARACTER_NODE) {
			sHeaderValue= pBasicNode->getValue();
		}

        strTemp = "EchoStringHeaderHandlerPr1.id";
		pIMsg->setProperty(strTemp, sHeaderValue);
		//pIMsg->setProperty(string("EchoSt"), sHeaderValue);
		
	}

	return AXIS_SUCCESS;
}

void ESHHandler::OnFault(IMessageData *pIMsg)
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
