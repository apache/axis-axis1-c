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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

#include "AxisConfig.h"
#include <axis/server/GDefine.h>
#include "../common/AxisFile.h"
#include "AxisUtils.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>

AXIS_CPP_NAMESPACE_START 

AxisConfig::AxisConfig ()
{
    m_pcKeyArray[AXCONF_WSDDFILEPATH] = "WSDDFilePath";
    m_pcKeyArray[AXCONF_LOGPATH] = "LogPath";
    m_pcKeyArray[AXCONF_CLIENTLOGPATH] = "ClientLogPath";
    m_pcKeyArray[AXCONF_CLIENTWSDDFILEPATH] = "ClientWSDDFilePath";
    /*
       The value for this is taken from the environment variable "AXISCPP_DEPLOY".
       So no need for a key for AXCONF_AXISHOME
     */
    m_pcKeyArray[AXCONF_AXISHOME] = "\0";
    m_pcKeyArray[AXCONF_TRANSPORTHTTP] = "Transport_http";
    m_pcKeyArray[AXCONF_TRANSPORTSMTP] = "Transport_smtp";
    m_pcKeyArray[AXCONF_XMLPARSER] = "XMLParser";
    m_pcKeyArray[AXCONF_NODENAME] = "NodeName";
    m_pcKeyArray[AXCONF_LISTENPORT] = "ListenPort";

#ifdef _DEBUG
#ifdef WIN32
    m_pcValueArray[AXCONF_XMLPARSER] = "AxisXMLParser_D.dll";
    m_pcValueArray[AXCONF_TRANSPORTHTTP] = "AxisTransport_D.dll";
    m_pcValueArray[AXCONF_NODENAME] = "server name";
    m_pcValueArray[AXCONF_LISTENPORT] = "listen port";
#else
    m_pcValueArray[AXCONF_XMLPARSER] = 
		"/usr/local/axiscpp_deploy/lib/libaxis_xmlparser.so";
    m_pcValueArray[AXCONF_TRANSPORTHTTP] =
		"/usr/local/axiscpp_deploy/lib/libaxis_transport.so";
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
    m_pcValueArray[AXCONF_XMLPARSER] =
		"/usr/local/axiscpp_deploy/lib/libaxis_xmlparser.so";
    m_pcValueArray[AXCONF_TRANSPORTHTTP] =
		"/usr/local/axiscpp_deploy/lib/libaxis_transport.so";
    m_pcValueArray[AXCONF_LOGPATH] =
		"/usr/local/axiscpp_deploy/log/AxisLog";
    m_pcValueArray[AXCONF_CLIENTLOGPATH] =
		"/usr/local/axiscpp_deploy/log/AxisClientLog";
    m_pcValueArray[AXCONF_NODENAME] = "server name";
    m_pcValueArray[AXCONF_LISTENPORT] = "listen port";
#endif
#endif

}

int AxisConfig::readConfFile ()
{
    char carrLine[CONFBUFFSIZE];
    char *pcValue;
    AxisFile fileConfig;	/*AxisFile is AxisC++ resource for file manipulation */
    char *sConfPath = NULL;
    char sNewConfPath[CONFBUFFSIZE];
    char key[CONFBUFFSIZE];
    int iValueLength = 0;
    const char *pcSeparator = ":";
    const char pcComment = '#';

    sConfPath = getenv ("AXISCPP_DEPLOY");
    if (!sConfPath)
        sConfPath = "";
    m_pcValueArray[AXCONF_AXISHOME] = sConfPath;
    /*
       Even if the AXISCPP_DEPLOY environment variable is not set default values 
       will be used. Therefore return AXIS_SUCCESS
     */
    if (!sConfPath || (sConfPath == '\0'))
    {
	    return AXIS_SUCCESS;
    }

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
    if (AXIS_SUCCESS != fileConfig.fileOpen (sNewConfPath, "r"))
    {
	

#ifdef _DEBUG
		printf("Warning - The configuration file was not found (%s).\n", sNewConfPath);
		printf("          Using the following default file paths.\n");
		OutputConfigInfo ();
#else
		printf ("Warning - The configuration file was not found (%s).\n",
		sNewConfPath);
#endif
	    return AXIS_SUCCESS;
    }

    while (AXIS_SUCCESS == fileConfig.fileGet (carrLine, CONFBUFFSIZE))
    {
	int linesize = strlen (carrLine);
	/*
	   Ignore lines starting with # and empty lines
	 */
	if (carrLine[0] == pcComment || carrLine[0] == '\0')
	    continue;
	pcValue = strpbrk (carrLine, pcSeparator);
	if (!pcValue)
	    break;
	pcValue[0] = '\0';
	sscanf (carrLine, "%s", key);
	iValueLength = linesize - strlen (key) - 1;

	bool bKeyFound = false;

	for (int i = 0; i < AXCONF_LAST; i++)
	{
	    if (m_pcKeyArray[i] == key)
	    {
		setValue (iValueLength, (g_axconfig) i, pcValue + 1);

		// If the name/value pair is a reference to a WSDD file, then the file must exist.
		// If the WSDD file does not exist, then echo a warning to the console.
		if (strcmp ("WSDDFilePath", key) == 0 ||
		    strcmp ("ClientWSDDFilePath", key) == 0)
		{
		    FILE *fp = fopen (pcValue + 1, "r");

		    if (fp == NULL)
		    {
			printf
			    ("Warning - The %s file (%s) in the AXISCPP.CONF file does not exist.\n",
			     key, pcValue + 1);
		    }
		    else
		    {
			fclose (fp);
		    }
		}

		bKeyFound = true;
		break;
	    }
	}

	if (!bKeyFound)
	{
	    printf ("Warning - Unknown key (%s) in config file.\n", key);
	}

    }

#ifdef _DEBUG
    printf ("The AXIS configuration has now been set to:-\n");

    OutputConfigInfo ();
#endif
    return AXIS_SUCCESS;
}

