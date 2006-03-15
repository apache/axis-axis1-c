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
 */

 /**
 * @file AxisConfig.h
 *
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 *
 */
 
#if !defined(__AXIS_AXISCONFIG_H_OF_AXIS_INCLUDED__)
#define __AXIS_AXISCONFIG_H_OF_AXIS_INCLUDED__

#define CONFBUFFSIZE						256
#define AXCONF_WSDDFILEPATH_TAGNAME			"WSDDFilePath"
#define AXCONF_LOGPATH_TAGNAME				"LogPath"
#define AXCONF_CLIENTLOGPATH_TAGNAME		"ClientLogPath"
#define AXCONF_CLIENTWSDDFILEPATH_TAGNAME	"ClientWSDDFilePath"
#define AXCONF_TRANSPORTHTTP_TAGNAME		"Transport_http"
#define AXCONF_SSLCHANNEL_HTTP_TAGNAME		"Channel_HTTP_SSL"
#define AXCONF_CHANNEL_HTTP_TAGNAME			"Channel_HTTP"
#define AXCONF_TRANSPORTSMTP_TAGNAME		"Transport_smtp"
#define AXCONF_XMLPARSER_TAGNAME			"XMLParser"
#define AXCONF_NODENAME_TAGNAME				"NodeName"
#define AXCONF_LISTENPORT_TAGNAME			"ListenPort"
#define AXCONF_SECUREINFO_TAGNAME			"SecureInfo"

#include <axis/GDefine.hpp>
#include <string>
/**
 *   @class AxisConfig
 *   @brief class for taking configuration parameters.
 *   
 *   The purpose of this class is to provide a way so that
 *   the server takes the configuration path where the
 *   axiscpp.conf lies from the environment variable AXISCPP_DEPLOY.
 *   User has to set this variable pointing the path to axiscpp.conf file.
 *   This axiscpp.conf file contains all the configuration paths
 *   like wsdd configuration file path, axis log path etc.
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */

enum g_axconfig 
{
	AXCONF_WSDDFILEPATH=0, 
	AXCONF_LOGPATH, 
	AXCONF_CLIENTLOGPATH, 
	AXCONF_CLIENTWSDDFILEPATH, 
	AXCONF_AXISHOME, 
	AXCONF_TRANSPORTHTTP, 
	AXCONF_TRANSPORTSMTP, 
	AXCONF_XMLPARSER,
	AXCONF_NODENAME,
	AXCONF_LISTENPORT,
	AXCONF_SSLCHANNEL_HTTP,
	AXCONF_CHANNEL_HTTP,
	AXCONF_SECUREINFO,
	AXCONF_LAST
};

AXIS_CPP_NAMESPACE_START

class AxisConfig
{
    public:
    AxisConfig();
//    AxisConfig( bool bDefaultsOnly);
    AxisConfig( AxisConfig * pOrgAxisConfig);

    /**
     * This method will read from the configuration file called axiscpp.conf
     * which is located in a place defined by AXISCPP_DEPLOY environment variable. 
     *
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    int readConfFile();

    /**
     * This is called to get the value of a property as defined by the g_axconfig
	 * enumeration.
     * 
     * @return the requested value or NULL if the property is not set.
     */

	char* getAxisConfProperty(g_axconfig property);
    void setValue(int valuelength, g_axconfig valueindex, char* value);
        
    private:
		std::string m_pcKeyArray [AXCONF_LAST];
		std::string m_pcValueArray [AXCONF_LAST];
};

AXIS_CPP_NAMESPACE_END

#endif

