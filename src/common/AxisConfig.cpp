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

AXIS_CPP_NAMESPACE_START AxisConfig::AxisConfig ()
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
    m_pcKeyArray[AXCONF_TRANSPORTHTTP] = "Transport_http";
    m_pcKeyArray[AXCONF_TRANSPORTSMTP] = "Transport_smtp";
    m_pcKeyArray[AXCONF_XMLPARSER] = "XMLParser";
    m_pcKeyArray[AXCONF_NODENAME] = "NodeName";
    m_pcKeyArray[AXCONF_LISTENPORT] = "ListenPort";

    for (int i = 0; i < AXCONF_LAST; i++)
    {
	m_pcValueArray[i] = NULL;
    }

#ifdef _DEBUG
#ifdef WIN32
    // Samisa : I used strdup here so that I could use free in destructor
    // This was done to make sure that the memory allocated in AxisConfig::setValue
    // is freed properly
    m_pcValueArray[AXCONF_XMLPARSER] = strdup ("AxisXMLParser_D.dll");
    m_pcValueArray[AXCONF_TRANSPORTHTTP] = strdup ("AxisTransport_D.dll");
    m_pcValueArray[AXCONF_NODENAME] = strdup ("server name");
    m_pcValueArray[AXCONF_LISTENPORT] = strdup ("listen port");
#else
    m_pcValueArray[AXCONF_XMLPARSER] =
	strdup ("/usr/local/axiscpp_deploy/lib/libaxis_xmlparser.so");
    m_pcValueArray[AXCONF_TRANSPORTHTTP] =
	strdup ("/usr/local/axiscpp_deploy/lib/libaxis_transport.so");
    m_pcValueArray[AXCONF_NODENAME] = strdup ("server name");
    m_pcValueArray[AXCONF_LISTENPORT] = strdup ("listen port");
#endif
#else
#ifdef WIN32
    m_pcValueArray[AXCONF_XMLPARSER] = strdup ("AxisXMLParser.dll");
    m_pcValueArray[AXCONF_TRANSPORTHTTP] = strdup ("AxisTransport.dll");
    m_pcValueArray[AXCONF_NODENAME] = strdup ("server name");
    m_pcValueArray[AXCONF_LISTENPORT] = strdup ("listen port");
#else
    m_pcValueArray[AXCONF_XMLPARSER] =
	strdup ("/usr/local/axiscpp_deploy/lib/libaxis_xmlparser.so");
    m_pcValueArray[AXCONF_TRANSPORTHTTP] =
	strdup ("/usr/local/axiscpp_deploy/lib/libaxis_transport.so");
    m_pcValueArray[AXCONF_LOGPATH] =
	strdup ("/usr/local/axiscpp_deploy/log/AxisLog");
    m_pcValueArray[AXCONF_CLIENTLOGPATH] =
	strdup ("/usr/local/axiscpp_deploy/log/AxisClientLog");
    m_pcValueArray[AXCONF_NODENAME] = strdup ("server name");
    m_pcValueArray[AXCONF_LISTENPORT] = strdup ("listen port");
#endif
#endif

}

AxisConfig::~AxisConfig ()
{
    for (int i = 0; i < AXCONF_LAST; i++)
    {
        if (m_pcValueArray[i])
	    free(m_pcValueArray[i]);
    }

    if (m_pcAxisHome)
        free(m_pcAxisHome);
}

