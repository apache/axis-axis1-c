#include "ENTITIES.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* ENTITIES::deserializeENTITIES(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
