/* -*- C++ -*- */
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
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 * @author Roshan Weerasuriya (roshanw@jkcsworld.com, roshan@opensource.lk, roshan_444@yahoo.com)
 *
 */

/*
 * Revision 1.1  2005/01/19 roshan
 * Added decodeFromBase64Binary
 */


#include "AxisUtils.h"
#include <axis/AxisUserAPI.hpp>
#include "../soap/apr_base64.h"

AXIS_CPP_NAMESPACE_START

AxisXMLCh AxisUtils::m_Buffer[CONVERT_BUFFER_SIZE];

AxisUtils::AxisUtils ()
{

}

AxisUtils::~AxisUtils ()
{

}

const AxisXMLCh* AxisUtils::ToAxisXMLCh (const AxisChar* pch)
{
    /* return XMLString::transcode(pch); 
     *     this is ok as long as we use xerces library.
     */
    return pch;
}

void AxisUtils::initialize ()
{
}

/* following functions is not thread safe and should only be used 
 * for initialization purposes.
 */
const AxisXMLCh *
AxisUtils::Convert (const AxisChar * pch)
{

/*    if (XMLString::transcode(pch, m_Buffer, CONVERT_BUFFER_SIZE))
 *        return m_Buffer;
 *    return NULL;
 */
    return pch;
}


int AxisUtils::clearArray (char* arrCh, int iSize)
{
    for (int iTmp = 0; iTmp < iSize; iTmp++)
    {
        arrCh[iTmp] = '\0';
    }

    return AXIS_SUCCESS;
}

bool AxisUtils::isCharacterAvailable (const string &sString,
    const char cCharacter)
{
    bool bFoundStatus = false;

    if ((sString.find (cCharacter, 0)) != string::npos)
    {
        bFoundStatus = true;
    }

    return bFoundStatus;
}

bool AxisUtils::isCharacterAvailable (const char* pchStringToSearch,
    const char cCharacter)
{
    bool bFoundStatus = false;

    if (strchr (pchStringToSearch, cCharacter))
    {
        bFoundStatus = true;
    }

    return bFoundStatus;
}

string AxisUtils::toUpperCase (const string sWord)
{
    /* Fill the code */

    return NULL;
}

char* AxisUtils::toUpperCase (const char* pchWord)
{
    /* Fill the code */

    return NULL;
}

string AxisUtils::toLowerCase (const string sWord)
{
    /* Fill the code */

    return NULL;
}

char* AxisUtils::toLowerCase (const char* pchWord)
{
    /* Fill the code */

    return NULL;
}

xsd__base64Binary * AxisUtils::decodeFromBase64Binary(const AxisChar *pValue)
{
    xsd__base64Binary* value = new xsd__base64Binary();
	int size = apr_base64_decode_len (pValue);
	xsd__unsignedByte * pTemp = new unsigned char[size + 1];
	size = apr_base64_decode_binary (pTemp, pValue);
	pTemp[size] = 0; // Null terminate so it could be used as a string
	value->set(pTemp, size);
	delete [] pTemp;
    return value;
}

bool AxisUtils::isStringOnlyWithSpaces(const char* pchWord)
{
	bool blnStatus = true;

	int iLen = strlen(pchWord);

	for (int i=0; i<iLen; i++) {	
		if (pchWord[i] != ' ') {
			blnStatus = false;	
			break;
		}
	}

	return blnStatus;
}

IAnySimpleType* AxisUtils::createSimpleTypeObject(XSDTYPE type)
{
    return createSimpleTypeObject(NULL, type);
}

