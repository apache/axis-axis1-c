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
#include <axis/GDefine.hpp>
#include "AxisConfig.h"
#include <string>
// cctype is needed to make isprint compile on linux
#include <cctype>

extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;
AXIS_CPP_NAMESPACE_START
using namespace std;

bool AxisTrace::m_bLoggingOn = false;
AxisFile *AxisTrace::m_fileTrace = NULL;
std::stack<std::string> AxisTrace::m_stack;

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

int AxisTrace::logaxis (const char* sLog1, const char* sLog2, int level,
    char* arg3, int arg4)
{
    if (!m_bLoggingOn) return AXIS_FAIL;

    time_t ltime;
    time (&ltime);
    string text = "Severity Level : ";
    switch (level)
    {
        case 1:
            text += "CRITICAL";
            break;
        case 2:
            text += "WARN";
            break;
        case 3:
            text += "INFO";
            break;
        default:
            text += "TRIVIAL";
            break;
    }

    traceLine(text.c_str());
    text = "time : ";
    text += ctime (&ltime);
    text += "file : ";
    text += arg3;
    traceLine(text.c_str());
    text = "line : ";
    char buff[32];
    sprintf (buff, "%d", arg4);
    text += buff;
    traceLine(text.c_str());
    text = sLog1;
    text += ":";
    if(0 != sLog2)
        text += sLog2;
    traceLine(text.c_str());
    traceLine("-------------------------------------------------");
    return AXIS_SUCCESS;
}

int AxisTrace::logaxis (const char* sLog, int level, char* arg2, int arg3)
{
    return logaxis(sLog,NULL,level,arg2,arg3);
}
/*
int AxisTrace::logaxis (const char* sLog1, const int nLog2, int level,
    char* arg3, int arg4)
{
    char convToInt[32];
    sprintf(convToInt, "%d", nLog2);
    return logaxis(sLog1,convToInt,level,arg3,arg4);
}

int AxisTrace::logaxis (const char* sLog1, const double dLog2, int level,
    char* arg3, int arg4)
{
    char convToDouble[32];
    sprintf(convToDouble, "%f", dLog2);
    return logaxis(sLog1,convToDouble,level,arg3,arg4);
}
*/
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
    traceLine("--------- Axis C++ trace ----------");
    string text = "Axis C++ libraries built on ";
    text += __DATE__;
    text += " at ";
    text += __TIME__;
    traceLine(text.c_str());

    time_t ltime;
    time (&ltime);
    text = "Trace produced on ";
    text += ctime (&ltime);
    traceLine(text.c_str());

    traceLine("Dumping environment variables...");
    char *envVars[]={"PATH","LIBPATH","LD_LIBRARY_PATH","AXISCPP_DEPLOY","PWD",
        "CLASSPATH","INCLUDE","LIB","NLSPATH","OS","COMPUTERNAME","USERNAME",
        "HOSTNAME","LANG","LOGIN","LOGNAME","MACHTYPE","OSTYPE","UID","USER"};
    for (unsigned i=0; i<sizeof(envVars)/4; i++) 
	{
        text = envVars[i];
        const char *value = getenv(envVars[i]);
        if (NULL==value)
		{
			text += " was not set";
		}
        else 
		{
            text += "=";
            text += value;
        }
        traceLine(text.c_str());
    }

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

void AxisTrace::traceLineInternal(const char *data) 
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
		for (unsigned is=0; is<m_stack.size(); is++) line += " ";
		line += "{ ";
		if (NULL!=className) {
			line += className;
			line += "::";
		}
		if (NULL!=methodName)
			line += methodName;
		if (NULL!=that) {
			line += "<";
			char prim[32];
			sprintf(prim,"%p",that);
			line += prim;
			line += ">";
		}
		line += "(";

		for (int i=0; i<nParms; i++) {
			int type = va_arg(args, int);
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

    string name;
    if (NULL!=className) {
        name = className;
	  name += "::";
	  name += methodName;
    } else name = methodName;
    m_stack.push(name);
}

void AxisTrace::traceExitInternal(const char *className, const char *methodName, int returnIndex,
						  int type, unsigned len, void *value)
{
    if (!isTraceOn()) return;

	try {
		// Careful here in case entries and exits don't match
		string name;
            if (NULL!=className) {
                name = className;
		    name += "::";
		    name += methodName;
            } else name = methodName;
		while (m_stack.size()>0 && name!=m_stack.top()) m_stack.pop();
		if (m_stack.size()>0) m_stack.pop();

		string line;
		for (unsigned is=0; is<m_stack.size(); is++) line += " ";
		line += "} ";
		if (NULL!=className) {
			line += className;
			line += "::";
		}
		if (NULL!=methodName) 
			line += methodName;
            if (0!=returnIndex) { // Zero means only one return
                  line += "@";
                  char prim[32];
                  sprintf(prim,"%d",returnIndex);
                  line += prim;
            }
		line += "(";
		if (TRACETYPE_UNKNOWN != type)
			addParameter(line,type,len,value);
		line += ")";
		traceLine(line.c_str());
    } catch (...) {
        traceLine("Unknown exception caught during trace exit");
    }
}

void AxisTrace::traceCatchInternal(const char *className, const char *methodName, int catchIndex,
						   int type, unsigned len, void *value)
{
    if (!isTraceOn()) return;

	try {
		// The method that caught the exception may not be top of the stack.
		string name = className;
		name += "::";
		name += methodName;
		while (m_stack.size()>0 && name!=m_stack.top()) m_stack.pop();

		string line;
		for (unsigned is=0; is<m_stack.size(); is++) line += " ";
		line += "! ";
		if (NULL!=className) {
			line += className;
			line += "::";
		}
		if (NULL!=methodName) 
			line += methodName;
		line += " caught ";
            if (0!=catchIndex) { // Zero means only one catch
                  line += "@";
                  char prim[32];
                  sprintf(prim,"%d",catchIndex);
                  line += prim;
                  line += " ";
            }
		if (TRACETYPE_UNKNOWN != type)
			addParameter(line,type,len,value);
            else line += "\"...\"";
		traceLine(line.c_str());
    } catch (...) {
        traceLine("Unknown exception caught during trace catch");
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
            if (NULL==pcValue) return;
		// no break!
	
	case TRACETYPE_DATA:	
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
			line += "\"";	
   		      line += ((string*)value)->c_str();
			line += "\"";	
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

/*
int main(int argc, char* argv[])
{
  tracer.trace("test");
  return 0;
}
*/

AXIS_CPP_NAMESPACE_END
