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
 * @author Sanjaya Singharage
 *
 */

#include "WSDDDocument.h"
#include <iostream>
#include <string>

#define toString(X) XMLString::transcode(X)
#define toXMLCh(X) XMLString::transcode(X)


WSDDDocument::WSDDDocument()
{
	lev0 =WSDD_UNKNOWN;
	lev1 =WSDD_UNKNOWN;
	lev2 =WSDD_UNKNOWN;
	tempHandlerList=NULL;
	globReqFlowHanList=NULL;
	globResFlowHanList=NULL;
	svsMap = new WSDDServiceMap();
	tempTr = new WSDDTransport();
	protocol = APTOTHER;
}

WSDDDocument::~WSDDDocument()
{

}

int WSDDDocument::GetDeployment(string& sWSDD, WSDDDeployment * dep)
{
	if (SUCCESS != ParseDocument(sWSDD)) return FAIL;
	dep->SetGlobalRequestFlowHandlers(globReqFlowHanList);
	dep->SetGlobalResponseFlowHandlers(globResFlowHanList);
	dep->SetServices(svsMap);
	dep->SetTransport(tempTr);

	return SUCCESS;
}

int WSDDDocument::ParseDocument(string& sWSDD)
{
	try 
	{
		SAX2XMLReader * parser = XMLReaderFactory::createXMLReader();
		parser->setContentHandler(this);
		parser->setErrorHandler(this);
		parser->parse(sWSDD.c_str());
	}
	catch (...)
	{
		return FAIL;
	}
	return SUCCESS;
}


