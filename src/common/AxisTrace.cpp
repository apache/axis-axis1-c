/* -*- C++ -*- */
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
 *
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include "AxisTrace.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include "AxisUtils.h"
#include <axis/server/GDefine.hpp>
#include "AxisConfig.h"
#include <string>


extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

AXIS_CPP_NAMESPACE_START

using namespace std;

AxisTrace::AxisTrace ()
{
	m_bLoggingOn = false;
}

AxisTrace::~AxisTrace ()
{
}

int AxisTrace::openFile ()
{
    //char* sFileName = g_pConfig->getAxisLogPath ();
    char* sFileName = g_pConfig->getAxisConfProperty(AXCONF_LOGPATH);
    if (!sFileName) return AXIS_FAIL;
/*#ifndef WIN32
    setFilePerm(sFileName);
#endif
*/
    if(AXIS_FAIL == m_fileTrace.fileOpen(sFileName, "a"))
        return AXIS_FAIL;
	m_bLoggingOn = true;
	return AXIS_SUCCESS;
}

int AxisTrace::openFileByClient ()
{
    //char* sFileName = g_pConfig->getAxisClientLogPath ();
    char* sFileName = g_pConfig->getAxisConfProperty(AXCONF_CLIENTLOGPATH);
    if (!sFileName) return AXIS_FAIL;
/*#ifndef WIN32
    setFilePerm(sFileName);
#endif
*/
    if(AXIS_FAIL == m_fileTrace.fileOpen(sFileName, "a"))
        return AXIS_FAIL;
	m_bLoggingOn = true;
    return AXIS_SUCCESS;
}

int AxisTrace::setFilePerm(const char* sFileName)
{
/*    int length = strlen (sFileName) + 12;
    char* setPerm = (char *) malloc (length);
    if (setPerm)
    {
        strcpy (setPerm, "chmod 766 ");
        strcat (setPerm, sFileName);
    }
    else
        return AXIS_FAIL;
                                                                                                                             
#ifdef __GNUC__
    system (setPerm);
#endif
    if (AXIS_SUCCESS != (m_fileTrace.fileOpen(sFileName, "a")))
        return AXIS_FAIL;
*/
    return AXIS_SUCCESS;
}

int AxisTrace::logthis (const char* sLog, int level, char* arg2, int arg3)
{
    if (!m_bLoggingOn) return AXIS_FAIL;

    time_t ltime;
    time (&ltime);

    //fputs ("Severity Level : ", m_fileTrace);
    m_fileTrace.filePuts("Severity Level : ");

    switch (level)
    {
        case 1:
            m_pcLevel = "CRITICAL";
            break;
        case 2:
            m_pcLevel = "WARN";
            break;
        case 3:
            m_pcLevel = "INFO";
            break;
        case 4:
            m_pcLevel = "TRIVIAL";
            break;
    }

    m_fileTrace.filePuts(m_pcLevel);
    /*fputs ("\n", m_fileTrace);

    fputs ("time : ", m_fileTrace);
    fputs (ctime (&ltime), m_fileTrace);
    fputs ("file : ", m_fileTrace);
    fputs (arg2, m_fileTrace);
    fputs ("\n", m_fileTrace);
    fputs ("line : ", m_fileTrace);
    sprintf (m_acLine, "%d", arg3);
    fputs (m_acLine, m_fileTrace);
    fputs ("\n", m_fileTrace);
    fputs (sLog, m_fileTrace);
    fputs (":", m_fileTrace);
*/



    m_fileTrace.filePuts ("\n");

    m_fileTrace.filePuts ("time : ");
    m_fileTrace.filePuts (ctime (&ltime));
    m_fileTrace.filePuts ("file : ");
    m_fileTrace.filePuts (arg2);
    m_fileTrace.filePuts ("\n");
    m_fileTrace.filePuts ("line : ");
    sprintf (m_acLine, "%d", arg3);
    m_fileTrace.filePuts (m_acLine);
    m_fileTrace.filePuts ("\n");
    m_fileTrace.filePuts (sLog);
    m_fileTrace.filePuts (":");

    return AXIS_SUCCESS;

}
int AxisTrace::logaxis (const char* sLog, int level, char* arg2, int arg3)
{
    int iResult = logthis(sLog, level, arg2, arg3);
   /* fputs ("\n", m_fileTrace);
    fputs ("-------------------------------------------------", m_fileTrace);
    fputs ("\n", m_fileTrace);

    fflush (m_fileTrace);*/
    if(AXIS_SUCCESS == iResult)
    {
        m_fileTrace.filePuts ("\n");
        m_fileTrace.filePuts ("-------------------------------------------------");
        m_fileTrace.filePuts ("\n");

        m_fileTrace.fileFlush ();
    }
    return AXIS_SUCCESS;
}

