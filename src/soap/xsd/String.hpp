/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

AXIS_CPP_NAMESPACE_START

using namespace std;

class String : public IAnySimpleType {
public:

    /**
     * Constructor
     */
    String();
	
    /**
     * Serialize value to it's on-the-wire string form.
     * @param value The value to be serialized.
     * @return Serialized form of value.
     */
	AxisChar* serialize(const void* value) throw (AxisSoapException);

    /**
     * Deserialize value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of value.
     * @return Deserialized value.
     */
	void* deserialize(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize String value to it's on-the-wire string form.
     * @param value The String value to be serialized.
     * @return Serialized form of String value.
     */	
	AxisChar* serialize(const AxisChar* value) throw (AxisSoapException);

    /**
     * Deserialized String value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of String value.
     * @return Deserialized String value.
     */
	AxisChar* deserializeString(const AxisChar* valueAsChar) throw (AxisSoapException);

protected:

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

private:
    AxisChar* m_String;
};

AXIS_CPP_NAMESPACE_END

#endif
