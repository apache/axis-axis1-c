/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include <axis/GDefine.hpp>

#include "AxisConfig.h"
#include "AxisFile.h"
#include "AxisUtils.h"

#include "AxisTrace.h"

AXIS_CPP_NAMESPACE_START 

AxisConfig::AxisConfig()
{
    m_pcKeyArray[AXCONF_WSDDFILEPATH]       = AXCONF_WSDDFILEPATH_TAGNAME;
    m_pcKeyArray[AXCONF_LOGPATH]            = AXCONF_LOGPATH_TAGNAME;
    m_pcKeyArray[AXCONF_CLIENTLOGPATH]      = AXCONF_CLIENTLOGPATH_TAGNAME;
    m_pcKeyArray[AXCONF_CLIENTWSDDFILEPATH] = AXCONF_CLIENTWSDDFILEPATH_TAGNAME;
  
    m_pcKeyArray[AXCONF_AXISHOME]       = "\0"; // will be obtained dynamically.
    m_pcKeyArray[AXCONF_TRANSPORTHTTP]  = AXCONF_TRANSPORTHTTP_TAGNAME;
    m_pcKeyArray[AXCONF_SSLCHANNEL_HTTP]= AXCONF_SSLCHANNEL_HTTP_TAGNAME;
    m_pcKeyArray[AXCONF_CHANNEL_HTTP]   = AXCONF_CHANNEL_HTTP_TAGNAME;
    m_pcKeyArray[AXCONF_TRANSPORTSMTP]  = AXCONF_TRANSPORTSMTP_TAGNAME;
    m_pcKeyArray[AXCONF_XMLPARSER]      = AXCONF_XMLPARSER_TAGNAME;
    m_pcKeyArray[AXCONF_NODENAME]       = AXCONF_NODENAME_TAGNAME;
    m_pcKeyArray[AXCONF_LISTENPORT]     = AXCONF_LISTENPORT_TAGNAME;
    m_pcKeyArray[AXCONF_SECUREINFO]     = AXCONF_SECUREINFO_TAGNAME;

    m_pcValueArray[AXCONF_NODENAME]          = "server name";
    m_pcValueArray[AXCONF_LISTENPORT]        = "listen port";
    m_pcValueArray[AXCONF_XMLPARSER]         = PLATFORM_XMLPARSER_PATH;
    m_pcValueArray[AXCONF_TRANSPORTHTTP]     = PLATFORM_TRANSPORTHTTP_PATH;
    m_pcValueArray[AXCONF_LOGPATH]           = PLATFORM_LOG_PATH;
    m_pcValueArray[AXCONF_CLIENTLOGPATH]     = PLATFORM_CLIENTLOG_PATH;
    m_pcValueArray[AXCONF_SSLCHANNEL_HTTP]   = PLATFORM_SSLCHANNEL_PATH;
    m_pcValueArray[AXCONF_CHANNEL_HTTP]      = PLATFORM_CHANNEL_PATH;
    m_pcValueArray[AXCONF_SECUREINFO]        = PLATFORM_SECUREINFO;
    m_pcValueArray[AXCONF_AXISHOME]          = PLATFORM_DEFAULT_DEPLOY_PATH;
}

