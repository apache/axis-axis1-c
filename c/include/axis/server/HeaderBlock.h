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

// HeaderBlock.h: interface for the HeaderBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEADERBLOCK_H__F21C94A8_40D1_4CFC_9240_DD617494CF40__INCLUDED_)
#define AFX_HEADERBLOCK_H__F21C94A8_40D1_4CFC_9240_DD617494CF40__INCLUDED_

#include "Attribute.h"
#include <string>
#include <list>

using namespace std;

class BasicNode;
#include "../common/IHeaderBlock.h"

/**
 *	The Header block of a SOAP Header according to SOAP 1.2 specification.
 *
 *	Each child element information item of the SOAP Header is called a SOAP header block.
 *  Each SOAP header block element information item:
 *		- MUST have a [namespace name] property which has a value, that is the name of the 
 *		  element MUST be namespace qualified.
 *		- MAY have any number of character information item children. Child character 
 *		  information items whose character code is amongst the white space characters 
 *		  as defined by XML 1.0 [XML 1.0] are considered significant.
 *		- MAY have any number of element information item children. Such element information 
 *		  items MAY be namespace qualified.
 *		- MAY have zero or more attribute information items in its [attributes] property. Among 
 *		  these MAY be any or all of the following, which have special significance for SOAP 
 *		  processing:
 *			- encodingStyle attribute information item 
 *			- role attribute information item 
 *			- mustUnderstand attribute information item     
 *			- relay attribute information item 
 *
 *	
 *	@brief	The Header block of a SOAP Header according to SOAP 1.2 specification.
 */

class HeaderBlock : public IHeaderBlock
{

private:	
	int serializeNamespaceDecl(SoapSerializer& pSZ);
	int serializeChildren(SoapSerializer& pSZ);
	//int serializeChildren(string& sSerialized);
	list<BasicNode*> m_children;
	bool isSerializable();		
	int attrSerialize(SoapSerializer& pSZ);
	//int attrSerialize(string&);
	AxisString m_localname;
	AxisString m_prefix;
	AxisString m_uri;
	list<Attribute*> m_attributes;
	list<Attribute*> m_namespaceDecls;
	AxisString m_value;
	//string m_strSerialized;

public:
	BasicNode* createChild(NODE_TYPE eNODE_TYPE);
	BasicNode* getFirstChild();
	int addNamespaceDecl(Attribute *pAttribute);
	int addChild(BasicNode* pBasicNode);

	int serialize(SoapSerializer& pSZ);
	//int serialize(string&);
	void setValue(const AxisChar* value);
	void addAttribute(Attribute* attr);
	void setUri(const AxisChar* uri);
	void setPrefix(const AxisChar* prefix);
	void setLocalName(const AxisChar* localname);
	HeaderBlock();
	virtual ~HeaderBlock();

};

#endif // !defined(AFX_HEADERBLOCK_H__F21C94A8_40D1_4CFC_9240_DD617494CF40__INCLUDED_)
