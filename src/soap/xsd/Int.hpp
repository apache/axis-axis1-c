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

#if !defined(_INT_HPP____OF_AXIS_INCLUDED_)
#define _INT_HPP____OF_AXIS_INCLUDED_

#include "Long.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Int : public Long {
public:

    /**
     * Constructor
     */
    Int();

    /**
     * Destructor
     */
    virtual ~Int();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    Int(const xsd__int* value);

    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__int* getInt();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();

protected:

    /**
     * Deserialized Int value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of Int value.
     * @return Deserialized Int value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__int* deserializeInt(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize Int value to it's on-the-wire string form.
     * @param value The Int value to be serialized.
     * @return Serialized form of Int value.
     */  
    AxisChar* serialize(const xsd__int* value) throw (AxisSoapException);

    /**
     * Creates a MinInclusive object.  For the Int type this is defined as
     * -2147483648.
     * @return MinInclusive object
     */
    virtual MinInclusive* getMinInclusive();

    /**
     * Creates a MinExclusive object.  For the Int type this is defined as
     * -2147483649.
     * @return MinExclusive object
     */
    virtual MinExclusive* getMinExclusive();

    /**
     * Creates a MaxInclusive object.  For the Int type this is defined as
     * 2147483647.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();

    /**
     * Creates a MaxExclusive object.  For the Int type this is defined as
     * 2147483648.
     * @return MaxExclusive object
     */
    virtual MaxExclusive* getMaxExclusive();
};

AXIS_CPP_NAMESPACE_END

#endif
