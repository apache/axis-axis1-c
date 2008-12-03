/* -*- C++ -*- */
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
 *
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string>

// cctype is needed to make isprint compile on linux
#include <cctype>
#include <ctime>
#include <cstring>

#include "AxisTrace.h"

AXIS_CPP_NAMESPACE_START
using namespace std;

// Initialization of static trace variables.
bool AxisTrace::m_logFileIsSet             = false;

bool AxisTrace::m_stubLogLevelEnabled      = true;
bool AxisTrace::m_engineLogLevelEnabled    = true;
bool AxisTrace::m_parserLogLevelEnabled    = true;
bool AxisTrace::m_transportLogLevelEnabled = true;
bool AxisTrace::m_noEntryExit              = false;

bool AxisTrace::m_consoleMode = false;

string AxisTrace::m_logFilePath = "";

//******************************************************************************
//
// AxisTrace::startTrace() Implementation
//
//******************************************************************************
int AxisTrace::
startTrace(const char* logFilePath, 
           bool dumpEnvironment)
{
    // If startTrace() already invoked, just return.
    if (NULL == logFilePath || 0x00 == *logFilePath)
        return AXIS_FAIL;

    m_logFileIsSet = true;
    
    // Set log directory
    m_logFilePath = logFilePath;
    
    // We need to do open here in order to ensure file is created and tagged as ASCII. 
    // This is to cater to EBCDIC-based systems such as IBM i operating system.  Should really 
    // not matter for ASCII-based operating systems such as UNIX and windows.
    FILE *logFile = fopen(m_logFilePath.c_str(), TRACE_FILE_MODE1);
    if (logFile != NULL)
        fclose(logFile);

    // Now dump out environment information
    if (dumpEnvironment)
    {
        string text = "************ Start Display Current Environment ************\n";
        text += "Axis C++ libraries built on ";
        text += __DATE__;
        text += " at ";
        text += __TIME__;
        text += "\n";
        writeTrace(text);
    
        char *envVars[]={"AXISCPP_DEPLOY", "PATH","LIBPATH","LD_LIBRARY_PATH","SHLIB_PATH", 
            "PWD","CLASSPATH","INCLUDE","LIB","NLSPATH","OS",
            "COMPUTERNAME","USERNAME","HOSTNAME","LANG","LOGIN","LOGNAME",
            "MACHTYPE","OSTYPE","UID","USER"};
        for (unsigned i=0; i<(sizeof(envVars)/sizeof(char*)); i++) 
        {
            text = envVars[i];
            const char *value = getenv(envVars[i]);
            if (NULL!=value)
            {
                text += "=";
                text += value;
                text += "\n";
                writeTrace(text);
            }
        }
        writeTrace("************* End Display Current Environment *************\n");   
    }
    
    return AXIS_SUCCESS;
}

//******************************************************************************
//
// AxisTrace::stopTrace() Implementation
//
//******************************************************************************
void AxisTrace::
stopTrace()
{
    m_logFilePath  = "";
    m_logFileIsSet = false;
}

//******************************************************************************
//
// AxisTrace::setLogFilter() Implementation
//
//******************************************************************************
void AxisTrace::
setLogFilter(const char *filters)
{
    resetLogFilter();
    
    if (filters == NULL || *filters == 0x00)
        return;
    
    string filters_s = filters;
    
    if (filters_s.find(TRACE_FILTER_NOENTRYEXIT) != string::npos)
        m_noEntryExit      = true;
    
    if (filters_s.find(TRACE_FILTER_STUB) == string::npos)
        m_stubLogLevelEnabled      = false;
    
    if (filters_s.find(TRACE_FILTER_ENGINE) == string::npos)
        m_engineLogLevelEnabled    = false;
    
    if (filters_s.find(TRACE_FILTER_PARSER) == string::npos)
        m_parserLogLevelEnabled    = false;
    
    if (filters_s.find(TRACE_FILTER_TRANSPORT) == string::npos)
        m_transportLogLevelEnabled = false;
}

