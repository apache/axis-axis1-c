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

#include "Short.hpp"

AXIS_CPP_NAMESPACE_START

Short::Short():m_Short(NULL)
{
}

Short::~Short()
{
}

AxisChar* Short::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__short*) value);
}

void* Short::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeShort(valueAsChar);
}

AxisChar* Short::serialize(const xsd__short* value) throw (AxisSoapException)
{
    xsd__int valueAsInt = static_cast<xsd__int>(*value);
    return Int::serialize(&valueAsInt);
}

xsd__short* Short::deserializeShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__int* returnValue = Int::deserializeInt(valueAsChar);
 
    if(m_Short)
    {
        delete m_Short;
        m_Short = NULL;
    }
    m_Short = new xsd__short;
    *m_Short = static_cast<xsd__short> (*returnValue);
    delete returnValue; // Samissa - need to clean this memory
    return m_Short;
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
