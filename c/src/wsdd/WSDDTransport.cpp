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
 *
 */



#include "../wsdd/WSDDTransport.h"



WSDDTransport::WSDDTransport()
{
    m_RequestHandlers = NULL;
    m_ResponseHandlers = NULL;
}

WSDDTransport::~WSDDTransport()
{
    map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>::iterator iter;
    /* WSDDHandlerList * hl = NULL; */
    WSDDHandlerList::iterator iter2;
    if(m_RequestHandlers)
    {
        for(iter = m_RequestHandlers->begin(); iter !=
            m_RequestHandlers->end(); iter++)
        {
            for(iter2 = (*iter).second.begin(); iter2 != 
                (*iter).second.end(); iter2++)
            {
                delete (*iter2);
            }
        }
    }

    if(m_ResponseHandlers)
    {
        for(iter = m_ResponseHandlers->begin(); iter != 
            m_ResponseHandlers->end(); iter++)
        {
            for(iter2 = (*iter).second.begin(); iter2 != 
                (*iter).second.end();iter2++)
            {
                delete (*iter2);
            }
        }
    }
}

const WSDDHandlerList* WSDDTransport::GetRequestFlowHandlers
(AXIS_PROTOCOL_TYPE Protocol)
{
    if (m_RequestHandlers && m_RequestHandlers->find(Protocol) !=
        m_RequestHandlers->end())
        return &(*m_RequestHandlers)[Protocol];
    return NULL;
}


const WSDDHandlerList* WSDDTransport::GetResponseFlowHandlers
(AXIS_PROTOCOL_TYPE Protocol)
{
    if (m_ResponseHandlers && m_ResponseHandlers->find(Protocol) !=
        m_ResponseHandlers->end())
        return &(*m_ResponseHandlers)[Protocol];
    return NULL;
}

void WSDDTransport::AddHandler(bool bRequestFlow, AXIS_PROTOCOL_TYPE protocol,
                               WSDDHandler* pHandler)
{
    if (bRequestFlow)
    {
        if (!m_RequestHandlers) m_RequestHandlers = new map<AXIS_PROTOCOL_TYPE,
            WSDDHandlerList>;
        (*m_RequestHandlers)[protocol].push_back(pHandler);
    }
    else
    {
        if (!m_ResponseHandlers) m_ResponseHandlers = 
            new map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>;
        (*m_ResponseHandlers)[protocol].push_back(pHandler);
    }
}

int WSDDTransport::RemoveHandler(bool bRequestFlow, 
                                 AXIS_PROTOCOL_TYPE protocol,
                                 WSDDHandler* pHandler)
{
    map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>* pTempHandlers = 
        bRequestFlow ? m_RequestHandlers : m_ResponseHandlers;
    WSDDHandlerList* pList = &(*(pTempHandlers->find(protocol))).second;
    if (pList)
    {
        for (WSDDHandlerList::iterator itr = pList->begin();
             itr != pList->end(); itr++)
        {
            if (strcmp((*itr)->GetLibName(), pHandler->GetLibName()) == 0)
            {
                pList->remove(*itr);
                delete (*itr);
                delete pHandler;
                return AXIS_SUCCESS;
            }
        }
    }
    return AXIS_NO_SUCH_HANDLER;    
}

int WSDDTransport::UpdateWSDD(FILE* wsddfile, int tabcount)
{
    WSDDHandlerList::iterator iter2;
    const char* trtype = 0;
    for (int type = APTHTTP; type < APTOTHER; type++)
    {
        if((m_RequestHandlers && 
            (m_RequestHandlers->find((AXIS_PROTOCOL_TYPE)type) != 
            m_RequestHandlers->end())) ||
            (m_RequestHandlers && 
            (m_RequestHandlers->find((AXIS_PROTOCOL_TYPE)type) != 
            m_RequestHandlers->end())))
        {
            trtype = (APTHTTP == type) ? 
                "http" : ((APTSMTP == type) ? "smtp" : "unsupported");
            if (fputs("\t<transport name=\"", wsddfile) < 0) return AXIS_FAIL;
            if (fputs(trtype, wsddfile) < 0) return AXIS_FAIL;
            if (fputs("\" >\n", wsddfile) < 0) return AXIS_FAIL;
            /* Write request flow handler configuration */
            if(m_RequestHandlers && 
                (m_RequestHandlers->find((AXIS_PROTOCOL_TYPE)type) != 
                m_RequestHandlers->end()))
            {
                WSDDHandlerList &list = 
                    (*m_RequestHandlers)[(AXIS_PROTOCOL_TYPE)type];
                if (fputs("\t\t<requestFlow>\n", wsddfile) < 0) 
                    return AXIS_FAIL;
                for(iter2 = list.begin(); iter2 != list.end(); iter2++)
                {
                    if (AXIS_SUCCESS != 
                        (*iter2)->UpdateWSDD(wsddfile, tabcount)) 
                        return AXIS_FAIL;
                }            
                if (fputs("\t\t</requestFlow>\n", wsddfile) < 0) 
                    return AXIS_FAIL;
            }
            /* Write response flow handler configuration */
            if(m_ResponseHandlers &&
                (m_ResponseHandlers->find((AXIS_PROTOCOL_TYPE)type) != 
                m_ResponseHandlers->end()))
            {
                WSDDHandlerList &list = 
                    (*m_ResponseHandlers)[(AXIS_PROTOCOL_TYPE)type];
                if (fputs("\t\t<responseFlow>\n", wsddfile) < 0) 
                    return AXIS_FAIL;
                for(iter2 = list.begin(); iter2 != list.end(); iter2++)
                {
                    if (AXIS_SUCCESS != 
                        (*iter2)->UpdateWSDD(wsddfile, tabcount)) 
                        return AXIS_FAIL;
                }            
                if (fputs("\t\t</responseFlow>\n", wsddfile) < 0) 
                    return AXIS_FAIL;
            }
            if (fputs("\t</transport>\n", wsddfile) < 0) return AXIS_FAIL;
        }

    }
    return AXIS_SUCCESS;
}

