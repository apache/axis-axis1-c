#include "Base64Binary.hpp"

AXIS_CPP_NAMESPACE_START

    Base64Binary::Base64Binary():m_Buf(NULL), m_base64Binary(NULL)
    {
    }
    
    Base64Binary::~Base64Binary()
    {
        if (m_Buf)
        {
            delete [] m_Buf;
            m_Buf = NULL;
        }
        
        /**
         * Don't release storage for m_base64Binary as this is still needed by
         * by customer applications, under current memory model.
         */
    }

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
	    	    
        if (m_Buf)
        {
            delete [] m_Buf;
            m_Buf = NULL;
        }
	    m_Buf = new char[strlen (serializedValue) + 1];
		strcpy (m_Buf, serializedValue);
        delete serializedValue;        
		return m_Buf;
    }
	
    xsd__base64Binary* Base64Binary::deserializeBase64Binary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
        if (m_base64Binary)
        {
            delete [] m_base64Binary;
            m_base64Binary = NULL;
        }
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
