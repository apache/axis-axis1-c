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
 */
#ifndef SOAPFAULTEXCEPTION_INCLUDED
#define SOAPFAULTEXCEPTION_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif


#include <axis/GDefine.h>
#include <axis/AxisException.h>

/**
 * @file SoapFaultException.hpp
 */
/**
 * @class SoapFaultException
 * @brief Superclass of all user-defined soap faults defined in the WSDL
 *
 * SoapFaultException is the superclass of all user faults that are defined
 * in the WSDL. This enables a client application to catch all soap faults
 * in a single catch block. To catch a specific soap fault, a client
 * application should catch the class that represents the fault's complex
 * type. SoapFaultException is a simple class that encapsulates the fault
 * information and does not reference the SoapFault itself. This means it
 * can clean it's own storage in its destructor so the client application
 * doesn't have to.
 *
 */


/**
 * SoapFaultException constructor
 *
 * @param code is the SOAP faultcode
 * @param string is the SOAP faultstring
 * @param actor is the SOAP faultactor
 * @param exceptionCode is the axis exception code
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscSoapFaultExceptionCreate(const AxiscChar * code, 
	const AxiscChar * string, 
	const AxiscChar * actor, 
	int exceptionCode);

/**
 * Destructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapFaultExceptionDestroy(AXISCHANDLE soapFaultException);

/**
 * Returns the SOAP faultcode
 *
 * @return faultCode
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultExceptionGetFaultCode(AXISCHANDLE soapFaultException);

/**
 * Returns the SOAP faultstring
 *
 * @return faultString
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultExceptionGetFaultString(AXISCHANDLE soapFaultException);

/**
 * Returns the SOAP faultactor
 *
 * @return faultActor
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultExceptionGetFaultActor(AXISCHANDLE soapFaultException);

/**
 * Set the SOAP faultcode
 *
 * @param code is the SOAP faultcode
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapFaultExceptionSetFaultCode(AXISCHANDLE soapFaultException, const AxiscChar * code);

/**
 * Set the SOAP faultstring
 *
 * @param string is the SOAP faultstring
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapFaultExceptionSetFaultString(AXISCHANDLE soapFaultException, const AxiscChar * string);

/**
 * Set the SOAP faultactor
 *
 * @param actor is the SOAP faultactor
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapFaultExceptionSetFaultActor(AXISCHANDLE soapFaultException, const AxiscChar * actor);



#ifdef __cplusplus
 }
#endif

#endif /* SOAPFAULTEXCEPTION_INCLUDED */
