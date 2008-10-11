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

#include "UnsignedByte.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedByte::UnsignedByte()
{
}

UnsignedByte::UnsignedByte(const xsd__unsignedByte* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

UnsignedByte::~UnsignedByte()
{
}

XSDTYPE UnsignedByte::getType()
{
    return XSD_UNSIGNEDBYTE;
}

xsd__unsignedByte* UnsignedByte::getUnsignedByte()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeUnsignedByte(m_Buf);
    }
}

void * UnsignedByte::getValue()
{
    return (void*) getUnsignedByte();
}

AxisChar* UnsignedByte::serialize(const xsd__unsignedByte* value) throw (AxisSoapException)
{
    xsd__unsignedShort valueAsShort = static_cast<xsd__unsignedShort>(*value);
    return UnsignedShort::serialize(&valueAsShort);
}

xsd__unsignedByte* UnsignedByte::deserializeUnsignedByte(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedShort* returnValue = UnsignedShort::deserializeUnsignedShort(valueAsChar);
 
    xsd__unsignedByte * value = new xsd__unsignedByte;
    *value = static_cast<xsd__unsignedByte> (*returnValue);
    delete returnValue;
    return value;
}

MaxInclusive* UnsignedByte::getMaxInclusive()
{
    LONGLONG maxInclusive = LONGLONGVALUE(255);
    
    return new MaxInclusive(maxInclusive);
}

AXIS_CPP_NAMESPACE_END
