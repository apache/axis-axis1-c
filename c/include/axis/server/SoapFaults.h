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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *
 */


#ifndef __SOAPFAULTS_H_OF_AXIS_INCLUDED___
#define __SOAPFAULTS_H_OF_AXIS_INCLUDED___

/*
 * The structure which is used as a container for soap faults.
 */
struct SoapFaultStruct
{
    const char* pchFaultcode;
    const char* pchFaultstring;
    const char* pchFaultactor;
    const char* pchDetail;
    
};

/*
 * The following enumeration is used to serve the Axis C++ codes for 
 * soap faults.
 */
enum SOAP_FAULTS 
{
    /* VersionMismatch faults */
    SF_VERSION_MISMATCH,
    
    /* MustUnderstand faults */
    SF_MUST_UNDERSTAND,

    /* Client faults */
    SF_MESSAGEINCOMPLETE,
    SF_SOAPACTIONEMPTY,
    SF_SERVICENOTFOUND,
    SF_SOAPCONTENTERROR,
    SF_NOSOAPMETHOD,
    SF_METHODNOTALLOWED,
    SF_PARATYPEMISMATCH,
    SF_CLIENTHANDLERFAILED,

    /* Server faults */
    SF_COULDNOTLOADSRV,
    SF_COULDNOTLOADHDL,
    SF_HANDLERFAILED,
    SF_WEBSERVICEFAILED,

    /*
     * This FAULT_LAST is not used as a fault code, but instead is used 
     * internaly in the code. Developers should not use this as a fault 
     * code.
     */
    FAULT_LAST
};

/*
 * The following array of structure is used to store all the soap faults
 * which are used in Axis C++. Each time a fault object is needed it is
 * created using this array, in SoapFault class.
 */
static SoapFaultStruct g_sObjSoapFaultStruct[FAULT_LAST] = 
                        {
/*VersionMismatch faults */
    /*SF_VERSION_MISMATCH*/    {"VersionMismatch", 
    "Soap Version Mismatch error", "none", ""},

/*MustUnderstand faults */
    /*SF_MUST_UNDERSTAND*/    {"MustUnderstand", "Soap Must Understand  error",
    "none", ""},

/*Client faults */
    /*SF_MESSAGEINCOMPLETE*/{"Client", 
    "Soap message is incorrect or incomplete", "none", ""},
    /*SF_SOAPACTIONEMPTY*/    {"Client", "Soap Action header empty", 
    "none", ""},
    /*SF_SERVICENOTFOUND*/    {"Client", 
    "Requested service is not registerd at the server", "none", ""},
    /*SF_SOAPCONTENTERROR*/ {"Client", "Soap content is not valid", 
    "none", ""},
    /*SF_NOSOAPMETHOD*/        {"Client", "No method to invoke", "none", ""},
    /*SF_METHODNOTALLOWED*/    {"Client", 
    "Soap method is not allowed to invoke", "none", ""},
  /*SF_PARATYPEMISMATCH*/    {"Client", 
  "Parameter type mismatch", "none", ""},
  /*SF_CLIENTHANDLERFAILED*/{"Client", 
  "A client handler failed", "none", ""},

/*Server faults */
    /*SF_COULDNOTLOADSRV*/    {"Server", "Cannot load web service", 
    "none", ""},
    /*SF_COULDNOTLOADHDL*/    {"Server", "Cannot load service handlers", 
    "none", ""},
    /*SF_HANDLERFAILED*/    {"Server", "A service handler failed", 
    "none", ""},
    /*SF_WEBSERVICEFAILED*/    {"Server", "Webservice failed", "none", ""}
                        };        

#endif

