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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *
 */

// SoapSerializer.cpp: implementation of the SoapSerializer class.
//
//////////////////////////////////////////////////////////////////////

#include "SoapEnvelope.h"
#include "SoapSerializer.h"
#include "../common/GDefine.h"
#include "../common/Packet.h"
#include "../common/ArrayBean.h"
#include "../common/BasicTypeSerializer.h"

extern "C" int sendSoapResponse(char *cSerializedStream);

int SoapSerializer::iCounter=0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapSerializer::SoapSerializer()
{
	m_pSoapEnvelope= NULL;
}

SoapSerializer::~SoapSerializer()
{
	if (m_pSoapEnvelope) delete m_pSoapEnvelope;
}

int SoapSerializer::setSoapEnvelope(SoapEnvelope *pSoapEnvelope)
{
	m_pSoapEnvelope= pSoapEnvelope;

	return SUCCESS;
}

int SoapSerializer::setSoapHeader(SoapHeader *pSoapHeader)
{
	int intStatus= FAIL;

	if(m_pSoapEnvelope) {
		m_pSoapEnvelope->setSoapHeader(pSoapHeader);
		intStatus= SUCCESS;
	}

	return intStatus;
}

int SoapSerializer::setSoapBody(SoapBody *pSoapBody)
{
	int intStatus= FAIL;

	if(m_pSoapEnvelope) {
		m_pSoapEnvelope->setSoapBody(pSoapBody);
		intStatus= SUCCESS;
	}

	return intStatus;
}

int SoapSerializer::setSoapMethod(SoapMethod *pSoapMethod)
{
	int intStatus= FAIL;

	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody)) {
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod= pSoapMethod;
		intStatus= SUCCESS;
	}

	return intStatus;
}

IParam* SoapSerializer::setResponseParam(XSDTYPE nType, uParamValue Value)
{
	Param* pParam = new Param();
	pParam->SetValue(nType, Value);

	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
	{
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->setOutputParam(pParam);
	}

	return pParam;
}

int SoapSerializer::setSoapFault(SoapFault *pSoapFault)
{
	int intStatus= FAIL;

	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody)) {
		m_pSoapEnvelope->m_pSoapBody->m_pSoapFault= pSoapFault;
		intStatus= SUCCESS;
	}

	return intStatus;
}

/*string& SoapSerializer::getStream()
{
	m_sSerializedStream= "";

	if(m_pSoapEnvelope) {
		m_sSerializedStream= m_pSoapEnvelope->serialize();
	}

	return m_sSerializedStream;
}*/

int SoapSerializer::getStream()
{
	int iStatus= SUCCESS;

	if(m_pSoapEnvelope) {
		iStatus= m_pSoapEnvelope->serialize(*this, (SOAP_VERSION)m_iSoapVersion);
		//cout<<endl<<"after getStream"<<endl;
		//SoapSerializer tmp_sz;
		//iStatus= m_pSoapEnvelope->serialize(sSerialized, tmp_sz, (SOAP_VERSION)m_iSoapVersion);
		//does this need to be handled here or at the top level. Discuss this.
		//if(iStatus==FAIL) {
		//	sSerialized="";
		//}
	}
	//flushSerializedBuffer();
	return iStatus;
}

void SoapSerializer::init()
{
	//initializing the members of the class. This is needed since
	// the same object instance of this class, may be used to server
	// several SOAP requests.

	if(m_pSoapEnvelope) {
		delete m_pSoapEnvelope;
		m_pSoapEnvelope= NULL;
	}

	iCounter=0;
	m_iCurrentSerBufferSize=0;
	m_cSerializedBuffer[0]='\0'; //make buffer to empty content (as a char*)
}

int SoapSerializer::setSoapVersion(SOAP_VERSION eSOAP_VERSION)
{
	m_iSoapVersion= eSOAP_VERSION;
	return SUCCESS;
}

const char* SoapSerializer::getNewNamespacePrefix()
{
	iCounter++;
	sprintf(cCounter, "ns%d", iCounter);
	return cCounter;
}

ISoapSerializer& SoapSerializer::operator <<(const char *cSerialized)
{
	int iTmpSerBufferSize= strlen(cSerialized);
	if((m_iCurrentSerBufferSize+iTmpSerBufferSize)>1023) {
		flushSerializedBuffer();		
	}
	strcat(m_cSerializedBuffer, cSerialized);
	//cout<<m_cSerializedBuffer<<"END@@";

	m_iCurrentSerBufferSize+= iTmpSerBufferSize;

	return *this;
	//call the ruputs to send this soap response
	//ruputs(m_cSerializedBuffer);
}

int SoapSerializer::flushSerializedBuffer()
{
	//cout<<"++++++++++++++++"<<"flushed"<<endl;
	//cout<<"++++++++++++++++"<<m_cSerializedBuffer<<endl;
	//sendSoapResponse(m_cSerializedBuffer);
	send_response_bytes(m_cSerializedBuffer);
	m_cSerializedBuffer[0]= '\0';
	m_iCurrentSerBufferSize=0;

	return SUCCESS;
}

ISoapMethod* SoapSerializer::createSoapMethod()
{
	SoapMethod* pMethod = new SoapMethod();
	setSoapMethod(pMethod);
	return pMethod;
}

IArrayBean* SoapSerializer::makeArrayBean(XSDTYPE nType, void* pArray)
{
	ArrayBean* pAb = new ArrayBean();
	pAb->m_type = nType;
	pAb->m_value.sta = pArray;
	return pAb;
}

string& SoapSerializer::SerializeBasicType(const string& sName, string& sValue, XSDTYPE type)
{
	return BasicTypeSerializer::serialize(sName, sValue, type);
}

string& SoapSerializer::SerializeBasicType(const string& sName, float fValue)
{
	return BasicTypeSerializer::serialize(sName, fValue);	
}

string& SoapSerializer::SerializeBasicType(const string& sName, int nValue)
{
	return BasicTypeSerializer::serialize(sName, nValue);		
}
