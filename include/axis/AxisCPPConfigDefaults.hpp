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
 *       This is the programmatic equivaluent of the AXISCPP_DEPLOY
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
 
      char* getClientLog();
      char* getClientWSDDFile();
      char* getXMLParserLibrary();
      char* getHTTPTransportLibrary();
      char* getHTTPChannelLibrary();
      char* getHTTPSSLChannelLibrary(); 
      char* getNodeName();
      char* getListenPort();
      char* getSecureInfo();
      char* getAxisHome();
        
      void setClientLog(char*);
      void setClientWSDDFile(char*);
      void setXMLParserLibrary(char*);
      void setHTTPTransportLibrary(char*);
      void setHTTPChannelLibrary(char*);
      void setHTTPSSLChannelLibrary(char*);
      void setNodeName(char*);
      void setListenPort(char*);
      void setSecureInfo(char*);
      void setAxisHome(char*);                    

      void apply();                                

    protected:         
        AxisCPPConfigDefaultsImpl *m_pImpl;

};

AXIS_CPP_NAMESPACE_END

#endif

