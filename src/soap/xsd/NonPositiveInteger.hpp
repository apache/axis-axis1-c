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

#if !defined(_NONPOSITIVEINTEGER_HPP____OF_AXIS_INCLUDED_)
#define _NONPOSITIVEINTEGER_HPP____OF_AXIS_INCLUDED_

#include "Integer.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class NonPositiveInteger : public Integer {
public:

    /**
     * Constructor
     */
    NonPositiveInteger();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    NonPositiveInteger(const xsd__nonPositiveInteger* value);
    
    /**
     * Destructor
     */
    ~NonPositiveInteger();

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
   * Deserialized NonPositiveInteger value from it's on-the-wire string form.
   * @param valueAsChar Serialized form of NonPositiveInteger value.
   * @return Deserialized NonPositiveInteger value.
   */
    xsd__nonPositiveInteger* deserializeNonPositiveInteger(const AxisChar* valueAsChar) throw (AxisSoapException);

protected:

    /**
     * Serialize NonPositiveInteger value to it's on-the-wire string form.
     * @param value The NonPositiveInteger value to be serialized.
     * @return Serialized form of NonPositiveInteger value.
     */
    AxisChar* serialize(const xsd__nonPositiveInteger* value) throw (AxisSoapException);

    /**
     * Creates a MaxInclusive object.  For the NonPositiveInteger type this is
     * defined as 0.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();

private:
   xsd__nonPositiveInteger* m_NonPositiveInteger;

};

AXIS_CPP_NAMESPACE_END

#endif
