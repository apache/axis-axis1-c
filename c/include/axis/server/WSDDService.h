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
 */

// WSDDService.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WSDDSERVICE_H__F5F6BB58_0733_445B_97E3_B7488446AC47__INCLUDED_)
#define AFX_WSDDSERVICE_H__F5F6BB58_0733_445B_97E3_B7488446AC47__INCLUDED_

#include "WSDDHandler.h"
#include "WSDDDefines.h"

#include <string>
#include <map>

using namespace std;
/**
    @class WSDDService
    @brief interface for the WSDDService class.


    @author Susantha Kumara (skumara@virtusa.com)
*/
class WSDDService : public WSDDHandler 
{
public:
	const list<AxisString> getAllowedMethods() const;
	void SetServiceName(const AxisChar* sServiceName);
	void SetProvider(const AxisChar* sProvider);
	PROVIDERTYPE GetProvider() const;
	const AxisChar* GetServiceName() const;
	bool IsAllowedMethod(const AxisChar* sMethodName) const;
	void AddAllowedMethod(const AxisChar* sMethodName);
	const WSDDHandlerList* GetResponseFlowHandlers() const;
	void AddHandler(bool bRequestFlow, WSDDHandler* pHandler);
	const WSDDHandlerList* GetRequestFlowHandlers() const;
	void AddAllowedRole(const AxisChar* sRole);
	const list<AxisString>& GetAllowedRoles();
	WSDDService();
	virtual ~WSDDService();
	int UpdateWSDD(FILE* wsddfile, int tabcount);
private:
	const char* GetProviderString();
private:
	PROVIDERTYPE m_Provider;
	list<AxisString> m_AllowedMethods;
	WSDDHandlerList* m_RequestHandlers;
	WSDDHandlerList* m_ResponseHandlers;
	list<AxisString> m_AllowedRoles;
};

typedef map<AxisString, WSDDService*> WSDDServiceMap;

#endif // !defined(AFX_WSDDSERVICE_H__F5F6BB58_0733_445B_97E3_B7488446AC47__INCLUDED_)
