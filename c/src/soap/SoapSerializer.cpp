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
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

// SoapSerializer.cpp: implementation of the SoapSerializer class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/soap/SoapEnvelope.h>
#include <axis/soap/SoapSerializer.h>
#include <axis/soap/HeaderBlock.h>
#include <axis/common/GDefine.h>
#include <axis/common/Packet.h>
#include <axis/common/ArrayBean.h>
#include <axis/common/BasicTypeSerializer.h>
#include <axis/soap/SoapKeywordMapping.h>
#include <stdio.h>
#include <stdarg.h>

#include <axis/common/AxisTrace.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// Following values should come from axis configuration files.
#define INITIAL_SERIALIZE_BUFFER_SIZE 4096
#define NO_OF_SERIALIZE_BUFFERS 10

IWrapperSoapSerializerBaseFunctions SoapSerializer::ms_VFtable;

SoapSerializer::SoapSerializer()
{
	__vfptr = &ms_VFtable;
	m_pSoapEnvelope = NULL;
	m_iSoapVersion = SOAP_VER_1_1;
	m_pOutputStream = NULL;
	m_nMaxBuffersToCreate = NO_OF_SERIALIZE_BUFFERS;
	m_nInitialBufferSize = INITIAL_SERIALIZE_BUFFER_SIZE;
	m_pSZBuffers = new SerializeBuffers[m_nMaxBuffersToCreate];
	for (int x=0; x<m_nMaxBuffersToCreate; x++)
	{
		m_pSZBuffers[x].inuse = 0;
		m_pSZBuffers[x].buffer = NULL;
	}
}

SoapSerializer::~SoapSerializer()
{
	if (m_pSoapEnvelope) delete m_pSoapEnvelope;
}

int SoapSerializer::setSoapEnvelope(SoapEnvelope *pSoapEnvelope)
{
	m_pSoapEnvelope = pSoapEnvelope;

	return AXIS_SUCCESS;
}

int SoapSerializer::setSoapHeader(SoapHeader *pSoapHeader)
{
	int intStatus = AXIS_FAIL;

	if(m_pSoapEnvelope) {

		if((m_pSoapEnvelope)&& (m_pSoapEnvelope->m_pSoapHeader)) {
			//no need to create a SOAP Header, it already exists
			intStatus= AXIS_OBJECT_ALREADY_EXISTS;
		} else {
			m_pSoapEnvelope->setSoapHeader(pSoapHeader);
			intStatus= AXIS_SUCCESS;
		}
	}

	return intStatus;
}

int SoapSerializer::setSoapBody(SoapBody *pSoapBody)
{
	int intStatus= AXIS_FAIL;

	if(m_pSoapEnvelope) {
		m_pSoapEnvelope->setSoapBody(pSoapBody);
		intStatus= AXIS_SUCCESS;
	}

	return intStatus;
}

int SoapSerializer::setSoapMethod(SoapMethod *pSoapMethod)
{
	int intStatus= AXIS_FAIL;

	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody)) {
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod= pSoapMethod;
		intStatus= AXIS_SUCCESS;
	}

	return intStatus;
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, int nValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.nValue = nValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParamHelper(const AxisChar* pchName, XSDTYPE nType, uParamValue uValue)
{
	Param* pParam = new Param();
	pParam->SetValue(nType, uValue);
	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
	{
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->AddOutputParam(pParam);
	}
	pParam->SetName(pchName);
	return AXIS_SUCCESS;
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, unsigned int unValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.unValue = unValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, short sValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.sValue = sValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, unsigned short usValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.usValue = usValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, long lValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.lValue = lValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, unsigned long ulValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.ulValue = ulValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, char cValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.cValue = cValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, unsigned char ucValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.ucValue = ucValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, float fValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.fValue = fValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, double dValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.dValue = dValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, struct tm tValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.tValue = tValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, const AxisChar* pStrValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.pStrValue = pStrValue;
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, const string& sStrValue, XSDTYPE type)
{
	uParamValue uValue;
	uValue.pStrValue = sStrValue.c_str();
	return AddOutputParamHelper(pchName, type, uValue);
}

