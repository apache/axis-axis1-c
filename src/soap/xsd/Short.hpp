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

#if !defined(_SHORT_HPP____OF_AXIS_INCLUDED_)
#define _SHORT_HPP____OF_AXIS_INCLUDED_

#include "Int.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Short : public Int {
public:

    /**
     * Constructor
     */
    Short();

    /**
     * Destructor
     */
    ~Short();

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
    void* deserializer(const AxisChar* valueAsChar) throw (AxisSoapException);

    /**
     * Serialize Short value to it's on-the-wire string form.
     * @param value The Short value to be serialized.
     * @return Serialized form of Short value.
     */  
    AxisChar* serialize(const short* value) throw (AxisSoapException);
  
    /**
     * Deserialized Short value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of Short value.
     * @return Deserialized Short value.
     */
    short* deserializeShort(const AxisChar* valueAsChar) throw (AxisSoapException);

protected:

    /**
     * Creates a MinInclusive object.  For the Short type this is defined as
     * -32768.
     * @return MinInclusive object
     */
    virtual MinInclusive* getMinInclusive();

    /**
     * Creates a MinExclusive object.  For the Short type this is defined as
     * -32769.
     * @return MinExclusive object
     */
    virtual MinExclusive* getMinExclusive();
    
private:
    short* m_Short;
};

AXIS_CPP_NAMESPACE_END

#endif
