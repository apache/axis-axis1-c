// ServerAxisEngine.cpp: implementation of the ServerAxisEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "ServerAxisEngine.h"
#include <stdio.h>
#include "../common/AxisException.h"
#include "../common/AxisTrace.h"
#include "../common/AxisUtils.h"
#include "../wsdd/WSDDDeployment.h"
#include "HandlerPool.h"

extern HandlerPool* g_pHandlerPool;
extern WSDDDeployment* g_pWSDDDeployment;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ServerAxisEngine::ServerAxisEngine()
{
	m_pWebService = NULL;
}

ServerAxisEngine::~ServerAxisEngine()
{

}

int ServerAxisEngine::Process(Ax_soapstream* soap) 
{
	int Status;
	AXIS_TRY
		AXISTRACE1("ServerAxisEngine::Process");
		const WSDDService* pService = NULL;
		string sSessionId = soap->sessionid;
        AXISTRACE2("ServerAxisEngine::Process", sSessionId.c_str());
		int nSoapVersion;

		do {
			//populate MessageData with transport information
			m_pMsgData->m_Protocol = soap->trtype;
    
			if (SUCCESS != m_pDZ->SetInputStream(soap->str.ip_stream))
			{
				nSoapVersion = m_pDZ->GetVersion();
				nSoapVersion = (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
				m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion);
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SOAPCONTENTERROR));
				break; //do .. while(0)
			}

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
				nSoapVersion = m_pMsgData->m_pDZ->GetVersion();
				nSoapVersion = (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
				m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion);
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SOAPACTIONEMPTY));
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
				nSoapVersion = m_pMsgData->m_pDZ->GetVersion();
				nSoapVersion = (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
				m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion);
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SERVICENOTFOUND));
				break; //do .. while(0)
			}

			m_pMsgData->SetService(pService);
			
			//check for soap version in the request and decide whether we support it or not
			//if we do not support send a soapfault with version mismatch.		  
			nSoapVersion = m_pMsgData->m_pDZ->GetVersion();
			if (nSoapVersion == VERSION_LAST) //version not supported
			{
				m_pSZ->setSoapVersion(SOAP_VER_1_2);
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_VERSION_MISMATCH));
				break; //do .. while(0)		
			}		  


			//Set Soap version in the Serializer and the envelope
			if (SUCCESS != m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion))
			{
			  m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SOAPCONTENTERROR));
			  break; //do .. while(0)
			}

			SoapMethod* pSm = m_pDZ->GetMethod();
			if (pSm) 
			{
				const AxisChar* pMethod = pSm->getMethodName();
//				AXISTRACE2("pSm->getMethodName(); :", pMethod);
				if (pMethod)
				{
					if (pService->IsAllowedMethod(pMethod))
					{          
						//load actual web service handler
						if (SUCCESS != g_pHandlerPool->GetWebService(&m_pWebService, sSessionId, pService))
						{
            				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADSRV));
							//Error couldnot load web service
							break; //do .. while(0)
						}
					}
					else
					{
						m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_METHODNOTALLOWED));
						//method is not an exposed allowed method
						break; //do .. while(0)
					}
				}
				else
				{
					m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_NOSOAPMETHOD));
					//no method to be invoked
					break; //do .. while(0)
				}
			}
			//Get Global and Transport Handlers
			if(SUCCESS != (Status = InitializeHandlers(sSessionId, soap->trtype)))
			{
			  m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADHDL));
			  break; //do .. while(0)
			}
    		//Get Service specific Handlers from the pool if configured any
			if(SUCCESS != (Status = g_pHandlerPool->GetRequestFlowHandlerChain(&m_pSReqFChain, sSessionId, pService)))
			{        
			  m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADHDL));
			  break; //do .. while(0)
			}
			if(SUCCESS != (Status = g_pHandlerPool->GetResponseFlowHandlerChain(&m_pSResFChain, sSessionId, pService)))
			{        
			  m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADHDL));
			  break; //do .. while(0)
			}

			//and handlers may add headers to the Serializer.
			//Invoke all handlers including the webservice
			//in case of failure coresponding soap fault message will be set
			Status = Invoke(m_pMsgData); //we generate response in the same way even if this has failed
		}
		while(0);
		//send any transoport information like http headers first
		send_transport_information(soap);
		//Serialize
		m_pSZ->SetOutputStream(soap->str.op_stream);

		//Pool back the Service specific handlers
		if (m_pSReqFChain) g_pHandlerPool->PoolHandlerChain(m_pSReqFChain, sSessionId);
		if (m_pSResFChain) g_pHandlerPool->PoolHandlerChain(m_pSResFChain, sSessionId);
		//Pool back the Global and Transport handlers
		//UnInitializeHandlers(sSessionId, soap->trtype);
		//Pool back the webservice
		if (m_pWebService) g_pHandlerPool->PoolWebService(sSessionId, m_pWebService, pService); 
		return Status;
	AXIS_CATCH(exception* e)
		//todo
		/*
		An exception derived from exception which is not handled will be handled here.
		You can call a method in AxisModule which may unload the ServerAxisEngine
		from the webserver and report the error. You can also write this
		in a logfile specific to axis.
		*/
		#ifdef _AXISTRACE
//		AXISTRACE1(e->what());   
		delete(e);
		#endif
	AXIS_CATCH(...)
		//todo
		/*
		An unknown exception which is not handled will be handled here.
		You can call a method in AxisModule which may unload the ServerAxisEngine
		from the webserver and report the error. You can also write this
		in a logfile specific to axis.
		*/
//		AXISTRACE1("UNKNOWN EXCEPTION");
	AXIS_ENDCATCH
	return Status;
}

int ServerAxisEngine::Invoke(MessageData* pMsg)
{
	enum AE_LEVEL {AE_START=1, AE_TRH, AE_GLH, AE_SERH, AE_SERV};
	int Status = FAIL;
	int level = AE_START;
	do
	{
		//invoke transport request handlers
		if (m_pTReqFChain) {
			if(SUCCESS != (Status = m_pTReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_HANDLERFAILED));
				break; //do .. while (0)
			}

		}
//		AXISTRACE1("AFTER invoke transport request handlers");
		level++; // AE_TRH
		//invoke global request handlers
		if (m_pGReqFChain)
		{
			if(SUCCESS != (Status = m_pGReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_HANDLERFAILED));
				break; //do .. while (0)
			}		
		}
//        AXISTRACE1("AFTER invoke global request handlers");
		level++; //AE_GLH
		//invoke service specific request handlers
		if (m_pSReqFChain)
		{
			if(SUCCESS != (Status = m_pSReqFChain->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_HANDLERFAILED));
				break; //do .. while (0)
			}
		}
//		AXISTRACE1("AFTER invoke service specific request handlers");
		level++; //AE_SERH
		//call actual web service handler
		if (m_pWebService)
		{
			if (SUCCESS != (Status = m_pWebService->Invoke(pMsg)))
			{
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_WEBSERVICEFAILED));
				break;
			}        
		}
//		AXISTRACE1("AFTER call actual web service handler");
		level++; //AE_SERV
	}
	while(0);

	pMsg->setPastPivotState(true);

	/*
	The case clauses in this switch statement have no breaks.
	Hence, if Everything up to web service invokation was successful
	then all response handlers are invoked. If there was a failure
	at some point the response handlers from that point onwards
	are invoked.
	*/
	switch (level)
	{
	
	case AE_SERV: //Everything Success.
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

void ServerAxisEngine::OnFault(MessageData* pMsg)
{
	
}

