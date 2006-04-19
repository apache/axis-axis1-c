/*
 *   Copyright 2005 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2005 All Rights Reserved
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
 * @file AxisCPPConfigDefaults.hpp
 *
 * @author John Kelly (john_kelly@uk.ibm.com)
 *
 */
 
#if !defined(__AXIS_AXISCPPCONFIGDEFAULTS_H_OF_AXIS_INCLUDED__)
#define __AXIS_AXISCPPCONFIGDEFAULTS_H_OF_AXIS_INCLUDED__

#include <axis/GDefine.hpp>
#include <string>
/**
 *   @class AxisCPPConfigDefaults
 *   @brief class for programmatically setting configuration defaults.
 *   
 *   AxisCPPConfigDefaults allows you to apply new configuration 
 *   defaults, prior to the instantiation of the first web service
 *   class in the application. These programmer-set defaults may be
 *   over-ridden by the external factors, such as..
 *    - the values in axiscpp.conf
 *    - the value of AXISCPP_DEPLOY
 * 
 *   The get/set methods don't have any effect on the ACTUAL defaults. They
 *   are mearly a bundle of values which are set on the ACTUAL defaults when
 *   the apply() method is issued.
 * 
 *   It consists of...
 *   (a) get/set methods for each of the values to be found
 *       in the configuration file, namely:
 *       - ClientLog
 *       - ClientWSDDFile
 *       - XMLParserLibrary
 *       - HTTPTransportLibrary
 *       - HTTPChannelLibrary
 *       - HTTPSSLChannelLibrary 
 *       - NodeName
 *       - ListenPort
 *       - SecureInfo
 *       When the first web-services class is instantiated any values set in the config 
 *       file would over-ride those set by this class.
 *   (b) get/set methods for AxisHome 
 *       This is the programmatic equivalent of the AXISCPP_DEPLOY
 *       environment variable.
 *       When the first class is instantiated, if AXISCPP_DEPLOY is set 
 *       it will over-ride the value set by this class.
 *   (c) The apply() method takes any values that have been set on the object
 *       and set them as the Axis CPP defaults for this process. 
 * 
 *   Exceptions thrown: AxisConfigException
 * 
 *       Once the first web service is instantiated, new defaults may no longer
 *       be applied. If this is attempted an AxisConfigException is thrown.
 * 
 *   Usage examples
 *   (a) Setting the location of the axiscpp.conf file to the 
 *      "current working directory"
 * 
 *      AxisCPPDefaultConfig defConfig;
 *      defConfig.setAxisHome(".");
 *      defConfig.apply();
 * 
 * 
 *   @author John Kelly (john_kelly@uk.ibm.com)
 */

AXIS_CPP_NAMESPACE_START

/*
 * Forward declarations.
 */

class AxisCPPConfigDefaultsImpl;

/*
 * Class definition.
 */

class STORAGE_CLASS_INFO AxisCPPConfigDefaults
{
    public:
        
        AxisCPPConfigDefaults();      
        ~AxisCPPConfigDefaults();
 
        /**
         * Get the location of the client log file.  This is the programmatic equivalent of
         * reading the ClientLogPath parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @return location of the client log file.
         */
        char* getClientLog();
        
        /**
         * Get the location of the client WSDD file.  This is the programmatic equivalent of
         * reading the ClientWSDDFilePath parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @return location of the client WSDD file.
         */
        char* getClientWSDDFile();
        
        /**
         * Get the value for the XML Parser library name.  This is the programmatic equivalent of
         * reading the XMLParser parameter in the axiscpp.conf configuration file.
         * 
         * @return name of the XML Parser library.
         */
        char* getXMLParserLibrary();

        /**
         * Get the value for the HTTP transport library name.  This is the programmatic equivalent of
         * reading the Transport_http parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @return name of the HTTP Transport library.
         */
        char* getHTTPTransportLibrary();

        /**
         * Get the value for the HTTP channel library name.  This is the programmatic equivalent of
         * reading the Channel_HTTP parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @return name of the HTTP Channel library.
         */
        char* getHTTPChannelLibrary();

