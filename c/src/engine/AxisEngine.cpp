/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include <axis/engine/AxisEngine.h>
#include <stdio.h>

#include <axis/engine/HandlerPool.h>
#include <axis/engine/DeserializerPool.h>
#include <axis/engine/SerializerPool.h>

extern DeserializerPool* g_pDeserializerPool;
extern SerializerPool* g_pSerializerPool;
extern HandlerPool* g_pHandlerPool;
//extern WSDDDeployment* g_pWSDDDeployment;

AxisEngine::AxisEngine()
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

AxisEngine::~AxisEngine()
{
	if (m_pDZ) g_pDeserializerPool->PutInstance(m_pDZ);
	if (m_pSZ) g_pSerializerPool->PutInstance(m_pSZ);
	if (m_pMsgData) delete m_pMsgData;
}

int AxisEngine::Initialize()
{
	int Status;
	m_pMsgData = new MessageData();
	if (!m_pMsgData) return AXIS_FAIL;
	//Create and initialize Serializer and Deserializer objects
	if (AXIS_SUCCESS != (Status = g_pSerializerPool->GetInstance(&m_pSZ))) return Status;
	if (AXIS_SUCCESS != (Status = g_pDeserializerPool->GetInstance(&m_pDZ))) return Status;
	m_pMsgData->SetSerializer(m_pSZ);
	m_pMsgData->SetDeSerializer(m_pDZ);   
    
	return AXIS_SUCCESS;
}

void AxisEngine::UnInitialize()
{
	if (m_pMsgData) 
	{
		delete m_pMsgData;
		m_pMsgData = NULL;
	}
	//nothing to do with m_pWSDD because its destructor deletes its objects
	//nothing to do with m_pHandlerPool because its destructor deletes its objects
}

int AxisEngine::InitializeHandlers(string &sSessionId, AXIS_PROTOCOL_TYPE protocol)
{
	int Status = AXIS_SUCCESS;  
	//Get Global Handlers from the pool if configured any
	if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetGlobalRequestFlowHandlerChain(&m_pGReqFChain, sSessionId)))
		return Status;
	if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetGlobalResponseFlowHandlerChain(&m_pGResFChain, sSessionId)))
		return Status;

	//Get Transport Handlers from the pool if configured any
	if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetTransportRequestFlowHandlerChain(&m_pTReqFChain, sSessionId, protocol)))
		return Status;
	if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetTransportResponseFlowHandlerChain(&m_pTResFChain, sSessionId, protocol)))
		return Status;
	return Status;
}
