#include "MaxExclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MaxExclusive::MaxExclusive(LONGLONG maxExclusive)
    {
        m_MaxExclusive.longlongMaxExclusive = maxExclusive;
        m_isSet = true;
    }

    MaxExclusive::MaxExclusive(double maxExclusive)
    {
        m_MaxExclusive.doubleMaxExclusive = maxExclusive;
        m_isSet = true;
    }
    
    MaxExclusive::MaxExclusive(struct tm maxExclusive)
    {
        m_MaxExclusive.structTMMaxExclusive = maxExclusive;
        m_isSet = true;
    }

    MaxExclusive::MaxExclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MaxExclusive::getMaxExclusiveAsLONGLONG()
    {
        return m_MaxExclusive.longlongMaxExclusive;
    }
    
    double MaxExclusive::getMaxExclusiveAsDouble()
    {
        return m_MaxExclusive.doubleMaxExclusive;
    }
    
    struct tm MaxExclusive::getMaxExclusiveAsStructTM()
    {
        return m_MaxExclusive.structTMMaxExclusive;
    }
    
AXIS_CPP_NAMESPACE_END
