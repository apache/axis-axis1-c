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
 */
// SoapDeSerializer.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPDESERIALIZER_H__FD0E7C3B_B887_480A_9E2A_20736A88B09B__INCLUDED_)
#define AFX_SOAPDESERIALIZER_H__FD0E7C3B_B887_480A_9E2A_20736A88B09B__INCLUDED_

#include <axis/common/IHandlerSoapDeSerializer.h>
#include <axis/soap/SoapEnvVersions.h>
#include <axis/soap/HeaderBlock.h>
#include <axis/wsdd/WSDDDefines.h>
#include <axis/xml/XMLParser.h>
#include <axis/xml/AnyElement.h>

class SoapFault;
class SoapMethod;
class SoapBody;
class SoapEnvelope;
class SoapHeader;
class IHeaderBlock;

/**
    @class SoapDeSerializer
    @brief interface for the SoapDeSerializer class.
    @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
*/
class SoapDeSerializer : public IHandlerSoapDeSerializer
{
private:
	SoapEnvelope* m_pEnv;
	SoapHeader* m_pHeader;
    XMLParser* m_pParser;
	/* Current Serialization Style */
	AXIS_BINDING_STYLE m_nStyle;
	/* Last procesed node needed when the attributes are processed */
	const AnyElement* m_pCurrNode;
	const AnyElement* m_pNode;
	SOAP_VERSION m_nSoapVersion;
	AxisChar* m_pEndptr; /* used as a parameter to strtoXX conversion functionss */
	int m_nStatus;
	/* Provider type of current service that uses this DeSerializer object */
	PROVIDERTYPE m_ProviderType;

private:
	int AXISCALL GetArraySize(const AnyElement* pElement);
	int GetBody();
public:
	int Init();
	int GetVersion();
	SoapEnvelope* GetEnvelope();
	int GetHeader();
	int FlushInputStream();
	PROVIDERTYPE GetCurrentProviderType() { return m_ProviderType;};
	void SetCurrentProviderType(PROVIDERTYPE nType) { m_ProviderType = nType;};
	/*
	 * Methods to manipulate entire body when the body is compressed or encrypted 
	 * These functions are provided for handlers to manipulate entire soap body.
	 */
	xsd__hexBinary AXISCALL GetBodyAsHexBinary();
	xsd__base64Binary AXISCALL GetBodyAsBase64Binary();
	int AXISCALL SetNewSoapBody(AxisChar* pNewSoapBody);
	bool IsAnyMustUnderstandHeadersLeft();
	SoapFault* GetFault();
	int AXISCALL CheckMessageBody(const AxisChar* pName, const AxisChar* pNamespace);
	/** to get any header blocks left in the Deserializer */
	HeaderBlock* GetHeaderBlock();
	/** to add a header block to the Deserializer. Probably a handler */
	int AXISCALL AddHeaderBlock(IHeaderBlock* pBlk);
	/** to get a named header blcok from the Deserializer */
	IHeaderBlock* GetHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace);
	int SetInputStream(const Ax_soapstream* pInputStream);
	SoapDeSerializer();
	virtual ~SoapDeSerializer();
	/** Method used by wrappers to get a deserialized Array of complex types */
	Axis_Array AXISCALL GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/** Method used by wrappers to get a deserialized Array of basic types */
	Axis_Array AXISCALL GetBasicArray(XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace);
	/** Method used by wrappers to get a deserialized single object of complex type */
	void* AXISCALL GetCmplxObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	
	/* Methods used by wrappers to get a deserialized value of basic types */
	int AXISCALL GetElementAsInt(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__boolean AXISCALL GetElementAsBoolean(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int AXISCALL GetElementAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace);
    short AXISCALL GetElementAsShort(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short AXISCALL GetElementAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace);
    char AXISCALL GetElementAsByte(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char AXISCALL GetElementAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetElementAsLong(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetElementAsInteger(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long AXISCALL GetElementAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace);
	float AXISCALL GetElementAsFloat(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetElementAsDouble(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetElementAsDecimal(const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* AXISCALL GetElementAsString(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetElementAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetElementAsQName(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary AXISCALL GetElementAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary AXISCALL GetElementAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetElementAsDateTime(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetElementAsDate(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetElementAsTime(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetElementAsDuration(const AxisChar* pName, const AxisChar* pNamespace);

	int AXISCALL GetAttributeAsInt(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__boolean AXISCALL GetAttributeAsBoolean(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int AXISCALL GetAttributeAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace);
    short AXISCALL GetAttributeAsShort(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short AXISCALL GetAttributeAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace);
    char AXISCALL GetAttributeAsByte(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char AXISCALL GetAttributeAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetAttributeAsLong(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetAttributeAsInteger(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long AXISCALL GetAttributeAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace);
	float AXISCALL GetAttributeAsFloat(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetAttributeAsDouble(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetAttributeAsDecimal(const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* AXISCALL GetAttributeAsString(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetAttributeAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetAttributeAsQName(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary AXISCALL GetAttributeAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary AXISCALL GetAttributeAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetAttributeAsDateTime(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetAttributeAsDate(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetAttributeAsTime(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetAttributeAsDuration(const AxisChar* pName, const AxisChar* pNamespace);
	
//	void* CreateArray(XSDTYPE nType, int nSize);
//	void DeleteArray(Axis_Array* pArray , XSDTYPE nType);
	void SetStyle(AXIS_BINDING_STYLE nStyle){ m_nStyle = nStyle;};
	XSDTYPE GetXSDType(const AnyElement* pElement);
	int AXISCALL GetStatus(){return m_nStatus;};

private:
	int GetElementForAttributes(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary DecodeFromBase64Binary(const AxisChar* pValue);
	xsd__hexBinary DecodeFromHexBinary(const AxisChar* pValue);
};

#endif // !defined(AFX_SOAPDESERIALIZER_H__FD0E7C3B_B887_480A_9E2A_20736A88B09B__INCLUDED_)
