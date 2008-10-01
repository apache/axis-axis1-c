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

#if !defined(_DOUBLE_HPP____OF_AXIS_INCLUDED_)
#define _DOUBLE_HPP____OF_AXIS_INCLUDED_

#include "IAnySimpleType.hpp"
#include "constraints/MinInclusive.hpp"
#include "constraints/MinExclusive.hpp"
#include "constraints/MaxInclusive.hpp"
#include "constraints/MaxExclusive.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Double : public IAnySimpleType {
public:

    /**
     * Constructor
     */
    Double();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    Double(const xsd__double* value);
    
    /**
     * Destructor
     */
    virtual ~Double() { }
 
     /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__double* getDouble();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();
    
protected:

    /**
     * Deserialized Double value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of Double value.
     * @return Deserialized Double value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__double* deserializeDouble(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize Double value to it's on-the-wire string form.
     * @param value The Double value to be serialized.
     * @return Serialized form of Double value.
     */
    AxisChar* serialize(const xsd__double* value) throw (AxisSoapException);

    /**
     * Creates a MinInclusive object.  For the Double type this is undefined, 
     * so an unset MinInclusive object is created.
     * @return MinInclusive object
     */
    virtual MinInclusive* getMinInclusive();

    /**
     * Creates a MinExclusive object.  For the Double type this is undefined, 
     * so an unset MinExclusive object is created.
     * @return MinExclusive object
     */
    virtual MinExclusive* getMinExclusive();

    /**
     * Creates a MaxInclusive object.  For the Double type this is undefined, 
     * so an unset MaxInclusive object is created.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();

    /**
     * Creates a MaxExclusive object.  For the Double type this is undefined, 
     * so an unset MaxExclusive object is created.
     * @return MaxExclusive object
     */
    virtual MaxExclusive* getMaxExclusive();

    /**
     * Creates a WhiteSpace object to collapse whitespace
     * @return WhiteSpace object set to collapse whitespace
     */
    WhiteSpace* getWhiteSpace();
};

AXIS_CPP_NAMESPACE_END

#endif
