#include "Int.hpp"

AXIS_CPP_NAMESPACE_START

Int::Int():m_Int(NULL)
{
}

Int::~Int()
{
    if (m_Int)
        delete m_Int;
}

AxisChar* Int::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((int*) value);
}

void* Int::deserializer(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeInt(valueAsChar);
}

AxisChar* Int::serialize(const int* value) throw (AxisSoapException)
{
    LONGLONG valueAsLong = static_cast<LONGLONG>(*value);
    return Long::serialize(&valueAsLong);
}

int* Int::deserializeInt(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    LONGLONG* returnValue = Long::deserializeLong(valueAsChar);
 
    if(m_Int)
    {
        delete m_Int;
        m_Int = NULL;
    }
    m_Int = new int;
    *m_Int = static_cast<int> (*returnValue);
    return m_Int;
}

MinInclusive* Int::getMinInclusive()
{   
  AxisChar* end;    
  LONGLONG* minInclusive = new LONGLONG;
  *minInclusive = strtol ("-2147483648", &end, 10);
    
    return new MinInclusive(*minInclusive);
}

MinExclusive* Int::getMinExclusive()
{   
  AxisChar* end;    
  LONGLONG* minExclusive = new LONGLONG;
  *minExclusive = strtol ("-2147483649", &end, 10);
    
    return new MinExclusive(*minExclusive);
}

MaxInclusive* Int::getMaxInclusive()
{   
  AxisChar* end;    
  LONGLONG* maxInclusive = new LONGLONG;
  *maxInclusive = strtol ("2147483647", &end, 10);
    
    return new MaxInclusive(*maxInclusive);
}

MaxExclusive* Int::getMaxExclusive()
{   
  AxisChar* end;    
  LONGLONG* maxExclusive = new LONGLONG;
  *maxExclusive = strtol ("2147483648", &end, 10);
    
    return new MaxExclusive(*maxExclusive);
}

AXIS_CPP_NAMESPACE_END
