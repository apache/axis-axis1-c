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

xsd__base64Binary* AxisUtils::decodeFromBase64Binary(const AxisChar *pValue)
{
    xsd__base64Binary* value = new xsd__base64Binary();
    value->__size = apr_base64_decode_len (pValue);
    value->__ptr = new unsigned char[value->__size + 1];
    value->__size = apr_base64_decode_binary (value->__ptr, pValue);
    /* put null at the end because it enables the decoded string to be used
     * as a string 
     */
    value->__ptr[value->__size] = 0;

    return value;
}


AXIS_CPP_NAMESPACE_END
