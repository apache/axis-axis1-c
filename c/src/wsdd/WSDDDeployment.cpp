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
 *   @author Sanjaya Singharage
 *   @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *   @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */

#include "WSDDDeployment.h"

#ifdef USE_EXPAT_PARSER
#include "WSDDDocumentExpat.h"
#define WSDDDOCUMENTPARSER WSDDDocumentExpat
#elif USE_XERCES_PARSER
#include "WSDDDocumentXerces.h"
#define WSDDDOCUMENTPARSER WSDDDocumentXerces
#else
#include "WSDDDocumentTXPP.h"
#define WSDDDOCUMENTPARSER WSDDDocumentTXPP
#endif

#include <axis/server/GDefine.h>
#include <axis/server/AxisConfig.h>
#include <axis/server/AxisTrace.h>

extern AxisTrace* g_pAT;

WSDDDeployment::WSDDDeployment()
{
    m_DeployedServices = NULL;
    m_sAux = "";
    m_pTransportHandlers = NULL;
    m_GlobalResponseHandlers = NULL;
    m_GlobalRequestHandlers = NULL;
    m_DeplType = DT_DEPLOYMENT;
    m_pLibNameIdMap = new map<AxisString, int>;
}

WSDDDeployment::~WSDDDeployment()
{
    WSDDHandlerList::iterator iter;
    if(m_pTransportHandlers)
    {
        delete m_pTransportHandlers;
    }

    if(m_GlobalRequestHandlers)
    {
        for(iter=m_GlobalRequestHandlers->begin();
                iter!=m_GlobalRequestHandlers->end();iter++)
        {
            delete (*iter);
        }
    }

    if(m_GlobalResponseHandlers)
    {
        for(iter=m_GlobalResponseHandlers->begin();
                iter!=m_GlobalResponseHandlers->end();iter++)
        {
            delete (*iter);
        }
    }

    WSDDServiceMap::iterator iter2;
    if(m_DeployedServices)
    {
        for(iter2=m_DeployedServices->begin()
                ;iter2!=m_DeployedServices->end();iter2++)
        {
            delete ((*iter2).second);
        }
    }
    delete m_pLibNameIdMap;
}

const WSDDHandlerList* WSDDDeployment::getGlobalRequestFlowHandlers()
{
    return m_GlobalRequestHandlers;
}

const WSDDHandlerList* WSDDDeployment::getGlobalResponseFlowHandlers()
{
    return m_GlobalResponseHandlers;
}

int WSDDDeployment::updateWSDD(const AxisChar* sWSDD)
{
    WSDDDocument* doc = new WSDDDOCUMENTPARSER(m_pLibNameIdMap);
    if (AXIS_SUCCESS != doc->updateDeployment(sWSDD, this))
    {
        delete doc;
        return AXIS_FAIL;
    }
    delete doc;
    saveWSDD();
    return AXIS_SUCCESS;        
}

int WSDDDeployment::loadWSDD(const AxisChar* sWSDD)
{
    m_sWSDDPath = string(sWSDD);
    WSDDDocument* doc = new WSDDDOCUMENTPARSER(m_pLibNameIdMap);
    if (AXIS_SUCCESS != doc->getDeployment(sWSDD, this))
    {
            printf("wsdd loading failed\n");
        delete doc;
        return AXIS_FAIL;
    }
#ifdef _DEBUG
    printf("wsdd loading successful\n");
#endif
    delete doc;
    return AXIS_SUCCESS;
}

