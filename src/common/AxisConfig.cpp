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

#include "../platforms/PlatformAutoSense.hpp"

#include "AxisConfig.h"
#include <axis/GDefine.hpp>
#include "../common/AxisFile.h"
#include "AxisUtils.h"
#include <stdlib.h>
#include <iostream>
#include <string>

AXIS_CPP_NAMESPACE_START 

AxisConfig::AxisConfig ()
{
    m_pcKeyArray[AXCONF_WSDDFILEPATH]       = "WSDDFilePath";
    m_pcKeyArray[AXCONF_LOGPATH]            = "LogPath";
    m_pcKeyArray[AXCONF_CLIENTLOGPATH]      = "ClientLogPath";
    m_pcKeyArray[AXCONF_CLIENTWSDDFILEPATH] = "ClientWSDDFilePath";
  
    m_pcKeyArray[AXCONF_AXISHOME]       = "\0"; // will be obtained dynamically.
    m_pcKeyArray[AXCONF_TRANSPORTHTTP]  = "Transport_http";
    m_pcKeyArray[AXCONF_SSLCHANNEL_HTTP]= "Channel_HTTP_SSL";
    m_pcKeyArray[AXCONF_CHANNEL_HTTP]   = "Channel_HTTP";
    m_pcKeyArray[AXCONF_TRANSPORTSMTP]  = "Transport_smtp";
    m_pcKeyArray[AXCONF_XMLPARSER]      = "XMLParser";
    m_pcKeyArray[AXCONF_NODENAME]       = "NodeName";
    m_pcKeyArray[AXCONF_LISTENPORT]     = "ListenPort";
    m_pcKeyArray[AXCONF_SECUREINFO]     = "SecureInfo";

    m_pcValueArray[AXCONF_NODENAME]          = "server name";
    m_pcValueArray[AXCONF_LISTENPORT]        = "listen port";
    m_pcValueArray[AXCONF_XMLPARSER]         = PLATFORM_XMLPARSER_PATH;
    m_pcValueArray[AXCONF_TRANSPORTHTTP]     = PLATFORM_TRANSPORTHTTP_PATH;
    m_pcValueArray[AXCONF_LOGPATH]           = PLATFORM_LOG_PATH;
    m_pcValueArray[AXCONF_CLIENTLOGPATH]     = PLATFORM_CLIENTLOG_PATH;
    m_pcValueArray[AXCONF_SSLCHANNEL_HTTP]   = PLATFORM_SSLCHANNEL_PATH;
    m_pcValueArray[AXCONF_CHANNEL_HTTP]      = PLATFORM_CHANNEL_PATH;
    m_pcValueArray[AXCONF_SECUREINFO]        = PLATFORM_SECUREINFO;
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
    if (!sConfPath)
        sConfPath = PLATFORM_DEFAULT_DEPLOY_PATH;
    m_pcValueArray[AXCONF_AXISHOME] = sConfPath;
    
    // If the AXIS deployment path is not set default values 
    // will be used. Therefore return AXIS_SUCCESS
    if (!sConfPath || (sConfPath == '\0'))
    {
        return AXIS_SUCCESS;
    }

    strcpy (sNewConfPath, sConfPath);
    strcat (sNewConfPath, PLATFORM_CONFIG_PATH);
    
    // Even if axiscpp.conf does not exist in AXISCPP_DEPLOY default values 
    // will be used. Therefore return AXIS_SUCCESS
    if (AXIS_SUCCESS != fileConfig.fileOpen (sNewConfPath, "r"))
    {
        printf ("Warning - The configuration file was not found (%s).\n", sNewConfPath);
        printf("Using default values\n");
        return AXIS_SUCCESS;
    }

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
