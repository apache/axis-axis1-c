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


#include <axis/server/MessageData.h>
#include "IDeployerUtils.h"
#include "../wsdd/WSDDDeployment.h"

const AxisChar* MessageData::m_pachBlankPropertyValue = "";
extern WSDDDeployment* g_pWSDDDeployment;
IMessageDataFunctions IMessageData::ms_VFtable;
AdminUtils MessageData::m_AdminUtil;

MessageData::MessageData ()
{
    m_pSZ = NULL;
    m_pDZ = NULL;
    m_bPastPivotState = false;
}

MessageData::~MessageData ()
{
    map < AxisChar*, AxisChar*, ltstr >::iterator itCurrentItem =
        m_Properties.begin ();

    while (itCurrentItem != m_Properties.end ())
    {
        free ((*itCurrentItem).first);
        free ((*itCurrentItem).second);

        itCurrentItem++;
    }

    m_Properties.clear ();
}

void MessageData::SetSerializer (SoapSerializer* pSZ)
{
    m_pSZ = pSZ;
}

void MessageData::SetDeSerializer (SoapDeSerializer* pDZ)
{
    m_pDZ = pDZ;
}

void MessageData::SetUserName (string &sUserName)
{
    m_sUserName = sUserName;
}

string &MessageData::GetUserName ()
{
    return m_sUserName;
    // return "damitha kumarage"; 
}

void MessageData::SetService (const WSDDService* argService)
{
    m_Service = argService;
}

const WSDDService* MessageData::GetService ()
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

void MessageData::GetSoapSerializer (IWrapperSoapSerializer**
    pIWrapperSoapSerializer)
{
    *pIWrapperSoapSerializer = static_cast < IWrapperSoapSerializer* >(m_pSZ);
}

void MessageData::GetSoapDeSerializer (IWrapperSoapDeSerializer**
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

int MessageData::setProperty (AxisChar* pachName, const AxisChar* pachValue)
{
    AxisChar* pachTmpName = (AxisChar*) malloc (strlen (pachName) + 1);
    strcpy (pachTmpName, pachName);
    AxisChar* pachTmpValue = (AxisChar*) malloc (strlen (pachValue) + 1);
    strcpy (pachTmpValue, pachValue);

    m_Properties[pachTmpName] = pachTmpValue;

    return AXIS_SUCCESS;
}

/*
 *    The method caller has to check whether the returned string is empty or
 *    not. If it is empty then the idea is that the property is not 
 *    available.
 */
const AxisChar* MessageData::getProperty (AxisChar* pachName)
{
    if (m_Properties.find (pachName) != m_Properties.end ())
    {
        return m_Properties[pachName];
    }

    return m_pachBlankPropertyValue;
}

void MessageData::GetAdminUtils (IAdminUtils** pIAdminUtils)
{
    *pIAdminUtils = &m_AdminUtil;
}
