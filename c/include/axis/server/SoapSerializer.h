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

class SoapEnvelope;
class SoapHeader;
class SoapMethod;
class SoapBody;
class SoapFault;
class HeaderBlock;

#include <map>
using namespace std;

class SoapSerializer : public IHandlerSoapSerializer
{
	typedef struct
	{
		volatile unsigned char inuse;
		volatile char* buffer;
	} SerializeBuffers;
private:
	int m_nCounter;
	AxisChar m_Buf[8];
	SoapEnvelope* m_pSoapEnvelope;	
	int m_iSoapVersion;
	/* Current Serialization Style */
	AXIS_BINDING_STYLE m_nStyle;
	/* Table that keeps all allocated buffers */
	volatile SerializeBuffers* m_pSZBuffers;
	/* Size of the initial buffer created.*/
	int m_nInitialBufferSize;
	/* Size of the m_SZBuffers array.*/
	int m_nMaxBuffersToCreate;
	/* Maximum size of the buffer that is being filled */
	int m_nCurrentBufferSize;
	/* How much charators has been filled to the currently selected buffer */
	int m_nFilledSize;
	/* Currently selected buffer index*/
	int m_nCurrentBufferIndex;
	/* Overall status of Serializer. If anything goes wrong this is not AXIS_SUCCESS */
	int m_nStatus;
	/* Map that contains pairs of currently available namespaces and prefixes */ 
	map<AxisXMLString, AxisXMLString> m_NsStack;

public:
	int AXISCALL CreateSoapMethod(const AxisChar* sLocalName, const AxisChar* sURI);	
//	IWrapperSoapSerializer& operator<<(const char* cSerialized);
	IWrapperSoapSerializer& operator<<(const AxisChar* cSerialized);
	const AxisChar* AXISCALL GetNamespacePrefix(const AxisChar* pNamespace);
	void AXISCALL RemoveNamespacePrefix(const AxisChar* pNamespace);
	int setSoapVersion(SOAP_VERSION);
	int Init();
	int SetOutputStream(const Ax_soapstream* pStream);
	void MarkEndOfStream();
	int setSoapFault(SoapFault* pSoapFault);
	int setSoapMethod(SoapMethod* pSoapMethod);
	int setSoapBody(SoapBody* pSoapBody);
	int setSoapHeader(SoapHeader* pSoapHeader);
	int setSoapEnvelope(SoapEnvelope* pSoapEnvelope);
	SoapSerializer();
	virtual ~SoapSerializer();
	//for arrays of basic types
	int AXISCALL AddOutputBasicArrayParam(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName);
	//for arrays of complex types
	int AXISCALL AddOutputCmplxArrayParam(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	//for complex types
	int AXISCALL AddOutputCmplxParam(void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	int AXISCALL SerializeCmplxArray(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	int AXISCALL SerializeBasicArray(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName);

private:
	int SendSerializedBuffer();
	int SetNextSerilizeBuffer();
	IArrayBean* makeArrayBean(XSDTYPE nType, void* pArray);
	IArrayBean* makeArrayBean(void* pObject, void* pSZFunct, void* pDelFunct, void* pSizeFunct);

public: //Basic Type Serializing methods
	int removeSoapHeader();
	int setHeaderBlock(HeaderBlock* pHeaderBlock);
	IHeaderBlock* createHeaderBlock();
    
private:
	BasicTypeSerializer m_BTSZ;
	const Ax_soapstream* m_pOutputStream;
public:
	/* to add a header block to the Serializer. Probably by a handler */
	int AXISCALL AddHeaderBlock(IHeaderBlock* pBlk);
	int AXISCALL AddOutputParam(const AxisChar* pchName, void* pValue, XSDTYPE type);
	int AXISCALL SerializeAsElement(const AxisChar* pchName, void* pValue, XSDTYPE type);
	int AXISCALL SerializeAsAttribute(const AxisChar* pName, const AxisChar* pNamespace, void* pValue, XSDTYPE type);
	void AXISCALL Serialize(const char* pFirst, ...);
	void SetStyle(AXIS_BINDING_STYLE nStyle){ m_nStyle = nStyle; m_BTSZ.SetStyle(nStyle);};
	AXIS_BINDING_STYLE GetStyle(){return m_nStyle;};
	int AXISCALL SetBodyAsHexBinary(xsd__hexBinary body);
	int AXISCALL SetBodyAsBase64Binary(xsd__base64Binary body);
	const AxisChar* AXISCALL GetBodyAsString();
};

#endif // !defined(AFX_SOAPSERIALIZER_H__C37229AD_BD54_430D_9619_E4574CF95334__INCLUDED_)
