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

#include <axis/server/AxisTrace.h>
#include <time.h>
#include <stdio.h>
#include "AxisUtils.h"
#include <axis/server/GDefine.h>
#include <axis/server/AxisConfig.h>


extern AxisConfig* g_pConfig;


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
	char* sFileName = g_pConfig->getAxConfProperty(AXCONF_LOGPATH);
	if (!sFileName) return AXIS_FAIL;
#ifndef WIN32
    setFilePerm(sFileName);
#endif
    if(AXIS_FAIL == m_fileTrace.fileOpen(sFileName, "a"))
        return AXIS_FAIL;
	m_bLoggingOn = true;
	return AXIS_SUCCESS;
}

int AxisTrace::openFileByClient ()
{
    //char* sFileName = g_pConfig->getAxisClientLogPath ();
	char* sFileName = g_pConfig->getAxConfProperty(AXCONF_CLIENTLOGPATH);
	if (!sFileName) return AXIS_FAIL;
#ifndef WIN32
    setFilePerm(sFileName);
#endif
    if(AXIS_FAIL == m_fileTrace.fileOpen(sFileName, "a"))
        return AXIS_FAIL;
	m_bLoggingOn = true;
    return AXIS_SUCCESS;
}

int AxisTrace::setFilePerm(const char* sFileName)
{
    int length = strlen (sFileName) + 12;
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
    if (!m_bLoggingOn) return AXIS_FAIL;
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
    if (!m_bLoggingOn) return AXIS_FAIL;
    int iResult = logthis(sLog1, level, arg3, arg4);
    if(AXIS_SUCCESS == iResult)
    {
        /*fputs (sLog2, m_fileTrace);
        fputs ("\n", m_fileTrace);
        fputs ("-------------------------------------------------", m_fileTrace);
        fputs ("\n", m_fileTrace);

        fflush (m_fileTrace);*/
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
    if (!m_bLoggingOn) return AXIS_FAIL;
    char* convToInt = (char*) malloc(4 * sizeof(char));
    int iResult = logthis(sLog1, level, arg3, arg4);
    if(AXIS_SUCCESS == iResult)
    {
	sprintf(convToInt, "%d", nLog2);
        /*fputs (convToLong, m_fileTrace);
        fputs ("\n", m_fileTrace);
        fputs ("-------------------------------------------------", m_fileTrace);
        fputs ("\n", m_fileTrace);

        fflush (m_fileTrace);*/
        m_fileTrace.filePuts (convToInt);
        m_fileTrace.filePuts ("\n");
        m_fileTrace.filePuts ("-------------------------------------------------");
        m_fileTrace.filePuts ("\n");

        m_fileTrace.fileFlush ();

        return AXIS_SUCCESS;
    }
    free(convToInt);
    return AXIS_FAIL;
}

int AxisTrace::logaxis (const char* sLog1, const double dLog2, int level,
    char* arg3, int arg4)
{
    if (!m_bLoggingOn) return AXIS_FAIL;
    char* convToDouble = (char*) malloc(4 * sizeof(char));
    int iResult = logthis(sLog1, level, arg3, arg4);
    if(AXIS_SUCCESS == iResult)
    {
	sprintf(convToDouble, "%f", dLog2);
        /*fputs (convToDouble, m_fileTrace);
        fputs ("\n", m_fileTrace);
        fputs ("-------------------------------------------------", m_fileTrace);
        fputs ("\n", m_fileTrace);

        fflush (m_fileTrace);*/
        m_fileTrace.filePuts (convToDouble);
        m_fileTrace.filePuts ("\n");
        m_fileTrace.filePuts ("-------------------------------------------------");
        m_fileTrace.filePuts ("\n");

        m_fileTrace.fileFlush ();

        return AXIS_SUCCESS;
    }
    free(convToDouble);
    return AXIS_FAIL;
}

int AxisTrace::trace (const char *pchLog)
{
    printf ("DEBUG LINE :\n%s\n", pchLog);
    return AXIS_SUCCESS;
}

/*
int main(int argc, char* argv[])
{
  tracer.trace("test");
  return 0;
}
*/
