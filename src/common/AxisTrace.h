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
 */ 

/**
 * @file AxisTrace.h
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
  
#ifndef __AXISLOG_H_INCLUDED_
#define __AXISLOG_H_INCLUDED_

#include "AxisFile.h"
#include <string>
#include <stack>
#include <stdio.h>
#include <stdarg.h>

#if defined(ENABLE_AXISTRACE)  
  #define AXISTRACE1(X, Y) AxisTrace::logaxis(X,Y,__FILE__,__LINE__);
  #define AXISTRACE2(X, Y, Z) AxisTrace::logaxis(X,Y,Z,__FILE__,__LINE__);
  #define AXISTRACE3(X) AxisTrace::trace(X);
#else
  #define AXISTRACE1(X,Y)
  #define AXISTRACE2(X,Y,Z)
  #define AXISTRACE3(X)
#endif

typedef enum 
{ 
    CRITICAL=1, WARN, INFO, TRIVIAL
} AXIS_SEVERITY_LEVEL;

/**
 * @class AxisTrace
 * @brief This is class is used to log messages when AXISTRACE is defined.
 *
 * writing to the log could be disabled by commenting the line 
 * #define ENABLE_AXISTRACE
 * of Axisconfig.h.   
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */

AXIS_CPP_NAMESPACE_START

// Unfortunately the trace type has to be an int with #defines, not an enum because
// it is used with '...' and va_args, and ints can be used with '...' but enums 
// cannot.
#define TRACETYPE_UNKNOWN	0
#define TRACETYPE_CHAR		1
#define TRACETYPE_USHORT	2
#define TRACETYPE_SHORT		3
#define TRACETYPE_UINT		4
#define TRACETYPE_INT		5
#define TRACETYPE_ULONG		6
#define TRACETYPE_LONG		7
#define TRACETYPE_UDOUBLE	8
#define TRACETYPE_DOUBLE	9
#define TRACETYPE_FLOAT		10
#define TRACETYPE_BOOL		11
#define TRACETYPE_POINTER	12
#define TRACETYPE_DATA		13
#define TRACETYPE_STRING	14
#define TRACETYPE_STLSTRING	15
#define TRACETYPE_ANONYMOUS	16

class AxisTraceEntrypoints {
public:
    void (*m_traceLine)(const char *data);
    void (*m_traceEntry)(const char *className, const char *methodName, const void* that, int nParms, va_list vargs);
    void (*m_traceExit)(const char *className, const char *methodName, int returnIndex,
		int type, unsigned len, void *value);
    void (*m_traceCatch)(const char *className, const char *methodName, int catchIndex,
		int type, unsigned len, void *value);
    bool m_traceOn;
};

#ifdef AXISTRACE_LIBRARY
    extern AxisTraceEntrypoints *g_traceEntrypoints;
#endif
#ifdef AXISTRACE_LIBRARY_MAINENTRYPOINT
    AxisTraceEntrypoints *g_traceEntrypoints = NULL;
#endif

#ifdef WIN32
#pragma warning (disable : 4251)
#endif

class STORAGE_CLASS_INFO AxisTrace
{
public:
    AxisTrace() {};
    virtual ~AxisTrace() {};

    /**
     * This is called in writing to the log file whose path is specified in 
     * $AXIS_HOME/axiscpp.conf file.
     * This method is used when the caller has only one 
     * string message as argument. User
     * can also specify the severity of the message by assigning level 
     * argument to one
     * of CRITICAL, WARN, INFO or TRIVIAL.
     * @param sLog string message
     * @param level severity level
     * @param arg2 file name
     * @param arg3 line number
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    static int logaxis(const char* sLog, int level, char* arg2, int arg3);

    /**
     * This is called in writing to the log file whose path is specified in 
     * $AXIS_HOME/axiscpp.c     * onf file.
     * This method is used when the caller has two string messages 
     * as arguments. One may be his      *own message.
     * The other may be to print a trace value. User can also specify the 
     * severity of the messag     *e by
     * assigning level argument to one of CRITICAL, WARN, INFO or TRIVIAL.
     * @param sLog1 string message one
     * @param sLog2 string message two  
     * @param level severity level
     * @param arg3 file name
     * @param arg4 line number
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not     * (AXIS_FAIL).
     */
    static int logaxis(const char* sLog1, const char* sLog2, int level, char* arg3, 
        int arg4);

