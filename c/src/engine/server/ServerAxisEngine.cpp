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
#include "../../common/AxisUtils.h"
#include "../../wsdd/WSDDDeployment.h"
#include "../HandlerPool.h"
#include <axis/server/AxisMessage.h>
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

int ServerAxisEngine::process(SOAPTransport* pStream)
{
    int Status = 0;
    //const WSDDService* pService = NULL;
    int nSoapVersion;
    AXISC_TRY
    if (!pStream)
    {
        AXISTRACE1 ("transport is not set properly", CRITICAL);
        THROW_AXIS_CONFIG_EXCEPTION(SERVER_CONFIG_TRANSPORTCONFFAILED);
    }
     string sSessionId = pStream->getSessionId();
   
    /*
     * After this point we should return AXIS_SUCCESS. Otherwise the transport 
     * layer may not send the response back (either soap fault or result).
     */
    do
    {
        /* populate MessageData with transport information */
        m_pMsgData->m_Protocol = pStream->getProtocol();

        if (AXIS_SUCCESS != m_pDZ->setInputStream(pStream))
        {
            nSoapVersion = m_pDZ->getVersion ();
            nSoapVersion = 
                (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
            m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion);
            AXISTRACE1 ("CLIENT_SOAP_SOAPCONTENTERROR", CRITICAL);
            THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_SOAPCONTENTERROR);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_SOAP_SOAPCONTENTERROR));
            break; // do .. while(0)
        }

        const char* cService = pStream->getTransportProperty(SERVICE_URI);
        if (!cService)
        {
            AXISTRACE1 ("CLIENT_SOAP_SOAPCONTENTERROR", CRITICAL);
            THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_SOAPCONTENTERROR);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_SOAP_SOAPCONTENTERROR));
            break; // do .. while(0)
        }
        AxisString service = (cService == NULL) ? "" : cService;

        if (service.empty ())
        {
            nSoapVersion = m_pMsgData->m_pDZ->getVersion ();
            nSoapVersion =
                (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
            m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion);
            AXISTRACE1("CLIENT_SOAP_SOAPACTIONEMTPY", CRITICAL);
            THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_SOAPACTIONEMTPY);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_SOAP_SOAPACTIONEMTPY));
            break; // do .. while(0)
        }
        /* if there are quotes remove them. */
        if (service.find ('\"') != string::npos)
        {
            service = service.substr (1, service.length () - 2);
        }

        /* get service description object from the WSDD Deployment object */
        m_pService = g_pWSDDDeployment->getService (service.c_str ());
        if (!m_pService)
        {
            nSoapVersion = m_pMsgData->m_pDZ->getVersion ();
            nSoapVersion =
                (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
            m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion);
            AXISTRACE1("CLIENT_WSDD_SERVICENOTFOUND", CRITICAL);
            THROW_AXIS_WSDD_EXCEPTION(CLIENT_WSDD_SERVICENOTFOUND);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_WSDD_SERVICENOTFOUND));
            break; // do .. while(0)
        }

        m_pMsgData->setService (m_pService);

        m_CurrentProviderType = m_pService->getProvider ();
        m_pSZ->setCurrentProviderType (m_CurrentProviderType);
        m_pDZ->setCurrentProviderType (m_CurrentProviderType);
        switch (m_CurrentProviderType)
        {
            case C_RPC_PROVIDER:
            case CPP_RPC_PROVIDER:
                m_pSZ->setStyle (RPC_ENCODED);
                m_pDZ->setStyle (RPC_ENCODED);
                break;
            case C_DOC_PROVIDER:
            case CPP_DOC_PROVIDER:
                m_pSZ->setStyle (DOC_LITERAL);
                m_pDZ->setStyle (DOC_LITERAL);
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
        nSoapVersion = m_pDZ->getVersion ();
        if (m_pDZ->getStatus () != AXIS_SUCCESS)
        {
            AXISTRACE1("CLIENT_SOAP_MESSAGEINCOMPLETE", CRITICAL);
            THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_MESSAGEINCOMPLETE);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault(CLIENT_SOAP_MESSAGEINCOMPLETE));
            break; // do .. while(0)
        }

        if (nSoapVersion == VERSION_LAST)     /* version not supported */
        {
            m_pSZ->setSoapVersion (SOAP_VER_1_2);
            AXISTRACE1("SOAP_VERSIONMISMATCH", CRITICAL);
            THROW_AXIS_EXCEPTION(SOAP_VERSIONMISMATCH);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (SOAP_VERSIONMISMATCH));
            break; // do .. while(0)         
        }

        /* Set Soap version in the Serializer and the envelope */
        if (AXIS_SUCCESS != m_pSZ->setSoapVersion ((SOAP_VERSION) nSoapVersion))
        {
            AXISTRACE1 ("CLIENT_SOAP_SOAPCONTENTERROR", CRITICAL);
            THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_SOAPCONTENTERROR);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_SOAP_SOAPCONTENTERROR));
            break; // do .. while(0)
        }

        /* Get the operation name from transport information Ex: from 
	 * SOAPAction header 
	 */
        AxisString sOperation = pStream->getTransportProperty(OPERATION_NAME);
        if (sOperation.empty ())
        {
            AXISTRACE1("CLIENT_SOAP_NOSOAPMETHOD", CRITICAL);
            THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_NOSOAPMETHOD);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_SOAP_NOSOAPMETHOD));
            break; // do .. while(0)
        }
        /* remove any quotes in the operation name */
        if (sOperation.rfind ('\"') != string::npos)
        {
            sOperation = sOperation.substr (0, sOperation.length () - 1);
        }

        m_pMsgData->setOperationName (sOperation.c_str ());

        if (m_pService->isAllowedMethod (sOperation.c_str ()))
        {
            /* load actual web service handler */
            if (AXIS_SUCCESS != g_pHandlerPool->getWebService (&m_pWebService, 
                sSessionId, m_pService))
            {
                /* error : couldnot load web service */
                AXISTRACE1("SERVER_ENGINE_COULDNOTLOADSRV", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_COULDNOTLOADSRV);
                //m_pSZ->
                //    setSoapFault(SoapFault::getSoapFault(SERVER_ENGINE_COULDNOTLOADSRV));
                break; // do .. while(0)
            }

            /* Check whether the provider type in the wsdd matchs the service's 
	     * binding style 
	     */
            AXIS_BINDING_STYLE nBindingStyle =  RPC_ENCODED;
            if (0 != m_pWebService->_functions)
            /* C service */
            {
                nBindingStyle = m_pWebService->_functions->
                    getBindingStyle (m_pWebService->_object);
            }
            else if (0 != m_pWebService->_object)
            {
                nBindingStyle = ((WrapperClassHandler *) 
                    m_pWebService->_object)->getBindingStyle ();
            }
            
	    if (m_pSZ->getStyle () != nBindingStyle)
            {
                AXISTRACE1 ("CLIENT_SOAP_SOAPCONTENTERROR", CRITICAL);
                THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_SOAPCONTENTERROR);
                //m_pSZ->
                //    setSoapFault(SoapFault::getSoapFault(CLIENT_SOAP_SOAPCONTENTERROR));
                break; // do .. while(0)
            }
        }
        else
        {
            AXISTRACE1("CLIENT_WSDD_METHODNOTALLOWED", CRITICAL);
            THROW_AXIS_WSDD_EXCEPTION(CLIENT_WSDD_METHODNOTALLOWED);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_WSDD_METHODNOTALLOWED));
            // Method is not an exposed allowed method
            break; // do .. while(0)
        }
        
	// Get Global and Transport Handlers
        if (AXIS_SUCCESS != (Status = initializeHandlers (sSessionId, 
            pStream->getProtocol())))
        {
            AXISTRACE1("SERVER_ENGINE_COULDNOTLOADHDL", CRITICAL);
            THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_COULDNOTLOADHDL);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (SERVER_ENGINE_COULDNOTLOADHDL));
            break; // do .. while(0)
        }
        // Get Service specific Handlers from the pool if configured any
        if (AXIS_SUCCESS != (Status = g_pHandlerPool->getRequestFlowHandlerChain
            (&m_pSReqFChain, sSessionId, m_pService)))
        {
            AXISTRACE1("SERVER_ENGINE_COULDNOTLOADHDL", CRITICAL);
            THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_COULDNOTLOADHDL);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (SERVER_ENGINE_COULDNOTLOADHDL));
            break; // do .. while(0)
        }

        if (AXIS_SUCCESS != (Status = 
            g_pHandlerPool->getResponseFlowHandlerChain (&m_pSResFChain, 
            sSessionId, m_pService)))
        {
            AXISTRACE1("SERVER_ENGINE_COULDNOTLOADHDL", CRITICAL);
            THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_COULDNOTLOADHDL);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (SERVER_ENGINE_COULDNOTLOADHDL));
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
        if (AXIS_SUCCESS != m_pDZ->getHeader ())
        {
            AXISTRACE1 ("CLIENT_SOAP_SOAPCONTENTERROR", CRITICAL);
            THROW_AXIS_SOAP_EXCEPTION(CLIENT_SOAP_SOAPCONTENTERROR);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_SOAP_SOAPCONTENTERROR));
            break; // do .. while(0)                         
        }
        /*
         * Invoke all handlers including the webservice
         * in case of failure coresponding stream fault message will be set
         */
        Status = invoke (m_pMsgData);
    } while (0);

    if (AXIS_SUCCESS != m_pDZ->flushInputStream ())
    {
        AXISTRACE1 ("CLIENT_SOAP_SOAPCONTENTERROR", CRITICAL);
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
        pHderBlk = m_pDZ->getHeaderBlock ();
        /* Add it to the Serializer */
        if (pHderBlk)
            m_pSZ->addHeaderBlock (pHderBlk);
        else
            break;
    }
    m_pSZ->setOutputStream (pStream);

    // Pool back the handlers and services
    releaseHandlers(pStream);
    //todo
    /* An exception derived from exception which is not handled will be 
     * handled here. You can call a method in AxisModule which may unload 
     * the ServerAxisEngine from the webserver and report the error. You can
     * also write this in a logfile specific to axis.
    */
    AXISC_CATCH(AxisException& e)
    /*
     * An exception which is not handled will be handled here.
     */
     //m_pSZ->setSoapFault (SoapFault::getSoapFault (CLIENT_SOAP_SOAPCONTENTERROR));