//******************************************************************************
//
// AxisTrace::getLogFilters() Implementation
//
//******************************************************************************
string AxisTrace::
getLogFilter()
{
    string filters   = "";
    string delimiter = ";";
    
    if (m_noEntryExit)
        filters += TRACE_FILTER_NOENTRYEXIT + delimiter;
    
    if (m_stubLogLevelEnabled)
        filters += TRACE_FILTER_STUB + delimiter;
    
    if (m_engineLogLevelEnabled)
        filters += TRACE_FILTER_ENGINE + delimiter;
    
    if (m_parserLogLevelEnabled)
        filters += TRACE_FILTER_PARSER + delimiter;
    
    if (m_transportLogLevelEnabled)
        filters += TRACE_FILTER_TRANSPORT + delimiter;
    
    return filters;
}

//******************************************************************************
//
// AxisTrace::resetLogFilters() Implementation
//
//******************************************************************************
void AxisTrace::
resetLogFilter()
{
    m_stubLogLevelEnabled      = true;
    m_engineLogLevelEnabled    = true;
    m_parserLogLevelEnabled    = true;
    m_transportLogLevelEnabled = true;
    m_noEntryExit              = false;
}

//******************************************************************************
//
// AxisTrace::enableConsoleMode() Implementation
//
//******************************************************************************
void AxisTrace::
enableConsoleMode()
{
    m_consoleMode = true;
}

//******************************************************************************
//
// AxisTrace::disableConsoleMode() Implementation
//
//******************************************************************************
void AxisTrace::
disableConsoleMode()
{
    m_consoleMode = false;
}

//******************************************************************************
//
// AxisTrace::writeEntry() Implementation
//
//******************************************************************************
void AxisTrace::
writeEntry   (const char* component, 
              const char* functionName, 
              const char * fmt, 
              ...)
{
    // If logging is not enabled, just return
    if (!isLoggingEnabled())
        return;
    
    // Filter out entry/exit? If so, simply return.
    if (m_noEntryExit)
        return;
    
    // Construct final formatter
    char myfmt[1024];
    if (NULL == fmt)
        fmt = "";
    sprintf(myfmt, "%s %s %s(): %s\n", component, TRACE_TYPE_ENTRY, functionName, fmt);
    
    va_list vargs;
    va_start(vargs,fmt);
    writeTrace(myfmt, vargs);        
    va_end(vargs);
}

//******************************************************************************
//
// AxisTrace::writeExit() Implementation
//
//******************************************************************************
void AxisTrace::
writeExit   (const char* component,
             const char* functionName, 
             const char * fmt, 
             ...)
{
    // If logging is not enabled, just return
    if (!isLoggingEnabled())
        return;
    
    // Filter out entry/exit? If so, simply return.
    if (m_noEntryExit)
        return;
    
    // Construct final formatter
    char myfmt[1024];
    if (NULL == fmt)
        fmt = "";
    sprintf(myfmt, "%s %s %s(): %s\n", component, TRACE_TYPE_EXIT, functionName, fmt);
    
    va_list vargs;
    va_start(vargs,fmt);
    writeTrace(myfmt, vargs);        
    va_end(vargs);
}

//******************************************************************************
//
// AxisTrace::writeTrace() Implementation
//
//******************************************************************************
void AxisTrace::
writeTrace  (const char* component,
             const char* type,
             const char* functionName, 
             const char * fmt, 
             ...)
{
    // If logging is not enabled, just return
    if (!isLoggingEnabled())
        return;
    
    // Construct final formatter
    char myfmt[1024];
    if (NULL == fmt)
        fmt = "";
    sprintf(myfmt, "%s %s %s(): %s\n", component, type, functionName, fmt);
    
    va_list vargs;
    va_start(vargs,fmt);
    writeTrace(myfmt, vargs);        
    va_end(vargs);
}

//******************************************************************************
//
// AxisTrace::writeTrace() Implementation
//
//******************************************************************************
void AxisTrace::
writeTrace   (const char* component,
              const char* type,
              const char* functionName, 
              int lineNumber, 
              const char* fileName, 
              const char * fmt, 
              ...)
{
    // If logging is not enabled, just return
    if (!isLoggingEnabled())
        return;
    
    // Construct final formatter
    char myfmt[1024];
    if (NULL == fmt)
        fmt = "";
    sprintf(myfmt, "%s %s %s(): Line=%d: File=%s:\n%s\n", component, type, functionName, lineNumber, fileName, fmt);
    
    va_list vargs;
    va_start(vargs,fmt);
    writeTrace(myfmt, vargs);        
    va_end(vargs);
}

