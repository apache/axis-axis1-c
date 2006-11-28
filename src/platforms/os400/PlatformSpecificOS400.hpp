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

// =============================================================
// Default paths to shared library/DLLs and files
// =============================================================

#define PLATFORM_DEFAULT_DEPLOY_PATH ""

#define PLATFORM_XMLPARSER_PATH      PLATFORM_DEFAULT_DEPLOY_PATH "libaxis_xmlparser.so"
#define PLATFORM_TRANSPORTHTTP_PATH  PLATFORM_DEFAULT_DEPLOY_PATH "libhttp_transport.so"
#define PLATFORM_CHANNEL_PATH        PLATFORM_DEFAULT_DEPLOY_PATH "libhttp_channel.so"
#define PLATFORM_SSLCHANNEL_PATH     PLATFORM_DEFAULT_DEPLOY_PATH "Unknown"

#define PLATFORM_LOG_PATH            "/usr/local/axiscpp_deploy/log/AxisLog"
#define PLATFORM_CLIENTLOG_PATH      "/usr/local/axiscpp_deploy/log/AxisClientLog"
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
// CANNOT be used with constants
extern char*      strtoasc( char* );
extern char*      asctostr( char* );
#define PLATFORM_STRTOASC( x ) strtoasc( (char*)(x) )
#define PLATFORM_ASCTOSTR( x ) asctostr( (char*)(x) )

// reference to ebcdic to ascii conversion table 
extern const char EBCDICtoASCII[256];

// Following returns a buffer that must be free'ed by caller. 
extern char *toUTF8(char *b, int len);

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
#define PLATFORM_GET_THREAD_ID pthread_self()

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

/**
 * For debugging
 */
static void traceData(void *d, int length)
{
    char logFile[1024];
    sprintf(logFile, "/tmp/axis.log");
    FILE *fh = fopen(logFile, "ab, codepage=819");
    setvbuf(fh, NULL, _IOFBF, (size_t)(4*1024));
    fwrite(d, 1, length, fh);
    fwrite("\x0d\x0a\x2b\x2b\x2b\x2b\x2b\x2b\x0d\x0a", 1, 10, fh);
    fflush(fh);
    fclose(fh);
}


#endif


