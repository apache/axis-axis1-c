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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *
 */

// SoapBody.h: interface for the SoapBody class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPBODY_H__D1A60F04_287F_4688_A8F0_10BE0EA25775__INCLUDED_)
#define AFX_SOAPBODY_H__D1A60F04_287F_4688_A8F0_10BE0EA25775__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SoapMethod.h"
#include "SoapFault.h"
#include "SoapEnvVersions.h"

class Attribute;

/**
 *	The SOAP Body of a SOAP Envelope according to SOAP 1.2 specification.
 *
 *	A SOAP body provides a mechanism for transmitting information to an ultimate SOAP receiver.
 *  The Body element information item has:
 *		- A [local name] of Body .
 *		- A [namespace name] of "http://www.w3.org/2003/05/soap-envelope".
 *		- Zero or more namespace qualified attribute information items in its [attributes] property.
 *		- Zero or more namespace qualified element information items in its [children] property.
 *  
 *  The Body element information item MAY have any number of character information item children whose 
 *  character code is amongst the white space characters as defined by XML 1.0 [XML 1.0]. These are 
 *  considered significant.
 *
 *  SOAP Body child Element:
 *  All child element information items of the SOAP Body element information item:
 *		- SHOULD have a [namespace name] property which has a value, that is the name of the element 
 *		  SHOULD be namespace qualified.
 *		- MAY have any number of character information item children. Child character information 
 *		  items whose character code is amongst the white space characters as defined by XML 1.0 [XML 1.0] 
 *		  are considered significant.
 *		- MAY have any number of element information item children. Such element information items MAY be 
 *		  namespace qualified.
 *		- MAY have zero or more attribute information items in its [attributes] property. Among these MAY 
 *		  be the following, which has special significance for SOAP processing:
 *			- encodingStyle attribute information item
 *  SOAP defines one particular direct child of the SOAP body, the SOAP fault, which is used for reporting 
 *  errors 
 *	
 *	@brief	The SOAP Body of a SOAP Envelope according to SOAP 1.2 specification.
 */

class SoapBody  
{
friend class SoapSerializer;

private:
	int serializeAttributes(string& sSerialized);
	list<Attribute*> m_attributes;
	SoapMethod *m_pSoapMethod;
	SoapFault *m_pSoapFault;
	//string m_strBodySerialized;

public:
	void addAttribute(Attribute* attr);
	//string& serialize();
	int serialize(string&, SOAP_VERSION eSoapVersion);
	void setSoapFault(SoapFault* ptrSoapFault);
	void setSoapMethod(SoapMethod* ptrSoapMethod);
	SoapBody();
	virtual ~SoapBody();

};

#endif // !defined(AFX_SOAPBODY_H__D1A60F04_287F_4688_A8F0_10BE0EA25775__INCLUDED_)
