#include "Byte.hpp"

AXIS_CPP_NAMESPACE_START

Byte::Byte():m_Byte(NULL)
{
}

Byte::~Byte()
{
    if (m_Byte)
        delete m_Byte;
}

AxisChar* Byte::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((char*) value);
}

void* Byte::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeByte(valueAsChar);
}

AxisChar* Byte::serialize(const char* value) throw (AxisSoapException)
{
    short valueAsShort = static_cast<short>(*value);
    return Short::serialize(&valueAsShort);
}

char* Byte::deserializeByte(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    short* returnValue = Short::deserializeShort(valueAsChar);
 
    if(m_Byte)
    {
        delete m_Byte;
        m_Byte = NULL;
    }
    m_Byte = new char;
    *m_Byte = static_cast<char> (*returnValue);
    return m_Byte;
}

MinInclusive* Byte::getMinInclusive()
{
    return new MinInclusive(static_cast<LONGLONG>(-128));
}

AXIS_CPP_NAMESPACE_END
