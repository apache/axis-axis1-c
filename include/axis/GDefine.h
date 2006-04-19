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

#if !defined(__GDEFINEC_H_OF_AXIS_INCLUDED__)
#define __GDEFINEC_H_OF_AXIS_INCLUDED__

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE APIS.                                    */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
  extern "C" {
#endif

/*
 * @file GDefine.h
 *  
 * This file contains all global definitions that are valid across whole
 * Axis C++ project.
 */
typedef enum 
{ 
    /**
     * Success
     */
    AXISC_SUCCESS=0,
    
    /**
     * Failure
     */
    AXISC_FAIL = -1, 
    
    /**
     * Object already exists
     */
    AXISC_OBJECT_ALREADY_EXISTS=1,
    
    /**
     * A matching handler does not exist
     */
    AXISC_NO_SUCH_HANDLER,
    
    /**
     * A matching service does not exist
     */
    AXISC_NO_SUCH_SERVICE,
    
    /**
     * No SOAP header blocks remaining
     */
    AXISC_NO_REMAINING_SOAP_HEADERS
} AXISC_GLOBAL_ERROR;

/**
 * @enum AXIS_PROTOCOL_TYPE
 * Enumeration of transport protocols.
 */
typedef enum 
{ 
    /**
     * Unknown
     */
    AXISC_APT_UNKNOWN = -1,
    
    /**
     * HTTP 1.0
     */
    AXISC_APTHTTP1_0=0,
    
    /**
     * HTTP 1.1
     */
    AXISC_APTHTTP1_1,
    
    /**
     * FTP
     */
    AXISC_APTFTP,
    
    /**
     * SMTP
     */
    AXISC_APTSMTP,
    
    /**
     * HTTPS
     */
    AXISC_APTHTTPS,
    
    /**
     * Other
     */
    AXISC_APTOTHER
} AXISC_PROTOCOL_TYPE;

/**
 * @enum AXIS_TRANSPORT_INFORMATION_TYPE
 * Enumeration of the different information types used by the transport.
 */
typedef enum 
{
    /**
     * SoapAction header field
     */
    AXISC_SOAPACTION_HEADER,
    
    /**
     * URI to service
     */
    AXISC_SERVICE_URI,
    
    /**
     * Name of operation on service
     */
    AXISC_OPERATION_NAME,
    
    /**
     * Length of SOAP message
     */
    AXISC_SOAP_MESSAGE_LENGTH,
    
    /**
     * Generic transport properties
     */
    AXISC_TRANSPORT_PROPERTIES,
    
    /**
     * Properties for secure transport
     */
    AXISC_SECURE_PROPERTIES,
    
    /**
     * Name of transport library
     */
    AXISC_DLL_NAME,
    
    /**
     * Name of SSL channel library
     */
    AXISC_CHANNEL_HTTP_SSL_DLL_NAME = AXISC_DLL_NAME,
    
    /**
     * Name of non-SSL channel library
     */
    AXISC_CHANNEL_HTTP_DLL_NAME,
   
    /**
     * Content type
     */
    AXISC_CONTENT_TYPE
} AXISC_TRANSPORT_INFORMATION_TYPE;

#define AXISC_SOAPACTIONHEADER "SOAPAction"

#define AxiscChar char
#define AxiscXMLCh char

#if defined(WIN32) 
#define AXISC_STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define AXISC_STORAGE_CLASS_INFO 
#endif

#if defined(__GNUC__)
#define AXISCCALL __attribute__((cdecl))
#else /* unix or win32 */
#if defined(__unix)
#define AXISCCALL
#else
#define AXISCCALL __stdcall
#endif
#endif

typedef int AxiscBool;
typedef void* AXISCHANDLE;

#ifdef __cplusplus
  }
#endif

#endif 


