#include "UnsignedByte.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedByte::UnsignedByte():m_UnsignedByte(NULL)
{
}

UnsignedByte::~UnsignedByte()
{
    if (m_UnsignedByte)
        delete m_UnsignedByte;
}

AxisChar* UnsignedByte::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((unsigned char*) value);
}

void* UnsignedByte::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedByte(valueAsChar);
}

AxisChar* UnsignedByte::serialize(const unsigned char* value) throw (AxisSoapException)
{
    unsigned short valueAsShort = static_cast<unsigned short>(*value);
    return UnsignedShort::serialize(&valueAsShort);
}

unsigned char* UnsignedByte::deserializeUnsignedByte(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    unsigned short* returnValue = UnsignedShort::deserializeUnsignedShort(valueAsChar);
 
    if(m_UnsignedByte)
    {
        delete m_UnsignedByte;
        m_UnsignedByte = NULL;
    }
    m_UnsignedByte = new unsigned char;
    *m_UnsignedByte = static_cast<unsigned char> (*returnValue);
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
