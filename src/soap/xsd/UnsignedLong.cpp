// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "UnsignedLong.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedLong::UnsignedLong():m_UnsignedLong(NULL)
{
}

UnsignedLong::~UnsignedLong()
{
}

AxisChar* UnsignedLong::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__unsignedLong*) value);
}

void* UnsignedLong::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedLong(valueAsChar);
}

AxisChar* UnsignedLong::serialize(const xsd__unsignedLong* value) throw (AxisSoapException)
{
    unsigned LONGLONG valueAsLong = static_cast<unsigned LONGLONG>(*value);
    return NonNegativeInteger::serialize(&valueAsLong);
}

xsd__unsignedLong* UnsignedLong::deserializeUnsignedLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    unsigned LONGLONG* returnValue = NonNegativeInteger::deserializeNonNegativeInteger(valueAsChar);
 
    if(m_UnsignedLong)
    {
        delete m_UnsignedLong;
        m_UnsignedLong = NULL;
    }
    m_UnsignedLong = new xsd__unsignedLong;
    *m_UnsignedLong = static_cast<xsd__unsignedLong> (*returnValue);
    return m_UnsignedLong;
}

MaxInclusive* UnsignedLong::getMaxInclusive()
{
 /*
  * The actual value for this is 18446744073709551615, but as this is also the
  * physical limit of an unsigned 64bit integer, we don't actually need to check
  * this.
  */
    return new MaxInclusive();
}

AXIS_CPP_NAMESPACE_END
