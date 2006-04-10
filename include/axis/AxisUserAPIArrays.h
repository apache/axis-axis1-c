/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 * (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

#if !defined(_AXISUSERAPIARRAYSC_H____OF_AXIS_INCLUDED_)
#define _AXISUSERAPIARRAYSC_H____OF_AXIS_INCLUDED_

#include <time.h>
#include <string.h>

#include <axis/GDefine.h>
#include <axis/TypeMapping.h>
#include <axis/AxisUserAPI.h>


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

 /**
  * @file AxisUserAPIArrays.h
  * This file contains arrays defined for the basic types declared in AxisUserAPI.h
  */

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
    void** m_Array;
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
 
#ifdef __cplusplus
  }
#endif

#endif

