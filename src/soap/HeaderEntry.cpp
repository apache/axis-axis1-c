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

// HeaderEntry.cpp: implementation of the HeaderEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "HeaderEntry.h"
#include "../common/GDefine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HeaderEntry::HeaderEntry()
{

}

HeaderEntry::~HeaderEntry()
{
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		

		delete (*itCurrAttribute);
		itCurrAttribute++;		
	}
	
	m_attributes.clear();
}

void HeaderEntry::setLocalName(const string &localname)
{
	m_localname= localname;
}

void HeaderEntry::setPrefix(const string &prefix)
{
	m_prefix= prefix;
}

void HeaderEntry::setUri(const string &uri)
{
	m_uri= uri;
}

void HeaderEntry::addAttribute(Attribute* attr)
{
	m_attributes.push_back(attr);
}

void HeaderEntry::setValue(const string &value)
{
	m_value= value;
}

int HeaderEntry::serialize(string& sSerialized)
{
	/*
	 *In the code we don't look whether the m_prefix is available or
	 *	not. Instead directly insert it. The reason is that the SOAP
	 *  1.1 spec says that "All immediate child elements of the SOAP 
	 *  Header element MUST be namespace-qualified".
	 */

	int iStatus= SUCCESS;

	do {
		if(isSerializable()) {

			sSerialized= sSerialized + "<" + m_prefix + ":" + m_localname +
								" xmlns:"+ m_prefix +"=\""+ m_uri+ "\"";

			iStatus= attrSerialize(sSerialized);
			if(iStatus==FAIL) {
				break;
			}

			sSerialized= sSerialized + ">" + m_value + "</"+ m_prefix + 
					":"+ m_localname+ ">";
			
		} else {
			iStatus= FAIL;
		}
	} while(0);

	return iStatus;
}

/*string& HeaderEntry::serialize()
{*/
	/*
	 *In the code we don't look whether the m_prefix is available or
	 *	not. Instead directly insert it. The reason is that the SOAP
	 *  1.1 spec says that "All immediate child elements of the SOAP 
	 *  Header element MUST be namespace-qualified".
	 */


/*	m_strSerialized= "";

	if(isSerializable()) {
		string strAttrSerialized= attrSerialize();

		m_strSerialized= "<" + m_prefix + ":" + m_localname + " xmlns:"+ m_prefix +
							"=\""+ m_uri+ "\"";

		if(!strAttrSerialized.empty()) {	//NOTE: check whether the list is empty
			m_strSerialized= m_strSerialized+ " "+ strAttrSerialized;		
		}

		m_strSerialized= m_strSerialized + ">" + m_value + "</"+ m_prefix + 
				":"+ m_localname+ ">";
	}

	return m_strSerialized;
}*/

int HeaderEntry::attrSerialize(string& sSerialized)
{
	int iStatus= SUCCESS;

	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		

		iStatus= (*itCurrAttribute)->serialize(sSerialized);
		if(iStatus==FAIL) {
			break;
		}
		itCurrAttribute++;		
	}	

	return iStatus;
}

/*string HeaderEntry::attrSerialize()
{
	string strAttrSerialized;

	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		

		strAttrSerialized= strAttrSerialized+ (*itCurrAttribute)->serialize();
		itCurrAttribute++;

		if(itCurrAttribute != m_attributes.end()) {
			strAttrSerialized= strAttrSerialized+ " ";
		}
	}	

	return strAttrSerialized;
}*/

bool HeaderEntry::isSerializable()
{
	//bool blnStatus= true;\

	//return blnStatus;

	bool bStatus= true;	

	if(m_localname.length() == 0) {
		bStatus= false;
	} else {
		if(m_prefix.length() == 0) {
			if(m_uri.length() != 0) {
				bStatus= false;
			}
		} else {
			if(m_uri.length() == 0) {
				bStatus= false;
			}
		}
	}

	return bStatus;
}