int SoapSerializer::AddOutputBasicArrayParam(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
{
	IArrayBean* pAb = makeArrayBean(nType, (void*)(pArray->m_Array));
	pAb->SetDimension(pArray->m_Size);
	Param* pParam = new Param();
	if (RPC_ENCODED == m_nStyle)
	{
		pAb->SetItemName("item");
		pParam->SetName(pName);
	}
	else
	{
		pAb->SetItemName(pName);
		pParam->SetName("array");		
	}
	pParam->m_Value.pIArray = pAb;
	pParam->m_Type = XSD_ARRAY;
	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
	{
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->AddOutputParam(pParam);
	}
	return AXIS_SUCCESS;
}

int SoapSerializer::AddOutputCmplxArrayParam(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	IArrayBean* pAb = makeArrayBean((void*)(pArray->m_Array), pSZFunct, pDelFunct, pSizeFunct);
	pAb->SetDimension(pArray->m_Size);
	Param* pParam = new Param();
	if (RPC_ENCODED == m_nStyle)
	{
		pAb->SetItemName("item");
		pAb->SetTypeName(pName);
		pAb->SetUri(pNamespace);
		pParam->SetName(pName);
	}
	else
	{
		pAb->SetItemName(pName);
		pParam->SetName("array");		
	}
	pParam->m_Value.pIArray = pAb;
	pParam->m_Type = XSD_ARRAY;
	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
	{
		m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->AddOutputParam(pParam);
	}
	pParam->SetName(pName);
	return AXIS_SUCCESS;
}

int SoapSerializer::AddOutputCmplxParam(void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace )
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
	pParam->SetName(pName);
	return AXIS_SUCCESS;
}

int SoapSerializer::setSoapFault(SoapFault *pSoapFault)
{
	int intStatus= AXIS_FAIL;

	if(m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody)) {
		m_pSoapEnvelope->m_pSoapBody->m_pSoapFault= pSoapFault;
		intStatus= AXIS_SUCCESS;
	}

	return intStatus;
}

int SoapSerializer::SetOutputStream(const Ax_soapstream* pStream)
{
	m_pOutputStream = pStream;
	int iStatus= AXIS_SUCCESS;

	if(m_pSoapEnvelope) {
		Serialize("<?xml version='1.0' encoding='utf-8' ?>", NULL);
		iStatus= m_pSoapEnvelope->serialize(*this, (SOAP_VERSION)m_iSoapVersion);
		SendSerializedBuffer();
	}
	return iStatus;
}

/**
 * Initializing the members of the class. This is needed since
 * the same object instance of this class, may be used to server
 * several SOAP requests.
 */
int SoapSerializer::Init()
{
	m_nStatus = AXIS_SUCCESS;

	if(m_pSoapEnvelope) {
		delete m_pSoapEnvelope;
		m_pSoapEnvelope= NULL;
	}

	/* Adding SoapEnvelop and SoapBody to Serializer */
	m_pSoapEnvelope = new SoapEnvelope();
	m_pSoapEnvelope->setSoapBody(new SoapBody());
	
	SetNextSerilizeBuffer();

	iCounter=0;
	return AXIS_SUCCESS;
}

int SoapSerializer::setSoapVersion(SOAP_VERSION nSoapVersion)
{
	m_iSoapVersion = nSoapVersion;
	//here the default namespaces of the SoapEnvelop should be added and intialized as well.
	m_pSoapEnvelope->addStandardNamespaceDecl(SoapKeywordMapping::Map(nSoapVersion).pEnv);
	m_pSoapEnvelope->addStandardNamespaceDecl(SoapKeywordMapping::Map(nSoapVersion).pXsd);
	m_pSoapEnvelope->addStandardNamespaceDecl(SoapKeywordMapping::Map(nSoapVersion).pXsi);
	return AXIS_SUCCESS;
}

const AxisChar* SoapSerializer::getNewNamespacePrefix()
{
	iCounter++;
    AxisSprintf(cCounter, 64, "ns%d", iCounter);
	return cCounter;
}

