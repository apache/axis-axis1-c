#include "Double.hpp"

AXIS_CPP_NAMESPACE_START

Double::Double():m_Double(NULL)
{
}

AxisChar* Double::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((double*) value);	
}

void* Double::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeDouble(valueAsChar);
}


AxisChar* Double::serialize(const double* value) throw (AxisSoapException)
{
    AxisChar* serializedValue = new char[80];
    AxisSprintf (serializedValue, 80, "%f", *value);
	
	if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }
    m_Buf = new char[strlen (serializedValue) + 1];
    strcpy (m_Buf, serializedValue);
    delete serializedValue;        
    return m_Buf;
}

double* Double::deserializeDouble(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
   
    if (m_Double)
    {
        delete m_Double;
        m_Double = NULL;
    }
	m_Double = new double;
	*m_Double = strtod (valueAsChar, &end);
	
	return m_Double;
}

AXIS_CPP_NAMESPACE_END
