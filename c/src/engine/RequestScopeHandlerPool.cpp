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


#include "RequestScopeHandlerPool.h"
#include "HandlerLoader.h"


extern HandlerLoader* g_pHandlerLoader;

RequestScopeHandlerPool::RequestScopeHandlerPool ()
{

}

RequestScopeHandlerPool::~RequestScopeHandlerPool ()
{
    for (map < int, list <BasicHandler*> >::iterator it =
        m_Handlers.begin (); it != m_Handlers.end (); it++)
    {
        for (list <BasicHandler*>::iterator itr = (*it).second.begin ();
            itr != (*it).second.end (); itr++)
        {
            g_pHandlerLoader->deleteHandler (*itr, (*it).first);
        }
        (*it).second.clear ();
    }
    m_Handlers.clear ();
}

int RequestScopeHandlerPool::getInstance (BasicHandler** pHandler, int nLibId)
{
    lock ();
    int Status;
    if (m_Handlers.find (nLibId) != m_Handlers.end ())
    {
        if (m_Handlers[nLibId].empty ())
        {
            Status = g_pHandlerLoader->createHandler (pHandler, nLibId);
            if (AXIS_SUCCESS == Status)
            {
                /* This just creates the entry in m_Handlers so that next 
	         * time we know that the DLL is loaded
		 */ 
                m_Handlers[nLibId].clear ();
            }
            unlock ();
            return Status;
        }
        else
        {
            *pHandler = m_Handlers[nLibId].front ();
            m_Handlers[nLibId].pop_front ();
            unlock ();
            return AXIS_SUCCESS;
        }
    }
    else // Not even the handler DLL loaded
    {
        Status = g_pHandlerLoader->createHandler (pHandler, nLibId);
        if (AXIS_SUCCESS == Status)
        {
            /* This just creates the entry in m_Handlers so that next time we 
	     * know that the DLL is loaded
	     */ 
            m_Handlers[nLibId].clear ();
        }
        unlock ();
        return Status;
    }
}

int RequestScopeHandlerPool::putInstance (BasicHandler* pHandler, int nLibId)
{
    lock ();
    m_Handlers[nLibId].push_back (pHandler);
    unlock ();
    return AXIS_SUCCESS;
}
