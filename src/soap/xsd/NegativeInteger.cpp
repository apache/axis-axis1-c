#include "NegativeInteger.hpp"

AXIS_CPP_NAMESPACE_START

unsigned LONGLONG* NegativeInteger::deserializeNegativeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (unsigned LONGLONG*) deserialize(valueAsChar);
}

MaxInclusive* NegativeInteger::getMaxInclusive()
{   
    return new MaxInclusive((unsigned LONGLONG) 1);
    /* 
     * Note: 
     * Due to use of unsigned values all values are actually negative
     */
}

AXIS_CPP_NAMESPACE_END
