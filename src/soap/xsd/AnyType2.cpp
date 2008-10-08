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

#include "AnyType2.hpp"

AXIS_CPP_NAMESPACE_START

AnyType2::AnyType2()
{
}

AnyType2::AnyType2(const xsd__anyType value)
{
        if (value)
        {
            setNil(false);
            serialize(value);
        }
}

XSDTYPE AnyType2::getType()
{
    return XSD_ANYTYPE;
}

xsd__anyType AnyType2::getAnyType()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeAnyType(m_Buf);
    }
}

void * AnyType2::getValue()
{
    return (void*) getAnyType();
}

AxisChar* AnyType2::serialize(const xsd__anyType value) throw (AxisSoapException)
{
    MinLength* minLength= getMinLength();
    if (minLength->isSet())
    {
        if (strlen(value) < (unsigned int) minLength->getMinLength())
        {
            AxisString exceptionMessage =
            "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
            AxisChar length[100];
            sprintf(length, "%d", minLength->getMinLength());
            exceptionMessage += length;
            exceptionMessage += ", Length of value = ";
            sprintf(length, "%d", strlen(value));
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete minLength;
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
            AxisChar length[100];
            sprintf(length, "%d", maxLength->getMaxLength());
            exceptionMessage += length;
            exceptionMessage += ", Length of value = ";
            sprintf(length, "%d", strlen(value));
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete maxLength;
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
            AxisChar lengthAsString[100];
            sprintf(lengthAsString, "%d", length->getLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", strlen(value));
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";
            
            delete length;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete length;

    IAnySimpleType::serialize(value);
    return m_Buf;
}

xsd__anyType AnyType2::deserializeAnyType(const AxisChar* valueAsChar) throw (AxisSoapException)
{

	xsd__anyType value = new char[strlen (valueAsChar) + 1];
	strcpy (value, valueAsChar);
	return value;
}

MinLength* AnyType2::getMinLength()
{
    return new MinLength();
}

MaxLength* AnyType2::getMaxLength()
{
    return new MaxLength();
}

Length* AnyType2::getLength()
{
    return new Length();
}

AXIS_CPP_NAMESPACE_END
