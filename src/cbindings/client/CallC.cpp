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

#include <axis/client/Call.hpp>

AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/SoapEnvVersions.h>
#include <axis/TypeMapping.h>
#include <axis/WSDDDefines.h>
#include <axis/client/Call.h>

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateCall() {
	Call *c = new Call();
	return (AXISCHANDLE)c;
}

AXISC_STORAGE_CLASS_INFO void axiscDestroyCall(AXISCHANDLE call) {
	Call *c = (Call*)call;
	delete c;
}

AXISC_STORAGE_CLASS_INFO void axiscSetSOAPVersionCall(AXISCHANDLE call, AXISC_SOAP_VERSION version) {
	Call *c = (Call*)call;
	c->setSOAPVersion((SOAP_VERSION)version);
}

AXISC_STORAGE_CLASS_INFO int axiscSetTransportPropertyCall(AXISCHANDLE call, AXISC_TRANSPORT_INFORMATION_TYPE type, 
	const char * value) {
	Call *c = (Call*)call;
	return c->setTransportProperty((AXIS_TRANSPORT_INFORMATION_TYPE)type, value);
}

AXISC_STORAGE_CLASS_INFO int axiscSetHandlerPropertyCall(AXISCHANDLE call, AxiscChar * name, 
	void * value, int len) {
	Call *c = (Call*)call;
	return c->setHandlerProperty(name,value,len);
}

AXISC_STORAGE_CLASS_INFO int axiscSetProtocolCall(AXISCHANDLE call, AXISC_PROTOCOL_TYPE protocol) {
	Call *c = (Call*)call;
	return c->setProtocol((AXIS_PROTOCOL_TYPE)protocol);
}

AXISC_STORAGE_CLASS_INFO AXISC_PROTOCOL_TYPE axiscGetProtocol(AXISCHANDLE call) {
	Call *c = (Call*)call;
	return (AXISC_PROTOCOL_TYPE)(c->getProtocol());
}

AXISC_STORAGE_CLASS_INFO int axiscUnInitializeCall(AXISCHANDLE call) {
	Call *c = (Call*)call;
	return c->unInitialize();
}

AXISC_STORAGE_CLASS_INFO int axiscInitializeCall(AXISCHANDLE call, AXISC_PROVIDERTYPE nStyle) {
	Call *c = (Call*)call;
	return c->initialize((PROVIDERTYPE)nStyle);
}

AXISC_STORAGE_CLASS_INFO int axiscInvokeCall(AXISCHANDLE call) {
	Call *c = (Call*)call;
	return c->invoke();
}

