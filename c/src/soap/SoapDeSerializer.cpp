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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

// SoapDeSerializer.cpp: implementation of the SoapDeSerializer class.
//
//////////////////////////////////////////////////////////////////////
#include "SoapEnvelope.h"
#include "SoapHeader.h"
#include "SoapMethod.h"
#include "SoapBody.h"
#include "SoapFault.h"
#include "SoapDeSerializer.h"
#include "../common/GDefine.h"
#include "../common/Packet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapDeSerializer::SoapDeSerializer()
{
	m_pHandler = new XMLStreamHandler();
	m_pParser = XMLReaderFactory::createXMLReader();
    m_pParser->setContentHandler(m_pHandler);
    m_pParser->setErrorHandler(m_pHandler);
	m_pInputStream = NULL;
}

SoapDeSerializer::~SoapDeSerializer()
{
	delete m_pHandler;
	delete m_pParser;
}

int SoapDeSerializer::SetInputStream(void* InputStream)
{
	m_pInputStream = InputStream;
	MemBufInputSource* pSoapInput = NULL;
	//---------------------start--------------------------
	//Deserialize
	//---------START XERCES SAX2 SPCIFIC CODE---------//
	//a huge buffer to store the whole soap request stream
	//to store the number of chars returned by get_request_bytes
	int nChars = 0;
	//request a huge number of bytes to get the whole soap request
	//when pull parsing is used this should change
	get_request_bytes(m_hugebuffer, HUGE_BUFFER_SIZE, &nChars, m_pInputStream);
	//if no soap then quit
	if (nChars <= 0) return FAIL;
	pSoapInput = new MemBufInputSource((const unsigned char*)m_hugebuffer, nChars ,"bufferid",false);
	m_pParser->parse(*pSoapInput);
	return SUCCESS;
}

SoapEnvelope* SoapDeSerializer::GetEnvelope()
{
	return m_pHandler->m_pEnv;
}

ISoapHeader* SoapDeSerializer::GetHeader()
{
	//actually here a dynamic cast is not needed. But it is
	// done for safe side, incase SoapHeader derives from 
	// more that one interface and the deriving order changes.
	return static_cast<ISoapHeader*>(m_pHandler->m_pHead);
}

SoapBody* SoapDeSerializer::GetBody()
{
	return m_pHandler->m_pBody;
}

SoapMethod* SoapDeSerializer::GetMethod()
{
	return m_pHandler->m_pMethod;
}

SoapFault* SoapDeSerializer::GetFault()
{
	return m_pHandler->m_pFault;
}

//this function is more usefull with XMLpull parser
int SoapDeSerializer::Deserialize(IParam* pIParam, int bHref)
{
	Param* pParam = (Param*)pIParam;
	//if multiref add to m_Multirefs map
	//else call its deserializer
	switch (pParam->m_Type)
	{
	case XSD_ARRAY:
		if (pParam->m_Value.pArray && pParam->m_Value.pArray->m_value.sta)
		{
			pParam->m_Value.pArray->DeSerialize(this);
		}
		else
			return FAIL;
		break;
	case USER_TYPE:
		if (pParam->m_Value.pBean)
		{
			pParam->m_Value.pBean->DeSerialize(this);
		}
		else
			return FAIL;
		break;
	default:; //no need of calling this function for basic types - error condition
	}
	return SUCCESS;
}

IParam* SoapDeSerializer::GetParam()
{
	return m_pHandler->GetParam();
}

int SoapDeSerializer::Init()
{
	m_hugebuffer[0] = '\0';
	m_pHandler->Init();
	return SUCCESS;
}

string& SoapDeSerializer::GetMethodName()
{
	if (m_pHandler->m_pMethod)
	{
		return m_pHandler->m_pMethod->getMethodName();
	}
}

int SoapDeSerializer::GetVersion()
{
	return m_pHandler->m_nSoapVersion;	
}
