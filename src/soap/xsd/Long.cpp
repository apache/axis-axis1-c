#include "Long.hpp"

AXIS_CPP_NAMESPACE_START

LONGLONG* Long::deserializeLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (LONGLONG*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
