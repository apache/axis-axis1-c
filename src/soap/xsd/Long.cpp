#include "Long.hpp"

AXIS_CPP_NAMESPACE_START

Long::Long():m_Long(NULL)
{
}

Long::~Long()
{
}


AxisChar* Long::serialize(const void* value) throw (AxisSoapException)
{
    return serialize((xsd__long*) value);
}

void* Long::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    return (void*) deserializeLong(valueAsChar);
}

AxisChar* Long::serialize(const xsd__long* value) throw (AxisSoapException)
{
    xsd__integer valueAsLong = static_cast<xsd__integer>(*value);
    return Integer::serialize(&valueAsLong);
}

xsd__long* Long::deserializeLong(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    xsd__integer* returnValue = Integer::deserializeInteger(valueAsChar);
 
    if(m_Long)
    {
        delete m_Long;
        m_Long = NULL;
    }
    m_Long = new xsd__long;
    *m_Long = static_cast<xsd__long> (*returnValue);
    return m_Long;
}

MinInclusive* Long::getMinInclusive()
{ 
    AxisChar* end;    
    LONGLONG* minInclusive = new LONGLONG;
    *minInclusive = strtol ("-9223372036854775808", &end, 10);
    
    MinInclusive* retVal = new MinInclusive(*minInclusive);
    delete minInclusive;
    return retVal;
}

MaxInclusive* Long::getMaxInclusive()
{
    AxisChar* end;    
    LONGLONG* maxInclusive = new LONGLONG;
    *maxInclusive = strtol ("9223372036854775807", &end, 10);
    
    MaxInclusive* retVal = new MaxInclusive(*maxInclusive);
    delete maxInclusive;
    return retVal;
}

AXIS_CPP_NAMESPACE_END
