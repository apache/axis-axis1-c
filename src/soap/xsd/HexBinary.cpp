#include "HexBinary.hpp"

AXIS_CPP_NAMESPACE_START

HexBinary::HexBinary()
:m_Buf(NULL), m_hexBinary(NULL)
{
}

HexBinary::~HexBinary()
{
    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }

    // Samisa: should not release m_hexBinary, as this is used by the deserializer and
    // according to our current memory management semantics, this is deallocated at
    // user written client code level. If we are to delete it here (which I think is the better way)
    // we have to change the memory management semantics and updated the docs accordingly
    
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
	    
        if (m_Buf) // Samisa : memory management BP
        {
            delete [] m_Buf;
            m_Buf = NULL;
        }

	    m_Buf = new char[strlen (serializedValue) + 1];
	    strcpy (m_Buf, serializedValue);
        // Samisa: serializedValue no more required, hence clean
        delete [] serializedValue;
	    return m_Buf;
    }
	
    xsd__hexBinary* HexBinary::deserializeHexBinary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
        if (m_hexBinary) // Samisa : memory management BP
        {
            delete [] m_hexBinary;
            m_hexBinary = NULL;
        }

    	m_hexBinary = new xsd__hexBinary();    	
	    m_hexBinary->__size = strlen (valueAsChar) / 2;
	    m_hexBinary->__ptr = new unsigned char[m_hexBinary->__size + 1];
	    Hex_Decode (m_hexBinary->__ptr, valueAsChar);
	    /* put null at the end because it enables the decoded string to be used
	     * as a string 
	     */
	    m_hexBinary->__ptr[m_hexBinary->__size] = 0;

	    return m_hexBinary;
    }

AXIS_CPP_NAMESPACE_END
