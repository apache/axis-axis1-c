/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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
 * @author Sanjaya Singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

// Call.h: interface for the Call class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
#define AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_

#include "../common/IParam.h"
#include "../engine/ClientAxisEngine.h"

class AxisTransport;

/* A separate call class object should be used by each thread */
class Call  
{
public:
	void SetSOAPVersion(SOAP_VERSION version);
	int SetHeader(char * key, char* value);
	int SetProtocol(AXIS_PROTOCOL_TYPE protocol);
	int UnInitialize();
	int Initialize();
	uParamValue GetResult();
	int Invoke();
	void SetReturnType(void* pObject, void* pDZFunct, void* pDelFunct, const char * theType, const char * uri);
	void SetReturnType(XSDTYPE nType);

	void AddParameter(void* pObject, void* pSZFunct, void* pDelFunct, const char* pchName);
	void AddParameter(IArrayBean* pArrayBean, const char* pchName);

	void AddParameter(int nValue,const char* pchName);
	void AddParameter(unsigned int unValue,const char* pchName);
	void AddParameter(short sValue,const char* pchName);
	void AddParameter(unsigned short usValue,const char* pchName);
	void AddParameter(long lValue,const char* pchName);
	void AddParameter(unsigned long ulValue,const char* pchName);
	void AddParameter(char cValue,const char* pchName);
	void AddParameter(unsigned char ucValue,const char* pchName);
	void AddParameter(float fValue,const char* pchName);
	void AddParameter(double dValue,const char* pchName);
	void AddParameter(struct tm tValue,const char* pchName);
	void AddParameter(const AxisChar* pStrValue,const char* pchName);

	void SetOperation(const char* pchOperation, const char* pchNamespace);
	void SetOperation(const char* pchOperation, const char* pchNamespace,const char* pchName);
	int SetEndpointURI(const char* pchEndpointURI);
	Call();
	virtual ~Call();
private:
	int OpenConnection();
	void CloseConnection();
private:
	ClientAxisEngine* m_pAxisEngine;
	uParamValue m_uReturnValue;
	MessageData* m_pMsgData;
	SoapSerializer* m_pIWSSZ;
	SoapDeSerializer* m_pIWSDZ;
	XSDTYPE m_nReturnType;
	ComplexObjectHandler m_ReturnCplxObj;
	Ax_soapstream m_Soap;
	AxisTransport* m_pTransport;
};

#endif // !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
