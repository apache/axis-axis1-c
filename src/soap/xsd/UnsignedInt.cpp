#include "UnsignedInt.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedInt::UnsignedInt():m_UnsignedInt(NULL)
{
}

UnsignedInt::~UnsignedInt()
{
    if (m_UnsignedInt)
        delete m_UnsignedInt;
}

AxisChar* UnsignedInt::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((unsigned int*) value);
}

void* UnsignedInt::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedInt(valueAsChar);
}

AxisChar* UnsignedInt::serialize(const unsigned int* value) throw (AxisSoapException)
{
    unsigned LONGLONG valueAsLong = static_cast<unsigned long>(*value);
    return UnsignedLong::serialize(&valueAsLong);
}

unsigned int* UnsignedInt::deserializeUnsignedInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    unsigned long* returnValue = UnsignedLong::deserializeUnsignedLong(valueAsChar);
 
    if(m_UnsignedInt)
    {
        delete m_UnsignedInt;
        m_UnsignedInt = NULL;
    }
    m_UnsignedInt = new unsigned int;
    *m_UnsignedInt = static_cast<unsigned int> (*returnValue);
    return m_UnsignedInt;
}

MaxInclusive* UnsignedInt::getMaxInclusive()
{
   AxisChar* end;    
   LONGLONG* maxInclusive = new LONGLONG;
   *maxInclusive = strtol ("4294967295", &end, 10);
    
    MaxInclusive* retVal = new MaxInclusive(*maxInclusive);
    delete maxInclusive;
    return retVal;
}

AXIS_CPP_NAMESPACE_END
