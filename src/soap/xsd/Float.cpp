#include "Float.hpp"

AXIS_CPP_NAMESPACE_START

Float::Float():m_Float(NULL)
{
}

Float::~Float()
{
    if (m_Float)
        delete m_Float;
}

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
    AxisChar* serializedValue = new char[80];
    AxisSprintf (serializedValue, 80, "%f", *value);
  
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

float* Float::deserializeFloat(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
        if (m_Float)
        {
            delete m_Float;
            m_Float = NULL;
        }
	m_Float = new float;
	*m_Float = (float) strtod (valueAsChar, &end);
	
	return m_Float;
}

AXIS_CPP_NAMESPACE_END

