#include "IDREF.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* IDREF::deserializeIDREF(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
