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

/* IWrapperSoapDeSerializer.h:*/

#if !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_)
#define AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_


#include "GDefine.h"
#include "AxisUserAPI.h"
#include "TypeMapping.h"
#include "WSDDDefines.h"
#include "Packet.h"

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
	xsd__boolean (AXISCALL* GetElementAsBoolean)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
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
	xsd__hexBinary (AXISCALL* GetElementAsHexBinary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary (AXISCALL* GetElementAsBase64Binary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsDateTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsDate)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetElementAsDuration)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);

	int (AXISCALL* GetAttributeAsInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__boolean (AXISCALL* GetAttributeAsBoolean)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int (AXISCALL* GetAttributeAsUnsignedInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    short (AXISCALL* GetAttributeAsShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short (AXISCALL* GetAttributeAsUnsignedShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    char (AXISCALL* GetAttributeAsByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char (AXISCALL* GetAttributeAsUnsignedByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetAttributeAsLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetAttributeAsInteger)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long (AXISCALL* GetAttributeAsUnsignedLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	float (AXISCALL* GetAttributeAsFloat)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetAttributeAsDouble)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetAttributeAsDecimal)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* (AXISCALL* GetAttributeAsString)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetAttributeAsAnyURI)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetAttributeAsQName)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary (AXISCALL* GetAttributeAsHexBinary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary (AXISCALL* GetAttributeAsBase64Binary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetAttributeAsDateTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetAttributeAsDate)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetAttributeAsTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetAttributeAsDuration)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	int (AXISCALL* GetStatus)(void* pObj);
} IWrapperSoapDeSerializerFunctions;

typedef struct { 
	void* _object; /* this will be C++ SoapDeSerializer Object */
	IWrapperSoapDeSerializerFunctions* _functions; /* this is the static function table */
} IWrapperSoapDeSerializer_C;

#ifndef __cplusplus
typedef IWrapperSoapDeSerializer_C IWrapperSoapDeSerializer;
#else
/**
    @class IWrapperSoapDeSerializer
    @brief interface for the IWrapperSoapDeSerializer class.


    @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
class IWrapperSoapDeSerializer : public ISoapDeSerializer
{
public:
	virtual ~IWrapperSoapDeSerializer(){};

	virtual int AXISCALL CheckMessageBody(const AxisChar* pName, const AxisChar* pNamespace)=0;
	/** Method used by wrappers to get a deserialized Array of complex types */
	virtual Axis_Array AXISCALL GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/** Method used by wrappers to get a deserialized Array of basic types */
	virtual Axis_Array AXISCALL GetBasicArray(XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/** Method used by wrappers to get a deserialized single object of complex type */
	virtual void* AXISCALL GetCmplxObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	
	/* Methods used by wrappers to get a deserialized value of basic types */
	virtual int AXISCALL GetElementAsInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__boolean AXISCALL GetElementAsBoolean(const AxisChar* pName, const AxisChar* pNamespace)=0;
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
	virtual xsd__hexBinary AXISCALL GetElementAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__base64Binary AXISCALL GetElementAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsDate(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetElementAsDuration(const AxisChar* pName, const AxisChar* pNamespace)=0;

	virtual int AXISCALL GetAttributeAsInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__boolean AXISCALL GetAttributeAsBoolean(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned int AXISCALL GetAttributeAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual short AXISCALL GetAttributeAsShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned short AXISCALL GetAttributeAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual char AXISCALL GetAttributeAsByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned char AXISCALL GetAttributeAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetAttributeAsLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetAttributeAsInteger(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned long AXISCALL GetAttributeAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual float AXISCALL GetAttributeAsFloat(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetAttributeAsDouble(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetAttributeAsDecimal(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL GetAttributeAsString(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetAttributeAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetAttributeAsQName(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__hexBinary AXISCALL GetAttributeAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__base64Binary AXISCALL GetAttributeAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetAttributeAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetAttributeAsDate(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetAttributeAsTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetAttributeAsDuration(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual int AXISCALL GetStatus()=0;
	
	/* Externalization of deserializer API */
	virtual int SetInputStream(const Ax_soapstream* pInputStream)=0;
	virtual	int Init()=0;
	virtual PROVIDERTYPE GetCurrentProviderType()=0;
	virtual void SetCurrentProviderType(PROVIDERTYPE nType)=0;	
	virtual AXIS_BINDING_STYLE AXISCALL GetStyle()=0;	
	virtual void SetStyle(AXIS_BINDING_STYLE nStyle)=0;
	virtual int GetVersion()=0;
	virtual int GetHeader()=0;	
	    	

	/* following stuff is needed to provide the interface for C web services */
public:
	static IWrapperSoapDeSerializerFunctions ms_VFtable;
	static int AXISCALL s_CheckMessageBody(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((IWrapperSoapDeSerializer*)pObj)->CheckMessageBody(pName, pNamespace);};
	static Axis_Array AXISCALL s_GetCmplxArray(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((IWrapperSoapDeSerializer*)pObj)->GetCmplxArray(pDZFunct, pCreFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
	static Axis_Array AXISCALL s_GetBasicArray(void* pObj, XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((IWrapperSoapDeSerializer*)pObj)->GetBasicArray(nType, pName, pNamespace);};
	static void* AXISCALL s_GetCmplxObject(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((IWrapperSoapDeSerializer*)pObj)->GetCmplxObject(pDZFunct, pCreFunct, pDelFunct, pName, pNamespace);};
	static int AXISCALL s_GetElementAsInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsInt(pName, pNamespace);};
	static xsd__boolean AXISCALL s_GetElementAsBoolean(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsBoolean(pName, pNamespace);};
    static unsigned int AXISCALL s_GetElementAsUnsignedInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsUnsignedInt(pName, pNamespace);};
    static short AXISCALL s_GetElementAsShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsShort(pName, pNamespace);};
    static unsigned short AXISCALL s_GetElementAsUnsignedShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsUnsignedShort(pName, pNamespace);};
    static char AXISCALL s_GetElementAsByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsByte(pName, pNamespace);};
    static unsigned char AXISCALL s_GetElementAsUnsignedByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsUnsignedByte(pName, pNamespace);};
    static long AXISCALL s_GetElementAsLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsLong(pName, pNamespace);};
    static long AXISCALL s_GetElementAsInteger(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsInteger(pName, pNamespace);};
    static unsigned long AXISCALL s_GetElementAsUnsignedLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsUnsignedLong(pName, pNamespace);};
	static float AXISCALL s_GetElementAsFloat(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsFloat(pName, pNamespace);};
    static double AXISCALL s_GetElementAsDouble(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsDouble(pName, pNamespace);};
    static double AXISCALL s_GetElementAsDecimal(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsDouble(pName, pNamespace);};
	static AxisChar* AXISCALL s_GetElementAsString(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsString(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsAnyURI(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsAnyURI(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsQName(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsQName(pName, pNamespace);};
	static xsd__hexBinary AXISCALL s_GetElementAsHexBinary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsHexBinary(pName, pNamespace);};
	static xsd__base64Binary AXISCALL s_GetElementAsBase64Binary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsBase64Binary(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsDateTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsDateTime(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsDate(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsDate(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsTime(pName, pNamespace);};
    static long AXISCALL s_GetElementAsDuration(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetElementAsDuration(pName, pNamespace);};
	static int AXISCALL s_GetAttributeAsInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsInt(pName, pNamespace);};
	static xsd__boolean AXISCALL s_GetAttributeAsBoolean(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsBoolean(pName, pNamespace);};
    static unsigned int AXISCALL s_GetAttributeAsUnsignedInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsUnsignedInt(pName, pNamespace);};
    static short AXISCALL s_GetAttributeAsShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsShort(pName, pNamespace);};
    static unsigned short AXISCALL s_GetAttributeAsUnsignedShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsUnsignedShort(pName, pNamespace);};
    static char AXISCALL s_GetAttributeAsByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsByte(pName, pNamespace);};
    static unsigned char AXISCALL s_GetAttributeAsUnsignedByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsUnsignedByte(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsLong(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsInteger(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsInteger(pName, pNamespace);};
    static unsigned long AXISCALL s_GetAttributeAsUnsignedLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsUnsignedLong(pName, pNamespace);};
	static float AXISCALL s_GetAttributeAsFloat(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsFloat(pName, pNamespace);};
    static double AXISCALL s_GetAttributeAsDouble(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsDouble(pName, pNamespace);};
    static double AXISCALL s_GetAttributeAsDecimal(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsDecimal(pName, pNamespace);};
	static AxisChar* AXISCALL s_GetAttributeAsString(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsString(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsAnyURI(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsAnyURI(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsQName(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsQName(pName, pNamespace);};
	static xsd__hexBinary AXISCALL s_GetAttributeAsHexBinary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsHexBinary(pName, pNamespace);};
	static xsd__base64Binary AXISCALL s_GetAttributeAsBase64Binary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsBase64Binary(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDateTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsDateTime(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDate(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsDate(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsTime(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsDuration(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetAttributeAsDuration(pName, pNamespace);};
	static int AXISCALL s_GetStatus(void* pObj)
	{ return ((IWrapperSoapDeSerializer*)pObj)->GetStatus();};
	static void s_Initialize()
	{
		ms_VFtable.CheckMessageBody = s_CheckMessageBody;
		ms_VFtable.GetCmplxArray = s_GetCmplxArray;
		ms_VFtable.GetBasicArray = s_GetBasicArray;
		ms_VFtable.GetCmplxObject = s_GetCmplxObject;
		ms_VFtable.GetElementAsInt = s_GetElementAsInt;
		ms_VFtable.GetElementAsBoolean = s_GetElementAsBoolean;
		ms_VFtable.GetElementAsUnsignedInt = s_GetElementAsUnsignedInt;
		ms_VFtable.GetElementAsShort = s_GetElementAsShort;
		ms_VFtable.GetElementAsUnsignedShort = s_GetElementAsUnsignedShort;
		ms_VFtable.GetElementAsByte = s_GetElementAsByte;
		ms_VFtable.GetElementAsUnsignedByte = s_GetElementAsUnsignedByte;
		ms_VFtable.GetElementAsLong = s_GetElementAsLong;
		ms_VFtable.GetElementAsInteger = s_GetElementAsInteger;
		ms_VFtable.GetElementAsUnsignedLong = s_GetElementAsUnsignedLong;
		ms_VFtable.GetElementAsFloat = s_GetElementAsFloat;
		ms_VFtable.GetElementAsDouble = s_GetElementAsDouble;
		ms_VFtable.GetElementAsDecimal = s_GetElementAsDecimal;
		ms_VFtable.GetElementAsString = s_GetElementAsString;
		ms_VFtable.GetElementAsAnyURI = s_GetElementAsAnyURI;
		ms_VFtable.GetElementAsQName = s_GetElementAsQName;
		ms_VFtable.GetElementAsHexBinary = s_GetElementAsHexBinary;
		ms_VFtable.GetElementAsBase64Binary = s_GetElementAsBase64Binary;
		ms_VFtable.GetElementAsDateTime = s_GetElementAsDateTime;
		ms_VFtable.GetElementAsDate = s_GetElementAsDate;
		ms_VFtable.GetElementAsTime = s_GetElementAsTime;
		ms_VFtable.GetElementAsDuration = s_GetElementAsDuration;
		ms_VFtable.GetAttributeAsInt = s_GetAttributeAsInt;
		ms_VFtable.GetAttributeAsBoolean = s_GetAttributeAsBoolean;
		ms_VFtable.GetAttributeAsUnsignedInt = s_GetAttributeAsUnsignedInt;
		ms_VFtable.GetAttributeAsShort = s_GetAttributeAsShort;
		ms_VFtable.GetAttributeAsUnsignedShort = s_GetAttributeAsUnsignedShort;
		ms_VFtable.GetAttributeAsByte = s_GetAttributeAsByte;
		ms_VFtable.GetAttributeAsUnsignedByte = s_GetAttributeAsUnsignedByte;
		ms_VFtable.GetAttributeAsLong = s_GetAttributeAsLong;
		ms_VFtable.GetAttributeAsInteger = s_GetAttributeAsInteger;
		ms_VFtable.GetAttributeAsUnsignedLong = s_GetAttributeAsUnsignedLong;
		ms_VFtable.GetAttributeAsFloat = s_GetAttributeAsFloat;
		ms_VFtable.GetAttributeAsDouble = s_GetAttributeAsDouble;
		ms_VFtable.GetAttributeAsDecimal = s_GetAttributeAsDecimal;
		ms_VFtable.GetAttributeAsString = s_GetAttributeAsString;
		ms_VFtable.GetAttributeAsAnyURI = s_GetAttributeAsAnyURI;
		ms_VFtable.GetAttributeAsQName = s_GetAttributeAsQName;
		ms_VFtable.GetAttributeAsHexBinary = s_GetAttributeAsHexBinary;
		ms_VFtable.GetAttributeAsBase64Binary = s_GetAttributeAsBase64Binary;
		ms_VFtable.GetAttributeAsDateTime = s_GetAttributeAsDateTime;
		ms_VFtable.GetAttributeAsDate = s_GetAttributeAsDate;
		ms_VFtable.GetAttributeAsTime = s_GetAttributeAsTime;
		ms_VFtable.GetAttributeAsDuration = s_GetAttributeAsDuration;
		ms_VFtable.GetStatus = s_GetStatus;
	}
};
#endif

#endif /* !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_) */
