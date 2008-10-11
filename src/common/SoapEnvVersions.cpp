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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <axis/SoapEnvVersions.hpp>

AXIS_CPP_NAMESPACE_START

SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST]=
{
    /* SOAP_VER_1_1 */
    { 
        "http://schemas.xmlsoap.org/soap/envelope/",
        "SOAP-ENV",
        {
/*SKW_ENVELOPE*/        "Envelope",
/*SKW_HEADER*/            "Header",
/*SKW_BODY*/            "Body",
/*SKW_MUSTUNDERSTAND*/    "mustUnderstand",
/*SKW_ACTOR*/            "actor",
/*SKW_ENCODING_STYLE*/    "encodingStyle",
/*SKW_FAULT*/            "Fault",
/*SKW_FAULT_CODE*/        "faultcode",
/*SKW_FAULT_STRING*/    "faultstring",
/*SKW_FAULT_ACTOR*/        "faultactor",
/*SKW_DETAIL*/            "detail",
/*SKW_MULTIREF*/        "multiRef",

/*SKW_TYPE*/            "type",
/*SKW_ARRAYTYPE*/        "arrayType",
/*SKW_HREF*/            "href",
/*SKW_ID*/                "id"
        },
    },

    /*SOAP_VER_1_2*/
    { 
        "http://www.w3.org/2003/05/soap-envelope",
        "env",
        {
/*SKW_ENVELOPE*/        "Envelope",
/*SKW_HEADER*/            "Header",
/*SKW_BODY*/            "Body",
/*SKW_MUSTUNDERSTAND*/    "mustUnderstand",
/*SKW_ACTOR*/            "actor",
/*SKW_ENCODING_STYLE*/    "encodingStyle",
/*SKW_FAULT*/            "Fault",
/*SKW_FAULT_CODE*/        "Code",
/*SKW_FAULT_STRING*/    "Reason",
/*SKW_FAULT_ACTOR*/        "Role",
/*SKW_DETAIL*/            "Detail",
/*SKW_MULTIREF*/        "multiRef",

/*SKW_TYPE*/            "type",
/*SKW_ARRAYTYPE*/        "arrayType",
/*SKW_HREF*/            "href",
/*SKW_ID*/                "id"
        },
    }
};

AXIS_CPP_NAMESPACE_END
