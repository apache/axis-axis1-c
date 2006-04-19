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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED TO THE        */
/* C-EQUIVALENT HEADER FILE IN SUPPORT OF THE C-BINDING INTERFACES.   */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
 
 
#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4530)
#endif

#if !defined(__GDEFINE_OF_AXIS_INCLUDED__)
#define __GDEFINE_OF_AXIS_INCLUDED__

/**
 * @file GDefine.hpp
 *  
 * This file contains all global definitions that are valid across whole
 * Axis C++ project.
 */

#define AXIS_CPP_NAMESPACE_START namespace axiscpp {
#define AXIS_CPP_NAMESPACE_END }
/*
The following is necessary for the skeletons and stubs to be built
*/
namespace axiscpp {}

#define AXIS_CPP_NAMESPACE_USE using namespace axiscpp;
#define AXIS_CPP_NAMESPACE_PREFIX axiscpp::

AXIS_CPP_NAMESPACE_START

/**
 * @enum AXIS_GLOBAL_ERROR
 * Enumeration of global error codes used by the Axis C++ engine.
 */
typedef enum 
{ 
    /**
     * Success
     */
    AXIS_SUCCESS=0,
    
    /**
     * Failure
     */
    AXIS_FAIL = -1, 
    
    /**
     * Object already exists
     */
    AXIS_OBJECT_ALREADY_EXISTS=1,
    
    /**
     * A matching handler does not exist
     */
    AXIS_NO_SUCH_HANDLER,
    
    /**
     * A matching service does not exist
     */
    AXIS_NO_SUCH_SERVICE,
    
    /**
     * No SOAP header blocks remaining
     */
    AXIS_NO_REMAINING_SOAP_HEADERS
} AXIS_GLOBAL_ERROR;

/**
 * @enum AXIS_PROTOCOL_TYPE
 * Enumeration of transport protocols.
 */
typedef enum 
{ 
    /**
     * Unknown
     */
    APT_UNKNOWN = -1,
    
    /**
     * HTTP 1.0
     */
    APTHTTP1_0=0,
    
    /**
     * HTTP 1.1
     */
    APTHTTP1_1,
    
    /**
     * FTP
     */
    APTFTP,
    
    /**
     * SMTP
     */
    APTSMTP,
    
    /**
     * HTTPS
     */
    APTHTTPS,
    
    /**
     * Other
     */
    APTOTHER
} AXIS_PROTOCOL_TYPE;

/**
 * @enum AXIS_TRANSPORT_INFORMATION_TYPE
 * Enumeration of the different information types used by the transport.
 */
typedef enum 
{
    /**
     * SoapAction header field
     */
    SOAPACTION_HEADER,
    
    /**
     * URI to service
     */
    SERVICE_URI,
    
    /**
     * Name of operation on service
     */
    OPERATION_NAME,
    
    /**
     * Length of SOAP message
     */
    SOAP_MESSAGE_LENGTH,
    
    /**
     * Generic transport properties
     */
    TRANSPORT_PROPERTIES,
    
    /**
     * Properties for secure transport
     */
    SECURE_PROPERTIES,
    
    /**
     * Name of transport library
     */
    DLL_NAME,
    
    /**
     * Name of SSL channel library
     */
    CHANNEL_HTTP_SSL_DLL_NAME = DLL_NAME,
    
    /**
     * Name of non-SSL channel library
     */
    CHANNEL_HTTP_DLL_NAME,
   
    /**
     * Content type
     */
    CONTENT_TYPE
} AXIS_TRANSPORT_INFORMATION_TYPE;

#define SOAPACTIONHEADER "SOAPAction"

#define AxisChar char
#define AxisXMLCh char
#define XML_Ch AxisChar
#define AxisString std::basic_string<char>
#define AxisXMLString std::basic_string<AxisXMLCh>

#ifdef WIN32
    #define AxisSprintf(X, Y, Z, W) sprintf(X, Z, W)
#else /* linux */
    #define AxisSprintf(X, Y, Z, W) sprintf(X, Z, W)
#endif

#if defined(WIN32) 
#define STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define STORAGE_CLASS_INFO 
#endif

#if defined(__GNUC__)
/*replaced stdcall with cdecl to make it work on some platforms with older libraries - Samisa*/
/*#define AXISCALL __attribute__((stdcall))*/
#define AXISCALL __attribute__((cdecl))
#else /* unix or win32 */
#if defined(__unix)
#define AXISCALL
#else
#define AXISCALL __stdcall
#endif
#endif

/*
 * Following macro define an API function of Axis C++
 * Format of the AXISAPI macro is as follows
 * AXISAPI(<METHOD NAME>, <PARAMETER LIST>)
 */

#define AXISAPI(M, P) AXISCALL M P = 0;
#define APIHASPARAMS
#define APINOPARAMS 

AXIS_CPP_NAMESPACE_END
#endif 