IWrapperSoapSerializer& SoapSerializer::operator <<(const AxisChar* cSerialized)
{
	if (AXIS_SUCCESS != m_nStatus) 
	{
		/* some thing has gone wrong. So do nothing */
		return *this;
	}

	int iTmpSerBufferSize = strlen(cSerialized);
	if((m_nFilledSize + iTmpSerBufferSize)>= m_nCurrentBufferSize) 
	{
		/*
		 * Send the current buffer to the transport and get
		 * another buffer to be filled
		 */
		if (AXIS_SUCCESS == SendSerializedBuffer())
		{
			if (AXIS_SUCCESS == SetNextSerilizeBuffer())
			{
				strcat((char*)m_pSZBuffers[m_nCurrentBufferIndex].buffer, cSerialized);
				m_nFilledSize += iTmpSerBufferSize;
			}
		}
	}
	else
	{
		strcat((char*)m_pSZBuffers[m_nCurrentBufferIndex].buffer, cSerialized);
		m_nFilledSize += iTmpSerBufferSize;
	}
	return *this;
}

int SoapSerializer::SendSerializedBuffer()
{
	int nStatus;
	if (NULL != m_pOutputStream->transport.pSendFunct)
	{
		nStatus = m_pOutputStream->transport.pSendFunct((char*)
		m_pSZBuffers[m_nCurrentBufferIndex].buffer, (void*)(&(m_pSZBuffers[m_nCurrentBufferIndex].inuse)), m_pOutputStream);
		if (TRANSPORT_FINISHED == nStatus) 
		/* transport layer has done with the buffer.So same buffer can be re-used*/
		{
			m_pSZBuffers[m_nCurrentBufferIndex].buffer[0] = '\0'; /* put nul */
			m_pSZBuffers[m_nCurrentBufferIndex].inuse = 0; /* not in use */
		}
		else if (TRANSPORT_FAILED == nStatus) 
		{
			return AXIS_FAIL;
		}
	}
	else
	{
		return AXIS_FAIL;
	}
	return AXIS_SUCCESS;
}

/**
 * This method sets the next buffer to be used for serialization.
 *
 */
int SoapSerializer::SetNextSerilizeBuffer()
{
	for (int x=0;x<m_nMaxBuffersToCreate;x++)
	{
		if (m_pSZBuffers[x].buffer) /* a buffer has been created */
		{
			if (0 == m_pSZBuffers[x].inuse) /* buffer is not being used */ 
			{
				m_nCurrentBufferIndex = x;
				m_pSZBuffers[m_nCurrentBufferIndex].inuse = 1;
				m_pSZBuffers[m_nCurrentBufferIndex].buffer[0] = '\0';
				m_nFilledSize = 0;
				m_nCurrentBufferSize = m_nInitialBufferSize*(1 << m_nCurrentBufferIndex);
				return AXIS_SUCCESS;
			}
		}
		else /* a buffer is not yet created at this array index. So create one and use it */
		{
			m_nCurrentBufferIndex = x;
			m_nCurrentBufferSize = m_nInitialBufferSize*(1 << m_nCurrentBufferIndex);			
			m_pSZBuffers[m_nCurrentBufferIndex].buffer = new char[m_nCurrentBufferSize];
			m_pSZBuffers[m_nCurrentBufferIndex].inuse = 1;
			m_pSZBuffers[m_nCurrentBufferIndex].buffer[0] = '\0';
			m_nFilledSize = 0;
			return AXIS_SUCCESS;
		}
	}
	AXISTRACE1("No buffers left for serialization");
	return AXIS_FAIL;
}

int SoapSerializer::createSoapMethod(const AxisChar* sLocalName, 
									 const AxisChar* sPrefix, const AxisChar* sURI)
{
	SoapMethod* pMethod = new SoapMethod();
	setSoapMethod(pMethod);
	pMethod->setLocalName(sLocalName);
	pMethod->setPrefix(sPrefix);
	pMethod->setUri(sURI);
	return AXIS_SUCCESS;
}

/**
 * Used to create an ArrayBean when the return type of a method is an array
 * of basic types
 */
IArrayBean* SoapSerializer::makeArrayBean(XSDTYPE nType, void* pArray)
{
	ArrayBean* pAb = new ArrayBean();
	pAb->m_type = nType;
	pAb->m_value.sta = pArray;
	return pAb;
}

