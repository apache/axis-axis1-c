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

// IWrapperSoapDeSerializer.h: interface for the IWrapperSoapDeSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_)
#define AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_

#include "ISoapDeSerializer.h"
#include "GDefine.h"
#include "AxisUserAPI.h"
#include <string>
using namespace std;
class IParam;

class IWrapperSoapDeSerializer : public virtual ISoapDeSerializer
{
public:
	virtual const AxisChar* GetMethodName()=0;
	virtual IParam* GetParam()=0;
	virtual int Deserialize(IParam* pIParam, int bHref)=0;
	virtual ~IWrapperSoapDeSerializer() {};

	/* Method used by wrappers to get a deserialized Array of complex types */
	virtual Axis_Array GetArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI)=0;
	/* Method used by wrappers to get a deserialized Array of basic types */
	virtual Axis_Array GetArray(XSDTYPE nType)=0;
	/* Method used by wrappers to get a deserialized single object of complex type */
	virtual void* GetObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pchTypeName, const AxisChar* pchURI)=0;
	
	/* Methods used by wrappers to get a deserialized value of basic types */
	virtual int GetInt() = 0;
    virtual unsigned int GetUnsignedInt() = 0;
    virtual short GetShort() = 0;
    virtual unsigned short GetUnsignedShort() = 0;
    virtual char GetByte() = 0;
    virtual unsigned char GetUnsignedByte() = 0;
    virtual long GetLong() = 0;
    virtual long GetInteger() = 0;
    virtual unsigned long GetUnsignedLong() = 0;
	virtual float GetFloat() = 0;
    virtual double GetDouble() = 0;
    virtual double GetDecimal() = 0;
	virtual const AxisChar* GetString() = 0;
    virtual const AxisChar* GetAnyURI() = 0;
    virtual const AxisChar* GetQName() = 0;
	virtual const AxisChar* GetHexString() = 0;
	virtual const AxisChar* GetBase64String() = 0;
    /*return a tm struct which contain year-month-date-hour-
      minute-second*/
    virtual struct tm GetDateTime() = 0;
    virtual struct tm GetDate() = 0;
    virtual struct tm GetTime() = 0;
    /*return a tm struct which contain years-months-dates-hours-
      minutes-seconds which represents a duration*/
    virtual long GetDuration() = 0;
	virtual void* CreateArray(XSDTYPE nType, int nSize)=0;
	virtual void DeleteArray(void* pArray, XSDTYPE nType)=0;

};

#endif // !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_)
