/*
 *   Copyright 2004-2004 The Apache Software Foundation.
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


#if !defined( _PLATFORM_SPECIFIC_WINDOWS_HPP )
#define _PLATFORM_SPECIFIC_WINDOWS_HPP

#ifndef _CRT_SECURE_NO_WARNINGS
  #define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
  #define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef _USE_32BIT_TIME_T
  #define _USE_32BIT_TIME_T
#endif

// C4101: 'identifier' : unreferenced local variable (revisit this)
#pragma warning (disable : 4101)

// C4251: class xx needs to have dll-interface to be used by clients of class bb
#pragma warning (disable : 4251)

// C4275: non dll-interface class used as base for dll-interface class
#pragma warning (disable : 4275)

// C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#pragma warning (disable : 4290)

// C4297: function assumed not to throw an exception but does
#pragma warning (disable : 4297)

// C4503: decorated name length exceeded, name was truncated
#pragma warning (disable : 4503)

// C4786: identifier was truncated to '255' characters in the debug information
#pragma warning (disable : 4786)

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN  

//#define _WIN32_WINNT 0x0400
#define _WINSOCKAPI_ /* Prevent inclusion of winsock.h in windows.h */
#include <windows.h>
#include <string>
#include <sys/timeb.h>

// =============================================================
// Default paths to shared library/DLLs and files
// =============================================================
#define PLATFORM_DEFAULT_DEPLOY_PATH ""

#ifdef _DEBUG
  #define PLATFORM_XMLPARSER_PATH      "AxisXMLParser_D.dll"
  #define PLATFORM_TRANSPORTHTTP_PATH  "HTTPTransport_D.dll"
  #define PLATFORM_CHANNEL_PATH		   "HTTPChannel_D.dll"
  #define PLATFORM_SSLCHANNEL_PATH	   "Unknown"
#else
  #define PLATFORM_XMLPARSER_PATH      "AxisXMLParser.dll"
  #define PLATFORM_TRANSPORTHTTP_PATH  "HTTPTransport.dll"
  #define PLATFORM_CHANNEL_PATH		   "HTTPChannel.dll"
  #define PLATFORM_SSLCHANNEL_PATH	   "Unknown"
#endif

#define PLATFORM_LOG_PATH            ""
#define PLATFORM_CLIENTLOG_PATH      ""
#define PLATFORM_CONFIG_PATH         "/axiscpp.conf"
#define PLATFORM_SECUREINFO			 ""

// =============================================================
// Library loading and procedure resolution
// =============================================================
#define DLHandler HINSTANCE
#define RTLD_LAZY 0    // not sure this is needed?

#define PLATFORM_LOADLIBINIT()
#define PLATFORM_LOADLIB(_lib)     callLoadLib(_lib)
#define PLATFORM_UNLOADLIB         FreeLibrary
#define PLATFORM_GETPROCADDR       GetProcAddress
#define PLATFORM_LOADLIBEXIT()
#define PLATFORM_LOADLIB_ERROR     PLATFORM_GET_ERROR_MESSAGE(GetLastError()) 

// =============================================================
// National Language Support
// =============================================================

// STRTOASC is to translate single byte 'native' character representation to ASCII
// ASCTOSTR is to translate single byte ascii representation to 'native' character
// CANNOT be used with constants
#define PLATFORM_STRTOASC( x ) ( x )
#define PLATFORM_ASCTOSTR( x ) ( x )

// =============================================================
// Miscellaneous
// =============================================================
#define PLATFORM_SLEEP(x) Sleep(x)

/**
 * Get the last error code from the system.
 * Please ensure that this is a thread safe implementation
 * and that it returns a long
 * @return long the lsat error message for this thread
 */
#define GETLASTERROR GetLastError()

/**
 * From the last error number get a sensible std::string representing it
 * @param errorNumber the error Number you are trying to get a message for
 * @return the error message. NOTE: The caller is responsible for deleting the returned string
 */
#define PLATFORM_GET_ERROR_MESSAGE(errorNumber) getPlatformErrorMessage(errorNumber)

/**
 * type to be used for 64bit integers
 */
#define LONGLONG __int64
#define LONGLONGVALUE(value) value##I64
#define UNSIGNED_LONGLONGVALUE(value) value##UI64

/**
 * Format string to be used in printf for 64bit integers
 */
#define PRINTF_LONGLONG_FORMAT_SPECIFIER "%I64d"
#define PRINTF_LONGLONG_FORMAT_SPECIFIER_CHARS "I64d"
#define PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER "%I64u"
#define PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER_CHARS "I64u"

/**
 * Platform specific method to obtain current thread ID
 */
#define PLATFORM_GET_THREAD_ID GetCurrentThreadId()

/**
 * Platform specific method to obtain current time in milli seconds
 */
#define PLATFORM_GET_TIME_IN_MILLIS _ftime
#define PLATFORM_TIMEB _timeb

std::string getPlatformErrorMessage(long errorNumber);

HMODULE callLoadLib(LPCTSTR lib);

#endif


