#include "ID.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* ID::deserializeID(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
