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
 *
 */

#if !defined(_AXISUSERAPI_H____OF_AXIS_INCLUDED_)
#define _AXISUSERAPI_H____OF_AXIS_INCLUDED_

#include <axis/server/GDefine.h>
#include <time.h>
#include <string.h>

 /**
  * @file AxisUserAPI.h
  * This file contains types defined in Axis C++. The mapping of basic xsd types
  * to the C language types.
  * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
  */
#define AxisChar char

/**
 * @typedef xsd__string
 * Axis C++ defined type for xml basic type string
 */
typedef AxisChar * xsd__string;
/**
 * @typedef xsd__integer
 * Axis C++ defined type for xml basic type integer
 */
typedef int xsd__integer;
/**
 * @typedef xsd__int
 * Axis C++ defined type for xml basic type int
 */
typedef int xsd__int;
/**
 * @typedef xsd__long
 * Axis C++ defined type for xml basic type long
 */
typedef long xsd__long;
/**
 * @typedef xsd__short
 * Axis C++ defined type for xml basic type short
 */
typedef short xsd__short;
/**
 * @typedef xsd__decimal
 * Axis C++ defined type for xml basic type decimal
 */
typedef double xsd__decimal;
/**
 * @typedef xsd__float
 * Axis C++ defined type for xml basic type float
 */
typedef float xsd__float;
/**
 * @typedef xsd__double
 * Axis C++ defined type for xml basic type double
 */
typedef double xsd__double;
/**
 * @typedef xsd__boolean
 * Axis C++ defined type for xml basic type boolean
 */
typedef enum { false_=0, true_ } xsd__boolean;
/**
 * @typedef xsd__byte
 * Axis C++ defined type for xml basic type byte
 */
typedef signed char xsd__byte;
/**
 * @typedef xsd__QName
 * Axis C++ defined type for xml basic type QName
 */
typedef AxisChar * xsd__QName;
/**
 * @typedef xsd__dateTime
 * Axis C++ defined type for xml basic type dateTime
 */
typedef struct tm xsd__dateTime;
/**
 * @typedef xsd__date
 * Axis C++ defined type for xml basic type date
 */
typedef struct tm xsd__date;
/**
 * @typedef xsd__time
 * Axis C++ defined type for xml basic type time
 */
typedef struct tm xsd__time;
/**
 * @typedef xsd__unsignedByte
 * Axis C++ defined type for xml basic type unsignedByte
 */
typedef unsigned char xsd__unsignedByte;
/**
 * @typedef xsd__unsignedInt
 * Axis C++ defined type for xml basic type unsignedInt
 */
typedef unsigned int xsd__unsignedInt;
/**
 * @typedef xsd__unsignedLong
 * Axis C++ defined type for xml basic type unsignedLong
 */
typedef unsigned long xsd__unsignedLong;
/**
 * @typedef xsd__unsignedShort
 * Axis C++ defined type for xml basic type unsignedShort
 */
typedef unsigned short xsd__unsignedShort;
/**
 * @struct xsd__base64Binary
 * Axis C++ defined type for xml basic type base64Binary
 */
typedef struct {
    xsd__unsignedByte * __ptr;
    xsd__int __size;
} xsd__base64Binary;
/**
 * @struct xsd__hexBinary
 * Axis C++ defined type for xml basic type hexBinary
 */
typedef struct{
    xsd__unsignedByte * __ptr;
    xsd__int __size;
} xsd__hexBinary;
/**
 * @typedef xsd__anyURI
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxisChar * xsd__anyURI;
/**
 * @typedef xsd__NMTOKEN
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxisChar * xsd__NMTOKEN;
/**
 * @enum AXIS_BINDING_STYLE
 * Enumeration for the different wsdl styles. This is used by the Axis
 * engine to identify the web service or client style.
 */
typedef enum {
    RPC_ENCODED, /*default*/
    DOC_LITERAL,
    RPC_LITERAL
} AXIS_BINDING_STYLE;

#define AXIS_DEFINED_ARRAY(type) \
    struct {\
        type * m_Array;\
        int m_Size;\
    }

typedef AXIS_DEFINED_ARRAY(void) Axis_Array;
typedef AXIS_DEFINED_ARRAY(xsd__string) xsd__string_Array;
typedef AXIS_DEFINED_ARRAY(xsd__integer) xsd__integer_Array;
typedef AXIS_DEFINED_ARRAY(xsd__int) xsd__int_Array;
typedef AXIS_DEFINED_ARRAY(xsd__long) xsd__long_Array;
typedef AXIS_DEFINED_ARRAY(xsd__short) xsd__short_Array;
typedef AXIS_DEFINED_ARRAY(xsd__decimal) xsd__decimal_Array;
typedef AXIS_DEFINED_ARRAY(xsd__float) xsd__float_Array;
typedef AXIS_DEFINED_ARRAY(xsd__double) xsd__double_Array;
typedef AXIS_DEFINED_ARRAY(xsd__boolean) xsd__boolean_Array;
typedef AXIS_DEFINED_ARRAY(xsd__QName) xsd__QName_Array;
typedef AXIS_DEFINED_ARRAY(xsd__dateTime) xsd__dateTime_Array;
typedef AXIS_DEFINED_ARRAY(xsd__unsignedByte) xsd__unsignedByte_Array;
typedef AXIS_DEFINED_ARRAY(xsd__unsignedInt) xsd__unsignedInt_Array;
typedef AXIS_DEFINED_ARRAY(xsd__unsignedLong) xsd__unsignedLong_Array;
typedef AXIS_DEFINED_ARRAY(xsd__unsignedShort) xsd__unsignedShort_Array;
typedef AXIS_DEFINED_ARRAY(xsd__base64Binary) xsd__base64Binary_Array;
typedef AXIS_DEFINED_ARRAY(xsd__hexBinary) xsd__hexBinary_Array;
typedef AXIS_DEFINED_ARRAY(xsd__anyURI) xsd__anyURI_Array;
typedef AXIS_DEFINED_ARRAY(xsd__NMTOKEN) xsd__NMTOKEN_Array;
 
#define AXIS_OUT_PARAM 

static const int xsd_boolean_true = 1;
static const int xsd_boolean_false = 0;

typedef enum {
    NORMAL_CHANNEL=0,
    SSL_CHANNEL
} AXIS_CHANNEL_TYPE;

/**
 * @typedef XML_String
 * Axis C++ defined type for xml encoded string. This is used only in AnyType.
 */
typedef char* XML_String;

/**
 * @struct AnyType
 * Axis C++ defined type for handling xsd:any.
 */
typedef struct 
{
    /**
     * @var _array Contains an array of xml encoded strings.
     */
    XML_String* _array;
    /**
     * @var _size Contains how many xml strings are there in _array
     */
    int _size;
} AnyType;

#endif
