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

int ClientAxisEngine::process (Ax_soapstream* pSoap)
{
    int Status;
    const WSDDService* pService = NULL;

    if (!pSoap)
    {
        AXISTRACE1 ("Ax_soapstream is null", CRITICAL);
        return AXIS_FAIL;
    }
    m_pSoap = pSoap;

    string sSessionId = m_pSoap->sessionid;

    if (!(m_pSoap->transport.pSendFunct && m_pSoap->transport.pGetFunct &&
        m_pSoap->transport.pSetTrtFunct && m_pSoap->transport.pGetTrtFunct))
    {
        AXISTRACE1 ("transport is not set properly", CRITICAL);
        return AXIS_FAIL;
    }

    do
    {
        // const char* cService = get_header(soap, SOAPACTIONHEADER);

        const char* pchService = get_service_name (pSoap->so.http->uri_path);
        /* get service description object from the WSDD Deployment object */
        pService = g_pWSDDDeployment->getService (pchService);

        //Get Global and Transport Handlers
        if (AXIS_SUCCESS !=
            (Status = initializeHandlers (sSessionId, pSoap->trtype)))
        {
            break;          //do .. while(0)
        }
        //Get Service specific Handlers from the pool if configured any
        if (pService != NULL)
        {
            if (AXIS_SUCCESS != (Status = 
                g_pHandlerPool-> getRequestFlowHandlerChain (&m_pSReqFChain, 
                sSessionId, pService)))
            {
                break;    //do .. while(0)
            }
            if (AXIS_SUCCESS !=
                (Status =
                g_pHandlerPool->
                getResponseFlowHandlerChain (&m_pSResFChain, sSessionId,
                                                  pService)))
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
                // m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
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
                // m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
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
                // m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
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

    // AXISTRACE1("end axisengine process()");
    return Status;
}

void ClientAxisEngine::onFault (MessageData* pMsg)
{

}

char* ClientAxisEngine::get_service_name (const char* pch_uri_path)
{
    // return "InteropBaseDL";

    char* pachTmp = strrchr (pch_uri_path, '/');

    if (pachTmp != NULL)
    {
        int iTmp = strlen (pachTmp);

        if (iTmp <= 1)
        {
            return NULL;
        }
        else
        {
            pachTmp = pachTmp + 1;
        }
    }

    return pachTmp;
}
