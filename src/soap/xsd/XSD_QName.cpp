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

#include "XSD_QName.hpp"

AXIS_CPP_NAMESPACE_START

    XSD_QName::XSD_QName()
    {
    }

    XSD_QName::XSD_QName(const xsd__QName value)
    {
        if (value)
        {
            setNil(false);
            serialize(value);
        }
    }
    
    XSDTYPE XSD_QName::getType()
    {
        return XSD_QNAME;
    }
    
    xsd__QName XSD_QName::getQName()
    {
        if (isNil())
        {
            return NULL;
        }
        else
        {
            return deserializeQName(m_Buf);
        }
    }

    void * XSD_QName::getValue()
    {
        return (void*) getQName();
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
                AxisChar length[100];
                sprintf(length, "%d", minLength->getMinLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", strlen(value));
                exceptionMessage += length;
                exceptionMessage += ".";
                
                delete minLength;
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
                AxisChar length[100];
                sprintf(length, "%d", maxLength->getMaxLength());
                exceptionMessage += length;
                exceptionMessage += ", Length of value = ";
                sprintf(length, "%d", strlen(value));
                exceptionMessage += length;
                exceptionMessage += ".";
                
                delete maxLength;
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
                AxisChar lengthAsString[100];
                sprintf(lengthAsString, "%d", length->getLength());
                exceptionMessage += lengthAsString;
                exceptionMessage += ", Length of value = ";
                sprintf(lengthAsString, "%d", strlen(value));
                exceptionMessage += lengthAsString;
                exceptionMessage += ".";
                
                delete length;
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
		xsd__QName value = new char[strlen (valueAsChar) + 1];
		strcpy (value, valueAsChar);
		return value;
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
