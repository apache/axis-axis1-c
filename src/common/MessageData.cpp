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
 *
 */


#include "../common/MessageData.h"
#include "IDeployerUtils.h"
#include "../wsdd/WSDDDeployment.h"

extern AXIS_CPP_NAMESPACE_PREFIX WSDDDeployment* g_pWSDDDeployment;

AXIS_CPP_NAMESPACE_START

const AxisChar* MessageData::m_pachBlankPropertyValue = "";
AdminUtils MessageData::m_AdminUtil;

MessageData::MessageData ()
{
    m_pSZ = NULL;
    m_pDZ = NULL;
    m_bPastPivotState = false;
}

MessageData::~MessageData ()
{
    map < const AxisChar*, const AxisChar*, ltstr >::const_iterator itCurrentItem =
        m_Properties.begin ();

    while (itCurrentItem != m_Properties.end ())
    {
        delete [] (char*)(*itCurrentItem).first;
		delete [] (char*)(*itCurrentItem).second;

        itCurrentItem++;
    }

    m_Properties.clear ();
}

void MessageData::setSerializer (IWrapperSoapSerializer* pSZ)
{
    m_pSZ = pSZ;
}

void MessageData::setDeSerializer (IWrapperSoapDeSerializer* pDZ)
{
    m_pDZ = pDZ;
}

void MessageData::setOperationName(const AxisChar* pchOperation)
{
	m_sOperationName = pchOperation;
}
const AxisChar* MessageData::getOperationName()
{
	return m_sOperationName.c_str();
}

void MessageData::setUserName (string &sUserName)
{
    m_sUserName = sUserName;
}

string &MessageData::getUserName ()
{
    return m_sUserName;
    // return "damitha kumarage"; 
}

void MessageData::setService (const WSDDService* argService)
{
    m_Service = argService;
}

const WSDDService* MessageData::getService ()
{
    return m_Service;
}

/*
 *    comm on 25Jul2003 at 10.00am
 *    ISoapSerializer* MessageData::getSoapSerializer()
 *    {
 *        return m_pSZ;
 *    }
 */

IWrapperSoapDeSerializer* MessageData::getSoapDeserializer ()
{
    return m_pDZ;
}

bool MessageData::isPastPivot ()
{
    return m_bPastPivotState;
}

int MessageData::setPastPivotState (bool bState)
{
    m_bPastPivotState = bState;

    return AXIS_SUCCESS;
}

void MessageData::getSoapSerializer 
    (IHandlerSoapSerializer** pIHandlerSoapSerializer)
{
    *pIHandlerSoapSerializer = static_cast < IHandlerSoapSerializer* >(m_pSZ);
}

void MessageData::getSoapSerializer (IWrapperSoapSerializer**
    pIWrapperSoapSerializer)
{
    *pIWrapperSoapSerializer = static_cast < IWrapperSoapSerializer* >(m_pSZ);
}

void MessageData::getSoapDeSerializer (IWrapperSoapDeSerializer**
    pIWrapperSoapDeSerializer)
{
    *pIWrapperSoapDeSerializer = 
        static_cast < IWrapperSoapDeSerializer* >(m_pDZ);
}

void MessageData::getSoapDeSerializer (IHandlerSoapDeSerializer**
    pIHandlerSoapDeSerializer)
{
    *pIHandlerSoapDeSerializer = 
        static_cast < IHandlerSoapDeSerializer * >(m_pDZ);
}



int MessageData::setProperty (const AxisChar* pachName, const AxisChar* pachValue)
{
    AxisChar* pachTmpName = new AxisChar[strlen (pachName) + 1];
    strcpy (pachTmpName, pachName);
    AxisChar* pachTmpValue = new AxisChar[strlen (pachValue) + 1];
    strcpy (pachTmpValue, pachValue);

    m_Properties[pachTmpName] = pachTmpValue;

    return AXIS_SUCCESS;
}

int MessageData::setProperty (const AxisChar* pachName, const void* pachValue, int len)
{
     AxisChar* pachTmpName = new AxisChar[strlen (pachName) + 1];
     strcpy (pachTmpName, pachName);
     AxisChar* pachTmpValue = new AxisChar[len];
     memcpy (pachTmpValue, pachValue, len);
 
     m_Properties[pachTmpName] = pachTmpValue;
 
     return AXIS_SUCCESS;
}

void MessageData::setComplexProperty(const AxisChar* pachName, void* pValue, int iObjectSize)
{
    AxisChar* pachTmpName = new AxisChar[strlen (pachName) + 1];
    strcpy (pachTmpName, pachName);
    void* pchTmpObject = malloc(iObjectSize);
    pchTmpObject = pValue;

    m_ComplexProperties[pachTmpName] = pchTmpObject;
}

/*
 *    The method caller has to check whether the returned string is empty or
 *    not. If it is empty then the idea is that the property is not 
 *    available.
 */
const void* MessageData::getProperty (const AxisChar* pachName)
{
    if (m_Properties.find (pachName) != m_Properties.end ())
    {
        return m_Properties[pachName];
    }

    return m_pachBlankPropertyValue;
}

void* MessageData::getComplexProperty(const AxisChar* pachName)
{
    if (m_ComplexProperties.find (pachName) != m_ComplexProperties.end ())
    {
        return m_ComplexProperties[pachName];
    }
                                                                                                                                                                            
    return NULL;	
}

void MessageData::getAdminUtils (IAdminUtils** pIAdminUtils)
{
    *pIAdminUtils = &m_AdminUtil;
}


AXIS_CPP_NAMESPACE_END
