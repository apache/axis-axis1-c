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


#if !defined(_PLATFORM_SPECIFIC_OS400_HPP)
#define _PLATFORM_SPECIFIC_OS400_HPP


// =============================================================
// Default paths to shared library/DLLs and files
// =============================================================
#define PLATFORM_XMLPARSER_PATH      "libaxis_xmlparser.so"
#define PLATFORM_TRANSPORTHTTP_PATH  "libhttp_transport.so"

#define PLATFORM_LOG_PATH            "/usr/local/axiscpp_deploy/log/AxisLog"
#define PLATFORM_CLIENTLOG_PATH      "/usr/local/axiscpp_deploy/log/AxisClientLog"
#define PLATFORM_CONFIG_PATH         "/etc/axiscpp.conf"
#define PLATFORM_CHANNEL_PATH        "libhttp_channel.so"
#define PLATFORM_SSLCHANNEL_PATH     "libhttp_channelssl.so"
#define PLATFORM_SECUREINFO			 ""

// =============================================================
// Library loading and procedure resolution
// =============================================================
#define DLHandler void*
#define RTLD_LAZY 0    // not sure this is needed?

#define PLATFORM_LOADLIBINIT()
#define PLATFORM_LOADLIB(_lib)     os400_dlopen(_lib)
#define PLATFORM_UNLOADLIB         os400_dlclose
#define PLATFORM_GETPROCADDR       os400_dlsym
#define PLATFORM_LOADLIBEXIT()
#define PLATFORM_LOADLIB_ERROR     ""

extern void	*os400_dlopen(const char *);
extern void	*os400_dlsym(void *, const char *);
extern int   os400_dlclose(void *);

// =============================================================
// National Language Support
// =============================================================

// STRTOASC is to translate single byte 'native' character representation to ASCII
// ASCTOSTR is to translate single byte ascii representation to 'native' character (EBCDIC)
// CANNOT be used with constants
extern char*      cvtSingleByteEbcdicToAsciiStr( char* );
extern char*      cvtSingleByteAsciiToEbcdicStr( char* );
#define PLATFORM_STRTOASC( x ) cvtSingleByteEbcdicToAsciiStr( (char*)(x) )
#define PLATFORM_ASCTOSTR( x ) cvtSingleByteAsciiToEbcdicStr( (char*)(x) )

// =============================================================
// Miscellaneous
// =============================================================
#include <sys/time.h>
#include <unistd.h>
#define PLATFORM_SLEEP(x) sleep(0);

/**
 * Get the last error code from the system.
 * Please ensure that this is a thread safe implementation
 * and that it returns a long
 * @return long the lsat error message for this thread
 */
#define GETLASTERROR -1;


/**
 * From the last error number get a sensible std::string representing it
 * @param errorNumber the error Number you are trying to get a message for
 * @return the error message. NOTE: The caller is responsible for deleting the returned string
 */
#include <string>
#define PLATFORM_GET_ERROR_MESSAGE(errorNumber) new string();

#endif


