// ClientAxisEngine.cpp: implementation of the ClientAxisEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "ClientAxisEngine.h"
#include "../../wsdd/WSDDDeployment.h"
#include "../HandlerPool.h"
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

extern WSDDDeployment* g_pWSDDDeployment;
extern HandlerPool* g_pHandlerPool;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ClientAxisEngine::ClientAxisEngine()
{

}

ClientAxisEngine::~ClientAxisEngine()
{

}

MessageData* ClientAxisEngine::GetMessageData()
{
	return m_pMsgData;
}

int ClientAxisEngine::Process(Ax_soapstream* pSoap)
{
	int Status;
	const WSDDService* pService = NULL;

	if (!pSoap)
    {
        AXISTRACE1("Ax_soapstream is null", CRITICAL);
        return AXIS_FAIL;
    }
	m_pSoap = pSoap;

	string sSessionId = m_pSoap->sessionid;

	if (!(m_pSoap->transport.pSendFunct && m_pSoap->transport.pGetFunct &&
		m_pSoap->transport.pSetTrtFunct && m_pSoap->transport.pGetTrtFunct))
        {
            AXISTRACE1("transport is not set properly", CRITICAL);
            return AXIS_FAIL;
        }

	do {
		//const char* cService = get_header(soap, SOAPACTIONHEADER);

		const char* pchService = get_service_name(pSoap->so.http->uri_path);
		/* get service description object from the WSDD Deployment object */
		pService = g_pWSDDDeployment->GetService(pchService);

		//Get Global and Transport Handlers
		if(AXIS_SUCCESS != (Status = InitializeHandlers(sSessionId, pSoap->trtype)))
		{
		  break; //do .. while(0)
		}
    	//Get Service specific Handlers from the pool if configured any
		if (pService != NULL) {
			if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetRequestFlowHandlerChain(&m_pSReqFChain, sSessionId, pService)))
			{        
			  break; //do .. while(0)
			}
			if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetResponseFlowHandlerChain(&m_pSResFChain, sSessionId, pService)))
			{        
			  break; //do .. while(0)
			}
		}

		//Invoke all handlers and then the remote webservice
		Status = Invoke(m_pMsgData); //we generate response in the same way even if this has failed
		
	}
	while(0);

	//Pool back the Service specific handlers
	//if (m_pSReqFChain) g_pHandlerPool->PoolHandlerChain(m_pSReqFChain, sSessionId);
	//if (m_pSResFChain) g_pHandlerPool->PoolHandlerChain(m_pSResFChain, sSessionId);
	//Pool back the Global and Transport handlers
	//UnInitializeHandlers(sSessionId, soap->trtype);
	return Status;
}

int ClientAxisEngine::Invoke(MessageData* pMsg)
{
	enum AE_LEVEL {AE_START=1, AE_SERH, AE_GLH, AE_TRH, AE_SERV};
	int Status = AXIS_FAIL;
	int level = AE_START;

	do
	{
		//invoke client side service specific request handlers
		if (m_pSReqFChain)
		{
			if(AXIS_SUCCESS != (Status = m_pSReqFChain->Invoke(pMsg)))
			{
				//m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}
		}
//		AXISTRACE1("AFTER invoke service specific request handlers");
		level++; //AE_SERH		

		//invoke global request handlers
		if (m_pGReqFChain)
		{
			if(AXIS_SUCCESS != (Status = m_pGReqFChain->Invoke(pMsg)))
			{
				//m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}		
		}
//        AXISTRACE1("AFTER invoke global request handlers");
		level++; //AE_GLH	

		//invoke transport request handlers
		if (m_pTReqFChain) {
			if(AXIS_SUCCESS != (Status = m_pTReqFChain->Invoke(pMsg)))
			{
				//m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}
		}
//		AXISTRACE1("AFTER invoke transport request handlers");
		level++; // AE_TRH

		if (AXIS_SUCCESS != (Status = m_pSZ->SetOutputStream(m_pSoap))) break;
		m_pSZ->MarkEndOfStream();

		level++; // AE_SERV

		pMsg->setPastPivotState(true);

		if (AXIS_SUCCESS != (Status = m_pDZ->SetInputStream(m_pSoap))) break;
		
		int nSoapVersion = m_pDZ->GetVersion();
		if (nSoapVersion == VERSION_LAST) /* version not supported */
		{
			Status = AXIS_FAIL;
			//return AXIS_FAIL;
		}

		m_pDZ->GetHeader();

	}
	while(0);


	/*
	The case clauses in this switch statement have no breaks.
	Hence, if Everything up to web service invocation was successful
	then all response handlers are invoked. If there was a failure
	at some point the response handlers from that point onwards
	are invoked.
	*/
	switch (level)
	{
	case AE_SERV: //everything success
		Status = AXIS_SUCCESS;
		//no break;
	case AE_TRH: //after invoking the transport handlers (at actual service invokation) it has failed
		if (m_pTResFChain) 
		{
			m_pTResFChain->Invoke(pMsg);
		}
		//no break;
	case AE_GLH: //transport handlers have failed
		//invoke global response handlers
		if (m_pGResFChain)
		{
			m_pGResFChain->Invoke(pMsg);
		}
		//no break;
	case AE_SERH: //global handlers have failed
		//invoke web service specific response handlers
		if (m_pSResFChain)
		{
			m_pSResFChain->Invoke(pMsg);
		}
		//no break;
	case AE_START:;//service specific handlers have failed
	};
	
//	AXISTRACE1("end axisengine process()");
	return Status;
}

void ClientAxisEngine::OnFault(MessageData* pMsg)
{

}

char* ClientAxisEngine::get_service_name(const char* pch_uri_path)
{
	//return "InteropBaseDL";

	char* pachTmp = strrchr(pch_uri_path, '/');

	if (pachTmp != NULL) {
		int iTmp = strlen(pachTmp);

		if (iTmp <= 1) {
			return NULL;
		} else {
			pachTmp = pachTmp +1;
		}
	}

	return pachTmp;
}
