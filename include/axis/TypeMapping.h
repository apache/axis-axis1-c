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
{ XSDC__UNKNOWN=1, XSDC__INT, XSDC__FLOAT, XSDC__STRING, XSDC__LONG, XSDC__SHORT, \
                XSDC__BYTE, XSDC__UNSIGNEDLONG, \
                XSDC__BOOLEAN, XSDC__UNSIGNEDINT, XSDC__UNSIGNEDSHORT, \
                XSDC__UNSIGNEDBYTE, \
                XSDC__DOUBLE, XSDC__DECIMAL, XSDC__DURATION, \
                XSDC__DATETIME, XSDC__TIME, XSDC__DATE, \
                XSDC__GYEARMONTH, XSDC__GYEAR, XSDC__GMONTHDAY, XSDC__GDAY, \
                XSDC__GMONTH, XSDC__HEXBINARY, \
                XSDC__BASE64BINARY, XSDC__ANYURI, XSDC__QNAME,  XSDC__NOTATION, \
                XSDC__INTEGER, \
                XSDC__ARRAY, C_USER_TYPE,  XSDC__NMTOKEN, XSDC__ANY, XSDC__NONNEGATIVEINTEGER, \
                XSDC__POSITIVEINTEGER, XSDC__NONPOSITIVEINTEGER, XSDC__NEGATIVEINTEGER, \
                XSDC__NORMALIZEDSTRING, XSDC__TOKEN, XSDC__LANGUAGE, XSDC__NAME, \
                XSDC__NCNAME, XSDC__ID, XSDC__IDREF, XSDC__IDREFS, XSDC__ENTITY, \
                XSDC__ENTITIES, XSDC_NMTOKENS, C_ATTACHMENT \
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

