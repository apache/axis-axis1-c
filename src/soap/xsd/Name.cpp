#include "Name.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* Name::deserializeName(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
