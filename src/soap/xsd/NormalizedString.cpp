#include "NormalizedString.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* NormalizedString::deserializeNormalizedString(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

WhiteSpace* NormalizedString::getWhiteSpace()
{
    return new WhiteSpace(REPLACE);
}

AXIS_CPP_NAMESPACE_END
