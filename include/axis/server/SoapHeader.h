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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

// SoapHeader.h: interface for the SoapHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPHEADER_H__9EFB8E6F_A23B_4DC7_AB92_1E572A26B09C__INCLUDED_)
#define AFX_SOAPHEADER_H__9EFB8E6F_A23B_4DC7_AB92_1E572A26B09C__INCLUDED_

#include "HeaderBlock.h"
#include "SoapEnvVersions.h"
#include "../common/ISoapHeader.h"

/**
 *	The Header element information item according to SOAP 1.2 specification.
 *
 *	The Header element information item has:
 *   1) A [local name] of Header. 
 *   2) A [namespace name] of "http://www.w3.org/2003/05/soap-envelope".
 *   3) Zero or more namespace qualified attribute information items in its [attributes] property.
 *   4) Zero or more namespace qualified element information items in its [children] property.
 *
 *	Each child element information item of the SOAP Header is called a SOAP header block.
 *
 *
 *	@brief	The Header element information item according to SOAP 1.2 specification
 */

class SoapHeader : public ISoapHeader
{
private:	
	int serializeNamespaceDecl(SoapSerializer& pSZ);
	//int serializeNamespaceDecl(string&);	
	int serializeAttributes(SoapSerializer& pSZ);
	//int serializeAttributes(string&);
	list<Attribute*> m_attributes;
	list<Attribute*> m_namespaceDecls;
	list<HeaderBlock*> m_headerBlocks;
	//string m_strHeaderSerialized;
public:
	IHeaderBlock* getHeaderBlock();
	int addNamespaceDecl(Attribute* pAttribute);
	int addAttribute(Attribute* pAttribute);
	//string& serialize();
	int serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion);
	//int serialize(string&, SOAP_VERSION eSoapVersion);	
	void addHeaderBlock(HeaderBlock* headerBlock);

	SoapHeader();
	virtual ~SoapHeader();

};

#endif // !defined(AFX_SOAPHEADER_H__9EFB8E6F_A23B_4DC7_AB92_1E572A26B09C__INCLUDED_)
