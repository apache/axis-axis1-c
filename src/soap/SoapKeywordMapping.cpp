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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
// SoapKeywordMapping.cpp: implementation of the SoapKeywordMapping class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/soap/SoapKeywordMapping.h>
#include <axis/soap/Attribute.h>
#include <axis/common/AxisUtils.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
map<int, SoapKeywordStruct> SoapKeywordMapping::m_Map;
volatile bool SoapKeywordMapping::m_bInit = false;

#define __TRC(X) AxisUtils::ToAxisXMLCh(X)

SoapKeywordMapping::SoapKeywordMapping()
{

}

SoapKeywordMapping::~SoapKeywordMapping()
{

}

void SoapKeywordMapping::Initialize()
{
	if (!m_bInit)
	{
		for (int sv = SOAP_VER_1_1; sv < VERSION_LAST; sv++)
		{
			m_Map[sv].pchNamespaceUri = __TRC(gs_SoapEnvVersionsStruct[sv].pchNamespaceUri);
			m_Map[sv].pchPrefix = __TRC(gs_SoapEnvVersionsStruct[sv].pchPrefix);
			for (int sw = SKW_ENVELOPE; sw < SOAP_WORDS_LAST; sw++)
			{
				m_Map[sv].pchWords[sw] = __TRC(gs_SoapEnvVersionsStruct[sv].pchWords[sw]);
			}
		}
		//soap 1.1 envelop attributes
		m_Map[SOAP_VER_1_1].pEnv = new Attribute("SOAP-ENV","xmlns","","http://schemas.xmlsoap.org/soap/envelope/");
		m_Map[SOAP_VER_1_1].pXsi = new Attribute("xsi","xmlns","","http://www.w3.org/2001/XMLSchema-instance");
		m_Map[SOAP_VER_1_1].pXsd = new Attribute("xsd","xmlns","","http://www.w3.org/2001/XMLSchema");
		//soap 1.2 envelop attributes
		m_Map[SOAP_VER_1_2].pEnv = new Attribute("env","xmlns","","http://www.w3.org/2003/05/soap-envelope");
		m_Map[SOAP_VER_1_2].pXsi = new Attribute("xsi","xmlns","","http://www.w3.org/2001/XMLSchema-instance");
		m_Map[SOAP_VER_1_2].pXsd = new Attribute("xsd","xmlns","","http://www.w3.org/2001/XMLSchema");
		m_bInit = true;
	}
}

const SoapKeywordStruct& SoapKeywordMapping::Map(int nVersion)
{
	return m_Map[nVersion];
}