int AxisTrace::logaxis (const char* sLog1, const char* sLog2, int level,
    char* arg3, int arg4)
{
    int iResult = logthis(sLog1, level, arg3, arg4);
    if(AXIS_SUCCESS == iResult)
    {
        /*fputs (sLog2, m_fileTrace);
        fputs ("\n", m_fileTrace);
        fputs ("-------------------------------------------------", m_fileTrace);
        fputs ("\n", m_fileTrace);

        fflush (m_fileTrace);*/
        if(0 != sLog2)
            m_fileTrace.filePuts (sLog2);
        m_fileTrace.filePuts ("\n");
        m_fileTrace.filePuts ("-------------------------------------------------");
        m_fileTrace.filePuts ("\n");

        m_fileTrace.fileFlush ();

        return AXIS_SUCCESS;
    }
    return AXIS_FAIL;

}

int AxisTrace::logaxis (const char* sLog1, const int nLog2, int level,
    char* arg3, int arg4)
{
    int iResult = logthis(sLog1, level, arg3, arg4);
    char convToInt[5];
    if(AXIS_SUCCESS == iResult)
    {
        sprintf(convToInt, "%d", nLog2);
        m_fileTrace.filePuts (convToInt);
        m_fileTrace.filePuts ("\n");
        m_fileTrace.filePuts ("-------------------------------------------------");
        m_fileTrace.filePuts ("\n");
        m_fileTrace.fileFlush ();

        return AXIS_SUCCESS;
    }
    return AXIS_FAIL;
}

int AxisTrace::logaxis (const char* sLog1, const double dLog2, int level,
    char* arg3, int arg4)
{
    int iResult = logthis(sLog1, level, arg3, arg4);
    char convToDouble[5];
    if(AXIS_SUCCESS == iResult)
    {
        sprintf(convToDouble, "%f", dLog2);
        m_fileTrace.filePuts (convToDouble);
        m_fileTrace.filePuts ("\n");
        m_fileTrace.filePuts ("-------------------------------------------------");
        m_fileTrace.filePuts ("\n");
        m_fileTrace.fileFlush ();

        return AXIS_SUCCESS;
    }
    return AXIS_FAIL;
}

int AxisTrace::trace (const char *pchLog)
{
    printf ("DEBUG LINE :\n%s\n", pchLog);
    return AXIS_SUCCESS;
}

void AxisTrace::traceLine(const char *data) 
{
    if (!isTraceOn()) return;
    m_fileTrace.filePuts(data);
    m_fileTrace.filePuts("\n");
    return;
}

void AxisTrace::traceEntry(const char *className, const char *methodName, void *that, int nParms, ...)
{
    if (!isTraceOn()) return;

	try {
		string line;
		for (int is=0; is<m_stack.size(); is++) line += " ";
		line += "{ ";
		if (NULL!=className) {
			line += className;
			if (NULL!=that) {
				line += "(";
				char prim[32];
				sprintf(prim,"%p",that);
				line += prim;
				line += ")";
			}
			line += "::";
		}

		if (NULL!=methodName)
			line += methodName;
		line += "(";

		va_list args;
		va_start(args, nParms);
		for (int i=0; i<nParms; i++) {
			AxisTraceType type = va_arg(args, AxisTraceType);
			unsigned len = va_arg(args, unsigned);
			void *value = va_arg(args, void*);
			if (0!=i) line += ", ";
			addParameter(line,type,len,value);
		}

		line += ")";
		traceLine(line.c_str());
    } catch (...) {
        traceLine("Unknown exception caught during trace entry");
    }

	string name = className;
	name += "::";
	name += methodName;
	m_stack.push(name);
}

