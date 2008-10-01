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

#if !defined(_UNSIGNEDSHORT_HPP____OF_AXIS_INCLUDED_)
#define _UNSIGNEDSHORT_HPP____OF_AXIS_INCLUDED_

#include "UnsignedInt.hpp"
#include <axis/AxisUserAPI.hpp>

AXIS_CPP_NAMESPACE_START

using namespace std;

class UnsignedShort : public UnsignedInt {
public:
    
    /**
     * Constructor
     */
    UnsignedShort();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    UnsignedShort(const xsd__unsignedShort* value);
    
    /**
     * Destructor
     */
    virtual ~UnsignedShort();

    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__unsignedShort* getUnsignedShort();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();

protected:

    /**
     * Deserialized UnsignedShort value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of UnsignedShort value.
     * @return Deserialized UnsignedShort value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__unsignedShort* deserializeUnsignedShort(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize UnsignedShort value to it's on-the-wire string form.
     * @param value The UnsignedShort value to be serialized.
     * @return Serialized form of UnsignedShort value.
     */  
    AxisChar* serialize(const xsd__unsignedShort* value) throw (AxisSoapException);

    /**
     * Creates a MaxInclusive object.  For the UnsignedShort type this is
     * defined as 65535.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();
};

AXIS_CPP_NAMESPACE_END

#endif
