#include "XSD_QName.hpp"

AXIS_CPP_NAMESPACE_START

    XSD_QName::XSD_QName():m_QName(NULL)
    {
    }

    AxisChar* XSD_QName::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((AxisChar*) value);
    }
	
    void* XSD_QName::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeQName(valueAsChar);
    }
	
    AxisChar* XSD_QName::serialize(const AxisChar* value) throw (AxisSoapException)
    {
		AxisString valueAsString = value;
		AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();
		
		IAnySimpleType::serialize(serializedValue);
		return m_Buf;
    }
	
    AxisChar* XSD_QName::deserializeQName(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
		m_QName = new char[strlen (valueAsChar) + 1];
		strcpy (m_QName, valueAsChar);
		return m_QName;
    }

    WhiteSpace* XSD_QName::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }

AXIS_CPP_NAMESPACE_END
