// ClientAxisEngine.cpp: implementation of the ClientAxisEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "ClientAxisEngine.h"
#include "../wsdd/WSDDDeployment.h"
#include "HandlerPool.h"

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

int ClientAxisEngine::Process(Ax_soapstream* soap)
{
	int Status;
	const WSDDService* pService = NULL;
	string sSessionId = soap->sessionid;
	int nSoapVersion;

	do {
		//populate MessageData with transport information
		m_pMsgData->m_Protocol = soap->trtype;

		const char* cService = get_header(soap, SOAPACTIONHEADER);
		if (!cService) //get from URL if http
		{
			cService = get_service_from_uri(soap);
		}
		AxisString service = (cService == NULL)? "" : cService;
		//AxisUtils::convert(service, (cService == NULL)? "" : cService);
	  
//			AXISTRACE2("string service = ",service.c_str());
 
		if (service.empty()) 
		{
			break; //do .. while(0)
		}
		if (service.find('\"') != string::npos) //if there are quotes remove them.
		{
			service = service.substr(1, service.length() - 2);
		}

		//get service description object from the WSDD
		pService = g_pWSDDDeployment->GetService(service.c_str());
		if (!pService) 
		{
			break; //do .. while(0)
		}

		m_pMsgData->SetService(pService);
		
		//Get Global and Transport Handlers
		if(SUCCESS != (Status = InitializeHandlers(sSessionId, soap->trtype)))
		{
		  break; //do .. while(0)
		}
    	//Get Service specific Handlers from the pool if configured any
		if(SUCCESS != (Status = g_pHandlerPool->GetRequestFlowHandlerChain(&m_pSReqFChain, sSessionId, pService)))
		{        
		  break; //do .. while(0)
		}
		if(SUCCESS != (Status = g_pHandlerPool->GetResponseFlowHandlerChain(&m_pSResFChain, sSessionId, pService)))
		{        
		  break; //do .. while(0)
		}

		//and handlers may add headers to the Serializer.
		//Invoke all handlers and then the remote webservice
		Status = Invoke(m_pMsgData); //we generate response in the same way even if this has failed
	}
	while(0);

	//Pool back the Service specific handlers
	if (m_pSReqFChain) g_pHandlerPool->PoolHandlerChain(m_pSReqFChain, sSessionId);
	if (m_pSResFChain) g_pHandlerPool->PoolHandlerChain(m_pSResFChain, sSessionId);
	//Pool back the Global and Transport handlers
	//UnInitializeHandlers(sSessionId, soap->trtype);
	return Status;
}

int ClientAxisEngine::Invoke(MessageData* pMsg)
{
	enum AE_LEVEL {AE_START=1, AE_TRH, AE_GLH, AE_SERH, AE_SERV};
	int Status = FAIL;
	int level = AE_START;
	do
	{
		//invoke client side service specific request handlers
		if (m_pSReqFChain)
		{
			if(SUCCESS != (Status = m_pSReqFChain->Invoke(pMsg)))
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
			if(SUCCESS != (Status = m_pGReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}		
		}
//        AXISTRACE1("AFTER invoke global request handlers");
		level++; //AE_GLH	
		if (m_pTReqFChain) {
			if(SUCCESS != (Status = m_pTReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_CLIENTHANDLERFAILED));
				break; //do .. while (0)
			}
		}
//		AXISTRACE1("AFTER invoke transport request handlers");
		level++; // AE_TRH


	}
	while(0);
/*
	send_transport_information(soap);
	//Serialize and send to server
	m_pSZ->SetOutputStream(soap->str.op_stream);

	pMsg->setPastPivotState(true);

	receive_transport_information(&soap);
	//receive response from the server and Deserialize
	m_pDZ->SetInputStream(soap->str.ip_stream);
*/
	switch (level)
	{
	case AE_SERV: //everything success
		Status = SUCCESS;
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
//	AXISTRACE1("end axisengine process()");
	return Status;
}

void ClientAxisEngine::OnFault(MessageData* pMsg)
{

}
