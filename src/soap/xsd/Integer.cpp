#include "Integer.hpp"

AXIS_CPP_NAMESPACE_START

Integer::Integer():m_Integer(NULL)
{
}

Integer::~Integer()
{
    if (m_Integer)
        delete m_Integer;
}

AxisChar* Integer::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((LONGLONG*) value);  
}

void* Integer::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
   return (void*) deserializeInteger(valueAsChar);
}


AxisChar* Integer::serialize(const LONGLONG* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < minInclusive->getMinInclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minInclusive->getMinInclusiveAsLONGLONG());
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
        if ( *value <= minExclusive->getMinExclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minExclusive->getMinExclusiveAsLONGLONG());
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
        if ( *value > maxInclusive->getMaxInclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxInclusive->getMaxInclusiveAsLONGLONG());
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
        if ( *value >= maxExclusive->getMaxExclusiveAsLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxExclusive->getMaxExclusiveAsLONGLONG());
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

LONGLONG* Integer::deserializeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    AxisChar* end;
    
    if(m_Integer)
    {
        delete m_Integer;
        m_Integer = NULL;
    }
    m_Integer = new LONGLONG;
    *m_Integer = strtol (valueAsChar, &end, 10);
  
    return m_Integer;
}

FractionDigits* Integer::getFractionDigits()
{
    return new FractionDigits(0);
}

AXIS_CPP_NAMESPACE_END
