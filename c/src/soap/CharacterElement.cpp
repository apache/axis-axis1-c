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

/*
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

/* haracterElement.cpp: implementation of the CharacterElement class. */


#include <axis/server/CharacterElement.h>
#include <axis/server/SoapSerializer.h>
#include <axis/server/GDefine.h>

CharacterElement::CharacterElement()
{
    m_iNodeType= CHARACTER_NODE;
    m_pachValue = '\0';
}

CharacterElement::CharacterElement(const AxisChar* pachValue)
{
    m_pachValue = (AxisChar*) malloc(strlen(pachValue)+1);
    strcpy(m_pachValue, pachValue);
    m_iNodeType= CHARACTER_NODE;
}

CharacterElement::~CharacterElement()
{
    free(m_pachValue);
}

NODE_TYPE CharacterElement::getNodeType() const
{
    return m_iNodeType;
}

int CharacterElement::serialize(SoapSerializer& pSZ)
{
    if (m_pachValue != NULL)
    {
        pSZ.Serialize(m_pachValue, NULL);
        return AXIS_SUCCESS;
    }
    else
    {
        return AXIS_FAIL;
    }
}

const AxisChar* CharacterElement::getValue() const
{
    return m_pachValue;
}

int CharacterElement::setValue(const AxisChar* pachValue)
{
    m_pachValue = (AxisChar*) malloc(strlen(pachValue)+1);
    strcpy(m_pachValue, pachValue);

    return AXIS_SUCCESS;
}

bool CharacterElement::operator == ( const CharacterElement &objChEle) 
{
    if (strcmp(objChEle.m_pachValue , m_pachValue) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}
