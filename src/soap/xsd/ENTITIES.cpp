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

#include "ENTITIES.hpp"

AXIS_CPP_NAMESPACE_START

ENTITIES::ENTITIES()
{}

ENTITIES::ENTITIES(const xsd__ENTITIES value)
{
	if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE ENTITIES::getType()
{
    return XSD_ENTITIES;
}

xsd__ENTITIES ENTITIES::getENTITIES()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeENTITIES(m_Buf);
    }
}

void * ENTITIES::getValue()
{
    return (void*) getENTITIES();
}

xsd__ENTITIES ENTITIES::deserializeENTITIES(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (xsd__ENTITIES) deserializeENTITY(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
