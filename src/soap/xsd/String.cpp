#include "String.hpp"

AXIS_CPP_NAMESPACE_START

String::String():m_String(NULL)
{
}

AxisChar* String::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((AxisChar*) value);
}

void* String::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeString(valueAsChar);
}

AxisChar* String::serialize(const AxisChar* value) throw (AxisSoapException)
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
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete maxLength;
 
	AxisString valueAsString = value;
	AxisChar* serializedValue = (AxisChar*) replaceReservedCharacters(valueAsString).c_str();

    IAnySimpleType::serialize(serializedValue);
    return m_Buf;
}

AxisChar* String::deserializeString(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    if (m_String)
    {
        delete [] m_String;
        m_String = NULL;
    }
	m_String = new char[strlen (valueAsChar) + 1];
	strcpy (m_String, valueAsChar);
	return m_String;
}

MinLength* String::getMinLength()
{
    return new MinLength();
}

MaxLength* String::getMaxLength()
{
    return new MaxLength();
}

AXIS_CPP_NAMESPACE_END
