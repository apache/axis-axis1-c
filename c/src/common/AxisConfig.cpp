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

#include <axis/server/AxisConfig.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisFile.h>
#include "AxisUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

AxisConfig::AxisConfig ()
{
    m_pcWsddFilePath = 0;
    m_pcAxisLogPath = 0;
    m_pcAxisClientLogPath = 0;
    m_pcClientWsddFilePath = 0;
    m_pcAxisHome = 0;
}

AxisConfig::~AxisConfig ()
{
    if (m_pcWsddFilePath)
        free(m_pcWsddFilePath);
    if (m_pcAxisLogPath)
        free(m_pcAxisLogPath);
    if (m_pcAxisClientLogPath)
        free(m_pcAxisClientLogPath);
    if (m_pcClientWsddFilePath)
        free(m_pcClientWsddFilePath);
    if (m_pcAxisHome)
        free(m_pcAxisHome);
}

int AxisConfig::readConfFile ()
{
    char carrLine[CONFBUFFSIZE];
    char* pcValue;
    AxisFile fileConfig; /*AxisFile is AxisC++ resource for file manipulation */
    char* sConfPath = NULL;
    char* sNewConfPath = (char*) malloc(CONFBUFFSIZE);
    char* key;


    sConfPath = getenv ("AXIS_HOME");
    if (!sConfPath)
        return AXIS_FAIL;
    m_pcAxisHome = (char*) malloc (CONFBUFFSIZE);
    strcpy (m_pcAxisHome, sConfPath);

    strcpy (sNewConfPath, sConfPath);
    strcat (sNewConfPath, "/axiscpp.conf");
    if (AXIS_SUCCESS != fileConfig.fileOpen(sNewConfPath, "r"))
        return AXIS_FAIL;

    while (AXIS_SUCCESS == fileConfig.fileGet(carrLine, CONFBUFFSIZE)) 
    {
        int linesize = strlen (carrLine);
        pcValue = strpbrk (carrLine, ":");
        if (!pcValue)
            break;
        key = (char*) malloc (strlen (pcValue));
        pcValue[0] = '\0';
        sscanf (carrLine, "%s", key);

        if (strcmp (key, "WSDDFILEPATH") == 0)
        {
            m_pcWsddFilePath = (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcWsddFilePath, pcValue + 1, linesize - strlen (key) - 2);
            m_pcWsddFilePath[linesize - strlen (key) - 2] = '\0';
        }
        if (strcmp (key, "AXISLOGPATH") == 0)
        {
            m_pcAxisLogPath = (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcAxisLogPath, pcValue + 1, linesize - strlen (key) - 2);
            m_pcAxisLogPath[linesize - strlen (key) - 2] = '\0';
        }
        if (strcmp (key, "AXISCLIENTLOGPATH") == 0)
        {
            m_pcAxisClientLogPath = (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcAxisClientLogPath, pcValue + 1, linesize - strlen (key) - 2);
            m_pcAxisClientLogPath[linesize - strlen (key) - 2] = '\0';
        }
        if (strcmp (key, "CLIENTWSDDFILEPATH") == 0)
        {
            m_pcClientWsddFilePath = (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcClientWsddFilePath, pcValue + 1,
                linesize - strlen (key) - 2);
            m_pcClientWsddFilePath[linesize - strlen (key) - 2] = '\0';
        }
    }


    return AXIS_SUCCESS;
}

char* AxisConfig::getWsddFilePath ()
{
    return m_pcWsddFilePath;
}

char* AxisConfig::getAxisLogPath ()
{
    return m_pcAxisLogPath;
}

char* AxisConfig::getAxisClientLogPath ()
{
    return m_pcAxisClientLogPath;
}

char* AxisConfig::getClientWsddFilePath ()
{
    return m_pcClientWsddFilePath;
}

char* AxisConfig::getAxisHomePath ()
{
    return m_pcAxisHome;
}

/*int main(void)
{
    AxisConfig* objConfig = new AxisConfig();
    objConfig->ReadConfFile();
    char* pWsddPath = objConfig->GetWsddFilePath();
    printf("pWsddPath:%s\n", pWsddPath);
    char* LogPath = objConfig->GetAxisLogPath();
    //to build
    //gcc AxisConfig.cpp -o temp -I$AXISCPP_HOME/include -L$AXISCPP_HOME/bin -lserver_engine -ldl

}
*/
