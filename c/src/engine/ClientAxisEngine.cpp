// ClientAxisEngine.cpp: implementation of the ClientAxisEngine class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/engine/ClientAxisEngine.h>
#include <axis/wsdd/WSDDDeployment.h>
#include <axis/engine/HandlerPool.h>

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
	//const WSDDService* pService = NULL;

	if (!pSoap) return AXIS_FAIL;
	m_pSoap = pSoap;

	string sSessionId = m_pSoap->sessionid;

	if (!(m_pSoap->transport.pSendFunct && m_pSoap->transport.pGetFunct &&
		m_pSoap->transport.pSendTrtFunct && m_pSoap->transport.pGetTrtFunct))
		return AXIS_FAIL;

	do {
		//const char* cService = get_header(soap, SOAPACTIONHEADER);
/*
		//Get Global and Transport Handlers
		if(AXIS_SUCCESS != (Status = InitializeHandlers(sSessionId, soap->trtype)))
		{
		  break; //do .. while(0)
		}
    	//Get Service specific Handlers from the pool if configured any
		if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetRequestFlowHandlerChain(&m_pSReqFChain, sSessionId, pService)))
		{        
		  break; //do .. while(0)
		}
		if(AXIS_SUCCESS != (Status = g_pHandlerPool->GetResponseFlowHandlerChain(&m_pSResFChain, sSessionId, pService)))
		{        
		  break; //do .. while(0)
		}
*/

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
	enum AE_LEVEL {AE_START=1, AE_TRH, AE_GLH, AE_SERH, AE_SERV};
	int Status = AXIS_FAIL;
	//int level = AE_START;
	/*
	No Client side handlers for now. Therefore returns AXIS_SUCCESS
	*/
	Status = AXIS_SUCCESS;

	/*
	do
	{
		//invoke client side service specific request handlers
		if (m_pSReqFChain)
		{
			if(AXIS_SUCCESS != (Status = m_pSReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}
		}
//		AXISTRACE1("AFTER invoke service specific request handlers");
		level++; //AE_SERH		//invoke transport request handlers
		//invoke global request handlers
		if (m_pGReqFChain)
		{
			if(AXIS_SUCCESS != (Status = m_pGReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}		
		}
//        AXISTRACE1("AFTER invoke global request handlers");
		level++; //AE_GLH	
		if (m_pTReqFChain) {
			if(AXIS_SUCCESS != (Status = m_pTReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}
		}
//		AXISTRACE1("AFTER invoke transport request handlers");
		level++; // AE_TRH


	}
	while(0);
	*/
	
	do 
	{
		if (AXIS_SUCCESS != (Status = m_pSoap->transport.pSendTrtFunct(m_pSoap))) break;
		if (AXIS_SUCCESS != (Status = m_pSZ->SetOutputStream(m_pSoap))) break;
		pMsg->setPastPivotState(true);
		if (AXIS_SUCCESS != (Status = m_pSoap->transport.pGetTrtFunct(m_pSoap))) break;
		if (AXIS_SUCCESS != (Status = m_pDZ->SetInputStream(m_pSoap))) break;
	}
	while(0);

	/*
	switch (level)
	{
	case AE_SERV: //everything success
		Status = AXIS_SUCCESS;
		//no break;
	case AE_SERH: //actual web service handler has failed
		//invoke web service specific response handlers
		if (m_pSResFChain)
		{
			m_pSResFChain->Invoke(pMsg);
		}
		//no break;
	case AE_GLH: //web service specific handlers have failed
		//invoke global response handlers
		if (m_pGResFChain)
		{
			m_pGResFChain->Invoke(pMsg);
		}
		//no break;
	case AE_TRH: //global handlers have failed
		if (m_pTResFChain) 
		{
			m_pTResFChain->Invoke(pMsg);
		}
		//no break;
	case AE_START:;//transport handlers have failed
	};
	*/
//	AXISTRACE1("end axisengine process()");
	return Status;
}

void ClientAxisEngine::OnFault(MessageData* pMsg)
{

}
