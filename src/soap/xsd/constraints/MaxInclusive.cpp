#include "MaxInclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MaxInclusive::MaxInclusive(LONGLONG maxInclusive)
    {
        m_MaxInclusive.longlongMaxInclusive = maxInclusive;
        m_isSet = true;
    }

    MaxInclusive::MaxInclusive(double maxInclusive)
    {
        m_MaxInclusive.doubleMaxInclusive = maxInclusive;
        m_isSet = true;
    }
    
    MaxInclusive::MaxInclusive(struct tm maxInclusive)
    {
        m_MaxInclusive.structTMMaxInclusive = maxInclusive;
        m_isSet = true;
    }

    MaxInclusive::MaxInclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MaxInclusive::getMaxInclusiveAsLONGLONG()
    {
        return m_MaxInclusive.longlongMaxInclusive;
    }
    
    double MaxInclusive::getMaxInclusiveAsDouble()
    {
        return m_MaxInclusive.doubleMaxInclusive;
    }
    
    struct tm MaxInclusive::getMaxInclusiveAsStructTM()
    {
        return m_MaxInclusive.structTMMaxInclusive;
    }
    
AXIS_CPP_NAMESPACE_END
