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
 
 /*
  * @file IAnySimpleType.hpp
  */
  
#if !defined(_IANYSIMPLETYPE_HPP____OF_AXIS_INCLUDED_)
#define _IANYSIMPLETYPE_HPP____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <string>
#include "../AxisSoapException.h"
#include "constraints/WhiteSpace.hpp"
#include "constraints/Pattern.hpp"
#include "constraints/Enumeration.hpp"

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
	 * Serialize value to it's on-the-wire string form.
	 * @param value The value to be serialized.
	 * @return Serialized form of value.
	 */
    virtual AxisChar* serialize(const void* value) throw (AxisSoapException) = 0;
	
	/**
	 * Deserialize value from it's on-the-wire string form.
	 * @param valueAsChar Serialized form of value.
	 * @return Deserialized value.
	 */
    virtual void* deserialize(const AxisChar* valueAsChar) throw (AxisSoapException) = 0;

    /**
     * Take partially serialized value, process WhiteSpace and validate Pattern.
     * @param value
     * @return Serialized form of value
     */
    AxisChar* serialize(const AxisChar* value) throw (AxisSoapException);

protected:

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
        GREATER_THAN_CHAR    =    L'>',    /* Greater than character */
        LESSER_THAN_CHAR    =    L'<',    /* Less than character */
        SINGLE_QUOTE_CHAR    =    L'\'',    /* Single quotation character */
        DOUBLE_QUOTE_CHAR    =    L'\"',    /* Double quotation character */
        AMPERSAND_CHAR        =    L'&'    /* Ampersand character */
    };

    AxisChar* m_Buf;
    
private:
    AxisString m_strReturnVal;
};

AXIS_CPP_NAMESPACE_END

#endif
