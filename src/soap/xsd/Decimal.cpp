#include "Decimal.hpp"

AXIS_CPP_NAMESPACE_START

Decimal::Decimal():m_Decimal(NULL)
{
}

Decimal::~Decimal()
{
    if (m_Decimal)
    {
        delete m_Decimal;
        m_Decimal = NULL;
    }
}

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

double* Decimal::deserializeDecimal(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	AxisChar* end;
   
    if (m_Decimal)
    {
        delete m_Decimal;
        m_Decimal = NULL;
    }
	m_Decimal = new double;
	*m_Decimal = strtod (valueAsChar, &end);
	
	return m_Decimal;
}

AXIS_CPP_NAMESPACE_END
