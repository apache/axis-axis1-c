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
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 *
 */

#include "AxisConfig.h"
#include <axis/server/GDefine.h>
#include "../common/AxisFile.h"
#include "AxisUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

AXIS_CPP_NAMESPACE_START

AxisConfig::AxisConfig ()
{
    m_pcAxisHome = 0;
	m_pcKeyArray[AXCONF_WSDDFILEPATH] = "WSDDFilePath";
	m_pcKeyArray[AXCONF_LOGPATH] = "LogPath";
	m_pcKeyArray[AXCONF_CLIENTLOGPATH] = "ClientLogPath";
	m_pcKeyArray[AXCONF_CLIENTWSDDFILEPATH] = "ClientWSDDFilePath";
	/*
	The value for this is taken from the environment variable "AXISCPP_DEPLOY".
	So no need for a key for AXCONF_AXISHOME
	*/
	m_pcKeyArray[AXCONF_AXISHOME] = "\0";
	m_pcKeyArray[AXCONF_TRANSPORTHTTP]="Transport_http";
	m_pcKeyArray[AXCONF_TRANSPORTSMTP]="Transport_smtp";
	m_pcKeyArray[AXCONF_XMLPARSER] = "XMLParser";
	m_pcKeyArray[AXCONF_NODENAME] = "NodeName";
	m_pcKeyArray[AXCONF_LISTENPORT] = "ListenPort";

    for(int i=0;i<AXCONF_LAST;i++)
	{
        m_pcValueArray[i] = NULL; 
	}

#ifdef _DEBUG
#ifdef WIN32
	m_pcValueArray[AXCONF_XMLPARSER] = "AxisXMLParser_D.dll";
	m_pcValueArray[AXCONF_TRANSPORTHTTP] = "AxisTransport_D.dll";
    m_pcValueArray[AXCONF_NODENAME] = "server name";
    m_pcValueArray[AXCONF_LISTENPORT] = "listen port";
#else
	m_pcValueArray[AXCONF_XMLPARSER] = "/usr/local/Axis/libs/libaxis_xmlparser.so";
	m_pcValueArray[AXCONF_TRANSPORTHTTP] = "/usr/local/Axis/libs/libaxis_transport.so";
    m_pcValueArray[AXCONF_NODENAME] = "server name";
    m_pcValueArray[AXCONF_LISTENPORT] = "listen port";
#endif
#else
#ifdef WIN32
    m_pcValueArray[AXCONF_XMLPARSER] = "AxisXMLParser.dll";
	m_pcValueArray[AXCONF_TRANSPORTHTTP] = "AxisTransport.dll";
    m_pcValueArray[AXCONF_NODENAME] = "server name";
    m_pcValueArray[AXCONF_LISTENPORT] = "listen port";
#else
	m_pcValueArray[AXCONF_XMLPARSER] = "/usr/local/axiscpp_deploy/lib/libaxis_xmlparser.so";
	m_pcValueArray[AXCONF_TRANSPORTHTTP] = "/usr/local/axiscpp_deploy/lib/libaxis_transport.so";
    m_pcValueArray[AXCONF_LOGPATH] = "/usr/local/axiscpp_deploy/log/AxisLog";
    m_pcValueArray[AXCONF_CLIENTLOGPATH] = "/usr/local/axiscpp_deploy/log/AxisClientLog";
    m_pcValueArray[AXCONF_NODENAME] = "server name";
    m_pcValueArray[AXCONF_LISTENPORT] = "listen port";
#endif
#endif

}

AxisConfig::~AxisConfig ()
{
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


    sConfPath = getenv ("AXISCPP_DEPLOY");
	m_pcValueArray[AXCONF_AXISHOME] = sConfPath;
	/*
	Even if the AXISCPP_DEPLOY environment variable is not set default values 
	will be used. Therefore return AXIS_SUCCESS
	*/
    if (!sConfPath || (sConfPath == '\0') )
		return AXIS_SUCCESS;
    m_pcAxisHome = (char*) malloc (CONFBUFFSIZE);
    strcpy (m_pcAxisHome, sConfPath);

    strcpy (sNewConfPath, sConfPath);
#ifdef WIN32
    strcat (sNewConfPath, "/axiscpp.conf");
#else
    strcat (sNewConfPath, "/etc/axiscpp.conf");
#endif
	/*
	Even if axiscpp.conf does not exist in AXISCPP_DEPLOY default values 
	will be used. Therefore return AXIS_SUCCESS
	*/
    if (AXIS_SUCCESS != fileConfig.fileOpen(sNewConfPath, "r"))
		return AXIS_SUCCESS;

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
        key = (char*) malloc (pcValue - carrLine + 1);
        pcValue[0] = '\0';
        sscanf (carrLine, "%s", key);
		iValueLength = linesize - strlen (key) - 1;

        for(int i=0;i<AXCONF_LAST;i++)
		{
			if(strcmp(key, m_pcKeyArray[i]) == 0)
			{
				setValue(iValueLength, (g_axconfig)i, pcValue+1);
				break;
			}
		}

		free(key);
    }

    return AXIS_SUCCESS;
}

void AxisConfig::setValue(int valuelength, g_axconfig valueindex, char* value)
{
    m_pcValueArray[valueindex] =  (char*) malloc (valuelength+1);
    strncpy (m_pcValueArray[valueindex], value, valuelength+1);
	//*(m_pcValueArray[valueindex]+valuelength)
        //= '\0';
}


char* AxisConfig::getAxisConfProperty(g_axconfig property)
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

AXIS_CPP_NAMESPACE_END