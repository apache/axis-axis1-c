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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include "AxisEngine.h"
#include <stdio.h>

#include "HandlerPool.h"
#include "DeserializerPool.h"
#include "SerializerPool.h"
#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX AxisTrace* g_pAT;
extern AXIS_CPP_NAMESPACE_PREFIX DeserializerPool* g_pDeserializerPool;
extern AXIS_CPP_NAMESPACE_PREFIX SerializerPool* g_pSerializerPool;
extern AXIS_CPP_NAMESPACE_PREFIX HandlerPool* g_pHandlerPool;
// extern WSDDDeployment* g_pWSDDDeployment;

AXIS_CPP_NAMESPACE_START

AxisEngine::AxisEngine ()
{
    m_pSZ = NULL;
    m_pDZ = NULL;
    m_pGReqFChain = NULL;
    m_pGResFChain = NULL;
    m_pTReqFChain = NULL;
    m_pTResFChain = NULL;
    m_pSReqFChain = NULL;
    m_pSResFChain = NULL;
    m_pMsgData = NULL;

}

AxisEngine::~AxisEngine ()
{
    if (m_pDZ)
        g_pDeserializerPool->putInstance (m_pDZ);
    if (m_pSZ)
        g_pSerializerPool->putInstance (m_pSZ);
    if (m_pMsgData)
        delete m_pMsgData;
}

int AxisEngine::initialize ()
{
    int Status;
    m_pMsgData = new MessageData ();
    if (!m_pMsgData)
        return AXIS_FAIL;
    // Create and initialize Serializer and Deserializer objects
    if (AXIS_SUCCESS != (Status = g_pSerializerPool->getInstance ((IWrapperSoapSerializer**)&m_pSZ)))
        return Status;
    if (AXIS_SUCCESS != (Status = g_pDeserializerPool->getInstance ((IWrapperSoapDeSerializer**)&m_pDZ)))
        return Status;
    m_pMsgData->setSerializer (m_pSZ);
    m_pMsgData->setDeSerializer (m_pDZ);

    return AXIS_SUCCESS;
}

void AxisEngine::unInitialize ()
{
    if (m_pMsgData)
    {
        delete m_pMsgData;
        m_pMsgData = NULL;
    }
    /* nothing to do with m_pWSDD because its destructor deletes its objects
     * nothing to do with m_pHandlerPool because its destructor deletes its 
     * objects
     */ 
}

int AxisEngine::initializeHandlers (string & sSessionId, 
    AXIS_PROTOCOL_TYPE protocol)
{
    int Status = AXIS_SUCCESS;
    // Get Global Handlers from the pool if configured any
    if (AXIS_SUCCESS !=
        (Status =
        g_pHandlerPool->getGlobalRequestFlowHandlerChain (&m_pGReqFChain,
        sSessionId)))
        return Status;
    if (AXIS_SUCCESS !=
        (Status =
        g_pHandlerPool->getGlobalResponseFlowHandlerChain (&m_pGResFChain,
        sSessionId)))
        return Status;

    // Get Transport Handlers from the pool if configured any
    if (AXIS_SUCCESS !=
        (Status =
        g_pHandlerPool->getTransportRequestFlowHandlerChain (&m_pTReqFChain,
        sSessionId, protocol)))
        return Status;
    if (AXIS_SUCCESS !=
        (Status =
        g_pHandlerPool->getTransportResponseFlowHandlerChain (&m_pTResFChain,
        sSessionId, protocol)))
        return Status;
    return Status;
}

AXIS_CPP_NAMESPACE_END
