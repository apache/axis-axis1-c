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

#include "UnsignedInt.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedInt::UnsignedInt():m_UnsignedInt(NULL)
{
}

UnsignedInt::UnsignedInt(const xsd__unsignedInt* value):m_UnsignedInt(NULL)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

UnsignedInt::~UnsignedInt()
{
}

XSDTYPE UnsignedInt::getType()
{
    return XSD_UNSIGNEDINT;
}

void* UnsignedInt::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedInt(valueAsChar);
}

AxisChar* UnsignedInt::serialize(const xsd__unsignedInt* value) throw (AxisSoapException)
{
    xsd__unsignedLong valueAsLong = static_cast<xsd__unsignedLong>(*value);
    return UnsignedLong::serialize(&valueAsLong);
}

xsd__unsignedInt* UnsignedInt::deserializeUnsignedInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedLong* returnValue = UnsignedLong::deserializeUnsignedLong(valueAsChar);
 
    if(m_UnsignedInt)
    {
        delete m_UnsignedInt;
        m_UnsignedInt = NULL;
    }
    m_UnsignedInt = new xsd__unsignedInt;
    *m_UnsignedInt = static_cast<xsd__unsignedInt> (*returnValue);
    return m_UnsignedInt;
}

MaxInclusive* UnsignedInt::getMaxInclusive()
{
    LONGLONG maxInclusive = LONGLONGVALUE(4294967295);
    
    return new MaxInclusive(maxInclusive);
}

AXIS_CPP_NAMESPACE_END
