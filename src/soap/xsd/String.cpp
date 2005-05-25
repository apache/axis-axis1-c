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

#include "String.hpp"

AXIS_CPP_NAMESPACE_START

String::String():m_String(NULL)
{
}

String::String(const xsd__string value):m_String(NULL)
{
        if (value)
        {
            setNil(false);
            serialize(value);
        }
}

XSDTYPE String::getType()
{
    return XSD_STRING;
}

void* String::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeString(valueAsChar);
}

AxisChar* String::serialize(const xsd__string value) throw (AxisSoapException)
{
    MinLength* minLength= getMinLength();
    if (minLength->isSet())
    {
        if (strlen(value) < (unsigned int) minLength->getMinLength())
        {
            AxisString exceptionMessage =
            "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
            AxisChar* length = new AxisChar[10];
            sprintf(length, "%d", minLength->getMinLength());
            exceptionMessage += length;
            exceptionMessage += ", Length of value = ";
            sprintf(length, "%d", strlen(value));
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete minLength;
    
    MaxLength* maxLength = getMaxLength();
    if (maxLength->isSet())
    {
        if (strlen(value) > (unsigned int) maxLength->getMaxLength())
        {
            AxisString exceptionMessage =
            "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
            AxisChar* length = new AxisChar[10];
            sprintf(length, "%d", maxLength->getMaxLength());
            exceptionMessage += length;
            exceptionMessage += ", Length of value = ";
            sprintf(length, "%d", strlen(value));
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxLength;

    Length* length = getLength();
    if (length->isSet())
    {
        if (strlen(value) != (unsigned int) length->getLength())
        {
            AxisString exceptionMessage =
            "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
            AxisChar* lengthAsString = new AxisChar[10];
            sprintf(lengthAsString, "%d", length->getLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", strlen(value));
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";
            delete [] lengthAsString;
            
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete length;
 
	AxisString valueAsString = value;
	AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();

    IAnySimpleType::serialize(serializedValue);
    return m_Buf;
}

xsd__string String::deserializeString(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    if (m_String)
    {
        delete [] m_String;
        m_String = NULL;
    }
	m_String = new char[strlen (valueAsChar) + 1];
	strcpy (m_String, valueAsChar);
	return m_String;
}

MinLength* String::getMinLength()
{
    return new MinLength();
}

MaxLength* String::getMaxLength()
{
    return new MaxLength();
}

Length* String::getLength()
{
    return new Length();
}

AXIS_CPP_NAMESPACE_END
