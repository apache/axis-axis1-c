#include "Integer.hpp"

AXIS_CPP_NAMESPACE_START

Integer::Integer():m_Integer(NULL)
{
}

Integer::~Integer()
{
    if (m_Integer)
        delete m_Integer;
}

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
    AxisChar* serializedValue = new char[80];
    AxisSprintf (serializedValue, 80, "%lld", *value);
  
    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }
    m_Buf = new char[strlen (serializedValue) + 1];
    strcpy (m_Buf, serializedValue);
    delete [] serializedValue;        
    return m_Buf;
}

LONGLONG* Integer::deserializeInteger(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    AxisChar* end;
    
    if(m_Integer)
    {
        delete m_Integer;
        m_Integer = NULL;
    }
    m_Integer = new LONGLONG;
    *m_Integer = strtol (valueAsChar, &end, 10);
  
    return m_Integer;
}

AXIS_CPP_NAMESPACE_END
