#include "PositiveInteger.hpp"

AXIS_CPP_NAMESPACE_START

unsigned LONGLONG* PositiveInteger::deserializePositiveInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (unsigned LONGLONG*) deserialize(valueAsChar);
}

MinInclusive* PositiveInteger::getMinInclusive()
{   
    return new MinInclusive((unsigned LONGLONG) 1);
}

AXIS_CPP_NAMESPACE_END
