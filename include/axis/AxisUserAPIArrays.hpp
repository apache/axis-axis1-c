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

#if !defined(_AXISUSERAPIARRAYS_H____OF_AXIS_INCLUDED_)
#define _AXISUSERAPIARRAYS_H____OF_AXIS_INCLUDED_

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED TO THE        */
/* C-EQUIVALENT HEADER FILE IN SUPPORT OF THE C-BINDING INTERFACES.   */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

 /**
  * @file AxisUserAPIArrays.hpp
  * This file contains arrays defined for the basic types declared in AxisUserAPI.hpp
  * 
  * 
  * @author Adrian DIck (adrian.dick@uk.ibm.com)
  */

#include <time.h>
#include <string.h>

#include <axis/GDefine.hpp>
#include <axis/TypeMapping.hpp>
#include <axis/AxisUserAPI.hpp>


AXIS_CPP_NAMESPACE_START



/**
 * @class xsd__duration_Array
 * 
 * The storage class for arrays of xsd__duration
 * 
 */
class STORAGE_CLASS_INFO xsd__duration_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__duration_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__duration_Array(const xsd__duration_Array & original);
    
    /**
     * Destructor
     */
    virtual ~xsd__duration_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__duration** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__duration** get(int& size) const;
};

/**
 * @class xsd__dateTime_Array
 * 
 * The storage class for arrays of xsd__dateTime
 * 
 */
class STORAGE_CLASS_INFO xsd__dateTime_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__dateTime_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__dateTime_Array(const xsd__dateTime_Array & original);
    
    /**
     * Destructor
     */
    virtual ~xsd__dateTime_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__dateTime** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__dateTime** get(int& size) const;
};

/**
 * @class xsd__time_Array
 * 
 * The storage class for arrays of xsd__time
 * 
 */
class STORAGE_CLASS_INFO xsd__time_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__time_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__time_Array(const xsd__time_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__time_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__time** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__time** get(int& size) const;
};

/**
 * @class xsd__date_Array
 * 
 * The storage class for arrays of xsd__date
 * 
 */
class STORAGE_CLASS_INFO xsd__date_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__date_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__date_Array(const xsd__date_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__date_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__date** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__date** get(int& size) const;
};

/**
 * @class xsd__gYearMonth_Array
 * 
 * The storage class for arrays of xsd__gYearMonth
 * 
 */
class STORAGE_CLASS_INFO xsd__gYearMonth_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gYearMonth_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__gYearMonth_Array(const xsd__gYearMonth_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__gYearMonth_Array();
    
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gYearMonth** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gYearMonth** get(int& size) const;
};

/**
 * @class xsd__gYear_Array
 * 
 * The storage class for arrays of xsd__gYear
 * 
 */
class STORAGE_CLASS_INFO xsd__gYear_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gYear_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__gYear_Array(const xsd__gYear_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__gYear_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gYear** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gYear** get(int& size) const;
};

/**
 * @class xsd__gMonthDay_Array
 * 
 * The storage class for arrays of xsd__gMonthDay
 * 
 */
class STORAGE_CLASS_INFO xsd__gMonthDay_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gMonthDay_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__gMonthDay_Array(const xsd__gMonthDay_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__gMonthDay_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gMonthDay** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gMonthDay** get(int& size) const;
};
/**
 * @class xsd__gDay_Array
 * 
 * The storage class for arrays of xsd__gDay
 * 
 */
class STORAGE_CLASS_INFO xsd__gDay_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gDay_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__gDay_Array(const xsd__gDay_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__gDay_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gDay** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gDay** get(int& size) const;
};

/**
 * @class xsd__gMonth_Array
 * 
 * The storage class for arrays of xsd__gMonth
 * 
 */
class STORAGE_CLASS_INFO xsd__gMonth_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gMonth_Array();

    /**
     * Copy constructor
     * @param original Axis_Array to copy.
     */
    xsd__gMonth_Array(const xsd__gMonth_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__gMonth_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gMonth** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gMonth** get(int& size) const;
};

/**
 * @class xsd__string_Array
 * 
 * The storage class for arrays of xsd__string
 * 
 */
class STORAGE_CLASS_INFO xsd__string_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__string_Array();

    /**
     * Copy constructor
     * @param original xsd__string_Array to copy.
     */
    xsd__string_Array(const xsd__string_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__string_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__string data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__string* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__string data.
     */
    const xsd__string* get(int& size) const;
};

