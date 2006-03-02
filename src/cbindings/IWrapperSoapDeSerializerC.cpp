/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

AXISC_STORAGE_CLASS_INFO Axisc_Array* axiscGetCmplxArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, Axisc_Array * pArray, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented
	Axisc_Array* aa = new Axisc_Array();
	memset(aa,0,sizeof(aa));
	return aa;
}

AXISC_STORAGE_CLASS_INFO Axisc_Array* axiscGetBasicArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, AXISC_XSDTYPE nType, 
	const AxiscChar * pName, const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented
	Axisc_Array* aa = new Axisc_Array();
	memset(aa,0,sizeof(aa));
	return aa;
}

AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxObjectIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getCmplxObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__int * axiscGetElementAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsInt(pName,pNamespace);
}

/*AXISC_STORAGE_CLASS_INFO int axiscGetFaultDetailIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, char * * ppcDetail) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getFaultDetail(ppcDetail);
}*/

AXISC_STORAGE_CLASS_INFO xsdc__boolean * axiscGetElementAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return (xsdc__boolean *)(dz->getElementAsBoolean(pName,pNamespace));
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedInt * axiscGetElementAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__short * axiscGetElementAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedShort * axiscGetElementAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__byte * axiscGetElementAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedByte * axiscGetElementAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__long * axiscGetElementAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__integer * axiscGetElementAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsInteger(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedLong * axiscGetElementAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsUnsignedLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__float * axiscGetElementAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsFloat(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__double * axiscGetElementAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDouble(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__decimal * axiscGetElementAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDecimal(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__string axiscGetElementAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsString(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__anyURI axiscGetElementAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsAnyURI(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__QName axiscGetElementAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsQName(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__hexBinary * axiscGetElementAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented yet
	xsdc__hexBinary * hb = new xsdc__hexBinary();
	memset(hb,0,sizeof(hb));
	return hb;
}

AXISC_STORAGE_CLASS_INFO xsdc__base64Binary * axiscGetElementAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO: not implemented yet
	xsdc__base64Binary * bb = new xsdc__base64Binary();
	memset(bb,0,sizeof(bb));
	return bb;
}

AXISC_STORAGE_CLASS_INFO xsdc__dateTime * axiscGetElementAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDateTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__date * axiscGetElementAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDate(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__time * axiscGetElementAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__duration * axiscGetElementAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getElementAsDuration(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__int * axiscGetAttributeAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__boolean * axiscGetAttributeAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return (xsdc__boolean *)(dz->getAttributeAsBoolean(pName,pNamespace));
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedInt * axiscGetAttributeAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedInt(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__short * axiscGetAttributeAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedShort * axiscGetAttributeAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedShort(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__byte * axiscGetAttributeAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedByte * axiscGetAttributeAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedByte(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__long * axiscGetAttributeAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__integer * axiscGetAttributeAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsInteger(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__unsignedLong * axiscGetAttributeAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsUnsignedLong(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__float * axiscGetAttributeAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsFloat(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__double * axiscGetAttributeAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDouble(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__decimal * axiscGetAttributeAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDecimal(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__string axiscGetAttributeAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsString(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__anyURI axiscGetAttributeAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsAnyURI(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__QName axiscGetAttributeAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsQName(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__hexBinary * axiscGetAttributeAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO not implemented yet
	xsdc__hexBinary * hb = new xsdc__hexBinary();
	memset(hb,0,sizeof(hb));
	return hb;
}

AXISC_STORAGE_CLASS_INFO xsdc__base64Binary * axiscGetAttributeAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	// TODO not implemented yet
	xsdc__base64Binary * bb = new xsdc__base64Binary();
	memset(bb,0,sizeof(bb));
	return bb;
}

AXISC_STORAGE_CLASS_INFO xsdc__dateTime * axiscGetAttributeAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDateTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__date * axiscGetAttributeAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsDate(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__time * axiscGetAttributeAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace) {
	IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
	return dz->getAttributeAsTime(pName,pNamespace);
}

AXISC_STORAGE_CLASS_INFO xsdc__duration * axiscGetAttributeAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
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
