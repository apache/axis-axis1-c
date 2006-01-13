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

    HexBinary::HexBinary()
    {
    }

    HexBinary::~HexBinary()
    {
    }

    HexBinary::HexBinary(const xsd__hexBinary* value)
    {
        if (value)
        {
            setNil(false);
            serialize(value);
        }
    }
    
    XSDTYPE HexBinary::getType()
    {
        return XSD_HEXBINARY;
    }

    xsd__hexBinary* HexBinary::getHexBinary()
    {
        if (isNil())
        {
            return NULL;
        }
        else
        {
            return deserializeHexBinary(m_Buf);
        }
    }

    void * HexBinary::getValue()
    {
        return (void*) getHexBinary();
    }    

    AxisChar* HexBinary::serialize(const xsd__hexBinary * value) throw (AxisSoapException)
    {
        MinLength* minLength= getMinLength();
        if (minLength->isSet())
        {
            if (value->getSize() < minLength->getMinLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is shorter than MinLength specified for this type.  Minlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", minLength->getMinLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", value->getSize());
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
            if (value->getSize() > maxLength->getMaxLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is longer than MaxLength specified for this type.  Maxlength = ";
                AxisChar* length = new AxisChar[10];
                sprintf(length, "%d", maxLength->getMaxLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", value->getSize());
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
            if (value->getSize() != length->getLength())
            {
                AxisString exceptionMessage =
                "Length of value to be serialized is not the same as Length specified for this type.  Length = ";
                AxisChar* lengthAsString = new AxisChar[10];
                sprintf(lengthAsString, "%d", length->getLength());
                exceptionMessage += lengthAsString;
                exceptionMessage += ", Length of value = ";
                sprintf(lengthAsString, "%d", value->getSize());
                exceptionMessage += lengthAsString;
                exceptionMessage += ".";
                delete [] lengthAsString;
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete length;
     
		char* serializedValue = new char[value->getSize() * 2 + 1];
		int size = 0;
		xsd__unsignedByte * pTemp = value->get(size);
	    Hex_Encode (serializedValue, pTemp, size);
	    serializedValue[value->getSize() * 2] = 0;
	    
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
	    return m_Buf;
    }
	
    xsd__hexBinary * HexBinary::deserializeHexBinary(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	xsd__hexBinary * value = new xsd__hexBinary();    	
	    int size = strlen (valueAsChar) / 2;
		xsd__unsignedByte * pTemp = new xsd__unsignedByte[size + 1];
	    Hex_Decode (pTemp, valueAsChar);
	    pTemp[size] = 0; // Null terminate so it could be used as a string
		value->set(pTemp, size);
		delete [] pTemp;

	    return value;
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
