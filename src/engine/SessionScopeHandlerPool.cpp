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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include "SessionScopeHandlerPool.h"
#include "HandlerLoader.h"

#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX HandlerLoader* g_pHandlerLoader;

AXIS_CPP_NAMESPACE_START

SessionScopeHandlerPool::
SessionScopeHandlerPool ()
{
	logEntryEngine("SessionScopeHandlerPool::SessionScopeHandlerPool")

    logExit()
}

SessionScopeHandlerPool::
~SessionScopeHandlerPool ()
{
	logEntryEngine("SessionScopeHandlerPool::~SessionScopeHandlerPool")

    for (map <int, SessionHandlers*>::iterator it = m_Handlers.begin (); it != m_Handlers.end (); it++)
    {
        SessionHandlers *pSH = (*it).second;
        for (SessionHandlers::iterator itr = pSH->begin ();
            itr != pSH->end (); itr++)
        {
            for (list <BasicHandler*>::iterator ite =
                (*itr).second.begin (); ite != (*itr).second.end ();
                ite++)
            {
                g_pHandlerLoader->deleteHandler (*ite, (*it).first);
            }
            (*itr).second.clear ();
        }
        delete pSH;
    }
    m_Handlers.clear ();
    
    logExit()
}

int SessionScopeHandlerPool::
getInstance (string &sSessionId, BasicHandler** pHandler, int nLibId)
{
	logEntryEngine("SessionScopeHandlerPool::getInstance")

    //lock ();
	Lock l(this);

    int Status = AXIS_SUCCESS;
    
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
					l.unlock ();
					Status = g_pHandlerLoader->createHandler (pHandler, nLibId);
                }
                else
                {
                    *pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front ();
                    (*pSesHandlers)[SESSIONLESSHANDLERS].pop_front ();
                }
            }
            else
            {
                *pHandler = HandlerList.front ();
                HandlerList.pop_front ();
            }
        }
        else // No handler list for this session id
        {
            // Check in the store for reuse
            if ((*pSesHandlers)[SESSIONLESSHANDLERS].empty ())
            {
				l.unlock ();
				Status = g_pHandlerLoader->createHandler (pHandler, nLibId);
            }
            else
            {
                *pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front ();
                (*pSesHandlers)[SESSIONLESSHANDLERS].pop_front ();
            }
        }
    }
    else // Not even the handler DLL loaded
    {
        Status = g_pHandlerLoader->createHandler (pHandler, nLibId);
        if (AXIS_SUCCESS == Status)
        {
            SessionHandlers* pNewSH = new SessionHandlers;
            pNewSH->clear ();
            m_Handlers[nLibId] = pNewSH;
        }
    }
    
	logExitWithReturnCode(Status)

    return Status;
}

int SessionScopeHandlerPool::
putInstance (string &sSessionId, BasicHandler* pHandler, int nLibId)
{
	logEntryEngine("SessionScopeHandlerPool::putInstance")

	Lock l(this);
    SessionHandlers* pSesHandlers;
    if (m_Handlers.find (nLibId) != m_Handlers.end ())
        pSesHandlers = m_Handlers[nLibId];
    else // This is unexpected situation. anyway do it
    {
        pSesHandlers = new SessionHandlers;
        pSesHandlers->clear ();
        m_Handlers[nLibId] = pSesHandlers;
    }
    list <BasicHandler*>&HandlerList = ((*pSesHandlers)[sSessionId]);
    HandlerList.push_back (pHandler);

	logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

void SessionScopeHandlerPool::
endSession (string &sSessionId)
{
	logEntryEngine("SessionScopeHandlerPool::endSession")

    /* Traverse all the lists and remove corresponding handlers if any and put 
     * to SESSIONLESSHANDLERS        
     */
	
    logExit()
}

AXIS_CPP_NAMESPACE_END
