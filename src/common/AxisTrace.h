/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

// Trace only gets traced if the runtime flag is on
  #define AXISTRACE1(X, L) AxisTrace::logaxis(X,NULL,"W",__FILE__,__LINE__);
  #define AXISTRACE2(X, Y, L) AxisTrace::logaxis(X,Y,"W",__FILE__,__LINE__);
  #define AXISTRACE3(X) AxisTrace::trace(X);

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
#define TRACETYPE_UNKNOWN		0
#define TRACETYPE_CHAR			1
#define TRACETYPE_USHORT		2
#define TRACETYPE_SHORT			3
#define TRACETYPE_UINT			4
#define TRACETYPE_INT			5
#define TRACETYPE_ULONG			6	
#define TRACETYPE_LONG			7
#define TRACETYPE_DOUBLE		9
#define TRACETYPE_FLOAT			10
#define TRACETYPE_BOOL			11
#define TRACETYPE_POINTER		12
#define TRACETYPE_DATA			13
#define TRACETYPE_STRING		14
#define TRACETYPE_STLSTRING		15
#define TRACETYPE_ANONYMOUS		16
#define TRACETYPE_EXCEPTION		17
#define TRACETYPE_AXISEXCEPTION	18

#define TRACE_ENTRY  ">"
#define TRACE_EXIT   "<"
#define TRACE_AUDIT  "A"
#define TRACE_DEBUG  "D"
#define TRACE_EVENT  "E"
#define TRACE_INFO   "I"
#define TRACE_SYSOUT "O"
#define TRACE_UNCOND "U"
#define TRACE_WARN   "W"
#define TRACE_EXCEPT "X"

/*
 * enum AxisTraceState gives the states that trace can be in. This is primarily
 * to support startup trace. So initially trace is uninitialised. Then at the 
 * first trace call isTraceOn decides whether startup trace should be on and
 * either initialises startup trace or switches trace off. Then when axiscpp.conf
 * is read in openFile() or openFileByClient() is called which switches trace off
 * or on depending on how ClientLogPath or LogPath is set. Either way startup 
 * trace is switched off when axiscpp.conf is read in. When trace is terminated,
 * trace is set to stopped.
 */
enum AxisTraceState
{
	STATE_UNINITIALISED=0,
	STATE_OFF,
	STATE_ON,
	STATE_STOPPED,
	STATE_STARTUP
};

class STORAGE_CLASS_INFO AxisTraceEntrypoints {
public:
    void (*m_traceLine)(const char *data);
    void (*m_traceEntry)(const char *className, const char *methodName, const void* that, int nParms, va_list vargs);
    void (*m_traceExit)(const char *className, const char *methodName, const void* that, int returnIndex,
		int type, unsigned len, void *value);
    void (*m_traceCatch)(const char *className, const char *methodName, const void* that, int catchIndex,
		int type, unsigned len, void *value);
    bool (*m_traceOn) ();
};

#ifdef AXISTRACE_LIBRARY
    extern AxisTraceEntrypoints *g_traceEntrypoints;
#elif !defined(AXIS_CLIENTC_LIB)
	extern AxisTraceEntrypoints g_traceEntrypoints;
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
     * $AXISCPP_DEPLOY/axiscpp.conf file.
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
    static int logaxis(const char* sLog1, const char* sLog2, 
		const char *type, const char* file, int line);

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
     * path specified in AXISCPP_DEPLOY/axiscpp.conf file when web server loads.
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
    static inline bool isTraceOn() { return (*g_traceEntrypoints->m_traceOn)(); }
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
    static void traceLineInternal(const char *type, const char *classname, 
								  const char *methodname, const void *that, 
								  const char *parms);
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
    static inline void traceExit(const char *className, const char *methodName, const void* that, int returnIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) { 
            (*g_traceEntrypoints->m_traceExit)(className,methodName,that,returnIndex,type,len,value); 
    }
#else
    static inline void traceExit(const char *className, const char *methodName, const void* that, int returnIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) {
        traceExitInternal(className,methodName,that,returnIndex,type,len,value);
    }
#endif
	static void traceExitInternal(const char *className, const char *methodName, const void* that, int returnIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0);

	/**
	 * Traces something that has been caught
	 */
#ifdef AXISTRACE_LIBRARY
    static inline void traceCatch(const char *className, const char *methodName, const void* that, int catchIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) { 
            (*g_traceEntrypoints->m_traceCatch)(className,methodName,that,catchIndex,type,len,value); 
    }
#else
    static inline void traceCatch(const char *className, const char *methodName, const void* that, int catchIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0) {
        traceCatchInternal(className,methodName,that,catchIndex,type,len,value);
    }
#endif
	static void traceCatchInternal(const char *className, const char *methodName, const void* that, int catchIndex,
		int type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0);
      /**
       * Closes the trace file
       */
      static void terminate();

      /**
       * Returns the trace entrypoints to pass to a dynamically loaded library.
       */
#ifdef AXISTRACE_LIBRARY
      static AxisTraceEntrypoints* getTraceEntrypoints() {
          return g_traceEntrypoints;
      }
#elif !defined(AXIS_CLIENTC_LIB)
      static AxisTraceEntrypoints* getTraceEntrypoints() {
         return &g_traceEntrypoints;
      }
#endif

#ifdef AXISTRACE_LIBRARY
      static void setTraceEntrypoints(AxisTraceEntrypoints* entrypoints) {
          g_traceEntrypoints = entrypoints;
      }
#endif

