#include "NOTATION.hpp"

AXIS_CPP_NAMESPACE_START

NOTATION::NOTATION():m_NOTATION(NULL)
{
}

AxisChar* NOTATION::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((AxisChar*) value);
}

void* NOTATION::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeNOTATION(valueAsChar);
}

AxisChar* NOTATION::serialize(const AxisChar* value) throw (AxisSoapException)
{
	AxisString valueAsString = value;
	AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();

    IAnySimpleType::serialize(serializedValue);
	return m_Buf;
}

AxisChar* NOTATION::deserializeNOTATION(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    if (m_NOTATION)
    {
        delete [] m_NOTATION;
        m_NOTATION = NULL;
    }
	m_NOTATION = new char[strlen (valueAsChar) + 1];
	strcpy (m_NOTATION, valueAsChar);
	return m_NOTATION;
}

WhiteSpace* NOTATION::getWhiteSpace()
{
    return new WhiteSpace(REPLACE);
}

AXIS_CPP_NAMESPACE_END
