#include "Short.hpp"

AXIS_CPP_NAMESPACE_START

Short::Short():m_Short(NULL)
{
}

Short::~Short()
{
}

AxisChar* Short::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__short*) value);
}

void* Short::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeShort(valueAsChar);
}

AxisChar* Short::serialize(const xsd__short* value) throw (AxisSoapException)
{
    xsd__int valueAsInt = static_cast<xsd__int>(*value);
    return Int::serialize(&valueAsInt);
}

xsd__short* Short::deserializeShort(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__int* returnValue = Int::deserializeInt(valueAsChar);
 
    if(m_Short)
    {
        delete m_Short;
        m_Short = NULL;
    }
    m_Short = new xsd__short;
    *m_Short = static_cast<xsd__short> (*returnValue);
    return m_Short;
}

MinInclusive* Short::getMinInclusive()
{
    return new MinInclusive(static_cast<LONGLONG>(-32768));
}

MinExclusive* Short::getMinExclusive()
{
    return new MinExclusive(static_cast<LONGLONG>(-32769));
}

MaxInclusive* Short::getMaxInclusive()
{
    return new MaxInclusive(static_cast<LONGLONG>(32767));
}

MaxExclusive* Short::getMaxExclusive()
{
    return new MaxExclusive(static_cast<LONGLONG>(32768));
}

AXIS_CPP_NAMESPACE_END
