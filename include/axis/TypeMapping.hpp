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

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED TO THE        */
/* C-EQUIVALENT HEADER FILE IN SUPPORT OF THE C-BINDING INTERFACES.   */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/**
 * @file TypeMapping.hpp
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(_TYPEMAPPING_H____OF_AXIS_INCLUDED_)
#define _TYPEMAPPING_H____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <map>
#include <string>

AXIS_CPP_NAMESPACE_START
using namespace std;

/**
 * @enum XSDTYPE
 * Enumeration of xsd types
 */
typedef enum XSDTYPETag 
{
    /**
     * Unknown XSD type
     */
    XSD_UNKNOWN=1,
    
    /**
     * xsd:int
     */
    XSD_INT,
    
    /**
     * xsd:float
     */
    XSD_FLOAT,
    
    /**
     * xsd:string
     */
    XSD_STRING,
    
    /**
     * xsd:long
     */
    XSD_LONG,
    
    /**
     * xsd:short
     */
    XSD_SHORT,
    
    /**
     * xsd:byte
     */
    XSD_BYTE,
    
    /**
     * xsd:unsignedLong
     */
    XSD_UNSIGNEDLONG,
    
    /**
     * xsd:boolean
     */
    XSD_BOOLEAN,
    
    /**
     * xsd:unsignedInt
     */
    XSD_UNSIGNEDINT,
    
    /**
     * xsd:unsignedShort
     */
    XSD_UNSIGNEDSHORT,
    
    /**
     * xsd:unsignedByte
     */
    XSD_UNSIGNEDBYTE,
    
    /**
     * xsd:double
     */
    XSD_DOUBLE,
    
    /**
     * xsd:decimal
     */
    XSD_DECIMAL,
    
    /**
     * xsd:duration
     */
    XSD_DURATION,
    
    /**
     * xsd:dateTime
     */
    XSD_DATETIME,
    
    /**
     * xsd:time
     */
    XSD_TIME,
    
    /**
     * xsd:date
     */
    XSD_DATE,
    
    /**
     * xsd:gYearMonth
     */
    XSD_GYEARMONTH,
    
    /**
     * xsd:gYear
     */
    XSD_GYEAR,
    
    /**
     * xsd:gMonthDay
     */
    XSD_GMONTHDAY,
    
    /**
     * xsd:gDay
     */
    XSD_GDAY,
    
    /**
     * xsd:gMonth
     */
    XSD_GMONTH,
    
    /**
     * xsd:hexBinary
     */
    XSD_HEXBINARY,
    
    /**
     * xsd:base64Binary
     */
    XSD_BASE64BINARY,
    
    /**
     * xsd:anyURI
     */
    XSD_ANYURI,
    
    /**
     * xsd:QName
     */
    XSD_QNAME,
    
    /**
     * xsd:NOTATION
     */
    XSD_NOTATION,
    
    /**
     * xsd:integer
     */
    XSD_INTEGER,
    
    /**
     * Array, indicated in WSDL by maxOccurs greater than 1.
     * This may be an array of any other XSDTYPE.
     */
    XSD_ARRAY,
    
    /**
     * User type, also referred to as a complex type
     */
    USER_TYPE,
    
    /**
     * xsd:NMTOKEN
     */
    XSD_NMTOKEN,
    
    /**
     * xsd:any
     */
    XSD_ANY,
    
    /**
     * xsd:nonNegativeInteger
     */
    XSD_NONNEGATIVEINTEGER,
    
    /**
     * xsd:positivInteger
     */
    XSD_POSITIVEINTEGER,
    
    /**
     * xsd:nonPositiveInteger
     */
    XSD_NONPOSITIVEINTEGER,
    
    /**
     * xsd:negativeInteger
     */
    XSD_NEGATIVEINTEGER,
    
    /**
     * xsd:normalizedString
     */
    XSD_NORMALIZEDSTRING,
    
    /**
     * xsd:token
     */
    XSD_TOKEN,
    
    /**
     * xsd:language
     */
    XSD_LANGUAGE,
    
    /**
     * xsd:Name
     */
    XSD_NAME,
    
    /**
     * xsd:NCName
     */
    XSD_NCNAME,
    
    /**
     * xsd:ID
     */
    XSD_ID,
    
    /**
     * xsd:IDREF
     */
    XSD_IDREF,
    
    /**
     * xsd:IDREFS
     */
    XSD_IDREFS,
    
    /**
     * xsd:ENTITY
     */
    XSD_ENTITY,
    
    /**
     * xsd:ENTITIES
     */
    XSD_ENTITIES,
    
    /**
     * xsd:NMTOKENS
     */
    XSD_NMTOKENS,
    
    /**
     * Attachment
     */
    ATTACHMENT
} XSDTYPE;

/**
 * REMOVED from XSDTYPETag-> ACCESSOR,
 */
/**
 *  @class TypeMapping
 *  @brief interface for the TypeMapping class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com)
 */

class TypeMapping  
{
public:
    /**
     * Map xsd type name to corresponding XSDTYPE enumeration value.
     * 
     * @param sType xsd type name
     * @return corresponding XSDTYPE enumeration value.
     */
    static XSDTYPE map(const AxisXMLCh* sType);
    
    /**
     * Initialize internal table of mappings from xsd type names to XSDTYPE enumeration values.
     */
    static void initialize();
    
    /**
     * Clear internal table of mappings from xsd type names to XSDTYPE enumeration values.
     */
	static void uninitialize();

    /**
     * Internal table of mappings from xsd type names to XSDTYPE enumeration values.
     */
#if (defined(AIX) || (defined(_MSC_VER) && _MSC_VER >= 1300) || defined( __OS400__ ) || defined(__sun))
    /**
     * Internal table of mappings from xsd type names to XSDTYPE enumeration values.
     */
	static std::map<std::string, XSDTYPE> m_sTypeMap;
#else
    /**
     * Internal table of mappings from xsd type names to XSDTYPE enumeration values.
     */
	static std::map<const std::string, XSDTYPE> m_sTypeMap;
#endif

    /**
     * Flag to indicate if TypeMapping class has been initialized.
     */
    static volatile bool m_bInit;

    /**
     * Default constructor
     */
    TypeMapping();
    
    /**
     * Destructor
     */
    virtual ~TypeMapping();

};

AXIS_CPP_NAMESPACE_END

#endif
