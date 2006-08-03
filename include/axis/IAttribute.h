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
 * @file IAttribute.hpp
 *
 *
 */
#ifndef IATTRIBUTE_INCLUDED
#define IATTRIBUTE_INCLUDED

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
 *   @class IAttribute
 *   @brief interface for the IAttribute class.
 *
 *
 */
AXISC_STORAGE_CLASS_INFO
void axiscAttributeDestroy(AXISCHANDLE attribute);

/**
 * Get the value of this attribute
 * @return The value of this attribute
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscAttributeGetValue(AXISCHANDLE attribute);

/**
 * Get the URI of this attribute
 * @return The URI of this attribute
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscAttributeGetURI(AXISCHANDLE attribute);

/**
 * Get the prefix of this attribute
 * @return The prefix of this attribute
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscAttributeGetPrefix(AXISCHANDLE attribute);

/**
 * Get the local name of this attribute
 * @return The local name of this attribute
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscAttributeGetLocalName(AXISCHANDLE attribute);

/**
 * try to set theattribute with given value
 * @param value to set
 * @return AXIS_SUCCESS if succeeded, AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_SUCCESS
 */
AXISC_STORAGE_CLASS_INFO
int axiscAttributeSetValue(AXISCHANDLE attribute, const AxiscChar * value);

/**
 * try to set the URI
 * @param uri to set
 * @return AXIS_SUCCESS if succeeded, AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_SUCCESS
 */
AXISC_STORAGE_CLASS_INFO
int axiscAttributeSetURI(AXISCHANDLE attribute, const AxiscChar * uri);

/**
 * try to set the prefix with given value
 * @param prefix to set
 * @return AXIS_SUCCESS if succeeded, AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_SUCCESS
 */
AXISC_STORAGE_CLASS_INFO
int axiscAttributeSetPrefix(AXISCHANDLE attribute, const AxiscChar * prefix);

/**
 * try to set the attribute with given value
 * @param localname to be set
 * @return AXIS_SUCCESS if succeeded, AXIS_FAIL otherwise. NOTE: Passing NULL will result in a AXIS_SUCCESS
 */
AXISC_STORAGE_CLASS_INFO
int axiscAttributeSetLocalName(AXISCHANDLE attribute, const AxiscChar * localname);


#ifdef __cplusplus
 }
#endif

#endif /* IATTRIBUTE_INCLUDED */
