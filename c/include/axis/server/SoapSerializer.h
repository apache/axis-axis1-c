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
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

// SoapSerializer.h: interface for the SoapSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPSERIALIZER_H__C37229AD_BD54_430D_9619_E4574CF95334__INCLUDED_)
#define AFX_SOAPSERIALIZER_H__C37229AD_BD54_430D_9619_E4574CF95334__INCLUDED_

#include "../common/IHandlerSoapSerializer.h"
#include "../common/BasicTypeSerializer.h"
#include "../common/AxisTime.h"
#include "../common/Packet.h"
#include "SoapEnvVersions.h"


#define SERIALIZE_BUFFER_SIZE 8192

class SoapEnvelope;
class SoapHeader;
class SoapMethod;
class SoapBody;
class SoapFault;
class HeaderBlock;

class SoapSerializer : public IHandlerSoapSerializer /*: public ISoapSerializer*/
{
private:
	int iCounter;
	AxisChar cCounter[64];
	SoapEnvelope* m_pSoapEnvelope;	
	int m_iSoapVersion;
	char m_cSerializedBuffer[SERIALIZE_BUFFER_SIZE];
	int m_iCurrentSerBufferSize;
public:
	int AXISCALL createSoapMethod(const AxisChar* sLocalName, const AxisChar* sPrefix, const AxisChar* sURI);	
//	IWrapperSoapSerializer& operator<<(const char* cSerialized);
	IWrapperSoapSerializer& operator<<(const AxisChar* cSerialized);
	const AxisChar* AXISCALL getNewNamespacePrefix();
	int setSoapVersion(SOAP_VERSION);
	int Init();
	int SetOutputStream(const Ax_soapstream* pStream);
	int setSoapFault(SoapFault* pSoapFault);
	int setSoapMethod(SoapMethod* pSoapMethod);
	int setSoapBody(SoapBody* pSoapBody);
	int setSoapHeader(SoapHeader* pSoapHeader);
	int setSoapEnvelope(SoapEnvelope* pSoapEnvelope);
	SoapSerializer();
	virtual ~SoapSerializer();
	//for basic types
	int AddOutputParam(const AxisChar* pchName, int nValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, unsigned int unValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, short sValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, unsigned short usValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, long lValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, unsigned long ulValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, char cValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, unsigned char ucValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, float fValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, double dValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, struct tm tValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, const AxisChar* pStrValue, XSDTYPE type);
	int AddOutputParam(const AxisChar* pchName, const string& sStrValue, XSDTYPE type);
	//for arrays of basic types
	int AXISCALL AddOutputBasicArrayParam(const AxisChar* pchName, const Axis_Array* pArray, XSDTYPE nType);
	//for arrays of complex types
	int AXISCALL AddOutputCmplxArrayParam(const AxisChar* pchName, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI);
	//for complex types
	int AXISCALL AddOutputCmplxParam(const AxisChar* pchName, void* pObject, void* pDZFunct, void* pDelFunct);
	int AXISCALL SerializeCmplxArray(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI, const AxisChar* pchArrayName);
	int AXISCALL SerializeBasicArray(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pchArrayName);

private:
	int AddOutputParamHelper(const AxisChar* pchName, XSDTYPE nType, uParamValue Value);
	int flushSerializedBuffer();
	IArrayBean* makeArrayBean(XSDTYPE nType, void* pArray);
	IArrayBean* makeArrayBean(void* pObject, void* pSZFunct, void* pDelFunct, void* pSizeFunct);

public: //Basic Type Serializing methods
	int removeSoapHeader();
	int setHeaderBlock(HeaderBlock* pHeaderBlock);
	IHeaderBlock* createHeaderBlock();

	const AxisChar* SerializeBasicType(const AxisChar* sName, const AxisChar* sValue, XSDTYPE type);
	const AxisChar* SerializeBasicType(const AxisChar* sName, const string sValue, XSDTYPE type);
	const AxisChar* SerializeBasicType(const AxisChar* sName, int nValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, struct tm tValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned int unValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, short sValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned short usValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, char cValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned char ucValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, long lValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned long ulValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, float fValue, XSDTYPE type);
    const AxisChar* SerializeBasicType(const AxisChar* sName, double dValue, XSDTYPE type);
    
private:
	BasicTypeSerializer m_BTSZ;
	const Ax_soapstream* m_pOutputStream;
public:
	int AXISCALL AddOutputParam(const AxisChar* pchName, void* pValue, XSDTYPE type);
	int AXISCALL SerializeBasicType(const AxisChar* pchName, void* pValue, XSDTYPE type);
	void AXISCALL Serialize(const char* pFirst, ...);
};

#endif // !defined(AFX_SOAPSERIALIZER_H__C37229AD_BD54_430D_9619_E4574CF95334__INCLUDED_)
