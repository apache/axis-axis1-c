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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <stdio.h>

#include "AxisEngine.h"
#include "HandlerPool.h"
#include "DeserializerPool.h"
#include "SerializerPool.h"

#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX DeserializerPool* g_pDeserializerPool;
extern AXIS_CPP_NAMESPACE_PREFIX SerializerPool* g_pSerializerPool;
extern AXIS_CPP_NAMESPACE_PREFIX HandlerPool* g_pHandlerPool;

AXIS_CPP_NAMESPACE_START

AxisEngine::AxisEngine ()
{
    logEntryEngine("AxisEngine::AxisEngine")

    m_pSZ = NULL;
    m_pDZ = NULL;
    m_pGReqFChain = NULL;
    m_pGResFChain = NULL;
    m_pTReqFChain = NULL;
    m_pTResFChain = NULL;
    m_pSReqFChain = NULL;
    m_pSResFChain = NULL;
    m_pMsgData = NULL;
    
    logExit()
}

AxisEngine::~AxisEngine ()
{
    logEntryEngine("AxisEngine::~AxisEngine")

    if (m_pDZ)
        g_pDeserializerPool->putInstance (m_pDZ);
    if (m_pSZ)
        g_pSerializerPool->putInstance (m_pSZ);
    if (m_pMsgData)
        delete m_pMsgData;
    
    logExit()    
}

int AxisEngine::initialize ()
{
    logEntryEngine("AxisEngine::initialize")

    int Status = AXIS_SUCCESS;
    
    m_pMsgData = new MessageData ();
    if (!m_pMsgData)
        Status = AXIS_FAIL;
    
    // Create and initialize Serializer and Deserializer objects
    if (AXIS_SUCCESS == Status)
        Status = g_pSerializerPool->getInstance ((IWrapperSoapSerializer**)&m_pSZ);
    
    if (AXIS_SUCCESS == Status)
        Status = g_pDeserializerPool->getInstance ((IWrapperSoapDeSerializer**)&m_pDZ);

    if (AXIS_SUCCESS == Status)
    {
        m_pMsgData->setSerializer (m_pSZ);
        m_pMsgData->setDeSerializer (m_pDZ);
    }

    logExitWithReturnCode(Status)

    return Status;
}

void AxisEngine::unInitialize ()
{
    logEntryEngine("AxisEngine::unInitialize")

    if (m_pMsgData)
    {
        delete m_pMsgData;
        m_pMsgData = NULL;
    }
    
    logExit()
}

int AxisEngine::initializeHandlers (string & sSessionId, AXIS_PROTOCOL_TYPE protocol)
{
    logEntryEngine("AxisEngine::initializeHandlers")

    int Status;
    
    // Get Global Handlers from the pool if configured any
    Status = g_pHandlerPool->getGlobalRequestFlowHandlerChain (&m_pGReqFChain, sSessionId);
    if (AXIS_SUCCESS == Status)
        Status = g_pHandlerPool->getGlobalResponseFlowHandlerChain (&m_pGResFChain, sSessionId);

    // Get Transport Handlers from the pool if configured any
    if (AXIS_SUCCESS == Status)
        Status = g_pHandlerPool->getTransportRequestFlowHandlerChain (&m_pTReqFChain, sSessionId, protocol);
    if (AXIS_SUCCESS == Status)
        Status = g_pHandlerPool->getTransportResponseFlowHandlerChain (&m_pTResFChain, sSessionId, protocol);
    
    logExitWithReturnCode(Status)

    return Status;
}

AXIS_CPP_NAMESPACE_END
