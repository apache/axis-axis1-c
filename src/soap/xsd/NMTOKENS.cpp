#include "NMTOKENS.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* NMTOKENS::deserializeNMTOKENS(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
