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

#if !defined(_UNSIGNEDSHORT_HPP____OF_AXIS_INCLUDED_)
#define _UNSIGNEDSHORT_HPP____OF_AXIS_INCLUDED_

#include "UnsignedInt.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class UnsignedShort : public UnsignedInt {
public:
    
    /**
     * Constructor
     */
    UnsignedShort();
    
    /**
     * Destructor
     */
    ~UnsignedShort();

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
     * Serialize UnsignedShort value to it's on-the-wire string form.
     * @param value The UnsignedShort value to be serialized.
     * @return Serialized form of UnsignedShort value.
     */  
    AxisChar* serialize(const unsigned short* value) throw (AxisSoapException);
  
  /**
   * Deserialized UnsignedShort value from it's on-the-wire string form.
   * @param valueAsChar Serialized form of UnsignedShort value.
   * @return Deserialized UnsignedShort value.
   */
    unsigned short* deserializeUnsignedShort(const AxisChar* valueAsChar) throw (AxisSoapException);

protected:

    /**
     * Creates a MaxInclusive object.  For the UnsignedShort type this is
     * defined as 65535.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();
    
private:
    unsigned short *m_UnsignedShort;
};

AXIS_CPP_NAMESPACE_END

#endif
