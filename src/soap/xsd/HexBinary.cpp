#include "HexBinary.hpp"

AXIS_CPP_NAMESPACE_START

    HexBinary::HexBinary():m_HexBinary(NULL)
    {
    }

    HexBinary::~HexBinary()
    {
        if (m_HexBinary)
        {
            delete m_HexBinary;
            m_HexBinary = NULL;
        }
    }

    AxisChar* HexBinary::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((xsd__hexBinary*) value);
    }
	
    void* HexBinary::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeHexBinary(valueAsChar);
    }
	
    AxisChar* HexBinary::serialize(const xsd__hexBinary* value) throw (AxisSoapException)
    {
		char* serializedValue = new char[value->__size * 2 + 1];
	    Hex_Encode (serializedValue, value->__ptr, value->__size);
	    serializedValue[value->__size * 2] = 0;
	    
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
	    return m_Buf;
    }
	
    xsd__hexBinary* HexBinary::deserializeHexBinary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
        if (m_HexBinary) // Samisa : memory management BP
        {
            delete [] m_HexBinary;
            m_HexBinary = NULL;
        }

    	m_HexBinary = new xsd__hexBinary();    	
	    m_HexBinary->__size = strlen (valueAsChar) / 2;
	    m_HexBinary->__ptr = new unsigned char[m_HexBinary->__size + 1];
	    Hex_Decode (m_HexBinary->__ptr, valueAsChar);
	    /* put null at the end because it enables the decoded string to be used
	     * as a string 
	     */
	    m_HexBinary->__ptr[m_HexBinary->__size] = 0;

	    return m_HexBinary;
    }

AXIS_CPP_NAMESPACE_END
