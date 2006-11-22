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

#include "AnyURI.hpp"

AXIS_CPP_NAMESPACE_START

AnyURI::AnyURI()
{
}

AnyURI::AnyURI(const xsd__anyURI value)
{
    if (value)
    {
        setNil(false);            
        serialize(value);
    }
}

XSDTYPE AnyURI::getType()
{
    return XSD_ANYURI;
}

xsd__anyURI AnyURI::getAnyURI()
{
    if (isNil())
        return NULL;
    else
        return deserializeAnyURI(m_Buf);
}

void * AnyURI::getValue()
{
    return (void*) getAnyURI();
}

AxisChar* AnyURI::serialize(const xsd__anyURI value) throw (AxisSoapException)
{
    AxisString exceptionMessage;
    char lengthAsString[100];
    
    MinLength* minLength= getMinLength();
    if (minLength->isSet())
        if (strlen(value) < (unsigned int) minLength->getMinLength())
        {
            exceptionMessage =
            "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
            sprintf(lengthAsString, "%d", minLength->getMinLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", strlen(value));
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";
            
            delete minLength;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete minLength;
    
    MaxLength* maxLength = getMaxLength();
    if (maxLength->isSet())
        if (strlen(value) > (unsigned int) maxLength->getMaxLength())
        {
            exceptionMessage =
            "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
            sprintf(lengthAsString, "%d", maxLength->getMaxLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", strlen(value));
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";
            
            delete maxLength;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete maxLength;

    Length* length = getLength();
    if (length->isSet())
        if (strlen(value) != (unsigned int) length->getLength())
        {
            exceptionMessage =
            "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
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
    delete length;
         
	AxisString valueAsString = value;
	AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();
	
    IAnySimpleType::serialize(serializedValue);

	return m_Buf;
}

xsd__anyURI AnyURI::deserializeAnyURI(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__anyURI value = new char[strlen (valueAsChar) + 1];
	strcpy (value, valueAsChar);
	return value;
}

WhiteSpace* AnyURI::getWhiteSpace()
{
    return new WhiteSpace(REPLACE);
}

MinLength* AnyURI::getMinLength()
{
    return new MinLength();
}

MaxLength* AnyURI::getMaxLength()
{
    return new MaxLength();
}

Length* AnyURI::getLength()
{
    return new Length();
}

AXIS_CPP_NAMESPACE_END
