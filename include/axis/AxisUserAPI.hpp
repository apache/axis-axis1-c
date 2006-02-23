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

#if !defined(_AXISUSERAPI_H____OF_AXIS_INCLUDED_)
#define _AXISUSERAPI_H____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <axis/TypeMapping.hpp>
#include <time.h>
#include <string.h>

AXIS_CPP_NAMESPACE_START

 /**
  * @file AxisUserAPI.hpp
  * This file contains types defined in Axis C++. The mapping of basic xsd types
  * to the C language types.
  * 
  * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
  */

/**
 * @typedef xsd__string
 * Axis C++ defined type for xml basic type string
 */
typedef AxisChar * xsd__string;
/**
 * @typedef xsd__normalizedString
 * Axis C++ defined type for xml basic type normalizedString
 */
typedef AxisChar * xsd__normalizedString;
/**
 * @typedef xsd__token
 * Axis C++ defined type for xml basic type token
 */
typedef AxisChar * xsd__token;
/**
 * @typedef xsd__language
 * Axis C++ defined type for xml basic type language
 */
typedef AxisChar * xsd__language;
/**
 * @typedef xsd__Name
 * Axis C++ defined type for xml basic type Name
 */
typedef AxisChar * xsd__Name;
/**
 * @typedef xsd__NCName
 * Axis C++ defined type for xml basic type NCName
 */
typedef AxisChar * xsd__NCName;
/**
 * @typedef xsd__ID
 * Axis C++ defined type for xml basic type ID
 */
typedef AxisChar * xsd__ID;
/**
 * @typedef xsd__IDREF
 * Axis C++ defined type for xml basic type IDREF
 */
typedef AxisChar * xsd__IDREF;
/**
 * @typedef xsd__IDREFS
 * Axis C++ defined type for xml basic type IDREFS
 */
typedef AxisChar * xsd__IDREFS;
/**
 * @typedef xsd__ENTITY
 * Axis C++ defined type for xml basic type ENTITY
 */
typedef AxisChar * xsd__ENTITY;
/**
 * @typedef xsd__ENTITIES
 * Axis C++ defined type for xml basic type ENTITIES
 */
typedef AxisChar * xsd__ENTITIES;
/**
 * @typedef xsd__NMTOKEN
 * Axis C++ defined type for xml basic type NMTOKEN
 */
typedef AxisChar * xsd__NMTOKEN;
/**
 * @typedef xsd__NMTOKENS
 * Axis C++ defined type for xml basic type NMTOKENS
 */
typedef AxisChar * xsd__NMTOKENS;
/**
 * @typedef xsd__integer
 * Axis C++ defined type for xml basic type integer
 */
#ifdef WIN32
typedef __int64 xsd__integer;
#else
typedef long long xsd__integer;
#endif
/**
 * @typedef xsd__int
 * Axis C++ defined type for xml basic type int
 */
typedef int xsd__int;
/**
 * @typedef xsd__long
 * Axis C++ defined type for xml basic type long
 */
//FJP v Added
#ifdef WIN32
typedef __int64 xsd__long;
#else
typedef long long xsd__long;
#endif
//FJP ^ Added
/**
 * @typedef xsd__short
 * Axis C++ defined type for xml basic type short
 */
typedef short xsd__short;
/**
 * @typedef xsd__decimal
 * Axis C++ defined type for xml basic type decimal
 */
typedef double xsd__decimal;
/**
 * @typedef xsd__float
 * Axis C++ defined type for xml basic type float
 */
typedef float xsd__float;
/**
 * @typedef xsd__double
 * Axis C++ defined type for xml basic type double
 */
typedef double xsd__double;
/**
 * @typedef xsd__boolean
 * Axis C++ defined type for xml basic type boolean
 */
typedef enum { false_=0, true_ } xsd__boolean;
/**
 * @typedef xsd__byte
 * Axis C++ defined type for xml basic type byte
 */
typedef signed char xsd__byte;
/**
 * @typedef xsd__QName
 * Axis C++ defined type for xml basic type QName
 */
typedef AxisChar * xsd__QName;
/**
 * @typedef xsd__NOTATION
 * Axis C++ defined type for xml basic type NOTATION
 */
typedef AxisChar * xsd__NOTATION;
/**
 * @typedef xsd__dateTime
 * Axis C++ defined type for xml basic type dateTime
 */
typedef struct tm xsd__dateTime;
/**
 * @typedef xsd__date
 * Axis C++ defined type for xml basic type date
 */
