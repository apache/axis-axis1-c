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
#include <stdlib.h>
#include "AxisUtils.h"
#include <axis/AxisException.hpp>
#include "AxisConfig.h"
#include <string>
// cctype is needed to make isprint compile on linux
#include <cctype>
#include <exception>
#include <ctime>
#include <cstring>

extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;
AXIS_CPP_NAMESPACE_START
using namespace std;

bool AxisTrace::m_bLoggingOn = false;
AxisFile *AxisTrace::m_fileTrace = NULL;

int AxisTrace::openFile ()
{
    m_fileTrace = new AxisFile();
    //char* sFileName = g_pConfig->getAxisLogPath ();
    char* sFileName = g_pConfig->getAxisConfProperty(AXCONF_LOGPATH);
    if (!sFileName) return AXIS_FAIL;
    if(AXIS_FAIL == m_fileTrace->fileOpen(sFileName, "a"))
        return AXIS_FAIL;
	m_bLoggingOn = true;
      traceHeader();
	return AXIS_SUCCESS;
}

int AxisTrace::openFileByClient ()
{
    m_fileTrace = new AxisFile();
    //char* sFileName = g_pConfig->getAxisClientLogPath ();
    char* sFileName = g_pConfig->getAxisConfProperty(AXCONF_CLIENTLOGPATH);
    if (!sFileName) return AXIS_FAIL;
    if(AXIS_FAIL == m_fileTrace->fileOpen(sFileName, "a"))
        return AXIS_FAIL;
	m_bLoggingOn = true;
    traceHeader();
    return AXIS_SUCCESS;
}

void AxisTrace::terminate() 
{ 
    m_bLoggingOn = false; 
    delete m_fileTrace; 
    m_fileTrace = NULL; 
}

bool AxisTrace::isTraceOn()
{ 
    return m_bLoggingOn; 
}

int AxisTrace::logaxis (const char* sLog1, const char* sLog2, const char *type,
    char* file, int line)
{
    if (!m_bLoggingOn) return AXIS_FAIL;

    string name = file;
	name += "@";
	name += line;

    string text = sLog1;
    text += ":";
    if(0 != sLog2)
        text += sLog2;

    traceLineInternal(type,name.c_str(),NULL,NULL,text.c_str());
    return AXIS_SUCCESS;
}

int AxisTrace::trace (const char *pchLog)
{
    if (pchLog != NULL) {
        traceLine(pchLog);
        printf ("DEBUG LINE :\n%s\n", pchLog);
    }
    return AXIS_SUCCESS;
}

void AxisTrace::traceHeader()
{
    traceLine2("************ Start Display Current Environment ************");
    string text = "Axis C++ libraries built on ";
    text += __DATE__;
    text += " at ";
    text += __TIME__;
    traceLine2(text.c_str());

    time_t ltime;
    time (&ltime);
    text = "Trace produced on ";
    text += ctime (&ltime);
    traceLine2(text.c_str());

    char *envVars[]={"PATH","LIBPATH","LD_LIBRARY_PATH","AXISCPP_DEPLOY","PWD",
        "CLASSPATH","INCLUDE","LIB","NLSPATH","OS","COMPUTERNAME","USERNAME",
        "HOSTNAME","LANG","LOGIN","LOGNAME","MACHTYPE","OSTYPE","UID","USER"};
    for (unsigned i=0; i<sizeof(envVars)/4; i++) 
	{
        text = envVars[i];
        const char *value = getenv(envVars[i]);
        if (NULL!=value)
		{
            text += "=";
            text += value;
	        traceLine2(text.c_str());
        }
    }
    traceLine2("************* End Display Current Environment *************");

	// Write out the config settings
	traceLine("-------------- Config File settings START ----------------");
	string confLine="";

    char *confProps[]={
		"AXCONF_WSDDFILEPATH",		//1
		"AXCONF_LOGPATH",			//2
		"AXCONF_CLIENTLOGPATH",		//3
		"AXCONF_CLIENTWSDDFILEPATH",	//4
		"AXCONF_AXISHOME",		//5
		"AXCONF_TRANSPORTHTTP",		//6
		"AXCONF_TRANSPORTSMTP",		//7
		"AXCONF_XMLPARSER",		//8
		"AXCONF_NODENAME",		//9
		"AXCONF_LISTENPORT",		//10
		"AXCONF_SSLCHANNEL_HTTP",	//11
		"AXCONF_CHANNEL_HTTP",		//12
		"AXCONF_SECUREINFO"};		//13 Please use this number in the #if below

// Check at build time whether the lists of properties are in sync
#if AXCONF_LAST > 13
#error "The list of configuration properties in AxisConfig.h and AxisTrace.cpp are different. Please keep them in sync."
#endif

    for (unsigned j=0; j<sizeof(confProps)/sizeof(char*); j++) 
	{
        confLine ="";
		confLine += confProps[j];
		confLine += " = ";

	    const char *value = g_pConfig->getAxisConfProperty((g_axconfig)j);
        if (NULL==value)
		{
			confLine += "NULL";
		}
        else 
		{
            confLine += value;
        }
        traceLine(confLine.c_str());
    }

	
	traceLine("-------------- Config File settings END OF ----------------");


}

