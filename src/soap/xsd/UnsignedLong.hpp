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

#if !defined(_UNSIGNEDLONG_HPP____OF_AXIS_INCLUDED_)
#define _UNSIGNEDLONG_HPP____OF_AXIS_INCLUDED_

#include "NonNegativeInteger.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class UnsignedLong : public NonNegativeInteger {
public:
    
    /**
     * Constructor
     */
    UnsignedLong();
    
    /**
     * Destructor
     */
    ~UnsignedLong();

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
     * Serialize UnsignedLong value to it's on-the-wire string form.
     * @param value The UnsignedLong value to be serialized.
     * @return Serialized form of UnsignedLong value.
     */  
    AxisChar* serialize(const unsigned long* value) throw (AxisSoapException);
  
  /**
   * Deserialized UnsignedLong value from it's on-the-wire string form.
   * @param valueAsChar Serialized form of UnsignedLong value.
   * @return Deserialized UnsignedLong value.
   */
    unsigned long* deserializeUnsignedLong(const AxisChar* valueAsChar) throw (AxisSoapException);
    
private:
    unsigned long *m_UnsignedLong;
};

AXIS_CPP_NAMESPACE_END

#endif
