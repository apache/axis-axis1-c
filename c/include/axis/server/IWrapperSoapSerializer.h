/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#if !defined(_IWRAPPERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IWRAPPERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_

#ifdef __cplusplus

#include "AxisUserAPI.h"
#include "TypeMapping.h"
#include "ISoapSerializer.h"
#include "WSDDDefines.h"
#include "Packet.h"

#endif

typedef struct {
	int (AXISCALL* createSoapMethod)(void* pObj, const AxisChar* sLocalName, const AxisChar* sURI);
	const AxisChar* (AXISCALL* getNamespacePrefix)(void* pObj, const AxisChar* pNamespace);
	void (AXISCALL* removeNamespacePrefix)(void* pObj, const AxisChar* pNamespace);
	/* for basic types */
	int (AXISCALL* addOutputParam)(void* pObj, const AxisChar* pchName, void* pValue, XSDTYPE type);
	/* for arrays */
	int (AXISCALL* addOutputCmplxArrayParam)(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	int (AXISCALL* addOutputBasicArrayParam)(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName);
	/* for complex types */
	int (AXISCALL* addOutputCmplxParam)(void* pObj, void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Methods used to serialize arrays */
	int (AXISCALL* serializeCmplxArray)(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	int (AXISCALL* serializeBasicArray)(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName);
	/* Basic Type Serializing methods */
	int (AXISCALL* serializeAsElement)(void* pObj, const AxisChar* sName, void* pValue, XSDTYPE type);
	int (AXISCALL* serializeAsAttribute)(void* pObj, const AxisChar* sName, const AxisChar* pNamespace, void* pValue, XSDTYPE type);
	void (AXISCALL* serialize)(void* pObj, const char* pFirst);
	void (AXISCALL* serializeStartElementOfType)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace, const AxisChar* pPrefix);
	void (AXISCALL* serializeEndElementOfType)(void* pObj, const AxisChar* pName);
}IWrapperSoapSerializerFunctions;

typedef struct { 
	void* _object; /* this will be C++ SoapSerializer Object */
	IWrapperSoapSerializerFunctions* _functions; /* this is the static function table */
} IWrapperSoapSerializer_C;

#ifndef __cplusplus
typedef IWrapperSoapSerializer_C IWrapperSoapSerializer;
#else
/**
    @class IWrapperSoapSerializer
    @brief interface for the IWrapperSoapSerializer class.


    @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)

*/
class IWrapperSoapSerializer : public ISoapSerializer
{
public:
	virtual ~IWrapperSoapSerializer(){};
	virtual int AXISCALL createSoapMethod(const AxisChar* sLocalName, const AxisChar* sURI)=0;
	virtual const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace)=0;
	virtual void AXISCALL removeNamespacePrefix(const AxisChar* pNamespace)=0;
	/* for basic types */
	virtual int AXISCALL addOutputParam(const AxisChar* pchName, void* pValue, XSDTYPE type)=0;
	/* for arrays */
	virtual int AXISCALL addOutputCmplxArrayParam(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual int AXISCALL addOutputBasicArrayParam(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)=0;
	/* for complex types */
	virtual int AXISCALL addOutputCmplxParam(void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Methods used to serialize arrays */
	virtual int AXISCALL serializeCmplxArray(const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual int AXISCALL serializeBasicArray(const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)=0;
	/* Basic Type Serializing methods */
	virtual int AXISCALL serializeAsElement(const AxisChar* sName, void* pValue, XSDTYPE type)=0;
	virtual int AXISCALL serializeAsAttribute(const AxisChar* sName, const AxisChar* pNamespace, void* pValue, XSDTYPE type)=0;
	virtual void AXISCALL serialize(const char* pFirst, ...)=0;
	/* following two functions are needed by serializer functions of complex types for RPC style web services */
	virtual void AXISCALL serializeStartElementOfType(const AxisChar* pName, const AxisChar* pNamespace, const AxisChar* pPrefix)=0;
	virtual void AXISCALL serializeEndElementOfType(const AxisChar* pName)=0;

	/* Externalization of serializer API */
	virtual int setOutputStream(const Ax_soapstream* pStream)=0;
	virtual void markEndOfStream()=0;	
	virtual	int init()=0;	
	virtual PROVIDERTYPE getCurrentProviderType()=0;
	virtual void setCurrentProviderType(PROVIDERTYPE nType)=0;	
	virtual void setStyle(AXIS_BINDING_STYLE nStyle)=0;
	virtual AXIS_BINDING_STYLE getStyle()=0;

	/* following stuff is needed to provide the interface for C web services */
public:
	static IWrapperSoapSerializerFunctions ms_VFtable;
	static int AXISCALL s_CreateSoapMethod(void* pObj, const AxisChar* sLocalName, const AxisChar* sURI)
	{ return ((IWrapperSoapSerializer*)pObj)->createSoapMethod(sLocalName, sURI);};
	static const AxisChar* AXISCALL s_GetNamespacePrefix(void* pObj, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->getNamespacePrefix(pNamespace);};
	static void AXISCALL s_RemoveNamespacePrefix(void* pObj, const AxisChar* pNamespace)
	{ ((IWrapperSoapSerializer*)pObj)->removeNamespacePrefix(pNamespace);};
	static int AXISCALL s_AddOutputParam(void* pObj, const AxisChar* pchName, void* pValue, XSDTYPE type)
	{ return ((IWrapperSoapSerializer*)pObj)->addOutputParam(pchName, pValue, type);};
	static int AXISCALL s_AddOutputCmplxArrayParam(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->addOutputCmplxArrayParam(pArray, pSZFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
	static int AXISCALL s_AddOutputBasicArrayParam(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
	{ return ((IWrapperSoapSerializer*)pObj)->addOutputBasicArrayParam(pArray, nType, pName);};
	static int AXISCALL s_AddOutputCmplxParam(void* pObj, void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->addOutputCmplxParam(pObject, pSZFunct, pDelFunct, pName, pNamespace);};
	static int AXISCALL s_SerializeCmplxArray(void* pObj, const Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((IWrapperSoapSerializer*)pObj)->serializeCmplxArray(pArray, pSZFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
	static int AXISCALL s_SerializeBasicArray(void* pObj, const Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
	{ return ((IWrapperSoapSerializer*)pObj)->serializeBasicArray(pArray, nType, pName);};
	static int AXISCALL s_SerializeAsElement(void* pObj, const AxisChar* sName, void* pValue, XSDTYPE type)
	{ return ((IWrapperSoapSerializer*)pObj)->serializeAsElement(sName, pValue, type);};
	static int AXISCALL s_SerializeAsAttribute(void* pObj, const AxisChar* sName, const AxisChar* pNamespace, void* pValue, XSDTYPE type)
	{ return ((IWrapperSoapSerializer*)pObj)->serializeAsAttribute(sName, pNamespace, pValue, type);};
	static void AXISCALL s_Serialize(void* pObj, const char* pFirst)
	{ ((IWrapperSoapSerializer*)pObj)->serialize(pFirst, 0);};
	static void AXISCALL s_SerializeStartElementOfType(void* pObj, const AxisChar* pName, const AxisChar* pNamespace, const AxisChar* pPrefix)
	{ ((IWrapperSoapSerializer*)pObj)->serializeStartElementOfType(pName, pNamespace, pPrefix);}
	static void AXISCALL s_SerializeEndElementOfType(void* pObj, const AxisChar* pName)
	{ ((IWrapperSoapSerializer*)pObj)->serializeEndElementOfType(pName);}
	static void s_Initialize()
	{
		ms_VFtable.createSoapMethod = s_CreateSoapMethod;
		ms_VFtable.getNamespacePrefix = s_GetNamespacePrefix;
		ms_VFtable.removeNamespacePrefix = s_RemoveNamespacePrefix;
		ms_VFtable.addOutputParam = s_AddOutputParam;
		ms_VFtable.addOutputCmplxArrayParam = s_AddOutputCmplxArrayParam;
		ms_VFtable.addOutputBasicArrayParam = s_AddOutputBasicArrayParam;
		ms_VFtable.addOutputCmplxParam = s_AddOutputCmplxParam;
		ms_VFtable.serializeCmplxArray = s_SerializeCmplxArray;
		ms_VFtable.serializeBasicArray = s_SerializeBasicArray;
		ms_VFtable.serializeAsElement = s_SerializeAsElement;
		ms_VFtable.serializeAsAttribute = s_SerializeAsAttribute;
		ms_VFtable.serialize = s_Serialize;
		ms_VFtable.serializeStartElementOfType = s_SerializeStartElementOfType;
		ms_VFtable.serializeEndElementOfType = s_SerializeEndElementOfType;
	}
};

#endif
#endif /* !defined(_IWRAPPERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_) */
