#include "AnyURI.hpp"

AXIS_CPP_NAMESPACE_START

    AnyURI::AnyURI():m_AnyURI(NULL)
    {
    }

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
		AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();
		
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
		return m_Buf;
    }
	
    AxisChar* AnyURI::deserializeAnyURI(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
        if (m_AnyURI)
        {
            delete [] m_AnyURI;
            m_AnyURI = NULL;
        }
		m_AnyURI = new char[strlen (valueAsChar) + 1];
		strcpy (m_AnyURI, valueAsChar);
		return m_AnyURI;
    }

    WhiteSpace* AnyURI::getWhiteSpace()
    {
        return new WhiteSpace(REPLACE);
    }

AXIS_CPP_NAMESPACE_END
