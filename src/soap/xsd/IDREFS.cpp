#include "IDREFS.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* IDREFS::deserializeIDREFS(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
