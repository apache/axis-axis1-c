#include "NonPositiveInteger.hpp"

AXIS_CPP_NAMESPACE_START

NonPositiveInteger::NonPositiveInteger():m_NonPositiveInteger(NULL)
{
}

NonPositiveInteger::~NonPositiveInteger()
{
    if (m_NonPositiveInteger)
        delete m_NonPositiveInteger;
}

AxisChar* NonPositiveInteger::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((unsigned LONGLONG*) value);  
}

void* NonPositiveInteger::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
   return (void*) deserializeNonPositiveInteger(valueAsChar);
}


AxisChar* NonPositiveInteger::serialize(const unsigned LONGLONG* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value > minInclusive->getMinInclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = -";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minInclusive->getMinInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = -";
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
        if ( *value >= minExclusive->getMinExclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = -";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, minExclusive->getMinExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = -";
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
        if ( *value < maxInclusive->getMaxInclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MaxInclusive specified for this type.  MaxInclusive = -";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxInclusive->getMaxInclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = -";
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
        if ( *value <= maxExclusive->getMaxExclusiveAsUnsignedLONGLONG() )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MaxExclusive specified for this type.  MaxExclusive = -";
            AxisChar* length = new AxisChar[25];
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, maxExclusive->getMaxExclusiveAsUnsignedLONGLONG());
            exceptionMessage += length;
            exceptionMessage += ", Value = -";
            sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxExclusive;
    

    AxisChar* serializedValue = new char[80];
    AxisSprintf (serializedValue, 80, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);

    if(*value != 0)
    {
        AxisString serializingString = "-";
        serializingString += serializedValue;
        
        serializedValue = const_cast<AxisChar*>(serializingString.c_str());
    }
  
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    return m_Buf;
}

unsigned LONGLONG* NonPositiveInteger::deserializeNonPositiveInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    AxisChar* end;
    
    if(m_NonPositiveInteger)
    {
        delete m_NonPositiveInteger;
        m_NonPositiveInteger = NULL;
    }
    
    m_NonPositiveInteger = new unsigned LONGLONG;
    if (*valueAsChar == '-')
    {
        const AxisChar* tempVar = valueAsChar + 1;
        *m_NonPositiveInteger = strtol (tempVar, &end, 10);
    }
    else
    {
        
        *m_NonPositiveInteger = strtol (valueAsChar, &end, 10);
    }
  
    return m_NonPositiveInteger;
}

MaxInclusive* NonPositiveInteger::getMaxInclusive()
{   
    return new MaxInclusive((unsigned LONGLONG) 0);
}

AXIS_CPP_NAMESPACE_END
