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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4530)
#endif

#if !defined(__GDEFINE_OF_AXIS_INCLUDED__)
#define __GDEFINE_OF_AXIS_INCLUDED__

/* This file contains all global definitions that are valid across whole
 * Axis C++ project.
 */

typedef enum {SECURE, UNSECURE} AXIS_SECURE_PROTOCOL;

typedef enum 
{ 
    AXIS_SUCCESS=0, 
    AXIS_FAIL = -1, 
    AXIS_OBJECT_ALREADY_EXISTS=1,
    AXIS_NO_SUCH_HANDLER,
    AXIS_NO_SUCH_SERVICE
} AXIS_GLOBAL_ERROR;
typedef enum 
{ 
    APTHTTP=1, APTFTP, APTSMTP, APTHTTPS, APTOTHER 
} AXIS_PROTOCOL_TYPE;
typedef enum 
{ 
    CRITICAL=1, WARN, INFO, TRIVIAL
} AXIS_SEVERITY_LEVEL;

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
#else /* linux */
    #define AxisSprintf(X, Y, Z, W) sprintf(X, Z, W)
#endif

extern void Ax_Sleep(int);
extern void ModuleInitialize();
extern void ModuleUnInitialize();

#if defined(WIN32) 
#define STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define STORAGE_CLASS_INFO 
#endif

#if defined(__GNUC__)
//replaced stdcall with cdecl to make it work on some platforms with older libraries - Samisa
//#define AXISCALL __attribute__((stdcall))
#define AXISCALL __attribute__((cdecl))
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

/*
 * Following macro define an API function of Axis C++
 * Format of the AXISAPI macro is as follows
 * AXISAPI(<METHOD NAME>, <PARAMETER LIST>)
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

/*This was a hack to work around gcc version problems; hence commented out - samisa
#if defined (__GNUC__)
#if __GNUC_VERSION__ > 30000
#define AXISDESTRUCTOR void* unused; void AXISAPI(destructor,(APINOPARAMS))
#else
#define AXISDESTRUCTOR void* unused; void*unused1; 
void AXISAPI(destructor,(APINOPARAMS))
#endif
#else 
#define AXISDESTRUCTOR void AXISAPI(destructor,(APINOPARAMS))
#endif
*/

#endif 


