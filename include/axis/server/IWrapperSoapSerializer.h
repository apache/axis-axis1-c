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

// IWrapperSoapSerializer.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_)
#define AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_

#ifdef __cplusplus

#include "AxisUserAPI.h"
#include "TypeMapping.h"
#include "ISoapSerializer.h"

#endif

typedef struct {
	int (AXISCALL* CreateSoapMethod)(void* pObj, const AxisChar* sLocalName, const AxisChar* sURI);
	const AxisChar* (AXISCALL* GetNamespacePrefix)(void* pObj, const AxisChar* pNamespace);
	void (AXISCALL* RemoveNamespacePrefix)(void* pObj, const AxisChar* pNamespace);
	/* for basic types */
	int (AXISCALL* AddOutputParam)(void* pObj, const AxisChar* pchName, void* pValue, XSDTYPE type);
	/* for arrays */
	int (AXISCALL* AddOutputCmplxArrayParam)(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	int (AXISCALL* AddOutputBasicArrayParam)(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName);
	/* for complex types */
	int (AXISCALL* AddOutputCmplxParam)(void* pObj, void* pObject, void* pDZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Methods used to serialize arrays */
	int (AXISCALL* SerializeCmplxArray)(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	int (AXISCALL* SerializeBasicArray)(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName);
	/* Basic Type Serializing methods */
	int (AXISCALL* SerializeAsElement)(void* pObj, const AxisChar* sName, void* pValue, XSDTYPE type);
	int (AXISCALL* SerializeAsAttribute)(void* pObj, const AxisChar* sName, const AxisChar* pNamespace, void* pValue, XSDTYPE type);
	void (AXISCALL* Serialize)(void* pObj, const char* pFirst, ...);
}IWrapperSoapSerializerFunctions;

#ifndef __cplusplus

typedef struct { 
	void* unused; /* this corresponds to C++ virtual function pointer which is ignored in C */ 
	IWrapperSoapSerializerFunctions* __vfptr;
} IWrapperSoapSerializer;

#else
/**
    @class IWrapperSoapSerializer
    @brief interface for the IWrapperSoapSerializer class.


    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)

*/
class IWrapperSoapSerializer : public ISoapSerializer
{
protected:
	void* __vfptr;
public:
	virtual ~IWrapperSoapSerializer(){};
	virtual int AXISCALL CreateSoapMethod(const AxisChar* sLocalName, const AxisChar* sURI)=0;
	virtual const AxisChar* AXISCALL GetNamespacePrefix(const AxisChar* pNamespace)=0;
	virtual void AXISCALL RemoveNamespacePrefix(const AxisChar* pNamespace)=0;
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
	virtual int AXISCALL SerializeAsElement(const AxisChar* sName, void* pValue, XSDTYPE type)=0;
	virtual int AXISCALL SerializeAsAttribute(const AxisChar* sName, const AxisChar* pNamespace, void* pValue, XSDTYPE type)=0;
	virtual void AXISCALL Serialize(const char* pFirst, ...)=0;
	/* following stuff is needed to provide the interface for C web services */
public:
	static IWrapperSoapSerializerFunctions ms_VFtable;
	static int AXISCALL s_CreateSoapMethod(void* pObj, const AxisChar* sLocalName, const AxisChar* sURI)
	{ return ((IWrapperSoapSerializer*)pObj)->CreateSoapMethod(sLocalName, sURI);};
	static const AxisChar* AXISCALL s_GetNamespacePrefix(void* pObj, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->GetNamespacePrefix(pNamespace);};
	static void AXISCALL s_RemoveNamespacePrefix(void* pObj, const AxisChar* pNamespace)
	{ ((IWrapperSoapSerializer*)pObj)->RemoveNamespacePrefix(pNamespace);};
	static int AXISCALL s_AddOutputParam(void* pObj, const AxisChar* pchName, void* pValue, XSDTYPE type)
	{ return ((IWrapperSoapSerializer*)pObj)->AddOutputParam(pchName, pValue, type);};
	static int AXISCALL s_AddOutputCmplxArrayParam(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->AddOutputCmplxArrayParam(pArray, pSZFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
	static int AXISCALL s_AddOutputBasicArrayParam(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
	{ return ((IWrapperSoapSerializer*)pObj)->AddOutputBasicArrayParam(pArray, nType, pName);};
	static int AXISCALL s_AddOutputCmplxParam(void* pObj, void* pObject, void* pDZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->AddOutputCmplxParam(pObject, pDZFunct, pDelFunct, pName, pNamespace);};
	static int AXISCALL s_SerializeCmplxArray(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->SerializeCmplxArray(pArray, pSZFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
	static int AXISCALL s_SerializeBasicArray(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
	{ return ((IWrapperSoapSerializer*)pObj)->SerializeBasicArray(pArray, nType, pName);};
	static int AXISCALL s_SerializeAsElement(void* pObj, const AxisChar* sName, void* pValue, XSDTYPE type)
	{ return ((IWrapperSoapSerializer*)pObj)->SerializeAsElement(sName, pValue, type);};
	static int AXISCALL s_SerializeAsAttribute(void* pObj, const AxisChar* sName, const AxisChar* pNamespace, void* pValue, XSDTYPE type)
	{ return ((IWrapperSoapSerializer*)pObj)->SerializeAsAttribute(sName, pNamespace, pValue, type);};
	static void AXISCALL s_Serialize(void* pObj, const char* pFirst, ...)
	{ ((IWrapperSoapSerializer*)pObj)->Serialize(pFirst);};
	static void s_Initialize()
	{
		ms_VFtable.CreateSoapMethod = s_CreateSoapMethod;
		ms_VFtable.GetNamespacePrefix = s_GetNamespacePrefix;
		ms_VFtable.RemoveNamespacePrefix = s_RemoveNamespacePrefix;
		ms_VFtable.AddOutputParam = s_AddOutputParam;
		ms_VFtable.AddOutputCmplxArrayParam = s_AddOutputCmplxArrayParam;
		ms_VFtable.AddOutputBasicArrayParam = s_AddOutputBasicArrayParam;
		ms_VFtable.AddOutputCmplxParam = s_AddOutputCmplxParam;
		ms_VFtable.SerializeCmplxArray = s_SerializeCmplxArray;
		ms_VFtable.SerializeBasicArray = s_SerializeBasicArray;
		ms_VFtable.SerializeAsElement = s_SerializeAsElement;
		ms_VFtable.SerializeAsAttribute = s_SerializeAsAttribute;
		ms_VFtable.Serialize = s_Serialize;
	}
};

#endif
#endif /* !defined(AFX_IWRAPPERSOAPSERIALIZER_H__D3E794EC_8A67_4E0E_BE28_583DCDCE1C42__INCLUDED_) */