//AxisConfig::AxisConfig( bool bDefaultsOnly)
AxisConfig::AxisConfig( AxisConfig * pOrgAxisConfig)
{
    m_pcKeyArray[AXCONF_WSDDFILEPATH]       = AXCONF_WSDDFILEPATH_TAGNAME;
    m_pcKeyArray[AXCONF_LOGPATH]            = AXCONF_LOGPATH_TAGNAME;
    m_pcKeyArray[AXCONF_CLIENTLOGPATH]      = AXCONF_CLIENTLOGPATH_TAGNAME;
    m_pcKeyArray[AXCONF_CLIENTWSDDFILEPATH] = AXCONF_CLIENTWSDDFILEPATH_TAGNAME;
  
    m_pcKeyArray[AXCONF_AXISHOME]       = "\0"; // will be obtained dynamically.
    m_pcKeyArray[AXCONF_TRANSPORTHTTP]  = AXCONF_TRANSPORTHTTP_TAGNAME;
    m_pcKeyArray[AXCONF_SSLCHANNEL_HTTP]= AXCONF_SSLCHANNEL_HTTP_TAGNAME;
    m_pcKeyArray[AXCONF_CHANNEL_HTTP]   = AXCONF_CHANNEL_HTTP_TAGNAME;
    m_pcKeyArray[AXCONF_TRANSPORTSMTP]  = AXCONF_TRANSPORTSMTP_TAGNAME;
    m_pcKeyArray[AXCONF_XMLPARSER]      = AXCONF_XMLPARSER_TAGNAME;
    m_pcKeyArray[AXCONF_NODENAME]       = AXCONF_NODENAME_TAGNAME;
    m_pcKeyArray[AXCONF_LISTENPORT]     = AXCONF_LISTENPORT_TAGNAME;
    m_pcKeyArray[AXCONF_SECUREINFO]     = AXCONF_SECUREINFO_TAGNAME;

	char *	pszDefaultValues[] = {"",							// (AXCONF_WSDDFILEPATH) Server WSDD File Path
								  PLATFORM_LOG_PATH,			// (AXCONF_LOGPATH) Server log path
								  PLATFORM_CLIENTLOG_PATH,		// (AXCONF_CLIENTLOGPATH) Client log path
								  "",							// (AXCONF_CLIENTWSDDFILEPATH) Client WSDD File Path
								  PLATFORM_DEFAULT_DEPLOY_PATH,	// (AXCONF_AXISHOME) Axis home
								  PLATFORM_TRANSPORTHTTP_PATH,	// (AXCONF_TRANSPORTHTTP) Transport HTTP path
								  "",							// (AXCONF_TRANSPORTSMTP) Transport SMTP path
								  PLATFORM_XMLPARSER_PATH,		// (AXCONF_XMLPARSER) XML Parser path
								  "server name",				// (AXCONF_NODENAME) Node name
								  "listen port",				// (AXCONF_LISTENPORT) Listener port
								  PLATFORM_SSLCHANNEL_PATH,		// (AXCONF_SSLCHANNEL_HTTP) HTTP SSL Channel
								  PLATFORM_CHANNEL_PATH,		// (AXCONF_CHANNEL_HTTP) HTTP Channel
								  PLATFORM_SECUREINFO};			// (AXCONF_SECUREINFO) HTTP SSL secure information

	for( int iPropertyCount = 0; iPropertyCount < AXCONF_LAST; iPropertyCount++)
	{
		char *	pszValue = pOrgAxisConfig->getAxisConfProperty( (g_axconfig) iPropertyCount);

		if( pszValue == NULL)
		{
			m_pcValueArray[iPropertyCount] = pszDefaultValues[iPropertyCount];
		}
		else
		{
			m_pcValueArray[iPropertyCount] = pszValue;
		}
	}

	delete pOrgAxisConfig;
/*
	m_pcValueArray[AXCONF_NODENAME]			 = "server name";
    m_pcValueArray[AXCONF_LISTENPORT]        = "listen port";
    m_pcValueArray[AXCONF_XMLPARSER]         = PLATFORM_XMLPARSER_PATH;
    m_pcValueArray[AXCONF_TRANSPORTHTTP]     = PLATFORM_TRANSPORTHTTP_PATH;
    m_pcValueArray[AXCONF_LOGPATH]           = PLATFORM_LOG_PATH;
    m_pcValueArray[AXCONF_CLIENTLOGPATH]     = PLATFORM_CLIENTLOG_PATH;
    m_pcValueArray[AXCONF_SSLCHANNEL_HTTP]   = PLATFORM_SSLCHANNEL_PATH;
    m_pcValueArray[AXCONF_CHANNEL_HTTP]      = PLATFORM_CHANNEL_PATH;
    m_pcValueArray[AXCONF_SECUREINFO]        = PLATFORM_SECUREINFO;
    m_pcValueArray[AXCONF_AXISHOME]          = PLATFORM_DEFAULT_DEPLOY_PATH;
*/
}

int AxisConfig::readConfFile ()
{
    char carrLine[CONFBUFFSIZE];
    char *pcValue = NULL;
    AxisFile fileConfig;    // AxisFile is resource for file manipulation
    char *sConfPath = NULL;
    char sNewConfPath[CONFBUFFSIZE];
    char key[CONFBUFFSIZE];
    long iValueLength = 0;
    const char *pcSeparator = ":";
    const char pcComment = '#';

    // Obtain AXIS deployment path from environment,  If not set, we will use
    // default deployment path.  Note that default deployment path is the NULL
    // string unless it is modified.
    sConfPath = getenv ("AXISCPP_DEPLOY");
    if (sConfPath)
        setValue(0,AXCONF_AXISHOME,sConfPath);

    // get the value of the path
    sConfPath = getAxisConfProperty(AXCONF_AXISHOME);
    
    // If the AXIS deployment path is not set default values 
    // will be used. Therefore return AXIS_SUCCESS
    if (!sConfPath || (*sConfPath == '\0'))
    {
        return AXIS_SUCCESS;
    }

    strcpy (sNewConfPath, sConfPath);
    strcat (sNewConfPath, PLATFORM_CONFIG_PATH);
    
    // Even if axiscpp.conf does not exist in AXISCPP_DEPLOY default values 
    // will be used. Therefore return AXIS_SUCCESS
    if (AXIS_SUCCESS != fileConfig.fileOpen (sNewConfPath, "r"))
        return AXIS_SUCCESS;

    while (AXIS_SUCCESS == fileConfig.fileGet (carrLine, CONFBUFFSIZE))
    {
        long linesize = strlen (carrLine);
        
        // Ignore lines starting with # and empty lines
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
        
                // If the name/value pair is a reference to a WSDD file, then the 
                // file must exist. If the WSDD file does not exist, then echo a 
                // warning to the console.
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

AXIS_CPP_NAMESPACE_END
