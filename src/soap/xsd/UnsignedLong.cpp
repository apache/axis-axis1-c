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

#include "UnsignedLong.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedLong::UnsignedLong()
{
}

UnsignedLong::UnsignedLong(const xsd__unsignedLong* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

UnsignedLong::~UnsignedLong()
{
}

XSDTYPE UnsignedLong::getType()
{
    return XSD_UNSIGNEDLONG;
}

xsd__unsignedLong* UnsignedLong::getUnsignedLong()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeUnsignedLong(m_Buf);
    }
}

void * UnsignedLong::getValue()
{
    return (void*) getUnsignedLong();
}

AxisChar* UnsignedLong::serialize(const xsd__unsignedLong* value) throw (AxisSoapException)
{
    xsd__nonNegativeInteger valueAsLong = static_cast<xsd__nonNegativeInteger>(*value);
    return NonNegativeInteger::serialize(&valueAsLong);
}

xsd__unsignedLong* UnsignedLong::deserializeUnsignedLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__nonNegativeInteger* returnValue = NonNegativeInteger::deserializeNonNegativeInteger(valueAsChar);
 
    xsd__unsignedLong * value = new xsd__unsignedLong;
    *value = static_cast<xsd__unsignedLong> (*returnValue);
    delete returnValue;
    return value;
}

MaxInclusive* UnsignedLong::getMaxInclusive()
{
 /*
  * The actual value for this is 18446744073709551615, but as this is also the
  * physical limit of an unsigned 64bit integer, we don't actually need to check
  * this.
  */
    return new MaxInclusive(UNSIGNED_LONGLONGVALUE(18446744073709551615));
}

AXIS_CPP_NAMESPACE_END
