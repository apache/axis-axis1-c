#include "AnyURI.hpp"

AXIS_CPP_NAMESPACE_START

    AxisChar* AnyURI::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((AxisChar*) value);
    }
	
    void* AnyURI::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeAnyURI(valueAsChar);
    }
	
    AxisChar* AnyURI::serialize(const AxisChar* value) throw (AxisSoapException)
    {
		AxisString valueAsString = value;
		AxisChar* returnValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();
		
		m_Buf = new char[strlen (returnValue) + 1];
		strcpy (m_Buf, returnValue);
		return m_Buf;
    }
	
    AxisChar* AnyURI::deserializeAnyURI(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
		m_Buf = new char[strlen (valueAsChar) + 1];
		strcpy (m_Buf, valueAsChar);
		return m_Buf;
    }

AXIS_CPP_NAMESPACE_END