        /**
         * Get the value for the HTTP SSL channel library name.  This is the programmatic equivalent of
         * reading the Channel_HTTP_SSL parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @return name of the HTTP SSL Channel library.
         */
        char* getHTTPSSLChannelLibrary(); 

        /**
         * Get the value for NodeName.  This is the programmatic equivalent of
         * reading the NodeName parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a server.
         * 
         * @return nodeName to be set.
         */
        char* getNodeName();

        /**
         * Get the value for ListenPort.  This is the programmatic equivalent of
         * reading the ListenPort parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a server.
         * 
         * @return listenPort to be set.
         */
        char* getListenPort();

        /**
         * Get the value for SecureInfo.  This is the programmatic equivalent of
         * reading the SecureInfo parameter in the axiscpp.conf configuration file.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @return secureInfo to be set.
         */
        char* getSecureInfo();
        
        /**
         * Get the location of AxisHome.  This is the programmatic equivalent of
         * using the environment variable AXISCPP_DEPLOY.
         * 
         * @return location of AxisHome.
         */
        char* getAxisHome();

        /**
         * Set the location of the client log file.  This is the programmatic equivalent of
         * setting the ClientLogPath parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @param location of the client log file.
         */
        void setClientLog(char* location);

        /**
         * Set the location of the client WSDD file.  This is the programmatic equivalent of
         * setting the ClientWSDDFilePath parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @param location of the client WSDD file.
         */
        void setClientWSDDFile(char* location);

        /**
         * Set the value for the XML Parser library name.  This is the programmatic equivalent of
         * setting the XMLParser parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * @param name of the XML Parser library.
         */
        void setXMLParserLibrary(char* name);
        
        /**
         * Set the value for the HTTP transport library name.  This is the programmatic equivalent of
         * setting the Transport_http parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @param name of the HTTP Transport library.
         */
        void setHTTPTransportLibrary(char* name);

        /**
         * Set the value for the HTTP channel library name.  This is the programmatic equivalent of
         * setting the Channel_HTTP parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @param name of the HTTP Channel library.
         */
        void setHTTPChannelLibrary(char* name);
        
        /**
         * Set the value for the HTTP SSL channel library name.  This is the programmatic equivalent of
         * setting the Channel_HTTP_SSL parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @param name of the HTTP SSL Channel library.
         */
        void setHTTPSSLChannelLibrary(char* name);

        /**
         * Set the value for NodeName.  This is the programmatic equivalent of
         * setting the NodeName parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a server.
         * 
         * @param nodeName to be set.
         */
        void setNodeName(char* nodeName);
        
        /**
         * Set the value for ListenPort.  This is the programmatic equivalent of
         * setting the ListenPort parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a server.
         * 
         * @param listenPort to be set.
         */
        void setListenPort(char* listenPort);
        
        /**
         * Set the value for SecureInfo.  This is the programmatic equivalent of
         * setting the SecureInfo parameter in the axiscpp.conf configuration file.
         * 
         * If this parameter has been set in the axiscpp.conf configuration file
         * this value will be ignored.
         * 
         * This parameter is only used when Axis is operating as a client.
         * 
         * @param secureInfo to be set.
         */
        void setSecureInfo(char* secureInfo);
        
        /**
         * Set the location of AxisHome.  This is the programmatic equivalent of
         * setting the environment variable AXISCPP_DEPLOY.
         * 
         * If the environment variable AXISCPP_DEPLOY has been set this value
         * will be ignored.
         * 
         * @param location of axis home.
         */
        void setAxisHome(char* location);

        /**
         * Apply the set configuration values.
         * 
         * This takes any values that have been set and applies as the Axis C++
         * defaults for this process, it is not possible to then re-apply.
         * 
         * @throw AxisException if the configuration defaults have already been set.
         */
        void apply();

    protected:
        /**
         * Axis C++ engine implementation
         */      
        AxisCPPConfigDefaultsImpl *m_pImpl;

};

AXIS_CPP_NAMESPACE_END

#endif

