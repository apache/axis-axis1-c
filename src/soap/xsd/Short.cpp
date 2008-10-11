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

#include "Short.hpp"

AXIS_CPP_NAMESPACE_START

Short::Short()
{
}

Short::~Short()
{
}

Short::Short(const xsd__short* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE Short::getType()
{
    return XSD_SHORT;
}

xsd__short* Short::getShort()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeShort(m_Buf);
    }
}

void * Short::getValue()
{
    return (void*) getShort();
}

AxisChar* Short::serialize(const xsd__short* value) throw (AxisSoapException)
{
    xsd__int valueAsInt = static_cast<xsd__int>(*value);
    return Int::serialize(&valueAsInt);
}

xsd__short* Short::deserializeShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__int* returnValue = Int::deserializeInt(valueAsChar);
 
    xsd__short * value = new xsd__short;
    *value = static_cast<xsd__short> (*returnValue);
    delete returnValue; 
    return value;
}

MinInclusive* Short::getMinInclusive()
{
    return new MinInclusive(static_cast<LONGLONG>(-32768));
}

MinExclusive* Short::getMinExclusive()
{
    return new MinExclusive(static_cast<LONGLONG>(-32769));
}

MaxInclusive* Short::getMaxInclusive()
{
    return new MaxInclusive(static_cast<LONGLONG>(32767));
}

MaxExclusive* Short::getMaxExclusive()
{
    return new MaxExclusive(static_cast<LONGLONG>(32768));
}

AXIS_CPP_NAMESPACE_END
