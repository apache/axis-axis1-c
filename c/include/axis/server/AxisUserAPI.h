/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */
/* AxisUserAPI.h: interface for the AxisUserAPI class.*/

#if !defined(AFX_AXISUSERAPI_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_)
#define AFX_AXISUSERAPI_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_

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

#endif /* !defined(AFX_AXISUSERAPI_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_) */
