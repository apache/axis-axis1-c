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
#ifndef IWRAPPERSOAPDESERIALIZER_INCLUDED
#define IWRAPPERSOAPDESERIALIZER_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif


#include <axis/AxisUserAPI.h>
#include <axis/TypeMapping.h>
#include <axis/WSDDDefines.h>
#include <axis/ISoapAttachment.h>

/**
 * @file IWrapperSoapDeSerializer.hpp
 */
/**
@class IWrapperSoapDeSerializer
@brief interface for the IWrapperSoapDeSerializer class.
 */
/**
 * Destructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapDeSerializerDestroy(AXISCHANDLE wrapperSoapDeSerializer);

/**
 * Check expected message has been received
 *
 * @param pName SOAP element for message
 * @param pNamespace SOAP namespace for message
 * @return AXIS_SUCCESS if expected message has been received
 *
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapDeSerializerCheckMessageBody(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Check if message is a fault
 *
 * @param pName SOAP element for fault
 * @param pNamespace SOAP namspace for fault
 * @return ISoapFault object
 */
AXISC_STORAGE_CLASS_INFO
void * axiscSoapDeSerializerCheckForFault(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrappers to get a deserialized Array of complex types
 *
 * @param pArray is populated with the deserialized complex type objects
 * @param pDZFunct function pointer to the complex type deserialize method
 * @param pCreFunct function pointer to the complex type creation method
 * @param pDelFunct function pointer to the complex type delete method
 * @param pName SOAP element name for complex type
 * @param pNamespace SOAP namespace for complex type
 * @return deserialized complex type array, this is pArray
 */
AXISC_STORAGE_CLASS_INFO
Axisc_Array * axiscSoapDeSerializerGetCmplxArray(AXISCHANDLE wrapperSoapDeSerializer, Axisc_Array * pArray, 
	void * pDZFunct, 
	void * pCreFunct, 
	void * pDelFunct, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 *  Method used by wrappers to get a deserialized Array of basic types
 *
 * @param nType the xsd basic type of the array elements
 * @param pName SOAP element name for array elements
 * @param pNamespace SOAP namespace for array elements
 * @return deserialized array
 */
AXISC_STORAGE_CLASS_INFO
Axisc_Array * axiscSoapDeSerializerGetBasicArray(AXISCHANDLE wrapperSoapDeSerializer, AXISC_XSDTYPE nType, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 *  Method used by wrappers to get a deserialized single object of
 *  complex type
 *
 * @param pDZFunct function pointer to the complex type deserialize method
 * @param pCreFunct function pointer to the complex type creation method
 * @param pDelFunct function pointer to the complex type delete method
 * @param pName SOAP element name for complex type
 * @param pNamespace SOAP namespace for complex type
 * @return deserialized complex type
 */
AXISC_STORAGE_CLASS_INFO
void * axiscSoapDeSerializerGetCmplxObject(AXISCHANDLE wrapperSoapDeSerializer, void * pDZFunct, 
	void * pCreFunct, 
	void * pDelFunct, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:int element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:int value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__int * axiscSoapDeSerializerGetElementAsInt(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:boolean element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:boolean value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__boolean * axiscSoapDeSerializerGetElementAsBoolean(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedInt element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedInt value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedInt * axiscSoapDeSerializerGetElementAsUnsignedInt(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:short element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:short value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__short * axiscSoapDeSerializerGetElementAsShort(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedShort element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedShort value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedShort * axiscSoapDeSerializerGetElementAsUnsignedShort(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:byte element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:byte value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__byte * axiscSoapDeSerializerGetElementAsByte(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedByte element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedByte value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedByte * axiscSoapDeSerializerGetElementAsUnsignedByte(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:long element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:long value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__long * axiscSoapDeSerializerGetElementAsLong(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:integer element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:integer value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__integer * axiscSoapDeSerializerGetElementAsInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedLong element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedLong value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedLong * axiscSoapDeSerializerGetElementAsUnsignedLong(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:float element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:float value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__float * axiscSoapDeSerializerGetElementAsFloat(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:double element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:double value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__double * axiscSoapDeSerializerGetElementAsDouble(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:decimal element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:decimal value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__decimal * axiscSoapDeSerializerGetElementAsDecimal(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:string element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:string value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__string axiscSoapDeSerializerGetElementAsString(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:anyURI element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:anyURI value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__anyURI axiscSoapDeSerializerGetElementAsAnyURI(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:QName element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:QName value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__QName axiscSoapDeSerializerGetElementAsQName(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:hexBinary element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:hexBinary value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__hexBinary * axiscSoapDeSerializerGetElementAsHexBinary(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:base64Binary element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:base64Binary value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__base64Binary * axiscSoapDeSerializerGetElementAsBase64Binary(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:dateTime element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:dateTime value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__dateTime * axiscSoapDeSerializerGetElementAsDateTime(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:date element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:date value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__date * axiscSoapDeSerializerGetElementAsDate(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:time element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:time value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__time * axiscSoapDeSerializerGetElementAsTime(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:duration element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:duration value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__duration * axiscSoapDeSerializerGetElementAsDuration(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gYearMonth element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gYearMonth value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gYearMonth * axiscSoapDeSerializerGetElementAsGYearMonth(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gYear element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gYear value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gYear * axiscSoapDeSerializerGetElementAsGYear(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gMonthDay element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gMonthDay value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gMonthDay * axiscSoapDeSerializerGetElementAsGMonthDay(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gDay element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gDay value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gDay * axiscSoapDeSerializerGetElementAsGDay(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gMonth element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gMonth value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gMonth * axiscSoapDeSerializerGetElementAsGMonth(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:nonPositiveInteger element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:nonPositiveInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__nonPositiveInteger * axiscSoapDeSerializerGetElementAsNonPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:negativeInteger element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:negativeInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__negativeInteger * axiscSoapDeSerializerGetElementAsNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:nonNegativeInteger element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:nonNegativeInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__nonNegativeInteger * axiscSoapDeSerializerGetElementAsNonNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:positiveInteger element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:positiveInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__positiveInteger * axiscSoapDeSerializerGetElementAsPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:normalizedString element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:normalizedString value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__normalizedString axiscSoapDeSerializerGetElementAsNormalizedString(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:token element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:token value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__token axiscSoapDeSerializerGetElementAsToken(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:language element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:language value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__language axiscSoapDeSerializerGetElementAsLanguage(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:Name element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:Name value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__Name axiscSoapDeSerializerGetElementAsName(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NCName element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NCName value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NCName axiscSoapDeSerializerGetElementAsNCName(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:ID element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:ID value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__ID axiscSoapDeSerializerGetElementAsID(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:IDREF element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:IDREF value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__IDREF axiscSoapDeSerializerGetElementAsIDREF(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:IDREFS element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:IDREFS value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__IDREFS axiscSoapDeSerializerGetElementAsIDREFS(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:ENTITY element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:ENTITY value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__ENTITY axiscSoapDeSerializerGetElementAsENTITY(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:ENTITIES element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:ENTITIES value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__ENTITIES axiscSoapDeSerializerGetElementAsENTITIES(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NMTOKEN element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NMTOKEN value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKEN axiscSoapDeSerializerGetElementAsNMTOKEN(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NMTOKENS element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NMTOKENS value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKENS axiscSoapDeSerializerGetElementAsNMTOKENS(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NOTATION element
 *
 * @param pName SOAP element name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NOTATION value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NOTATION axiscSoapDeSerializerGetElementAsNOTATION(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:int attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:int value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__int * axiscSoapDeSerializerGetAttributeAsInt(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:boolean attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:boolean value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__boolean * axiscSoapDeSerializerGetAttributeAsBoolean(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedInt attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedInt value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedInt * axiscSoapDeSerializerGetAttributeAsUnsignedInt(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:short attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:short value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__short * axiscSoapDeSerializerGetAttributeAsShort(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedShort attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedShort value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedShort * axiscSoapDeSerializerGetAttributeAsUnsignedShort(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:byte attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:byte value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__byte * axiscSoapDeSerializerGetAttributeAsByte(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedByte attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedByte value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedByte * axiscSoapDeSerializerGetAttributeAsUnsignedByte(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:long attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:long value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__long * axiscSoapDeSerializerGetAttributeAsLong(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:integer attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:integer value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__integer * axiscSoapDeSerializerGetAttributeAsInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:nonPositiveInteger attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:nonPositiveInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__nonPositiveInteger * axiscSoapDeSerializerGetAttributeAsNonPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:negativeInteger attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:negativeInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__negativeInteger * axiscSoapDeSerializerGetAttributeAsNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:nonNegativeInteger attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:nonNegativeInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__nonNegativeInteger * axiscSoapDeSerializerGetAttributeAsNonNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:positiveInteger attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:positiveInteger value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__positiveInteger * axiscSoapDeSerializerGetAttributeAsPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:unsignedLong attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:unsignedLong value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__unsignedLong * axiscSoapDeSerializerGetAttributeAsUnsignedLong(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:float attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:float value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__float * axiscSoapDeSerializerGetAttributeAsFloat(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:double attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:double value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__double * axiscSoapDeSerializerGetAttributeAsDouble(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:decimal attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:decimal value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__decimal * axiscSoapDeSerializerGetAttributeAsDecimal(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NOTATION attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NOTATION value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NOTATION axiscSoapDeSerializerGetAttributeAsNOTATION(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:string attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:string value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__string axiscSoapDeSerializerGetAttributeAsString(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:normalizedString attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:normalizedString value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__normalizedString axiscSoapDeSerializerGetAttributeAsNormalizedString(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:token attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:token value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__token axiscSoapDeSerializerGetAttributeAsToken(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:language attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:language value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__language axiscSoapDeSerializerGetAttributeAsLanguage(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NMTOKEN attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NMTOKEN value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKEN axiscSoapDeSerializerGetAttributeAsNMTOKEN(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NMTOKENS attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NMTOKENS value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKENS axiscSoapDeSerializerGetAttributeAsNMTOKENS(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:Name attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:Name value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__Name axiscSoapDeSerializerGetAttributeAsName(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:NCName attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:NCName value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__NCName axiscSoapDeSerializerGetAttributeAsNCName(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:ID attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:ID value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__ID axiscSoapDeSerializerGetAttributeAsID(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:IDREF attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:IDREF value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__IDREF axiscSoapDeSerializerGetAttributeAsIDREF(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:IDREFS attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:IDREFS value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__IDREFS axiscSoapDeSerializerGetAttributeAsIDREFS(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:ENTITY attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:ENTITY value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__ENTITY axiscSoapDeSerializerGetAttributeAsENTITY(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:ENTITIES attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:ENTITIES value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__ENTITIES axiscSoapDeSerializerGetAttributeAsENTITIES(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:anyURI attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:anyURI value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__anyURI axiscSoapDeSerializerGetAttributeAsAnyURI(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:QName attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:QName value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__QName axiscSoapDeSerializerGetAttributeAsQName(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:hexBinary attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:hexBinary value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__hexBinary * axiscSoapDeSerializerGetAttributeAsHexBinary(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:base64Binar attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:base64Binary value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__base64Binary * axiscSoapDeSerializerGetAttributeAsBase64Binary(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:dateTime attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:dateTime value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__dateTime * axiscSoapDeSerializerGetAttributeAsDateTime(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:date attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:date value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__date * axiscSoapDeSerializerGetAttributeAsDate(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:time attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:time value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__time * axiscSoapDeSerializerGetAttributeAsTime(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gDay attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gDay value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gDay * axiscSoapDeSerializerGetAttributeAsGDay(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gMonth attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gMonth value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gMonth * axiscSoapDeSerializerGetAttributeAsGMonth(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gMonthDay attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gMonthDay value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gMonthDay * axiscSoapDeSerializerGetAttributeAsGMonthDay(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gYear attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gYear value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gYear * axiscSoapDeSerializerGetAttributeAsGYear(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:gYearMonth attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:gYearMonth value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__gYearMonth * axiscSoapDeSerializerGetAttributeAsGYearMonth(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Method used by wrapper to deserialize an xsd:duration attribute
 *
 * @param pName SOAP attribute name
 * @param pNamespace SOAP namespace
 * @return deserialized xsd:duration value
 */
AXISC_STORAGE_CLASS_INFO
xsdc__duration * axiscSoapDeSerializerGetAttributeAsDuration(AXISCHANDLE wrapperSoapDeSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * Return status of last operation
 *
 * @return AXIS_SUCCESS of AXIS_FAIL
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapDeSerializerGetStatus(AXISCHANDLE wrapperSoapDeSerializer);

/**
 * Returns binding style of message
 *
 * @return binding style
 */
AXISC_STORAGE_CLASS_INFO
AXISC_BINDING_STYLE axiscSoapDeSerializerGetStyle(AXISCHANDLE wrapperSoapDeSerializer);

/**
 * Set binding style of message
 *
 * @param nStyle binding style
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapDeSerializerSetStyle(AXISCHANDLE wrapperSoapDeSerializer, AXISC_BINDING_STYLE nStyle);

/**
 * Returns SOAP version of message
 *
 * @return SOAP version
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapDeSerializerGetVersion(AXISCHANDLE wrapperSoapDeSerializer);

/**
 * Reads SOAP header ready for processing
 *
 * @return AXIS_SUCCESS if SOAP header ready for processing
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapDeSerializerGetHeader(AXISCHANDLE wrapperSoapDeSerializer);

/**
 * Deserialize an xsd:any element
 * This will deserialize the next available SOAP element and all child elements.
 *
 * @return Deserialized xsd:any element
 */
AXISC_STORAGE_CLASS_INFO
AxiscAnyType * axiscSoapDeSerializerGetAnyObject(AXISCHANDLE wrapperSoapDeSerializer);

/**
 * Deserialize character data, ie the data typically enclosed by an XML tag
 *
 * @param pValue object into which deserialized value will be placed
 * @param type The xsd simple type of the data.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapDeSerializerGetChardataAs(AXISCHANDLE wrapperSoapDeSerializer, void * pValue, 
	AXISC_XSDTYPE type);

/**
 * Returns attachment associated with the given ID.
 *
 * @param pcAttachmentid ID of the attachment to be returned
 * @return SOAP attachment
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscSoapDeSerializerGetAttachmentSoapAttachment(AXISCHANDLE wrapperSoapDeSerializer, const char * pcAttachmentid);

/**
 * Returns all attachments.
 *
 * @param pAttchArraySize is updated with the array size
 * @return array of SOAP attachments
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscSoapDeSerializerGetAllAttachmentsSoapAttachment(AXISCHANDLE wrapperSoapDeSerializer, int * pAttchArraySize);

/**
 * This method allows to peek for the name of the next element in XML stream.
 * Useful in supporting "all" & "choice" WSDL constructs.
 * @return Name of the next element in XML stream
 */
AXISC_STORAGE_CLASS_INFO
const char * axiscSoapDeSerializerPeekNextElementName(AXISCHANDLE wrapperSoapDeSerializer);


#ifdef __cplusplus
 }
#endif

#endif /* IWRAPPERSOAPDESERIALIZER_INCLUDED */
