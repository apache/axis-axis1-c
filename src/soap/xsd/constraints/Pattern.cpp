#include "Pattern.hpp"

AXIS_CPP_NAMESPACE_START

    Pattern::Pattern():m_Pattern(NULL)
    {
        m_isSet = false;
    }

    Pattern::Pattern(AxisChar* pattern)
    {
        if(m_Pattern)
        {
            delete [] m_Pattern;
            m_Pattern = NULL;
        }
        m_Pattern = pattern;
        m_isSet = true;
    }
    
    Pattern::~Pattern()
    {
        if(m_Pattern)
        {
            delete [] m_Pattern;
            m_Pattern = NULL;
        }
    }

    void Pattern::validatePattern(const AxisChar* value) throw (AxisSoapException)
    {
     /*
      * Currently has no effect.
      * Needs to validate the given string matches the regular expression
      * provided to the constructor.
      */
    }

AXIS_CPP_NAMESPACE_END
