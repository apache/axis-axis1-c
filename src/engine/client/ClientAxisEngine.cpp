/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

/*
 * Revision 1.1  2004/08/26 roshan
 * Added the method "releaseHandlers(string sSessionId)" in order to release the
 *  Handlers once they are used.
 */


#include "ClientAxisEngine.h"
#include "../../wsdd/WSDDDeployment.h"
#include "../HandlerPool.h"
#include <axis/AxisException.hpp>
#include "../../common/AxisTrace.h"
#include "../../common/AxisGenException.h"

extern AXIS_CPP_NAMESPACE_PREFIX WSDDDeployment* g_pWSDDDeployment;
extern AXIS_CPP_NAMESPACE_PREFIX HandlerPool* g_pHandlerPool;

AXIS_CPP_NAMESPACE_START

ClientAxisEngine::
ClientAxisEngine ()
{

}

ClientAxisEngine::
~ClientAxisEngine ()
{

}

MessageData* ClientAxisEngine::
getMessageData ()
{
    return m_pMsgData;
}

int ClientAxisEngine::
process (SOAPTransport* pSoap)
{
    return process(pSoap, false);
}

int ClientAxisEngine::
process (SOAPTransport* pSoap, bool noResponse)
{
    int Status = AXIS_FAIL;
    const WSDDService* pService = NULL;

    try
    {
        if (!pSoap)
            return AXIS_FAIL;

        m_pSoap = pSoap;
        string sSessionId = m_pSoap->getSessionId();
    
        do
        {
            // Get the service name that was specified in the second parameter of the call
            // to setTransportProperty( SOAPACTION_HEADER , "") matches a service name in
            // the 'service' part of the WSDD file then call that service now.
            const char* pchService = pSoap->getServiceName();
            
            // Check that there is a valid service name.
            if( pchService != NULL)
            {
                // The convention for the service name appears to be service#port
                if( strchr( pchService, '#') == NULL)
                {
                    int     iStringLength = strlen( pchService);
                    char *  pszService = new char[iStringLength];

                    memset( pszService, 0, iStringLength);
                    // If there is no # seperator, then strip off the outer quotes. if they exist !
                    if(strchr(pchService, '"') == NULL)
                        memcpy( pszService, pchService, iStringLength);
                    else
                        memcpy( pszService, pchService + 1, iStringLength - 2);

                    pService = g_pWSDDDeployment->getService( pszService);

                    delete [] pszService;                
                  }
                else
                {
                    char * pchTempService = new char [strlen(pchService)+1];
                    
                    // Skip the starting double quote
                    strcpy(pchTempService, pchService+1);
            
                    // The String returned as the service name has the format "Calculator#add".
                    // So null terminate string at #.
                    *(strchr(pchTempService, '#')) = '\0';

                    // get service description object from the WSDD Deployment object
                    pService = g_pWSDDDeployment->getService (pchTempService);
                    
                    delete [] pchTempService;
                }
            }
            
            //Get Global and Transport Handlers    
            Status = initializeHandlers (sSessionId, pSoap->getProtocol());
            if (AXIS_SUCCESS != Status)
                throw AxisEngineException(SERVER_ENGINE_HANDLER_INIT_FAILED);
            
            //Get Service specific Handlers from the pool if configured any
            if (pService != NULL)
            {
                Status = g_pHandlerPool->getRequestFlowHandlerChain(&m_pSReqFChain, sSessionId, pService);
                if (AXIS_SUCCESS != Status)
                    break;  

                Status = g_pHandlerPool->getResponseFlowHandlerChain(&m_pSResFChain, sSessionId, pService);
                if (AXIS_SUCCESS != Status)
                    break;   
            }
    
            // Invoke all handlers and then the remote webservice
            // we generate response in the same way even if this has failed 
            Status = invoke (m_pMsgData, noResponse); 
        }
        while (0);
    
        //release the handlers
        releaseHandlers(sSessionId);         
    }
    catch(AxisException& e)
    {
        /* Throw a AxisGenException here instead of rethrowing the original exception because
         * the original exception may be an transport exception which will go out of scope when
         * the transport library is unloaded. 
         */
        throw AxisGenException(e);
    }
    return Status;
}

void ClientAxisEngine::
releaseHandlers(string sSessionId)
{
    // Pool back the Service specific handlers
    if (m_pSReqFChain) 
        g_pHandlerPool->poolHandlerChain(m_pSReqFChain, sSessionId);
    if (m_pSResFChain) 
        g_pHandlerPool->poolHandlerChain(m_pSResFChain, sSessionId); 
}

int ClientAxisEngine::
invoke (MessageData* pMsg)
{
    return invoke(pMsg, false);
}

int ClientAxisEngine::
invoke (MessageData* pMsg, bool noResponse)
{
    enum AE_LEVEL { AE_START = 1, AE_SERH, AE_GLH, AE_TRH, AE_SERV };
    int Status = AXIS_FAIL;
    int level = AE_START;
    
    do
    {
        // Invoke client side service specific request handlers
        if (m_pSReqFChain)
            if (AXIS_SUCCESS != (Status = m_pSReqFChain->invoke (pMsg)))
                break;   
        
        // AXISTRACE1("AFTER invoke service specific request handlers");
        level++; //AE_SERH              

        // Invoke global request handlers
        if (m_pGReqFChain)
            if (AXIS_SUCCESS != (Status = m_pGReqFChain->invoke (pMsg)))
                break;  
        
        // AXISTRACE1("AFTER invoke global request handlers");
        level++; //AE_GLH       

        // Invoke transport request handlers
        if (m_pTReqFChain)
            if (AXIS_SUCCESS != (Status = m_pTReqFChain->invoke (pMsg)))
                break;   

        // AXISTRACE1("AFTER invoke transport request handlers");
        level++; // AE_TRH

        if (AXIS_SUCCESS != (Status = m_pSZ->setOutputStream (m_pSoap)))
            break;
        
        m_pSoap->openConnection();

        m_pSZ->markEndOfStream();

        level++; // AE_SERV

        pMsg->setPastPivotState (true);

        if (AXIS_SUCCESS != (Status = m_pDZ->setInputStream (m_pSoap)))
            break;

        // Get header and body only if we are expecting a response
        if (!noResponse || m_pSoap->isThereResponseData())
        {
            // version not supported set status to fail
            int nSoapVersion = m_pDZ->getVersion ();
            if (nSoapVersion == VERSION_LAST)     
                Status = AXIS_FAIL;

            m_pDZ->getHeader ();
            m_pDZ->getBody ();
            
            // If one-way messaging and there is response data, then it must be a fault. 
            if (noResponse)
            {
                // initiate fault processing. This will result in an exception being thrown.
                m_pDZ->initiateFault(NULL);
            }
        }
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
        case AE_SERV: 
            // everything success
            Status = AXIS_SUCCESS;
            
            // If no response expected, break out.
            if (noResponse)
                break;
            
        case AE_TRH: 
           // After invoking the transport handlers (at actual service invokation) it has failed
            if (m_pTResFChain)
                m_pTResFChain->invoke (pMsg);
                
        case AE_GLH: 
            // transport handlers have failed invoke global response handlers
            if (m_pGResFChain)
                m_pGResFChain->invoke (pMsg);
                
        case AE_SERH: // global handlers have failed
            // invoke web service specific response handlers
            if (m_pSResFChain)
                m_pSResFChain->invoke (pMsg);
                
        case AE_START:; 
           // service specific handlers have failed
    };

    return Status;
}

void ClientAxisEngine::
onFault (MessageData* pMsg)
{

}

AXIS_CPP_NAMESPACE_END
