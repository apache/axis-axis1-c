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

// IWrapperSoapSerializer.h: interface for the IWrapperSoapSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_)
#define AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_

class ISoapMethod;
//class IArrayBean;
class IParam;
union uParamValue;
#include "TypeMapping.h"
#include "ISoapSerializer.h"
#include "IArrayBean.h"

class IWrapperSoapSerializer  : public virtual ISoapSerializer
{
public:	
	virtual int AddOutputParam(const AxisChar* pchName, XSDTYPE nType, long lValue)=0;
	//for basic types
	virtual int AddOutputParam(const AxisChar* pchName, int nValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned int unValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, short sValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned short usValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, long lValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned long ulValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, char cValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned char ucValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, float fValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, double dValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, struct tm tValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, const AxisChar* pStrValue)=0;
	virtual int AddOutputParam(const AxisChar* pchName, const string& sStrValue)=0;
	//for arrays
	virtual int AddOutputParam(const AxisChar* pchName, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI)=0;
	virtual int AddOutputParam(const AxisChar* pchName, const Axis_Array* pArray, XSDTYPE nType)=0;
	//for complex types
	virtual int AddOutputParam(const AxisChar* pchName, void* pObject, void* pDZFunct, void* pDelFunct)=0;
	virtual int createSoapMethod(const AxisChar* sLocalName, const AxisChar* sPrefix, const AxisChar* sURI)=0;
//	virtual IWrapperSoapSerializer& operator<<(const char *cSerialized)=0;
	virtual IWrapperSoapSerializer& operator<<(const AxisChar* cSerialized)=0;
	virtual const AxisChar* getNewNamespacePrefix()=0;
	/* Methods used to serialize arrays */
	virtual int SerializeArray(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI, const AxisChar* pchArrayName)=0;
	virtual int SerializeArray(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pchArrayName)=0;

public: //Basic Type Serializing methods
	virtual const AxisChar* SerializeBasicType(const AxisChar* sName, const AxisChar* sValue, XSDTYPE type=XSD_STRING)=0;
	virtual const AxisChar* SerializeBasicType(const AxisChar* sName, const string sValue, XSDTYPE type=XSD_STRING)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, struct tm tValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, int nValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned int unValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, short sValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned short usValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, char cValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned char ucValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, long lValue, XSDTYPE type=XSD_LONG)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned long ulValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, float fValue)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, double dValue, XSDTYPE type=XSD_DOUBLE)=0;
};

#endif // !defined(AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_)
