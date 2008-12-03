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
 * @file AxisCPPConfigDefaultsImpl.hpp
 *
 * @author John Kelly (john_kelly@uk.ibm.com)
 *
 */
 
#if !defined(__AXIS_AXISCPPCONFIGDEFAULTSIMPL_H_OF_AXIS_INCLUDED__)
#define __AXIS_AXISCPPCONFIGDEFAULTSIMPL_H_OF_AXIS_INCLUDED__

#include <axis/GDefine.hpp>
#include <string>
/**
 *   @class AxisCPPConfigDefaultsImpl
 *   @brief class for programmatically setting configuration parameters.
 *   
 *   To be completed
 * 
 *   @author John Kelly (john_kelly@uk.ibm.com)
 */

AXIS_CPP_NAMESPACE_START

class STORAGE_CLASS_INFO AxisCPPConfigDefaultsImpl
{
    public:
    AxisCPPConfigDefaultsImpl();
    ~AxisCPPConfigDefaultsImpl();
 
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

    private:         
        std::string m_pcClientLog;
        std::string m_pcClientWSDDFile;
        std::string m_pcXMLParserLibrary;
        std::string m_pcHTTPTransportLibrary;
        std::string m_pcHTTPChannelLibrary;
        std::string m_pcHTTPSSLChannelLibrary;
        std::string m_pcNodeName;
        std::string m_pcListenPort;
        std::string m_pcSecureInfo;
        std::string m_pcAxisHome;

};

AXIS_CPP_NAMESPACE_END

#endif

