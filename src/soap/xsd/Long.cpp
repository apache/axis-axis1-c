#include "Long.hpp"

AXIS_CPP_NAMESPACE_START

LONGLONG* Long::deserializeLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (LONGLONG*) deserialize(valueAsChar);
}

MinInclusive* Long::getMinInclusive()
{
    return new MinInclusive(static_cast<LONGLONG>(-9223372036854775808));
}

AXIS_CPP_NAMESPACE_END
