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

#include <axis/GDefine.hpp>
#include <axis/TypeMapping.hpp>
#include <time.h>
#include <string.h>

AXIS_CPP_NAMESPACE_START

 /**
  * @file AxisUserAPIArrays.hpp
  * This file contains arrays defined for the basic types declared in AxisUserAPI.hpp
  * 
  * 
  * @author Adrian DIck (adrian.dick@uk.ibm.com)
  */


#include <axis/AxisUserAPI.hpp>

class STORAGE_CLASS_INFO xsd__duration_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__duration_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__duration_Array(xsd__duration_Array & original);
    
    /**
     * Destructor
     */
    ~xsd__duration_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__duration** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__duration** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__dateTime_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__dateTime_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__dateTime_Array(xsd__dateTime_Array & original);
    
    /**
     * Destructor
     */
    ~xsd__dateTime_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__dateTime** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__dateTime** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__time_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__time_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__time_Array(xsd__time_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__time_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__time** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__time** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__date_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__date_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__date_Array(xsd__date_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__date_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__date** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__date** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__gYearMonth_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gYearMonth_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__gYearMonth_Array(xsd__gYearMonth_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__gYearMonth_Array();
    
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gYearMonth** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gYearMonth** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__gYear_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gYear_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__gYear_Array(xsd__gYear_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__gYear_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gYear** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gYear** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__gMonthDay_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gMonthDay_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__gMonthDay_Array(xsd__gMonthDay_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__gMonthDay_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gMonthDay** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gMonthDay** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__gDay_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gDay_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__gDay_Array(xsd__gDay_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__gDay_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gDay** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gDay** get(int& size) const;
};

class STORAGE_CLASS_INFO xsd__gMonth_Array : public Axis_Array {
  public:
    /**
     * Constructor
     */
    xsd__gMonth_Array();

    /**
     * Copy constructor
     * @param orginal Axis_Array to copy.
     */
    xsd__gMonth_Array(xsd__gMonth_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__gMonth_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd_duration data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__gMonth** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd_duration data.
     */
    const xsd__gMonth** get(int& size) const;
};

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
    xsd__string_Array(xsd__string_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__string_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__string data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__string* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__string data.
     */
    const xsd__string* get(int& size) const;
};

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
    xsd__normalizedString_Array(xsd__normalizedString_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__normalizedString_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__normalizedString data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__normalizedString* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__normalizedString data.
     */
    const xsd__normalizedString* get(int& size) const;
};

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
    xsd__token_Array(xsd__token_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__token_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__token data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__token* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__token data.
     */
    const xsd__token* get(int& size) const;
};

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
    xsd__language_Array(xsd__language_Array & original);
    
        
    /**
     * Destructor
     */
    ~xsd__language_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__language data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__language* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__language data.
     */
    const xsd__language* get(int& size) const;
};

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
    xsd__Name_Array(xsd__Name_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__Name_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__Name data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__Name* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__Name data.
     */
    const xsd__Name* get(int& size) const;
};

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
    xsd__NCName_Array(xsd__NCName_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__NCName_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NCName data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NCName* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NCName data.
     */
    const xsd__NCName* get(int& size) const;
};

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
    xsd__ID_Array(xsd__ID_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__ID_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__ID data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__ID* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__ID data.
     */
    const xsd__ID* get(int& size) const;
};

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
    xsd__IDREF_Array(xsd__IDREF_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__IDREF_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__IDREF data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__IDREF* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__IDREF data.
     */
    const xsd__IDREF* get(int& size) const;
};

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
    xsd__IDREFS_Array(xsd__IDREFS_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__IDREFS_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__IDREFS data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__IDREFS* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__IDREFS data.
     */
    const xsd__IDREFS* get(int& size) const;
};

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
    xsd__ENTITY_Array(xsd__ENTITY_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__ENTITY_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__ENTITY data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__ENTITY* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__ENTITY data.
     */
    const xsd__ENTITY* get(int& size) const;
};

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
    xsd__ENTITIES_Array(xsd__ENTITIES_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__ENTITIES_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__ENTITIES data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__ENTITIES* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__ENTITIES data.
     */
    const xsd__ENTITIES* get(int& size) const;
};

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
    xsd__NMTOKEN_Array(xsd__NMTOKEN_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__NMTOKEN_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NMTOKEN data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NMTOKEN* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NMTOKEN data.
     */
    const xsd__NMTOKEN* get(int& size) const;
};

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
    xsd__NMTOKENS_Array(xsd__NMTOKENS_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__NMTOKENS_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NMTOKENS data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NMTOKENS* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NMTOKENS data.
     */
    const xsd__NMTOKENS* get(int& size) const;
};

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
    xsd__boolean_Array(xsd__boolean_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__boolean_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__boolean data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__boolean** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__boolean data.
     */
    const xsd__boolean** get(int& size) const;
};

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
    xsd__base64Binary_Array(xsd__base64Binary_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__base64Binary_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__base64Binary data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__base64Binary** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__base64Binary data.
     */
    const xsd__base64Binary** get(int& size) const;
};

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
    xsd__hexBinary_Array(xsd__hexBinary_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__hexBinary_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__hexBinary data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__hexBinary** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__hexBinary data.
     */
    const xsd__hexBinary** get(int& size) const;
};

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
    xsd__float_Array(xsd__float_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__float_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__float data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__float** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__float data.
     */
    const xsd__float** get(int& size) const;
};

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
    xsd__decimal_Array(xsd__decimal_Array & original);
    
    /**
     * Destructor
     */
    ~xsd__decimal_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__decimal data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__decimal** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__decimal data.
     */
    const xsd__decimal** get(int& size) const;
};

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
    xsd__integer_Array(xsd__integer_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__integer_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__integer data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__integer** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__integer data.
     */
    const xsd__integer** get(int& size) const;
};

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
    xsd__nonPositiveInteger_Array(xsd__nonPositiveInteger_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__nonPositiveInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__nonPositiveInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__nonPositiveInteger** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__nonPositiveInteger data.
     */
    const xsd__nonPositiveInteger** get(int& size) const;
};

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
    xsd__negativeInteger_Array(xsd__negativeInteger_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__negativeInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__negativeInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__negativeInteger** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__negativeInteger data.
     */
    const xsd__negativeInteger** get(int& size) const;
};

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
    xsd__long_Array(xsd__long_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__long_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__long data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__long** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__long data.
     */
    const xsd__long** get(int& size) const;
};

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
    xsd__int_Array(xsd__int_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__int_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__int data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__int** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__int data.
     */
    const xsd__int** get(int& size) const;
};

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
    xsd__short_Array(xsd__short_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__short_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__short data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__short** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__short data.
     */
    const xsd__short** get(int& size) const;
};

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
    xsd__byte_Array(xsd__byte_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__byte_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__byte data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__byte** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__byte data.
     */
    const xsd__byte** get(int& size) const;
};

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
    xsd__nonNegativeInteger_Array(xsd__nonNegativeInteger_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__nonNegativeInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__nonNegativeInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__nonNegativeInteger** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__nonNegativeInteger data.
     */
    const xsd__nonNegativeInteger** get(int& size) const;
};

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
    xsd__unsignedLong_Array(xsd__unsignedLong_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__unsignedLong_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedLong data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedLong** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedLong data.
     */
    const xsd__unsignedLong** get(int& size) const;
};

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
    xsd__unsignedInt_Array(xsd__unsignedInt_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__unsignedInt_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedInt data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedInt** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedInt data.
     */
    const xsd__unsignedInt** get(int& size) const;
};

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
    xsd__unsignedByte_Array(xsd__unsignedByte_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__unsignedByte_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedByte data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedByte** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedByte data.
     */
    const xsd__unsignedByte** get(int& size) const;
};

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
    xsd__unsignedShort_Array(xsd__unsignedShort_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__unsignedShort_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__unsignedShort data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__unsignedShort** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__unsignedShort data.
     */
    const xsd__unsignedShort** get(int& size) const;
};

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
    xsd__positiveInteger_Array(xsd__positiveInteger_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__positiveInteger_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__positiveInteger data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__positiveInteger** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__positiveInteger data.
     */
    const xsd__positiveInteger** get(int& size) const;
};

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
    xsd__double_Array(xsd__double_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__double_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__double data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__double** array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__double data.
     */
    const xsd__double** get(int& size) const;
};

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
    xsd__anyURI_Array(xsd__anyURI_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__anyURI_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__anyURI data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__anyURI* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__anyURI data.
     */
    const xsd__anyURI* get(int& size) const;
};

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
    xsd__QName_Array(xsd__QName_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__QName_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__QName data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__QName* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__QName data.
     */
    const xsd__QName* get(int& size) const;
};

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
    xsd__NOTATION_Array(xsd__NOTATION_Array & original);
        
    /**
     * Destructor
     */
    ~xsd__NOTATION_Array();
    
    /**
     * Populate the array from a c-style array
     * 
     * @param array is a c-style array of pointers to the xsd__NOTATION data.
     * @param size of the array, including NULL entries.
     */
     void set(xsd__NOTATION* array, const int size);

    /**
     * Return a c-style array.
     * 
     * @param size, this will be updated with the size of the array returned.
     * @return c-style array of pointers to the xsd__NOTATION data.
     */
    const xsd__NOTATION* get(int& size) const;
};

AXIS_CPP_NAMESPACE_END
#endif

