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

#if !defined(_AXISUSERAPI_H_OF_AXIS_INCLUDED_)
#define _AXISUSERAPI_H_OF_AXIS_INCLUDED_

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE APIS.                                    */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
  extern "C" {
#endif

#include <axis/GDefine.h>
#include <time.h>
#include <string.h>
#include <axis/TypeMapping.h>

 /**
  * @file AxisUserAPI.h
  * This file contains types defined in Axis C++. The mapping of basic xsd types
  * to the C language types.
  * 
  * The following xsd basic types are supported:
  * - <tt> anyURI, base64Binary, boolean, byte, date, dateTime, decimal, double, duration, float, hexBinary, int, integer, long, NMTOKEN, NOTATION, QName, short, string, time, unsignedByte, unsignedInt, unsignedLong</tt> and \c unsignedShort.
  */

/**
 * @typedef xsdc__string
 * Axis C++ defined type for xml basic type string
 */
typedef AxiscChar * xsdc__string;

/**
 * @typedef xsdc__normalizedString
 * Axis C++ defined type for xml basic type normalizedString
 */
typedef AxiscChar * xsdc__normalizedString;

/**
 * @typedef xsdc__token
 * Axis C++ defined type for xml basic type token
 */
typedef AxiscChar * xsdc__token;

/**
 * @typedef xsdc__language
 * Axis C++ defined type for xml basic type language
 */
typedef AxiscChar * xsdc__language;

/**
 * @typedef xsdc__Name
 * Axis C++ defined type for xml basic type Name
 */
typedef AxiscChar * xsdc__Name;

/**
 * @typedef xsdc__NCName
 * Axis C++ defined type for xml basic type NCName
 */
typedef AxiscChar * xsdc__NCName;

/**
 * @typedef xsdc__ID
 * Axis C++ defined type for xml basic type ID
 */
typedef AxiscChar * xsdc__ID;

/**
 * @typedef xsdc__IDREF
 * Axis C++ defined type for xml basic type IDREF
 */
typedef AxiscChar * xsdc__IDREF;

/**
 * @typedef xsdc__IDREFS
 * Axis C++ defined type for xml basic type IDREFS
 */
typedef AxiscChar * xsdc__IDREFS;

/**
 * @typedef xsdc__ENTITY
 * Axis C++ defined type for xml basic type ENTITY
 */
typedef AxiscChar * xsdc__ENTITY;

/**
 * @typedef xsdc__ENTITIES
 * Axis C++ defined type for xml basic type ENTITIES
 */
typedef AxiscChar * xsdc__ENTITIES;

/**
 * @typedef xsdc__NMTOKEN
 * Axis C++ defined type for xml basic type NMTOKEN
 */
typedef AxiscChar * xsdc__NMTOKEN;

/**
 * @typedef xsdc__NMTOKENS
 * Axis C++ defined type for xml basic type NMTOKENS
 */
typedef AxiscChar * xsdc__NMTOKENS;

/**
 * @typedef xsdc__integer
 * Axis C++ defined type for xml basic type integer
 */
#ifdef WIN32
typedef __int64 xsdc__integer;
#else
typedef long long xsdc__integer;
#endif

/**
 * @typedef xsdc__int
 * Axis C++ defined type for xml basic type int
 */
typedef int xsdc__int;

/**
 * @typedef xsdc__long
 * Axis C++ defined type for xml basic type long
 */
#ifdef WIN32
typedef __int64 xsdc__long;
#else
typedef long long xsdc__long;
#endif

/**
 * @typedef xsdc__short
 * Axis C++ defined type for xml basic type short
 */
typedef short xsdc__short;

/**
 * @typedef xsdc__decimal
 * Axis C++ defined type for xml basic type decimal
 */
typedef double xsdc__decimal;

/**
 * @typedef xsdc__float
 * Axis C++ defined type for xml basic type float
 */
typedef float xsdc__float;

/**
 * @typedef xsdc__double
 * Axis C++ defined type for xml basic type double
 */
typedef double xsdc__double;

/**
 * @typedef xsdc__boolean
 * Axis C++ defined type for xml basic type boolean
 */
typedef enum { false_=0, true_ } xsdc__boolean;
/**
 * @typedef xsdc__byte
 * Axis C++ defined type for xml basic type byte
 */
typedef signed char xsdc__byte;

/**
 * @typedef xsdc__QName
 * Axis C++ defined type for xml basic type QName
 */
typedef AxiscChar * xsdc__QName;

/**
 * @typedef xsd__NOTATION
 * Axis C++ defined type for xml basic type NOTATION
 */
typedef AxiscChar * xsdc__NOTATION;

/**
 * @typedef xsdc__dateTime
 * Axis C++ defined type for xml basic type dateTime
 */
typedef struct tm xsdc__dateTime;

/**
 * @typedef xsdc__date
 * Axis C++ defined type for xml basic type date
 */
typedef struct tm xsdc__date;

/**
 * @typedef xsdc__time
 * Axis C++ defined type for xml basic type time
 */
typedef struct tm xsdc__time;

/**
 * @typedef xsdc__gYearMonth
 * Axis C++ defined type for xml basic type gYearMonth
 */
typedef struct tm xsdc__gYearMonth;

/**
 * @typedef xsdc__gYear
 * Axis C++ defined type for xml basic type gYear
 */
typedef struct tm xsdc__gYear;

/**
 * @typedef xsdc__gMonthDay
 * Axis C++ defined type for xml basic type gMonthDay
 */
typedef struct tm xsdc__gMonthDay;

/**
 * @typedef xsdc__gDay
 * Axis C++ defined type for xml basic type gDay
 */
typedef struct tm xsdc__gDay;

/**
 * @typedef xsdc__gMonth
 * Axis C++ defined type for xml basic type gMonth
 */
typedef struct tm xsdc__gMonth;

/**
 * @typedef xsdc__duration
 * Axis C++ defined type for xml basic type duration
 */
typedef long xsdc__duration;

/**
 * @typedef xsdc__nonNegativeInteger
 * Axis C++ defined type for xml basic type nonNegativeInteger
 */
#ifdef WIN32
typedef unsigned __int64 xsdc__nonNegativeInteger;
#else
typedef unsigned long long xsdc__nonNegativeInteger;
#endif

/**
 * @typedef xsdc__unsignedByte
 * Axis C++ defined type for xml basic type unsignedByte
 */
typedef unsigned char xsdc__unsignedByte;

/**
 * @typedef xsdc__unsignedInt
 * Axis C++ defined type for xml basic type unsignedInt
 */
typedef unsigned int xsdc__unsignedInt;

/**
 * @typedef xsdc__unsignedLong
 * Axis C++ defined type for xml basic type unsignedLong
 */
#ifdef WIN32
typedef unsigned __int64 xsdc__unsignedLong;
#else
typedef unsigned long long xsdc__unsignedLong;
#endif
/**
 * @typedef xsdc__unsignedShort
 * Axis C++ defined type for xml basic type unsignedShort
 */
typedef unsigned short xsdc__unsignedShort;

/**
 * @typedef xsdc__nonPositiveInteger
 * Axis C++ defined type for xml basic type nonPositiveInteger
 */
#ifdef WIN32
typedef __int64 xsdc__nonPositiveInteger;
#else
typedef long long xsdc__nonPositiveInteger;
#endif

/**
 * @typedef xsdc__positiveInteger
 * Axis C++ defined type for xml basic type positiveInteger
 */
#ifdef WIN32
typedef unsigned __int64 xsdc__positiveInteger;
#else
typedef unsigned long long xsdc__positiveInteger;
#endif

/**
 * @typedef xsdc__negativeInteger
 * Axis C++ defined type for xml basic type negativeInteger
 */
#ifdef WIN32
typedef __int64 xsdc__negativeInteger;
#else
typedef long long xsdc__negativeInteger;
#endif

/**
 * @struct xsdc__base64Binary
 * Axis C++ defined type for xml basic type base64Binary
 */
typedef struct
{
    /**
     * Binary data
     */
    xsdc__unsignedByte * __ptr;
    
    /**
     * Length, in bytes, of binary data
     */
    xsdc__int __size;
} xsdc__base64Binary;

/**
 * @struct xsdc__hexBinary
 * Axis C++ defined type for xml basic type hexBinary
 */
typedef struct
{
    /**
     * Binary data
     */
    xsdc__unsignedByte * __ptr;
    
    /**
     * Length, in bytes, of binary data
     */
    xsdc__int __size;
} xsdc__hexBinary;
/**
 * @typedef xsdc__anyURI
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxiscChar * xsdc__anyURI;

/**
 * @enum AXISC_BINDING_STYLE
 * Enumeration for the different wsdl styles. This is used by the Axis
 * engine to identify the web service or client style.
 */
typedef enum {
    AXISC_RPC_ENCODED, /*default*/
    AXISC_DOC_LITERAL,
    AXISC_RPC_LITERAL
} AXISC_BINDING_STYLE;

#define AXISC_DEFINED_ARRAY(type) \
    typedef struct {\
        type ** m_Array;\
        int m_Size;\
        AXISC_XSDTYPE m_Type; \
    } type##_Array;

#define AXISC_DEFINED_POINTER_ARRAY(type) \
    typedef struct {\
        type * m_Array;\
        int m_Size;\
        AXISC_XSDTYPE m_Type; \
    } type##_Array;

#define AXISC_DEFINED_ARRAY2(type) \
    typedef struct {\
        AXISCHANDLE m_Array;\
        int m_Size;\
        AXISC_XSDTYPE m_Type; \
    } type##_Array;

typedef struct {
    void* m_Array;
    int m_Size;
    AXISC_XSDTYPE m_Type; \
} Axisc_Array;

AXISC_DEFINED_ARRAY(xsdc__duration) 
AXISC_DEFINED_ARRAY(xsdc__dateTime)
AXISC_DEFINED_ARRAY(xsdc__time)
AXISC_DEFINED_ARRAY(xsdc__date)
AXISC_DEFINED_ARRAY(xsdc__gYearMonth)
AXISC_DEFINED_ARRAY(xsdc__gYear)
AXISC_DEFINED_ARRAY(xsdc__gMonthDay)
AXISC_DEFINED_ARRAY(xsdc__gDay)
AXISC_DEFINED_ARRAY(xsdc__gMonth)
AXISC_DEFINED_POINTER_ARRAY(xsdc__string)
AXISC_DEFINED_POINTER_ARRAY(xsdc__normalizedString)
AXISC_DEFINED_POINTER_ARRAY(xsdc__token)
AXISC_DEFINED_POINTER_ARRAY(xsdc__language)
AXISC_DEFINED_POINTER_ARRAY(xsdc__Name)
AXISC_DEFINED_POINTER_ARRAY(xsdc__NCName)
AXISC_DEFINED_POINTER_ARRAY(xsdc__ID)
AXISC_DEFINED_POINTER_ARRAY(xsdc__IDREF)
AXISC_DEFINED_POINTER_ARRAY(xsdc__IDREFS)
AXISC_DEFINED_POINTER_ARRAY(xsdc__ENTITY)
AXISC_DEFINED_POINTER_ARRAY(xsdc__ENTITIES)
AXISC_DEFINED_POINTER_ARRAY(xsdc__NMTOKEN)
AXISC_DEFINED_POINTER_ARRAY(xsdc__NMTOKENS)
AXISC_DEFINED_ARRAY(xsdc__boolean)
AXISC_DEFINED_ARRAY(xsdc__base64Binary)
AXISC_DEFINED_ARRAY(xsdc__hexBinary)
AXISC_DEFINED_ARRAY(xsdc__float)
AXISC_DEFINED_ARRAY(xsdc__decimal)
AXISC_DEFINED_ARRAY(xsdc__integer)
AXISC_DEFINED_ARRAY(xsdc__nonPositiveInteger)
AXISC_DEFINED_ARRAY(xsdc__negativeInteger)
AXISC_DEFINED_ARRAY(xsdc__long)
AXISC_DEFINED_ARRAY(xsdc__int)
AXISC_DEFINED_ARRAY(xsdc__short)
AXISC_DEFINED_ARRAY(xsdc__byte)
AXISC_DEFINED_ARRAY(xsdc__nonNegativeInteger)
AXISC_DEFINED_ARRAY(xsdc__unsignedLong)
AXISC_DEFINED_ARRAY(xsdc__unsignedInt)
AXISC_DEFINED_ARRAY(xsdc__unsignedByte)
AXISC_DEFINED_ARRAY(xsdc__unsignedShort)
AXISC_DEFINED_ARRAY(xsdc__positiveInteger)
AXISC_DEFINED_ARRAY(xsdc__double)
AXISC_DEFINED_POINTER_ARRAY(xsdc__anyURI)
AXISC_DEFINED_POINTER_ARRAY(xsdc__QName)
AXISC_DEFINED_POINTER_ARRAY(xsdc__NOTATION)
 
static const xsdc__boolean xsdc_boolean_true = (xsdc__boolean) 1;
static const xsdc__boolean xsdc_boolean_false = (xsdc__boolean) 0;

typedef enum {
    AXISC_NORMAL_CHANNEL=0,
    AXISC_SSL_CHANNEL
} AXISC_CHANNEL_TYPE;

/**
 * @typedef AXISC_XML_String
 * Axis C++ defined type for xml encoded string. This is used only in AnyType.
 */
typedef char* AXISC_XML_String;

/**
 * @struct AxiscAnyType
 * Axis C++ defined type for handling xsd:any.
 */
typedef struct
{
    /**
     * @var _array Contains an array of xml encoded strings.
     */
    AXISC_XML_String* _array;

    /**
     * @var _size Contains how many xml strings are there in _array
     */
    int _size;
} AxiscAnyType;

#ifdef __cplusplus
  }
#endif

#endif
