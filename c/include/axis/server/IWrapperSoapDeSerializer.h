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

// IWrapperSoapDeSerializer.h: interface for the IWrapperSoapDeSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_)
#define AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_


#include "GDefine.h"
#include "AxisUserAPI.h"
#include "TypeMapping.h"

#ifdef __cplusplus

#include "ISoapDeSerializer.h"
#include <string>
using namespace std;
class IParam;

class IWrapperSoapDeSerializer : public ISoapDeSerializer
{
public:
	virtual ~IWrapperSoapDeSerializer(){};

#else

typedef struct IWrapperSoapDeSerializerTag
{
	void* __vfptr;
} IWrapperSoapDeSerializer;

typedef struct IWrapperSoapDeSerializerXTag
{
	void AXISAPI(destructor,(APINOPARAMS))

#endif
	
	virtual const AxisChar* AXISAPI(GetMethodName,(APINOPARAMS))
//	virtual int AXISAPI(Deserialize,(APIHASPARAMS IParam* pIParam, int bHref));

	/* Method used by wrappers to get a deserialized Array of complex types */
	virtual Axis_Array AXISAPI(GetCmplxArray,(APIHASPARAMS void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI))
	/* Method used by wrappers to get a deserialized Array of basic types */
	virtual Axis_Array AXISAPI(GetBasicArray,(APIHASPARAMS XSDTYPE nType))
	virtual int AXISAPI(GetArraySize,(APINOPARAMS))
	virtual int AXISAPI(GetArray,(APIHASPARAMS Axis_Array* pArray, XSDTYPE nType))
	/* Method used by wrappers to get a deserialized single object of complex type */
	virtual void* AXISAPI(GetObject,(APIHASPARAMS void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pchTypeName, const AxisChar* pchURI))
	
	/* Methods used by wrappers to get a deserialized value of basic types */
	virtual int AXISAPI(GetInt,(APINOPARAMS))
    virtual unsigned int AXISAPI(GetUnsignedInt,(APINOPARAMS))
    virtual short AXISAPI(GetShort,(APINOPARAMS))
    virtual unsigned short AXISAPI(GetUnsignedShort,(APINOPARAMS))
    virtual char AXISAPI(GetByte,(APINOPARAMS))
    virtual unsigned char AXISAPI(GetUnsignedByte,(APINOPARAMS))
    virtual long AXISAPI(GetLong,(APINOPARAMS))
    virtual long AXISAPI(GetInteger,(APINOPARAMS))
    virtual unsigned long AXISAPI(GetUnsignedLong,(APINOPARAMS))
	virtual float AXISAPI(GetFloat,(APINOPARAMS))
    virtual double AXISAPI(GetDouble,(APINOPARAMS))
    virtual double AXISAPI(GetDecimal,(APINOPARAMS))
	virtual const AxisChar* AXISAPI(GetString,(APINOPARAMS))
    virtual const AxisChar* AXISAPI(GetAnyURI,(APINOPARAMS))
    virtual const AxisChar* AXISAPI(GetQName,(APINOPARAMS))
	virtual const AxisChar* AXISAPI(GetHexString,(APINOPARAMS))
	virtual const AxisChar* AXISAPI(GetBase64String,(APINOPARAMS))
    /*return a tm struct which contain year-month-date-hour-
      minute-second*/
    virtual struct tm AXISAPI(GetDateTime,(APINOPARAMS))
    virtual struct tm AXISAPI(GetDate,(APINOPARAMS))
    virtual struct tm AXISAPI(GetTime,(APINOPARAMS))
    virtual long AXISAPI(GetDuration,(APINOPARAMS))
//	virtual IParam* AXISAPI(GetParam,(APINOPARAMS))

#ifdef __cplusplus
};
#else
} IWrapperSoapDeSerializerX;
#endif

#endif // !defined(AFX_IWRAPPERSOAPDESERIALIZER_H__A6C89D23_4098_4A73_BFD7_D8F115AD9BA0__INCLUDED_)
