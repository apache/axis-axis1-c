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
#include "../common/MessageData.h"
#include "../soap/SoapSerializer.h"
#include "../soap/SoapDeSerializer.h"
#include "../soap/SoapFaults.h"
#include "../soap/URIMapping.h"
#include "../common/Debug.h"

#ifdef WIN32
#define WSDDFILEPATH "C:/Apache/Axis/server.wsdd"
#else //For linux
#define WSDDFILEPATH "/usr/local/axiscpp/axis/server.wsdd"
#endif

AxisEngine* AxisEngine::m_pObject = NULL;



AxisEngine::AxisEngine()
{
	//Create Serializer and Deserializer
	m_pSZ = new SoapSerializer();
	m_pDZ = new SoapDeSerializer();  
	m_pWSDD = new WSDDDeployment();
	m_pHandlerPool = new HandlerPool();
	m_pWebService = NULL;
  
  //printf("Done WSDD\n");
}

AxisEngine::~AxisEngine()
{
	delete m_pSZ;
	delete m_pDZ;
	delete m_pWSDD;
	delete m_pHandlerPool;
	//unload xerces DLL
	XMLPlatformUtils::Terminate();
}

AxisEngine* AxisEngine::GetAxisEngine()
{
	if (!m_pObject)
	{
		try
		{
      DEBUG1("AxisEngine::GetAxisEngine()");
			XMLPlatformUtils::Initialize();
			m_pObject = new AxisEngine();
			if (!m_pObject) return NULL;
			if(SUCCESS != m_pObject->Initialize())
			{
				m_pObject->UnInitialize();
				delete m_pObject;
				m_pObject = NULL;
				return NULL;
			}
		}
		catch (...)
		{
			return NULL;
		}	
	}
	return m_pObject;
}

