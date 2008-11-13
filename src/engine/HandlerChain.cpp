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

#include "HandlerChain.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START


HandlerChain::
HandlerChain ()
{
}

HandlerChain::
~HandlerChain ()
{
    /* Nothing to do because the list keeps only pointers to objects that 
     * belongs to the Handler pool;
     */
}

int HandlerChain::
invoke (void* pMsg)
{
	logEntryEngine("HandlerChain::invoke")

    int Status=AXIS_SUCCESS;

    m_itCurrHandler = m_HandlerList.begin ();
    while (m_itCurrHandler != m_HandlerList.end ())
    {
        BasicHandler* pHandler = (*m_itCurrHandler).m_pHandler;

        if (0 != pHandler->_functions)
        {
                /* This is a C Handler */
        }
        else if (0 != pHandler->_object)
        {
            logDebugArg1("Calling invoke() method for handler %p", pHandler->_object)

        	Status = ((Handler *) (pHandler->_object))->invoke (pMsg);
            
            logDebugArg2("Returned from invoke() method for handler %p with status=%d", pHandler->_object, Status)

            if (AXIS_SUCCESS == Status)
                m_itCurrHandler++;
            else
            {
                onFault (pMsg);
                break;
            }
        }
    }

	logExitWithReturnCode(Status)

    return Status;
}

void HandlerChain::
onFault (void* pMsg)
{
	logEntryEngine("HandlerChain::onFault")

    while (m_itCurrHandler != m_HandlerList.begin ())
    {
        BasicHandler* pHandler = (*m_itCurrHandler).m_pHandler;
        
        logDebugArg1("Calling onFault() method for handler %p", pHandler->_object)

        pHandler->_functions->onFault (pHandler->_object, pMsg);
        
        logDebugArg1("Returned from onFault() method for handler %p", pHandler->_object)

        m_itCurrHandler--;
    }
	
	logExit()
}

int HandlerChain::
addHandler (BasicHandler* pHandler, int nScope, int nLibId)
{
	logEntryEngine("HandlerChain::addHandler")

    ChainItem item;
    item.m_pHandler = pHandler;
    item.m_nScope = nScope;
    item.m_nLibId = nLibId;
    m_HandlerList.push_back (item);

	logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int HandlerChain::
init ()
{
    m_HandlerList.clear ();
    return AXIS_SUCCESS;
}

int HandlerChain::
fini ()
{
    m_HandlerList.clear ();
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