private:

	static enum AxisTraceState m_bLoggingOn;
    static AxisFile *m_fileTrace;

    static int logthis(const char* pcLog, int level, char* arg2, int arg3);
	static void addParameter(std::string& line, int type, unsigned len, void *value);
	static void addDataParameter(std::string& line, unsigned len, void *value);
    static void traceHeader(enum AxisTraceState newState);
    static void traceLine2(const char *data);
	static int initialise(const char *filename, enum AxisTraceState newState);
};

#ifdef ENABLE_AXISTRACE
#define TRACE_OBJECT_CREATE_FUNCT_ENTRY(funct, arr, bArr, size) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
	{ \
		void *traceArr = arr; \
		bool traceBArr = bArr; \
		int traceSize = size; \
		axiscpp::AxisTrace::traceEntry(NULL, "AXIS_OBJECT_CREATE_FUNCT", (void*)(funct), 3, \
			TRACETYPE_POINTER, 1, (void*)&traceArr, \
			TRACETYPE_BOOL, 0, (void*)&traceBArr, \
			TRACETYPE_INT, 0, (void*)&traceSize); \
	} \
}

#define TRACE_OBJECT_CREATE_FUNCT_EXIT(funct, arr) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
		axiscpp::AxisTrace::traceExit(NULL, "AXIS_OBJECT_CREATE_FUNCT", (void*)(funct), 1, \
			TRACETYPE_POINTER, 1, (void*)&(arr)); \
}

#define TRACE_OBJECT_SIZE_FUNCT_ENTRY(funct) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
	{ \
		axiscpp::AxisTrace::traceEntry(NULL, "AXIS_OBJECT_SIZE_FUNCT", (void*)(funct), 0); \
	} \
}

#define TRACE_OBJECT_SIZE_FUNCT_EXIT(funct, size) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
		axiscpp::AxisTrace::traceExit(NULL, "AXIS_OBJECT_SIZE_FUNCT", (void*)(funct), 1, \
			TRACETYPE_INT, 1, (void*)&(size)); \
}

#define TRACE_OBJECT_DELETE_FUNCT_ENTRY(funct, arr, bArr, size) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
	{ \
		void *traceArr = arr; \
		bool traceBArr = bArr; \
		int traceSize = size; \
		axiscpp::AxisTrace::traceEntry(NULL, "AXIS_OBJECT_DELETE_FUNCT", (void*)(funct), 3, \
			TRACETYPE_POINTER, 1, (void*)&traceArr, \
			TRACETYPE_BOOL, 0, (void*)&traceBArr, \
			TRACETYPE_INT, 0, (void*)&traceSize); \
	} \
}

#define TRACE_OBJECT_DELETE_FUNCT_EXIT(funct) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
		axiscpp::AxisTrace::traceExit(NULL, "AXIS_OBJECT_DELETE_FUNCT", (void*)(funct), 0); \
}

#define TRACE_DESERIALIZE_FUNCT_ENTRY(funct, item, that) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
	{ \
		void *traceItem = item; \
		void *traceThat = that; \
		axiscpp::AxisTrace::traceEntry(NULL, "AXIS_OBJECT_CREATE_FUNCT", (void*)(funct), 2, \
			TRACETYPE_POINTER, 1, (void*)&traceItem, \
			TRACETYPE_POINTER, 1, (void*)&traceThat); \
	} \
}

#define TRACE_DESERIALIZE_FUNCT_EXIT(funct, status) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
		axiscpp::AxisTrace::traceExit(NULL, "AXIS_DESERIALIZE_FUNCT", (void*)(funct), 1, \
			TRACETYPE_INT, 0, (void*)&(status)); \
}

#define TRACE_SERIALIZE_FUNCT_ENTRY(funct, item, that, bArr) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
	{ \
		void *traceItem = item; \
		void *traceThat = that; \
		bool traceBArr = bArr; \
		axiscpp::AxisTrace::traceEntry(NULL, "AXIS_SERIALIZE_FUNCT", (void*)(funct), 3, \
			TRACETYPE_POINTER, 1, (void*)&traceItem, \
			TRACETYPE_POINTER, 1, (void*)&traceThat, \
			TRACETYPE_BOOL, 0, (void*)&traceBArr); \
	} \
}

#define TRACE_SERIALIZE_FUNCT_EXIT(funct, status) \
{ \
	if (axiscpp::AxisTrace::isTraceOn()) \
		axiscpp::AxisTrace::traceExit(NULL, "AXIS_SERIALIZE_FUNCT", (void*)(funct), 1, \
			TRACETYPE_INT, 0, (void*)&(status)); \
}

#else
#define TRACE_OBJECT_CREATE_FUNCT_ENTRY(funct, arr, bArr, size)
#define TRACE_OBJECT_CREATE_FUNCT_EXIT(funct, arr)
#define TRACE_OBJECT_SIZE_FUNCT_ENTRY(funct)
#define TRACE_OBJECT_SIZE_FUNCT_EXIT(funct, size)
#define TRACE_OBJECT_DELETE_FUNCT_ENTRY(funct, arr, bArr, size)
#define TRACE_OBJECT_DELETE_FUNCT_EXIT(funct)
#define TRACE_DESERIALIZE_FUNCT_ENTRY(funct, item, that)
#define TRACE_DESERIALIZE_FUNCT_EXIT(funct, status)
#define TRACE_SERIALIZE_FUNCT_ENTRY(funct, item, that, bArr)
#define TRACE_SERIALIZE_FUNCT_EXIT(funct, status)
#endif

AXIS_CPP_NAMESPACE_END

#endif

