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
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

/* IWrapperSoapDeSerializer.h: interface for the IWrapperSoapDeSerializer class.*/
#if !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_)
#define AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_


#include "GDefine.h"
#include "AxisUserAPI.h"
#include "TypeMapping.h"

#ifdef __cplusplus

#include "ISoapDeSerializer.h"
#include <string>
using namespace std;
#endif

typedef struct {
	int (AXISCALL* CheckMessageBody)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by wrappers to get a deserialized Array of complex types */
	Axis_Array (AXISCALL* GetCmplxArray)(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by wrappers to get a deserialized Array of basic types */
	Axis_Array (AXISCALL* GetBasicArray)(void* pObj, XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by wrappers to get a deserialized single object of complex type */
	void* (AXISCALL* GetCmplxObject)(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	
	/* Methods used by wrappers to get a deserialized value of basic types */
	int (AXISCALL* GetElementAsInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int (AXISCALL* GetElementAsUnsignedInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    short (AXISCALL* GetElementAsShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short (AXISCALL* GetElementAsUnsignedShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    char (AXISCALL* GetElementAsByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char (AXISCALL* GetElementAsUnsignedByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetElementAsLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetElementAsInteger)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long (AXISCALL* GetElementAsUnsignedLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	float (AXISCALL* GetElementAsFloat)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetElementAsDouble)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetElementAsDecimal)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* (AXISCALL* GetElementAsString)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetElementAsAnyURI)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetElementAsQName)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* (AXISCALL* GetElementAsHexString)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* (AXISCALL* GetElementAsBase64String)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsDateTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsDate)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetElementAsDuration)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
} IWrapperSoapDeSerializerFunctions;

#ifndef __cplusplus

typedef struct { 
	void* unused; /* this corresponds to C++ virtual function pointer which is ignored in C */ 
	IWrapperSoapDeSerializerFunctions* __vfptr;
} IWrapperSoapDeSerializer;

#else

class IWrapperSoapDeSerializer : public ISoapDeSerializer
{
protected:
	void* __vfptr;
public:
	virtual ~IWrapperSoapDeSerializer(){};

	virtual int AXISCALL CheckMessageBody(const AxisChar* pName, const AxisChar* pNamespace)=0;

	/* Method used by wrappers to get a deserialized Array of complex types */
	virtual Axis_Array AXISCALL GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method used by wrappers to get a deserialized Array of basic types */
	virtual Axis_Array AXISCALL GetBasicArray(XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method used by wrappers to get a deserialized single object of complex type */
	virtual void* AXISCALL GetCmplxObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	
	/* Methods used by wrappers to get a deserialized value of basic types */
	virtual int AXISCALL GetElementAsInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned int AXISCALL GetElementAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual short AXISCALL GetElementAsShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned short AXISCALL GetElementAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual char AXISCALL GetElementAsByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned char AXISCALL GetElementAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetElementAsLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetElementAsInteger(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned long AXISCALL GetElementAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual float AXISCALL GetElementAsFloat(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetElementAsDouble(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetElementAsDecimal(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL GetElementAsString(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetElementAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetElementAsQName(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL GetElementAsHexString(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL GetElementAsBase64String(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsDate(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetElementAsDuration(const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* following stuff is needed to provide the interface for C web services */
public:
	static IWrapperSoapDeSerializerFunctions ms_VFtable;
	static int AXISCALL s_GetElementAsInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsInt(pName, pNamespace);};
	static unsigned int AXISCALL s_GetElementAsUnsignedInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsUnsignedInt(pName, pNamespace);};
	static short AXISCALL s_GetElementAsShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsShort(pName, pNamespace);};
	static void s_Initialize()
	{
		ms_VFtable.GetElementAsInt = s_GetElementAsInt;
		ms_VFtable.GetElementAsUnsignedInt = s_GetElementAsUnsignedInt;
		ms_VFtable.GetElementAsShort = s_GetElementAsShort;
	}
};
#endif

#endif /* !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_) */
