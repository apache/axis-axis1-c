#include "NonNegativeInteger.hpp"

AXIS_CPP_NAMESPACE_START

LONGLONG* NonNegativeInteger::deserializeNonNegativeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (LONGLONG*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