void AxisConfig::setValue (int valuelength, g_axconfig valueindex, char *value)
{
	// m_pcValueArray is a string and the string class will copy the value, so 
	// no need to copy the value into our own storage here.
    m_pcValueArray[valueindex] = value;
}


char* AxisConfig::getAxisConfProperty (g_axconfig property)
{
    if (0 == m_pcValueArray[property].length()) return NULL;
	return (char*)(m_pcValueArray[property].c_str());
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

void
AxisConfig::OutputConfigInfo ()
{
    if (m_pcValueArray[AXCONF_WSDDFILEPATH].length() == 0)
    {
	printf ("WSDD           (null)\n");
    }
    else
    {
	printf ("WSDD           %s\n", m_pcValueArray[AXCONF_WSDDFILEPATH].c_str());
    }
    if (m_pcValueArray[AXCONF_LOGPATH].length() == 0)
    {
	printf ("Log            (null)\n");
    }
    else
    {
	printf ("Log            %s\n", m_pcValueArray[AXCONF_LOGPATH].c_str());
    }
    if (m_pcValueArray[AXCONF_CLIENTLOGPATH].length() == 0)
    {
	printf ("Client Log     (null)\n");
    }
    else
    {
	printf ("Client Log     %s\n", m_pcValueArray[AXCONF_CLIENTLOGPATH].c_str());
    }
    if (m_pcValueArray[AXCONF_CLIENTWSDDFILEPATH].length() == 0)
    {
	printf ("ClientWSDD     (null)\n");
    }
    else
    {
	printf ("ClientWSDD     %s\n",
		m_pcValueArray[AXCONF_CLIENTWSDDFILEPATH].c_str());
    }
    if (m_pcValueArray[AXCONF_AXISHOME].length() == 0)
    {
	printf ("AXIS HOME      (null)\n");
    }
    else
    {
	printf ("AXIS HOME      %s\n", m_pcValueArray[AXCONF_AXISHOME].c_str());
    }
    if (m_pcValueArray[AXCONF_TRANSPORTHTTP].length() == 0)
    {
	printf ("Transport HTTP (null)\n");
    }
    else
    {
	printf ("Transport HTTP %s\n", m_pcValueArray[AXCONF_TRANSPORTHTTP].c_str());
    }
    if (m_pcValueArray[AXCONF_TRANSPORTSMTP].length() == 0)
    {
	printf ("Transport SMTP (null)\n");
    }
    else
    {
	printf ("Transport SMTP %s\n", m_pcValueArray[AXCONF_TRANSPORTSMTP].c_str());
    }
    if (m_pcValueArray[AXCONF_XMLPARSER].length() == 0)
    {
	printf ("XML Parser     (null)\n");
    }
    else
    {
	printf ("XML Parser     %s\n", m_pcValueArray[AXCONF_XMLPARSER].c_str());
    }
    if (m_pcValueArray[AXCONF_NODENAME].length() == 0)
    {
	printf ("Node Name      (null)\n");
    }
    else
    {
	printf ("Node Name      %s\n", m_pcValueArray[AXCONF_NODENAME].c_str());
    }
    if (m_pcValueArray[AXCONF_LISTENPORT].length() == 0)
    {
	printf ("Listen Port    (null)\n");
    }
    else
    {
	printf ("Listen Port    %s\n", m_pcValueArray[AXCONF_LISTENPORT].c_str());
    }
}

AXIS_CPP_NAMESPACE_END
