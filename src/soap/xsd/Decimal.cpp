#include "Decimal.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* Decimal::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((double*) value);	
}

void* Decimal::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeDecimal(valueAsChar);
}


AxisChar* Decimal::serialize(const double* value) throw (AxisSoapException)
{
	AxisSprintf (m_Buf, 80, "%f", *value);
	
	return m_Buf;
}

double* Decimal::deserializeDecimal(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
	m_Decimal = new double;
	*m_Decimal = strtod (valueAsChar, &end);
	
	return m_Decimal;
}

AXIS_CPP_NAMESPACE_END
