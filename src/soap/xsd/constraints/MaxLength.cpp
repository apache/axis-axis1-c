#include "MaxLength.hpp"

AXIS_CPP_NAMESPACE_START

    MaxLength::MaxLength():m_MaxLength(0)
    {
        m_isSet = false;
    }

    MaxLength::MaxLength(int maxLength)
    {
        m_MaxLength = maxLength;
        m_isSet = true;
    }

    int MaxLength::getMaxLength()
    {
        return m_MaxLength;
    }
    
AXIS_CPP_NAMESPACE_END
