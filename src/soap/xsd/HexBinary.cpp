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

#include "HexBinary.hpp"

AXIS_CPP_NAMESPACE_START

    HexBinary::HexBinary():m_HexBinary(NULL)
    {
    }

    HexBinary::~HexBinary()
    {
    }

    AxisChar* HexBinary::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((xsd__hexBinary*) value);
    }
	
    void* HexBinary::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeHexBinary(valueAsChar);
    }
	
    AxisChar* HexBinary::serialize(const xsd__hexBinary * value) throw (AxisSoapException)
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
     
		char* serializedValue = new char[value->__size * 2 + 1];
	    Hex_Encode (serializedValue, value->__ptr, value->__size);
	    serializedValue[value->__size * 2] = 0;
	    
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
	    return m_Buf;
    }
	
    xsd__hexBinary * HexBinary::deserializeHexBinary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
        if (m_HexBinary) // Samisa : memory management BP
        {
            delete [] m_HexBinary;
            m_HexBinary = NULL;
        }

    	m_HexBinary = new xsd__hexBinary();    	
	    m_HexBinary->__size = strlen (valueAsChar) / 2;
	    m_HexBinary->__ptr = new unsigned char[m_HexBinary->__size + 1];
	    Hex_Decode (m_HexBinary->__ptr, valueAsChar);
	    /* put null at the end because it enables the decoded string to be used
	     * as a string 
	     */
	    m_HexBinary->__ptr[m_HexBinary->__size] = 0;

	    return m_HexBinary;
    }

    MinLength* HexBinary::getMinLength()
    {
        return new MinLength();
    }
    
    MaxLength* HexBinary::getMaxLength()
    {
        return new MaxLength();
    }

    Length* HexBinary::getLength()
    {
        return new Length();
    }

AXIS_CPP_NAMESPACE_END