void AxisTrace::traceLineInternal(const char *type, const char *classname, 
								  const char *methodname, const void *that, 
								  const char *parms) 
{
    time_t current = time(NULL);
	struct tm *tm = localtime(&current);

	// TODO: Milliseconds
	// Use %Y not %y because %y gives a compiler warning on Linux
	const int timelen=256;
	char strtime[timelen];
	memset(strtime,0,timelen);
	strftime(strtime,timelen,"[%d/%m/%Y %H:%M:%S:000 %Z]",tm);

	string text = strtime;
	text += " 1 ";  // TODO: this should be the thread id

	if (NULL==classname) text += "-";
	else text += classname;
	text += " ";
	text += type;
	if (NULL!=methodname) {
		text += " ";
		text += methodname;
	}
	text += " ";
	if (NULL != that) {
		char prim[32];
		sprintf(prim,"|%p|",that);
		text += prim;
		if (NULL!=parms) text += ",";
	}

	if (NULL != parms) {
		if (NULL==strchr(parms,'\n')) {
			text += parms;
			traceLine2(text.c_str());
		} else {
			// Multi-line output
			text += "------------>";
			traceLine2(text.c_str());
			const char *tok = strtok(const_cast<char*>(parms),"\n");
			while (NULL != tok) {
				traceLineInternal(tok);
				tok = strtok(NULL,"\n");
			}
		}
	} else {
		traceLine2(text.c_str());
	}
}

void AxisTrace::traceLineInternal(const char *data) 
{
	traceLineInternal(TRACE_INFO,NULL,NULL,NULL,data);
}

void AxisTrace::traceLine2(const char *data) 
{
    if (!isTraceOn()) return;
    m_fileTrace->filePuts(data);
    m_fileTrace->filePuts("\n");
    m_fileTrace->fileFlush();
    return;
}

void AxisTrace::traceEntryInternal(const char *className, const char *methodName, 
    const void *that, int nParms, va_list args)
{
    if (!isTraceOn()) return;

	try {
		string line;
		const char *parms = NULL;
		if (0<nParms) {
			for (int i=0; i<nParms; i++) {
				int type = va_arg(args, int);
				unsigned len = va_arg(args, unsigned);
				void *value = va_arg(args, void*);
				if (0!=i) line += ", ";
				addParameter(line,type,len,value);
			}
			parms = line.c_str();
		}

		traceLineInternal(TRACE_ENTRY,className,methodName,that,parms);
    } catch (...) {
        traceLineInternal(TRACE_EXCEPT,NULL,NULL,NULL,"Unknown exception caught during trace entry");
    }
}

void AxisTrace::traceExitInternal(const char *className, const char *methodName, int returnIndex,
						  int type, unsigned len, void *value)
{
    if (!isTraceOn()) return;

	try {
		string line;
		bool added = false;
        if (0!=returnIndex) { // Zero means only one return
               line = "@";
               char prim[32];
               sprintf(prim,"%d",returnIndex);
               line += prim;
			   added = true;
        }

		if (TRACETYPE_UNKNOWN != type) {
			if (added) line += " ";
			addParameter(line,type,len,value);
			added = true;
		}

		traceLineInternal(TRACE_EXIT,className,methodName,NULL,added?line.c_str():NULL);
    } catch (...) {
        traceLineInternal(TRACE_EXCEPT,NULL,NULL,NULL,"Unknown exception caught during trace exit");
    }
}

void AxisTrace::traceCatchInternal(const char *className, const char *methodName, int catchIndex,
						   int type, unsigned len, void *value)
{
    if (!isTraceOn()) return;

	try {
		string line;
        if (0!=catchIndex) { // Zero means only one catch
              line = "@";
              char prim[32];
              sprintf(prim,"%d",catchIndex);
              line += prim;
              line += " ";
        }

		line += "caught ";
		if (TRACETYPE_UNKNOWN != type)
			addParameter(line,type,len,value);
        else line += "\"...\"";
		traceLineInternal(TRACE_EXCEPT,className,methodName,NULL,line.c_str());
    } catch (...) {
        traceLineInternal(TRACE_EXCEPT,NULL,NULL,NULL,"Unknown exception caught during trace catch");
    }
}