//******************************************************************************
//
// AxisTrace::writeTrace() Implementation
//
//******************************************************************************
void AxisTrace::
writeTrace(const char* component, 
           const char* type, 
           const char* functionName,
           bool hexFormat, 
           int dataLen, 
           const char *data)
{
    // If logging is not enabled, just return
    if (!isLoggingEnabled())
        return;
    
    int len = 0;
    
    if (NULL == data || dataLen==0)
        return;
    
    // Construct final formatter - the confuscated nature of the code is due to 
    // the support of EBCDIC based systems.
    char myfmt[1024];
    sprintf(myfmt, "%s %s %s(): \n", component, type, functionName);
    string prefix;
    generatePrefix(prefix, myfmt);
    PLATFORM_STRTOASC(prefix.c_str());
    
    if (!m_logFilePath.empty())
    {
        FILE *logFile = fopen(m_logFilePath.c_str(), TRACE_FILE_MODE1);
        if (logFile != NULL)
        {
            fprintf(logFile, "%s%*s%s", prefix.c_str(), dataLen, data, "\x0a");
            fflush(logFile);
            fclose(logFile);
        }
    }
    
    if (m_consoleMode)
    {
        fprintf(stdout, myfmt, dataLen, data);
        fflush(stdout);
    }
}

//******************************************************************************
//
// AxisTrace::writeTrace() Implementation
//
//******************************************************************************
void AxisTrace::
writeTrace(const char* data, int dataLen, bool hexFormat)
{
    // If logging is not enabled, just return
    if (!isLoggingEnabled())
        return;
    
    int len = 0;
    
    if (NULL == data || dataLen==0)
        return;
    
    if (!m_logFilePath.empty())
    {
        FILE *logFile = fopen(m_logFilePath.c_str(), TRACE_FILE_MODE2);
        if (logFile != NULL)
        {
            len = fwrite(data, 1, dataLen, logFile);
            fflush(logFile);
            fclose(logFile);
        }
    }
    
    if (m_consoleMode)
    {
        len = fwrite(data, 1, dataLen, stdout);
        fflush(stdout);
    }
}

//******************************************************************************
//
// AxisTrace::writeTrace() Implementation
//
//******************************************************************************
void AxisTrace::
writeTrace(string& s)
{
    // If logging is not enabled, just return
    if (!isLoggingEnabled())
        return;
    
    writeTrace(s.c_str(), s.length());
}

//******************************************************************************
//
// AxisTrace::writeTrace() Implementation
//
//******************************************************************************
void AxisTrace::
writeTrace(const char* fmt,
           va_list vargs)
{
    int len = 0;
    string prefix;
    generatePrefix(prefix, fmt);
    
    // Dump the data 
    
    if (!m_logFilePath.empty())
    {
        FILE *logFile = fopen(m_logFilePath.c_str(), TRACE_FILE_MODE2);
        if (logFile != NULL)
        {
            len = vfprintf(logFile, prefix.c_str(), vargs);
            fflush(logFile);
            fclose(logFile);
        }
    }
    
    if (m_consoleMode)
    {
        len = vfprintf(stdout, prefix.c_str(), vargs);
        fflush(stdout);
    }
}

//******************************************************************************
//
// AxisTrace::generatePrefix() Implementation
//
//******************************************************************************
void AxisTrace::
generatePrefix(string &prefix, const char *fmt)
{
    if (NULL == fmt)
        fmt = "";
        
    const int workBufLen=1024;
    char workBuf[workBufLen];
    memset(workBuf,0,workBufLen);
    
    // Generate trace timestamp.
    PLATFORM_TIMEB timeBuffer;
    PLATFORM_GET_TIME_IN_MILLIS( &timeBuffer );
    struct tm *tm = localtime(&timeBuffer.time);
    strftime(workBuf,workBufLen,"[%d/%m/%Y %H:%M:%S:", tm);
    prefix = workBuf;
    sprintf(workBuf, "%03u] ", timeBuffer.millitm);
    prefix += workBuf;
    
    // Generate trace thread ID - on some system thread ID is long long (64 bits)!
    LONGLONG tid = (LONGLONG)PLATFORM_GET_THREAD_ID;
    sprintf(workBuf, PRINTF_LONGLONG_LOG_FORMAT_SPECIFIER, tid);
    prefix += workBuf;
    prefix += "  ";
    
    // Add the format passed-in.
    prefix += fmt;
}

AXIS_CPP_NAMESPACE_END
