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

#include "RequestScopeHandlerPool.h"
#include "HandlerLoader.h"

#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX HandlerLoader* g_pHandlerLoader;

AXIS_CPP_NAMESPACE_START

RequestScopeHandlerPool::
RequestScopeHandlerPool ()
{

}

RequestScopeHandlerPool::
~RequestScopeHandlerPool ()
{
    logEntryEngine("RequestScopeHandlerPool::~RequestScopeHandlerPool")

    for (map < int, list <BasicHandler*> >::iterator it = m_Handlers.begin (); it != m_Handlers.end (); it++)
    {
        for (list <BasicHandler*>::iterator itr = (*it).second.begin (); itr != (*it).second.end (); itr++)
        {
            g_pHandlerLoader->deleteHandler (*itr, (*it).first);
        }
        
        (*it).second.clear ();
    }
    
    m_Handlers.clear ();
    
    logExit()
}

int RequestScopeHandlerPool::
getInstance (BasicHandler** pHandler, int nLibId)
{
    logEntryEngine("RequestScopeHandlerPool::getInstance")

    Lock l(this);
    
    int Status = AXIS_SUCCESS;
    
    if (m_Handlers.find (nLibId) != m_Handlers.end ())
    {
        if (m_Handlers[nLibId].empty ())
        {
            Status = g_pHandlerLoader->createHandler (pHandler, nLibId);
            if (AXIS_SUCCESS == Status)
                m_Handlers[nLibId].clear ();
        }
        else
        {
            *pHandler = m_Handlers[nLibId].front ();
            m_Handlers[nLibId].pop_front ();
        }
    }
    else // Not even the handler DLL loaded
    {
        Status = g_pHandlerLoader->createHandler (pHandler, nLibId);
        if (AXIS_SUCCESS == Status)
            m_Handlers[nLibId].clear ();
    }
    
    logExitWithReturnCode(Status)

    return Status;
}

int RequestScopeHandlerPool::
putInstance (BasicHandler* pHandler, int nLibId, bool bWebService)
{
    logEntryEngine("RequestScopeHandlerPool::putInstance")

    Lock l(this);

    if (0 != pHandler->_functions)
    {
        /* C Handler */
    }
    else if (0 != pHandler->_object)
    {
         if (!bWebService)
             ((HandlerBase *)(pHandler->_object))->fini();
    }

    m_Handlers[nLibId].push_back (pHandler);

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
