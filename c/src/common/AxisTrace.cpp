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
}

AxisTrace::~AxisTrace ()
{
    fclose (fileTrace);
}

int AxisTrace::openFile ()
{
    char* sFileName = g_pConfig->getAxisLogPath ();
    if ((fileTrace = fopen (sFileName, "a")) == NULL)
        return AXIS_FAIL;
    fclose (fileTrace);
    int length = strlen (sFileName) + 12;
    char* setPerm = (char *) malloc (length);
    if (setPerm)
    {
        strcpy (setPerm, "chmod 766 ");
        strcat (setPerm, sFileName);
    }

#ifdef __GNUC__
    system (setPerm);
#endif
    if ((fileTrace = fopen (sFileName, "a")) == NULL)
        return AXIS_FAIL;

    free(setPerm);
    return AXIS_SUCCESS;
}

int AxisTrace::openFileByClient ()
{
    char* sFileName = "./ClientAxisLog";

    if ((fileTrace = fopen (sFileName, "a")) == NULL)
        return AXIS_FAIL;

    return AXIS_SUCCESS;
}


int AxisTrace::logthis (const char* sLog, int level, char* arg2, int arg3)
{
    time_t ltime;
    time (&ltime);

    fputs ("Severity Level : ", fileTrace);

    switch (level)
    {
        case 1:
            strLevel = "CRITICAL";
            break;
        case 2:
            strLevel = "WARN";
            break;
        case 3:
            strLevel = "INFO";
            break;
        case 4:
            strLevel = "TRIVIAL";
            break;
    }

    fputs (strLevel, fileTrace);
    fputs ("\n", fileTrace);

    fputs ("time : ", fileTrace);
    fputs (ctime (&ltime), fileTrace);
    fputs ("file : ", fileTrace);
    fputs (arg2, fileTrace);
    fputs ("\n", fileTrace);
    fputs ("line : ", fileTrace);
    sprintf (strLine, "%d", arg3);
    fputs (strLine, fileTrace);
    fputs ("\n", fileTrace);
    fputs (sLog, fileTrace);
    fputs (":", fileTrace);

    return AXIS_SUCCESS;

}
int AxisTrace::logaxis (const char* sLog, int level, char* arg2, int arg3)
{
    
    int intResult = logthis(sLog, level, arg2, arg3);
    fputs ("\n", fileTrace);
    fputs ("-------------------------------------------------", fileTrace);
    fputs ("\n", fileTrace);

    fflush (fileTrace);

    return AXIS_SUCCESS;
}

int AxisTrace::logaxis (const char* sLog1, const char* sLog2, int level,
    char* arg3, int arg4)
{
    int intResult = logthis(sLog1, level, arg3, arg4);
    if(AXIS_SUCCESS == intResult)
    {
        fputs (sLog2, fileTrace);
        fputs ("\n", fileTrace);
        fputs ("-------------------------------------------------", fileTrace);
        fputs ("\n", fileTrace);

        fflush (fileTrace);

        return AXIS_SUCCESS;
    }
    return AXIS_FAIL;

}

int AxisTrace::logaxis (const char* sLog1, const long nLog2, int level,
    char* arg3, int arg4)
{
    char* convToLong = (char*) malloc(4 * sizeof(char));
    int intResult = logthis(sLog1, level, arg3, arg4);
    if(AXIS_SUCCESS == intResult)
    {
	sprintf(convToLong, "%d", nLog2);
        fputs (convToLong, fileTrace);
        fputs ("\n", fileTrace);
        fputs ("-------------------------------------------------", fileTrace);
        fputs ("\n", fileTrace);

        fflush (fileTrace);

        return AXIS_SUCCESS;
    }
    free(convToLong);
    return AXIS_FAIL;
}

int AxisTrace::logaxis (const char* sLog1, const double dLog2, int level,
    char* arg3, int arg4)
{
    char* convToDouble = (char*) malloc(4 * sizeof(char));
    int intResult = logthis(sLog1, level, arg3, arg4);
    if(AXIS_SUCCESS == intResult)
    {
	sprintf(convToDouble, "%f", dLog2);
        fputs (convToDouble, fileTrace);
        fputs ("\n", fileTrace);
        fputs ("-------------------------------------------------", fileTrace);
        fputs ("\n", fileTrace);

        fflush (fileTrace);

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
