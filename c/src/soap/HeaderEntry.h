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

// HeaderEntry.h: interface for the HeaderEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEADERENTRY_H__ACD7DFAC_12D0_4059_8C7F_02D62533CC17__INCLUDED_)
#define AFX_HEADERENTRY_H__ACD7DFAC_12D0_4059_8C7F_02D62533CC17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Attribute.h"
#include <string>
#include <list>

using namespace std;

/**
 *	The header entry of a SOAP Header according to SOAP 1.1 specification.
 *
 *	All immediate child elements of the Header element are called header
 *  entries.
 *  The encoding rules for header entries are as follows: 
 *   1) A header entry is identified by its fully qualified element name, 
 *      which consists of the namespace URI and the local name. All 
 *      immediate child elements of the SOAP Header element MUST be 
 *      namespace-qualified. 
 *   2) The SOAP encodingStyle attribute MAY be used to indicate the 
 *      encoding style used for the header entries. 
 *   3) The SOAP mustUnderstand attribute and SOAP actor attribute MAY 
 *      be used to indicate how to process the entry and by whom. 
 *
 *	
 *	@brief	The header entry of a SOAP Header according to SOAP 1.1 specification
 */

class HeaderEntry  
{

private:
	bool isSerializable();
	//string attrSerialize();
	int attrSerialize(string&);
	string m_localname;
	string m_prefix;
	string m_uri;
	list<Attribute*> m_attributes;
	string m_value;
	//string m_strSerialized;

public:
	//string& serialize();
	int serialize(string&);
	void setValue(const string &value);
	void addAttribute(Attribute* attr);
	void setUri(const string &uri);
	void setPrefix(const string &prefix);
	void setLocalName(const string &localname);
	HeaderEntry();
	virtual ~HeaderEntry();

};

#endif // !defined(AFX_HEADERENTRY_H__ACD7DFAC_12D0_4059_8C7F_02D62533CC17__INCLUDED_)
