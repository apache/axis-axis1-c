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

#include "NonNegativeInteger.hpp"

AXIS_CPP_NAMESPACE_START

NonNegativeInteger::NonNegativeInteger()
{
}

NonNegativeInteger::NonNegativeInteger(const xsd__nonNegativeInteger* value) throw (AxisSoapException)
{
    if (value)
    {
        if((*value) < 0) // the value must be non negative, hence validate and fix
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR, "NonNegativeInteger value must be non negative");
        setNil(false);
        serialize(value);
    }
}

NonNegativeInteger::~NonNegativeInteger()
{
}

XSDTYPE NonNegativeInteger::getType()
{
    return XSD_NONNEGATIVEINTEGER;
}

xsd__nonNegativeInteger* NonNegativeInteger::getNonNegativeInteger()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeNonNegativeInteger(m_Buf);
    }
}

void * NonNegativeInteger::getValue()
{
    return (void*) getNonNegativeInteger();
}

AxisChar* NonNegativeInteger::serialize(const xsd__nonNegativeInteger* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < minInclusive->getMinInclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, minInclusive->getMinInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete minInclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete minInclusive;

    MinExclusive* minExclusive = getMinExclusive();
    if (minExclusive->isSet())
    {
        if ( *value <= minExclusive->getMinExclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, minExclusive->getMinExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete minExclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete minExclusive;

    MaxInclusive* maxInclusive = getMaxInclusive();
    if (maxInclusive->isSet())
    {
        if ( *value > maxInclusive->getMaxInclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, maxInclusive->getMaxInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete maxInclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxInclusive;

    MaxExclusive* maxExclusive = getMaxExclusive();
    if (maxExclusive->isSet())
    {
        if ( *value >= maxExclusive->getMaxExclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, maxExclusive->getMaxExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete maxExclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxExclusive;

    AxisString formatSpecifier = "%";
    
    int valueSize = 80;
    TotalDigits* totalDigits = getTotalDigits();
    if (totalDigits->isSet())
    {
        valueSize = totalDigits->getTotalDigits() + 1;
        AxisChar digits[10];
        AxisSprintf (digits, 10, "%i", totalDigits->getTotalDigits());
        formatSpecifier += digits;
    }
    delete totalDigits;
    
    formatSpecifier += PRINTF_UNSIGNED_LONGLONG_FORMAT_SPECIFIER_CHARS;

    AxisChar* serializedValue = new char[valueSize];
    AxisSprintf (serializedValue, valueSize, formatSpecifier.c_str(), *value);
  
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    return m_Buf;
}

xsd__nonNegativeInteger* NonNegativeInteger::deserializeNonNegativeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__nonNegativeInteger * value = new xsd__nonNegativeInteger;
    *value = 0;
    AxisChar currentNumber[] = {'\0', '\0'};
    int stringLength = strlen(valueAsChar);
    
    if (stringLength > 0)
    {
        int count = 0;
        
        for ( ; count < stringLength ;  count ++)
        {
            *value *= 10;
    		currentNumber[0] = valueAsChar[count];
            *value += atoi(currentNumber);
        }
    }

    return value;
}

MinInclusive* NonNegativeInteger::getMinInclusive()
{   
    return new MinInclusive((unsigned LONGLONG) 0);
}

AXIS_CPP_NAMESPACE_END
