#include "UnsignedLong.hpp"

AXIS_CPP_NAMESPACE_START

UnsignedLong::UnsignedLong():m_UnsignedLong(NULL)
{
}

UnsignedLong::~UnsignedLong()
{
}

AxisChar* UnsignedLong::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__unsignedLong*) value);
}

void* UnsignedLong::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeUnsignedLong(valueAsChar);
}

AxisChar* UnsignedLong::serialize(const xsd__unsignedLong* value) throw (AxisSoapException)
{
    unsigned LONGLONG valueAsLong = static_cast<unsigned LONGLONG>(*value);
    return NonNegativeInteger::serialize(&valueAsLong);
}

xsd__unsignedLong* UnsignedLong::deserializeUnsignedLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    unsigned LONGLONG* returnValue = NonNegativeInteger::deserializeNonNegativeInteger(valueAsChar);
 
    if(m_UnsignedLong)
    {
        delete m_UnsignedLong;
        m_UnsignedLong = NULL;
    }
    m_UnsignedLong = new xsd__unsignedLong;
    *m_UnsignedLong = static_cast<xsd__unsignedLong> (*returnValue);
    return m_UnsignedLong;
}

MaxInclusive* UnsignedLong::getMaxInclusive()
{
 /*
  * The actual value for this is 18446744073709551615, but as this is also the
  * physical limit of an unsigned 64bit integer, we don't actually need to check
  * this.
  */
    return new MaxInclusive();
}

AXIS_CPP_NAMESPACE_END
