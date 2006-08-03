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
/**
 * @file ISoapFault.hpp
 *
 *
 */
#ifndef ISOAPFAULT_INCLUDED
#define ISOAPFAULT_INCLUDED

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

/**
 *  @class ISoapFault
 *  @brief Interface to represent SoapFault
 */
/**
 * Destructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapFaultDestroy(AXISCHANDLE soapFault);

/**
 * When a complex fault arrives this method can be used to
 * get the name of that fault. This is useful because once
 * we have the fault name we can pass the information necessary
 * to deserialize it, back to the SoapFault class.
 *
 * @return name of the complex fault
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultGetCmplxFaultObjectName(AXISCHANDLE soapFault);

/**
 * Once we know the complex fault name we can pass the information such as the
 * knowledge to deserialize the complex fault by calling this method.
 *
 * @param pDZFunct deserialize callback function pointer
 * @param pCreFunct create callback function
 * @param pDelFunct delete callback function
 * @param pName name
 * @param pNamespace url
 */
AXISC_STORAGE_CLASS_INFO
void * axiscSoapFaultGetCmplxFaultObject(AXISCHANDLE soapFault, void * pDZFunct, 
	void * pCreFunct, 
	void * pDelFunct, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/**
 * To retrieve a simple fault detail string
 *
 * @return Simple fault detail
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultGetSimpleFaultDetail(AXISCHANDLE soapFault);

/**
 * To retrieve the soap fault code
 *
 * @return fault code
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultGetFaultcode(AXISCHANDLE soapFault);

/**
 * To retrieve the soap fault string
 *
 * @return fault string
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultGetFaultstring(AXISCHANDLE soapFault);

/**
 * To retrieve the soap fault actor
 *
 * @return fault actor
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapFaultGetFaultactor(AXISCHANDLE soapFault);

/**
 * To set the soap fault code
 *
 * @param sFaultcode fault code
 * @return status
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapFaultSetFaultcode(AXISCHANDLE soapFault, const AxiscChar * sFaultcode);

/**
 * To set the soap fault string
 *
 * @param sFaultstring fault string
 * @return status
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapFaultSetFaultstring(AXISCHANDLE soapFault, const AxiscChar * sFaultstring);

/**
 * To set the soap fault actor
 *
 * @param sFaultactor fault actor
 * @return status
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapFaultSetFaultactor(AXISCHANDLE soapFault, const AxiscChar * sFaultactor);

/**
 * To set the soap fault detail for simple text detail
 *
 * @param sFaultdetail detail
 * @return status
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapFaultSetFaultDetail(AXISCHANDLE soapFault, const AxiscChar * sFaultdetail);

/**
 * To set the soap fault detail for complex detail
 *
 * @param pCmplxFaultObject detail
 * @return status
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapFaultSetCmplxFaultObject(AXISCHANDLE soapFault, const void * pCmplxFaultObject);


#ifdef __cplusplus
 }
#endif

#endif /* ISOAPFAULT_INCLUDED */