/**
 * @class xsd__normalizedString_Array
 * 
 * The storage class for arrays of xsd__normalizedString
 * 
 */
class STORAGE_CLASS_INFO xsd__normalizedString_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__normalizedString_Array();

    /**
     * Copy constructor
     * @param original xsd__normalizedString_Array to copy.
     */
    xsd__normalizedString_Array(const xsd__normalizedString_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__normalizedString_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__normalizedString data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__normalizedString* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__normalizedString data.
     */
    const xsd__normalizedString* get(int& size) const;
};

/**
 * @class xsd__token_Array
 * 
 * The storage class for arrays of xsd__token
 * 
 */
class STORAGE_CLASS_INFO xsd__token_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__token_Array();

    /**
     * Copy constructor
     * @param original xsd__token_Array to copy.
     */
    xsd__token_Array(const xsd__token_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__token_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__token data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__token* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__token data.
     */
    const xsd__token* get(int& size) const;
};

/**
 * @class xsd__language_Array
 * 
 * The storage class for arrays of xsd__language
 * 
 */
class STORAGE_CLASS_INFO xsd__language_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__language_Array();

    /**
     * Copy constructor
     * @param original xsd__language_Array to copy.
     */
    xsd__language_Array(const xsd__language_Array & original);
    
        
    /**
     * Destructor
     */
    virtual ~xsd__language_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__language data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__language* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__language data.
     */
    const xsd__language* get(int& size) const;
};

/**
 * @class xsd__Name_Array
 * 
 * The storage class for arrays of xsd__Name
 * 
 */
class STORAGE_CLASS_INFO xsd__Name_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__Name_Array();

    /**
     * Copy constructor
     * @param original xsd__Name_Array to copy.
     */
    xsd__Name_Array(const xsd__Name_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__Name_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__Name data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__Name* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__Name data.
     */
    const xsd__Name* get(int& size) const;
};

/**
 * @class xsd__NCName_Array
 * 
 * The storage class for arrays of xsd__NCName
 * 
 */
class STORAGE_CLASS_INFO xsd__NCName_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__NCName_Array();

    /**
     * Copy constructor
     * @param original xsd__NCName_Array to copy.
     */
    xsd__NCName_Array(const xsd__NCName_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__NCName_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NCName data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NCName* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NCName data.
     */
    const xsd__NCName* get(int& size) const;
};

/**
 * @class xsd__ID_Array
 * 
 * The storage class for arrays of xsd__ID
 * 
 */
class STORAGE_CLASS_INFO xsd__ID_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__ID_Array();

    /**
     * Copy constructor
     * @param original xsd__ID_Array to copy.
     */
    xsd__ID_Array(const xsd__ID_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__ID_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__ID data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__ID* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__ID data.
     */
    const xsd__ID* get(int& size) const;
};

/**
 * @class xsd__IDREF_Array
 * 
 * The storage class for arrays of xsd__IDREF
 * 
 */
class STORAGE_CLASS_INFO xsd__IDREF_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__IDREF_Array();

    /**
     * Copy constructor
     * @param original xsd__IDREF_Array to copy.
     */
    xsd__IDREF_Array(const xsd__IDREF_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__IDREF_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__IDREF data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__IDREF* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__IDREF data.
     */
    const xsd__IDREF* get(int& size) const;
};

/**
 * @class xsd__IDREFS_Array
 * 
 * The storage class for arrays of xsd__IDREFS
 * 
 */
class STORAGE_CLASS_INFO xsd__IDREFS_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__IDREFS_Array();

    /**
     * Copy constructor
     * @param original xsd__IDREFS_Array to copy.
     */
    xsd__IDREFS_Array(const xsd__IDREFS_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__IDREFS_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__IDREFS data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__IDREFS* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__IDREFS data.
     */
    const xsd__IDREFS* get(int& size) const;
};

/**
 * @class xsd__ENTITY_Array
 * 
 * The storage class for arrays of xsd__ENTITY
 * 
 */
class STORAGE_CLASS_INFO xsd__ENTITY_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__ENTITY_Array();

    /**
     * Copy constructor
     * @param original xsd__ENTITY_Array to copy.
     */
    xsd__ENTITY_Array(const xsd__ENTITY_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__ENTITY_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__ENTITY data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__ENTITY* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__ENTITY data.
     */
    const xsd__ENTITY* get(int& size) const;
};