int AxisEngine::Process(soapstream* soap) 
{
  try
  {
    DEBUG1("AxisEngine::Process");
  
	  MessageData* pMsg = NULL;
	  MemBufInputSource* pSoapInput = NULL;
	  WSDDHandlerList* pHandlerList = NULL;
	  WSDDService* pService = NULL;
	  do {
		  //Initialize Serializer and Deserializer objects
		  m_pSZ->init();
		  m_pDZ->Init();
		  //create and populate MessageData
		  pMsg = new MessageData();
		  pMsg->m_Protocol = soap->trtype;
		  pMsg->SetSerializer(m_pSZ);
		  pMsg->SetDeSerializer(m_pDZ);

		  //Adding SoapEnvelop and SoapBody to Serializer
		  SoapEnvelope* pEnv = new SoapEnvelope();
		  pMsg->m_pSZ->setSoapEnvelope(pEnv);
		  pMsg->m_pSZ->setSoapBody(new SoapBody());

		  string service = "Maths";//getheader(soap, SOAPACTIONHEADER);

    
      DEBUG2("string service = Maths :",service.c_str());
     
		  if (service.empty()) 
		  {
			  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SOAPACTIONEMPTY));
			  break; //do .. while(0)
		  }
		  pService = m_pWSDD->GetService(service);
		  if (!pService) {
			  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SERVICENOTFOUND));
			  break; //do .. while(0)
		  }

      pMsg->SetService(pService);
   
		  //Deserialize
		  //---------START XERCES SAX2 SPCIFIC CODE---------//
		  pSoapInput = new MemBufInputSource((const unsigned char*)soap->so.http.ip_soap, soap->so.http.ip_soapcount,"bufferid",false); 
		  if (SUCCESS != m_pDZ->SetStream(pSoapInput)) //this parses the full soap request.
		  {
			  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_SOAPCONTENTERROR));
			  break; //do .. while(0)
		  }
		  //---------END XERCES SAX2 SPCIFIC CODE---------//
		  //check for soap version in the request and decide whether we support it or not
		  //if we do not support send a soapfault with version mismatch.

		  int nSoapVersion = pMsg->m_pDZ->GetVersion();
		  if (nSoapVersion == VERSION_LAST) //version not supported
		  {
			  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_VERSION_MISMATCH));
			  break; //do .. while(0)		
		  }
		  //Set Soap version in the Serializer
		  pMsg->m_pSZ->setSoapVersion((SOAP_VERSION)nSoapVersion);

		  //add namespace URIs of the SoapEnvelope of the response corresponding to the soap version.
		  Attribute* pNS = new Attribute(g_sObjSoapEnvVersionsStruct[nSoapVersion].pchEnvelopePrefix,
			  "xmlns","",g_sObjSoapEnvVersionsStruct[nSoapVersion].pchEnvelopeNamespaceUri);
		  pEnv->addNamespaceDecl(pNS);
		  //add namespace URIs for xsd and xsi
		  pNS = new Attribute("xsd","xmlns","","http://www.w3.org/2001/XMLSchema");
		  pEnv->addNamespaceDecl(pNS);
		  pNS = new Attribute("xsi","xmlns","","http://www.w3.org/2001/XMLSchema-instance");
		  pEnv->addNamespaceDecl(pNS);

		  SoapMethod* pSm = m_pDZ->GetMethod();
		  if (pSm) 
		  {
			  string method = pSm->getMethodName();
      
        DEBUG2("pSm->getMethodName(); :", method.c_str());
          
			  if (!method.empty())
			  {        
				  //this is done here when we use SAX parser
				  //if we use XML pull parser this check is done within the invoke method of the wrapper class
				  if (pService->IsAllowedMethod(method))
				  {          
					  //load actual web service handler
         
					  m_pWebService = m_pHandlerPool->LoadWebService(pService);

                    
					  if (!m_pWebService)
					  {
            
						  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADSRV));
						  //Error couldnot load web service
						  break; //do .. while(0)
					  }
				  }
				  else
				  {
					  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_METHODNOTALLOWED));
					  //method is not an exposed allowed method
					  break; //do .. while(0)
				  }
			  }
			  else
			  {
				  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_NOSOAPMETHOD));
				  //no method to be invoked
				  break; //do .. while(0)
			  }
		  }
		  //create any service specific handlers
    
		  pHandlerList = pService->GetRequestFlowHandlers();

      DEBUG1("after pService->GetRequestFlowHandlers();");
       
		  if (pHandlerList)
		  {
      
			  if(SUCCESS != m_pHandlerPool->LoadServiceRequestFlowHandlers(pHandlerList))
			  {        
				  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADHDL));
				  break; //do .. while(0)
			  }
		  }
    
		  pHandlerList = pService->GetResponseFlowHandlers();
    
		  if (pHandlerList)
		  {
			  if(SUCCESS != m_pHandlerPool->LoadServiceResponseFlowHandlers(pHandlerList))
			  {
				  pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_COULDNOTLOADHDL));
				  break; //do .. while(0)
			  }
		  }
		  Invoke(pMsg); //we generate response in the same way even if this has failed
	  }
	  while(0);
	  //and handlers may add headers to the Serializer.
	  //Invoke all handlers including the webservice
	  //in case of failure coresponding soap fault message will be sent
	  if (pMsg) delete pMsg; //MessageData is no longer needed
	  if (pSoapInput) delete pSoapInput; //this should not be done if we use progressive parsing
	  //set soap version to the serializer.
	  //Serialize
    m_sResponse = "";
	  int iStatus= m_pSZ->getStream(m_sResponse);
	  soap->so.http.op_soap = m_sResponse.c_str();
	  //soap->so.http.op_soap = new char(sResponse.length() + 1); 
	  //strcpy(soap->so.http.op_soap, sResponse.c_str());
  #ifndef _DEBUG //this caused program to crash in debug mode
	  m_pSZ->init();
  #endif 
	//unload webservice handler
  #ifndef WIN32 //this crashes in Win32 at stl map::find(..) function - I cannot find what is wrong.
	  if (m_pWebService) m_pHandlerPool->UnloadWebService(pService);
	  //Unload service specific handlers
	  pHandlerList = pService->GetRequestFlowHandlers();
	  if (pHandlerList)
		  m_pHandlerPool->UnLoadServiceRequestFlowHandlers(pHandlerList);
	  pHandlerList = pService->GetResponseFlowHandlers();
	  if (pHandlerList)
		  m_pHandlerPool->UnLoadServiceResponseFlowHandlers(pHandlerList);
  #endif
	  return SUCCESS;
 }
 catch(exception* e)
 {
   //todo
   /*
    An exception derived from exception which is not handled will be handled here.
    You can call a method in AxisModule which may unload the AxisEngine
    from the webserver and report the error. You can also write this
    in a logfile specific to axis.
   */
   DEBUG1(e->what());   
   delete(e);
 }
 catch(...)
 {
   //todo
   /*
    An unknown exception which is not handled will be handled here.
    You can call a method in AxisModule which may unload the AxisEngine
    from the webserver and report the error. You can also write this
    in a logfile specific to axis.
   */
   DEBUG1("UNKNOWN EXCEPTION");
 }
}