AXISC_STORAGE_CLASS_INFO void axiscAddCmplxParameterCall(AXISCHANDLE call, void * pObject, 
	void * pSZFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	c->addCmplxParameter(pObject,pSZFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO void axiscAddCmplxArrayParameterCall(AXISCHANDLE call, Axisc_Array * pArray, 
	void * pSZFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	c->addCmplxArrayParameter((Axis_Array*)pArray,pSZFunct,pDelFunct,pSizeFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO void axiscAddBasicArrayParameterCall(AXISCHANDLE call, Axisc_Array * pArray, 
	AXISC_XSDTYPE nType, const AxiscChar * pName) {
	Call *c = (Call*)call;
	c->addBasicArrayParameter((Axis_Array*)pArray, (XSDTYPE)nType, pName);
}

AXISC_STORAGE_CLASS_INFO void axiscAddParameterCall(AXISCHANDLE call, void * pValue, 
	const char * pchName, AXISC_XSDTYPE nType) {
	Call *c = (Call*)call;
	c->addParameter(pValue,pchName,(XSDTYPE)nType);
}

AXISC_STORAGE_CLASS_INFO void axiscSetOperationCall(AXISCHANDLE call, const char * pchOperation, 
	const char * pchNamespace) {
	Call *c = (Call*)call;
	c->setOperation(pchOperation,pchNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscSetEndpointURICall(AXISCHANDLE call, const char * pchEndpointURI) {
	Call *c = (Call*)call;
	return c->setEndpointURI(pchEndpointURI);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateHeaderBlockCall(AXISCHANDLE call, AxiscChar * pachLocalName, 
	AxiscChar * pachUri, AxiscChar * pachPrefix) {
	Call *c = (Call*)call;
	return (AXISCHANDLE)(c->createHeaderBlock(pachLocalName, pachUri, pachPrefix));
}

AXISC_STORAGE_CLASS_INFO int axiscGetElementAsIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscGetFaultDetailCall(AXISCHANDLE call, char * * ppcDetail) {
	Call *c = (Call*)call;
	return c->getFaultDetail(ppcDetail);
}

AXISC_STORAGE_CLASS_INFO xsdc__boolean axiscGetElementAsBooleanCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return (xsdc__boolean)(c->getElementAsBoolean(pName,pNamespace));
}

AXISC_STORAGE_CLASS_INFO unsigned int axiscGetElementAsUnsignedIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsUnsignedInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO short axiscGetElementAsShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned short axiscGetElementAsUnsignedShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsUnsignedShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO char axiscGetElementAsByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned char axiscGetElementAsUnsignedByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsUnsignedByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__long axiscGetElementAsLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return (xsd__long)(c->getElementAsLong(pName,pNamespace));
}

AXISC_STORAGE_CLASS_INFO long axiscGetElementAsIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsInteger(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned long axiscGetElementAsUnsignedLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsUnsignedLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO float axiscGetElementAsFloatCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsFloat(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetElementAsDoubleCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsDouble(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetElementAsDecimalCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsDecimal(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetElementAsStringCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsString(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetElementAsAnyURICall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsAnyURI(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetElementAsQNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsQName(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__hexBinary axiscGetElementAsHexBinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	//TODO: Unimplemented
	xsdc__hexBinary hb;
	memset(&hb,0,sizeof(hb));
	return hb;
}

AXISC_STORAGE_CLASS_INFO xsdc__base64Binary axiscGetElementAsBase64BinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	//TODO: Unimplemented
	xsdc__base64Binary bb;
	memset(&bb,0,sizeof(bb));
	return bb;
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetElementAsDateTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsDateTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetElementAsDateCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsDate(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetElementAsTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetElementAsDurationCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getElementAsDuration(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscGetAttributeAsIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__boolean axiscGetAttributeAsBooleanCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return (xsdc__boolean)(c->getAttributeAsBoolean(pName,pNamespace));
}

AXISC_STORAGE_CLASS_INFO unsigned int axiscGetAttributeAsUnsignedIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsUnsignedInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO short axiscGetAttributeAsShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned short axiscGetAttributeAsUnsignedShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsUnsignedShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO char axiscGetAttributeAsByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned char axiscGetAttributeAsUnsignedByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsUnsignedByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetAttributeAsLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetAttributeAsIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsInteger(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned long axiscGetAttributeAsUnsignedLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsUnsignedLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO float axiscGetAttributeAsFloatCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsFloat(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetAttributeAsDoubleCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsDouble(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetAttributeAsDecimalCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsDecimal(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetAttributeAsStringCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsString(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetAttributeAsAnyURICall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsAnyURI(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetAttributeAsQNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsQName(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__hexBinary axiscGetAttributeAsHexBinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	//TODO: Unimplemented
	xsdc__hexBinary hb;
	memset(&hb,0,sizeof(hb));
	return hb;
}

AXISC_STORAGE_CLASS_INFO xsdc__base64Binary axiscGetAttributeAsBase64BinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	//TODO: Unimplemented
	xsdc__base64Binary bb;
	memset(&bb,0,sizeof(bb));
	return bb;
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetAttributeAsDateTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsDateTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetAttributeAsDateCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsDate(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetAttributeAsTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetAttributeAsDurationCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getAttributeAsDuration(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxObjectCall(AXISCHANDLE call, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getCmplxObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO Axisc_Array axiscGetCmplxArrayCall(AXISCHANDLE call, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	//TODO: Unimplemented
	Axisc_Array aa;
	memset(&aa,0,sizeof(aa));
	return aa;
}

AXISC_STORAGE_CLASS_INFO Axisc_Array axiscGetBasicArrayCall(AXISCHANDLE call, AXISC_XSDTYPE nType, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	//TODO: Unimplemented
	Axisc_Array aa;
	memset(&aa,0,sizeof(aa));
	return aa;
}

AXISC_STORAGE_CLASS_INFO int axiscCheckMessageCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->checkMessage(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO void * axiscCheckFaultCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->checkFault(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscGetStatusCall(AXISCHANDLE call) {
	Call *c = (Call*)call;
	return c->getStatus();
}


AXISC_STORAGE_CLASS_INFO void axiscSetProxyCall(AXISCHANDLE call, const char * pcProxyHost, 
	unsigned int uiProxyPort) {
	Call *c = (Call*)call;
	c->setProxy(pcProxyHost,uiProxyPort);
}

AXISC_STORAGE_CLASS_INFO AxiscAnyType * axiscGetAnyObjectCall(AXISCHANDLE call) {
	Call *c = (Call*)call;
	return (AxiscAnyType*)(c->getAnyObject());
}

AXISC_STORAGE_CLASS_INFO int axiscAddAnyObjectCall(AXISCHANDLE call, AxiscAnyType * pAnyObject) {
	Call *c = (Call*)call;
	return c->addAnyObject((AnyType*)pAnyObject);
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetNamespacePrefixCall(AXISCHANDLE call, const AxiscChar * pNamespace) {
	Call *c = (Call*)call;
	return c->getNamespacePrefix(pNamespace);
}

}