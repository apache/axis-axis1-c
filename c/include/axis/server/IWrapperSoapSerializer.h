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

/* IWrapperSoapSerializer.h: interface for the IWrapperSoapSerializer class.*/

#if !defined(AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_)
#define AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_

#ifdef __cplusplus

#include "AxisUserAPI.h"
#include "TypeMapping.h"
#include "ISoapSerializer.h"

#endif

typedef struct {
	int (AXISCALL* createSoapMethod)(void* pObj, const AxisChar* sLocalName, const AxisChar* sPrefix, const AxisChar* sURI);
	const AxisChar* (AXISCALL* getNewNamespacePrefix)(void* pObj);
	/* for basic types */
	int (AXISCALL* AddOutputParam)(void* pObj, const AxisChar* pchName, void* pValue, XSDTYPE type);
	/* for arrays */
	int (AXISCALL* AddOutputCmplxArrayParam)(void* pObj, const AxisChar* pchName, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI);
	int (AXISCALL* AddOutputBasicArrayParam)(void* pObj, const AxisChar* pchName, const Axis_Array* pArray, XSDTYPE nType);
	/* for complex types */
	int (AXISCALL* AddOutputCmplxParam)(void* pObj, const AxisChar* pchName, void* pObject, void* pDZFunct, void* pDelFunct);
	/* Methods used to serialize arrays */
	int (AXISCALL* SerializeCmplxArray)(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pchTypeName, const AxisChar* pchURI, const AxisChar* pchArrayName);
	int (AXISCALL* SerializeBasicArray)(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pchArrayName);
	/* Basic Type Serializing methods */
	int (AXISCALL* SerializeBasicType)(void* pObj, const AxisChar* sName, void* pValue, XSDTYPE type);
	void (AXISCALL* Serialize)(void* pObj, const char* pFirst, ...);
}IWrapperSoapSerializerBaseFunctions;

#ifndef __cplusplus

typedef struct { 
	void* unused; /* this corresponds to C++ virtual function pointer which is ignored in C */ 
	IWrapperSoapSerializerBaseFunctions* __vfptr;
} IWrapperSoapSerializerBase;

#else

class IWrapperSoapSerializerBase : public ISoapSerializer
{
protected:
	void* __vfptr;
public:
	virtual ~IWrapperSoapSerializerBase(){};
	virtual int AXISCALL createSoapMethod(const AxisChar* sLocalName, const AxisChar* sPrefix, const AxisChar* sURI)=0;
	virtual const AxisChar* AXISCALL getNewNamespacePrefix()=0;
	/* for basic types */
	virtual int AXISCALL AddOutputParam(const AxisChar* pchName, void* pValue, XSDTYPE type)=0;
	/* for arrays */
	virtual int AXISCALL AddOutputCmplxArrayParam(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual int AXISCALL AddOutputBasicArrayParam(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)=0;
	/* for complex types */
	virtual int AXISCALL AddOutputCmplxParam(void* pObject, void* pDZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Methods used to serialize arrays */
	virtual int AXISCALL SerializeCmplxArray(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual int AXISCALL SerializeBasicArray(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)=0;
	/* Basic Type Serializing methods */
	virtual int AXISCALL SerializeBasicType(const AxisChar* sName, void* pValue, XSDTYPE type)=0;
	virtual void AXISCALL Serialize(const char* pFirst, ...)=0;
	/* following stuff is needed to provide the interface for C web services */
public:
	static IWrapperSoapSerializerBaseFunctions ms_VFtable;
	static int AXISCALL s_createSoapMethod(void* pObj, const AxisChar* sLocalName, const AxisChar* sPrefix, const AxisChar* sURI)
	{ return ((IWrapperSoapSerializerBase*)pObj)->createSoapMethod(sLocalName, sPrefix, sURI);};
	static void s_Initialize()
	{
		ms_VFtable.createSoapMethod = s_createSoapMethod;
	}
};

class IWrapperSoapSerializer : public IWrapperSoapSerializerBase
{
public:
	virtual ~IWrapperSoapSerializer(){};
	virtual int AddOutputParam(const AxisChar* pchName, int nValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned int unValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, short sValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned short usValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, long lValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned long ulValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, char cValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, unsigned char ucValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, float fValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, double dValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, struct tm tValue, XSDTYPE type)=0;
	virtual int AddOutputParam(const AxisChar* pchName, const AxisChar* pStrValue, XSDTYPE type)=0;
	/* Basic Type Serializing methods */
	virtual const AxisChar* SerializeBasicType(const AxisChar* sName, const AxisChar* sValue, XSDTYPE type)=0;
	virtual const AxisChar* SerializeBasicType(const AxisChar* sName, const string sValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, struct tm tValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, int nValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned int unValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, short sValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned short usValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, char cValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned char ucValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, long lValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, unsigned long ulValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, float fValue, XSDTYPE type)=0;
    virtual const AxisChar* SerializeBasicType(const AxisChar* sName, double dValue, XSDTYPE type)=0;
	virtual IWrapperSoapSerializer& operator<<(const AxisChar* cSerialized)=0;
	virtual int AddOutputParam(const AxisChar* pchName, const string& pStrValue, XSDTYPE type)=0;
};
#endif
#endif /* !defined(AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_) */
