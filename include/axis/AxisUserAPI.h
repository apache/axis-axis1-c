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

#if !defined(_AXISUSERAPI_H_OF_AXIS_INCLUDED_)
#define _AXISUSERAPI_H_OF_AXIS_INCLUDED_

#include <axis/GDefine.h>
#include <time.h>
#include <string.h>

 /**
  * @file AxisUserAPI.h
  * This file contains types defined in Axis C++. The mapping of basic xsd types
  * to the C language types.
  */

/**
 * @typedef xsd__string
 * Axis C++ defined type for xml basic type string
 */
typedef AxiscChar * xsd__string;

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
#ifdef WIN32
typedef __int64 xsd__long;
#else
typedef long long xsd__long;
#endif

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
typedef AxiscChar * xsd__QName;

/**
 * @typedef xsd__NCName
 * Axis C++ defined type for xml basic type NCName
 */
typedef AxiscChar * xsd__NCName;

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
typedef struct {
    xsd__unsignedByte * __ptr;
    xsd__int __size;
} xsd__hexBinary;

/**
 * @typedef xsd__anyURI
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxiscChar * xsd__anyURI;

/**
 * @typedef xsd__NMTOKEN
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxiscChar * xsd__NMTOKEN;

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
        type * m_Array;\
        int m_Size;\
    } type##_Array;

#define AXISC_DEFINED_ARRAY2(type) \
    typedef struct {\
        AXISCHANDLE m_Array;\
        int m_Size;\
    } type##_Array;

typedef struct {
    void* m_Array;
    int m_Size;
} Axisc_Array;

AXISC_DEFINED_ARRAY(xsd__string)
AXISC_DEFINED_ARRAY(xsd__integer)
AXISC_DEFINED_ARRAY(xsd__int)
AXISC_DEFINED_ARRAY(xsd__long)
AXISC_DEFINED_ARRAY(xsd__short)
AXISC_DEFINED_ARRAY(xsd__decimal)
AXISC_DEFINED_ARRAY(xsd__float)
AXISC_DEFINED_ARRAY(xsd__double)
AXISC_DEFINED_ARRAY(xsd__boolean)
AXISC_DEFINED_ARRAY(xsd__QName)
AXISC_DEFINED_ARRAY(xsd__NCName)
AXISC_DEFINED_ARRAY(xsd__dateTime)
AXISC_DEFINED_ARRAY(xsd__unsignedByte)
AXISC_DEFINED_ARRAY(xsd__unsignedInt)
AXISC_DEFINED_ARRAY(xsd__unsignedLong)
AXISC_DEFINED_ARRAY(xsd__unsignedShort)
AXISC_DEFINED_ARRAY2(xsd__base64Binary)
AXISC_DEFINED_ARRAY2(xsd__hexBinary)
AXISC_DEFINED_ARRAY(xsd__anyURI)
AXISC_DEFINED_ARRAY(xsd__NMTOKEN)
 
static const int xsd_boolean_true = 1;
static const int xsd_boolean_false = 0;

typedef enum {
    AXISC_NORMAL_CHANNEL=0,
    AXISC_SSL_CHANNEL
} AXISC_CHANNEL_TYPE;

/**
 * @typedef XML_String
 * Axis C++ defined type for xml encoded string. This is used only in AnyType.
 */
typedef char* XML_String;

/**
 * @struct AxiscAnyType
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
} AxiscAnyType;

#endif