int WSDDDeployment::saveWSDD()
{
    FILE* file;
    int Status = AXIS_FAIL;
    /* TODO we have to rename the existing server.wsdd to server.wsdd.old
     * and if anything went wrong we have to rename it back to server.wsdd
     */
    file = fopen(m_sWSDDPath.c_str(), "w");
    if(!file) return AXIS_FAIL;
    do
    {
        if (fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n", file) < 0) 
            break;
        if (fputs("<deployment xmlns=\"http://xml.apache.org/axis/wsdd/\
            \" xmlns:C=\"http://xml.apache.org/axis/wsdd/providers/C\" xmlns:\
            CPP=\"http://xml.apache.org/axis/wsdd/providers/CPP\">\n",
            file) < 0) break;
        if (fputs("\t<globalConfiguration>\n", file) < 0) break;
        WSDDHandlerList::iterator iter;
        if(m_GlobalRequestHandlers)
        {
            if (fputs("\t\t<requestFlow>\n", file) < 0) break;
            for(iter=m_GlobalRequestHandlers->begin();
            iter!=m_GlobalRequestHandlers->end(); iter++)
            {
                (*iter)->updateWSDD(file, 3);
            }
            if (fputs("\t\t</requestFlow>\n", file) < 0) break;
        }

        if(m_GlobalResponseHandlers)
        {
            if (fputs("\t\t<responseFlow>\n", file) < 0) break;
            for(iter=m_GlobalResponseHandlers->begin();
            iter!=m_GlobalResponseHandlers->end(); iter++)
            {
                (*iter)->updateWSDD(file, 3);
            }
            if (fputs("\t\t</responseFlow>\n", file) < 0) break;
        }

        if (fputs("\t</globalConfiguration>\n", file) < 0) break;

        if(m_pTransportHandlers)
        {
            m_pTransportHandlers->updateWSDD(file, 3);
        }

        WSDDServiceMap::iterator iter2;
        if(m_DeployedServices)
        {
            for(iter2=m_DeployedServices->begin();
            iter2!=m_DeployedServices->end(); iter2++)
            {
                ((*iter2).second)->updateWSDD(file, 1);
            }
        }
        
        if (fputs("</deployment>", file) < 0) break;
    } while(0);
    fflush(file);
    fclose(file);
    if (AXIS_SUCCESS != Status)
    {
        /*TODO use the previous server.wsdd file itself. Undo renaming*/
    }
    return AXIS_SUCCESS;
}


const WSDDService* WSDDDeployment::getService(const AxisChar* sServiceName)
{
    WSDDServiceMap::iterator iter;
    if (!m_DeployedServices) return NULL;
    iter = m_DeployedServices->find(sServiceName);
    if (iter != m_DeployedServices->end())
    {
        return (*iter).second;
    }
    else
    {
        return NULL;
    }
}

const WSDDServiceMap* WSDDDeployment::getWSDDServiceMap() const
{
    return m_DeployedServices;
}

const AxisChar* WSDDDeployment::getLibName(int nLibId)
{
    for (map<AxisString, int>::iterator it = m_pLibNameIdMap->begin();
    it != m_pLibNameIdMap->end(); it++)
    {
        if ((*it).second == nLibId)
        {
            return (*it).first.c_str();
        }
    }
    return NULL;
}

int WSDDDeployment::addService(WSDDService* pService)
{
    if (!m_DeployedServices) m_DeployedServices = new WSDDServiceMap;
    if (m_DeployedServices->find(pService->getServiceName()) != 
        m_DeployedServices->end())
    {
        AXISTRACE1("The service already exists and the attempt to re-deploy \
            is ignored", WARN);
    }
    else
    {
        (*m_DeployedServices)[pService->getServiceName()] = pService;
    }
    return AXIS_SUCCESS;
}        

int WSDDDeployment::addHandler(bool bGlobal, bool bRequestFlow,
                               WSDDHandler* pHandler, 
                               AXIS_PROTOCOL_TYPE protocol)
{
    if (bGlobal)
    {
        if (bRequestFlow)
        {
            if(!m_GlobalRequestHandlers) m_GlobalRequestHandlers = 
                new WSDDHandlerList;
            m_GlobalRequestHandlers->push_back(pHandler);
        }
        else
        {
            if(!m_GlobalResponseHandlers) m_GlobalResponseHandlers = 
                new WSDDHandlerList;
            m_GlobalResponseHandlers->push_back(pHandler);
        }
    }
    else /* transport */
    {
        if (!m_pTransportHandlers) m_pTransportHandlers = new WSDDTransport();
        m_pTransportHandlers->addHandler(bRequestFlow, protocol, pHandler);
    }
    return AXIS_SUCCESS;
}

const WSDDHandlerList* WSDDDeployment::getTransportRequestFlowHandlers
    (AXIS_PROTOCOL_TYPE protocol)
{
    if (!m_pTransportHandlers) return NULL;
    return m_pTransportHandlers->getRequestFlowHandlers(protocol);
}

const WSDDHandlerList* WSDDDeployment::getTransportResponseFlowHandlers
    (AXIS_PROTOCOL_TYPE protocol)
{
    if (!m_pTransportHandlers) return NULL;
    return m_pTransportHandlers->getResponseFlowHandlers(protocol);
}

int WSDDDeployment::removeService(WSDDService* pService)
{
    if (m_DeployedServices && 
        (m_DeployedServices->find(pService->getServiceName()) != 
        m_DeployedServices->end()))
    {
        WSDDService* pTheService = 
            (*m_DeployedServices)[pService->getServiceName()];
        m_pLibNameIdMap->erase(pTheService->getLibName());
        m_DeployedServices->erase(pService->getServiceName());
        delete pTheService;    
        delete pService;
        return AXIS_SUCCESS;
    }
    return AXIS_NO_SUCH_SERVICE;
}

int WSDDDeployment::removeHandler(bool bGlobal, bool bRequestFlow, 
                                  WSDDHandler* pHandler, 
                                  AXIS_PROTOCOL_TYPE protocol)
{
    m_pLibNameIdMap->erase(pHandler->getLibName());
    if (bGlobal)
    {
        WSDDHandlerList* pTempList = 
            bRequestFlow ? m_GlobalRequestHandlers : m_GlobalResponseHandlers;
        if(pTempList)
        {
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
        }
    }
    else /* transport */
    {
        if (!m_pTransportHandlers) return AXIS_NO_SUCH_HANDLER;
        return m_pTransportHandlers->removeHandler(bRequestFlow, 
            protocol, pHandler);
    }
    return AXIS_NO_SUCH_HANDLER;    
}

DEPLOYMENTTYPE WSDDDeployment::getDeploymentType() const
{
    return m_DeplType;
}

void WSDDDeployment::setDeploymentType(DEPLOYMENTTYPE nType)
{
    m_DeplType = nType;
}


