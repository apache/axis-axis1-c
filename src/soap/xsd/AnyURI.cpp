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
        MinLength* minLength= getMinLength();
        if (minLength->isSet())
        {
            if (strlen(value) < minLength->getMinLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", minLength->getMinLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", strlen(value));
                exceptionMessage += length;
                exceptionMessage += ".";
                delete [] length;
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete minLength;
        
        MaxLength* maxLength = getMaxLength();
        if (maxLength->isSet())
        {
            if (strlen(value) > maxLength->getMaxLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", maxLength->getMaxLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", strlen(value));
                exceptionMessage += length;
                exceptionMessage += ".";
                delete [] length;
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete maxLength;
             
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

    MinLength* AnyURI::getMinLength()
    {
        return new MinLength();
    }
    
    MaxLength* AnyURI::getMaxLength()
    {
        return new MaxLength();
    }

AXIS_CPP_NAMESPACE_END
