#include "Base64Binary.hpp"

AXIS_CPP_NAMESPACE_START

    AxisChar* Base64Binary::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((xsd__base64Binary*) value);
    }
	
    void* Base64Binary::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeBase64Binary(valueAsChar);
    }
	
    AxisChar* Base64Binary::serialize(const xsd__base64Binary* value) throw (AxisSoapException)
    {
	    int len = apr_base64_encode_len (value->__size);	    
	    AxisChar* serializedValue = new AxisChar[len + 1];
	    len = apr_base64_encode_binary (serializedValue, value->__ptr, value->__size);
	    serializedValue[len] = 0;
	    	    
	    m_Buf = new char[strlen (serializedValue) + 1];
		strcpy (m_Buf, serializedValue);
		return m_Buf;
    }
	
    xsd__base64Binary* Base64Binary::deserializeBase64Binary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	m_base64Binary = new xsd__base64Binary();
	    m_base64Binary->__size = apr_base64_decode_len (valueAsChar);
	    m_base64Binary->__ptr = new unsigned char[m_base64Binary->__size + 1];
	    m_base64Binary->__size = apr_base64_decode_binary (m_base64Binary->__ptr, valueAsChar);
	    /* put null at the end because it enables the decoded string to be used
	     * as a string 
	     */
	    m_base64Binary->__ptr[m_base64Binary->__size] = 0;
	
	    return m_base64Binary;
    }

AXIS_CPP_NAMESPACE_END
