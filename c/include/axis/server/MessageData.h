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

// MessageData.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEDATA_H__8B839E07_3D23_46C6_8743_543B4917D202__INCLUDED_)
#define AFX_MESSAGEDATA_H__8B839E07_3D23_46C6_8743_543B4917D202__INCLUDED_

#include "GDefine.h"
#include "IMessageData.h"
#include "WSDDService.h"
#include "SoapSerializer.h"
#include "SoapDeSerializer.h"
#include "Param.h"

#include <string>
#include <list>
#include <map>

using namespace std;
/**
    @class MessageData
    @brief interface for the MessageData class.


    @author Susantha Kumara (skumara@virtusa.com)
*/

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

class MessageData : public IMessageData
{
public:
	MessageData();
	virtual ~MessageData();
public:
	SoapSerializer* m_pSZ;
	SoapDeSerializer* m_pDZ;
public:
	const AxisChar* getProperty(AxisChar* pachName);
	int setProperty(AxisChar* pachName, const AxisChar* pachValue);
	void SetOperationName(const AxisChar* pchOperation){m_sOperationName = pchOperation;};
	void getSoapDeSerializer(IHandlerSoapDeSerializer** pIHandlerSoapDeSerializer);
	const AxisChar* AXISCALL GetOperationName(){return m_sOperationName.c_str();};
	void AXISCALL GetSoapSerializer(IWrapperSoapSerializer** pIWSS);
	void AXISCALL GetSoapDeSerializer(IWrapperSoapDeSerializer** pIWSDS);
	void getSoapSerializer(IHandlerSoapSerializer** pIHandlerSoapSerializer);
	IWrapperSoapDeSerializer* getSoapDeserializer();
	int setPastPivotState(bool bState);
	bool isPastPivot();
	void SetDeSerializer(SoapDeSerializer* pDZ);
	void SetSerializer(SoapSerializer* pSZ);
	void SetUserName(string& m_sUserName);
	string& GetUserName();
	void SetService(const WSDDService* argService);
	const WSDDService* GetService();  
	AXIS_PROTOCOL_TYPE m_Protocol;
	
protected:
  string m_sUserName;
  string m_sOperationName;
  const WSDDService* m_Service;

private:
	void getWSDDDeployment(IDeployerUtils** pIDeployerUtils);
	bool m_bPastPivotState;
	map <AxisChar*, AxisChar*, ltstr> m_Properties;
	static const AxisChar* m_pachBlankPropertyValue;
};

#endif // !defined(AFX_MESSAGEDATA_H__8B839E07_3D23_46C6_8743_543B4917D202__INCLUDED_)