/**
 * Used to create an ArrayBean when the return type of a method is an array
 * of complex types
 */
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

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, const string sValue, XSDTYPE type)
{
	return m_BTSZ.serialize(sName, sValue.c_str(), type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, int nValue, XSDTYPE type)
{
	return m_BTSZ.serialize(sName, nValue, type);		
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, struct tm tValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, tValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned int unValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, unValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, short sValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, sValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned short usValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, usValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, char cValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, cValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned char ucValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, ucValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, long lValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, lValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, unsigned long ulValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, ulValue, type);
}

const AxisChar* SoapSerializer::SerializeBasicType(const AxisChar* sName, float fValue, XSDTYPE type)
{
    return m_BTSZ.serialize(sName, fValue, type);
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
	int intStatus= AXIS_FAIL;

	if((m_pSoapEnvelope)&& (m_pSoapEnvelope->m_pSoapHeader)) {
		//no need to create a SOAP Header, it already exists
	} else {
		SoapHeader* pSoapHeader= new SoapHeader();
		setSoapHeader(pSoapHeader);
	}

	m_pSoapEnvelope->m_pSoapHeader->addHeaderBlock(pHeaderBlock);
	intStatus= AXIS_SUCCESS;

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

	return AXIS_SUCCESS;
}

/**
 * Used to Serialize an array of complex types inside a complex type. Called from within the Serialize wrapper
 * method of the complex type.
 */
int SoapSerializer::SerializeCmplxArray(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	ArrayBean* pAb = (ArrayBean*)makeArrayBean((void*)(pArray->m_Array), pSZFunct, pDelFunct, pSizeFunct);
	pAb->SetDimension(pArray->m_Size);
	Param* pParam = new Param();
	if (RPC_ENCODED == m_nStyle)
	{
		pAb->SetItemName("item");
		pAb->SetTypeName(pName);
		pAb->SetUri(pNamespace);
		pParam->SetName(pName);
	}
	else
	{
		pAb->SetItemName(pName);
		pParam->SetName("array");		
	}
	pParam->m_Value.pIArray = pAb;
	pParam->m_Type = XSD_ARRAY;
	pParam->serialize(*this);
	/* Remove pointer to the array from the ArrayBean to avoid deleting the array when ArrayBean is deleted 
	   Array will be deleted when the complex type that contains this array is deleted */
	pAb->RemoveArrayPointer();
	delete pParam;
	return AXIS_SUCCESS;
}

/**
 * Used to Serialize an array of basic types inside a complex type. Called from within the Serialize wrapper
 * method of the complex type.
 */
