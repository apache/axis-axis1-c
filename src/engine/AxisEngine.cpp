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

#include <stdio.h>
#include "AxisEngine.h"
#include "../common/AxisException.h"
#include "../common/Debug.h"
#include "../common/Packet.h"
#include "../common/AxisUtils.h"
#include "../wsdd/WSDDDeployment.h"
#include "HandlerPool.h"
#include "DeserializerPool.h"
#include "SerializerPool.h"

extern DeserializerPool* g_pDeserializerPool;
extern SerializerPool* g_pSerializerPool;
extern HandlerPool* g_pHandlerPool;
extern WSDDDeployment* g_pWSDDDeployment;

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
	m_pWebService = NULL;
}

AxisEngine::~AxisEngine()
{
	if (m_pSZ) g_pSerializerPool->PutInstance(m_pSZ);
	if (m_pDZ) g_pDeserializerPool->PutInstance(m_pDZ);
}

int AxisEngine::Process(Ax_soapstream* soap) 
{
	int Status;
	AXIS_TRY
		DEBUG1("AxisEngine::Process");
		MessageData* pMsg = NULL;
		const WSDDService* pService = NULL;
		string sSessionId = soap->sessionid;
		int nSoapVersion;

		do {
			//create and populate MessageData
			if (SUCCESS != Initialize())
			{
				nSoapVersion = m_pDZ->GetVersion();
				nSoapVersion = (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
				m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion);
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADSRV));
				break; //do .. while(0)
			}
			pMsg = new MessageData();
			pMsg->m_Protocol = soap->trtype;
			pMsg->SetSerializer(m_pSZ);
			pMsg->SetDeSerializer(m_pDZ);
    
			if (SUCCESS != m_pDZ->SetInputStream(soap->str.ip_stream))
			{
				nSoapVersion = m_pDZ->GetVersion();
				nSoapVersion = (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
				m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion);
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SOAPCONTENTERROR));
				break; //do .. while(0)
			}

			char* cService= getheader(soap, SOAPACTIONHEADER);
			AxisString service;
			AxisUtils::convert(service, (cService == NULL)? "" : cService);
		  
			DEBUG2("string service = ",service.c_str());
     
			if (service.empty()) 
			{
				nSoapVersion = pMsg->m_pDZ->GetVersion();
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
			pService = g_pWSDDDeployment->GetService(service);
			if (!pService) 
			{
				nSoapVersion = pMsg->m_pDZ->GetVersion();
				nSoapVersion = (nSoapVersion == VERSION_LAST) ? SOAP_VER_1_2 : nSoapVersion;
				m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion);
				m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SERVICENOTFOUND));
				break; //do .. while(0)
			}

			pMsg->SetService(pService);
			
			//check for soap version in the request and decide whether we support it or not
			//if we do not support send a soapfault with version mismatch.		  
			nSoapVersion = pMsg->m_pDZ->GetVersion();
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
				AxisString method = pSm->getMethodName();
				DEBUG2("pSm->getMethodName(); :", method.c_str());
				if (!method.empty())
				{
					if (pService->IsAllowedMethod(method))
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
			Status = Invoke(pMsg); //we generate response in the same way even if this has failed
		}
		while(0);
		if (pMsg) delete pMsg; //MessageData is no longer needed
		//send any transoport information like http headers first
		send_transport_information(soap);
		//Serialize
		m_pSZ->SetOutputStream(soap->str.op_stream);

		//Pool back the Service specific handlers
		if (m_pSReqFChain) g_pHandlerPool->PoolHandlerChain(m_pSReqFChain, sSessionId);
		if (m_pSResFChain) g_pHandlerPool->PoolHandlerChain(m_pSResFChain, sSessionId);
		//Pool back the webservice
		if (m_pWebService) g_pHandlerPool->PoolWebService(sSessionId, m_pWebService, pService); 
		return Status;
	AXIS_CATCH(exception* e)
		//todo
		/*
		An exception derived from exception which is not handled will be handled here.
		You can call a method in AxisModule which may unload the AxisEngine
		from the webserver and report the error. You can also write this
		in a logfile specific to axis.
		*/
		#ifdef _DEBUG
		DEBUG1(e->what());   
		delete(e);
		#endif
	AXIS_CATCH(...)
		//todo
		/*
		An unknown exception which is not handled will be handled here.
		You can call a method in AxisModule which may unload the AxisEngine
		from the webserver and report the error. You can also write this
		in a logfile specific to axis.
		*/
		DEBUG1("UNKNOWN EXCEPTION");
	AXIS_ENDCATCH
	return Status;
}

int AxisEngine::Invoke(MessageData* pMsg)
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
		DEBUG1("AFTER invoke transport request handlers");
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
		DEBUG1("AFTER invoke global request handlers");
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
		DEBUG1("AFTER invoke service specific request handlers");
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
		DEBUG1("AFTER call actual web service handler");
		level++; //AE_SERV
	}
	while(0);

	pMsg->setPastPivotState(true);

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
	DEBUG1("end axisengine process()");
	return Status;
}

void AxisEngine::OnFault(MessageData* pMsg)
{
	
}

int AxisEngine::Initialize()
{
	int Status;
	//Create and initialize Serializer and Deserializer objects
	if (SUCCESS != (Status = g_pSerializerPool->GetInstance(&m_pSZ))) return Status;
	if (SUCCESS != (Status = g_pDeserializerPool->GetInstance(&m_pDZ))) return Status;
	return SUCCESS;
}

void AxisEngine::UnInitialize()
{
	//nothing to do with m_pWSDD because its destructor deletes its objects
	//nothing to do with m_pHandlerPool because its destructor deletes its objects
}

int AxisEngine::InitializeHandlers(string &sSessionId, AXIS_PROTOCOL_TYPE protocol)
{
	int Status = SUCCESS;  
	//Get Global Handlers from the pool if configured any
	if(SUCCESS != (Status = g_pHandlerPool->GetGlobalRequestFlowHandlerChain(&m_pGReqFChain, sSessionId)))
		return Status;
	if(SUCCESS != (Status = g_pHandlerPool->GetGlobalResponseFlowHandlerChain(&m_pGResFChain, sSessionId)))
		return Status;

	//Get Transport Handlers from the pool if configured any
	if(SUCCESS != (Status = g_pHandlerPool->GetTransportRequestFlowHandlerChain(&m_pTReqFChain, sSessionId, protocol)))
		return Status;
	if(SUCCESS != (Status = g_pHandlerPool->GetTransportResponseFlowHandlerChain(&m_pTResFChain, sSessionId, protocol)))
		return Status;
	return Status;
}
