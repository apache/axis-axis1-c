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

#if !defined(_LONG_HPP____OF_AXIS_INCLUDED_)
#define _LONG_HPP____OF_AXIS_INCLUDED_

#include "Integer.hpp"

AXIS_CPP_NAMESPACE_START

using namespace std;

class Long : public Integer {
public:
  
  /**
   * Deserialized Long value from it's on-the-wire string form.
   * @param valueAsChar Serialized form of Long value.
   * @return Deserialized Long value.
   */
    LONGLONG* deserializeLong(const AxisChar* valueAsChar) throw (AxisSoapException);
    
protected:

    /**
     * Creates a MinInclusive object.  For the Long type this is defined as
     * -9223372036854775808.
     * @return MinInclusive object
     */
    virtual MinInclusive* getMinInclusive();
    
    /**
     * Creates a MinExclusive object.  For the Long type this is defined as
     * -9223372036854775809.
     * @return MinExclusive object
     */
    virtual MinExclusive* getMinExclusive();
    
    /**
     * Creates a MaxInclusive object.  For the Long type this is defined as
     * 9223372036854775807.
     * @return MaxInclusive object
     */
    virtual MaxInclusive* getMaxInclusive();
    
    /**
     * Creates a MaxExclusive object.  For the Long type this is defined as
     * 9223372036854775808.
     * @return MaxExclusive object
     */
    virtual MaxExclusive* getMaxExclusive();
};

AXIS_CPP_NAMESPACE_END

#endif
