#include "NCName.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* NCName::deserializeNCName(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
