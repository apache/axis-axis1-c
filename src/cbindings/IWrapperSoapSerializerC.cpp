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

#include <axis/IWrapperSoapSerializer.hpp>
#include "../soap/SoapSerializer.h"
AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/TypeMapping.h>
#include <axis/WSDDDefines.h>
#include <axis/IWrapperSoapSerializer.h>

AXISC_STORAGE_CLASS_INFO void axiscDestroyIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	delete sz;
}

AXISC_STORAGE_CLASS_INFO int axiscCreateSoapMethod(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sLocalName, 
	const AxiscChar * sURI) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->createSoapMethod(sLocalName,sURI);
}

AXISC_STORAGE_CLASS_INFO int axiscCreateSoapFault(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sLocalName, 
	const AxiscChar * sURI, const AxiscChar * sFaultCode, 
	const AxiscChar * sFaultString) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->createSoapFault(sLocalName,sURI,sFaultCode,sFaultString);
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetNamespacePrefixIWrapperSoapSerializer(
	AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pNamespace) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->getNamespacePrefix(pNamespace);
}

AXISC_STORAGE_CLASS_INFO void axiscRemoveNamespacePrefix(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pNamespace) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	sz->removeNamespacePrefix(pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscAddOutputParam(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pchName, 
	void * pValue, AXISC_XSDTYPE type) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->addOutputParam(pchName,pValue,(XSDTYPE)type);
}

AXISC_STORAGE_CLASS_INFO int axiscAddOutputCmplxArrayParam(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	void * pSZFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->addOutputCmplxArrayParam((const Axis_Array*)pArray,pSZFunct,pDelFunct,pSizeFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscAddOutputBasicArrayParam(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	AXISC_XSDTYPE nType, const AxiscChar * pName) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->addOutputBasicArrayParam((const Axis_Array*)pArray,(XSDTYPE)nType,pName);
}

AXISC_STORAGE_CLASS_INFO int axiscAddOutputCmplxParam(AXISCHANDLE wrapperSoapSerializer, void * pObject, 
	void * pSZFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->addOutputCmplxParam(pObject,pSZFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscAddFaultDetail(AXISCHANDLE wrapperSoapSerializer, void * pObject, 
	void * pSZFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->addFaultDetail(pObject,pSZFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscSerializeCmplxArray(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	void * pSZFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->serializeCmplxArray((const Axis_Array*)pArray,pSZFunct,pDelFunct,pSizeFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscSerializeBasicArray(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	const AxiscChar * pNamespace,AXISC_XSDTYPE nType, const AxiscChar * pName) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->serializeBasicArray((const Axis_Array*)pArray,pNamespace,(XSDTYPE)nType,pName);
}

AXISC_STORAGE_CLASS_INFO int axiscSerializeAsElement(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sName, 
	const AxiscChar * pNamespace, void * pValue, AXISC_XSDTYPE type) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->serializeAsElement(sName,pValue,(XSDTYPE)type);
}

AXISC_STORAGE_CLASS_INFO int axiscSerializeAsAttribute(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sName, 
	const AxiscChar * pNamespace, void * pValue, AXISC_XSDTYPE type) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->serializeAsAttribute(sName,pNamespace,pValue,(XSDTYPE)type);
}

AXISC_STORAGE_CLASS_INFO void axiscSerializeStartElementOfType(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace, const AxiscChar * pPrefix) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	sz->serializeStartElementOfType(pName,pNamespace,pPrefix);
}

AXISC_STORAGE_CLASS_INFO void axiscSerializeEndElementOfType(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pName) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	sz->serializeEndElementOfType(pName);
}

AXISC_STORAGE_CLASS_INFO AXISC_PROVIDERTYPE axiscGetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return (AXISC_PROVIDERTYPE)(sz->getCurrentProviderType());
}

AXISC_STORAGE_CLASS_INFO void axiscSetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer, AXISC_PROVIDERTYPE nType) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	sz->setCurrentProviderType((PROVIDERTYPE)nType);
}

AXISC_STORAGE_CLASS_INFO int axiscAddOutputAnyObject(AXISCHANDLE wrapperSoapSerializer, AxiscAnyType * pAnyObject) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->addOutputAnyObject((AnyType*)pAnyObject);
}

AXISC_STORAGE_CLASS_INFO int axiscSerializeAnyObject(AXISCHANDLE wrapperSoapSerializer, AxiscAnyType * pAnyObject) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->serializeAnyObject((AnyType*)pAnyObject);
}

AXISC_STORAGE_CLASS_INFO int axiscSerializeAsChardata(AXISCHANDLE wrapperSoapSerializer, void * pValue, 
	AXISC_XSDTYPE type) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return sz->serializeAsChardata(pValue,(XSDTYPE)type);
}

AXISC_STORAGE_CLASS_INFO void axiscAddAttachment(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	AXISCHANDLE objAttach) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	sz->addAttachment(achId,(ISoapAttachment*)objAttach);
}

AXISC_STORAGE_CLASS_INFO void axiscAddAttachmentBody(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	xsdc__base64Binary * pAttchBody) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	sz->addAttachmentBody(achId,(xsd__base64Binary*)pAttchBody);
}

AXISC_STORAGE_CLASS_INFO void axiscAddAttachmentHeader(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	const AxiscChar * achHeaderName, const AxiscChar * achHeaderValue) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	sz->addAttachmentHeader(achId,achHeaderName,achHeaderValue);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateSoapAttachementSoapAttachment(AXISCHANDLE wrapperSoapSerializer) {
	IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;
	return (AXISCHANDLE)(sz->createSoapAttachement());
}

AXISC_STORAGE_CLASS_INFO void axiscSerialize(AXISCHANDLE wrapperSoapSerializer, const char *pFirst, ...) {
	SoapSerializer *sz = (SoapSerializer*)wrapperSoapSerializer;
	va_list vList;
	va_start( vList, pFirst );
	sz->serializeVargs(pFirst,vList);
	va_end( vList);
}

}
