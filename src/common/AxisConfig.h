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
 */

 /**
 * @file AxisConfig.h
 *
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 *
 */
 
#if !defined(__AXIS_AXISCONFIG_H_OF_AXIS_INCLUDED__)
#define __AXIS_AXISCONFIG_H_OF_AXIS_INCLUDED__

#define CONFBUFFSIZE 256
#include <axis/GDefine.hpp>
#include <string>
/**
 *   @class AxisConfig
 *   @brief class for taking configuration parameters.
 *   
 *   The purpose of this class is to provide a way so that
 *   the server takes the configuration path where the
 *   axiscpp.conf lies from the environment variable AXIS_HOME.
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
	AXCONF_LAST
};

AXIS_CPP_NAMESPACE_START

class AxisConfig
{
    public:
    AxisConfig();

    /**
     * This method will read from the configuration file called axiscpp.conf
     * which is located in a place defined by AXIS_HOME environment variable. 
     *
     * @return The status which indicates whether the operation is success 
     * (AXIS_SUCCESS) or not (AXIS_FAIL).
     */
    int readConfFile();

    /**
     * This is called to get the value of a property as defined by the g_axconfig
	 * enumeration.
     * 
     * @return the $AXIS_HOME value
     */

	char* getAxisConfProperty(g_axconfig property);
        
    private:         
		std::string m_pcKeyArray [AXCONF_LAST];
		std::string m_pcValueArray [AXCONF_LAST];

		void setValue(int valuelength, g_axconfig valueindex, char* value);

		void OutputConfigInfo();

};

AXIS_CPP_NAMESPACE_END

#endif

