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
 */

#include "ClientAxisEngine.h"
#include "../../wsdd/WSDDDeployment.h"
#include "../HandlerPool.h"
#include <axis/server/AxisException.h>
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

extern WSDDDeployment* g_pWSDDDeployment;
extern HandlerPool* g_pHandlerPool;


ClientAxisEngine::ClientAxisEngine ()
{

}

ClientAxisEngine::~ClientAxisEngine ()
{

}

MessageData* ClientAxisEngine::getMessageData ()
{
    return m_pMsgData;
}

int ClientAxisEngine::process (SOAPTransport* pSoap)
{
    int Status = AXIS_FAIL;
    const WSDDService* pService = NULL;

    AXISC_TRY
    if (!pSoap)
    {
        AXISTRACE1 ("Transport is null", CRITICAL);
        return AXIS_FAIL;
    }
    m_pSoap = pSoap;

    string sSessionId = m_pSoap->getSessionId();

    do
    {
        const char* pchService = pSoap->getServiceName();
        /* get service description object from the WSDD Deployment object */
        pService = g_pWSDDDeployment->getService (pchService);

        //Get Global and Transport Handlers
        
        Status = initializeHandlers (sSessionId, pSoap->getProtocol());
        if (AXIS_SUCCESS != Status)
        {
            THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLER_INIT_FAILED);
            break;          //do .. while(0)
        }
        //Get Service specific Handlers from the pool if configured any
        if (pService != NULL)
        {
            Status = g_pHandlerPool-> getRequestFlowHandlerChain (&m_pSReqFChain, 
                sSessionId, pService);
            if (AXIS_SUCCESS != Status)
            {
                break;    //do .. while(0)
            }
            Status = g_pHandlerPool->
                getResponseFlowHandlerChain (&m_pSResFChain, sSessionId,
                pService);
            if (AXIS_SUCCESS != Status)
            {
                break;    //do .. while(0)
            }
        }

        // Invoke all handlers and then the remote webservice
        Status = invoke (m_pMsgData); /* we generate response in the same way 
                                       * even if this has failed
				       */ 
    }
    while (0);

    /* // Pool back the Service specific handlers
     * if (m_pSReqFChain) g_pHandlerPool->PoolHandlerChain(m_pSReqFChain, 
     *     sSessionId);
     * if (m_pSResFChain) g_pHandlerPool->PoolHandlerChain(m_pSResFChain, 
     *     sSessionId);
     * // Pool back the Global and Transport handlers
     * UnInitializeHandlers(sSessionId, soap->trtype);
     */

     AXISC_CATCH(exception& e)
#ifdef __ENABLE_AXIS_EXCEPTION__
        AxisException* objException = (AxisException*) &e;
        char* pcTempStr = (char*) objException->what();
        AXISTRACE2("Error:", pcTempStr, CRITICAL);
        return objException->getExceptionCode();
#endif

         
     AXISC_CATCH(...)
#ifdef __ENABLE_AXIS_EXCEPTION__
         return SERVER_UNKNOWN_ERROR;
#endif
     AXISC_ENDCATCH 
    return Status;
}

int ClientAxisEngine::invoke (MessageData* pMsg)
{
    enum AE_LEVEL
    { AE_START = 1, AE_SERH, AE_GLH, AE_TRH, AE_SERV };
    int Status = AXIS_FAIL;
    int level = AE_START;

    do
    {
        // Invoke client side service specific request handlers
        if (m_pSReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pSReqFChain->invoke (pMsg)))
            {
                // m_pSZ->setSoapFault(SoapFault::getSoapFault(CLIENT_ENGINE_CLIENTHANDLERFAILED));
                break;    //do .. while (0)
            }
        }
        // AXISTRACE1("AFTER invoke service specific request handlers");
        level++; //AE_SERH              

        // Invoke global request handlers
        if (m_pGReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pGReqFChain->invoke (pMsg)))
            {
                // m_pSZ->setSoapFault(SoapFault::getSoapFault(CLIENT_ENGINE_CLIENTHANDLERFAILED));
                break;    //do .. while (0)
            }
        }
        // AXISTRACE1("AFTER invoke global request handlers");
        level++; //AE_GLH       

        // Invoke transport request handlers
        if (m_pTReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pTReqFChain->invoke (pMsg)))
            {
                // m_pSZ->setSoapFault(SoapFault::getSoapFault(CLIENT_ENGINE_CLIENTHANDLERFAILED));
                break;    //do .. while (0)
            }
        }
        // AXISTRACE1("AFTER invoke transport request handlers");
        level++; // AE_TRH

        if (AXIS_SUCCESS != (Status = m_pSZ->setOutputStream (m_pSoap)))
            break;
        m_pSZ->markEndOfStream ();

        level++; // AE_SERV

        pMsg->setPastPivotState (true);

        if (AXIS_SUCCESS != (Status = m_pDZ->setInputStream (m_pSoap)))
            break;

        int nSoapVersion = m_pDZ->getVersion ();
        if (nSoapVersion == VERSION_LAST)     /* version not supported */
        {
            Status = AXIS_FAIL;
            // return AXIS_FAIL;
        }

        m_pDZ->getHeader ();

    }
    while (0);

    /*
     *  The case clauses in this switch statement have no breaks.
     *  Hence, if Everything up to web service invocation was successful
     *  then all response handlers are invoked. If there was a failure
     *  at some point the response handlers from that point onwards
     *  are invoked.
     */
    switch (level)
    {
        case AE_SERV: // everything success
            Status = AXIS_SUCCESS;
            // no break;
        case AE_TRH: /* after invoking the transport handlers 
                      * (at actual service invokation) it has failed
		      */ 
            if (m_pTResFChain)
            {
                m_pTResFChain->invoke (pMsg);
            }
            // no break;
        case AE_GLH: // transport handlers have failed
            // invoke global response handlers
            if (m_pGResFChain)
            {
                m_pGResFChain->invoke (pMsg);
            }
            //no break;
        case AE_SERH: // global handlers have failed
            // invoke web service specific response handlers
            if (m_pSResFChain)
            {
                m_pSResFChain->invoke (pMsg);
            }
            // no break;
        case AE_START:; // service specific handlers have failed
    };

    return Status;
}

void ClientAxisEngine::onFault (MessageData* pMsg)
{

}
