#include "Long.hpp"

AXIS_CPP_NAMESPACE_START

LONGLONG* Long::deserializeLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (LONGLONG*) deserialize(valueAsChar);
}

MinInclusive* Long::getMinInclusive()
{ 
    AxisChar* end;    
    LONGLONG* minInclusive = new LONGLONG;
    *minInclusive = strtol ("-9223372036854775808", &end, 10);
    
    MinInclusive* retVal = new MinInclusive(*minInclusive);
    delete minInclusive;
    return retVal;
}

MaxInclusive* Long::getMaxInclusive()
{
    AxisChar* end;    
    LONGLONG* maxInclusive = new LONGLONG;
    *maxInclusive = strtol ("9223372036854775807", &end, 10);
    
    MaxInclusive* retVal = new MaxInclusive(*maxInclusive);
    delete maxInclusive;
    return retVal;
}

AXIS_CPP_NAMESPACE_END
