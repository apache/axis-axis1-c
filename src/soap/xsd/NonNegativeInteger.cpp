#include "NonNegativeInteger.hpp"

AXIS_CPP_NAMESPACE_START

NonNegativeInteger::NonNegativeInteger():m_NonNegativeInteger(NULL)
{
}

NonNegativeInteger::~NonNegativeInteger()
{
    if (m_NonNegativeInteger)
        delete m_NonNegativeInteger;
}

AxisChar* NonNegativeInteger::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((unsigned LONGLONG*) value);  
}

void* NonNegativeInteger::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
   return (void*) deserializeNonNegativeInteger(valueAsChar);
}


AxisChar* NonNegativeInteger::serialize(const unsigned LONGLONG* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < minInclusive->getMinInclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minInclusive->getMinInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minExclusive->getMinExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxInclusive->getMaxInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxExclusive->getMaxExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
        AxisChar* digits = new char[10];
        AxisSprintf (digits, 10, "%i", totalDigits->getTotalDigits());
        formatSpecifier += digits;
        delete [] digits;
    }
    delete totalDigits;
    
    formatSpecifier += PRINTF_LONGLONG_FORMAT_SPECIFIER_CHARS;

    AxisChar* serializedValue = new char[valueSize];
    AxisSprintf (serializedValue, valueSize, formatSpecifier.c_str(), *value);
  
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    return m_Buf;
}

unsigned LONGLONG* NonNegativeInteger::deserializeNonNegativeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    AxisChar* end;
    
    if(m_NonNegativeInteger)
    {
        delete m_NonNegativeInteger;
        m_NonNegativeInteger = NULL;
    }
    m_NonNegativeInteger = new unsigned LONGLONG;
    *m_NonNegativeInteger = strtol (valueAsChar, &end, 10);
  
    return m_NonNegativeInteger;
}

MinInclusive* NonNegativeInteger::getMinInclusive()
{   
    return new MinInclusive((unsigned LONGLONG) 0);
}

AXIS_CPP_NAMESPACE_END
