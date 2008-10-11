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

#include "Int.hpp"

AXIS_CPP_NAMESPACE_START

Int::Int()
{
}

Int::~Int()
{
}

Int::Int(const xsd__int* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE Int::getType()
{
    return XSD_INT;
}

xsd__int* Int::getInt()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeInt(m_Buf);
    }
}

void * Int::getValue()
{
    return (void*) getInt();
}

AxisChar* Int::serialize(const xsd__int* value) throw (AxisSoapException)
{
    xsd__long valueAsLong = static_cast<xsd__long>(*value);
    return Long::serialize(&valueAsLong);
}

xsd__int* Int::deserializeInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__long* returnValue = Long::deserializeLong(valueAsChar);
 
    xsd__int * value = new xsd__int;
    *value = static_cast<xsd__int> (*returnValue);

    delete returnValue;
    return value;
}

MinInclusive* Int::getMinInclusive()
{   
    LONGLONG minInclusive = -LONGLONGVALUE(2147483648);
    
    return new MinInclusive(minInclusive);
}

MinExclusive* Int::getMinExclusive()
{   
    LONGLONG minExclusive = -LONGLONGVALUE(2147483649);

    return new MinExclusive(minExclusive);
}

MaxInclusive* Int::getMaxInclusive()
{   
    LONGLONG maxInclusive = LONGLONGVALUE(2147483647);
    
    return new MaxInclusive(maxInclusive);
}

MaxExclusive* Int::getMaxExclusive()
{   
    LONGLONG maxExclusive = LONGLONGVALUE(2147483648);
    
    return new MaxExclusive(maxExclusive);
}

AXIS_CPP_NAMESPACE_END
