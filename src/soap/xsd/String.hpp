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

#if !defined(_STRING_HPP____OF_AXIS_INCLUDED_)
#define _STRING_HPP____OF_AXIS_INCLUDED_

#include "IAnySimpleType.hpp"
#include "constraints/MinLength.hpp"
#include "constraints/MaxLength.hpp"
#include "constraints/Length.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class String : public IAnySimpleType {
public:

    /**
     * Constructor
     */
    String();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    String(const xsd__string value);

    /**
     * Destructor
     */
    virtual ~String() { }

    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__string getString();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();

protected:

    /**
     * Deserialized String value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of String value.
     * @return Deserialized String value. Note: it is the responsibility of the calling code to delete this value!
     */
	xsd__string deserializeString(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize String value to it's on-the-wire string form.
     * @param value The String value to be serialized.
     * @return Serialized form of String value.
     */   
  AxisChar* serialize(const xsd__string value) throw (AxisSoapException);

    /**
     * Creates a minLength object, used to allocate storage.  By default the String
     * object does not have this specified, so this is an unset minLength object.
     * @return An unset MinLength object
     */
    MinLength* getMinLength();

    /**
     * Creates a maxLength object, used to allocate storage.  By default the String
     * object does not have this specified, so this is an unset maxLength object.
     * @return An unset MaxLength object
     */
    MaxLength* getMaxLength();

    /**
     * Creates a Length object, used to allocate storage.  By default the String
     * object does not have this specified, so this is an unset Length object.
     * @return An unset Length object
     */
    Length* getLength();
};

AXIS_CPP_NAMESPACE_END

#endif
