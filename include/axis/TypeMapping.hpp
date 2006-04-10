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
#endif

#if !defined(_TYPEMAPPING_H____OF_AXIS_INCLUDED_)
#define _TYPEMAPPING_H____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <map>
#include <string>

AXIS_CPP_NAMESPACE_START
using namespace std;

typedef enum XSDTYPETag 
{ XSD_UNKNOWN=1, XSD_INT, XSD_FLOAT, XSD_STRING, XSD_LONG, XSD_SHORT, \
                XSD_BYTE, XSD_UNSIGNEDLONG, \
                XSD_BOOLEAN, XSD_UNSIGNEDINT, XSD_UNSIGNEDSHORT, \
                XSD_UNSIGNEDBYTE, \
                XSD_DOUBLE, XSD_DECIMAL, XSD_DURATION, \
                XSD_DATETIME, XSD_TIME, XSD_DATE, \
                XSD_GYEARMONTH, XSD_GYEAR, XSD_GMONTHDAY, XSD_GDAY, \
                XSD_GMONTH, XSD_HEXBINARY, \
                XSD_BASE64BINARY, XSD_ANYURI, XSD_QNAME,  XSD_NOTATION, \
                XSD_INTEGER, \
                XSD_ARRAY, USER_TYPE,  XSD_NMTOKEN, XSD_ANY, XSD_NONNEGATIVEINTEGER, \
                XSD_POSITIVEINTEGER, XSD_NONPOSITIVEINTEGER, XSD_NEGATIVEINTEGER, \
                XSD_NORMALIZEDSTRING, XSD_TOKEN, XSD_LANGUAGE, XSD_NAME, \
                XSD_NCNAME, XSD_ID, XSD_IDREF, XSD_IDREFS, XSD_ENTITY, \
                XSD_ENTITIES, XSD_NMTOKENS, ATTACHMENT \
} XSDTYPE;

/**
 * REMOVED from XSDTYPETag-> ACCESSOR, XSD_NCNAME,
 */
/**
 *  @class TypeMapping
 *  @brief interface for the TypeMapping class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com)
 */

class TypeMapping  
{
public:
    static XSDTYPE map(const AxisXMLCh* sType);
    static void initialize();
	static void uninitialize();

#if (defined(AIX) || (defined(_MSC_VER) && _MSC_VER >= 1300) || defined( __OS400__ ) || defined(__sun))
	static std::map<std::string, XSDTYPE> m_sTypeMap;
#else
	static std::map<const std::string, XSDTYPE> m_sTypeMap;
#endif
    static volatile bool m_bInit;
    TypeMapping();
    virtual ~TypeMapping();

};

AXIS_CPP_NAMESPACE_END

#endif
