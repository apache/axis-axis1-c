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

// SoapSerializer.h: interface for the SoapSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPSERIALIZER_H__C37229AD_BD54_430D_9619_E4574CF95334__INCLUDED_)
#define AFX_SOAPSERIALIZER_H__C37229AD_BD54_430D_9619_E4574CF95334__INCLUDED_

#include "../common/IWrapperSoapSerializer.h"
#include "../common/IHandlerSoapSerializer.h"
#include "../common/BasicTypeSerializer.h"
#include "../common/AxisTime.h"
#include "SoapEnvVersions.h"


#define SERIALIZE_BUFFER_SIZE 1024

class SoapEnvelope;
class SoapHeader;
class SoapMethod;
class SoapBody;
class SoapFault;
class HeaderBlock;

class SoapSerializer : public IWrapperSoapSerializer, public IHandlerSoapSerializer /*: public ISoapSerializer*/
{
private:
	int iCounter;
	AxisChar cCounter[64];
	SoapEnvelope* m_pSoapEnvelope;	
	int m_iSoapVersion;
	char m_cSerializedBuffer[SERIALIZE_BUFFER_SIZE];
	int m_iCurrentSerBufferSize;
public:
	ISoapMethod* createSoapMethod();	
	int flushSerializedBuffer();
//	IWrapperSoapSerializer& operator<<(const char* cSerialized);
	IWrapperSoapSerializer& operator<<(const AxisChar* cSerialized);
	const AxisChar* getNewNamespacePrefix();
	int setSoapVersion(SOAP_VERSION);
	int Init();
	int SetOutputStream(const void* pStream);
	int setSoapFault(SoapFault* pSoapFault);
	int setSoapMethod(SoapMethod* pSoapMethod);
	int setSoapBody(SoapBody* pSoapBody);
	int setSoapHeader(SoapHeader* pSoapHeader);
	int setSoapEnvelope(SoapEnvelope* pSoapEnvelope);
	SoapSerializer();
	virtual ~SoapSerializer();
	IParam* AddOutputParam(XSDTYPE nType, uParamValue Value);
	IParam* AddOutputParam(IArrayBean* pArrayBean);
	IParam* AddOutputParam(void* pObject, void* pDZFunct, void* pDelFunct);
	IArrayBean* makeArrayBean(XSDTYPE nType, void* pArray);
	IArrayBean* makeArrayBean(void* pObject, void* pSZFunct, void* pDelFunct, void* pSizeFunct);
public: //Basic Type Serializing methods
	int removeSoapHeader();
	int setHeaderBlock(HeaderBlock* pHeaderBlock);
	IHeaderBlock* createHeaderBlock();

	const AxisChar* SerializeBasicType(const AxisChar* sName, const AxisChar* sValue, XSDTYPE type=XSD_STRING);
	const AxisChar* SerializeBasicType(const AxisChar* sName, int nValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, struct tm tValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned int unValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, short sValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned short usValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, char cValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned char ucValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, long lValue, XSDTYPE type=XSD_LONG);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned long ulValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, float fValue);
    const AxisChar* SerializeBasicType(const AxisChar* sName, double dValue, XSDTYPE type=XSD_DOUBLE);
    
private:
	BasicTypeSerializer m_BTSZ;
	const void* m_pOutputStream;
    AxisTime m_uAxisTime;
};

#endif // !defined(AFX_SOAPSERIALIZER_H__C37229AD_BD54_430D_9619_E4574CF95334__INCLUDED_)
