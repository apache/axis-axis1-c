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

MinExclusive* Long::getMinExclusive()
{
    return new MinExclusive(static_cast<LONGLONG>(-9223372036854775809));
}

MaxInclusive* Long::getMaxInclusive()
{
    return new MaxInclusive(static_cast<LONGLONG>(9223372036854775807));
}

MaxExclusive* Long::getMaxExclusive()
{
    return new MaxExclusive(static_cast<LONGLONG>(9223372036854775808));
}

AXIS_CPP_NAMESPACE_END
