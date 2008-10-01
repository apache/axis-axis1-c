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

#if !defined(_DECIMAL_HPP____OF_AXIS_INCLUDED_)
#define _DECIMAL_HPP____OF_AXIS_INCLUDED_

#include "IAnySimpleType.hpp"
#include "constraints/MinInclusive.hpp"
#include "constraints/MinExclusive.hpp"
#include "constraints/MaxInclusive.hpp"
#include "constraints/MaxExclusive.hpp"
#include "constraints/TotalDigits.hpp"
#include "constraints/FractionDigits.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Decimal : public IAnySimpleType {
public:

    /**
     * Constructor
     */
    Decimal();
    
    /**
     * Destructor
     */
    virtual ~Decimal();

    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    Decimal(const xsd__decimal* value);

    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();

    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__decimal* getDecimal();

    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();
   
protected:

    /**
     * Deserialized Decimal value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of Decimal value.
     * @return Deserialized Decimal value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__decimal* deserializeDecimal(const AxisChar* valueAsChar) throw (AxisSoapException);


    /**
     * Serialize Decimal value to it's on-the-wire string form.
     * @param value The Decimal value to be serialized.
     * @return Serialized form of Decimal value.
     */
    AxisChar* serialize(const xsd__decimal* value) throw (AxisSoapException);

    /**
     * Creates a MinInclusive object.  For the Decimal type this is undefined, 
     * so an unset MinInclusive object is created.
     * @return MinInclusive object
     */
    virtual MinInclusive* getMinInclusive();

    /**
     * Creates a MinExclusive object.  For the Decimal type this is undefined, 
     * so an unset MinExclusive object is created.
     * @return MinExclusive object
     */
    virtual MinExclusive* getMinExclusive();

    /**
     * Creates a MaxInclusive object.  For the Decimal type this is undefined, 
     * so an unset MaxInclusive object is created.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();

    /**
     * Creates a MaxExclusive object.  For the Decimal type this is undefined, 
     * so an unset MaxExclusive object is created.
     * @return MaxExclusive object
     */
    virtual MaxExclusive* getMaxExclusive();

    /**
     * Creates a WhiteSpace object to collapse whitespace
     * @return WhiteSpace object set to collapse whitespace
     */
    WhiteSpace* getWhiteSpace();

    /**
     * Creates a TotalDigits object.  For the Decimal type this is undefined,
     * so an unset TotalDigits object is created.
     * @return TotalDigits object
     */
    TotalDigits* getTotalDigits();

    /**
     * Creates a FractionDigits object.  For the Decimal type this is undefined,
     * so an unset FractionDigits object is created.
     * @return FractionDigits object
     */
    FractionDigits* getFractionDigits();
};

AXIS_CPP_NAMESPACE_END

#endif
