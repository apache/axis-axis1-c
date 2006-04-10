/*
 *   Copyright 2003-2006 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2006 All Rights Reserved
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
#ifndef TYPEMAPPING_INCLUDED
#define TYPEMAPPING_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#include <axis/GDefine.h>

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum XSDCTYPETag 
{ XSDC_UNKNOWN=1, XSDC_INT, XSDC_FLOAT, XSDC_STRING, XSDC_LONG, XSDC_SHORT, \
                XSDC_BYTE, XSDC_UNSIGNEDLONG, \
                XSDC_BOOLEAN, XSDC_UNSIGNEDINT, XSDC_UNSIGNEDSHORT, \
                XSDC_UNSIGNEDBYTE, \
                XSDC_DOUBLE, XSDC_DECIMAL, XSDC_DURATION, \
                XSDC_DATETIME, XSDC_TIME, XSDC_DATE, \
                XSDC_GYEARMONTH, XSDC_GYEAR, XSDC_GMONTHDAY, XSDC_GDAY, \
                XSDC_GMONTH, XSDC_HEXBINARY, \
                XSDC_BASE64BINARY, XSDC_ANYURI, XSDC_QNAME,  XSDC_NOTATION, \
                XSDC_INTEGER, \
                XSDC_ARRAY, C_USER_TYPE,  XSDC_NMTOKEN, XSDC_ANY, XSDC_NONNEGATIVEINTEGER, \
                XSDC_POSITIVEINTEGER, XSDC_NONPOSITIVEINTEGER, XSDC_NEGATIVEINTEGER, \
                XSDC_NORMALIZEDSTRING, XSDC_TOKEN, XSDC_LANGUAGE, XSDC_NAME, \
                XSDC_NCNAME, XSDC_ID, XSDC_IDREF, XSDC_IDREFS, XSDC_ENTITY, \
                XSDC_ENTITIES, XSDC_NMTOKENS, C_ATTACHMENT \
} AXISC_XSDTYPE;

/**
 *  @class TypeMapping
 *  @brief interface for the TypeMapping class.
 */
AXISC_STORAGE_CLASS_INFO AXISC_XSDTYPE axiscMap(const AxiscXMLCh * sType);
AXISC_STORAGE_CLASS_INFO void axiscInitializeTypeMapping();
AXISC_STORAGE_CLASS_INFO void axiscUninitialize();

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateTypeMapping();
AXISC_STORAGE_CLASS_INFO void axiscDestroyTypeMapping(AXISCHANDLE typeMapping);


#ifdef __cplusplus
 }
#endif

#endif /* TYPEMAPPING_INCLUDED */

