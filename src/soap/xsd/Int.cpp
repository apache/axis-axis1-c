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

#include "Int.hpp"

AXIS_CPP_NAMESPACE_START

Int::Int():m_Int(NULL)
{
}

Int::~Int()
{
}

AxisChar* Int::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__int*) value);
}

void* Int::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeInt(valueAsChar);
}

AxisChar* Int::serialize(const xsd__int* value) throw (AxisSoapException)
{
    xsd__long valueAsLong = static_cast<xsd__long>(*value);
    return Long::serialize(&valueAsLong);
}

xsd__int* Int::deserializeInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__long* returnValue = Long::deserializeLong(valueAsChar);
 
    if(m_Int)
    {
        delete m_Int;
        m_Int = NULL;
    }
    m_Int = new xsd__int;
    *m_Int = static_cast<xsd__int> (*returnValue);
    delete returnValue; // Samissa - need to clean this memory
    return m_Int;
}

MinInclusive* Int::getMinInclusive()
{   
  AxisChar* end;    
  LONGLONG* minInclusive = new LONGLONG;
  *minInclusive = strtol ("-2147483648", &end, 10);
    
    MinInclusive* retVal = new MinInclusive(*minInclusive);
    delete minInclusive;
    return retVal;
}

MinExclusive* Int::getMinExclusive()
{   
  AxisChar* end;    
  LONGLONG* minExclusive = new LONGLONG;
  *minExclusive = strtol ("-2147483649", &end, 10);

    MinExclusive* retVal = new MinExclusive(*minExclusive);
    delete minExclusive;
    return retVal;
}

MaxInclusive* Int::getMaxInclusive()
{   
  AxisChar* end;    
  LONGLONG* maxInclusive = new LONGLONG;
  *maxInclusive = strtol ("2147483647", &end, 10);
    
    MaxInclusive* retVal = new MaxInclusive(*maxInclusive);
    delete maxInclusive;
    return retVal;
}

MaxExclusive* Int::getMaxExclusive()
{   
  AxisChar* end;    
  LONGLONG* maxExclusive = new LONGLONG;
  *maxExclusive = strtol ("2147483648", &end, 10);
    
    MaxExclusive* retVal = new MaxExclusive(*maxExclusive);
    delete maxExclusive;
    return retVal;
}

AXIS_CPP_NAMESPACE_END
