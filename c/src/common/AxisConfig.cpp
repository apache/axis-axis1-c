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
	m_pcKeyArray[AXCONF_AXISHOME] = "";
	m_pcKeyArray[AXCONF_TRANSPORTHTTP]="AXISTRANSPORT_HTTP";
	m_pcKeyArray[AXCONF_TRANSPORTSMTP]="AXISTRANSPORT_SMTP";
	m_pcKeyArray[AXCONF_XMLPARSER] = "AXISXMLPARSER";

    for(int i=0;i<NOOFPROPERTIES;i++)
	{
        m_pcValueArray[i] = NULL; 
	}

#ifdef _DEBUG
	m_pcValueArray[AXCONF_XMLPARSER] = "AxisXMLParser_D.dll";
	m_pcValueArray[AXCONF_TRANSPORTHTTP] = "AxisTransport_D.dll";
#else
    m_pcValueArray[AXCONF_XMLPARSER] = "AxisXMLParser.dll";
	m_pcValueArray[AXCONF_TRANSPORTHTTP] = "AxisTransport.dll";
#endif

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
	int iValueLength = 0;
	const char* pcSeparator = ":";
	const char pcComment = '#';


    sConfPath = getenv ("AXIS_HOME");
	m_pcValueArray[AXCONF_AXISHOME] = sConfPath;
	/*
	Even if the AXIS_HOME environment variable is not set it is handled.
	Therefore return AXIS_SUCCESS
	*/
    if (!sConfPath)
		return AXIS_SUCCESS;
    m_pcAxisHome = (char*) malloc (CONFBUFFSIZE);
    strcpy (m_pcAxisHome, sConfPath);

    strcpy (sNewConfPath, sConfPath);
    strcat (sNewConfPath, "/axiscpp.conf");
    if (AXIS_SUCCESS != fileConfig.fileOpen(sNewConfPath, "r"))
        return AXIS_FAIL;

    while (AXIS_SUCCESS == fileConfig.fileGet(carrLine, CONFBUFFSIZE)) 
    {
        int linesize = strlen (carrLine);
		/*
		Ignore lines starting with # and empty lines
		*/
		if(carrLine[0]== pcComment || carrLine[0]=='\0')
			continue;
        pcValue = strpbrk (carrLine, pcSeparator);
        if (!pcValue)
            break;
        key = (char*) malloc (strlen (pcValue));
        pcValue[0] = '\0';
        sscanf (carrLine, "%s", key);
		iValueLength = linesize - strlen (key) - 1;

        for(int i=0;i<=NOOFPROPERTIES;i++)
		{
			if(strcmp(key, m_pcKeyArray[i]) == 0)
			{
				setValue(iValueLength, (g_axconfig)i, pcValue+1);
				break;
			}
		}

    }

    return AXIS_SUCCESS;
}

void AxisConfig::setValue(int valuelength, g_axconfig valueindex, char* value)
{
    m_pcValueArray[valueindex] =  (char*) malloc (valuelength);
    strncpy (m_pcValueArray[valueindex], value, valuelength);
	*(m_pcValueArray[valueindex]+valuelength)
        = '\0';
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
