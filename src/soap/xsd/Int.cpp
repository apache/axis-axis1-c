#include "Int.hpp"

AXIS_CPP_NAMESPACE_START

int* Int::deserializeInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (int*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
