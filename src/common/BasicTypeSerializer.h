/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * @file BasicTypeSerializer.h
 *
 * This file contains the BasicTypeSerializer class which has the functions
 * that the Serializer uses to serialize all xsd basic types.
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
  
#if !defined(_BASICTYPESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _BASICTYPESERIALIZER_H____OF_AXIS_INCLUDED_

#include <axis/TypeMapping.hpp>
#include "AxisTime.h"
#include <string>
using namespace std;

#define BTS_BUFFSIZE 32
const AxisChar XML_ENTITY_REFERENCE_CAHRS[]    = "<>&\"\'";
/* Entity reference characters */
const AxisChar ENCODED_LESSER_STR[]            = "&lt;";    
/* Encoded string for less than character */
const AxisChar ENCODED_GREATOR_STR[]        = "&gt;";    
/* Encoded string for greator than character */
const AxisChar ENCODED_AMPERSAND_STR[]        = "&amp;";    
/* Encoded string for ampersand character */
const AxisChar ENCODED_DBL_QUOTE_STR[]        = "&quot;";    
/* Encoded string for single quote character */
const AxisChar ENCODED_SGL_QUOTE_STR[]        = "&apos;";    
/* Encoded string for double quote character */

/*
 *   @class BasicTypeSerializer
 *   @brief interface for the BasicTypeSerializer class.
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 */

AXIS_CPP_NAMESPACE_START

class BasicTypeSerializer
{
    friend class SoapSerializer;
public:
    BasicTypeSerializer();
    virtual ~BasicTypeSerializer();
    const AxisString& getEntityReferenced(const AxisString& str);
    const AxisChar* serializeAsElement(const AxisChar* pName, 
        const void* pValue, XSDTYPE type);
    const AxisChar* serializeAsAttribute(const AxisChar* pName, 
        const AxisChar* pPrefix, const void* pValue, XSDTYPE type);
    const AxisChar* encodeToHexBinary(const xsd__hexBinary* pBinary);
    const AxisChar* encodeToBase64Binary(const xsd__base64Binary* pBinary);
    void setStyle(AXIS_BINDING_STYLE nStyle){ m_nStyle = nStyle;};
    static const AxisChar* basicTypeStr(XSDTYPE type);

private:
    enum
    {
        GREATOR_THAN_CHAR    =    L'>',    /* Greator than character */
        LESSER_THAN_CHAR    =    L'<',    /* Less than character */
        SINGLE_QUOTE_CHAR    =    L'\'',    /* Single quotation character */
        DOUBLE_QUOTE_CHAR    =    L'\"',    /* Double quotation character */
        AMPERSAND_CHAR        =    L'&'    /* Ampersand character */
    };
private:
    AxisString m_sSZ;
    AxisString m_AuxStr;
    AxisString m_strReturnVal;
    AxisChar m_Buf[BTS_BUFFSIZE]; 
    /* used for numeric to string conversions with sprintf */
    AxisTime m_AxisTime;
    /* Current Serialization Style */
    AXIS_BINDING_STYLE m_nStyle;
};

AXIS_CPP_NAMESPACE_END

#endif 