/**
 * @class xsd__ENTITIES_Array
 * 
 * The storage class for arrays of xsd__ENTITIES
 * 
 */
class STORAGE_CLASS_INFO xsd__ENTITIES_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__ENTITIES_Array();

    /**
     * Copy constructor
     * @param original xsd__ENTITIES_Array to copy.
     */
    xsd__ENTITIES_Array(const xsd__ENTITIES_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__ENTITIES_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__ENTITIES data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__ENTITIES* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__ENTITIES data.
     */
    const xsd__ENTITIES* get(int& size) const;
};

/**
 * @class xsd__NMTOKEN_Array
 * 
 * The storage class for arrays of xsd__NMTOKEN
 * 
 */
class STORAGE_CLASS_INFO xsd__NMTOKEN_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__NMTOKEN_Array();

    /**
     * Copy constructor
     * @param original xsd__NMTOKEN_Array to copy.
     */
    xsd__NMTOKEN_Array(const xsd__NMTOKEN_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__NMTOKEN_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NMTOKEN data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NMTOKEN* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NMTOKEN data.
     */
    const xsd__NMTOKEN* get(int& size) const;
};

/**
 * @class xsd__NMTOKENS_Array
 * 
 * The storage class for arrays of xsd__NMTOKENS
 * 
 */
class STORAGE_CLASS_INFO xsd__NMTOKENS_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__NMTOKENS_Array();

    /**
     * Copy constructor
     * @param original xsd__NMTOKENS_Array to copy.
     */
    xsd__NMTOKENS_Array(const xsd__NMTOKENS_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__NMTOKENS_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NMTOKENS data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NMTOKENS* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NMTOKENS data.
     */
    const xsd__NMTOKENS* get(int& size) const;
};

/**
 * @class xsd__boolean_Array
 * 
 * The storage class for arrays of xsd__boolean
 * 
 */
class STORAGE_CLASS_INFO xsd__boolean_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__boolean_Array();

    /**
     * Copy constructor
     * @param original xsd__boolean_Array to copy.
     */
    xsd__boolean_Array(const xsd__boolean_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__boolean_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__boolean data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__boolean** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__boolean data.
     */
    const xsd__boolean** get(int& size) const;
};

/**
 * @class xsd__base64Binary_Array
 * 
 * The storage class for arrays of xsd__base64Binary
 * 
 */
class STORAGE_CLASS_INFO xsd__base64Binary_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__base64Binary_Array();

    /**
     * Copy constructor
     * @param original xsd__base64Binary_Array to copy.
     */
    xsd__base64Binary_Array(const xsd__base64Binary_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__base64Binary_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__base64Binary data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__base64Binary** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__base64Binary data.
     */
    const xsd__base64Binary** get(int& size) const;
};

/**
 * @class xsd__hexBinary_Array
 * 
 * The storage class for arrays of xsd__hexBinary
 * 
 */
class STORAGE_CLASS_INFO xsd__hexBinary_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__hexBinary_Array();

    /**
     * Copy constructor
     * @param original xsd__hexBinary_Array to copy.
     */
    xsd__hexBinary_Array(const xsd__hexBinary_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__hexBinary_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__hexBinary data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__hexBinary** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__hexBinary data.
     */
    const xsd__hexBinary** get(int& size) const;
};

/**
 * @class xsd__float_Array
 * 
 * The storage class for arrays of xsd__float
 * 
 */
class STORAGE_CLASS_INFO xsd__float_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__float_Array();

    /**
     * Copy constructor
     * @param original xsd__float_Array to copy.
     */
    xsd__float_Array(const xsd__float_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__float_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__float data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__float** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__float data.
     */
    const xsd__float** get(int& size) const;
};

/**
 * @class xsd__decimal_Array
 * 
 * The storage class for arrays of xsd__decimal
 * 
 */
class STORAGE_CLASS_INFO xsd__decimal_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__decimal_Array();

    /**
     * Copy constructor
     * @param original xsd__decimal_Array to copy.
     */
    xsd__decimal_Array(const xsd__decimal_Array & original);
    
    /**
     * Destructor
     */
    virtual ~xsd__decimal_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__decimal data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__decimal** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__decimal data.
     */
    const xsd__decimal** get(int& size) const;
};

