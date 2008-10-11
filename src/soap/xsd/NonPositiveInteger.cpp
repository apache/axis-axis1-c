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

#include "NonPositiveInteger.hpp"

AXIS_CPP_NAMESPACE_START

NonPositiveInteger::NonPositiveInteger()
{
}

NonPositiveInteger::NonPositiveInteger(const xsd__nonPositiveInteger* value) throw (AxisSoapException)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}


NonPositiveInteger::~NonPositiveInteger()
{
}

XSDTYPE NonPositiveInteger::getType()
{
    return XSD_NONPOSITIVEINTEGER;
}

xsd__nonPositiveInteger* NonPositiveInteger::getNonPositiveInteger()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeNonPositiveInteger(m_Buf);
    }
}

void * NonPositiveInteger::getValue()
{
    return (void*) getNonPositiveInteger();
}

xsd__nonPositiveInteger* NonPositiveInteger::deserializeNonPositiveInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (xsd__negativeInteger*) deserializeInteger(valueAsChar);
}

MaxInclusive* NonPositiveInteger::getMaxInclusive()
{   
    return new MaxInclusive((LONGLONG) 0);
}

AXIS_CPP_NAMESPACE_END
