#include "UnsignedShort.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedShort::UnsignedShort():m_UnsignedShort(NULL)
{
}

UnsignedShort::~UnsignedShort()
{
    if (m_UnsignedShort)
        delete m_UnsignedShort;
}

AxisChar* UnsignedShort::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((unsigned int*) value);
}

void* UnsignedShort::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedShort(valueAsChar);
}

AxisChar* UnsignedShort::serialize(const unsigned short* value) throw (AxisSoapException)
{
    unsigned int valueAsInt = static_cast<unsigned int>(*value);
    return UnsignedInt::serialize(&valueAsInt);
}

unsigned short* UnsignedShort::deserializeUnsignedShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    unsigned int* returnValue = UnsignedInt::deserializeUnsignedInt(valueAsChar);
 
    if(m_UnsignedShort)
    {
        delete m_UnsignedShort;
        m_UnsignedShort = NULL;
    }
    m_UnsignedShort = new unsigned short;
    *m_UnsignedShort = static_cast<unsigned short> (*returnValue);
    return m_UnsignedShort;
}

MaxInclusive* UnsignedShort::getMaxInclusive()
{
   AxisChar* end;    
   LONGLONG* maxInclusive = new LONGLONG;
   *maxInclusive = strtol ("65535", &end, 10);
    
    MaxInclusive* retVal = new MaxInclusive(*maxInclusive);
    delete maxInclusive;
    return retVal;
}

AXIS_CPP_NAMESPACE_END
