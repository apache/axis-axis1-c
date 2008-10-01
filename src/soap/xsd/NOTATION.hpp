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

#if !defined(_NOTATION_HPP____OF_AXIS_INCLUDED_)
#define _NOTATION_HPP____OF_AXIS_INCLUDED_

#include "IAnySimpleType.hpp"
#include "constraints/MinLength.hpp"
#include "constraints/MaxLength.hpp"
#include "constraints/Length.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class NOTATION : public IAnySimpleType {
public:

    /**
     * Constructor
     */
    NOTATION();

        /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    NOTATION(const xsd__NOTATION value);

    /**
     * Destructor
     */
    virtual ~NOTATION() { }  
    
    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__NOTATION getNOTATION();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();

protected:

    /**
     * Deserialized NOTATION value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of NOTATION value.
     * @return Deserialized NOTATION value. Note: it is the responsibility of the calling code to delete this value!
     */
	xsd__NOTATION deserializeNOTATION(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize NOTATION value to it's on-the-wire string form.
     * @param value The NOTATION value to be serialized.
     * @return Serialized form of NOTATION value.
     */ 
    AxisChar* serialize(const xsd__NOTATION value) throw (AxisSoapException);

    /**
     * Creates a WhiteSpace object to replace whitespace
     * @return WhiteSpace object set to replace whitespace
     */
    WhiteSpace* getWhiteSpace();

    /**
     * Creates a minLength object, used to allocate storage.  By default the NOTATION
     * object does not have this specified, so this is an unset minLength object.
     * @return An unset MinLength object
     */
    MinLength* getMinLength();

    /**
     * Creates a maxLength object, used to allocate storage.  By default the NOTATION
     * object does not have this specified, so this is an unset maxLength object.
     * @return An unset MaxLength object
     */
    MaxLength* getMaxLength();

    /**
     * Creates a Length object, used to allocate storage.  By default the NOTATION
     * object does not have this specified, so this is an unset Length object.
     * @return An unset Length object
     */
    Length* getLength();
};

AXIS_CPP_NAMESPACE_END

#endif
