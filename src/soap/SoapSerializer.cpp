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
#include "SoapKeywordMapping.h"
#include <stdio.h>

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

IParam* SoapSerializer::AddOutputParam(XSDTYPE nType, uParamValue Value)
{
	Param* pParam = new Param();
	pParam->SetValue(nType, Value);
	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
	{
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->AddOutputParam(pParam);
	}
	return pParam;
}

IParam* SoapSerializer::AddOutputParam(IArrayBean* pArrayBean)
{
	Param* pParam = new Param();
	pParam->m_Value.pIArray = pArrayBean;
	pParam->m_Type = XSD_ARRAY;
	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
	{
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->AddOutputParam(pParam);
	}
	return pParam;
}

IParam* SoapSerializer::AddOutputParam(void* pObject, void* pSZFunct, void* pDelFunct)
{ 
	Param* pParam = new Param();
	pParam->m_Value.pCplxObj = new ComplexObjectHandler;
	pParam->m_Value.pCplxObj->pObject = pObject;
	pParam->m_Value.pCplxObj->pSZFunct = (AXIS_SERIALIZE_FUNCT)pSZFunct;
	pParam->m_Value.pCplxObj->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
	{
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->AddOutputParam(pParam);
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

int SoapSerializer::SetOutputStream(const void* pStream)
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
	m_pSoapEnvelope->addStandardNamespaceDecl(SoapKeywordMapping::Map(nSoapVersion).pEnv);
	m_pSoapEnvelope->addStandardNamespaceDecl(SoapKeywordMapping::Map(nSoapVersion).pXsd);
	m_pSoapEnvelope->addStandardNamespaceDecl(SoapKeywordMapping::Map(nSoapVersion).pXsi);
	return SUCCESS;
}

const AxisChar* SoapSerializer::getNewNamespacePrefix()
{
	iCounter++;
    AxisSprintf(cCounter, 64, "ns%d", iCounter);
	return cCounter;
}

IWrapperSoapSerializer& SoapSerializer::operator <<(const AxisChar* cSerialized)
{
	int iTmpSerBufferSize = strlen(cSerialized);
	if((m_iCurrentSerBufferSize + iTmpSerBufferSize)>= SERIALIZE_BUFFER_SIZE) 
	{
		flushSerializedBuffer();		
	}
	strcat(m_cSerializedBuffer, cSerialized);
	m_iCurrentSerBufferSize += iTmpSerBufferSize;
	return *this;
}
/*
IWrapperSoapSerializer& SoapSerializer::operator<<(const AxisChar* cSerialized)
{
	flushSerializedBuffer();
	//following is done for the time being
	int slen = wcslen(cSerialized);
	for (m_iCurrentSerBufferSize=0; m_iCurrentSerBufferSize < slen; m_iCurrentSerBufferSize++)
	{
		m_cSerializedBuffer[m_iCurrentSerBufferSize] = (char) cSerialized[m_iCurrentSerBufferSize];
	}
	m_cSerializedBuffer[m_iCurrentSerBufferSize] = '\0';
	return *this;
}
*/
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

IArrayBean* SoapSerializer::makeArrayBean(void* pObject, void* pSZFunct, void* pDelFunct, void* pSizeFunct)
{
	ArrayBean* pAb = new ArrayBean();
	pAb->m_type = USER_TYPE;
	pAb->m_value.cta = new ComplexObjectHandler;
	pAb->m_value.cta->pSZFunct = (AXIS_SERIALIZE_FUNCT)pSZFunct;
	pAb->m_value.cta->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
	pAb->m_value.cta->pSizeFunct = (AXIS_OBJECT_SIZE_FUNCT)pSizeFunct;
	pAb->m_value.cta->pObject = pObject;
	return pAb;
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, const AxisChar* sValue, XSDTYPE type)
{
	return m_BTSZ.serialize(sName, sValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, int nValue)
{
	return m_BTSZ.serialize(sName, nValue);		
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, struct tm tValue)
{
    return m_uAxisTime.serialize(sName, tValue).c_str();
    //return NULL;
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned int unValue)
{
    return m_BTSZ.serialize(sName, unValue);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, short sValue)
{
    return m_BTSZ.serialize(sName, sValue);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned short usValue)
{
    return m_BTSZ.serialize(sName, usValue);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, char cValue)
{
    return m_BTSZ.serialize(sName, cValue);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned char ucValue)
{
    return m_BTSZ.serialize(sName, ucValue);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, long lValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, lValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned long ulValue)
{
    return m_BTSZ.serialize(sName, ulValue);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, float fValue)
{
    return m_BTSZ.serialize(sName, fValue);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, double dValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, dValue, type);
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
