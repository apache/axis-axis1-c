#include "Byte.hpp"

AXIS_CPP_NAMESPACE_START

Byte::Byte():m_Byte(NULL)
{
}

Byte::~Byte()
{
}

AxisChar* Byte::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__byte*) value);
}

void* Byte::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeByte(valueAsChar);
}

AxisChar* Byte::serialize(const char* value) throw (AxisSoapException)
{
    xsd__short valueAsShort = static_cast<xsd__short>(*value);
    return Short::serialize(&valueAsShort);
}

char* Byte::deserializeByte(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__short* returnValue = Short::deserializeShort(valueAsChar);
 
    if(m_Byte)
    {
        delete m_Byte;
        m_Byte = NULL;
    }
    m_Byte = new xsd__byte;
    *m_Byte = static_cast<xsd__byte> (*returnValue);
    return m_Byte;
}

MinInclusive* Byte::getMinInclusive()
{
    return new MinInclusive(static_cast<LONGLONG>(-128));
}

MinExclusive* Byte::getMinExclusive()
{
    return new MinExclusive(static_cast<LONGLONG>(-129));
}

MaxInclusive* Byte::getMaxInclusive()
{
    return new MaxInclusive(static_cast<LONGLONG>(127));
}

MaxExclusive* Byte::getMaxExclusive()
{
    return new MaxExclusive(static_cast<LONGLONG>(128));
}

AXIS_CPP_NAMESPACE_END
