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
	
    IAnySimpleType::serialize(serializedValue);
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

WhiteSpace* Decimal::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

AXIS_CPP_NAMESPACE_END
