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
 

#ifndef __AXISLOG_H_OF_AXIS_INCLUDED_
#define __AXISLOG_H_OF_AXIS_INCLUDED_

#include "GDefine.h"
#include <list>
#include <string>
#include <stdio.h>

#define __AXISTRACE__
#if defined(__AXISTRACE__)  
  #define AXISTRACE1(X, Y) g_pAT->logaxis(X,Y,__FILE__,__LINE__);
  #define AXISTRACE2(X,Y, Z) g_pAT->logaxis(X,Y,Z,__FILE__,__LINE__);
  #define AXISTRACE3(X) g_pAT->trace(X);
  
#endif
#if !defined(__AXISTRACE__)
  #define AXISTRACE1(X,Y) "";
  #define AXISTRACE2(X,Y,Z) "";
  #define AXISTRACE3(X) "";
#endif


using namespace std;

/**
 *  @class AxisTrace
 *  @brief This is class is used to log messages when AXISTRACE is defined.

 *  writing to the log could be disabled by commenting the line #define __AXISTRACE__
 *  of Axisconfig.h.   
 *  @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
*/

class AxisTrace
{
public:
    AxisTrace();
	virtual ~AxisTrace();
    /**
	 * This is called in writing to the log file whose path is specified in $AXIS_HOME/axiscpp.conf file.
     * This method is used when the caller has only one string message as argument. User
     * can also specify the severity of the message by assigning level argument to one
     * of CRITICAL, WARN, INFO or TRIVIAL.
	 * @param sLog string message
     * @param level severity level
     * @param arg2 file name
     * @param arg3 line number
	 * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not (AXIS_FAIL).
	 */
    int logaxis(const char* sLog, int level, char* arg2, int arg3);
    /**
	 * This is called in writing to the log file whose path is specified in $AXIS_HOME/axiscpp.conf file.
     * This method is used when the caller has two string messages as arguments. One may be his own message.
     * The other may be to print a trace value. User can also specify the severity of the message by
     * assigning level argument to one of CRITICAL, WARN, INFO or TRIVIAL.
	 * @param sLog1 string message one
     * @param sLog2 string message two  
     * @param level severity level
     * @param arg3 file name
     * @param arg4 line number
	 * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not (AXIS_FAIL).
	 */
    int logaxis(const char* sLog1, const char* sLog2, int level, char* arg3, int arg4);
	/**
	 * Writes the given string to the standard console. This method is useful when using
     * the standalone server.
	 * @param pchLog The given string which will be printed to the standard console.
	 * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not (AXIS_FAIL).
	 */
	int trace(const char* pchLog);
    /**
	 * Log file is opened for logging server side log messages
     *
     * The file is created( if one is already not there) with the name and path specified in $AXIS_HOME/axiscpp.conf file when web server
     * loads.
	 *
	 * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not (AXIS_FAIL).
	 */
    int openFile();
    /**
	 * Log file is opened for logging client side log messages
     *
     * The file is created with the name ClientAxisLog if one is not already in the current path.
	 * 
	 * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not (AXIS_FAIL).
	 */
    int openFileByClient();
  
private:
    char strLine[4];
    char* strLevel;
    FILE* fileTrace;
    FILE* ConfFile;

};

//static AxisTrace tracer;

#endif
