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

#include "Boolean.hpp"

AXIS_CPP_NAMESPACE_START

Boolean::Boolean():m_Boolean(NULL)
{
}

Boolean::Boolean(const xsd__boolean* value):m_Boolean(NULL)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

Boolean::~Boolean()
{
}

XSDTYPE Boolean::getType()
{
    return XSD_BOOLEAN;
}

/**
 * Deserialize value from it's on-the-wire string form.
 * @param valueAsChar Serialized form of value.
 * @return Deserialized value.
 */
void* Boolean::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeBoolean(valueAsChar);
}

/**
 * Serialize boolean value to it's on-the-wire string form.
 * @param value The boolean value to be serialized.
 * @return Serialized form of boolean value.
 */
AxisChar* Boolean::serialize(const xsd__boolean * value) throw (AxisSoapException)
{
    AxisChar* serializedValue = new char[6];
	AxisSprintf (serializedValue, 6, "%s",
            (*((int *) (value)) == false_) ? "false" : "true");
    
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    return m_Buf;
}

/**
 * Deserialize boolean value from it's on-the-wire string form.
 * @param valueAsChar Serialized form of boolean value.
 * @return Deserialized boolean value.
 */
xsd__boolean * Boolean::deserializeBoolean(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    if(m_Boolean)
    {
        delete m_Boolean;
        m_Boolean = NULL;
    }
    m_Boolean = new xsd__boolean;
 
	if ( 0 == strcmp (valueAsChar, "true") || 0 == strcmp (valueAsChar, "1"))
	{
		*m_Boolean = true_;
	}
	else
	{
		*m_Boolean =  false_;
	}
    
    return m_Boolean;
}

WhiteSpace* Boolean::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

Enumeration* Boolean::getEnumeration()
{
    static AxisChar* BooleanEnumerationValue1 = "true";
    static AxisChar* BooleanEnumerationValue2 = "false";
    static AxisChar* BooleanEnumerationValue3 = "1";
    static AxisChar* BooleanEnumerationValue4 = "0";
    AxisChar* enumerationValues[] = 
        {
         BooleanEnumerationValue1,
         BooleanEnumerationValue2,
         BooleanEnumerationValue3,
         BooleanEnumerationValue4
        };
    return new Enumeration(enumerationValues, sizeof(enumerationValues)/sizeof(AxisChar*));
}

AXIS_CPP_NAMESPACE_END
