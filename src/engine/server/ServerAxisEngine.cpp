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

#include "../../soap/SoapBody.h"
#include "../../soap/SoapMethod.h"
#include "ServerAxisEngine.h"
#include <stdio.h>
#include <axis/server/AxisException.h>
#include "../../common/AxisUtils.h"
#include "../../wsdd/WSDDDeployment.h"
#include "../HandlerPool.h"
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

extern HandlerPool* g_pHandlerPool;
extern WSDDDeployment* g_pWSDDDeployment;


ServerAxisEngine::ServerAxisEngine ()
{
    m_pWebService = NULL;
}

ServerAxisEngine::~ServerAxisEngine ()
{

}

int ServerAxisEngine::Process (Ax_soapstream* stream)
{
    int Status = 0;
    /* AXIS_TRY */
    const WSDDService* pService = NULL;
    string sSessionId = stream->sessionid;
    int nSoapVersion;

    if (!(stream->transport.pSendFunct && stream->transport.pGetFunct &&
        stream->transport.pSetTrtFunct && stream->transport.pGetTrtFunct))
    {
        AXISTRACE1 ("transport is not set properly", CRITICAL);
        return AXIS_FAIL;
    }
    
    /*
     * After this point we should return AXIS_SUCCESS. Otherwise the transport 
     * layer may not send the response back (either soap fault or result).
     */
    do
    {
        /* populate MessageData with transport information */
        m_pMsgData->m_Protocol = stream->trtype;

        if (AXIS_SUCCESS != m_pDZ->SetInputStream (stream))
        {
            nSoapVersion = m_pDZ->GetVersion ();
            nSoapVersion = 
                (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
            m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion);
            AXISTRACE1 ("SF_SOAPCONTENTERROR", CRITICAL);
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_SOAPCONTENTERROR));
            break; // do .. while(0)
        }

        const char* cService = stream->transport.pGetTrtFunct (SERVICE_URI, 
            stream);
        if (!cService)
        {
            AXISTRACE1 ("SF_SOAPCONTENTERROR", CRITICAL);
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_SOAPCONTENTERROR));
            break; // do .. while(0)
        }
        AxisString service = (cService == NULL) ? "" : cService;

        if (service.empty ())
        {
            nSoapVersion = m_pMsgData->m_pDZ->GetVersion ();
            nSoapVersion =
                (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
            m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion);
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_SOAPACTIONEMPTY));
            break; // do .. while(0)
        }
        /* if there are quotes remove them. */
        if (service.find ('\"') != string::npos)
        {
            service = service.substr (1, service.length () - 2);
        }

        /* get service description object from the WSDD Deployment object */
        pService = g_pWSDDDeployment->GetService (service.c_str ());
        if (!pService)
        {
            nSoapVersion = m_pMsgData->m_pDZ->GetVersion ();
            nSoapVersion =
                (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
            m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion);
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_SERVICENOTFOUND));
            break; // do .. while(0)
        }

        m_pMsgData->SetService (pService);

        m_CurrentProviderType = pService->GetProvider ();
        m_pSZ->SetCurrentProviderType (m_CurrentProviderType);
        m_pDZ->SetCurrentProviderType (m_CurrentProviderType);
        switch (m_CurrentProviderType)
        {
            case C_RPC_PROVIDER:
            case CPP_RPC_PROVIDER:
                m_pSZ->SetStyle (RPC_ENCODED);
                m_pDZ->SetStyle (RPC_ENCODED);
                break;
            case C_DOC_PROVIDER:
            case CPP_DOC_PROVIDER:
                m_pSZ->SetStyle (DOC_LITERAL);
                m_pDZ->SetStyle (DOC_LITERAL);
                break;
            case COM_PROVIDER:
                // TODO: ??
                break;
            default:;
                // TODO: ??
        }

        /* Check for stream version in the request and decide whether we support
	 * it or not. If we do not support send a soapfault with version 
	 * mismatch. 
	 */
        nSoapVersion = m_pDZ->GetVersion ();
        if (m_pDZ->GetStatus () != AXIS_SUCCESS)
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault(SF_MESSAGEINCOMPLETE));
            break; // do .. while(0)
        }

        if (nSoapVersion == VERSION_LAST)     /* version not supported */
        {
            m_pSZ->setSoapVersion (SOAP_VER_1_2);
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_VERSION_MISMATCH));
            break; // do .. while(0)         
        }

        /* Set Soap version in the Serializer and the envelope */
        if (AXIS_SUCCESS != m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion))
        {
            AXISTRACE1 ("SF_SOAPCONTENTERROR", CRITICAL);
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_SOAPCONTENTERROR));
            break; // do .. while(0)
        }

        /* Get the operation name from transport information Ex: from 
	 * SOAPAction header 
	 */
        AxisString sOperation = stream->transport.pGetTrtFunct (OPERATION_NAME, 
            stream);
        if (sOperation.empty ())
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_NOSOAPMETHOD));
            break; // do .. while(0)
        }
        /* remove any quotes in the operation name */
        if (sOperation.rfind ('\"') != string::npos)
        {
            sOperation = sOperation.substr (0, sOperation.length () - 1);
        }

        m_pMsgData->SetOperationName (sOperation.c_str ());

        if (pService->IsAllowedMethod (sOperation.c_str ()))
        {
            /* load actual web service handler */
            if (AXIS_SUCCESS != g_pHandlerPool->GetWebService (&m_pWebService, 
                sSessionId, pService))
            {
                /* error : couldnot load web service */
                m_pSZ->
                    setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADSRV));
                break; // do .. while(0)
            }
            /* Check whether the provider type in the wsdd matchs the service's 
	     * binding style 
	     */
            AXIS_BINDING_STYLE nBindingStyle;
            if (0 != m_pWebService->_functions)
            /* C service */
            {
                nBindingStyle = m_pWebService->_functions->
                    GetBindingStyle (m_pWebService->_object);
            }
            else if (0 != m_pWebService->_object)
            {
                nBindingStyle = ((WrapperClassHandler *) 
                    m_pWebService->_object)->GetBindingStyle ();
            }
            
	    if (m_pSZ->GetStyle () != nBindingStyle)
            {
                AXISTRACE1 ("SF_SOAPCONTENTERROR", CRITICAL);
                m_pSZ->
                    setSoapFault(SoapFault::getSoapFault(SF_SOAPCONTENTERROR));
                break; // do .. while(0)
            }
        }
        else
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_METHODNOTALLOWED));
            // Method is not an exposed allowed method
            break; // do .. while(0)
        }
        
	// Get Global and Transport Handlers
        if (AXIS_SUCCESS != (Status = InitializeHandlers (sSessionId, 
            stream->trtype)))
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_COULDNOTLOADHDL));
            break; // do .. while(0)
        }
        // Get Service specific Handlers from the pool if configured any
        if (AXIS_SUCCESS != (Status = g_pHandlerPool->GetRequestFlowHandlerChain
            (&m_pSReqFChain, sSessionId, pService)))
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_COULDNOTLOADHDL));
            break; // do .. while(0)
        }

        if (AXIS_SUCCESS != (Status = 
            g_pHandlerPool->GetResponseFlowHandlerChain (&m_pSResFChain, 
            sSessionId, pService)))
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_COULDNOTLOADHDL));
            break; // do .. while(0)
        }
        /*
         * Let Deserializer parse the header section so that handlers can use 
	 * them. Each handler should remove the header block targetted to it
	 * and handlers may add header blocks to the DeSerializer and Serializer
	 * irrespective of whether it is request message path or response path.
	 * header may be added to the Deserializer ONLY IF there is a CAN BE
	 * a handler in this soap processor to handle it.
	 */
        if (AXIS_SUCCESS != m_pDZ->GetHeader ())
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_SOAPCONTENTERROR));
            break; // do .. while(0)                         
        }
        /*
         * Invoke all handlers including the webservice
         * in case of failure coresponding stream fault message will be set
         */
        Status = Invoke (m_pMsgData);
    } while (0);

    if (AXIS_SUCCESS != m_pDZ->FlushInputStream ())
    {
        AXISTRACE1 ("SF_SOAPCONTENTERROR", CRITICAL);
    }
    /*
     * Get any header blocks unprocessed (left) in the Deserializer and add them
     * to the Serializer
     * They may be headers targetted to next soap processors
     */
    HeaderBlock* pHderBlk = NULL;
    while (true)
    {
        /* Following function gets a header block from Deserializer irrespective
         * of any thing 
	 */
        pHderBlk = m_pDZ->GetHeaderBlock ();
        /* Add it to the Serializer */
        if (pHderBlk)
            m_pSZ->AddHeaderBlock (pHderBlk);
        else
            break;
    }
    m_pSZ->SetOutputStream (stream);

    // Pool back the Service specific handlers
    if (m_pSReqFChain)
        g_pHandlerPool->PoolHandlerChain (m_pSReqFChain, sSessionId);
    if (m_pSResFChain)
        g_pHandlerPool->PoolHandlerChain (m_pSResFChain, sSessionId);
    /* Pool back the Global and Transport handlers
     * UnInitializeHandlers(sSessionId, stream->trtype);
     * Pool back the webservice
     */ 
    if (m_pWebService)
        g_pHandlerPool->PoolWebService (sSessionId, m_pWebService, pService);
        // AXIS_CATCH(exception* e)
        //todo
        /* An exception derived from exception which is not handled will be 
	 * handled here. You can call a method in AxisModule which may unload 
	 * the ServerAxisEngine from the webserver and report the error. You can
	 * also write this in a logfile specific to axis.
         */
