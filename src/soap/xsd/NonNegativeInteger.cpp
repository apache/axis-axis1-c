#include "NonNegativeInteger.hpp"

AXIS_CPP_NAMESPACE_START

LONGLONG* NonNegativeInteger::deserializeNonNegativeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (LONGLONG*) deserialize(valueAsChar);
}

MinInclusive* NonNegativeInteger::getMinInclusive()
{   
    return new MinInclusive((LONGLONG) 0);
}

MinExclusive* NonNegativeInteger::getMinExclusive()
{   
    return new MinExclusive((LONGLONG) -1);
}

MaxInclusive* NonNegativeInteger::getMaxInclusive()
{   
    return new MaxInclusive();
}

MaxExclusive* NonNegativeInteger::getMaxExclusive()
{   
    return new MaxExclusive();
}

AXIS_CPP_NAMESPACE_END
