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

#include "Duration.hpp"

AXIS_CPP_NAMESPACE_START

Duration::Duration()
{
}

Duration::Duration(const xsd__duration* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE Duration::getType()
{
    return XSD_DURATION;
}

xsd__duration* Duration::getDuration()
{
    if (isNil())
    {
        return NULL;
    }
    else
    {
        return deserializeDuration(m_Buf);
    }
}

void * Duration::getValue()
{
    return (void*) getDuration();
}

AxisChar* Duration::serialize(const xsd__duration* value) throw (AxisSoapException)
{
 
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
        if ( *value < minInclusive->getMinInclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minInclusive->getMinInclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%ld", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete minInclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete minInclusive;
 
    MinExclusive* minExclusive = getMinExclusive();
    if (minExclusive->isSet())
        if ( *value <= minExclusive->getMinExclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minExclusive->getMinExclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%ld", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete minExclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete minExclusive;


    MaxInclusive* maxInclusive = getMaxInclusive();
    if (maxInclusive->isSet())
        if ( *value > maxInclusive->getMaxInclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxInclusive->getMaxInclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%ld", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete maxInclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete maxInclusive;
 
    MaxExclusive* maxExclusive = getMaxExclusive();
    if (maxExclusive->isSet())
        if ( *value >= maxExclusive->getMaxExclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar length[100];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxExclusive->getMaxExclusiveAsLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%ld", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            
            delete maxExclusive;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete maxExclusive;
 
	long valueToSerialize = *value;
	AxisChar buff[4];
    AxisString serializedValue;
	/*
	 * Duration takes the form:
	 * PnYnMnDTnHnMnS
	 */
    serializedValue = "P";
    
    // Calculate years
    int x = 365 * 24 * 3600;
    int intYears = valueToSerialize / x;
    long tempYears = intYears * x;
    AxisSprintf (buff, 4, "%d", intYears);
    serializedValue.append (buff);
    serializedValue.append ("Y");


	// Calculate Months
    valueToSerialize = valueToSerialize - (tempYears);
    x = 30 * 24 * 3600;
    int intMonths = valueToSerialize / x;
    AxisSprintf (buff, 4, "%d", intMonths);
    serializedValue.append (buff);
    serializedValue.append ("M");

	// Calculate Days
    valueToSerialize = valueToSerialize - (intMonths * x);
    x = 24 * 3600;
    int intDays = valueToSerialize / x;
    AxisSprintf (buff, 4, "%d", intDays);
    serializedValue.append (buff);
    serializedValue.append ("DT");

	// Calculate Hours
    valueToSerialize = valueToSerialize - (intDays * x);
    x = 3600;
    int intHours = valueToSerialize / x;
    AxisSprintf (buff, 4, "%d", intHours);
    serializedValue.append (buff);
    serializedValue.append ("H");

	// Calculate Minutes
    valueToSerialize = valueToSerialize - (intHours * x);
    x = 60;
    int intMins = valueToSerialize / x;
    AxisSprintf (buff, 4, "%d", intMins);
    serializedValue.append (buff);
    serializedValue.append ("M");

	// Calculate Seconds
    int intSecs = valueToSerialize - (intMins * x);
    AxisSprintf (buff, 4, "%d", intSecs);
    serializedValue.append (buff);
    serializedValue.append ("S");

	// Convert from String to Char[]	
	AxisChar* returnValue = (AxisChar*) serializedValue.c_str ();
   
    IAnySimpleType::serialize(returnValue);
	return m_Buf;
}

xsd__duration* Duration::deserializeDuration(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisString valueAsString = valueAsChar;
	AxisString buff;
    unsigned int intPos1, intPos2, intPos3, intPos4, intPos5, intPos6;

    xsd__duration* value = new xsd__duration;

    /*XSD_DURATION is of the format PnYnMnDTnHnMnS */

	// Deserialize Years
	*value = 0;
    intPos1 = valueAsString.find_first_of ("Y");
    buff = valueAsString.substr (1, intPos1 - 1);
    int years = atoi (buff.c_str ());
    *value += years * 365 * 24 * 3600;

	// Deserialize Months
    intPos2 = valueAsString.find_first_of ("M");
    buff = valueAsString.substr (intPos1 + 1, intPos2 - intPos1 - 1);
    int months = atoi (buff.c_str ());
    *value += months * 30 * 24 * 3600;

	// Deserialize Days
    intPos3 = valueAsString.find_first_of ("D");
    buff = valueAsString.substr (intPos2 + 1, intPos3 - intPos2 - 1);
    int days = atoi (buff.c_str ());
    *value += days * 24 * 3600;
    
	// Deserialize Hours
    intPos4 = valueAsString.find_first_of ("H");
    buff = valueAsString.substr (intPos3 + 2, intPos4 - intPos3 - 2);
    int hours = atoi (buff.c_str ());
    *value += hours * 3600;

	// Deserialize Minutes
    intPos5 = valueAsString.find_last_of ("M");
    buff = valueAsString.substr (intPos4 + 1, intPos5 - intPos4 - 1);
    int mins = atoi (buff.c_str ());
    *value += mins * 60;

	// Deserialize Seconds
    intPos6 = valueAsString.find_first_of ("S");
    buff = valueAsString.substr (intPos5 + 1, intPos6 - intPos5 - 1);
    int secs = atoi (buff.c_str ());
    *value += secs;
    
    return value;
}

WhiteSpace* Duration::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

MinInclusive* Duration::getMinInclusive()
{
    return new MinInclusive();
}

MinExclusive* Duration::getMinExclusive()
{
    return new MinExclusive();
}

MaxInclusive* Duration::getMaxInclusive()
{
    return new MaxInclusive();
}

MaxExclusive* Duration::getMaxExclusive()
{
    return new MaxExclusive();
}
    
AXIS_CPP_NAMESPACE_END
