#include "Length.hpp"

AXIS_CPP_NAMESPACE_START

    Length::Length():m_Length(0)
    {
        m_isSet = false;
    }

    Length::Length(int length)
    {
        m_Length = length;
        m_isSet = true;
    }

    int Length::getLength()
    {
        return m_Length;
    }
    
AXIS_CPP_NAMESPACE_END
