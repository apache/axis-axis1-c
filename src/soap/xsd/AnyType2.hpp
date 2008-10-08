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
 * @author Nadir Amra (amra@us.ibm.com)
 *
 */

#if !defined(_ANYTYPE_HPP____OF_AXIS_INCLUDED_)
#define _ANYTYPE_HPP____OF_AXIS_INCLUDED_

#include "IAnySimpleType.hpp"
#include "constraints/MinLength.hpp"
#include "constraints/MaxLength.hpp"
#include "constraints/Length.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

/**
 * Unfortunate that we have to name as AnyType2, but we already have an 
 * AnyType for xsd:any element, which simple cannot be used cleanly in 
 * support of xsd:anyType.
 */
class AnyType2 : public IAnySimpleType {
public:

    /**
     * Constructor
     */
    AnyType2();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    AnyType2(const xsd__anyType value);

    /**
     * Destructor
     */
    virtual ~AnyType2() { }

    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__anyType getAnyType();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();

protected:

    /**
     * Deserialized AnyType value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of AnyType value.
     * @return Deserialized AnyType value. Note: it is the responsibility of the calling code to delete this value!
     */
	xsd__anyType deserializeAnyType(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize AnyType value to it's on-the-wire string form.
     * @param value The AnyType value to be serialized.
     * @return Serialized form of AnyType value.
     */   
    AxisChar* serialize(const xsd__anyType value) throw (AxisSoapException);

    /**
     * Creates a minLength object, used to allocate storage.  By default the AnyType
     * object does not have this specified, so this is an unset minLength object.
     * @return An unset MinLength object
     */
    MinLength* getMinLength();

    /**
     * Creates a maxLength object, used to allocate storage.  By default the AnyType
     * object does not have this specified, so this is an unset maxLength object.
     * @return An unset MaxLength object
     */
    MaxLength* getMaxLength();

    /**
     * Creates a Length object, used to allocate storage.  By default the AnyType
     * object does not have this specified, so this is an unset Length object.
     * @return An unset Length object
     */
    Length* getLength();
};

AXIS_CPP_NAMESPACE_END

#endif
