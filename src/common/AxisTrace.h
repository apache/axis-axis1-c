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

#if defined(ENABLE_AXISTRACE)  
  #define AXISTRACE1(X, Y) g_pAT->logaxis(X,Y,__FILE__,__LINE__);
  #define AXISTRACE2(X, Y, Z) g_pAT->logaxis(X,Y,Z,__FILE__,__LINE__);
  #define AXISTRACE3(X) g_pAT->trace(X);
  
#endif
#if !defined(ENABLE_AXISTRACE)
  #define AXISTRACE1(X,Y) "";
  #define AXISTRACE2(X,Y,Z) "";
  #define AXISTRACE3(X) "";
#endif

typedef enum 
{ 
    CRITICAL=1, WARN, INFO, TRIVIAL
} AXIS_SEVERITY_LEVEL;

//using namespace std;

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

typedef enum {
	TRACETYPE_UNKNOWN=0,
	TRACETYPE_CHAR,
	TRACETYPE_USHORT,
	TRACETYPE_SHORT,
	TRACETYPE_UINT,
	TRACETYPE_INT,
	TRACETYPE_ULONG,
	TRACETYPE_LONG,
	TRACETYPE_UDOUBLE,
	TRACETYPE_DOUBLE,
	TRACETYPE_FLOAT,
	TRACETYPE_BOOL,
	TRACETYPE_POINTER,
	TRACETYPE_DATA,
	TRACETYPE_STRING
} AxisTraceType;

class AxisTrace
{
public:
    AxisTrace();
    virtual ~AxisTrace();

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
    int logaxis(const char* sLog, int level, char* arg2, int arg3);

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
    int logaxis(const char* sLog1, const char* sLog2, int level, char* arg3, 
        int arg4);

    /**
     * This is called in writing to the log file whose path is specified in 
     * $AXIS_HOME/axiscpp.c     * onf file.
     * This method is used when the caller pass first argument as string and 
     * the second argument     * as long. First is his own message.
     * The other may be to print a trace value. User can also specify the 
     * severity of the messag     * e by
     * assigning level argument to one of CRITICAL, WARN, INFO or TRIVIAL.
     * @param sLog1 string message one
     * @param sLog2 string message two  
     * @param level severity level
     * @param arg3 file name
     * @param arg4 line number
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not  (AXIS_FAIL).
    */
    int logaxis(const char* sLog1, const int nLog2, int level, char* arg3, 
        int arg4);

    /**
     * This is called in writing to the log file whose path is specified in 
     * $AXIS_HOME/axiscpp.c     * onf file.
     * This method is used when the caller pass first argument as string 
     * and the second argument     * as double. First is his own message.
     * The other may be to print a trace value. User can also specify the 
     * severity of the messag     * e by
     * assigning level argument to one of CRITICAL, WARN, INFO or TRIVIAL.
     * @param sLog1 string message one
     * @param sLog2 string message two  
     * @param level severity level
     * @param arg3 file name
     * @param arg4 line number
     * @return The status which indicates whether the operation is success
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    int logaxis(const char* sLog1, const double dLog2, int level, 
        char* arg3, int arg4);

    /**
     * Writes the given string to the standard console. 
     * This method is useful when using the standalone server.
     * @param pchLog The given string which will be printed to the 
     * standard console.
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    int trace(const char* pchLog);

    /**
     * Log file is opened for logging server side log messages
     *
     * The file is created( if one is already not there) with the name and 
     * path specified in $AXIS_HOME/axiscpp.conf file when web server loads.
     *
     * @return The status which indicates whether the operation is successful
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    int openFile();

    /**
     * Log file is opened for logging client side log messages
     *
     * The file is created with the name ClientAxisLog if one is not 
     * already in the current path.
     * 
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    int openFileByClient();

    /**
     * Finds out whether trace is on.
     */
    inline bool isTraceOn() { return m_bLoggingOn; }

    /**
     * Traces a single line.
     */  
    void traceLine(const char *data);

	/**
	 * Traces the entry to a method.
	 */
	void traceEntry(const char *className, const char *methodName, void* that, int nParms, ...);

	/**
	 * Traces the exit to a method.
	 */
	void traceExit(const char *className, const char *methodName, 
		AxisTraceType type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0);

	/**
	 * Traces something that has been caught
	 */
	void traceCatch(const char *className, const char *methodName, 
		AxisTraceType type=TRACETYPE_UNKNOWN, unsigned len=0, void *value=0);

private:
	bool m_bLoggingOn;
    char m_acLine[4];
    char* m_pcLevel;
    AxisFile m_fileTrace;
	std::stack<std::string> m_stack;

    int setFilePerm(const char* pcFileName);
    int logthis(const char* pcLog, int level, char* arg2, int arg3);
	void addParameter(std::string& line, AxisTraceType type, unsigned len, void *value);
};

AXIS_CPP_NAMESPACE_END

#endif