int AxisEngine::Invoke(MessageData* pMsg)
{
	enum AE_LEVEL {AE_START=1, AE_TRH, AE_GLH, AE_SERH, AE_SERV};
	HandlerChain* pChain;
	int ret = FAIL;
	int level = AE_START;
	do
	{
		//invoke transport request handlers
		pChain = m_pHandlerPool->GetTransportRequestFlowHandlerChain(pMsg->m_Protocol);
		if (pChain) {
			if(SUCCESS != pChain->Invoke(pMsg))
			{
				pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_HANDLERFAILED));
				break; //do .. while (0)
			}

		}
    DEBUG1("AFTER pChain = m_pHandlerPool->GetTransportRequestFlowHandlerChain");
		level++; // AE_TRH
		//invoke global request handlers
		pChain = m_pHandlerPool->GetGlobalRequestFlowHandlerChain();
		if (pChain)
		{
			if(SUCCESS != pChain->Invoke(pMsg))
			{
				pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_HANDLERFAILED));
				break; //do .. while (0)
			}		
		}
    DEBUG1("AFTER pChain = m_pHandlerPool->GetGlobalRequestFlowHandlerChain();");
		level++; //AE_GLH
		//invoke service specific request handlers
		pChain = m_pHandlerPool->GetServiceRequestFlowHandlerChain();
		if (pChain)
		{
			if(SUCCESS != pChain->Invoke(pMsg))
			{
				pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_HANDLERFAILED));
				break; //do .. while (0)
			}
      DEBUG1("if(SUCCESS == pChain->Invoke(pMsg))");
		}
    DEBUG1("AFTER pChain = m_pHandlerPool->GetServiceRequestFlowHandlerChain();");
		level++; //AE_SERH
		//call actual web service handler
		if (m_pWebService)
			if (SUCCESS != m_pWebService->Invoke(pMsg))
			{
				pMsg->m_pSZ->setSoapFault(SoapFault::getSoapFault(SF_WEBSERVICEFAILED));
				break;
			}

    DEBUG1("if (m_pWebService)");      
         
		level++; //AE_SERV
	}
	while(0);

	switch (level)
	{
	case AE_SERV: //everything success
		ret = SUCCESS;
		//invoke service specific response handlers
		//no break;
	case AE_SERH: //actual web service handler has failed
		//invoke web service specific response handlers
		pChain = m_pHandlerPool->GetServiceResponseFlowHandlerChain();
		if (pChain)
		{
			pChain->Invoke(pMsg);
      
		}
		//no break;
	case AE_GLH: //web service specific handlers have failed
		//invoke global response handlers
		pChain = m_pHandlerPool->GetGlobalResponseFlowHandlerChain();
		if (pChain)
		{
			pChain->Invoke(pMsg);
		}
		//no break;
	case AE_TRH: //global handlers have failed
		pChain = m_pHandlerPool->GetTransportResponseFlowHandlerChain(pMsg->m_Protocol);
		if (pChain) 
		{
			pChain->Invoke(pMsg);
		}
		//no break;
	case AE_START: ;//transport handlers have failed
	};
  DEBUG1("end axisengine process()");
	return ret;
}

void AxisEngine::OnFault(MessageData* pMsg)
{
	
}

int AxisEngine::Initialize()
{
	string str(WSDDFILEPATH);
	TypeMapping::Initialize();
	URIMapping::Initialize();
	SoapFault::initialize();
  
  DEBUG1("AxisEngine::Initialize()");
      
	if (SUCCESS != m_pWSDD->LoadWSDD(str)) return FAIL;
  
	//Load Global Handlers to the pool if configured any
	WSDDHandlerList* pHandlerList = m_pWSDD->GetGlobalRequestFlowHandlers();
	if (pHandlerList)
		if(SUCCESS != m_pHandlerPool->LoadGlobalRequestFlowHandlers(pHandlerList))
			return FAIL;
	pHandlerList = m_pWSDD->GetGlobalResponseFlowHandlers();
	if (pHandlerList)
		if(SUCCESS != m_pHandlerPool->LoadGlobalResponseFlowHandlers(pHandlerList))
			return FAIL;

	//Load Transport Handlers to the pool if configured any
	WSDDTransport* pTransport = m_pWSDD->GetTransport();
	if (pTransport) {
		//HTTP
		pHandlerList = pTransport->GetRequestFlowHandlers(APTHTTP);
		if (pHandlerList)
			if(SUCCESS != m_pHandlerPool->LoadTransportRequestFlowHandlers(APTHTTP, pHandlerList))
				return FAIL;
		//FTP
		pHandlerList = pTransport->GetRequestFlowHandlers(APTFTP);
		if (pHandlerList)
			if(SUCCESS != m_pHandlerPool->LoadTransportRequestFlowHandlers(APTFTP, pHandlerList))
				return FAIL;
		//SMTP
		pHandlerList = pTransport->GetRequestFlowHandlers(APTSMTP);
		if (pHandlerList)
			if(SUCCESS != m_pHandlerPool->LoadTransportRequestFlowHandlers(APTSMTP, pHandlerList))
				return FAIL;
	}
	return SUCCESS;
}

void AxisEngine::UnInitialize()
{
	//nothing to do with m_pWSDD because its destructor deletes its objects
	//nothing to do with m_pHandlerPool because its destructor deletes its objects
}