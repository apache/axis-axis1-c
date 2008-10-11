// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include "Base64Binary.hpp"

AXIS_CPP_NAMESPACE_START

Base64Binary::Base64Binary()
{
}

Base64Binary::~Base64Binary()
{
}

Base64Binary::Base64Binary(const xsd__base64Binary* value)
{
    if (value)
    {
        setNil(false);
        serialize(value);
    }
}

XSDTYPE Base64Binary::getType()
{
    return XSD_BASE64BINARY;
}

xsd__base64Binary* Base64Binary::getBase64Binary()
{
    if (isNil())
        return NULL;
    else
        return deserializeBase64Binary(m_Buf);
}

void * Base64Binary::getValue()
{
    return (void*) getBase64Binary();
}

AxisChar* Base64Binary::serialize(const xsd__base64Binary * value) throw (AxisSoapException)
{
    AxisString exceptionMessage;
    char lengthAsString[100];
    
    MinLength* minLength= getMinLength();
    if (minLength->isSet())
        if (value->getSize() < minLength->getMinLength())
        {
            exceptionMessage =
            "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
            sprintf(lengthAsString, "%d", minLength->getMinLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", value->getSize());
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";
            
            delete minLength;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete minLength;
    
    MaxLength* maxLength = getMaxLength();
    if (maxLength->isSet())
        if (value->getSize() > maxLength->getMaxLength())
        {
            exceptionMessage =
            "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
            sprintf(lengthAsString, "%d", maxLength->getMaxLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", value->getSize());
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";
            
            delete maxLength;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete maxLength;

    Length* length= getLength();
    if (length->isSet())
        if (value->getSize() != length->getLength())
        {
            exceptionMessage =
            "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
            sprintf(lengthAsString, "%d", length->getLength());
            exceptionMessage += lengthAsString;
            exceptionMessage += ", Length of value = ";
            sprintf(lengthAsString, "%d", value->getSize());
            exceptionMessage += lengthAsString;
            exceptionMessage += ".";

            delete length;
            throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                const_cast<AxisChar*>(exceptionMessage.c_str()));
        }
    delete length;
 
    int len = apr_base64_encode_len (value->getSize());	    
    AxisChar* serializedValue = new AxisChar[len + 1];
	int size = 0;
	xsd__unsignedByte * pTemp = value->get(size);
    len = apr_base64_encode_binary (serializedValue, pTemp, size);
    serializedValue[len] = 0;
    	    
    IAnySimpleType::serialize(serializedValue);
    delete [] serializedValue;        
	return m_Buf;
}

xsd__base64Binary * Base64Binary::deserializeBase64Binary(const AxisChar* valueAsChar) throw (AxisSoapException)
{
	xsd__base64Binary * value = new xsd__base64Binary();
    xsd__int size = apr_base64_decode_len (valueAsChar);
    xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
    size = apr_base64_decode_binary (pTemp, valueAsChar);
    pTemp[size] = 0; // Null terminate so it could be used as a string
	value->set(pTemp, size);
	delete [] pTemp;
    return value;
}

MinLength* Base64Binary::getMinLength()
{
    return new MinLength();
}

MaxLength* Base64Binary::getMaxLength()
{
    return new MaxLength();
}

Length* Base64Binary::getLength()
{
    return new Length();
}

WhiteSpace* Base64Binary::getWhiteSpace()
{
    return new WhiteSpace(COLLAPSE);
}

AXIS_CPP_NAMESPACE_END
