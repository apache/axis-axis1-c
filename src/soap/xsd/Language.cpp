#include "Language.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* Language::deserializeLanguage(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

AXIS_CPP_NAMESPACE_END
