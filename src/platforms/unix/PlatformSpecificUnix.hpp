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


#if !defined(_PLATFORM_SPECIFIC_UNIX_HPP)
#define _PLATFORM_SPECIFIC_UNIX_HPP


// =============================================================
// Default paths to shared library/DLLs and files
// =============================================================
#define PLATFORM_XMLPARSER_PATH      "/usr/local/axiscpp_deploy/lib/libaxis_xmlparser.so"
#define PLATFORM_TRANSPORTHTTP_PATH  "/usr/local/axiscpp_deploy/lib/libaxis_transport.so"

#define PLATFORM_LOG_PATH            "/usr/local/axiscpp_deploy/log/AxisLog"
#define PLATFORM_CLIENTLOG_PATH      "/usr/local/axiscpp_deploy/log/AxisClientLog"
#define PLATFORM_CONFIG_PATH         "/etc/axiscpp.conf"

// =============================================================
// Library loading and procedure resolution
// =============================================================
#ifdef USE_LTDL
 #include <ltdl.h>
 #define DLHandler lt_dlhandle

 #define PLATFORM_LOADLIBINIT       lt_dlinit
 #define PLATFORM_LOADLIB(_lib)     lt_dlopen(_lib)
 #define PLATFORM_UNLOADLIB         lt_dlclose
 #define PLATFORM_GETPROCADDR       lt_dlsym
 #define PLATFORM_LOADLIBEXIT       lt_dlexit
#else
 #include <dlfcn.h>
 #define DLHandler void*

 #define PLATFORM_LOADLIBINIT()
 #define PLATFORM_LOADLIB(_lib)     dlopen(_lib, RTLD_LAZY)
 #define PLATFORM_UNLOADLIB         dlclose
 #define PLATFORM_GETPROCADDR       dlsym
 #define PLATFORM_LOADLIBEXIT()
#endif

// =============================================================
// National Language Support
// =============================================================

// STRTOASC is to translate single byte 'native' character representation to ASCII
// ASCTOSTR is to translate single byte ascii representation to 'native' character
// CANNOT be used with constants
#define PLATFORM_STRTOASC( x ) ( x )
#define PLATFORM_ASCTOSTR( x ) ( x )

#endif

