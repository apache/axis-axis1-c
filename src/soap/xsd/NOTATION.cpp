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
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
            
            throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    }
    delete length;
    
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

Length* NOTATION::getLength()
{
    return new Length();
}

AXIS_CPP_NAMESPACE_END
