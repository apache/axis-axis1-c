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

#include "../../platforms/PlatformAutoSense.hpp"

#include "Long.hpp"

AXIS_CPP_NAMESPACE_START

Long::Long()
{
}

Long::~Long()
{
}

Long::Long(const xsd__long* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE Long::getType()
{
    return XSD_LONG;
}

xsd__long* Long::getLong()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeLong(m_Buf);
    }
}

void * Long::getValue()
{
    return (void*) getLong();
}

AxisChar* Long::serialize(const xsd__long* value) throw (AxisSoapException)
{
    xsd__integer valueAsLong = static_cast<xsd__integer>(*value);
    return Integer::serialize(&valueAsLong);
}

xsd__long* Long::deserializeLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__integer* returnValue = Integer::deserializeInteger(valueAsChar);
 
    xsd__long * value = new xsd__long;
    *value = static_cast<xsd__long> (*returnValue);
    delete returnValue; 
    return value;
}

MinInclusive* Long::getMinInclusive()
{    
    LONGLONG minInclusive = (-LONGLONGVALUE(9223372036854775807) - LONGLONGVALUE(1));
    return new MinInclusive(minInclusive);
}

MaxInclusive* Long::getMaxInclusive()
{   
    LONGLONG maxInclusive = LONGLONGVALUE(9223372036854775807);
    return new MaxInclusive(maxInclusive);
}

AXIS_CPP_NAMESPACE_END
