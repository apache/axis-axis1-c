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
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */
/* AxisUserAPI.h: interface for the AxisUserAPI class.*/

#if !defined(_AXISUSERAPI_H____OF_AXIS_INCLUDED_)
#define _AXISUSERAPI_H____OF_AXIS_INCLUDED_

#include <time.h>
#include <string.h>

#define AxisChar char

typedef AxisChar * xsd__string;
typedef int xsd__integer;
typedef int xsd__int;
typedef long xsd__long;
typedef short xsd__short;
typedef double xsd__decimal;
typedef float xsd__float;
typedef double xsd__double;
typedef enum { false_=0, true_ } xsd__boolean;
typedef unsigned char xsd__byte;
typedef AxisChar * xsd__QName;
typedef struct tm xsd__dateTime;
typedef struct tm xsd__date;
typedef struct tm xsd__time;
typedef unsigned char xsd__unsignedByte;
typedef unsigned int xsd__unsignedInt;
typedef unsigned long xsd__unsignedLong;
typedef unsigned short xsd__unsignedShort;
typedef struct {
    xsd__unsignedByte * __ptr;
    xsd__int __size;
} xsd__base64Binary;
typedef struct{
    xsd__unsignedByte * __ptr;
    xsd__int __size;
} xsd__hexBinary;
typedef AxisChar * xsd__anyURI;

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
 
#define AXIS_OUT_PARAM 

static const int xsd_boolean_true = 1;
static const int xsd_boolean_false = 0;

typedef enum {
    NORMAL_CHANNEL=0,
    SSL_CHANNEL
} AXIS_CHANNEL_TYPE;

#endif
