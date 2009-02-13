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

#if !defined(_PLATFORM_SPECIFIC_OS400_HPP)
#define _PLATFORM_SPECIFIC_OS400_HPP


#include <stdio.h>      
#include <stdlib.h>      
#include <string.h>      
#include <errno.h>
#include <stdarg.h>
#include <time.h>       // strftime(), localtime()      
#include <sys/time.h>   // gettimeofday()
#include <unistd.h>     // access()
#include <string>  

#define DIR_SEPARATOR   '/'
#define DIR_SEPARATOR_S "/"

// =============================================================
// Default paths to shared library/DLLs and files
// =============================================================

#define PLATFORM_DEFAULT_DEPLOY_PATH ""

#define PLATFORM_XMLPARSER_PATH      PLATFORM_DEFAULT_DEPLOY_PATH "/lib/libaxis_xmlparser.so"
#define PLATFORM_TRANSPORTHTTP_PATH  PLATFORM_DEFAULT_DEPLOY_PATH "/lib/libhttp_transport.so"
#define PLATFORM_CHANNEL_PATH        PLATFORM_DEFAULT_DEPLOY_PATH "/lib/libhttp_channel.so"
#define PLATFORM_SSLCHANNEL_PATH     PLATFORM_DEFAULT_DEPLOY_PATH "Unknown"

#define PLATFORM_LOG_PATH            ""
#define PLATFORM_CLIENTLOG_PATH      ""
#define PLATFORM_CONFIG_PATH         "/etc/axiscpp.conf"

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
#define PLATFORM_LOADLIB_ERROR     string(os400_dlerror())

extern void	*os400_dlopen(const char *);
extern void	*os400_dlsym(void *, const char *);
extern int   os400_dlclose(void *);
extern char *os400_dlerror();

// =============================================================
// National Language Support
// =============================================================

// STRTOASC is to translate single byte 'native' character representation to ASCII
// ASCTOSTR is to translate single byte ascii representation to 'native' character (EBCDIC)
// CANNOT be used with constants.  
extern char*      strtoasc( char* );
extern char*      asctostr( char* );
#define PLATFORM_STRTOASC( x ) strtoasc( (char*)(x) )
#define PLATFORM_ASCTOSTR( x ) asctostr( (char*)(x) )

// reference to ebcdic to ascii conversion table 
extern const char EBCDICtoASCII[256];

// Turkish double quote in EBCDIC is not invariant (i.e. the hexadecimal
// value for double quote is different in turkish locale than when running
// in english locale).  This, when using double quotes we must reference the 
// following, which will be set to proper value on EBCDIC-based systems.

extern char PLATFORM_DOUBLE_QUOTE_S[];
extern char PLATFORM_DOUBLE_QUOTE_C;

extern char PLATFORM_XML_ENTITY_REFERENCE_CHARS_S[];

// =============================================================
// Miscellaneous
// =============================================================
#include <sys/time.h>
#include <pthread.h> 
#include <unistd.h>
#include <errno.h>
#define PLATFORM_SLEEP(x) sleep(x)


/**
 * Get the last error code from the system.
 * Please ensure that this is a thread safe implementation
 * and that it returns a long
 * @return long the lsat error message for this thread
 */
#define GETLASTERROR errno


/**
 * From the last error number get a sensible std::string representing it
 * @param errorNumber the error Number you are trying to get a message for
 * @return the error message. 
 */
#include <string>
#define PLATFORM_GET_ERROR_MESSAGE(errorNumber) string(strerror(errorNumber))

/**
 * Platform specific method to obtain current thread ID
 */
#define PLATFORM_GET_THREAD_ID os400_getThreadID()

inline long long os400_getThreadID()
{
	pthread_id_np_t tid = pthread_getthreadid_np();
	return *((long long *)&tid);
}

/**
 * Platform specific method to obtain current time in milli seconds
 */
struct os400_timeb                                                               
{                                                                          
     long  time;                       
     long  millitm;                    
};  

static int os400_ftime(struct os400_timeb * tp)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    tp->time    = t.tv_sec;
    tp->millitm = t.tv_usec/1000;
    return 0;
}
                                                                       
#define PLATFORM_GET_TIME_IN_MILLIS  os400_ftime
#define PLATFORM_TIMEB os400_timeb


/**
 * type to be used for 64bit integers
 */
#define LONGLONG long long
#define LONGLONGVALUE(value) value##LL
#define UNSIGNED_LONGLONGVALUE(value) value##ULL

/**
 * Format string to be used in printf for 64bit integers
 */
#define PRINTF_LONGLONG_FORMAT_SPECIFIER "%lld"
#define PRINTF_LONGLONG_FORMAT_SPECIFIER_CHARS "lld"
#define PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER "%llu"
#define PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER_CHARS "llu"
#define PRINTF_LONGLONG_LOG_FORMAT_SPECIFIER "%.8llu"

/**
 * File modes
 */
#define TRACE_FILE_MODE1   "a, o_ccsid=1208, crln=N"
#define TRACE_FILE_MODE2   "a, o_ccsid=0, crln=N"

#endif
