#include "String.hpp"

AXIS_CPP_NAMESPACE_START

String::String():m_String(NULL)
{
}

AxisChar* String::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((AxisChar*) value);
}

void* String::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeString(valueAsChar);
}

AxisChar* String::serialize(const AxisChar* value) throw (AxisSoapException)
{
	AxisString valueAsString = value;
	AxisChar* returnValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();

    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }	
	m_Buf = new char[strlen (returnValue) + 1];
	strcpy (m_Buf, returnValue);
	return m_Buf;
}

AxisChar* String::deserializeString(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    if (m_String)
    {
        delete [] m_String;
        m_String = NULL;
    }
	m_String = new char[strlen (valueAsChar) + 1];
	strcpy (m_String, valueAsChar);
	return m_String;
}

AXIS_CPP_NAMESPACE_END
