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
 * @author sanjaya
 * @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */

#pragma warning(disable : 4786)

#if !defined(__WSDDDOCUMENTS_H_INCLUDED__)
#define __WSDDDOCUMENTS_H_INCLUDED__

#include "WSDDDeployment.h"
#include "WSDDService.h"
#include "../common/GDefine.h"

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <string>
#include <map>

using namespace std;

enum WSDDLevels {WSDD_UNKNOWN=1, WSDD_DEPLOYMENT, WSDD_UNDEPLOYMENT, WSDD_GLOBCONF, WSDD_SERVICE, WSDD_HANDLER, WSDD_CHAIN, WSDD_TRANSPORT, WSDD_REQFLOW, WSDD_RESFLOW, WSDD_PARAM };

XERCES_CPP_NAMESPACE_USE;

//wsdd file related defines
#define METHODNAME_SEPARATOR " "
#define ROLENAME_SEPARATOR ","

//keywords used in the wsdd file
const char kw_depl[] = "deployment";
const char kw_srv[] = "service";
const char kw_glconf[] = "globalConfiguration";
const char kw_param[] = "parameter"; 
const char kw_hdl[] = "handler";
const char kw_chain[] = "chain";
const char kw_ns[] = "namespace";
const char kw_prv[] = "provider";
const char kw_cn[] = "className"; //must be changed to libname or so
const char kw_am[] = "allowedMethods";
const char kw_ar[] = "allowedRoles";
const char kw_rqf[] = "requestFlow";
const char kw_rsf[] = "responseFlow";
const char kw_tr[] = "transport";
const char kw_name[] = "name";
const char kw_value[] = "value";
const char kw_type[] = "type"; //what about this ? change to libname ?
const char kw_scope[] = "scope";
const char kw_http[] = "http";
const char kw_smtp[] = "smtp";

class WSDDDocument:public DefaultHandler
{
private:
	int m_nLibId;
	map<string, int>* m_pLibNameIdMap;
	WSDDDeployment* m_pDeployment; 
	WSDDLevels m_lev0;
	WSDDLevels m_lev1; //gets values WSDD_REQFLOW or WSDD_RESFLOW
	WSDDLevels m_lev2; //gets values WSDD_HANDLER or WSDD_CHAIN
	map<string, string> m_NsStack;
	WSDDService* m_pService; //Place holder for currently created Service object
	WSDDHandler* m_pHandler; //Place holder for currently created Handler object
	//map<string, string> m_GlobalConfParams;
	AXIS_PROTOCOL_TYPE m_CurTrType; //Current transport type of transport handlers

private:
	void ProcessAttributes(WSDDLevels ElementType, const Attributes &attrs);
	void GetParameters(WSDDLevels ElementType, const Attributes &attrs);
	void AddAllowedRolesToService(string& value);
	void AddAllowedMethodsToService(string& value);

public:
	WSDDDocument();
	~WSDDDocument();
	int ParseDocument(const string& sWSDD);
	int GetDeployment(const string& sWSDD, WSDDDeployment* pDeployment);
	void startElement(const XMLCh *const uri, const XMLCh *const localname,	const XMLCh *const qname, const Attributes &attrs);
	void characters (const XMLCh *const chars, const unsigned int length);
	void endElement (const XMLCh *const uri, const XMLCh *const localname,	const XMLCh *const qname);
	void startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri);
	void endPrefixMapping(const XMLCh* const prefix);
};

#endif //__WSDDDOCUMENTS_H_INCLUDED__