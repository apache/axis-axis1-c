/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 * (c) Copyright IBM Corp. 2004, 2006 All Rights Reserved
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
 *
 */
#ifndef AXIS_INCLUDED
#define AXIS_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE APIS.                                    */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


#include <axis/GDefine.h>
#include <axis/TypeMapping.h>

#ifdef __cplusplus
  extern "C" {
#endif

/**
 *
 * Contains methods to initialize and terminate the Axis runtime. Creating a stub also initializes
 * the Axis runtime and deleting the stub terminates it. So simple applications that only ever
 * use one stub at a time do not need to call these methods. More complicated applications that 
 * initialize multiple stubs, use them and delete them later, should initialize Axis at the start
 * of their application using axiscInitializeAxis and terminate Axis at the very end of their 
 * application with axiscTerminate. Applications that use Axis in multiple threads should also 
 * call axiscInitializeAxis and axiscTerminate.
 */
 
/**
  * Initializes the Axis runtime.
  * @param bIsServer should be set to false for client applications.
  * @return AXISC_SUCCESS or AXISC_FAIL to indicate success or fail
  */
AXISC_STORAGE_CLASS_INFO 
int axiscInitializeAxis(AxiscBool bIsServer);

/** 
  * Terminates the Axis runtime. 
  * @return AXISC_SUCCESS or AXISC_FAIL to indicate success or fail
  */
AXISC_STORAGE_CLASS_INFO 
int axiscTerminate();

/**
  * Deletes storage allocated by the Axis engine, that is no longer required
  * by the customer application.
  * 
  * @param pValue
  * @param type The XSDTYPE of the storage item to be deleted.
  * @return AXISC_SUCCESS or AXISC_FAIL to indicate success or fail
  */
AXISC_STORAGE_CLASS_INFO 
int axiscAxisDelete(void * pValue, AXISC_XSDTYPE type);

/**
  * Allocates storage to be used by Axis engine.  All proxy code and allocated
  * storage required by the client for basic types must use this 
  * function in order that it may be freed by proxy code or the Axis engine.
  * 
  * @param size - size of storage to be allocated
  * @return pointer to allocated storage
  */
AXISC_STORAGE_CLASS_INFO 
void * axiscAxisNew(AXISC_XSDTYPE type, int size);

/**
  * Registers a function that will be invoked to handle Axis engine
  * exceptions.  The function will be called with two parameters, 
  * the error code and the error message, if any. 
  * 
  * @param fp - pointer to exception handler function.
  */
  
typedef void (* AXIS_EXCEPTION_HANDLER_FUNCT)(int errorCode, const char *errorString);

AXISC_STORAGE_CLASS_INFO 
void axiscRegisterExceptionHandler(AXIS_EXCEPTION_HANDLER_FUNCT);

/**
  * Invokes the registered exception handler. If an exception handler was not
  * registered, the errorCode and errorString are printed to stderr. 
  * 
  * @param errorCode - error code.
  * @param errorString - error string.
  */

AXISC_STORAGE_CLASS_INFO 
void axiscInvokeExceptionHandler(int errorCode, const char *errorString);

#ifdef __cplusplus
  }
#endif


#endif
 