#include "NOTATION.hpp"

AXIS_CPP_NAMESPACE_START

NOTATION::NOTATION():m_NOTATION(NULL)
{
}

AxisChar* NOTATION::serialize(const void* value) throw (AxisSoapException)
{
	return serialize((AxisChar*) value);
}

void* NOTATION::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	return (void*) deserializeNOTATION(valueAsChar);
}

AxisChar* NOTATION::serialize(const AxisChar* value) throw (AxisSoapException)
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

AxisChar* NOTATION::deserializeNOTATION(const AxisChar* valueAsChar) throw (AxisSoapException)
{
    if (m_NOTATION)
    {
        delete [] m_NOTATION;
        m_NOTATION = NULL;
    }
	m_NOTATION = new char[strlen (valueAsChar) + 1];
	strcpy (m_NOTATION, valueAsChar);
	return m_NOTATION;
}

WhiteSpace* NOTATION::getWhiteSpace()
{
    return new WhiteSpace(REPLACE);
}

MinLength* NOTATION::getMinLength()
{
    return new MinLength();
}

MaxLength* NOTATION::getMaxLength()
{
    return new MaxLength();
}

AXIS_CPP_NAMESPACE_END
