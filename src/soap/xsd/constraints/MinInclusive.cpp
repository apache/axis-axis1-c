#include "MinInclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MinInclusive::MinInclusive(LONGLONG minInclusive)
    {
        m_MinInclusive.longlongMinInclusive = minInclusive;
        m_isSet = true;
    }

    MinInclusive::MinInclusive(double minInclusive)
    {
        m_MinInclusive.doubleMinInclusive = minInclusive;
        m_isSet = true;
    }
    
    MinInclusive::MinInclusive(struct tm minInclusive)
    {
        m_MinInclusive.structTMMinInclusive = minInclusive;
        m_isSet = true;
    }

    MinInclusive::MinInclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MinInclusive::getMinInclusiveAsLONGLONG()
    {
        return m_MinInclusive.longlongMinInclusive;
    }
    
    double MinInclusive::getMinInclusiveAsDouble()
    {
        return m_MinInclusive.doubleMinInclusive;
    }
    
    struct tm MinInclusive::getMinInclusiveAsStructTM()
    {
        return m_MinInclusive.structTMMinInclusive;
    }
    
AXIS_CPP_NAMESPACE_END
