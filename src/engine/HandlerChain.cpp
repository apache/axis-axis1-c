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


#include "HandlerChain.h"
#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX AxisTrace* g_pAT;

AXIS_CPP_NAMESPACE_START


HandlerChain::HandlerChain ()
{
}

HandlerChain::~HandlerChain ()
{
    /* Nothing to do because the list keeps only pointers to objects that 
     * belongs to the Handler pool;
     */
}

int HandlerChain::invoke (void* pMsg)
{
    m_itCurrHandler = m_HandlerList.begin ();
    while (m_itCurrHandler != m_HandlerList.end ())
    {
        BasicHandler* pHandler = (*m_itCurrHandler).m_pHandler;
        /*
         * if (AXIS_SUCCESS == pHandler->_functions->Invoke(pHandler->_object, 
	 *     pMsg))
         * {            
         *     m_itCurrHandler++;
         * }
         * else
         * {
         *     AXISTRACE1("Handler invoke not successful", WARN);            
         *     OnFault(pMsg);
         *     return AXIS_FAIL;
         * }
         */
        
	//----------change by roshan on 12Feb2004-------------
        if (0 != pHandler->_functions)
        {
                /* This is a C Handler */
        }
        else if (0 != pHandler->_object)
        {
            if (AXIS_SUCCESS ==
                ((Handler *) (pHandler->_object))->invoke (pMsg))
            {
                m_itCurrHandler++;
            }
            else
            {
                AXISTRACE1 ("Handler invoke not successful", WARN);
                onFault (pMsg);
                return AXIS_FAIL;
            }
        }
    }

    return AXIS_SUCCESS;
}

void HandlerChain::onFault (void* pMsg)
{
    while (m_itCurrHandler != m_HandlerList.begin ())
    {
        BasicHandler* pHandler = (*m_itCurrHandler).m_pHandler;
        pHandler->_functions->onFault (pHandler->_object, pMsg);
        m_itCurrHandler--;
    }
}

int HandlerChain::addHandler (BasicHandler* pHandler, int nScope, int nLibId)
{
    ChainItem item;
    item.m_pHandler = pHandler;
    item.m_nScope = nScope;
    item.m_nLibId = nLibId;
    m_HandlerList.push_back (item);

    return AXIS_SUCCESS;
}

int HandlerChain::init ()
{
    m_HandlerList.clear ();
    return AXIS_SUCCESS;
}

int HandlerChain::fini ()
{
    m_HandlerList.clear ();
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
