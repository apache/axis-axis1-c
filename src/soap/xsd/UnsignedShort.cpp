#include "UnsignedShort.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedShort::UnsignedShort():m_UnsignedShort(NULL)
{
}

UnsignedShort::~UnsignedShort()
{
}

AxisChar* UnsignedShort::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__unsignedShort *) value);
}

void* UnsignedShort::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedShort(valueAsChar);
}

AxisChar* UnsignedShort::serialize(xsd__unsignedShort * value) throw (AxisSoapException)
{
    xsd__unsignedInt valueAsInt = static_cast<xsd__unsignedInt>(*value);
    return UnsignedInt::serialize(&valueAsInt);
}

xsd__unsignedShort* UnsignedShort::deserializeUnsignedShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__unsignedInt* returnValue = UnsignedInt::deserializeUnsignedInt(valueAsChar);
 
    if(m_UnsignedShort)
    {
        delete m_UnsignedShort;
        m_UnsignedShort = NULL;
    }
    m_UnsignedShort = new xsd__unsignedShort;
    *m_UnsignedShort = static_cast<xsd__unsignedShort> (*returnValue);
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