void WSDDDocument::startElement(const XMLCh *const uri, 
							const XMLCh *const localname, 
							const XMLCh *const qname, 
							const Attributes &attrs)
{
	switch(lev0)
	{
		case WSDD_UNKNOWN:
			if(strcmp(XMLString::transcode(localname), "globalConfiguration")==0)
			{
				lev0=WSDD_GLOBCONF;
			}
			if(strcmp(XMLString::transcode(localname), "service")==0)
			{
				lev0=WSDD_SERVICE;
			}
			if(strcmp(XMLString::transcode(localname), "transport")==0)
			{
				lev0=WSDD_TRANSPORT;
			}

			if(lev0==WSDD_UNKNOWN)
			{
				break;
			}
		break;
	}

	
	switch(lev0)
	{
		case WSDD_GLOBCONF:
			//cout<<"we are in glob conf"<<endl;
			if(strcmp(XMLString::transcode(localname), "requestFlow")==0)
			{
				globReqFlowHanList = new WSDDHandlerList();
				lev1=WSDD_REQFLOW;
			}
			if(strcmp(XMLString::transcode(localname), "responseFlow")==0)
			{
				globResFlowHanList = new WSDDHandlerList();
				lev1=WSDD_RESFLOW;
			}
			switch(lev1)
			{
				case WSDD_REQFLOW:
					//cout<<"we are in glob conf>requestflow"<<endl;
					if(strcmp(XMLString::transcode(localname), "handler")==0)
					{
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(toXMLCh("type")));
						tempHandler->SetLibName(sLibName);
						globReqFlowHanList->push_back(tempHandler);
						tempHandler = NULL;
					}
				break;
				case WSDD_RESFLOW:
					if(strcmp(XMLString::transcode(localname), "handler")==0)
					{
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(toXMLCh("type")));
						tempHandler->SetLibName(sLibName);
						globResFlowHanList->push_back(tempHandler);
						tempHandler = NULL;
					}

				break;
			
			}
		break;


		case WSDD_SERVICE:
			if(strcmp(XMLString::transcode(localname), "service")==0)
			{
				tempService = new WSDDService();
				string sSrvName = toString(attrs.getValue(toXMLCh("name")));
				tempService->SetServiceName(sSrvName);
				(*svsMap)[toString(attrs.getValue(toXMLCh("name")))]=tempService;

				cout<<toString(attrs.getValue(toXMLCh("name")))<<endl;
			}
			//The check for lev1==WSDD_UNKNOWN is necessary because
			//parameter elements can occur inside handler elements
			if(strcmp(XMLString::transcode(localname), "parameter")==0 && (lev1==WSDD_UNKNOWN))
			{
				lev1=WSDD_PARAM;
			}
			if(strcmp(XMLString::transcode(localname), "requestFlow")==0)
			{
				lev1=WSDD_REQFLOW;
				tempHandlerList = new WSDDHandlerList();
			}
			if(strcmp(XMLString::transcode(localname), "responseFlow")==0)
			{
				lev1=WSDD_RESFLOW;
				tempHandlerList = new WSDDHandlerList();
			}
			switch(lev1)
			{
				case WSDD_PARAM:
					if(strcmp(toString(attrs.getValue(toXMLCh("name"))), "className")==0)
					{
						string sLibName = toString(attrs.getValue(toXMLCh("value")));
						tempService->SetLibName(sLibName);
						//cout<<toString(attrs.getValue(toXMLCh("value")))<<" The class name"<<endl;
					}
					if(strcmp(toString(attrs.getValue(toXMLCh("name"))), "allowedMethods")==0)
					{
						string sLibName = toString(attrs.getValue(toXMLCh("value")));
						//cout<<toString(attrs.getValue(toXMLCh("value")))<<" The class name"<<endl;
						
						char * x = toString(attrs.getValue(toXMLCh("value")));
						char * y;
						if(x)
						{
							y=strtok(x," ");
							while (y!=NULL)
							{
								string sY = y;
								tempService->SetAllowedMethod(sY);
								y=strtok(NULL," ");
							} 
						}
						XMLString::release(&x);
						delete y;
						
						x=NULL;
						y=NULL;
					}
				break;

				case WSDD_REQFLOW:
					if(strcmp(XMLString::transcode(localname), "handler")==0)
					{
						lev2=WSDD_HANDLER;
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(toXMLCh("type")));
						tempHandler->SetLibName(sLibName);
						tempHandlerList->push_back(tempHandler);
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(XMLString::transcode(localname), "parameter")==0)
							{
								tempHandler->SetOption(toString(attrs.getValue(toXMLCh("name"))),
														toString(attrs.getValue(toXMLCh("value"))));
							}
						break;
					}
				break;

				case WSDD_RESFLOW:
					if(strcmp(XMLString::transcode(localname), "handler")==0)
					{
						lev2=WSDD_HANDLER;
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(toXMLCh("type")));
						tempHandler->SetLibName(sLibName);
						tempHandlerList->push_back(tempHandler);
						//tempHandler = NULL;					
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(XMLString::transcode(localname), "parameter")==0)
							{
								tempHandler->SetOption(toString(attrs.getValue(toXMLCh("name"))),
														toString(attrs.getValue(toXMLCh("value"))));
							}
						break;
					}
				break;
			}
		break;

		case WSDD_TRANSPORT:
			if(strcmp(XMLString::transcode(localname), "transport")==0)
			{
				tempHandlerList = new WSDDHandlerList();
				if(strcmp(toString(attrs.getValue(toXMLCh("name"))), "http")==0)
				{
					protocol =APTHTTP;
				}
				if(strcmp(toString(attrs.getValue(toXMLCh("name"))), "local")==0)
				{
					protocol =APTFTP;
				}
				if(protocol==APTOTHER)
				{
					break;
				}

			}
			if(strcmp(XMLString::transcode(localname), "requestFlow")==0)
			{
				lev1=WSDD_REQFLOW;
			}

			switch(lev1)
			{
				case WSDD_REQFLOW:
					//cout<<"we are in glob conf>requestflow"<<endl;
					if(strcmp(XMLString::transcode(localname), "handler")==0)
					{
						lev2=WSDD_HANDLER;
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(toXMLCh("type")));
						tempHandler->SetLibName(sLibName);
						tempHandlerList->push_back(tempHandler);

					}
					switch(lev2)
					{
						case WSDD_HANDLER:
						break;
					}
				break;
			
			}

		break;
	}

}	

