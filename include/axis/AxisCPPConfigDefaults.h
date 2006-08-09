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
 *
 */
#ifndef AXISCPPCONFIGDEFAULTS_INCLUDED
#define AXISCPPCONFIGDEFAULTS_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/*                                                                    */
/* THIS FILE GENERATED BY CBINDINGGENERATOR TOOL.                     */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif


#include <axis/GDefine.h>

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
 */

/*
 * Class definition.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscConfigDefaultsCreate();

AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsDestroy(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the location of the client log file.  This is the programmatic equivalent of
 * reading the ClientLogPath parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a client.
 *
 * @return location of the client log file.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetClientLog(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the location of the client WSDD file.  This is the programmatic equivalent of
 * reading the ClientWSDDFilePath parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a client.
 *
 * @return location of the client WSDD file.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetClientWSDDFile(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the value for the XML Parser library name.  This is the programmatic equivalent of
 * reading the XMLParser parameter in the axiscpp.conf configuration file.
 *
 * @return name of the XML Parser library.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetXMLParserLibrary(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the value for the HTTP transport library name.  This is the programmatic equivalent of
 * reading the Transport_http parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a client.
 *
 * @return name of the HTTP Transport library.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetHTTPTransportLibrary(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the value for the HTTP channel library name.  This is the programmatic equivalent of
 * reading the Channel_HTTP parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a client.
 *
 * @return name of the HTTP Channel library.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetHTTPChannelLibrary(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the value for the HTTP SSL channel library name.  This is the programmatic equivalent of
 * reading the Channel_HTTP_SSL parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a client.
 *
 * @return name of the HTTP SSL Channel library.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetHTTPSSLChannelLibrary(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the value for NodeName.  This is the programmatic equivalent of
 * reading the NodeName parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a server.
 *
 * @return nodeName to be set.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetNodeName(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the value for ListenPort.  This is the programmatic equivalent of
 * reading the ListenPort parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a server.
 *
 * @return listenPort to be set.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetListenPort(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the value for SecureInfo.  This is the programmatic equivalent of
 * reading the SecureInfo parameter in the axiscpp.conf configuration file.
 *
 * This parameter is only used when Axis is operating as a client.
 *
 * @return secureInfo to be set.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetSecureInfo(AXISCHANDLE axisCPPConfigDefaults);

/**
 * Get the location of AxisHome.  This is the programmatic equivalent of
 * using the environment variable AXISCPP_DEPLOY.
 *
 * @return location of AxisHome.
 */
AXISC_STORAGE_CLASS_INFO
char * axiscConfigDefaultsGetAxisHome(AXISCHANDLE axisCPPConfigDefaults);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetClientLog(AXISCHANDLE axisCPPConfigDefaults, char * location);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetClientWSDDFile(AXISCHANDLE axisCPPConfigDefaults, char * location);

/**
 * Set the value for the XML Parser library name.  This is the programmatic equivalent of
 * setting the XMLParser parameter in the axiscpp.conf configuration file.
 *
 * If this parameter has been set in the axiscpp.conf configuration file
 * this value will be ignored.
 *
 * @param name of the XML Parser library.
 */
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetXMLParserLibrary(AXISCHANDLE axisCPPConfigDefaults, char * name);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetHTTPTransportLibrary(AXISCHANDLE axisCPPConfigDefaults, char * name);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetHTTPChannelLibrary(AXISCHANDLE axisCPPConfigDefaults, char * name);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetHTTPSSLChannelLibrary(AXISCHANDLE axisCPPConfigDefaults, char * name);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetNodeName(AXISCHANDLE axisCPPConfigDefaults, char * nodeName);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetListenPort(AXISCHANDLE axisCPPConfigDefaults, char * listenPort);

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
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetSecureInfo(AXISCHANDLE axisCPPConfigDefaults, char * secureInfo);

/**
 * Set the location of AxisHome.  This is the programmatic equivalent of
 * setting the environment variable AXISCPP_DEPLOY.
 *
 * If the environment variable AXISCPP_DEPLOY has been set this value
 * will be ignored.
 *
 * @param location of axis home.
 */
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsSetAxisHome(AXISCHANDLE axisCPPConfigDefaults, char * location);

/**
 * Apply the set configuration values.
 *
 * This takes any values that have been set and applies as the Axis C++
 * defaults for this process, it is not possible to then re-apply.
 *
 * @throw AxisException if the configuration defaults have already been set.
 */
AXISC_STORAGE_CLASS_INFO
void axiscConfigDefaultsApply(AXISCHANDLE axisCPPConfigDefaults);


#ifdef __cplusplus
 }
#endif

#endif /* AXISCPPCONFIGDEFAULTS_INCLUDED */