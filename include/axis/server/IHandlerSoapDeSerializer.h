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

// IHandlerSoapDeSerializer.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IHANDLERSOAPDESERIALIZER_H__EAD744F9_FEB3_4885_9510_D7BAD8C5AD1C__INCLUDED_)
#define AFX_IHANDLERSOAPDESERIALIZER_H__EAD744F9_FEB3_4885_9510_D7BAD8C5AD1C__INCLUDED_

#include "IWrapperSoapDeSerializer.h"
#include "IHeaderBlock.h"
#include "AxisUserAPI.h"
/**
    @class IHandlerSoapDeSerializer
    @brief interface for the IHandlerSoapDeSerializer class.


    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
#ifdef __cplusplus

class IHandlerSoapDeSerializer : public IWrapperSoapDeSerializer
{
public:
	virtual ~IHandlerSoapDeSerializer() {};
	virtual int AXISCALL AddHeaderBlock(IHeaderBlock* pBlk)=0;
	/**
	 * The soap body may be encrypted/compressed and a handler in the request message 
	 * path may decode and then decrypt and/or decompress whole soap body and set the
	 * XML to the Deserializer. In such a case a handler will use following functions 
	 * to get soap body and set back the XML. If this process goes throgh several
	 * handlers the intermediate binary data (unencrypted/uncompressed body) may be kept 
	 * in the IMessageData until it is converted to XML. A handler usually converts it 
	 * to XML and use SetNewSoapBody(..) function to set the new SoapBody back to the 
	 * Deserializer.
	 */
	virtual xsd__hexBinary AXISCALL GetBodyAsHexBinary()=0;
	virtual xsd__base64Binary AXISCALL GetBodyAsBase64Binary()=0;
	virtual int AXISCALL SetNewSoapBody(AxisChar* pNewSoapBody)=0;
	virtual IHeaderBlock* GetHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace) = 0;
};

#else

typedef struct { 
	void* unused; /* this corresponds to C++ virtual function pointer which is ignored in C */ 
	void* unused_; /* this corresponds to IWrapperSoapDeSerializerFunctions pointer */
	IHandlerSoapDeSerializerFunctions* __vfptr;
} IHandlerSoapDeSerializer;

#endif

#endif // !defined(AFX_IHANDLERSOAPDESERIALIZER_H__EAD744F9_FEB3_4885_9510_D7BAD8C5AD1C__INCLUDED_)
