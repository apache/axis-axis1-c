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

#if !defined(_INTEGER_HPP____OF_AXIS_INCLUDED_)
#define _INTEGER_HPP____OF_AXIS_INCLUDED_

#include "Decimal.hpp"
#include "../../platforms/PlatformAutoSense.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Integer : public Decimal {
public:

    /**
     * Constructor
     */
    Integer();

    /**
     * Destructor
     */
    ~Integer();

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
     * Serialize Integer value to it's on-the-wire string form.
     * @param value The Integer value to be serialized.
     * @return Serialized form of Integer value.
     */
    AxisChar* serialize(const LONGLONG* value) throw (AxisSoapException);
  
    /**
     * Deserialized Integer value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of Integer value.
     * @return Deserialized Integer value.
     */
    LONGLONG* deserializeInteger(const AxisChar* valueAsChar) throw (AxisSoapException);

private:
   LONGLONG* m_Integer;
};

AXIS_CPP_NAMESPACE_END

#endif
