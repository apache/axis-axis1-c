#include "Double.hpp"

AXIS_CPP_NAMESPACE_START

Double::Double():m_Double(NULL)
{
}

AxisChar* Double::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((double*) value);	
}

void* Double::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeDouble(valueAsChar);
}


AxisChar* Double::serialize(const double* value) throw (AxisSoapException)
{
    MinInclusive* minInclusive = getMinInclusive();
    if (minInclusive->isSet())
    {
        if ( *value < minInclusive->getMinInclusiveAsDouble() )
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
        if ( *value < minExclusive->getMinExclusiveAsDouble() )
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
        if ( *value < maxInclusive->getMaxInclusiveAsDouble() )
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
        if ( *value < maxExclusive->getMaxExclusiveAsDouble() )
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

double* Double::deserializeDouble(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
   
    if (m_Double)
    {
        delete m_Double;
        m_Double = NULL;
    }
	m_Double = new double;
	*m_Double = strtod (valueAsChar, &end);
	
	return m_Double;
}

WhiteSpace* Double::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

MinInclusive* Double::getMinInclusive()
{
    return new MinInclusive();
}

MinExclusive* Double::getMinExclusive()
{
    return new MinExclusive();
}

MaxInclusive* Double::getMaxInclusive()
{
    return new MaxInclusive();
}

MaxExclusive* Double::getMaxExclusive()
{
    return new MaxExclusive();
}

AXIS_CPP_NAMESPACE_END
