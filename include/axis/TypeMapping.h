/*
 *   Copyright 2003-2006 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2006 All Rights Reserved
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
#ifndef TYPEMAPPING_INCLUDED
#define TYPEMAPPING_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#include <axis/GDefine.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @file TypeMapping.h
 */


/**
 * @enum XSDTYPE
 * Enumeration of xsd types
 */
typedef enum XSDCTYPETag 
{
    /**
     * Unknown XSD type
     */
    XSDC_UNKNOWN=1,
    
    /**
     * xsd:int
     */
    XSDC_INT,
    
    /**
     * xsd:float
     */
    XSDC_FLOAT,
    
    /**
     * xsd:string
     */
    XSDC_STRING,
    
    /**
     * xsd:long
     */
    XSDC_LONG,
    
    /**
     * xsd:short
     */
    XSDC_SHORT,
    
    /**
     * xsd:byte
     */
    XSDC_BYTE,
    
    /**
     * xsd:unsignedLong
     */
    XSDC_UNSIGNEDLONG,
    
    /**
     * xsd:boolean
     */
    XSDC_BOOLEAN,
    
    /**
     * xsd:unsignedInt
     */
    XSDC_UNSIGNEDINT,
    
    /**
     * xsd:unsignedShort
     */
    XSDC_UNSIGNEDSHORT,
    
    /**
     * xsd:unsignedByte
     */
    XSDC_UNSIGNEDBYTE,
    
    /**
     * xsd:double
     */
    XSDC_DOUBLE,
    
    /**
     * xsd:decimal
     */
    XSDC_DECIMAL,
    
    /**
     * xsd:duration
     */
    XSDC_DURATION,
    
    /**
     * xsd:dateTime
     */
    XSDC_DATETIME,
    
    /**
     * xsd:time
     */
    XSDC_TIME,
    
    /**
     * xsd:date
     */
    XSDC_DATE,
    
    /**
     * xsd:gYearMonth
     */
    XSDC_GYEARMONTH,
    
    /**
     * xsd:gYear
     */
    XSDC_GYEAR,
    
    /**
     * xsd:gMonthDay
     */
    XSDC_GMONTHDAY,
    
    /**
     * xsd:gDay
     */
    XSDC_GDAY,
    
    /**
     * xsd:gMonth
     */
    XSDC_GMONTH,
    
    /**
     * xsd:hexBinary
     */
    XSDC_HEXBINARY,
    
    /**
     * xsd:base64Binary
     */
    XSDC_BASE64BINARY,
    
    /**
     * xsd:anyURI
     */
    XSDC_ANYURI,
    
    /**
     * xsd:QName
     */
    XSDC_QNAME,
    
    /**
     * xsd:NOTATION
     */
    XSDC_NOTATION,
    
    /**
     * xsd:integer
     */
    XSDC_INTEGER,
    
    /**
     * Array, indicated in WSDL by maxOccurs greater than 1.
     * This may be an array of any other XSDTYPE.
     */
    XSDC_ARRAY,
    
    /**
     * User type, also referred to as a complex type
     */
    C_USER_TYPE,
    
    /**
     * xsd:NMTOKEN
     */
    XSDC_NMTOKEN,
    
    /**
     * xsd:any
     */
    XSDC_ANY,
    
    /**
     * xsd:nonNegativeInteger
     */
    XSDC_NONNEGATIVEINTEGER,
    
    /**
     * xsd:positivInteger
     */
    XSDC_POSITIVEINTEGER,
    
    /**
     * xsd:nonPositiveInteger
     */
    XSDC_NONPOSITIVEINTEGER,
    
    /**
     * xsd:negativeInteger
     */
    XSDC_NEGATIVEINTEGER,
    
    /**
     * xsd:normalizedString
     */
    XSDC_NORMALIZEDSTRING,
    
    /**
     * xsd:token
     */
    XSDC_TOKEN,
    
    /**
     * xsd:language
     */
    XSDC_LANGUAGE,
    
    /**
     * xsd:Name
     */
    XSDC_NAME,
    
    /**
     * xsd:NCName
     */
    XSDC_NCNAME,
    
    /**
     * xsd:ID
     */
    XSDC_ID,
    
    /**
     * xsd:IDREF
     */
    XSDC_IDREF,
    
    /**
     * xsd:IDREFS
     */
    XSDC_IDREFS,
    
    /**
     * xsd:ENTITY
     */
    XSDC_ENTITY,
    
    /**
     * xsd:ENTITIES
     */
    XSDC_ENTITIES,
    
    /**
     * xsd:NMTOKENS
     */
    XSDC_NMTOKENS,
    
    /**
     * Attachment
     */
    C_ATTACHMENT,
    
    /**
     * xsd:anyType
     */
    XSDC_ANYTYPE    
} AXISC_XSDTYPE;

/**
 * Map xsd type name to corresponding XSDTYPE enumeration value.
 * 
 * @param sType xsd type name
 * @return corresponding XSDTYPE enumeration value.
 */
AXISC_STORAGE_CLASS_INFO 
AXISC_XSDTYPE axiscTypeMappingMap(const AxiscXMLCh * sType);

/**
 * Initialize internal table of mappings from xsd type names to XSDTYPE enumeration values.
 */
AXISC_STORAGE_CLASS_INFO 
void axiscTypeMappingInitialize();

/**
 * Clear internal table of mappings from xsd type names to XSDTYPE enumeration values.
 */
AXISC_STORAGE_CLASS_INFO 
void axiscTypeMappingUninitialize();

/**
 * Create TyeMapping object.
 */
AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscTypeMappingCreate();

/**
 * Destroy TypeMapping object.
 */
AXISC_STORAGE_CLASS_INFO 
void axiscTypeMappingDestroy(AXISCHANDLE typeMapping);


#ifdef __cplusplus
 }
#endif

#endif /* TYPEMAPPING_INCLUDED */

