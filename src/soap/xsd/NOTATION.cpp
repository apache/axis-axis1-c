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

#include "NOTATION.hpp"

AXIS_CPP_NAMESPACE_START

NOTATION::NOTATION():m_NOTATION(NULL)
{
}

NOTATION::NOTATION(const xsd__notation value):m_NOTATION(NULL)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE NOTATION::getType()
{
    return XSD_NOTATION;
}

void* NOTATION::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeNOTATION(valueAsChar);
}

AxisChar* NOTATION::serialize(const xsd__notation value) throw (AxisSoapException)
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

xsd__notation NOTATION::deserializeNOTATION(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    if (m_NOTATION)
    {
        delete [] m_NOTATION;
        m_NOTATION = NULL;
    }
	m_NOTATION = new char[strlen (valueAsChar) + 1];
	strcpy (m_NOTATION, valueAsChar);
	return m_NOTATION;
}

WhiteSpace* NOTATION::getWhiteSpace()
{
    return new WhiteSpace(REPLACE);
}

MinLength* NOTATION::getMinLength()
{
    return new MinLength();
}

MaxLength* NOTATION::getMaxLength()
{
    return new MaxLength();
}

Length* NOTATION::getLength()
{
    return new Length();
}

AXIS_CPP_NAMESPACE_END