int
AxisConfig::readConfFile ()
{
    char carrLine[CONFBUFFSIZE];
    char *pcValue;
    AxisFile fileConfig;	/*AxisFile is AxisC++ resource for file manipulation */
    char *sConfPath = NULL;
    char *sNewConfPath = (char *) malloc (CONFBUFFSIZE);
    char *key;
    int iValueLength = 0;
    const char *pcSeparator = ":";
    const char pcComment = '#';

    sConfPath = getenv ("AXISCPP_DEPLOY");
    if (!sConfPath)
        sConfPath = "";
    m_pcValueArray[AXCONF_AXISHOME] = strdup(sConfPath);
    /*
       Even if the AXISCPP_DEPLOY environment variable is not set default values 
       will be used. Therefore return AXIS_SUCCESS
     */
    if (!sConfPath || (sConfPath == '\0'))
    {
	free (sNewConfPath);
	return AXIS_SUCCESS;
    }
    m_pcAxisHome = (char *) malloc (CONFBUFFSIZE);
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
    if (AXIS_SUCCESS != fileConfig.fileOpen (sNewConfPath, "r"))
    {
	

#ifdef _DEBUG
	printf
	    ("Warning - The configuration file was not found (%s).\n          Using the following default file paths.\n",
	     sNewConfPath);

	OutputConfigInfo ();
#else
	printf ("Warning - The configuration file was not found (%s).\n",
		sNewConfPath);
#endif
        free (sNewConfPath);
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
	key = (char *) malloc (pcValue - carrLine + 1);
	pcValue[0] = '\0';
	sscanf (carrLine, "%s", key);
	iValueLength = linesize - strlen (key) - 1;

	bool bKeyFound = false;

	for (int i = 0; i < AXCONF_LAST; i++)
	{
	    if (strcmp (key, m_pcKeyArray[i]) == 0)
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

	free (key);
    }

    free (sNewConfPath);

#ifdef _DEBUG
    printf ("The AXIS configuration has now been set to:-\n");

    OutputConfigInfo ();
#endif
    return AXIS_SUCCESS;
}

void
AxisConfig::setValue (int valuelength, g_axconfig valueindex, char *value)
{
    // erase memory allocated for default value
    if (m_pcValueArray[valueindex])
        free (m_pcValueArray[valueindex]);
    m_pcValueArray[valueindex] = (char *) malloc (valuelength + 1);
    strncpy (m_pcValueArray[valueindex], value, valuelength + 1);
}


char *
AxisConfig::getAxisConfProperty (g_axconfig property)
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

void
AxisConfig::OutputConfigInfo ()
{
    if (m_pcValueArray[AXCONF_WSDDFILEPATH] == NULL)
    {
	printf ("WSDD           (null)\n");
    }
    else
    {
	printf ("WSDD           %s\n", m_pcValueArray[AXCONF_WSDDFILEPATH]);
    }
    if (m_pcValueArray[AXCONF_LOGPATH] == NULL)
    {
	printf ("Log            (null)\n");
    }
    else
    {
	printf ("Log            %s\n", m_pcValueArray[AXCONF_LOGPATH]);
    }
    if (m_pcValueArray[AXCONF_CLIENTLOGPATH] == NULL)
    {
	printf ("Client Log     (null)\n");
    }
    else
    {
	printf ("Client Log     %s\n", m_pcValueArray[AXCONF_CLIENTLOGPATH]);
    }
    if (m_pcValueArray[AXCONF_CLIENTWSDDFILEPATH] == NULL)
    {
	printf ("ClientWSDD     (null)\n");
    }
    else
    {
	printf ("ClientWSDD     %s\n",
		m_pcValueArray[AXCONF_CLIENTWSDDFILEPATH]);
    }
    if (m_pcValueArray[AXCONF_AXISHOME] == NULL)
    {
	printf ("AXIS HOME      (null)\n");
    }
    else
    {
	printf ("AXIS HOME      %s\n", m_pcValueArray[AXCONF_AXISHOME]);
    }
    if (m_pcValueArray[AXCONF_TRANSPORTHTTP] == NULL)
    {
	printf ("Transport HTTP (null)\n");
    }
    else
    {
	printf ("Transport HTTP %s\n", m_pcValueArray[AXCONF_TRANSPORTHTTP]);
    }
    if (m_pcValueArray[AXCONF_TRANSPORTSMTP] == NULL)
    {
	printf ("Transport SMTP (null)\n");
    }
    else
    {
	printf ("Transport SMTP %s\n", m_pcValueArray[AXCONF_TRANSPORTSMTP]);
    }
    if (m_pcValueArray[AXCONF_XMLPARSER] == NULL)
    {
	printf ("XML Parser     (null)\n");
    }
    else
    {
	printf ("XML Parser     %s\n", m_pcValueArray[AXCONF_XMLPARSER]);
    }
    if (m_pcValueArray[AXCONF_NODENAME] == NULL)
    {
	printf ("Node Name      (null)\n");
    }
    else
    {
	printf ("Node Name      %s\n", m_pcValueArray[AXCONF_NODENAME]);
    }
    if (m_pcValueArray[AXCONF_LISTENPORT] == NULL)
    {
	printf ("Listen Port    (null)\n");
    }
    else
    {
	printf ("Listen Port    %s\n", m_pcValueArray[AXCONF_LISTENPORT]);
    }
}

AXIS_CPP_NAMESPACE_END
