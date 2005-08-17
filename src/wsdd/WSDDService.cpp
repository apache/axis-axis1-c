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
 * @author Sanjaya Singharage
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */



#include "WSDDService.h"
#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

WSDDService::WSDDService()
{
    m_RequestHandlers = NULL;
    m_ResponseHandlers = NULL;
    m_Provider = UNKNOWN_PROVIDER;
}

WSDDService::~WSDDService()
{
    WSDDHandlerList::iterator iter;
    if(m_RequestHandlers)
    {
        for(iter=m_RequestHandlers->begin();iter!=m_RequestHandlers->end();
        iter++)
        {
            delete (*iter);
        }
        delete m_RequestHandlers;
    }

    if(m_ResponseHandlers)
    {
        for(iter=m_ResponseHandlers->begin();iter!=m_ResponseHandlers->end();
        iter++)
        {
            delete (*iter);
        }
        delete m_ResponseHandlers;
    }
}

void WSDDService::setProvider(const AxisChar* sProvider)
{
    if (0 == strcmp(sProvider, "CPP:RPC"))
    {
        m_Provider = CPP_RPC_PROVIDER;
    }
    else if (0 == strcmp(sProvider, "C:RPC"))
    {
        m_Provider = C_RPC_PROVIDER;
    }
    else if (0 == strcmp(sProvider, "CPP:DOCUMENT"))
    {
        m_Provider = CPP_DOC_PROVIDER;
    }
    else if (0 == strcmp(sProvider, "C:DOCUMENT"))
    {
        m_Provider = C_DOC_PROVIDER;
    }
    else if (0 == strcmp(sProvider, "MS:COM"))
    {
        m_Provider = COM_PROVIDER;
    }
    else
    {
        m_Provider = UNKNOWN_PROVIDER;
    }
}

PROVIDERTYPE WSDDService::getProvider() const
{
    return m_Provider;
}

const AxisChar* WSDDService::getServiceName() const
{
    return m_sName.c_str();
}

void WSDDService::addAllowedMethod(const AxisChar* sMethodName)
{
    m_AllowedMethods.push_back(sMethodName);
}

bool WSDDService::isAllowedMethod(const AxisChar* sServiceName) const
{
    if (m_AllowedMethods.size() == 0) //no allowedMethods mentioned in wsdd, hence assume all are allowed
        return true; // assume that the method is allowd if allowedMethods missing

    list<AxisString>::const_iterator iter;
    iter = m_AllowedMethods.begin();

    if ((*iter) == "*")
    {
        return true;
    }

    for(iter = m_AllowedMethods.begin();iter != m_AllowedMethods.end();iter++)
    {
        if((*iter) == sServiceName)
        {
            return true;
        }
    }
    return false;
}

const WSDDHandlerList* WSDDService::getRequestFlowHandlers() const
{
    return m_RequestHandlers;
}

const WSDDHandlerList* WSDDService::getResponseFlowHandlers() const
{
    return m_ResponseHandlers;
}

void WSDDService::addAllowedRole(const AxisChar* sRole)
{
    m_AllowedRoles.push_back(sRole);
}

const list<AxisString>& WSDDService::getAllowedRoles()
{
    return m_AllowedRoles;
}

void  WSDDService::addHandler(bool bRequestFlow, WSDDHandler* pHandler)
{
    if (bRequestFlow)
    {
        if (!m_RequestHandlers) m_RequestHandlers = new WSDDHandlerList;
        m_RequestHandlers->push_back(pHandler);
    }
    else
    {
        if (!m_ResponseHandlers) m_ResponseHandlers = new WSDDHandlerList;
        m_ResponseHandlers->push_back(pHandler);
    }
}

/*
 * This method removes the service specific handler of this service. But the entry
 * in WSDDDeployment's <LibId, LibName> is not removed because the same handler may
 * be in use by other services. 
 */
int WSDDService::removeHandler(bool bRequestFlow, WSDDHandler* pHandler)
{
    WSDDHandlerList* pTempList = 
        bRequestFlow ? m_RequestHandlers : m_ResponseHandlers;
    if (!pTempList) return AXIS_NO_SUCH_HANDLER;
    for (WSDDHandlerList::iterator itr = pTempList->begin();
         itr != pTempList->end(); itr++)
    {
        if (strcmp((*itr)->getLibName(), pHandler->getLibName()) == 0)
        {
            pTempList->remove(*itr);
            delete (*itr);
            delete pHandler;
            return AXIS_SUCCESS;
        }
    }
    return AXIS_NO_SUCH_HANDLER;
}

const list<AxisString> WSDDService::getAllowedMethods() const
{
    return m_AllowedMethods;
}

int WSDDService::updateWSDD(FILE* wsddfile, int tabcount)
{
    m_file = wsddfile;
    printTabs(tabcount); *this << "<service name=\"" << 
        m_sName.c_str() << "\" provider=\"" << getProviderString() << 
        "\" description=\"" << m_sDescription.c_str() << "\">\n";
    if (m_Params)
    {
        map<AxisString, AxisString>::iterator itr;
        for (itr = m_Params->begin(); itr != m_Params->end(); itr++)
        {
            printTabs(tabcount+1); *this << "<parameter name=\"" << 
                (*itr).first.c_str() << "\" value=\"" << 
                (*itr).second.c_str() << "\" />";
        }
    }
    WSDDHandlerList::iterator iter;
    if(m_RequestHandlers)
    {
        *this << "\t\t<requestFlow>\n";
        for(iter=m_RequestHandlers->begin(); iter!=m_RequestHandlers->end();
            iter++)
        {
            (*iter)->updateWSDD(wsddfile, 3);
        }
        *this << "\t\t</requestFlow>\n";
    }

    if(m_ResponseHandlers)
    {
        *this << "\t\t<responseFlow>\n";
        for(iter=m_ResponseHandlers->begin(); iter!=m_ResponseHandlers->end(); 
        iter++)
        {
            (*iter)->updateWSDD(wsddfile, 3);
        }
        *this << "\t\t</responseFlow>\n";
    }
    printTabs(tabcount+1); *this <<
        "<parameter name=\"allowedMethods\" value=\"";
    /* for looop */
    for (list<AxisString>::iterator itrs = m_AllowedMethods.begin();
    itrs != m_AllowedMethods.end(); itrs++)
    {
        *this << (*itrs).c_str() << " ";
    }
    *this << "\"/>\n"; 
    printTabs(tabcount+1); *this << "<parameter name=\"className\" value=\"" 
        << m_sLibName.c_str();
    *this << "\" />\n"; 
    printTabs(tabcount); *this << "</service>\n";
    m_file = 0;
    return AXIS_SUCCESS;
}

const char* WSDDService::getProviderString()
{
    switch(m_Provider)
    {
    case C_RPC_PROVIDER: return "C:RPC";
    case C_DOC_PROVIDER: return "C:DOCUMENT";
    case CPP_RPC_PROVIDER: return "CPP:RPC";
    case CPP_DOC_PROVIDER: return "CPP:DOCUMENT";
    case COM_PROVIDER: return "COM";
    default: return "unknown";
    }
    return 0;
}

AXIS_CPP_NAMESPACE_END
