#include "FractionDigits.hpp"

AXIS_CPP_NAMESPACE_START

    FractionDigits::FractionDigits():m_FractionDigits(0)
    {
        m_isSet = false;
    }

    FractionDigits::FractionDigits(int fractionDigits)
    {
        m_FractionDigits = fractionDigits;
        m_isSet = true;
    }

    int FractionDigits::getFractionDigits()
    {
        return m_FractionDigits;
    }
    
AXIS_CPP_NAMESPACE_END
