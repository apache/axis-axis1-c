#include "UnsignedInt.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedInt::UnsignedInt():m_UnsignedInt(NULL)
{
}

UnsignedInt::~UnsignedInt()
{
}

AxisChar* UnsignedInt::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__unsignedInt*) value);
}

void* UnsignedInt::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedInt(valueAsChar);
}

AxisChar* UnsignedInt::serialize(const xsd__unsignedInt* value) throw (AxisSoapException)
{
    xsd__unsignedLong valueAsLong = static_cast<xsd__unsignedLong>(*value);
    return UnsignedLong::serialize(&valueAsLong);
}

xsd__unsignedInt* UnsignedInt::deserializeUnsignedInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedLong* returnValue = UnsignedLong::deserializeUnsignedLong(valueAsChar);
 
    if(m_UnsignedInt)
    {
        delete m_UnsignedInt;
        m_UnsignedInt = NULL;
    }
    m_UnsignedInt = new xsd__unsignedInt;
    *m_UnsignedInt = static_cast<xsd__unsignedInt> (*returnValue);
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
