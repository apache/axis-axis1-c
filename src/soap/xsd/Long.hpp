/* -*- C++ -*- */
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
 *
 * @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */

#if !defined(_LONG_HPP____OF_AXIS_INCLUDED_)
#define _LONG_HPP____OF_AXIS_INCLUDED_

#include "Integer.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Long : public Integer {
public:
    /**
     * Constructor
     */
    Long();

    /**
     * Destructor
     */
    ~Long();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    Long(const xsd__long* value);

    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Deserialize value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of value.
     * @return Deserialized value.
     */  
    void* deserialize(const AxisChar* valueAsChar) throw (AxisSoapException);

  /**
   * Deserialized Long value from it's on-the-wire string form.
   * @param valueAsChar Serialized form of Long value.
   * @return Deserialized Long value.
   */
    xsd__long* deserializeLong(const AxisChar* valueAsChar) throw (AxisSoapException);
    
protected:

    /**
     * Serialize Long value to it's on-the-wire string form.
     * @param value The Long value to be serialized.
     * @return Serialized form of Long value.
     */  
    AxisChar* serialize(const xsd__long* value) throw (AxisSoapException);

    /**
     * Creates a MinInclusive object.  For the Long type this is defined as
     * -9223372036854775808.
     * @return MinInclusive object
     */
    virtual MinInclusive* getMinInclusive();
    
    /**
     * Creates a MaxInclusive object.  For the Long type this is defined as
     * 9223372036854775807.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();  

private:
    xsd__long* m_Long; 
};

AXIS_CPP_NAMESPACE_END

#endif
