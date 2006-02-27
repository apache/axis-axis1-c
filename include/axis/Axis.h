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

#ifdef __cplusplus
  extern "C" {
#endif

#include <axis/GDefine.h>
#include <axis/TypeMapping.h>

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
void axiscInitializeAxis(AxiscBool bIsServer);

/** 
  * Terminates the Axis runtime. 
  * @return AXISC_SUCCESS or AXISC_FAIL to indicate success or fail
  */
AXISC_STORAGE_CLASS_INFO 
void axiscTerminate();

/**
  * Deletes storage allocated by the Axis engine, that is no longer required
  * by the customer application.
  * 
  * @param pValue
  * @param type The XSDTYPE of the storage item to be deleted.
  * @return AXISC_SUCCESS or AXISC_FAIL to indicate success or fail
  */
AXISC_STORAGE_CLASS_INFO 
void axiscAxisDelete(void * pValue, AXISC_XSDTYPE type);

#ifdef __cplusplus
  }
#endif


#endif
 