#include "Int.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* Int::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((int*) value);
}

void* Int::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeInt(valueAsChar);
}

AxisChar* Int::serialize(const int* value) throw (AxisSoapException)
{
    LONGLONG valueAsLong = static_cast<LONGLONG>(*value);
    return Long::serialize(&valueAsLong);
}

int* Int::deserializeInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    LONGLONG* returnValue = Long::deserializeLong(valueAsChar);
    m_int = new int;
    *m_int = static_cast<int> (*returnValue);
    return m_int;
}

AXIS_CPP_NAMESPACE_END
