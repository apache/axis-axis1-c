#include "NMTOKEN.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* NMTOKEN::deserializeNMTOKEN(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
