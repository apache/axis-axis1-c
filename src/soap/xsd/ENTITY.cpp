#include "ENTITY.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* ENTITY::deserializeENTITY(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
