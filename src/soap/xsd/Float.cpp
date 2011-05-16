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

#include "Float.hpp"

AXIS_CPP_NAMESPACE_START

Float::Float()
{
}

Float::Float(const xsd__float* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

Float::~Float()
{
}

XSDTYPE Float::getType()
{
    return XSD_FLOAT;
}

xsd__float* Float::getFloat()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeFloat(m_Buf);
    }
}

void * Float::getValue()
{
    return (void*) getFloat();
}

AxisChar* Float::serialize(const xsd__float* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
        if ( *value < static_cast<float>(minInclusive->getMinInclusiveAsDouble()) )
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
        if ( *value <= static_cast<float>(minExclusive->getMinExclusiveAsDouble()) )
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
    {
        if ( *value > static_cast<float>(maxInclusive->getMaxInclusiveAsDouble()) )
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
    }
    delete maxInclusive;
 
    MaxExclusive* maxExclusive = getMaxExclusive();
    if (maxExclusive->isSet())
        if ( *value >= static_cast<float>(maxExclusive->getMaxExclusiveAsDouble()) )
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

    AxisChar serializedValue[80];
    AxisSprintf (serializedValue, 80, "%.6g", *value);

    // When sending decimal, double, or float, the decimal point character must be a period.
    if (PLATFORM_PROCESS_DECIMAL_POINT_C != '.')
    {
        char *p = serializedValue;
        while (*p)
        {
            if (*p == PLATFORM_PROCESS_DECIMAL_POINT_C)
            {
                *p = '.';
                break;
            }
            p++;
        }
    }
  
    IAnySimpleType::serialize(serializedValue);
    return m_Buf;
}

xsd__float* Float::deserializeFloat(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
    bool decimalPointChanged = false;

    // When sending decimal, double, or float, the decimal point character must be a period.
    // However, strtod is locale-sensitive, so that for it to function properly the decimal point
    // must be set to whatever the locale decimal point is.
    AxisChar *p = NULL;
    if (valueAsChar != NULL && PLATFORM_PROCESS_DECIMAL_POINT_C != '.')
    {
        p = (AxisChar *)valueAsChar;
        while (*p)
        {
            if (*p == '.')
            {
                decimalPointChanged = true;
                *p = PLATFORM_PROCESS_DECIMAL_POINT_C;
                break;
            }
            p++;
        }
    }

	xsd__float * value = new xsd__float;
	*value = (xsd__float) strtod (valueAsChar, &end);

    if (decimalPointChanged)
        *p = '.';

	return value;
}

WhiteSpace* Float::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

MinInclusive* Float::getMinInclusive()
{
    return new MinInclusive();
}

MinExclusive* Float::getMinExclusive()
{
    return new MinExclusive();
}

MaxInclusive* Float::getMaxInclusive()
{
    return new MaxInclusive();
}

MaxExclusive* Float::getMaxExclusive()
{
    return new MaxExclusive();
}

AXIS_CPP_NAMESPACE_END

