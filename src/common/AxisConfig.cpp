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
    m_pcAxisHome = 0;
	m_pcKeyArray[AXCONF_WSDDFILEPATH] = "WSDDFILEPATH";
	m_pcKeyArray[AXCONF_LOGPATH] = "AXISLOGPATH";
	m_pcKeyArray[AXCONF_CLIENTLOGPATH] = "AXISCLIENTLOGPATH";
	m_pcKeyArray[AXCONF_CLIENTWSDDFILEPATH] = "CLIENTWSDDFILEPATH";
	/*
	The value for this is taken from the environment variable "AXIS_HOME".
	So no need for a key for AXCONF_AXISHOME
	*/
	m_pcKeyArray[AXCONF_AXISHOME] = 0;
	m_pcKeyArray[AXCONF_TRANSPORTHTTP]="AXISTRANSPORT_HTTP";
	m_pcKeyArray[AXCONF_TRANSPORTSMTP]="AXISTRANSPORT_SMTP";
	m_pcKeyArray[AXCONF_XMLPARSER] = "AXISXMLPARSER";
}

AxisConfig::~AxisConfig ()
{
    for(int i=0;i<NOOFPROPERTIES;i++)
	{
        free(m_pcValueArray[i]);
	}
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
	m_pcValueArray[AXCONF_AXISHOME] = sConfPath;
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
			m_pcValueArray[AXCONF_WSDDFILEPATH] =  (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcValueArray[AXCONF_WSDDFILEPATH], pcValue + 
				1, linesize - strlen (key) - 2);
			*(m_pcValueArray[AXCONF_WSDDFILEPATH]+linesize - strlen (key) - 2)
				= '\0';
        }
        if (strcmp (key, "AXISLOGPATH") == 0)
        {
			m_pcValueArray[AXCONF_LOGPATH] =  (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcValueArray[AXCONF_LOGPATH], pcValue + 
				1, linesize - strlen (key) - 2);
			*(m_pcValueArray[AXCONF_LOGPATH]+linesize - strlen (key) - 2)
				= '\0';
        }
        if (strcmp (key, "AXISCLIENTLOGPATH") == 0)
        {
			m_pcValueArray[AXCONF_CLIENTLOGPATH] =  (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcValueArray[AXCONF_CLIENTLOGPATH], pcValue + 
				1, linesize - strlen (key) - 2);
			*(m_pcValueArray[AXCONF_CLIENTLOGPATH]+linesize - strlen (key) - 2)
				= '\0';
        }
        if (strcmp (key, "CLIENTWSDDFILEPATH") == 0)
        {
			m_pcValueArray[AXCONF_CLIENTWSDDFILEPATH] =  (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcValueArray[AXCONF_CLIENTWSDDFILEPATH], pcValue + 
				1, linesize - strlen (key) - 2);
			*(m_pcValueArray[AXCONF_CLIENTWSDDFILEPATH]+linesize - 
				strlen (key) - 2) = '\0';
        }
        if (strcmp (key, "AXISTRANSPORT_HTTP") == 0)
        {
			m_pcValueArray[AXCONF_TRANSPORTHTTP] =  (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcValueArray[AXCONF_TRANSPORTHTTP], pcValue + 
				1, linesize - strlen (key) - 2);
			*(m_pcValueArray[AXCONF_TRANSPORTHTTP]+linesize - 
				strlen (key) - 2) = '\0';
        }
        if (strcmp (key, "AXISTRANSPORT_SMTP") == 0)
        {
			m_pcValueArray[AXCONF_TRANSPORTSMTP] =  (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcValueArray[AXCONF_TRANSPORTSMTP], pcValue + 
				1, linesize - strlen (key) - 2);
			*(m_pcValueArray[AXCONF_TRANSPORTSMTP]+linesize - 
				strlen (key) - 2) = '\0';
        }
        if (strcmp (key, "AXISXMLPARSER") == 0)
        {
			m_pcValueArray[AXCONF_XMLPARSER] =  (char*) malloc (CONFBUFFSIZE);
            strncpy (m_pcValueArray[AXCONF_XMLPARSER], pcValue + 
				1, linesize - strlen (key) - 2);
			*(m_pcValueArray[AXCONF_XMLPARSER]+linesize - 
				strlen (key) - 2) = '\0';
        }

    }

    return AXIS_SUCCESS;
}

char* AxisConfig::getAxConfProperty(g_axconfig property)
{
	return m_pcValueArray[property];
}


/*
int main(void)
{
    AxisConfig* objConfig = new AxisConfig();
    objConfig->readConfFile();
    char* pWsddPath = objConfig->getWsddFilePath();
    printf("pWsddPath:%s\n", pWsddPath);
    char* LogPath = objConfig->getAxisLogPath();
    //to build
    //gcc AxisConfig.cpp -o temp -I$AXISCPP_HOME/include -L$AXISCPP_HOME/bin -lserver_engine -ldl

}

*/
