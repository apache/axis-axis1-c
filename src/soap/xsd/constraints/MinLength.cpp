#include "MinLength.hpp"

AXIS_CPP_NAMESPACE_START

    MinLength::MinLength():m_MinLength(0)
    {
        m_isSet = false;
    }

    MinLength::MinLength(int minLength)
    {
        m_MinLength = minLength;
        m_isSet = true;
    }

    int MinLength::getMinLength()
    {
        return m_MinLength;
    }
    
AXIS_CPP_NAMESPACE_END
