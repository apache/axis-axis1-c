#include "MinExclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MinExclusive::MinExclusive(LONGLONG minExclusive)
    {
        m_MinExclusive.longlongMinExclusive = minExclusive;
        m_isSet = true;
    }

    MinExclusive::MinExclusive(double minExclusive)
    {
        m_MinExclusive.doubleMinExclusive = minExclusive;
        m_isSet = true;
    }
    
    MinExclusive::MinExclusive(struct tm minExclusive)
    {
        m_MinExclusive.structTMMinExclusive = minExclusive;
        m_isSet = true;
    }

    MinExclusive::MinExclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MinExclusive::getMinExclusiveAsLONGLONG()
    {
        return m_MinExclusive.longlongMinExclusive;
    }
    
    double MinExclusive::getMinExclusiveAsDouble()
    {
        return m_MinExclusive.doubleMinExclusive;
    }
    
    struct tm MinExclusive::getMinExclusiveAsStructTM()
    {
        return m_MinExclusive.structTMMinExclusive;
    }
    
AXIS_CPP_NAMESPACE_END
