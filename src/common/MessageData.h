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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

// MessageData.h: interface for the MessageData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEDATA_H__8B839E07_3D23_46C6_8743_543B4917D202__INCLUDED_)
#define AFX_MESSAGEDATA_H__8B839E07_3D23_46C6_8743_543B4917D202__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GDefine.h"
#include "IMessageData.h"
#include "../wsdd/WSDDService.h"
#include "../soap/SoapSerializer.h"
#include "../soap/SoapDeSerializer.h"
#include "Param.h"

#include <string>
#include <list>
#include <map>

using namespace std;

class MessageData : public IMessageData
{
public:
	MessageData();
	virtual ~MessageData();
public:
	SoapSerializer* m_pSZ;
	SoapDeSerializer* m_pDZ;
public:
	void SetDeSerializer(SoapDeSerializer* pDZ);
	void SetSerializer(SoapSerializer* pSZ);
	void SetUserName(string& m_sUserName);
	string& GetUserName();
	void SetService(WSDDService* argService);
	WSDDService* GetService();  
	AXIS_PROTOCOL_TYPE m_Protocol;
	ISoapDeSerializer* getSoapDeserializer();
	ISoapSerializer* getSoapSerializer();
protected:
  string m_sUserName;
  WSDDService* m_Service;

};

#endif // !defined(AFX_MESSAGEDATA_H__8B839E07_3D23_46C6_8743_543B4917D202__INCLUDED_)
