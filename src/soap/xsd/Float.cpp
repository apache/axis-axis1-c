#include "Float.hpp"

AXIS_CPP_NAMESPACE_START

Float::Float():m_Float(NULL)
{
}

Float::~Float()
{
    if (m_Float)
        delete m_Float;
}

AxisChar* Float::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((float*) value);	
}

void* Float::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeFloat(valueAsChar);
}


AxisChar* Float::serialize(const float* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < static_cast<float>(minInclusive->getMinInclusiveAsDouble()) )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", minInclusive->getMinInclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
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
        if ( *value <= static_cast<float>(minExclusive->getMinExclusiveAsDouble()) )
        {
            AxisString exceptionMessage =
            "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", minExclusive->getMinExclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
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
        if ( *value > static_cast<float>(maxInclusive->getMaxInclusiveAsDouble()) )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than MaxInclusive specified for this type.  MaxInclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", maxInclusive->getMaxInclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
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
        if ( *value >= static_cast<float>(maxExclusive->getMaxExclusiveAsDouble()) )
        {
            AxisString exceptionMessage =
            "Value to be serialized is greater than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
            AxisChar* length = new AxisChar[25];
            sprintf(length, "%f", maxExclusive->getMaxExclusiveAsDouble());
            exceptionMessage += length;
            exceptionMessage += ", Value = ";
            sprintf(length, "%f", *value);
            exceptionMessage += length;
            exceptionMessage += ".";
            delete [] length;
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxExclusive;

    AxisChar* serializedValue = new char[80];
    AxisSprintf (serializedValue, 80, "%f", *value);
  
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
    return m_Buf;
}

float* Float::deserializeFloat(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
        if (m_Float)
        {
            delete m_Float;
            m_Float = NULL;
        }
	m_Float = new float;
	*m_Float = (float) strtod (valueAsChar, &end);
	
	return m_Float;
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