typedef struct tm xsd__date;
/**
 * @typedef xsd__time
 * Axis C++ defined type for xml basic type time
 */
typedef struct tm xsd__time;
/**
 * @typedef xsd__gYearMonth
 * Axis C++ defined type for xml basic type gYearMonth
 */
typedef struct tm xsd__gYearMonth;
/**
 * @typedef xsd__gYear
 * Axis C++ defined type for xml basic type gYear
 */
typedef struct tm xsd__gYear;
/**
 * @typedef xsd__gMonthDay
 * Axis C++ defined type for xml basic type gMonthDay
 */
typedef struct tm xsd__gMonthDay;
/**
 * @typedef xsd__gDay
 * Axis C++ defined type for xml basic type gDay
 */
typedef struct tm xsd__gDay;
/**
 * @typedef xsd__gMonth
 * Axis C++ defined type for xml basic type gMonth
 */
typedef struct tm xsd__gMonth;
/**
 * @typedef xsd__duration
 * Axis C++ defined type for xml basic type duration
 */
typedef long xsd__duration;
/**
 * @typedef xsd__nonNegativeInteger
 * Axis C++ defined type for xml basic type nonNegativeInteger
 */
#ifdef WIN32
typedef unsigned __int64 xsd__nonNegativeInteger;
#else
typedef unsigned long long xsd__nonNegativeInteger;
#endif
/**
 * @typedef xsd__unsignedByte
 * Axis C++ defined type for xml basic type unsignedByte
 */
typedef unsigned char xsd__unsignedByte;
/**
 * @typedef xsd__unsignedInt
 * Axis C++ defined type for xml basic type unsignedInt
 */
typedef unsigned int xsd__unsignedInt;
/**
 * @typedef xsd__unsignedLong
 * Axis C++ defined type for xml basic type unsignedLong
 */
#ifdef WIN32
typedef unsigned __int64 xsd__unsignedLong;
#else
typedef unsigned long long xsd__unsignedLong;
#endif
/**
 * @typedef xsd__unsignedShort
 * Axis C++ defined type for xml basic type unsignedShort
 */
typedef unsigned short xsd__unsignedShort;
/**
 * @typedef xsd__nonPositiveInteger
 * Axis C++ defined type for xml basic type nonPositiveInteger
 */
#ifdef WIN32
typedef __int64 xsd__nonPositiveInteger;
#else
typedef long long xsd__nonPositiveInteger;
#endif
/**
 * @typedef xsd__positiveInteger
 * Axis C++ defined type for xml basic type positiveInteger
 */
#ifdef WIN32
typedef unsigned __int64 xsd__positiveInteger;
#else
typedef unsigned long long xsd__positiveInteger;
#endif
/**
 * @typedef xsd__negativeInteger
 * Axis C++ defined type for xml basic type negativeInteger
 */
#ifdef WIN32
typedef __int64 xsd__negativeInteger;
#else
typedef long long xsd__negativeInteger;
#endif
/**
 * @class xsd__base64Binary
 * Axis C++ defined type for xml basic type base64Binary
 */
class STORAGE_CLASS_INFO xsd__base64Binary {
public:

    /**
     * Default constructor
     */
    xsd__base64Binary();
    
    /**
     * Copy Constructor
     * @param original xsd__base64Binary object to be copied.
     */
	xsd__base64Binary(const xsd__base64Binary & original);
   
   /**
    * Destructor
    */
    ~xsd__base64Binary();
    
    /**
     * Set binary data into xsd__base64Binary object.
     * @param data binary data
     * @param size length, in bytes, of binary data
     */
	void set(xsd__unsignedByte * data, xsd__int size);
   
    /**
     * Get binary data from xsd__base64Binary object.
     * @param size is updated with length, in bytes, of binary data
     * @return binary data
     */
	xsd__unsignedByte * get(xsd__int & size) const;
  
    /**
     * Get length, in bytes, of binary data.
     * @return length, in bytes, of binary data
     */
	xsd__int getSize(void) const;
    
    /**
     * Assignment operator
     * @param original xsd__base64Binary object from which data is to be assigned
     * @return reference to this
     */
	xsd__base64Binary & operator=(const xsd__base64Binary & original);
private:
    /**
     * Binary data
     */
    xsd__unsignedByte * __ptr;

    /**
     * Length, in bytes, of binary data
     */
    xsd__int __size;
};

/**
 * @class xsd__hexBinary
 * Axis C++ defined type for xml basic type hexBinary
 */
