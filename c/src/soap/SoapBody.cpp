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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

/* SoapBody.cpp: implementation of the SoapBody class. */

/*
 * Revision 1.1  2004/June/02 roshan
 * Added the parameter "eSoapVersion" to the call of m_pSoapFault->serialize
 * method. The SoapFault class is expecting this parameter to determine the
 * SoapVersion.
 */

#include "SoapBody.h"
#include <axis/server/SoapSerializer.h>
#include <axis/server/GDefine.h>
#include <axis/server/Attribute.h>
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

SoapBody::SoapBody()
{
    m_pSoapMethod= NULL;
    m_pSoapFault= NULL;
}

SoapBody::~SoapBody()
{
    if(m_pSoapMethod)
    {
        delete m_pSoapMethod;
    }

    if(m_pSoapFault)
    {
        delete m_pSoapFault;
    }
}

void SoapBody::setSoapMethod(SoapMethod* ptrSoapMethod)
{
    m_pSoapMethod= ptrSoapMethod;
}

void SoapBody::setSoapFault(SoapFault *pSoapFault)
{
    m_pSoapFault= pSoapFault;
}

int SoapBody::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{
    int iStatus= AXIS_SUCCESS;

    do
    {        
        pSZ.serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_BODY],
            NULL);
        iStatus= serializeAttributes(pSZ);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        
        pSZ.serialize(">", NULL);

        if(NULL != m_pSoapFault) 
        {        
            iStatus= m_pSoapFault->serialize(pSZ, eSoapVersion);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
        }
        else if(NULL != m_pSoapMethod)
        {
            iStatus= m_pSoapMethod->serialize(pSZ);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
        } 
        else
        {
            m_pSoapFault = SoapFault::getSoapFault(SERVER_ENGINE_WEBSERVICE_FAILED);
            if(m_pSoapFault!=NULL) 
            {        
                iStatus= m_pSoapFault->serialize(pSZ, eSoapVersion);
                if(iStatus==AXIS_FAIL) 
                    break;
            }
        }
        
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_BODY],
            ">", NULL);
    } while(0);

    return iStatus;
}

void SoapBody::addAttribute(Attribute *attr)
{
    m_attributes.push_back(attr);
}

int SoapBody::serializeAttributes(SoapSerializer& pSZ)
{
    int iStatus= AXIS_SUCCESS;

    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {        

        iStatus= (*itCurrAttribute)->serialize(pSZ);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        itCurrAttribute++;        
    }    

    return iStatus;
}

int SoapBody::initializeForTesting()
{
    SoapMethod* pSoapMethod = new SoapMethod();
    pSoapMethod->initializeForTesting();

    setSoapMethod(pSoapMethod);

    return AXIS_SUCCESS;
}