#ifdef ENABLE_AXIS_EXCEPTION
        int iExceptionCode = e.getExceptionCode();
        char* pcTempStr = (char*) e.what();
        AXISTRACE2("Exception:", pcTempStr, CRITICAL);
        if(AXISC_SERVICE_THROWN_EXCEPTION == iExceptionCode)
        {
            /*Writes the SoapMessage in which soap body contains only Fault*/
            m_pSZ->setOutputStream (pStream);
            releaseHandlers(pStream);
            return AXIS_SUCCESS;//Service created fault is written to the stream. 
                                //so return success.
        }
        else/* An exception has occured inside Axis C++ engine.(not in a
             * webservice or handler). Later we handle this according to the
             * exception code returned.
             */
            return e.getExceptionCode();
#endif
    AXISC_CATCH(exception& e)
#ifdef ENABLE_AXIS_EXCEPTION
    /* Handle standerd exceptions here
     */
#endif
    AXISC_CATCH(...)
#ifdef ENABLE_AXIS_EXCEPTION
        return SERVER_UNKNOWN_ERROR;
#endif
    AXISC_ENDCATCH
    return AXIS_SUCCESS;
}

int ServerAxisEngine::invoke (MessageData* pMsg)
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
            if (AXIS_SUCCESS != (Status = m_pTReqFChain->invoke (pMsg)))
            {
                AXISTRACE1("SERVER_ENGINE_HANDLERFAILED", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLERFAILED);
                //m_pSZ->setSoapFault (SoapFault::getSoapFault(SERVER_ENGINE_HANDLERFAILED));
                break; // do .. while (0)
            }

        }
        level++; // AE_TRH
        // Invoke global request handlers
        if (m_pGReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pGReqFChain->invoke (pMsg)))
            {
                AXISTRACE1("SERVER_ENGINE_HANDLERFAILED", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLERFAILED);
                //m_pSZ->setSoapFault (SoapFault::getSoapFault(SERVER_ENGINE_HANDLERFAILED));
                break; // do .. while (0)
            }
        }
        level++; // AE_GLH
        // Invoke service specific request handlers
        if (m_pSReqFChain)
        {
            if (AXIS_SUCCESS != (Status = m_pSReqFChain->invoke (pMsg)))
            {
                AXISTRACE1("SERVER_ENGINE_HANDLERFAILED", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLERFAILED);
                //m_pSZ->setSoapFault (SoapFault::getSoapFault(SERVER_ENGINE_HANDLERFAILED));
                break; // do .. while (0)
            }
        }
        level++; // AE_SERH
        /*
         * Before processing the soap body check whether there is any header 
	 * blocks with mustUnderstand attribute left unprocessed in the 
	 * Deserializer. If so return a soap fault.
	 */
        if (m_pDZ->isAnyMustUnderstandHeadersLeft ())
        {
            AXISTRACE1("SOAP_MUSTUNDERSTAND", CRITICAL);
            THROW_AXIS_EXCEPTION(SOAP_MUSTUNDERSTAND);
            //m_pSZ->setSoapFault (SoapFault::getSoapFault (SOAP_MUSTUNDERSTAND));
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
                Status = m_pWebService->_functions->invoke (m_pWebService->
                    _object, &cMC);
            }
            else if (0 != m_pWebService->_object)
            {
                Status = ((WrapperClassHandler *) m_pWebService->_object)->
                    invoke (pMsg);
                AXISTRACE1("came", INFO);
            }
            else
                Status = AXIS_FAIL;
            if (AXIS_SUCCESS != Status)
            {
                AXISTRACE1("SERVER_ENGINE_WEBSERVICEFAILED", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_WEBSERVICEFAILED);
                //m_pSZ->
                //    setSoapFault(SoapFault::getSoapFault(SERVER_ENGINE_WEBSERVICEFAILED));
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
                m_pSResFChain->invoke (pMsg);
            }
            // no break;
        case AE_GLH: // web service specific handlers have failed
            // invoke global response handlers
            if (m_pGResFChain)
            {
                m_pGResFChain->invoke (pMsg);
            }
            // no break;
        case AE_TRH: // Global handlers have failed
            if (m_pTResFChain)
            {
                m_pTResFChain->invoke (pMsg);
            }
          // no break;
        case AE_START:; // Transport handlers have failed
    };
    return Status;
}

