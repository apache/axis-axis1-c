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

// WSDDHandler.cpp: implementation of the WSDDHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "WSDDHandler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WSDDHandler::WSDDHandler()
{
  m_nLibId = 0;
  m_nScope = AH_REQUEST; //default
  m_sAux = "";
  m_Params = NULL;
}

WSDDHandler::~WSDDHandler()
{
  if (m_Params) delete m_Params;
}

void WSDDHandler::SetLibName(const string& sLibName)
{
	m_sLibName = sLibName;
}

void WSDDHandler::SetLibId(int nLibId)
{
	m_nLibId = nLibId;
}

int WSDDHandler::GetLibId() const
{
	return m_nLibId;
}

const string& WSDDHandler::GetLibName() const
{
	return m_sLibName;
}

int WSDDHandler::GetScope() const
{
	return m_nScope;
}

void WSDDHandler::SetScope(const string& sScope)
{
	if (sScope == kw_scope_app)
		m_nScope = AH_APPLICATION;	
	else if (sScope == kw_scope_ses)
		m_nScope = AH_SESSION;	
	else
		m_nScope = AH_REQUEST;	
}

const string& WSDDHandler::GetParameter(const string& sKey) const
{
	if (m_Params->find(sKey) != m_Params->end())
		return (*m_Params)[sKey];
	return m_sAux;
}

void WSDDHandler::AddParameter(const string& sKey, const string& sValue)
{
	if (!m_Params) m_Params = new map<string, string>;
	(*m_Params)[sKey] = sValue; 
}

const map<string, string>* WSDDHandler::GetParameterList() const
{
  return m_Params;
}

