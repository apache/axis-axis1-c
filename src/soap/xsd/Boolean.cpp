#include "Boolean.hpp"

AXIS_CPP_NAMESPACE_START

/**
 * Serialize value to it's on-the-wire string form.
 * @param value The value to be serialized.
 * @return Serialized form of value.
 */
AxisChar* Boolean::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((bool*) value);	
}

/**
 * Deserialize value from it's on-the-wire string form.
 * @param valueAsChar Serialized form of value.
 * @return Deserialized value.
 */
void* Boolean::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeBoolean(valueAsChar);
}

/**
 * Serialize boolean value to it's on-the-wire string form.
 * @param value The boolean value to be serialized.
 * @return Serialized form of boolean value.
 */
AxisChar* Boolean::serialize(const bool* value) throw (AxisSoapException)
{
    AxisChar* serializedValue = new char[6];
	AxisSprintf (serializedValue, 6, "%s",
            (*((int *) (value)) == false_) ? "false" : "true");
    
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

/**
 * Deserialize boolean value from it's on-the-wire string form.
 * @param valueAsChar Serialized form of boolean value.
 * @return Deserialized boolean value.
 */
xsd__boolean Boolean::deserializeBoolean(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	if ( 0 == strcmp (valueAsChar, "true") || 0 == strcmp (valueAsChar, "1"))
	{
		return true_;
	}
	else
	{
		return false_;
	}
}

AXIS_CPP_NAMESPACE_END