class STORAGE_CLASS_INFO xsd__hexBinary {
public:
    /**
     * Default constructor
     */
    xsd__hexBinary();
    
    /**
     * Copy Constructor
     * @param original xsd__hexBinary object to be copied.
     */
    xsd__hexBinary(const xsd__hexBinary & original);

   /**
    * Destructor
    */    
	~xsd__hexBinary();

    /**
     * Set binary data into xsd__hexBinary object.
     * @param data binary data
     * @param size length, in bytes, of binary data
     */
    void set(xsd__unsignedByte * data, xsd__int size);

    /**
     * Get binary data from xsd__hexBinary object.
     * @param size is updated with length, in bytes, of binary data
     * @return binary data
     */
    xsd__unsignedByte * get(xsd__int & size) const;

    /**
     * Get length, in bytes, of binary data.
     * @return length, in bytes, of binary data
     */
    xsd__int getSize(void) const;

    /**
     * Assignment operator
     * @param original xsd__hexBinary object from which data is to be assigned
     * @return reference to this
     */
    xsd__hexBinary & operator=(const xsd__hexBinary & original);
private:
    /**
     * Binary data
     */
    xsd__unsignedByte * __ptr;
    
    /**
     * Length, in bytes, of binary data
     */
    xsd__int __size;
};

/**
 * @typedef xsd__anyURI
 * Axis C++ defined type for xml basic type anyURI
 */
typedef AxisChar * xsd__anyURI;

/**
 * @enum AXIS_BINDING_STYLE
 * Enumeration for the different wsdl styles. This is used by the Axis
 * engine to identify the web service or client style.
 */
typedef enum {
    RPC_ENCODED, /*default*/
    DOC_LITERAL,
    RPC_LITERAL
} AXIS_BINDING_STYLE;

/**
 * @class Axis_Array
 * 
 * The parent storage class for arrays
 */
class STORAGE_CLASS_INFO Axis_Array {
  public:
    /**
     * Constructor
     */
    Axis_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    Axis_Array(const Axis_Array & original);
    
    /**
     * Destructor
     */
    virtual ~Axis_Array();
    
    /**
     * Clone the content of an existing Axis_Array
     * @param original array to be cloned into this array.
     */
    void clone(const Axis_Array & original);

    /**
     * Create a new clone of the current Axis_Array
     * @return New clone of the current Axis_Array.
     */
    virtual Axis_Array * clone() const;

    
    /**
     * Populate from a c-style array.
     * 
     * @param array is a c-style array of pointers to the array data.
     * @param size of the array, including NULL entries.
     * @param type of data.
     */
    void set(void** array, int size, XSDTYPE type);
    
    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @param type, this will be updated with the type of the data returned.
     * @return c-style array of pointers to the array data.
     */
    void** get(int& size, XSDTYPE& type) const;
    
    /**
     * Clear the array, and it's data
     */
    void clear();

    /**
     * Add an additional element to the array.
     * @param element to be added to the array. This will be appended to the
     * end of the existing array.
     */
    void addElement(void* element);

    friend class SoapDeSerializer;
    friend class SoapSerializer;

protected:
    /**
     * Array of pointers to array elements
     */
    void** m_Array;

    /**
     * Size of array
     */
    int m_Size;

    /**
     * XSD datatype within this array
     */
    XSDTYPE m_Type;

    /**
     * Indicates if array was created by the engine and therefore needs to be
     * destroyed by the engine.
     */
    bool m_belongsToAxisEngine;
};

#define AXIS_OUT_PARAM 

static const xsd__boolean xsd_boolean_true = (xsd__boolean) 1;
static const xsd__boolean xsd_boolean_false = (xsd__boolean) 0;

typedef enum {
    NORMAL_CHANNEL=0,
    SSL_CHANNEL
} AXIS_CHANNEL_TYPE;

/**
 * @typedef XML_String
 * Axis C++ defined type for xml encoded string. This is used only in AnyType.
 */
typedef char* XML_String;

/**
 * @class AnyType
 * Axis C++ defined type for handling xsd:any.
 */
class STORAGE_CLASS_INFO AnyType
{
public:
    AnyType();
    ~AnyType();

    /**
     * @var _array Contains an array of xml encoded strings.
     */
    XML_String* _array;

    /**
     * @var _size Contains how many xml strings are there in _array
     */
    int _size;
};

AXIS_CPP_NAMESPACE_END
#endif