int SoapSerializer::SerializeBasicArray(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
{
	ArrayBean* pAb = (ArrayBean*)makeArrayBean(nType, (void*)(pArray->m_Array));
	pAb->SetDimension(pArray->m_Size);
	Param* pParam = new Param();
	if (RPC_ENCODED == m_nStyle)
	{
		pAb->SetItemName("item");
		pParam->SetName(pName);
	}
	else
	{
		pAb->SetItemName(pName);
		pParam->SetName("array");		
	}
	pParam->m_Value.pIArray = pAb;
	pParam->m_Type = XSD_ARRAY;
	pParam->serialize(*this);
	/* Remove pointer to the array from the ArrayBean to avoid deleting the array when ArrayBean is deleted 
	   Array will be deleted when the complex type that contains this array is deleted */
	pAb->RemoveArrayPointer();
	delete pParam;
	return AXIS_SUCCESS;
}

int SoapSerializer::AddOutputParam(const AxisChar* pchName, void* pValue, XSDTYPE type)
{
	switch(type)
	{
	case XSD_INT:
	case XSD_BOOLEAN:
		AddOutputParam(pchName,*((int*)(pValue)),type);
		break; 
    case XSD_UNSIGNEDINT:
		AddOutputParam(pchName,*((unsigned int*)(pValue)),type);
		break;           
    case XSD_SHORT:
		AddOutputParam(pchName,*((short*)(pValue)),type);
		break; 
    case XSD_UNSIGNEDSHORT:
		AddOutputParam(pchName,*((unsigned short*)(pValue)),type);
		break;         
    case XSD_BYTE:
		AddOutputParam(pchName,*((char*)(pValue)),type);
		break; 
    case XSD_UNSIGNEDBYTE:
		AddOutputParam(pchName,*((unsigned char*)(pValue)),type);
		break;
    case XSD_LONG:
    case XSD_INTEGER:
	case XSD_DURATION:
		AddOutputParam(pchName,*((long*)(pValue)),type);
		break;        
    case XSD_UNSIGNEDLONG:
		AddOutputParam(pchName,*((unsigned long*)(pValue)),type);
		break;
	case XSD_FLOAT:
		AddOutputParam(pchName,*((float*)(pValue)),type);
		break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
		AddOutputParam(pchName,*((double*)(pValue)),type);
		break;              
	case XSD_STRING:
	case XSD_HEXBINARY:
	case XSD_BASE64BINARY:
		AddOutputParam(pchName,((char*)(pValue)),type);
		break;
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
		AddOutputParam(pchName,*((struct tm*)(pValue)),type);
        break;        
	}
	return AXIS_SUCCESS;
}

int SoapSerializer::SerializeBasicType(const AxisChar* pchName, void* pValue, XSDTYPE type)
{
	const AxisChar* pSerialized;
	switch(type)
	{
	case XSD_INT:
	case XSD_BOOLEAN:
		pSerialized = SerializeBasicType(pchName,*((int*)(pValue)),type);
		break;
    case XSD_UNSIGNEDINT:
		pSerialized = SerializeBasicType(pchName,*((unsigned int*)(pValue)),type);
		break;
    case XSD_SHORT:
		pSerialized = SerializeBasicType(pchName,*((short*)(pValue)),type);
		break;
    case XSD_UNSIGNEDSHORT:
		pSerialized = SerializeBasicType(pchName,*((unsigned short*)(pValue)),type);
		break;
    case XSD_BYTE:
		pSerialized = SerializeBasicType(pchName,*((char*)(pValue)),type);
		break;
    case XSD_UNSIGNEDBYTE:
		pSerialized = SerializeBasicType(pchName,*((unsigned char*)(pValue)),type);
		break;
    case XSD_LONG:
    case XSD_INTEGER:
	case XSD_DURATION:
		pSerialized = SerializeBasicType(pchName,*((long*)(pValue)),type);
		break;
    case XSD_UNSIGNEDLONG:
		pSerialized = SerializeBasicType(pchName,*((unsigned long*)(pValue)),type);
		break;
	case XSD_FLOAT:
		pSerialized = SerializeBasicType(pchName,*((float*)(pValue)),type);
		break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
		pSerialized = SerializeBasicType(pchName,*((double*)(pValue)),type);
		break;
	case XSD_STRING:
	case XSD_HEXBINARY:
	case XSD_BASE64BINARY:
		pSerialized = SerializeBasicType(pchName,((char*)(pValue)),type);
		break;
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
		pSerialized = SerializeBasicType(pchName,*((struct tm*)(pValue)),type);
		break;
	}
	if (NULL != pSerialized)
	{
		*this << pSerialized;
		return AXIS_SUCCESS;
	}
	else
	{
		return AXIS_FAIL;
	}
}

void SoapSerializer::Serialize(const char* pFirst, ...)
{
	va_list vList;
	const char* pArg;
	if (pFirst) *this << pFirst;
	va_start( vList, pFirst );     /* Initialize variable arguments. */
	do
	{
		pArg = va_arg( vList, const char*);
		if (pArg)
			*this << pArg;
	}
	while (pArg != NULL);
	va_end( vList);              /* Reset variable arguments.      */
}

/**
 * Callback function that should be called by the transport module to release a buffer passed to it by a Serializer. 
 * @param 
 *		buffer - Same buffer passed to transport by calling transport's AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES 
 *				 callback
 *		buffer - Same bufferid passed to transport by calling transport's AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES 
 *				 callback
 *		stream - Same stream object passed to transport by calling transport's AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES 
 *				 callback
 */
void axis_buffer_release(const char* buffer, const void* bufferid, const void* stream)
{
	int* pInt = (int*)bufferid;
	*pInt = 0; /* set that the buffer is not in use */
	char *pChar = const_cast<char*>(buffer);
	pChar[0] = '\0'; /* set nul */ 
}



