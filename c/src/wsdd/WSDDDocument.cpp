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
#include "../common/Debug.h"

#define toString(X) XMLString::transcode(X)
#define toXMLCh(X) XMLString::transcode(X)
#define REL(X) XMLString::release(X);


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
	ch = NULL;
	//xch = NULL;
	xchName = NULL;
	xchValue = NULL;
	xchType = NULL;
	svsch = NULL;
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
    DEBUG1("BEFORE parser->parse(sWSDD.c_str());");
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

	ch = XMLString::transcode(localname);
	xchName = toXMLCh("name");
	xchValue = toXMLCh("value");
	xchType = toXMLCh("type");
	svsch = toString(attrs.getValue(xchName));

	switch(lev0)
	{
		case WSDD_UNKNOWN:

			if(strcmp(ch, "globalConfiguration")==0)
			{  

				lev0=WSDD_GLOBCONF;
			}
			if(strcmp(ch, "service")==0)
			{  

				lev0=WSDD_SERVICE;
			}
			if(strcmp(ch, "transport")==0)
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

			if(strcmp(ch, "requestFlow")==0)
			{
				globReqFlowHanList = new WSDDHandlerList();
				lev1=WSDD_REQFLOW;
			}  

			if(strcmp(ch, "responseFlow")==0)
			{
				globResFlowHanList = new WSDDHandlerList();
				lev1=WSDD_RESFLOW;
			}  

			//xch = toXMLCh("type");
			switch(lev1)
			{
				case WSDD_REQFLOW:
					//cout<<"we are in glob conf>requestflow"<<endl;  

					if(strcmp(ch, "handler")==0)
					{
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(xchType));
						tempHandler->SetLibName(sLibName);
						globReqFlowHanList->push_back(tempHandler);
						tempHandler = NULL;
					}  

				break;
				case WSDD_RESFLOW:
					if(strcmp(ch, "handler")==0)
					{
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(xchType));
						tempHandler->SetLibName(sLibName);
						globResFlowHanList->push_back(tempHandler);
						tempHandler = NULL;
					}  

				break;
			}

			//REL(&xch);
		break;


		case WSDD_SERVICE:      
			if(strcmp(ch, "service")==0)
			{

				tempService = new WSDDService();
				string sSrvName = toString(attrs.getValue(xchName));
				tempService->SetServiceName(sSrvName);
				(*svsMap)[toString(attrs.getValue(xchName))]=tempService;

				cout<<toString(attrs.getValue(toXMLCh("name")))<<endl;
			}  

			//The check for lev1==WSDD_UNKNOWN is necessary because
			//parameter elements can occur inside handler elements
			if(strcmp(ch, "parameter")==0 && (lev1==WSDD_UNKNOWN))
			{
				lev1=WSDD_PARAM;
			} 


      if(strcmp(ch, "requestFlow")==0)
			{
				lev1=WSDD_REQFLOW;
				tempHandlerList = new WSDDHandlerList();
			}  

      if(strcmp(ch, "responseFlow")==0)
			{
				lev1=WSDD_RESFLOW;
				tempHandlerList = new WSDDHandlerList();
			}


      switch(lev1)
			{
				case WSDD_PARAM:
					if(strcmp(svsch, "className")==0)
					{ 

						string sLibName = toString(attrs.getValue(xchValue));
						tempService->SetLibName(sLibName);
						//cout<<toString(attrs.getValue(toXMLCh("value")))<<" The class name"<<endl;
					}
					if(strcmp(svsch, "allowedMethods")==0)
					{
						string sLibName = toString(attrs.getValue(xchValue));
						//cout<<toString(attrs.getValue(toXMLCh("value")))<<" The class name"<<endl;

						char * x = toString(attrs.getValue(xchValue));
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
						REL(&x);
						delete y;

						x=NULL;
						y=NULL;
					}
				break;

				case WSDD_REQFLOW:
					if(strcmp(ch, "handler")==0)
					{
						lev2=WSDD_HANDLER;
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(xchType));
						tempHandler->SetLibName(sLibName);
						tempHandlerList->push_back(tempHandler);
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(ch, "parameter")==0)
							{
								tempHandler->SetOption(toString(attrs.getValue(xchName)),
														toString(attrs.getValue(xchValue)));

                  DEBUG1("After tempHandler->SetOption");

							}
						break;
					}
				break;

				case WSDD_RESFLOW:
					if(strcmp(ch, "handler")==0)
					{
						lev2=WSDD_HANDLER;
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(xchType));
						tempHandler->SetLibName(sLibName);
						tempHandlerList->push_back(tempHandler);
						//tempHandler = NULL;
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(ch, "parameter")==0)
							{
								tempHandler->SetOption(toString(attrs.getValue(xchName)),
														toString(attrs.getValue(xchValue)));
							}
						break;
					}
				break;
			}

		break;  

		case WSDD_TRANSPORT:
			if(strcmp(ch, "transport")==0)
			{
				//tempHandlerList = new WSDDHandlerList();
				if(strcmp(svsch, "http")==0)
				{
					protocol =APTHTTP;
				}
				if(strcmp(svsch, "local")==0)
				{
					protocol =APTFTP;
				}
				if(protocol==APTOTHER)
				{
					break;
				}

			}
			if(strcmp(ch, "requestFlow")==0)
			{
				lev1=WSDD_REQFLOW;
				tempHandlerList = new WSDDHandlerList();
			}
			if(strcmp(ch, "responseFlow")==0)
			{
				lev1=WSDD_RESFLOW;
				tempHandlerList = new WSDDHandlerList();
			}
			switch(lev1)
			{
				case WSDD_REQFLOW:
					//cout<<"we are in glob conf>requestflow"<<endl;
					if(strcmp(ch, "handler")==0)
					{
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(xchType));
						tempHandler->SetLibName(sLibName);
						tempHandlerList->push_back(tempHandler);
						tempHandler = NULL;
					}
				break;

				case WSDD_RESFLOW:
					//cout<<"we are in glob conf>requestflow"<<endl;
					if(strcmp(ch, "handler")==0)
					{
						tempHandler = new WSDDHandler();
						string sLibName = toString(attrs.getValue(xchType));
						tempHandler->SetLibName(sLibName);
						tempHandlerList->push_back(tempHandler);
						tempHandler = NULL;
					}
				break;

			}

		break;
	}
	REL(&ch);
	REL(&xchName);
	REL(&xchValue);
	REL(&xchType);
	REL(&svsch);

}

