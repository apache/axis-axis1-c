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

// WSDDService.cpp: implementation of the WSDDService class.
//
//////////////////////////////////////////////////////////////////////

#include "WSDDService.h"
#include <iostream>
#include "../common/Debug.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WSDDService::WSDDService()
{
	m_RequestHandlers = NULL;
	m_ResponseHandlers = NULL;
}

WSDDService::~WSDDService()
{
	WSDDHandlerList::iterator iter;
	if(m_RequestHandlers)
	{
		for(iter=m_RequestHandlers->begin()
				;iter!=m_RequestHandlers->end()
				;iter++)
		{
			delete (*iter);
		}
	}

	if(m_ResponseHandlers)
	{
		for(iter=m_ResponseHandlers->begin()
				;iter!=m_ResponseHandlers->end()
				;iter++)
		{
			delete (*iter);
		}
	}


}

void WSDDService::SetServiceName(string& sServiceName)
{
	m_sName = sServiceName;
}

string& WSDDService::GetServiceName()
{
	return m_sName;
}

void WSDDService::SetAllowedMethod(string& sMethodName)
{
	m_AllowedMethods.push_back(sMethodName);
}

bool WSDDService::IsAllowedMethod(string& sServiceName)
{
	list<string>::iterator iter;

	for(iter=m_AllowedMethods.begin();iter!=m_AllowedMethods.end();iter++)
	{
		if((*iter)==sServiceName)
		{
			cout<<"we have a service by that name";
			return true;
		}
	}
	return false;
}

void WSDDService::SetRequestFlowHandlers(WSDDHandlerList * reqFlowHList)
{
  DEBUG1("WSDDService::SetRequestFlowHandlers");
	m_RequestHandlers = reqFlowHList;
}


WSDDHandlerList* WSDDService::GetRequestFlowHandlers()
{
	return m_RequestHandlers;
}

void WSDDService::SetResponseFlowHandlers(WSDDHandlerList * resFlowHList)
{
	m_ResponseHandlers = resFlowHList;
}

WSDDHandlerList* WSDDService::GetResponseFlowHandlers()
{
	return m_ResponseHandlers;
}

void WSDDService::SetAllowedRoles(string& sRole)
{
	m_AllowedRoles.push_back(sRole);
}

list<string> WSDDService::GetAllowedRoles()
{
	return m_AllowedRoles;
}

void WSDDService::SetIsServiceAllowed(int m_IsServiceAllowed)
{
  m_IsServiceAllowed = m_IsServiceAllowed;
}

int WSDDService::GetIsServiceAllowed()
{
  return m_IsServiceAllowed;
}