#include "Short.hpp"

AXIS_CPP_NAMESPACE_START

Short::Short():m_Short(NULL)
{
}

Short::~Short()
{
    if (m_Short)
        delete m_Short;
}

AxisChar* Short::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((short*) value);
}

void* Short::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeShort(valueAsChar);
}

AxisChar* Short::serialize(const short* value) throw (AxisSoapException)
{
    int valueAsInt = static_cast<int>(*value);
    return Int::serialize(&valueAsInt);
}

short* Short::deserializeShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    int* returnValue = Int::deserializeInt(valueAsChar);
 
    if(m_Short)
    {
        delete m_Short;
        m_Short = NULL;
    }
    m_Short = new short;
    *m_Short = static_cast<short> (*returnValue);
    return m_Short;
}

AXIS_CPP_NAMESPACE_END
