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
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */
// SoapDeSerializer.h: interface for the SoapDeSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPDESERIALIZER_H__FD0E7C3B_B887_480A_9E2A_20736A88B09B__INCLUDED_)
#define AFX_SOAPDESERIALIZER_H__FD0E7C3B_B887_480A_9E2A_20736A88B09B__INCLUDED_

#include "../common/IHandlerSoapDeSerializer.h"
#include "XMLStreamHandler.h"

#define HUGE_BUFFER_SIZE 8192

class SoapEnvelope;
class SoapHeader;
class SoapMethod;
class SoapBody;
class SoapFault;

class SoapDeSerializer : public IHandlerSoapDeSerializer
{
private:
	XMLStreamHandler* m_pHandler;
	SAX2XMLReader* m_pParser;
	const Ax_soapstream* m_pInputStream;
	char m_hugebuffer[HUGE_BUFFER_SIZE];
	Param* m_pLastArrayParam;
public:
	int GetVersion();
	const AxisChar* AXISCALL GetMethodName();
	int Init();
	IParam* AXISCALL GetParam();
	int AXISCALL Deserialize(IParam* pIParam, int bHref);
	SoapFault* GetFault();
	SoapMethod* GetMethod();
	SoapBody* GetBody();
	ISoapHeader* GetHeader();
	SoapEnvelope* GetEnvelope();
	int SetInputStream(const Ax_soapstream* pInputStream);
	SoapDeSerializer();
	virtual ~SoapDeSerializer();
	/* Method used by wrappers to get a deserialized Array of complex types */
	Axis_Array AXISCALL GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI);
	/* Method used by wrappers to get a deserialized Array of basic types */
	Axis_Array AXISCALL GetBasicArray(XSDTYPE nType);
	int AXISCALL GetArraySize();
	int AXISCALL GetArray(Axis_Array* pArray, XSDTYPE nType);
	/* Method used by wrappers to get a deserialized single object of complex type */
	void* AXISCALL GetObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pchTypeName, const AxisChar* pchURI);
	
	/* Methods used by wrappers to get a deserialized value of basic types */
	int AXISCALL GetInt();
    unsigned int AXISCALL GetUnsignedInt();
    short AXISCALL GetShort();
    unsigned short AXISCALL GetUnsignedShort();
    char AXISCALL GetByte();
    unsigned char AXISCALL GetUnsignedByte();
    long AXISCALL GetLong();
    long AXISCALL GetInteger();
    unsigned long AXISCALL GetUnsignedLong();
	float AXISCALL GetFloat();
    double AXISCALL GetDouble();
    double AXISCALL GetDecimal();
	const AxisChar* AXISCALL GetString();
    const AxisChar* AXISCALL GetAnyURI();
    const AxisChar* AXISCALL GetQName();
	const AxisChar* AXISCALL GetHexString();
	const AxisChar* AXISCALL GetBase64String();
    /*return a tm struct which contain year-month-date-hour-
      minute-second*/
    struct tm AXISCALL GetDateTime();
    struct tm AXISCALL GetDate();
    struct tm AXISCALL GetTime();
    /*return a tm struct which contain years-months-dates-hours-
      minutes-seconds which represents a duration*/
    long AXISCALL GetDuration();
	void* CreateArray(XSDTYPE nType, int nSize);
	void DeleteArray(Axis_Array* pArray , XSDTYPE nType);
};

#endif // !defined(AFX_SOAPDESERIALIZER_H__FD0E7C3B_B887_480A_9E2A_20736A88B09B__INCLUDED_)