/**
 * @class xsd__integer_Array
 * 
 * The storage class for arrays of xsd__integer
 * 
 */
class STORAGE_CLASS_INFO xsd__integer_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__integer_Array();

    /**
     * Copy constructor
     * @param original xsd__integer_Array to copy.
     */
    xsd__integer_Array(const xsd__integer_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__integer_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__integer data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__integer** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__integer data.
     */
    const xsd__integer** get(int& size) const;
};

/**
 * @class xsd__nonPositiveInteger_Array
 * 
 * The storage class for arrays of xsd__nonPositiveInteger
 * 
 */
class STORAGE_CLASS_INFO xsd__nonPositiveInteger_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__nonPositiveInteger_Array();

    /**
     * Copy constructor
     * @param original xsd__nonPositiveInteger_Array to copy.
     */
    xsd__nonPositiveInteger_Array(const xsd__nonPositiveInteger_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__nonPositiveInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__nonPositiveInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__nonPositiveInteger** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__nonPositiveInteger data.
     */
    const xsd__nonPositiveInteger** get(int& size) const;
};

/**
 * @class xsd__negativeInteger_Array
 * 
 * The storage class for arrays of xsd__negativeInteger
 * 
 */
class STORAGE_CLASS_INFO xsd__negativeInteger_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__negativeInteger_Array();

    /**
     * Copy constructor
     * @param original xsd__negativeInteger_Array to copy.
     */
    xsd__negativeInteger_Array(const xsd__negativeInteger_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__negativeInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__negativeInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__negativeInteger** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__negativeInteger data.
     */
    const xsd__negativeInteger** get(int& size) const;
};

/**
 * @class xsd__long_Array
 * 
 * The storage class for arrays of xsd__long
 * 
 */
class STORAGE_CLASS_INFO xsd__long_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__long_Array();

    /**
     * Copy constructor
     * @param original xsd__long_Array to copy.
     */
    xsd__long_Array(const xsd__long_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__long_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__long data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__long** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__long data.
     */
    const xsd__long** get(int& size) const;
};

/**
 * @class xsd__int_Array
 * 
 * The storage class for arrays of xsd__int
 * 
 */
class STORAGE_CLASS_INFO xsd__int_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__int_Array();

    /**
     * Copy constructor
     * @param original xsd__int_Array to copy.
     */
    xsd__int_Array(const xsd__int_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__int_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__int data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__int** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__int data.
     */
    const xsd__int** get(int& size) const;
};

/**
 * @class xsd__short_Array
 * 
 * The storage class for arrays of xsd__short
 * 
 */
class STORAGE_CLASS_INFO xsd__short_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__short_Array();

    /**
     * Copy constructor
     * @param original xsd__short_Array to copy.
     */
    xsd__short_Array(const xsd__short_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__short_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__short data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__short** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__short data.
     */
    const xsd__short** get(int& size) const;
};

/**
 * @class xsd__byte_Array
 * 
 * The storage class for arrays of xsd__byte
 * 
 */
class STORAGE_CLASS_INFO xsd__byte_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__byte_Array();

    /**
     * Copy constructor
     * @param original xsd__byte_Array to copy.
     */
    xsd__byte_Array(const xsd__byte_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__byte_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__byte data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__byte** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__byte data.
     */
    const xsd__byte** get(int& size) const;
};

/**
 * @class xsd__nonNegativeInteger_Array
 * 
 * The storage class for arrays of xsd__nonNegativeInteger
 * 
 */
class STORAGE_CLASS_INFO xsd__nonNegativeInteger_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__nonNegativeInteger_Array();

    /**
     * Copy constructor
     * @param original xsd__nonNegativeInteger_Array to copy.
     */
    xsd__nonNegativeInteger_Array(const xsd__nonNegativeInteger_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__nonNegativeInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__nonNegativeInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__nonNegativeInteger** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__nonNegativeInteger data.
     */
    const xsd__nonNegativeInteger** get(int& size) const;
};

/**
 * @class xsd__unsignedLong_Array
 * 
 * The storage class for arrays of xsd__unsignedLong
 * 
 */
class STORAGE_CLASS_INFO xsd__unsignedLong_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__unsignedLong_Array();

    /**
     * Copy constructor
     * @param original xsd__unsignedLong_Array to copy.
     */
    xsd__unsignedLong_Array(const xsd__unsignedLong_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__unsignedLong_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedLong data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedLong** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedLong data.
     */
    const xsd__unsignedLong** get(int& size) const;
};

