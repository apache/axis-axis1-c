#include "Token.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* Token::deserializeToken(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (AxisChar*) deserialize(valueAsChar);
}

WhiteSpace* Token::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

AXIS_CPP_NAMESPACE_END
