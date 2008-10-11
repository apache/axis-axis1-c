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

#include "UnsignedShort.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedShort::UnsignedShort()
{
}

UnsignedShort::UnsignedShort(const xsd__unsignedShort* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

UnsignedShort::~UnsignedShort()
{
}

XSDTYPE UnsignedShort::getType()
{
    return XSD_UNSIGNEDSHORT;
}

xsd__unsignedShort* UnsignedShort::getUnsignedShort()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeUnsignedShort(m_Buf);
    }
}

void * UnsignedShort::getValue()
{
    return (void*) getUnsignedShort();
}

AxisChar* UnsignedShort::serialize(const xsd__unsignedShort * value) throw (AxisSoapException)
{
    xsd__unsignedInt valueAsInt = static_cast<xsd__unsignedInt>(*value);
    return UnsignedInt::serialize(&valueAsInt);
}

xsd__unsignedShort* UnsignedShort::deserializeUnsignedShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedInt* returnValue = UnsignedInt::deserializeUnsignedInt(valueAsChar);
 
    xsd__unsignedShort * value = new xsd__unsignedShort;
    *value = static_cast<xsd__unsignedShort> (*returnValue);
    delete returnValue;
    return value;
}

MaxInclusive* UnsignedShort::getMaxInclusive()
{
    LONGLONG maxInclusive = LONGLONGVALUE(65535);
    
    return new MaxInclusive(maxInclusive);
}

AXIS_CPP_NAMESPACE_END