/**
 * @class xsd__unsignedInt_Array
 * 
 * The storage class for arrays of xsd__unsignedInt
 * 
 */
class STORAGE_CLASS_INFO xsd__unsignedInt_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__unsignedInt_Array();

    /**
     * Copy constructor
     * @param original xsd__unsignedInt_Array to copy.
     */
    xsd__unsignedInt_Array(const xsd__unsignedInt_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__unsignedInt_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedInt data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedInt** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedInt data.
     */
    const xsd__unsignedInt** get(int& size) const;
};

/**
 * @class xsd__unsignedByte_Array
 * 
 * The storage class for arrays of xsd__unsignedByte
 * 
 */
class STORAGE_CLASS_INFO xsd__unsignedByte_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__unsignedByte_Array();

    /**
     * Copy constructor
     * @param original xsd__unsignedByte_Array to copy.
     */
    xsd__unsignedByte_Array(const xsd__unsignedByte_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__unsignedByte_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedByte data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedByte** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedByte data.
     */
    const xsd__unsignedByte** get(int& size) const;
};

/**
 * @class xsd__unsignedShort_Array
 * 
 * The storage class for arrays of xsd__unsignedShort
 * 
 */
class STORAGE_CLASS_INFO xsd__unsignedShort_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__unsignedShort_Array();

    /**
     * Copy constructor
     * @param original xsd__unsignedShort_Array to copy.
     */
    xsd__unsignedShort_Array(const xsd__unsignedShort_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__unsignedShort_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedShort data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedShort** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedShort data.
     */
    const xsd__unsignedShort** get(int& size) const;
};

/**
 * @class xsd__positiveInteger_Array
 * 
 * The storage class for arrays of xsd__positiveInteger
 * 
 */
class STORAGE_CLASS_INFO xsd__positiveInteger_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__positiveInteger_Array();

    /**
     * Copy constructor
     * @param original xsd__positiveInteger_Array to copy.
     */
    xsd__positiveInteger_Array(const xsd__positiveInteger_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__positiveInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__positiveInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__positiveInteger** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__positiveInteger data.
     */
    const xsd__positiveInteger** get(int& size) const;
};

/**
 * @class xsd__double_Array
 * 
 * The storage class for arrays of xsd__double
 * 
 */
class STORAGE_CLASS_INFO xsd__double_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__double_Array();

    /**
     * Copy constructor
     * @param original xsd__double_Array to copy.
     */
    xsd__double_Array(const xsd__double_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__double_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__double data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__double** array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__double data.
     */
    const xsd__double** get(int& size) const;
};

/**
 * @class xsd__anyURI_Array
 * 
 * The storage class for arrays of xsd__anyURI
 * 
 */
class STORAGE_CLASS_INFO xsd__anyURI_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__anyURI_Array();

    /**
     * Copy constructor
     * @param original xsd__anyURI_Array to copy.
     */
    xsd__anyURI_Array(const xsd__anyURI_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__anyURI_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__anyURI data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__anyURI* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__anyURI data.
     */
    const xsd__anyURI* get(int& size) const;
};

/**
 * @class xsd__QName_Array
 * 
 * The storage class for arrays of xsd__QName
 * 
 */
class STORAGE_CLASS_INFO xsd__QName_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__QName_Array();

    /**
     * Copy constructor
     * @param original xsd__QName_Array to copy.
     */
    xsd__QName_Array(const xsd__QName_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__QName_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__QName data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__QName* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__QName data.
     */
    const xsd__QName* get(int& size) const;
};

/**
 * @class xsd__NOTATION_Array
 * 
 * The storage class for arrays of xsd__NOTATION
 * 
 */
class STORAGE_CLASS_INFO xsd__NOTATION_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__NOTATION_Array();

    /**
     * Copy constructor
     * @param original xsd__NOTATION_Array to copy.
     */
    xsd__NOTATION_Array(const xsd__NOTATION_Array & original);
        
    /**
     * Destructor
     */
    virtual ~xsd__NOTATION_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NOTATION data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NOTATION* array, int size);

    /**
     * Return a c-style array.
     * 
     * @param size will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NOTATION data.
     */
    const xsd__NOTATION* get(int& size) const;
};

AXIS_CPP_NAMESPACE_END
#endif