void AxisTrace::traceExit(const char *className, const char *methodName, 
						  AxisTraceType type, unsigned len, void *value)
{
    if (!isTraceOn()) return;

	try {
		// Careful here in case entries and exits don't match
		string name = className;
		name += "::";
		name += methodName;
		while (m_stack.size()>0 && name!=m_stack.top()) m_stack.pop();
		if (m_stack.size()>0) m_stack.pop();

		string line;
		for (int is=0; is<m_stack.size(); is++) line += " ";
		line += "} ";
		if (NULL!=className) {
			line += className;
			line += "::";
		}
		if (NULL!=methodName) 
			line += methodName;
		line += "(";
		if (TRACETYPE_UNKNOWN != type)
			addParameter(line,type,len,value);
		line += ")";
		traceLine(line.c_str());
    } catch (...) {
        traceLine("Unknown exception caught during trace exit");
    }
}

void AxisTrace::traceCatch(const char *className, const char *methodName, 
						   AxisTraceType type, unsigned len, void *value)
{
    if (!isTraceOn()) return;

	try {
		// The method that caught the exception may not be top of the stack.
		string name = className;
		name += "::";
		name += methodName;
		while (m_stack.size()>0 && name!=m_stack.top()) m_stack.pop();

		string line;
		for (int is=0; is<m_stack.size(); is++) line += " ";
		line += "!";
		if (NULL!=className) {
			line += className;
			line += "::";
		}
		if (NULL!=methodName) 
			line += methodName;
		line += " caught ";
		if (TRACETYPE_UNKNOWN != type)
			addParameter(line,type,len,value);
		traceLine(line.c_str());
    } catch (...) {
        traceLine("Unknown exception caught during trace catch");
    }
}

void AxisTrace::addParameter(string& line, AxisTraceType type, unsigned len, void *value)
{
	char prim[32]; // Plenty big enough to hold a primitive
      char *pcValue = (char*)value;
	switch (type) 
	{
	case TRACETYPE_CHAR:	sprintf(prim,"%c" ,*((char  *)value));	line += prim;	break;
	case TRACETYPE_USHORT:	sprintf(prim,"%hu",*((short *)value));	line += prim;	break;
	case TRACETYPE_SHORT:	sprintf(prim,"%hd",*((short *)value));	line += prim;	break;
	case TRACETYPE_UINT:	sprintf(prim,"%u" ,*((int   *)value));	line += prim;	break;
	case TRACETYPE_INT:	sprintf(prim,"%d" ,*((int   *)value));	line += prim;	break;
	case TRACETYPE_ULONG:	sprintf(prim,"%lu",*((long  *)value));	line += prim;	break;
	case TRACETYPE_LONG:	sprintf(prim,"%ld",*((long  *)value));	line += prim;	break;
	case TRACETYPE_UDOUBLE:	sprintf(prim,"%Lu",*((double*)value));	line += prim;	break;
	case TRACETYPE_DOUBLE:	sprintf(prim,"%Ld",*((double*)value));	line += prim;	break;
	case TRACETYPE_FLOAT:	sprintf(prim,"%f" ,*((float *)value));	line += prim;	break;

	case TRACETYPE_BOOL:
		line += *((bool*)value)?"true":"false";
		break;

	/*
	 * This code only prints out the first 32 bytes of storage pointed at by a 
	 * pointer. This is to prevent huge blocks of atorage repeatedly being output
	 * to the trace file. 32 bytes seems quite a low limit. Maybe this limit 
	 * could be increased in the future. Large blocks of storage could be output
	 * in a more human-friendly format.
	 */
	case TRACETYPE_POINTER:	
            pcValue = *((char**)pcValue);
		sprintf(prim,"%p ",pcValue);	
		line += prim;	
		// no break!
	
	case TRACETYPE_DATA:	
		try {
			line += "[";
			for (int i=0; i<len && i<32; i++) {
				int x = (int)(pcValue[i]);
				sprintf(prim,"%2.2X",x);
				line += prim;
			}
			line += "] <";
			for (int j=0; j<len && j<32; j++) {
				char c = pcValue[j];
				if (!isprint(c)) c='.';
				sprintf(prim,"%c",c);
				line += prim;
			}
			line += ">";
		} catch (...) {
			line += "<BADPOINTER>";
		}
		break;

	case TRACETYPE_STRING:	
		try {
                  pcValue = *((char**)pcValue);
			line += "\"";	
			line += pcValue;	
			line += "\"";	
		} catch (...) {
			line += "<BADPOINTER>";
		}
		break;

	default:
		sprintf(prim,"%d",type);
		line += "<UNKNOWNTYPE";				
		line += prim;
		line += ">";
		break;
	}
}

/*
int main(int argc, char* argv[])
{
  tracer.trace("test");
  return 0;
}
*/

AXIS_CPP_NAMESPACE_END