#ifdef _AXISTRACE

    delete (e);
#endif
    // AXIS_CATCH(...)
    // todo
    /*
     * An unknown exception which is not handled will be handled here.
     * You can call a method in AxisModule which may unload the ServerAxisEngine
     * from the webserver and report the error. You can also write this
     * in a logfile specific to axis.
     */

    // AXIS_ENDCATCH
    return AXIS_SUCCESS;
}

int ServerAxisEngine::Invoke (MessageData* pMsg)
{
    enum AE_LEVEL
    { AE_START = 1, AE_TRH, AE_GLH, AE_SERH, AE_SERV };
    int Status = AXIS_FAIL;
    int level = AE_START;
    do
    {
        // Invoke transport request handlers
        if (m_pTReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pTReqFChain->Invoke (pMsg)))
            {
                m_pSZ->setSoapFault (SoapFault::getSoapFault(SF_HANDLERFAILED));
                break; // do .. while (0)
            }

        }
        level++; // AE_TRH
        // Invoke global request handlers
        if (m_pGReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pGReqFChain->Invoke (pMsg)))
            {
                m_pSZ->setSoapFault (SoapFault::getSoapFault(SF_HANDLERFAILED));
                break; // do .. while (0)
            }
        }
        level++; // AE_GLH
        // Invoke service specific request handlers
        if (m_pSReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pSReqFChain->Invoke (pMsg)))
            {
                m_pSZ->setSoapFault (SoapFault::getSoapFault(SF_HANDLERFAILED));
                break; // do .. while (0)
            }
        }
        level++; // AE_SERH
        /*
         * Before processing the soap body check whether there is any header 
	 * blocks with mustUnderstand attribute left unprocessed in the 
	 * Deserializer. If so return a soap fault.
	 */
        if (m_pDZ->IsAnyMustUnderstandHeadersLeft ())
        {
            m_pSZ->setSoapFault (SoapFault::getSoapFault (SF_MUST_UNDERSTAND));
            break; // do .. while (0)
        }
        // Call actual web service handler
        if (m_pWebService)
        {
            if (0 != m_pWebService->_functions)
            /* C web service */
            {
                IMessageData_C cMC = { 0, 0 };
                cMC._object = pMsg;
                cMC._functions = &IMessageData::ms_VFtable;
                Status = m_pWebService->_functions->Invoke (m_pWebService->
                    _object, &cMC);
            }
            else if (0 != m_pWebService->_object)
            {
                Status = ((WrapperClassHandler *) m_pWebService->_object)->
                    Invoke (pMsg);
            }
            else
                Status = AXIS_FAIL;
            if (AXIS_SUCCESS != Status)
            {
                m_pSZ->
                    setSoapFault(SoapFault::getSoapFault(SF_WEBSERVICEFAILED));
                break;
            }
        }
        level++; // AE_SERV
    } while (0);

    pMsg->setPastPivotState (true);

    /*
     * The case clauses in this switch statement have no breaks.
     * Hence, if Everything up to web service invocation was successful
     * then all response handlers are invoked. If there was a failure
     * at some point the response handlers from that point onwards
     * are invoked.
     */
    switch (level)
    {
        case AE_SERV: // Everything Success.        
            Status = AXIS_SUCCESS;
            // no break;
        case AE_SERH: // Actual web service handler has failed
            // Invoke web service specific response handlers
            if (m_pSResFChain)
            {
                m_pSResFChain->Invoke (pMsg);
            }
            // no break;
        case AE_GLH: // web service specific handlers have failed
            // invoke global response handlers
            if (m_pGResFChain)
            {
                m_pGResFChain->Invoke (pMsg);
            }
            // no break;
        case AE_TRH: // Global handlers have failed
            if (m_pTResFChain)
            {
                m_pTResFChain->Invoke (pMsg);
            }
          // no break;
        case AE_START:; // Transport handlers have failed
    };
    return Status;
}

void ServerAxisEngine::OnFault (MessageData* pMsg)
{

}