void  WSDDDocument::endElement (const XMLCh *const uri,
				  const XMLCh *const localname,
				  const XMLCh *const qname)
{
	ch = XMLString::transcode(localname);
	switch (lev0)
	{  

		case WSDD_GLOBCONF:
			if(strcmp(ch, "globalConfiguration")==0)
			{
				lev0=WSDD_UNKNOWN;
			}
			switch(lev1)
			{
				case WSDD_REQFLOW:
					if(strcmp(ch, "requestFlow")==0)
					{
						lev1=WSDD_UNKNOWN;
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(ch, "handler")==0)
							{
								lev2=WSDD_UNKNOWN;
							}
						break;
					}

				break;
				case WSDD_RESFLOW:
					if(strcmp(ch, "responseFlow")==0)
					{
						lev1=WSDD_UNKNOWN;
					}
					switch(lev2)
					{
						case WSDD_HANDLER:
							if(strcmp(ch, "handler")==0)
							{
								lev2=WSDD_UNKNOWN;
							}
						break;
					}
				break;
			}
		break;

		case WSDD_REQFLOW:
			if(strcmp(ch, "requestFlow")==0)
			{
				lev0=WSDD_UNKNOWN;
			}
		break; 

		case WSDD_SERVICE:
			if(strcmp(ch, "service")==0)
			{
				lev0=WSDD_UNKNOWN;
				tempService = NULL;
			}
			switch(lev1)
			{
				case WSDD_PARAM:
					if(strcmp(ch, "parameter")==0)
					{
						lev1=WSDD_UNKNOWN;
					}
				break;
				case WSDD_REQFLOW:
					if(strcmp(ch, "requestFlow")==0)
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
							if(strcmp(ch, "handler")==0)
							{
								lev2=WSDD_UNKNOWN;
								tempHandler = NULL;
							}

						break;
					}
				break;
				case WSDD_RESFLOW:
					if(strcmp(ch, "responseFlow")==0)
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
							if(strcmp(ch, "handler")==0)
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
			if(strcmp(ch, "transport")==0)
			{
				protocol=APTOTHER;
				lev0=WSDD_UNKNOWN;
			}

			switch(lev1)
			{
				case WSDD_REQFLOW:
					if(strcmp(ch, "requestFlow")==0)
					{
						tempTr->SetRequestFlowHandlers(protocol, tempHandlerList);
						tempHandlerList = NULL;
						lev1=WSDD_UNKNOWN;
					}
				break;

				case WSDD_RESFLOW:

					if(strcmp(ch, "responseFlow")==0)
					{
						tempTr->SetResponseFlowHandlers(protocol, tempHandlerList);
						tempHandlerList = NULL;
						lev1=WSDD_UNKNOWN;
					}

				break;
			}
		break;
	}
	REL(&ch);

}

void  WSDDDocument::characters (const XMLCh *const chars,
				  const unsigned int length)
{
	//cout<<"==="<<XMLString::transcode(chars)<<"==="<<endl;
}