#include "TotalDigits.hpp"

AXIS_CPP_NAMESPACE_START

    TotalDigits::TotalDigits():m_TotalDigits(0)
    {
        m_isSet = false;
    }

    TotalDigits::TotalDigits(int totalDigits)
    {
        m_TotalDigits = totalDigits;
        m_isSet = true;
    }

    int TotalDigits::getTotalDigits()
    {
        return m_TotalDigits;
    }
    
AXIS_CPP_NAMESPACE_END
