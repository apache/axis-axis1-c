/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 */
 

#ifndef __AXISLOG_H_INCLUDED_
#define __AXISLOG_H_INCLUDED_

#include "GDefine.h"
#include <list>
#include <string>
#include <stdio.h>

#define __AXISTRACE__
#if defined(__AXISTRACE__)  
  #define AXISTRACE1(X, Y) g_pAT->logaxis(X,Y,__FILE__,__LINE__);
  #define AXISTRACE2(X, Y, Z) g_pAT->logaxis(X,Y,Z,__FILE__,__LINE__);
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
    int logthis(const char* sLog, int level, char* arg2, int arg3);
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
     * This is called in writing to the log file whose path is specified in $AXIS_HOME/axiscpp.c     * onf file.
     * This method is used when the caller has two string messages as arguments. One may be his      *own message.
     * The other may be to print a trace value. User can also specify the severity of the messag     *e by
     * assigning level argument to one of CRITICAL, WARN, INFO or TRIVIAL.
     * @param sLog1 string message one
     * @param sLog2 string message two  
     * @param level severity level
     * @param arg3 file name
     * @param arg4 line number
     * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not     * (AXIS_FAIL).
    */
    int logaxis(const char* sLog1, const char* sLog2, int level, char* arg3, int arg4);
    /**
     * This is called in writing to the log file whose path is specified in $AXIS_HOME/axiscpp.c     * onf file.
     * This method is used when the caller pass first argument as string and the second argument     * as long. First is his own message.
     * The other may be to print a trace value. User can also specify the severity of the messag     * e by
     * assigning level argument to one of CRITICAL, WARN, INFO or TRIVIAL.
     * @param sLog1 string message one
     * @param sLog2 string message two  
     * @param level severity level
     * @param arg3 file name
     * @param arg4 line number
     * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not     * (AXIS_FAIL).
    */
    int logaxis(const char* sLog1, const long nLog2, int level, char* arg3, int arg4);
    /**
     * This is called in writing to the log file whose path is specified in $AXIS_HOME/axiscpp.c     * onf file.
     * This method is used when the caller pass first argument as string and the second argument     * as double. First is his own message.
     * The other may be to print a trace value. User can also specify the severity of the messag     * e by
     * assigning level argument to one of CRITICAL, WARN, INFO or TRIVIAL.
     * @param sLog1 string message one
     * @param sLog2 string message two  
     * @param level severity level
     * @param arg3 file name
     * @param arg4 line number
     * @return The status which indicates whether the operation is success (AXIS_SUCCESS) or not     * (AXIS_FAIL).
    */
    int logaxis(const char* sLog1, const double dLog2, int level, char* arg3, int arg4);
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
