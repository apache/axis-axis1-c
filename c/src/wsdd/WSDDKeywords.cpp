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
 */

#include "WSDDKeywords.h"
#include "../common/AxisUtils.h"

#define __TRC(X) AxisUtils::ToAxisXMLCh(X)

volatile bool WSDDKeywords::m_bInit = false;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define AX_DELETE(X) delete const_cast<AxisXMLCh*>(X)

const AxisXMLCh* kw_depl;
const AxisXMLCh* kw_undepl;
const AxisXMLCh* kw_srv;
const AxisXMLCh* kw_glconf;
const AxisXMLCh* kw_param; 
const AxisXMLCh* kw_hdl;
const AxisXMLCh* kw_chain;
const AxisXMLCh* kw_ns;
const AxisXMLCh* kw_prv;
const AxisXMLCh* kw_cn; //must be changed to libname or so
const AxisXMLCh* kw_am;
const AxisXMLCh* kw_ar;
const AxisXMLCh* kw_rqf;
const AxisXMLCh* kw_rsf;
const AxisXMLCh* kw_tr;
const AxisXMLCh* kw_name;
const AxisXMLCh* kw_value;
const AxisXMLCh* kw_type; //what about this ? change to libname ?
const AxisXMLCh* kw_scope;
const AxisXMLCh* kw_http;
const AxisXMLCh* kw_smtp;
const AxisXMLCh* kw_desc;

WSDDKeywords::WSDDKeywords()
{
	Initialize();
}

WSDDKeywords::~WSDDKeywords()
{
	UnInitialize();
}

void WSDDKeywords::Initialize()
{
	if (!m_bInit)
	{
		kw_depl = __TRC("deployment");
		kw_undepl = __TRC("undeployment");
		kw_srv = __TRC("service");
		kw_glconf = __TRC("globalConfiguration");
		kw_param = __TRC("parameter"); 
		kw_hdl = __TRC("handler");
		kw_chain = __TRC("chain");
		kw_ns = __TRC("namespace");
		kw_prv = __TRC("provider");
		kw_cn = __TRC("className"); //must be changed to libname or so
		kw_am = __TRC("allowedMethods");
		kw_ar = __TRC("allowedRoles");
		kw_rqf = __TRC("requestFlow");
		kw_rsf = __TRC("responseFlow");
		kw_tr = __TRC("transport");
		kw_name = __TRC("name");
		kw_value = __TRC("value");
		kw_type = __TRC("type"); //what about this ? change to libname ?
		kw_scope = __TRC("scope");
		kw_http = __TRC("http");
		kw_smtp = __TRC("smtp");
		kw_desc = __TRC("description");
		m_bInit = true;
	}
}

void WSDDKeywords::UnInitialize()
{
	if (m_bInit)
	{
		AX_DELETE(kw_smtp);
		m_bInit = false;
	}
}