void  WSDDDocument::endElement (const XMLCh *const uri, 
				  const XMLCh *const localname, 
				  const XMLCh *const qname)
{
	switch (lev0)
	{
		case WSDD_GLOBCONF:
			if(strcmp(XMLString::transcode(localname), "globalConfiguration")==0)
			{
				lev0=WSDD_UNKNOWN;
			}
			switch(lev1)
			{
				case WSDD_REQFLOW:
					if(strcmp(XMLString::transcode(localname), "requestFlow")==0)
					{
						lev1=WSDD_UNKNOWN;
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(toString(localname), "handler")==0)
							{
								lev2=WSDD_UNKNOWN;
							}
						break;
					}
					
				break;
				case WSDD_RESFLOW:
					if(strcmp(XMLString::transcode(localname), "responseFlow")==0)
					{
						lev1=WSDD_UNKNOWN;
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(toString(localname), "handler")==0)
							{
								lev2=WSDD_UNKNOWN;
							}
						break;
					}
				break;
			}
		break;

		case WSDD_REQFLOW:
			if(strcmp(XMLString::transcode(localname), "requestFlow")==0)
			{
				lev0=WSDD_UNKNOWN;
			}
		break;

		case WSDD_SERVICE:
			if(strcmp(XMLString::transcode(localname), "service")==0)
			{
				lev0=WSDD_UNKNOWN;
				tempService = NULL;
			}
			switch(lev1)
			{
				case WSDD_PARAM:
					if(strcmp(XMLString::transcode(localname), "parameter")==0)
					{
						lev1=WSDD_UNKNOWN;
					}
				break;
				case WSDD_REQFLOW:
					if(strcmp(XMLString::transcode(localname), "requestFlow")==0)
					{
						lev1=WSDD_UNKNOWN;
						if(!tempHandlerList->empty())
						{
							tempService->SetRequestFlowHandlers(tempHandlerList);
						}
						else
						{
							delete tempHandlerList;
							tempService->SetRequestFlowHandlers(NULL);
						}
						tempHandlerList = NULL;
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(XMLString::transcode(localname), "handler")==0)
							{
								lev2=WSDD_UNKNOWN;
								tempHandler = NULL;
							}
							
						break;
					}
				break;
				case WSDD_RESFLOW:
					if(strcmp(XMLString::transcode(localname), "responseFlow")==0)
					{
						lev1=WSDD_UNKNOWN;
						if(!tempHandlerList->empty())
						{
							tempService->SetResponseFlowHandlers(tempHandlerList);
						}
						else
						{
							delete tempHandlerList;
							tempService->SetResponseFlowHandlers(NULL);
						}
						tempHandlerList= NULL;
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(XMLString::transcode(localname), "handler")==0)
							{
								lev2=WSDD_UNKNOWN;
								tempHandler = NULL;
							}
							
						break;
					}
				break;
			}
		break;

		case WSDD_TRANSPORT:
			if(strcmp(XMLString::transcode(localname), "transport")==0)
			{
				protocol=APTOTHER;
				lev0=WSDD_UNKNOWN;
			}

			switch(lev1)
			{
				case WSDD_REQFLOW:
					if(strcmp(XMLString::transcode(localname), "requestFlow")==0)
					{
						tempTr->SetRequestFlowHandlers(protocol, tempHandlerList);
						tempHandlerList = NULL;
						lev1=WSDD_UNKNOWN;
					}
				break;
			}
		break;
	}
}

void  WSDDDocument::characters (const XMLCh *const chars, 
				  const unsigned int length)
{
	//cout<<"==="<<XMLString::transcode(chars)<<"==="<<endl;
}