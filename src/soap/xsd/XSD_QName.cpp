#include "XSD_QName.hpp"

AXIS_CPP_NAMESPACE_START

    XSD_QName::XSD_QName():m_QName(NULL)
    {
    }

    AxisChar* XSD_QName::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((xsd__QName) value);
    }
	
    void* XSD_QName::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeQName(valueAsChar);
    }
	
    AxisChar* XSD_QName::serialize(const xsd__QName value) throw (AxisSoapException)
    {
        MinLength* minLength= getMinLength();
        if (minLength->isSet())
        {
            if (strlen(value) < (unsigned int) minLength->getMinLength())
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
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete minLength;
        
        MaxLength* maxLength = getMaxLength();
        if (maxLength->isSet())
        {
            if (strlen(value) > (unsigned int) maxLength->getMaxLength())
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
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete maxLength;

        Length* length = getLength();
        if (length->isSet())
        {
            if (strlen(value) != (unsigned int) length->getLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
                AxisChar* lengthAsString = new AxisChar[10];
                sprintf(lengthAsString, "%d", length->getLength());
                exceptionMessage += lengthAsString;
                exceptionMessage += ", Length of value = ";
                sprintf(lengthAsString, "%d", strlen(value));
                exceptionMessage += lengthAsString;
                exceptionMessage += ".";
                delete [] lengthAsString;
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete length;
    
		AxisString valueAsString = value;
		AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();
		
		IAnySimpleType::serialize(serializedValue);
		return m_Buf;
    }
	
    xsd__QName XSD_QName::deserializeQName(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
		m_QName = new char[strlen (valueAsChar) + 1];
		strcpy (m_QName, valueAsChar);
		return m_QName;
    }

    WhiteSpace* XSD_QName::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }
    
    MinLength* XSD_QName::getMinLength()
    {
        return new MinLength();
    }
    
    MaxLength* XSD_QName::getMaxLength()
    {
        return new MaxLength();
    }   

    Length* XSD_QName::getLength()
    {
        return new Length();
    }

AXIS_CPP_NAMESPACE_END
