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

#include "Base64Binary.hpp"

AXIS_CPP_NAMESPACE_START

    Base64Binary::Base64Binary():m_Base64Binary(NULL)
    {
    }
    
    Base64Binary::~Base64Binary()
    {
    }

    Base64Binary::Base64Binary(const xsd__base64Binary* value):m_Base64Binary(NULL)
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
    
    void* Base64Binary::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeBase64Binary(valueAsChar);
    }
	
    AxisChar* Base64Binary::serialize(const xsd__base64Binary * value) throw (AxisSoapException)
    {
        MinLength* minLength= getMinLength();
        if (minLength->isSet())
        {
            if (value->__size < minLength->getMinLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", minLength->getMinLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", value->__size);
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
            if (value->__size > maxLength->getMaxLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", maxLength->getMaxLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", value->__size);
                exceptionMessage += length;
                exceptionMessage += ".";
                delete [] length;
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete maxLength;

        Length* length= getLength();
        if (length->isSet())
        {
            if (value->__size != length->getLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
                AxisChar* lengthAsString = new AxisChar[10];
                sprintf(lengthAsString, "%d", length->getLength());
                exceptionMessage += lengthAsString;
                exceptionMessage += ", Length of value = ";
                sprintf(lengthAsString, "%d", value->__size);
                exceptionMessage += lengthAsString;
                exceptionMessage += ".";
                delete [] lengthAsString;
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete length;
     
	    int len = apr_base64_encode_len (value->__size);	    
	    AxisChar* serializedValue = new AxisChar[len + 1];
	    len = apr_base64_encode_binary (serializedValue, value->__ptr, value->__size);
	    serializedValue[len] = 0;
	    	    
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;        
		return m_Buf;
    }
	
    xsd__base64Binary * Base64Binary::deserializeBase64Binary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
        if (m_Base64Binary)
        {
            delete  m_Base64Binary;
            m_Base64Binary = NULL;
        }
    	m_Base64Binary = new xsd__base64Binary();
	    m_Base64Binary->__size = apr_base64_decode_len (valueAsChar);
	    m_Base64Binary->__ptr = new unsigned char[m_Base64Binary->__size + 1];
	    m_Base64Binary->__size = apr_base64_decode_binary (m_Base64Binary->__ptr, valueAsChar);
	    /* put null at the end because it enables the decoded string to be used
	     * as a string 
	     */
	    m_Base64Binary->__ptr[m_Base64Binary->__size] = 0;
	
	    return m_Base64Binary;
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

AXIS_CPP_NAMESPACE_END
