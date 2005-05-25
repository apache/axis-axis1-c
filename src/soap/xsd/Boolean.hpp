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

#if !defined(_BOOLEAN_HPP____OF_AXIS_INCLUDED_)
#define _BOOLEAN_HPP____OF_AXIS_INCLUDED_

#include "IAnySimpleType.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Boolean : public IAnySimpleType {
public:

    /**
     * Constructor
     */
    Boolean();
    
    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    Boolean(const xsd__boolean* value);
    
    /**
     * Destructor
     */
    ~Boolean();

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
	 * Deserialized boolean value from it's on-the-wire string form.
	 * @param valueAsChar Serialized form of boolean value.
	 * @return Deserialized boolean value.
	 */
    xsd__boolean * deserializeBoolean(const AxisChar* valueAsChar) throw (AxisSoapException);

protected:

    /**
     * Serialize boolean value to it's on-the-wire string form.
     * @param value The boolean value to be serialized.
     * @return Serialized form of boolean value.
     */
    AxisChar* serialize(const xsd__boolean * value) throw (AxisSoapException);

    /**
     * Creates a WhiteSpace object to collapse whitespace
     * @return WhiteSpace object set to collapse whitespace
     */
    WhiteSpace* getWhiteSpace();

    /**
     * Creates an Enumeration object to collapse whitespace
     * @return Enumeration object set to collapse whitespace
     */
    Enumeration* getEnumeration();
   
private:
    xsd__boolean * m_Boolean;
};

AXIS_CPP_NAMESPACE_END

#endif
