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

#ifdef WIN32
#pragma warning (disable : 4503)
#endif

#include "SessionScopeHandlerPool.h"
#include "HandlerLoader.h"


extern HandlerLoader* g_pHandlerLoader;

SessionScopeHandlerPool::SessionScopeHandlerPool ()
{

}

SessionScopeHandlerPool::~SessionScopeHandlerPool ()
{
    for (map <int, SessionHandlers*>::iterator it = m_Handlers.begin ();
        it != m_Handlers.end (); it++)
    {
        SessionHandlers *pSH = (*it).second;
        for (SessionHandlers::iterator itr = pSH->begin ();
            itr != pSH->end (); itr++)
        {
            for (list <BasicHandler*>::iterator ite =
                (*itr).second.begin (); ite != (*itr).second.end ();
                ite++)
            {
                g_pHandlerLoader->DeleteHandler (*ite, (*it).first);
            }
            (*itr).second.clear ();
        }
        delete pSH;
    }
    m_Handlers.clear ();
}

int SessionScopeHandlerPool::GetInstance (string &sSessionId,
    BasicHandler** pHandler, int nLibId)
{
    lock ();
    int Status;
    if (m_Handlers.find (nLibId) != m_Handlers.end ())
    {
        SessionHandlers *pSesHandlers = m_Handlers[nLibId];
        if (pSesHandlers->find (sSessionId) != pSesHandlers->end ())
        {
            list <BasicHandler*>&HandlerList = ((*pSesHandlers)[sSessionId]);
            if (HandlerList.empty ())
            {
                // check in the store for reuse
                if ((*pSesHandlers)[SESSIONLESSHANDLERS].empty ())
                {
                    unlock ();
                    return g_pHandlerLoader->CreateHandler (pHandler, nLibId);
                }
                else
                {
                    *pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front ();
                    (*pSesHandlers)[SESSIONLESSHANDLERS].pop_front ();
                    unlock ();
                    return AXIS_SUCCESS;
                }
            }
            else
            {
                *pHandler = HandlerList.front ();
                HandlerList.pop_front ();
                unlock ();
                return AXIS_SUCCESS;
            }
            unlock ();
            return g_pHandlerLoader->CreateHandler (pHandler, nLibId);
        }
        else // No handler list for this session id
        {
            // Check in the store for reuse
            if ((*pSesHandlers)[SESSIONLESSHANDLERS].empty ())
            {
                unlock ();
                return g_pHandlerLoader->CreateHandler (pHandler, nLibId);
            }
            else
            {
                *pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front ();
                (*pSesHandlers)[SESSIONLESSHANDLERS].pop_front ();
                unlock ();
                return AXIS_SUCCESS;
            }
        }
    }
    else // Not even the handler DLL loaded
    {
        Status = g_pHandlerLoader->CreateHandler (pHandler, nLibId);
        if (AXIS_SUCCESS == Status)
        {
            /* This just creates the entry in m_Handlers so that next time we 
             * know that the DLL is loaded
             */ 
            SessionHandlers* pNewSH = new SessionHandlers;
            pNewSH->clear ();
            m_Handlers[nLibId] = pNewSH;
        }
        unlock ();
        return Status;
    }
}

int SessionScopeHandlerPool::PutInstance (string &sSessionId,
    BasicHandler* pHandler, int nLibId)
{
    lock ();
    SessionHandlers* pSesHandlers;
    if (m_Handlers.find (nLibId) != m_Handlers.end ())
    {
        pSesHandlers = m_Handlers[nLibId];
    }
    else // This is unexpected situation. anyway do it
    {
        pSesHandlers = new SessionHandlers;
        pSesHandlers->clear ();
        m_Handlers[nLibId] = pSesHandlers;
    }
    list <BasicHandler*>&HandlerList = ((*pSesHandlers)[sSessionId]);
    HandlerList.push_back (pHandler);
    unlock ();
    return AXIS_SUCCESS;
}

void SessionScopeHandlerPool::EndSession (string &sSessionId)
{
    /* Traverse all the lists and remove corresponding handlers if any and put 
     * to SESSIONLESSHANDLERS        
     */
}
