#include "Float.hpp"

AXIS_CPP_NAMESPACE_START

AxisChar* Float::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((float*) value);	
}

void* Float::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeFloat(valueAsChar);
}


AxisChar* Float::serialize(const float* value) throw (AxisSoapException)
{
	AxisSprintf (m_Buf, 80, "%f", *value);
	
	return m_Buf;
}

float* Float::deserializeFloat(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
	m_Float = new float;
	*m_Float = (float) strtod (valueAsChar, &end);
	
	return m_Float;
}

AXIS_CPP_NAMESPACE_END
