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

#if !defined(_BYTE_HPP____OF_AXIS_INCLUDED_)
#define _BYTE_HPP____OF_AXIS_INCLUDED_

#include "Short.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Byte : public Short {
public:

    /**
     * Constructor
     */
    Byte();

    /**
     * Destructor
     */
    ~Byte();

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
     * Serialize Byte value to it's on-the-wire string form.
     * @param value The Byte value to be serialized.
     * @return Serialized form of Byte value.
     */  
    AxisChar* serialize(const char* value) throw (AxisSoapException);
  
    /**
     * Deserialized Byte value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of Byte value.
     * @return Deserialized Byte value.
     */
    char* deserializeByte(const AxisChar* valueAsChar) throw (AxisSoapException);

protected:

    /**
     * Creates a MinInclusive object.  For the Byte type this is defined as
     * -128.
     * @return MinInclusive object
     */
    virtual MinInclusive* getMinInclusive();

    /**
     * Creates a MinExclusive object.  For the Byte type this is defined as
     * -129.
     * @return MinExclusive object
     */
    virtual MinExclusive* getMinExclusive();

    /**
     * Creates a MaxInclusive object.  For the Byte type this is defined as
     * 127.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();

    /**
     * Creates a Maxexclusive object.  For the Byte type this is defined as
     * 128.
     * @return Maxexclusive object
     */
    virtual MaxExclusive* getMaxExclusive();
    
private:
    char* m_Byte;
};

AXIS_CPP_NAMESPACE_END

#endif
