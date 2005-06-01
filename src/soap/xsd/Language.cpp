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

#include "Language.hpp"

AXIS_CPP_NAMESPACE_START

Language::Language()
{}

Language::Language(const xsd__language value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE Language::getType()
{
    return XSD_LANGUAGE;
}

xsd__language Language::getLanguage()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeLanguage(m_Buf);
    }
}

void * Language::getValue()
{
    return (void*) getLanguage();
}

xsd__language Language::deserializeLanguage(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (xsd__language) deserializeToken(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
