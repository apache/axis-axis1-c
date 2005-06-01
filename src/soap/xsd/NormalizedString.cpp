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

#include "NormalizedString.hpp"

AXIS_CPP_NAMESPACE_START

NormalizedString::NormalizedString()
{}

NormalizedString::NormalizedString(const xsd__normalizedString value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE NormalizedString::getType()
{
    return XSD_NORMALIZEDSTRING;
}

xsd__normalizedString NormalizedString::getNormalizedString()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeNormalizedString(m_Buf);
    }
}

void * NormalizedString::getValue()
{
    return (void*) getNormalizedString();
}

xsd__normalizedString NormalizedString::deserializeNormalizedString(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (xsd__normalizedString) deserializeString(valueAsChar);
}

WhiteSpace* NormalizedString::getWhiteSpace()
{
    return new WhiteSpace(REPLACE);
}

AXIS_CPP_NAMESPACE_END