void AxisTrace::addParameter(string& line, int type, unsigned len, void *value)
{
	char prim[32]; // Plenty big enough to hold a primitive
      char *pcValue = (char*)value;
	switch (type) 
	{
	case TRACETYPE_CHAR:	sprintf(prim,"%c" ,*((char  *)value));	line += prim;	break;
	case TRACETYPE_USHORT:	sprintf(prim,"%hu",*((short *)value));	line += prim;	break;
	case TRACETYPE_SHORT:	sprintf(prim,"%hd",*((short *)value));	line += prim;	break;
	case TRACETYPE_UINT:	sprintf(prim,"%u" ,*((int   *)value));	line += prim;	break;
	case TRACETYPE_INT:		sprintf(prim,"%d" ,*((int   *)value));	line += prim;	break;
	case TRACETYPE_ULONG:	sprintf(prim,"%lu",*((long  *)value));	line += prim;	break;
	case TRACETYPE_LONG:	sprintf(prim,"%ld",*((long  *)value));	line += prim;	break;
	case TRACETYPE_DOUBLE:	sprintf(prim,"%f" ,*((double*)value));	line += prim;	break;
	case TRACETYPE_FLOAT:	sprintf(prim,"%f" ,*((float *)value));	line += prim;	break;

	case TRACETYPE_BOOL:
		line += *((bool*)value)?"true":"false";
		break;

	case TRACETYPE_POINTER:	
            pcValue = *((char**)pcValue);
		sprintf(prim,"%p ",pcValue);	
		line += prim;	
            if (NULL!=pcValue) 
			addDataParameter(line,len,value);
		break;
	
	case TRACETYPE_DATA:	
		addDataParameter(line,len,value);
		break;

	case TRACETYPE_STRING:	
		try {
                  pcValue = *((char**)pcValue);
                  if (NULL==pcValue) line += "<null>";
                  else {
			    line += "\"";	
			    line += pcValue;	
			    line += "\"";
                  }	
		} catch (...) {
			line += "<BADPOINTER>";
		}
		break;

	case TRACETYPE_STLSTRING:
		try {
			string *str = static_cast<string*>(value);
			if (str) {
				line += "\"";	
   			      line += str->c_str();
				line += "\"";	
			} else line += "<BADPOINTER>";
		} catch (...) {
			line += "<BADPOINTER>";
		}
		break;

	case TRACETYPE_EXCEPTION:
		try {
			exception *ex = static_cast<exception*>(value);
	   	      const char *msg = ex->what();
			if (NULL==msg) msg = "\?\?\?\?";
			line += "exception(\"";
	   	      line += msg;
			line += "\")";	
		} catch (...) {
			line += "<BADPOINTER>";
		}
		break;

	case TRACETYPE_AXISEXCEPTION:
		try {
			AxisException *ex = static_cast<AxisException*>(value);
		      const int code = ex->getExceptionCode();
	   	      const char *msg = ex->what();
			if (NULL==msg) msg = "\?\?\?\?";
			line += "AxisException(";	
   		      line += code;
   		     	line += ", \"";
	   	      line += msg;
			line += "\")";	
		} catch (...) {
			line += "<BADPOINTER>";
		}
		break;

	case TRACETYPE_ANONYMOUS:
		line += "<ANONYMOUS>";				
		break;

	default:
		sprintf(prim,"%d",type);
		line += "<UNKNOWNTYPE";				
		line += prim;
		line += ">";
		break;
	}
}

/**
 * This code only prints out the first 32 bytes of storage pointed at by a 
 * pointer. This is to prevent huge blocks of atorage repeatedly being output
 * to the trace file. 32 bytes seems quite a low limit. Maybe this limit 
 * could be increased in the future. Large blocks of storage could be output
 * in a more human-friendly format.
 */
void AxisTrace::addDataParameter(string& line, unsigned len, void *value) {
	char prim[32]; // Plenty big enough to hold a primitive
      char *pcValue = (char*)value;
	try {
		line += "[";
		for (unsigned i=0; i<len && i<32; i++) {
			int x = (int)(pcValue[i]);
			sprintf(prim,"%2.2X",x);
			line += prim;
		}
		line += "] <";
		for (unsigned j=0; j<len && j<32; j++) {
			char c = pcValue[j];
			if (!isprint(c)) c='.';
			sprintf(prim,"%c",c);
			line += prim;
		}
		line += ">";
	} catch (...) {
		line += "<BADPOINTER>";
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
