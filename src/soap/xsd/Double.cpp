#include "Double.hpp"

AXIS_CPP_NAMESPACE_START

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
	AxisSprintf (m_Buf, 80, "%f", *value);
	
	return m_Buf;
}

double* Double::deserializeDouble(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
	m_Double = new double;
	*m_Double = strtod (valueAsChar, &end);
	
	return m_Double;
}

AXIS_CPP_NAMESPACE_END
