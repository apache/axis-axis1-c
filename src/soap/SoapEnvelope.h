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
 * @author Roshan
 *
 */

// SoapEnvelope.h: interface for the SoapEnvelope class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPENVELOPE_H__285E1A2E_AC87_4F69_BAF2_4D556F43EC7C__INCLUDED_)
#define AFX_SOAPENVELOPE_H__285E1A2E_AC87_4F69_BAF2_4D556F43EC7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SoapHeader.h"
#include "SoapBody.h"
#include "SoapEnvVersions.h"

class SoapEnvelope  
{
friend class SoapSerializer;

private:
	int serializeNamespaceDecl(string&);
	//string serializeNamespaceDecl();
	int serializeAttributes(string&);
	//string serializeAttributes();
	SoapHeader *m_pSoapHeader;
	SoapBody *m_pSoapBody;
	//string m_strEnvelopSerialized;
	list<Attribute*> m_attributes;
	list<Attribute*> m_namespaceDecls;
	string m_sPrefix;	

public:	
	int setPrefix(const string& prefix);
	int addNamespaceDecl(Attribute* pAttribute);
	int addAttribute(Attribute* pAttribute);
	int serialize(string&, SOAP_VERSION iSoapVersion);
	//string& serialize()
	void setSoapBody(SoapBody* soapBody);
	void setSoapHeader(SoapHeader* soapHeader);
	SoapEnvelope();
	virtual ~SoapEnvelope();
};

#endif // !defined(AFX_SOAPENVELOPE_H__285E1A2E_AC87_4F69_BAF2_4D556F43EC7C__INCLUDED_)