    /**
     * Writes the given string to the standard console. 
     * This method is useful when using the standalone server.
     * @param pchLog The given string which will be printed to the 
     * standard console.
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    static int trace(const char* pchLog);

    /**
     * Log file is opened for logging server side log messages
     *
     * The file is created( if one is already not there) with the name and 
     * path specified in $AXIS_HOME/axiscpp.conf file when web server loads.
     *
     * @return The status which indicates whether the operation is successful
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    static int openFile();

    /**
     * Log file is opened for logging client side log messages
     *
     * The file is created with the name ClientAxisLog if one is not 
     * already in the current path.
     * 
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    static int openFileByClient();

    /**
     * Finds out whether trace is on.
     */
#ifdef AXISTRACE_LIBRARY
    static inline bool isTraceOn() { return g_traceEntrypoints->m_traceOn; }
#else
    static bool isTraceOn();
#endif

    /**
     * Traces a single line.
     */  
#ifdef AXISTRACE_LIBRARY
    static inline void traceLine(const char *data) {(*g_traceEntrypoints->m_traceLine)(data); }
#else
    static inline void traceLine(const char *data) {traceLineInternal(data);}
#endif
    static void traceLineInternal(const char *data);

	/**
	 * Traces the entry to a method.
	 */
#ifdef AXISTRACE_LIBRARY
    static inline void traceEntry(const char *className, const char *methodName, const void* that, int nParms, ...) { 
            va_list vargs;
            va_start(vargs,nParms);
            (*g_traceEntrypoints->m_traceEntry)(className,methodName,that,nParms,vargs);
            va_end(vargs);
    }
#else
    static inline void traceEntry(const char *className, const char *methodName, const void* that, int nParms, ...) {
            va_list vargs;
            va_start(vargs,nParms);
            traceEntryInternal(className,methodName,that,nParms,vargs);
            va_end(vargs);
    }
#endif
	static void traceEntryInternal(const char *className, const char *methodName, 
            const void* that, int nParms, va_list vargs);

	/**
	 * Traces the exit to a method.
	 */
#ifdef AXISTRACE_LIBRARY
    static inline void traceExit(const char *className, const char *methodName, int returnIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) { 
            (*g_traceEntrypoints->m_traceExit)(className,methodName,returnIndex,type,len,value); 
    }
#else
    static inline void traceExit(const char *className, const char *methodName, int returnIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) {
        traceExitInternal(className,methodName,returnIndex,type,len,value);
    }
#endif
	static void traceExitInternal(const char *className, const char *methodName, int returnIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0);

	/**
	 * Traces something that has been caught
	 */
#ifdef AXISTRACE_LIBRARY
    static inline void traceCatch(const char *className, const char *methodName, int catchIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) { 
            (*g_traceEntrypoints->m_traceCatch)(className,methodName,catchIndex,type,len,value); 
    }
#else
    static inline void traceCatch(const char *className, const char *methodName, int catchIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) {
        traceCatchInternal(className,methodName,catchIndex,type,len,value);
    }
#endif
	static void traceCatchInternal(const char *className, const char *methodName, int catchIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0);
      /**
       * Closes the trace file
       */
      static void terminate();

      /**
       * Returns the trace entrypoints to pass to a dynamically loaded library.
       */
#ifdef AXISTRACE_LIBRARY
      static void getTraceEntrypoints(AxisTraceEntrypoints& entrypoints) {
         entrypoints = *g_traceEntrypoints;
      }
#else
      static void getTraceEntrypoints(AxisTraceEntrypoints& entrypoints) {
         entrypoints.m_traceLine = traceLineInternal;
         entrypoints.m_traceEntry = traceEntryInternal;
         entrypoints.m_traceExit = traceExitInternal;
         entrypoints.m_traceCatch = traceCatchInternal;
         entrypoints.m_traceOn = isTraceOn();
      }
#endif

#ifdef AXISTRACE_LIBRARY
      static void setTraceEntrypoints(AxisTraceEntrypoints& entrypoints) {
          g_traceEntrypoints = new AxisTraceEntrypoints;
          *g_traceEntrypoints = entrypoints;
      }
#endif

private:
	static bool m_bLoggingOn;
    static AxisFile *m_fileTrace;
	static std::stack<std::string> m_stack;

    static int logthis(const char* pcLog, int level, char* arg2, int arg3);
	static void addParameter(std::string& line, int type, unsigned len, void *value);
    static void traceHeader();
};

AXIS_CPP_NAMESPACE_END

#endif

