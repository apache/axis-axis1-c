#include "Integer.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* Integer::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((LONGLONG*) value);  
}

void* Integer::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
   return (void*) deserializeInteger(valueAsChar);
}


AxisChar* Integer::serialize(const LONGLONG* value) throw (AxisSoapException)
{
    AxisSprintf (m_Buf, 80, "%lld", *value);
    return m_Buf;
}

LONGLONG* Integer::deserializeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    AxisChar* end;
    m_Integer = new LONGLONG;
    *m_Integer = strtol (valueAsChar, &end, 10);
  
    return m_Integer;
}

AXIS_CPP_NAMESPACE_END
