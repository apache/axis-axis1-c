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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4530)
#endif

#if !defined(__GDEFINE_INCLUDED__)
#define __GDEFINE_INCLUDED__
/* This file contains all global definitions that are valid across whole Axis C++ project.*/

typedef enum 
{ 
	AXIS_SUCCESS=0, 
	AXIS_FAIL = -1, 
	AXIS_OBJECT_ALREADY_EXISTS=1,
	AXIS_NO_SUCH_HANDLER,
	AXIS_NO_SUCH_SERVICE
} AXIS_GLOBAL_ERROR;
typedef enum { APTHTTP=1, APTFTP, APTSMTP, APTHTTPS, APTOTHER } AXIS_PROTOCOL_TYPE;
typedef enum { CRITICAL=1, WARN, INFO, TRIVIAL} AXIS_SEVERITY_LEVEL;

#define SOAPACTIONHEADER "SOAPAction"

#define AxisChar char
#define AxisXMLCh char
#define XML_Ch AxisChar

#ifdef __cplusplus
#define AxisString basic_string<char>
#define AxisXMLString basic_string<AxisXMLCh>
#endif

#ifdef WIN32
    #define AxisSprintf(X, Y, Z, W) sprintf(X, Z, W)
#else /*linux*/
    #define AxisSprintf(X, Y, Z, W) sprintf(X, Z, W)
#endif

extern void Ax_Sleep(int);
extern void ModuleInitialize();
extern void ModuleUnInitialize();

#if defined(__GNUC__)
#define AXISCALL __attribute__((stdcall))
#else
#define AXISCALL __stdcall
#endif

#if defined(__GNUC__)
# if defined(__GNU_PATCHLEVEL__)
#  define __GNUC_VERSION__ (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100 \
                            + __GNUC_PATCHLEVEL__)
# else
#  define __GNUC_VERSION__ (__GNUC__ * 10000 \
                            + __GNUC_MINOR__ * 100)
# endif
#endif

/**
 * Following macro define an API function of Axis C++
 * Format of the AXISAPI macro is as follows
 *		AXISAPI(<METHOD NAME>, <PARAMETER LIST>)
 */

#ifdef __cplusplus
    #define AXISAPI(M, P) AXISCALL M P = 0;
    #define APIHASPARAMS
    #define APINOPARAMS 
#else 
    #define virtual 
    #if !defined(bool)
        #define bool unsigned char
        #define false 0
        #define true 1
    #endif
    #if !defined(NULL)
        #define NULL 0
    #endif
    #define AXISAPI(M, P) (AXISCALL* M) P;
    #define APIHASPARAMS void*p,
    #define APINOPARAMS void*p
#endif

#if defined (__GNUC__)
#if __GNUC_VERSION__ > 30000
#define AXISDESTRUCTOR void* unused; void AXISAPI(destructor,(APINOPARAMS))
#else
#define AXISDESTRUCTOR void* unused; void*unused1; void AXISAPI(destructor,(APINOPARAMS))
#endif
#else 
#define AXISDESTRUCTOR void AXISAPI(destructor,(APINOPARAMS))
#endif
#endif /*__GDEFINE_INCLUDED__*/
