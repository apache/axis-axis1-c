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

#include <axis/IWrapperSoapDeSerializer.hpp>
AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/TypeMapping.h>
#include <axis/IWrapperSoapDeSerializer.h>

AXISC_STORAGE_CLASS_INFO void axiscDestroyIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	delete dz;
}

AXISC_STORAGE_CLASS_INFO int axiscCheckMessageBody(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->checkMessageBody(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO void * axiscCheckForFault(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->checkForFault(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO Axisc_Array axiscGetCmplxArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented
	Axisc_Array aa;
	memset(&aa,0,sizeof(aa));
	return aa;
}

AXISC_STORAGE_CLASS_INFO Axisc_Array axiscGetBasicArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, AXISC_XSDTYPE nType, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented
	Axisc_Array aa;
	memset(&aa,0,sizeof(aa));
	return aa;
}

AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxObjectIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getCmplxObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscGetElementAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscGetFaultDetailIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, char * * ppcDetail) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getFaultDetail(ppcDetail);
}

AXISC_STORAGE_CLASS_INFO xsdc__boolean axiscGetElementAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return (xsdc__boolean)(dz->getElementAsBoolean(pName,pNamespace));
}

AXISC_STORAGE_CLASS_INFO unsigned int axiscGetElementAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO short axiscGetElementAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned short axiscGetElementAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO char axiscGetElementAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned char axiscGetElementAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__long axiscGetElementAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetElementAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsInteger(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned long axiscGetElementAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO float axiscGetElementAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsFloat(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetElementAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDouble(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetElementAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDecimal(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetElementAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsString(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetElementAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsAnyURI(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetElementAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsQName(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__hexBinary axiscGetElementAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented yet
	xsdc__hexBinary hb;
	memset(&hb,0,sizeof(hb));
	return hb;
}

AXISC_STORAGE_CLASS_INFO xsdc__base64Binary axiscGetElementAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented yet
	xsdc__base64Binary bb;
	memset(&bb,0,sizeof(bb));
	return bb;
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetElementAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDateTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetElementAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDate(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetElementAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetElementAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDuration(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscGetAttributeAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__boolean axiscGetAttributeAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return (xsdc__boolean)(dz->getAttributeAsBoolean(pName,pNamespace));
}

AXISC_STORAGE_CLASS_INFO unsigned int axiscGetAttributeAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO short axiscGetAttributeAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned short axiscGetAttributeAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO char axiscGetAttributeAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned char axiscGetAttributeAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__long axiscGetAttributeAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetAttributeAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsInteger(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO unsigned long axiscGetAttributeAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO float axiscGetAttributeAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsFloat(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetAttributeAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDouble(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO double axiscGetAttributeAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDecimal(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetAttributeAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsString(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetAttributeAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsAnyURI(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO AxiscChar * axiscGetAttributeAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsQName(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__hexBinary axiscGetAttributeAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO not implemented yet
	xsdc__hexBinary hb;
	memset(&hb,0,sizeof(hb));
	return hb;
}

AXISC_STORAGE_CLASS_INFO xsdc__base64Binary axiscGetAttributeAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO not implemented yet
	xsdc__base64Binary bb;
	memset(&bb,0,sizeof(bb));
	return bb;
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetAttributeAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDateTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetAttributeAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDate(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO struct tm axiscGetAttributeAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO long axiscGetAttributeAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDuration(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO int axiscGetStatusIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getStatus();
}

AXISC_STORAGE_CLASS_INFO AXISC_BINDING_STYLE axiscGetStyle(AXISCHANDLE wrapperSoapDeSerializer) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return (AXISC_BINDING_STYLE)(dz->getStyle());
}

AXISC_STORAGE_CLASS_INFO void axiscSetStyle(AXISCHANDLE wrapperSoapDeSerializer, AXISC_BINDING_STYLE nStyle) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	dz->setStyle((AXIS_BINDING_STYLE)nStyle);
}

AXISC_STORAGE_CLASS_INFO int axiscGetVersion(AXISCHANDLE wrapperSoapDeSerializer) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getVersion();
}

AXISC_STORAGE_CLASS_INFO int axiscGetHeaderIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getHeader();
}

AXISC_STORAGE_CLASS_INFO AxiscAnyType * axiscGetAnyObjectIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return (AxiscAnyType*)(dz->getAnyObject());
}

AXISC_STORAGE_CLASS_INFO void axiscGetChardataAs(AXISCHANDLE wrapperSoapDeSerializer, void * pValue, 
	AXISC_XSDTYPE type) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	dz->getChardataAs(pValue,(XSDTYPE)type);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetAttachmentSoapAttachment(AXISCHANDLE wrapperSoapDeSerializer, const char * pcAttachmentid) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return (AXISCHANDLE)(dz->getAttachment(pcAttachmentid));
}

}
