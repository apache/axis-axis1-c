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

#include "Decimal.hpp"

AXIS_CPP_NAMESPACE_START

Decimal::Decimal()
{
}

Decimal::~Decimal()
{
}

Decimal::Decimal(const xsd__decimal* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE Decimal::getType()
{
    return XSD_DECIMAL;
}

xsd__decimal* Decimal::getDecimal()
{
    if (isNil())
        return NULL;
    else
        return deserializeDecimal(m_Buf);
}

void * Decimal::getValue()
{
    return (void*) getDecimal();
}

AxisChar* Decimal::serialize(const xsd__decimal* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
        if ( *value < minInclusive->getMinInclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar length[100];
            sprintf(length, "%f", minInclusive->getMinInclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete minInclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete minInclusive;

    MinExclusive* minExclusive = getMinExclusive();
    if (minExclusive->isSet())
        if ( *value <= minExclusive->getMinExclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar length[100];
            sprintf(length, "%f", minExclusive->getMinExclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete minExclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete minExclusive;


    MaxInclusive* maxInclusive = getMaxInclusive();
    if (maxInclusive->isSet())
        if ( *value > maxInclusive->getMaxInclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar length[100];
            sprintf(length, "%f", maxInclusive->getMaxInclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete maxInclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete maxInclusive;

    MaxExclusive* maxExclusive = getMaxExclusive();
    if (maxExclusive->isSet())
        if ( *value >= maxExclusive->getMaxExclusiveAsDouble() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar length[100];
            sprintf(length, "%f", maxExclusive->getMaxExclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete maxExclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete maxExclusive;


    AxisString formatSpecifier = "%";
    
    int valueSize = 80;
    TotalDigits* totalDigits = getTotalDigits();
    if (totalDigits->isSet())
    {
        valueSize = totalDigits->getTotalDigits() + 1;
        AxisChar digits[100];
        AxisSprintf (digits, 10, "%i", totalDigits->getTotalDigits());
        formatSpecifier += digits;
    }
    delete totalDigits;
    
    FractionDigits* fractionDigits = getFractionDigits();
    if (fractionDigits->isSet())
    {
        formatSpecifier += ".";
        AxisChar digits[100];
        AxisSprintf (digits, 10, "%i", fractionDigits->getFractionDigits());
        formatSpecifier += digits;
    }
    delete fractionDigits;
    
    formatSpecifier += "f";

    AxisChar* serializedValue = new char[valueSize];
    AxisSprintf (serializedValue, valueSize, formatSpecifier.c_str(), *value);
    
	
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    return m_Buf;
}

xsd__decimal* Decimal::deserializeDecimal(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
   
	xsd__decimal * value = new xsd__decimal;
	*value = strtod (valueAsChar, &end);
	
	return value;
}

WhiteSpace* Decimal::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

MinInclusive* Decimal::getMinInclusive()
{
    return new MinInclusive();
}

MinExclusive* Decimal::getMinExclusive()
{
    return new MinExclusive();
}

MaxInclusive* Decimal::getMaxInclusive()
{
    return new MaxInclusive();
}

MaxExclusive* Decimal::getMaxExclusive()
{
    return new MaxExclusive();
}

TotalDigits* Decimal::getTotalDigits()
{
    return new TotalDigits();
}

FractionDigits* Decimal::getFractionDigits()
{
    return new FractionDigits();
}

AXIS_CPP_NAMESPACE_END