IAnySimpleType* AxisUtils::createSimpleTypeObject(void * pValue, XSDTYPE type)
{
    IAnySimpleType* xsdValue = NULL;
    switch (type)
    {
        case XSD_FLOAT:
            xsdValue = new Float((xsd__float*) pValue);
            break;
        case XSD_BOOLEAN:
            xsdValue = new Boolean((xsd__boolean*) pValue);
            break;
        case XSD_DOUBLE:
            xsdValue = new Double((xsd__double*) pValue);
            break;
        case XSD_DURATION:
            xsdValue = new Duration((xsd__duration*) pValue);
            break;
        case XSD_DATETIME:
            xsdValue = new DateTime((xsd__dateTime*) pValue);
            break;
        case XSD_TIME:
            xsdValue = new Time((xsd__time*) pValue);
            break;
        case XSD_DATE:
            xsdValue = new Date((xsd__date*) pValue);
            break;
        case XSD_GYEARMONTH:
            xsdValue = new GYearMonth((xsd__gYearMonth*) pValue);
            break;
        case XSD_GYEAR:
            xsdValue = new GYear((xsd__gYear*) pValue);
            break;
        case XSD_GMONTHDAY:
            xsdValue = new GMonthDay((xsd__gMonthDay*) pValue);
            break;
        case XSD_GDAY:
            xsdValue = new GDay((xsd__gDay*) pValue);
            break;
        case XSD_GMONTH:
            xsdValue = new GMonth((xsd__gMonth*) pValue);
            break;
        case XSD_HEXBINARY:
            xsdValue = new HexBinary((xsd__hexBinary*) pValue);
            break;
        case XSD_BASE64BINARY:
            xsdValue = new Base64Binary((xsd__base64Binary*) pValue);
            break;
        case XSD_ANYURI:
            xsdValue = new AnyURI((xsd__anyURI) pValue);
            break;
        case XSD_QNAME:
            xsdValue = new XSD_QName((xsd__QName) pValue);
            break;
        case XSD_NOTATION:
            xsdValue = new NOTATION((xsd__NOTATION) pValue);
            break;
        case XSD_DECIMAL:
            xsdValue = new Decimal((xsd__decimal*) pValue);
            break;
        case XSD_INTEGER:
            xsdValue = new Integer((xsd__integer*) pValue);
            break;
        case XSD_LONG:
            xsdValue = new Long((xsd__long*) pValue);
            break;
        case XSD_INT:
            xsdValue = new Int((xsd__int*) pValue);
            break;
        case XSD_SHORT:
            xsdValue = new Short((xsd__short*) pValue);
            break;
        case XSD_BYTE:
            xsdValue = new Byte((xsd__byte*) pValue);
            break;
        case XSD_NONNEGATIVEINTEGER:
            xsdValue = new NonNegativeInteger((xsd__nonNegativeInteger*) pValue);
            break;
        case XSD_UNSIGNEDLONG:
            xsdValue = new UnsignedLong((xsd__unsignedLong*) pValue);
            break;
        case XSD_UNSIGNEDINT:
            xsdValue = new UnsignedInt((xsd__unsignedInt*) pValue);
            break;
        case XSD_UNSIGNEDSHORT:
            xsdValue = new UnsignedShort((xsd__unsignedShort*) pValue);
            break;
        case XSD_UNSIGNEDBYTE:
            xsdValue = new UnsignedByte((xsd__unsignedByte*) pValue);
            break;
        case XSD_POSITIVEINTEGER:
            xsdValue = new PositiveInteger((xsd__positiveInteger*) pValue);
            break;
        case XSD_NONPOSITIVEINTEGER:
            xsdValue = new NonPositiveInteger((xsd__nonPositiveInteger*) pValue);
            break;
        case XSD_NEGATIVEINTEGER:
            xsdValue = new NegativeInteger((xsd__negativeInteger*) pValue);
            break;
        case XSD_STRING:
            xsdValue = new String((xsd__string) pValue);
            break;
        case XSD_NORMALIZEDSTRING:
            xsdValue = new NormalizedString((xsd__normalizedString) pValue);
            break;
        case XSD_TOKEN:
            xsdValue = new Token((xsd__token) pValue);
            break;
        case XSD_LANGUAGE:
            xsdValue = new Language((xsd__language) pValue);
            break;
        case XSD_NAME:
            xsdValue = new Name((xsd__Name) pValue);
            break;
        case XSD_NCNAME:
            xsdValue = new NCName((xsd__NCName) pValue);
            break;
        case XSD_ID:
            xsdValue = new ID((xsd__ID) pValue);
            break;
        case XSD_IDREF:
            xsdValue = new IDREF((xsd__IDREF) pValue);
            break;
        case XSD_IDREFS:
            xsdValue = new IDREFS((xsd__IDREFS) pValue);
            break;
        case XSD_ENTITY:
            xsdValue = new ENTITY((xsd__ENTITY) pValue);
            break;
        case XSD_ENTITIES:
            xsdValue = new ENTITIES((xsd__ENTITIES) pValue);
            break;
        case XSD_NMTOKEN:
            xsdValue = new NMTOKEN((xsd__NMTOKEN) pValue);
            break;
        case XSD_NMTOKENS:
            xsdValue = new NMTOKENS((xsd__NMTOKENS) pValue);
            break;
        default:
            break;
    }
    
    return xsdValue;
}

AXIS_CPP_NAMESPACE_END



