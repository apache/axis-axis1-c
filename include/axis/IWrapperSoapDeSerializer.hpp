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

#if !defined(_IWRAPPERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IWRAPPERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include <axis/TypeMapping.hpp>
#include <axis/WSDDDefines.hpp>
#include <axis/ISoapAttachment.hpp>

/**
 * @file IWrapperSoapDeSerializer.hpp
 */

/**
    @class IWrapperSoapDeSerializer
    @brief interface for the IWrapperSoapDeSerializer class.


    @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/

AXIS_CPP_NAMESPACE_START

class IWrapperSoapDeSerializer
{
public:
    /**
     * Destructor
     */
    virtual ~IWrapperSoapDeSerializer(){};

    /**
     * Check expected message has been received
     * 
     * @param pName SOAP element for message
     * @param pNamespace SOAP namespace for message
     * @return AXIS_SUCCESS if expected message has been received
     * 
     */
    virtual int AXISCALL checkMessageBody(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;

    /**
     * Check if message is a fault
     * 
     * @param pName SOAP element for fault
     * @param pNamespace SOAP namspace for fault
     * @return ISoapFault object
     */
    virtual void* AXISCALL checkForFault(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrappers to get a deserialized Array of complex types
     * 
     * @param pArray is populated with the deserialized complex type objects
     * @param pDZFunct function pointer to the complex type deserialize method
     * @param pCreFunct function pointer to the complex type creation method
     * @param pDelFunct function pointer to the complex type delete method
     * @param pSizeFunct function pointer toeh complex type size method
     * @param pName SOAP element name for complex type
     * @param pNamespace SOAP namespace for complex type
     * @return deserialized complex type array, this is pArray
     */
    virtual Axis_Array* AXISCALL getCmplxArray(Axis_Array * pArray, void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     *  Method used by wrappers to get a deserialized Array of basic types
     * 
     * @param nType the xsd basic type of the array elements
     * @param pName SOAP element name for array elements
     * @param pNamespace SOAP namespace for array elements
     * @return deserialized array
     */
    virtual Axis_Array* AXISCALL getBasicArray(XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace)=0;
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
    virtual void* AXISCALL getCmplxObject(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
    
    /**
     * Method used by wrapper to deserialize an xsd:int element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:int value
     */
    virtual xsd__int * AXISCALL getElementAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:boolean element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:boolean value
     */
    virtual xsd__boolean * AXISCALL getElementAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedInt element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedInt value
     */
    virtual xsd__unsignedInt * AXISCALL getElementAsUnsignedInt(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:short element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:short value
     */
    virtual xsd__short * AXISCALL getElementAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedShort element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedShort value
     */
    virtual xsd__unsignedShort * AXISCALL getElementAsUnsignedShort(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
        /**
     * Method used by wrapper to deserialize an xsd:byte element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:byte value
     */
    virtual xsd__byte * AXISCALL getElementAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedByte element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedByte value
     */
    virtual xsd__unsignedByte * AXISCALL getElementAsUnsignedByte(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:long element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:long value
     */
    virtual xsd__long * AXISCALL getElementAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:integer element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:integer value
     */
    virtual xsd__integer * AXISCALL getElementAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedLong element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedLong value
     */
    virtual xsd__unsignedLong * AXISCALL getElementAsUnsignedLong(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:float element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:float value
     */
    virtual xsd__float * AXISCALL getElementAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:double element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:double value
     */
    virtual xsd__double * AXISCALL getElementAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:decimal element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:decimal value
     */
    virtual xsd__decimal * AXISCALL getElementAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:string element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:string value
     */
    virtual xsd__string AXISCALL getElementAsString(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:anyURI element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:anyURI value
     */
    virtual xsd__anyURI AXISCALL getElementAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:QName element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:QName value
     */
    virtual xsd__QName AXISCALL getElementAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:hexBinary element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:hexBinary value
     */
    virtual xsd__hexBinary * AXISCALL getElementAsHexBinary(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:base64Binary element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:base64Binary value
     */
    virtual xsd__base64Binary * AXISCALL getElementAsBase64Binary(const AxisChar*
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:dateTime element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:dateTime value
     */
    virtual xsd__dateTime * AXISCALL getElementAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:date element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:date value
     */
    virtual xsd__date * AXISCALL getElementAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:time element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:time value
     */
    virtual xsd__time * AXISCALL getElementAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:duration element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:duration value
     */
    virtual xsd__duration * AXISCALL getElementAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gYearMonth element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gYearMonth value
     */
    virtual xsd__gYearMonth * AXISCALL getElementAsGYearMonth(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gYear element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gYear value
     */
    virtual xsd__gYear * AXISCALL getElementAsGYear(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gMonthDay element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gMonthDay value
     */
    virtual xsd__gMonthDay * AXISCALL getElementAsGMonthDay(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gDay element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gDay value
     */
    virtual xsd__gDay * AXISCALL getElementAsGDay(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gMonth element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gMonth value
     */
    virtual xsd__gMonth * AXISCALL getElementAsGMonth(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:nonPositiveInteger element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:nonPositiveInteger value
     */
    virtual xsd__nonPositiveInteger * AXISCALL getElementAsNonPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:negativeInteger element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:negativeInteger value
     */
    virtual xsd__negativeInteger * AXISCALL getElementAsNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:nonNegativeInteger element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:nonNegativeInteger value
     */
    virtual xsd__nonNegativeInteger * AXISCALL getElementAsNonNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:positiveInteger element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:positiveInteger value
     */
    virtual xsd__positiveInteger * AXISCALL getElementAsPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:normalizedString element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:normalizedString value
     */
    virtual xsd__normalizedString AXISCALL getElementAsNormalizedString(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:token element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:token value
     */
    virtual xsd__token AXISCALL getElementAsToken(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:language element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:language value
     */
    virtual xsd__language AXISCALL getElementAsLanguage(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:Name element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:Name value
     */
    virtual xsd__Name AXISCALL getElementAsName(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NCName element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NCName value
     */
    virtual xsd__NCName AXISCALL getElementAsNCName(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:ID element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:ID value
     */
    virtual xsd__ID AXISCALL getElementAsID(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:IDREF element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:IDREF value
     */
    virtual xsd__IDREF AXISCALL getElementAsIDREF(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:IDREFS element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:IDREFS value
     */
    virtual xsd__IDREFS AXISCALL getElementAsIDREFS(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:ENTITY element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:ENTITY value
     */
    virtual xsd__ENTITY AXISCALL getElementAsENTITY(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:ENTITIES element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:ENTITIES value
     */
    virtual xsd__ENTITIES AXISCALL getElementAsENTITIES(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NMTOKEN element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NMTOKEN value
     */
    virtual xsd__NMTOKEN AXISCALL getElementAsNMTOKEN(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NMTOKENS element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NMTOKENS value
     */
    virtual xsd__NMTOKENS AXISCALL getElementAsNMTOKENS(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NOTATION element
     * 
     * @param pName SOAP element name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NOTATION value
     */
    virtual xsd__NOTATION AXISCALL getElementAsNOTATION(const AxisChar* pName,
        const AxisChar* pNamespace)=0;

    /**
     * Method used by wrapper to deserialize an xsd:int attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:int value
     */
    virtual xsd__int * AXISCALL getAttributeAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:boolean attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:boolean value
     */
    virtual xsd__boolean * AXISCALL getAttributeAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedInt attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedInt value
     */
    virtual xsd__unsignedInt * AXISCALL getAttributeAsUnsignedInt(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:short attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:short value
     */
    virtual xsd__short * AXISCALL getAttributeAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedShort attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedShort value
     */
    virtual xsd__unsignedShort * AXISCALL getAttributeAsUnsignedShort(const AxisChar*
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:byte attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:byte value
     */
    virtual xsd__byte * AXISCALL getAttributeAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedByte attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedByte value
     */
    virtual xsd__unsignedByte * AXISCALL getAttributeAsUnsignedByte(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:long attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:long value
     */
    virtual xsd__long * AXISCALL getAttributeAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:integer attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:integer value
     */
    virtual xsd__integer * AXISCALL getAttributeAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:nonPositiveInteger attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:nonPositiveInteger value
     */
    virtual xsd__nonPositiveInteger * AXISCALL getAttributeAsNonPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:negativeInteger attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:negativeInteger value
     */
    virtual xsd__negativeInteger * AXISCALL getAttributeAsNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:nonNegativeInteger attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:nonNegativeInteger value
     */
    virtual xsd__nonNegativeInteger * AXISCALL getAttributeAsNonNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:positiveInteger attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:positiveInteger value
     */
    virtual xsd__positiveInteger * AXISCALL getAttributeAsPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:unsignedLong attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:unsignedLong value
     */
    virtual xsd__unsignedLong * AXISCALL getAttributeAsUnsignedLong(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:float attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:float value
     */
    virtual xsd__float * AXISCALL getAttributeAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:double attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:double value
     */
    virtual xsd__double * AXISCALL getAttributeAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:decimal attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:decimal value
     */
    virtual xsd__decimal * AXISCALL getAttributeAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NOTATION attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NOTATION value
     */
    virtual xsd__NOTATION AXISCALL getAttributeAsNOTATION(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:string attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:string value
     */
    virtual xsd__string AXISCALL getAttributeAsString(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:normalizedString attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:normalizedString value
     */
    virtual xsd__normalizedString AXISCALL getAttributeAsNormalizedString(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:token attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:token value
     */
    virtual xsd__token AXISCALL getAttributeAsToken(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:language attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:language value
     */
    virtual xsd__language AXISCALL getAttributeAsLanguage(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NMTOKEN attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NMTOKEN value
     */
    virtual xsd__NMTOKEN AXISCALL getAttributeAsNMTOKEN(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NMTOKENS attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NMTOKENS value
     */
    virtual xsd__NMTOKENS AXISCALL getAttributeAsNMTOKENS(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:Name attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:Name value
     */
    virtual xsd__Name AXISCALL getAttributeAsName(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:NCName attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:NCName value
     */
    virtual xsd__NCName AXISCALL getAttributeAsNCName(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:ID attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:ID value
     */
    virtual xsd__ID AXISCALL getAttributeAsID(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:IDREF attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:IDREF value
     */
    virtual xsd__IDREF AXISCALL getAttributeAsIDREF(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:IDREFS attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:IDREFS value
     */
    virtual xsd__IDREFS AXISCALL getAttributeAsIDREFS(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:ENTITY attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:ENTITY value
     */
    virtual xsd__ENTITY AXISCALL getAttributeAsENTITY(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:ENTITIES attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:ENTITIES value
     */
    virtual xsd__ENTITIES AXISCALL getAttributeAsENTITIES(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:anyURI attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:anyURI value
     */
    virtual xsd__anyURI AXISCALL getAttributeAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:QName attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:QName value
     */
    virtual xsd__QName AXISCALL getAttributeAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:hexBinary attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:hexBinary value
     */
    virtual xsd__hexBinary * AXISCALL getAttributeAsHexBinary(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:base64Binar attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:base64Binary value
     */
    virtual xsd__base64Binary * AXISCALL getAttributeAsBase64Binary(const 
        AxisChar* pName, const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:dateTime attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:dateTime value
     */
    virtual xsd__dateTime * AXISCALL getAttributeAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:date attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:date value
     */
    virtual xsd__date * AXISCALL getAttributeAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:time attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:time value
     */
    virtual xsd__time * AXISCALL getAttributeAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gDay attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gDay value
     */
    virtual xsd__gDay * AXISCALL getAttributeAsGDay(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gMonth attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gMonth value
     */
    virtual xsd__gMonth * AXISCALL getAttributeAsGMonth(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gMonthDay attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gMonthDay value
     */
    virtual xsd__gMonthDay * AXISCALL getAttributeAsGMonthDay(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gYear attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gYear value
     */
    virtual xsd__gYear * AXISCALL getAttributeAsGYear(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:gYearMonth attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:gYearMonth value
     */
    virtual xsd__gYearMonth * AXISCALL getAttributeAsGYearMonth(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    /**
     * Method used by wrapper to deserialize an xsd:duration attribute
     * 
     * @param pName SOAP attribute name
     * @param pNamespace SOAP namespace
     * @return deserialized xsd:duration value
     */
    virtual xsd__duration * AXISCALL getAttributeAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;

    /**
     * Return status of last operation
     * 
     * @return AXIS_SUCCESS of AXIS_FAIL
     */
    virtual int AXISCALL getStatus()=0;
    
    /* Externalization of deserializer API */
//    virtual int setInputStream(SOAPTransport* pInputStream)=0;
//    virtual int init()=0;
//    virtual PROVIDERTYPE getCurrentProviderType()=0;
//    virtual void setCurrentProviderType(PROVIDERTYPE nType)=0;    
    /**
     * Returns binding style of message
     * 
     * @return binding style
     */
    virtual AXIS_BINDING_STYLE getStyle()=0;    
    
    /**
     * Set binding style of message
     * 
     * @param nStyle binding style
     */
    virtual void setStyle(AXIS_BINDING_STYLE nStyle)=0;

    /**
     * Returns SOAP version of message
     * 
     * @return SOAP version
     */
    virtual int getVersion()=0;

    /**
     * Reads SOAP header ready for processing
     * 
     * @return AXIS_SUCCESS if SOAP header ready for processing
     */
    virtual int getHeader()=0;    

    /**
     * Deserialize an xsd:any element
     * This will deserialize the next available SOAP element and all child elements.
     * 
     * @return Deserialized xsd:any element
     */
	virtual AnyType* AXISCALL getAnyObject()=0;            

    /**
     * Deserialize character data, ie the data typically enclosed by an XML tag
     * 
     * @param pValue object into which deserialized value will be placed
     * @param type The xsd simple type of the data.
     */
    virtual void getChardataAs(void* pValue, XSDTYPE type)=0;
    
    /**
     * Returns attachment associated with the given ID.
     * 
     * @param pcAttachmentid ID of the attachment to be returned
     * @return SOAP attachment
     */
	virtual ISoapAttachment* getAttachment(const char* pcAttachmentid)=0;

    /**
     * Returns all attachments.
     * 
     * @param pAttchArraySize is updated with the array size
     * @return array of SOAP attachments
     */
	virtual ISoapAttachment** getAllAttachments(int *pAttchArraySize)=0;
	/**
	* This method allows to peek for the name of the next element in XML stream.
	* Useful in supporting "all" & "choice" WSDL constructs.
	* @return Name of the next element in XML stream 
	*/
	virtual const char* peekNextElementName() = 0;
	
};

AXIS_CPP_NAMESPACE_END

#endif