void ServerAxisEngine::onFault (MessageData* pMsg)
{
}

int ServerAxisEngine::setFaultOutputStream(int iFaultCode, SOAPTransport* pStream)
{
    AxisMessage objMessage;
    string sMessage = objMessage.getMessage(iFaultCode);
    SoapFault* pObjSoapFault = SoapFault::getSoapFault(iFaultCode);
    pObjSoapFault->setFaultDetail(sMessage);
    AXISTRACE1("came70", INFO);
    m_pSZ->setSoapFault(pObjSoapFault);
    AXISTRACE1("came71", INFO);
    m_pSZ->setOutputStream(pStream);
    AXISTRACE1("came72", INFO);
    releaseHandlers(pStream);
    AXISTRACE1("came73", INFO);
    return AXIS_SUCCESS;
}

int ServerAxisEngine::releaseHandlers(SOAPTransport* pStream)
{
    string sSessionId = pStream->getSessionId();
    // Pool back the Service specific handlers
    if (m_pSReqFChain)
        g_pHandlerPool->poolHandlerChain (m_pSReqFChain, sSessionId);
    if (m_pSResFChain)
        g_pHandlerPool->poolHandlerChain (m_pSResFChain, sSessionId);
    /* Pool back the Global and Transport handlers
     * UnInitializeHandlers(sSessionId, stream->trtype);
     * Pool back the webservice
     */
    if (m_pWebService)
        g_pHandlerPool->poolWebService (sSessionId, m_pWebService, m_pService);

    return AXIS_SUCCESS;
}
