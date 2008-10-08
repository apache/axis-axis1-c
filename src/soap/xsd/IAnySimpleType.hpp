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
 
 /*
  * @file IAnySimpleType.hpp
  */
  
#if !defined(_IANYSIMPLETYPE_HPP____OF_AXIS_INCLUDED_)
#define _IANYSIMPLETYPE_HPP____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <string>
#include <axis/AxisUserAPI.hpp>
#include "../AxisSoapException.h"
#include "constraints/WhiteSpace.hpp"
#include "constraints/Pattern.hpp"
#include "constraints/Enumeration.hpp"
#include <axis/TypeMapping.hpp>

AXIS_CPP_NAMESPACE_START

/* Entity reference characters */
const AxisChar XML_ENTITY_REFERENCE_CHARS[]    = "<>&\"\'";

/* Encoded string for less than character */
const AxisChar ENCODED_LESSER_STR[]            = "&lt;";    

/* Encoded string for greator than character */
const AxisChar ENCODED_GREATER_STR[]        = "&gt;";    

/* Encoded string for ampersand character */
const AxisChar ENCODED_AMPERSAND_STR[]        = "&amp;";    

/* Encoded string for single quote character */
const AxisChar ENCODED_DBL_QUOTE_STR[]        = "&quot;";    

/* Encoded string for double quote character */
const AxisChar ENCODED_SGL_QUOTE_STR[]        = "&apos;";    



/**
 *   @class IAnySimpleType
 *   @brief Interface for all XSD built-in simple type.
 *
 *   @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */
class IAnySimpleType {
public:

    /**
     * Constructor
     */
    IAnySimpleType();
    
    /**
     * Destructor
     */
    virtual ~IAnySimpleType();

    /**
     * This method provides ability to determine if value is nill.
     * @return true is value is nil, otherwise false
     */
    bool isNil();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    virtual void* getValue() = 0;

    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    virtual XSDTYPE getType() = 0;

    /**
     * Provides the contained value in it's on-the-wire string form.
     * @return Serialized form of value
     */
    AxisChar* serialize();

    /**
     * Takes the value in it's on-the-wire string form
     * @param Serialized form of value
     */
    void deserialize(const AxisChar* value);
    
    /**
     * Utility function to replace reserved characters in XML with corresponding
     * entities. 
     * 
     * @param inValue - source string
     * @param outValue - source string with reserved characters converted.
     */
    static void replaceReservedCharacters(AxisString& inValue, AxisString& outValue);

protected:

    /**
     * Take partially serialized value, process WhiteSpace and validate Pattern.
     * @param value partially serialized value
     * @return Serialized form of value
     */
    AxisChar* serialize(const AxisChar* value) throw (AxisSoapException);

    /**
     * Set whether or not value is nil
     * @param nil
     */
    void setNil(bool nil);

    /**
     * Replace all XML reserved characters in string
     * @param value Original string
     * @return String with all reserved characters replaced
     */
    const AxisString& replaceReservedCharacters(AxisString& value);

    /**
     * Creates a WhiteSpace object which preserve original string form
     * @return WhiteSpace object
     */
    virtual WhiteSpace* getWhiteSpace();

    /**
     * Creates an Enumeration object. Enumeration is not defined for IAnySimpleType
     * so an unset Enumeration object is created.
     * @return Enumeration object
     */
    virtual Enumeration* getEnumeration();
   
    /**
     * Create a Pattern object with no rules
     * @return Pattern object
     */
    Pattern* getPattern();

    /**
     * Reserved Characters
     */
    enum
    {
        GREATER_THAN_CHAR    =    '>',    /* Greater than character */
        LESSER_THAN_CHAR    =    '<',    /* Less than character */
        SINGLE_QUOTE_CHAR    =    '\'',    /* Single quotation character */
        DOUBLE_QUOTE_CHAR    =    '\"',    /* Double quotation character */
        AMPERSAND_CHAR        =    '&'    /* Ampersand character */
    };

    AxisChar* m_Buf;
   
private:

    bool m_isNil;

    AxisString m_strReturnVal;
};

AXIS_CPP_NAMESPACE_END

#endif
