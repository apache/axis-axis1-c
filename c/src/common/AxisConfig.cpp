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
#include "AxisUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

AxisConfig::AxisConfig ()
{
    m_sWsddFilePath = 0;
    m_sAxisLogPath = 0;
    m_sClientWsddFilePath = 0;
    m_sAxisHome = 0;
    m_sValue = NULL;
}

AxisConfig::~AxisConfig ()
{
    if (m_sWsddFilePath)
        free(m_sWsddFilePath);
    if (m_sAxisLogPath)
        free(m_sAxisLogPath);
    if (m_sClientWsddFilePath)
        free(m_sClientWsddFilePath);
    if (m_sAxisHome)
        free(m_sAxisHome);
    if (m_sValue)
        free(m_sValue);
}

int AxisConfig::readConfFile ()
{
    FILE* fileConfig = NULL;
    char* sConfPath = NULL;
    char sNewConfPath[CONFBUFFSIZE] = { 0 };
    //char key[CONFBUFFSIZE] = {0};
    char* key;
    //char m_sLine[CONFBUFFSIZE] = {0};
    //char value[CONFBUFFSIZE] = {0};


    sConfPath = getenv ("AXIS_HOME");
    if (!sConfPath)
        return AXIS_FAIL;
    m_sAxisHome = (char*) malloc (CONFBUFFSIZE);
    strcpy (m_sAxisHome, sConfPath);

    strcpy (sNewConfPath, sConfPath);
    strcat (sNewConfPath, "/axiscpp.conf");
    if ((fileConfig = fopen (sNewConfPath, "r")) == NULL)
        return AXIS_FAIL;

    while (fgets (m_sLine, CONFBUFFSIZE, fileConfig) != NULL)
    {
        int linesize = strlen (m_sLine);
        m_sValue = strpbrk (m_sLine, ":");
        if (!m_sValue)
            break;
        key = (char*) malloc (strlen (m_sValue));
        m_sValue[0] = '\0';
        sscanf (m_sLine, "%s", key);

        if (strcmp (key, "WSDDFILEPATH") == 0)
        {
            m_sWsddFilePath = (char*) malloc (CONFBUFFSIZE);
            strncpy (m_sWsddFilePath, m_sValue + 1, linesize - strlen (key) - 2);
            m_sWsddFilePath[linesize - strlen (key) - 2] = '\0';
        }
        if (strcmp (key, "AXISLOGPATH") == 0)
        {
            m_sAxisLogPath = (char*) malloc (CONFBUFFSIZE);
            strncpy (m_sAxisLogPath, m_sValue + 1, linesize - strlen (key) - 2);
            m_sAxisLogPath[linesize - strlen (key) - 2] = '\0';
        }
        if (strcmp (key, "CLIENTWSDDFILEPATH") == 0)
        {
            m_sClientWsddFilePath = (char*) malloc (CONFBUFFSIZE);
            strncpy (m_sClientWsddFilePath, m_sValue + 1,
                linesize - strlen (key) - 2);
            m_sClientWsddFilePath[linesize - strlen (key) - 2] = '\0';
        }
    }


    return AXIS_SUCCESS;
}

char* AxisConfig::getWsddFilePath ()
{
    return m_sWsddFilePath;
}

char* AxisConfig::getAxisLogPath ()
{
    return m_sAxisLogPath;
}


char* AxisConfig::getClientWsddFilePath ()
{
    return m_sClientWsddFilePath;
}

char* AxisConfig::getAxisHomePath ()
{
    return m_sAxisHome;
}

/*int main(void)
{
    AxisConfig* objConfig = new AxisConfig();
    objConfig->ReadConfFile();
    char* pWsddPath = objConfig->GetWsddFilePath();
    printf("pWsddPath:%s\n", pWsddPath);
    char* LogPath = objConfig->GetAxisLogPath();

}
*/
