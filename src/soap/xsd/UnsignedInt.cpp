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

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include "UnsignedInt.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedInt::UnsignedInt()
{
}

UnsignedInt::UnsignedInt(const xsd__unsignedInt* value)
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

xsd__unsignedInt* UnsignedInt::getUnsignedInt()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeUnsignedInt(m_Buf);
    }
}

void * UnsignedInt::getValue()
{
    return (void*) getUnsignedInt();
}

AxisChar* UnsignedInt::serialize(const xsd__unsignedInt* value) throw (AxisSoapException)
{
    xsd__unsignedLong valueAsLong = static_cast<xsd__unsignedLong>(*value);
    return UnsignedLong::serialize(&valueAsLong);
}

xsd__unsignedInt* UnsignedInt::deserializeUnsignedInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedLong* returnValue = UnsignedLong::deserializeUnsignedLong(valueAsChar);
 
    xsd__unsignedInt * value = new xsd__unsignedInt;
    *value = static_cast<xsd__unsignedInt> (*returnValue);
    delete returnValue;
    return value;
}

MaxInclusive* UnsignedInt::getMaxInclusive()
{
    LONGLONG maxInclusive = LONGLONGVALUE(4294967295);
    
    return new MaxInclusive(maxInclusive);
}

AXIS_CPP_NAMESPACE_END
