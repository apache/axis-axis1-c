/*
 *   Copyright 2004-2004 The Apache Software Foundation.
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

//#define _WIN32_WINNT 0x0400
#define _WINSOCKAPI_ /* Prevent inclusion of winsock.h in windows.h */
#include <windows.h>

// =============================================================
// Default paths to shared library/DLLs and files
// =============================================================
#ifdef _DEBUG
  #define PLATFORM_XMLPARSER_PATH      "AxisXMLParser_D.dll"
  #define PLATFORM_TRANSPORTHTTP_PATH  "AxisTransport_D.dll"
#else
  #define PLATFORM_XMLPARSER_PATH      "AxisXMLParser.dll"
  #define PLATFORM_TRANSPORTHTTP_PATH  "AxisTransport.dll"
#endif
#define PLATFORM_CHANNEL_PATH		   "????"
#define PLATFORM_SSLCHANNEL_PATH	   "????"

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
#define PLATFORM_LOADLIB(_lib)     LoadLibrary(_lib)
#define PLATFORM_UNLOADLIB         FreeLibrary
#define PLATFORM_GETPROCADDR       GetProcAddress
#define PLATFORM_LOADLIBEXIT()
#define PLATFORM_LOADLIB_ERROR     ""

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
#define PLATFORM_SLEEP(x) Sleep(0);

#endif


