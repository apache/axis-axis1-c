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

#include "NMTOKENS.hpp"

AXIS_CPP_NAMESPACE_START

NMTOKENS::NMTOKENS()
{}

NMTOKENS::NMTOKENS(const xsd__NMTOKENS value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE NMTOKENS::getType()
{
    return XSD_NMTOKENS;
}

xsd__NMTOKENS NMTOKENS::getNMTOKENS()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeNMTOKENS(m_Buf);
    }
}

void * NMTOKENS::getValue()
{
    return (void*) getNMTOKENS();
}

xsd__NMTOKENS NMTOKENS::deserializeNMTOKENS(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (xsd__NMTOKENS) deserializeNMTOKEN(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
