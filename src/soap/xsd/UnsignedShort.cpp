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

#include "UnsignedShort.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedShort::UnsignedShort():m_UnsignedShort(NULL)
{
}

UnsignedShort::~UnsignedShort()
{
}

AxisChar* UnsignedShort::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__unsignedShort *) value);
}

void* UnsignedShort::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedShort(valueAsChar);
}

AxisChar* UnsignedShort::serialize(xsd__unsignedShort * value) throw (AxisSoapException)
{
    xsd__unsignedInt valueAsInt = static_cast<xsd__unsignedInt>(*value);
    return UnsignedInt::serialize(&valueAsInt);
}

xsd__unsignedShort* UnsignedShort::deserializeUnsignedShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedInt* returnValue = UnsignedInt::deserializeUnsignedInt(valueAsChar);
 
    if(m_UnsignedShort)
    {
        delete m_UnsignedShort;
        m_UnsignedShort = NULL;
    }
    m_UnsignedShort = new xsd__unsignedShort;
    *m_UnsignedShort = static_cast<xsd__unsignedShort> (*returnValue);
    return m_UnsignedShort;
}

MaxInclusive* UnsignedShort::getMaxInclusive()
{
   AxisChar* end;    
   LONGLONG* maxInclusive = new LONGLONG;
   *maxInclusive = strtol ("65535", &end, 10);
    
    MaxInclusive* retVal = new MaxInclusive(*maxInclusive);
    delete maxInclusive;
    return retVal;
}

AXIS_CPP_NAMESPACE_END
