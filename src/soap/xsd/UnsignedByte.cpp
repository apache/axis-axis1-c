#include "UnsignedByte.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedByte::UnsignedByte():m_UnsignedByte(NULL)
{
}

UnsignedByte::~UnsignedByte()
{
}

AxisChar* UnsignedByte::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__unsignedByte*) value);
}

void* UnsignedByte::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedByte(valueAsChar);
}

AxisChar* UnsignedByte::serialize(const xsd__unsignedByte* value) throw (AxisSoapException)
{
    xsd__unsignedShort valueAsShort = static_cast<xsd__unsignedShort>(*value);
    return UnsignedShort::serialize(&valueAsShort);
}

xsd__unsignedByte* UnsignedByte::deserializeUnsignedByte(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedShort* returnValue = UnsignedShort::deserializeUnsignedShort(valueAsChar);
 
    if(m_UnsignedByte)
    {
        delete m_UnsignedByte;
        m_UnsignedByte = NULL;
    }
    m_UnsignedByte = new xsd__unsignedByte;
    *m_UnsignedByte = static_cast<xsd__unsignedByte> (*returnValue);
    return m_UnsignedByte;
}

MaxInclusive* UnsignedByte::getMaxInclusive()
{
   AxisChar* end;    
   LONGLONG* maxInclusive = new LONGLONG;
   *maxInclusive = strtol ("255", &end, 10);
    
    MaxInclusive* retVal = new MaxInclusive(*maxInclusive);
    delete maxInclusive;
    return retVal;
}

AXIS_CPP_NAMESPACE_END
