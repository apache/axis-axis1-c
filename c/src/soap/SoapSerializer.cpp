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
#include "HeaderBlock.h"
#include "../common/GDefine.h"
#include "../common/Packet.h"
#include "../common/ArrayBean.h"
#include "../common/BasicTypeSerializer.h"

extern "C" int sendSoapResponse(char *cSerializedStream);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapSerializer::SoapSerializer()
{
	m_pSoapEnvelope = NULL;
	m_iSoapVersion = SOAP_VER_1_1;
	m_pOutputStream = NULL;
}

SoapSerializer::~SoapSerializer()
{
	if (m_pSoapEnvelope) delete m_pSoapEnvelope;
}

int SoapSerializer::setSoapEnvelope(SoapEnvelope *pSoapEnvelope)
{
	m_pSoapEnvelope = pSoapEnvelope;

	return SUCCESS;
}

int SoapSerializer::setSoapHeader(SoapHeader *pSoapHeader)
{
	int intStatus = FAIL;

	if(m_pSoapEnvelope) {

		if((m_pSoapEnvelope)&& (m_pSoapEnvelope->m_pSoapHeader)) {
			//no need to create a SOAP Header, it already exists
			intStatus= OBJECT_ALREADY_EXISTS;
		} else {
			m_pSoapEnvelope->setSoapHeader(pSoapHeader);
			intStatus= SUCCESS;
		}
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

int SoapSerializer::SetOutputStream(void* pStream)
{
	m_pOutputStream = pStream;
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

int SoapSerializer::Init()
{
	//initializing the members of the class. This is needed since
	// the same object instance of this class, may be used to server
	// several SOAP requests.

	if(m_pSoapEnvelope) {
		delete m_pSoapEnvelope;
		m_pSoapEnvelope= NULL;
	}

	//Adding SoapEnvelop and SoapBody to Serializer
	m_pSoapEnvelope = new SoapEnvelope();
	m_pSoapEnvelope->setSoapBody(new SoapBody());

	iCounter=0;
	m_iCurrentSerBufferSize=0;
	m_cSerializedBuffer[0]='\0'; //make buffer to empty content (as a char*)
	return SUCCESS;
}

int SoapSerializer::setSoapVersion(SOAP_VERSION nSoapVersion)
{
	//here the default namespaces of the SoapEnvelop should be added and intialized as well.
/*
	Attribute* pNS = new Attribute(g_sObjSoapEnvVersionsStruct[nSoapVersion].pchEnvelopePrefix,
	  "xmlns","",g_sObjSoapEnvVersionsStruct[nSoapVersion].pchEnvelopeNamespaceUri);
	m_pSoapEnvelope->addNamespaceDecl(pNS);
	//add namespace URIs for xsd and xsi
	pNS = new Attribute("xsd","xmlns","","http://www.w3.org/2001/XMLSchema");
	m_pSoapEnvelope->addNamespaceDecl(pNS);
	pNS = new Attribute("xsi","xmlns","","http://www.w3.org/2001/XMLSchema-instance");
	m_pSoapEnvelope->addNamespaceDecl(pNS);
*/
	m_pSoapEnvelope->addStandardNamespaceDecl(g_sObjSoapEnvVersionsStruct[nSoapVersion].pEnv);
	m_pSoapEnvelope->addStandardNamespaceDecl(g_sObjSoapEnvVersionsStruct[nSoapVersion].pXsd);
	m_pSoapEnvelope->addStandardNamespaceDecl(g_sObjSoapEnvVersionsStruct[nSoapVersion].pXsi);
	return SUCCESS;
}

const char* SoapSerializer::getNewNamespacePrefix()
{
	iCounter++;
	sprintf(cCounter, "ns%d", iCounter);
	return cCounter;
}

IWrapperSoapSerializer& SoapSerializer::operator <<(const char *cSerialized)
{
	int iTmpSerBufferSize = strlen(cSerialized);
	if((m_iCurrentSerBufferSize + iTmpSerBufferSize)>= SERIALIZE_BUFFER_SIZE) 
	{
		flushSerializedBuffer();		
	}
	strcat(m_cSerializedBuffer, cSerialized);
	m_iCurrentSerBufferSize += iTmpSerBufferSize;
	return *this;
	//call the ruputs to send this soap response
	//ruputs(m_cSerializedBuffer);
}

int SoapSerializer::flushSerializedBuffer()
{
	//sendSoapResponse(m_cSerializedBuffer);
	send_response_bytes(m_cSerializedBuffer, m_pOutputStream);
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
	return m_BTSZ.serialize(sName, sValue, type);
}

string& SoapSerializer::SerializeBasicType(const string& sName, float fValue)
{
	return m_BTSZ.serialize(sName, fValue);	
}

string& SoapSerializer::SerializeBasicType(const string& sName, int nValue)
{
	return m_BTSZ.serialize(sName, nValue);		
}

IHeaderBlock* SoapSerializer::createHeaderBlock()
{
	HeaderBlock* pHeaderBlock= new HeaderBlock();
	setHeaderBlock(pHeaderBlock);
	return pHeaderBlock;
}

int SoapSerializer::setHeaderBlock(HeaderBlock *pHeaderBlock)
{
	int intStatus= FAIL;

	if((m_pSoapEnvelope)&& (m_pSoapEnvelope->m_pSoapHeader)) {
		//no need to create a SOAP Header, it already exists
	} else {
		SoapHeader* pSoapHeader= new SoapHeader();
		setSoapHeader(pSoapHeader);
	}

	m_pSoapEnvelope->m_pSoapHeader->addHeaderBlock(pHeaderBlock);
	intStatus= SUCCESS;

	return intStatus;
}

/*
 *This method not only removes the existing SoapHeader, but also removes
 * all the existing HeaderBlocks which are associated with this SoapHeader.
 * Therefore the caller of this method has to be exactly sure whether he wants to
 * do this.
 */
int SoapSerializer::removeSoapHeader()
{
	delete m_pSoapEnvelope->m_pSoapHeader;
	m_pSoapEnvelope->m_pSoapHeader= NULL;

	return SUCCESS;
}
