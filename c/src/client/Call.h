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
	void GetResult(void** pReturn);
	int Invoke();

	/* Method to set that the return type is complex type */
	void SetReturnType(void* pDZFunct, void* pCreFunct, void* pDelFunct, const char* pchTypeName, const char* pchUri);
	/* Method to set that the return type is an array of complex types */
	void SetReturnType(Axis_Array* pArray, void* pDZFunct, void* pCreFunct, void* pDelFunct, const char* pchTypeName, const char* pchUri);
	/* Method to set that the return type is an array of basic types */
	void SetReturnType(Axis_Array* pArray, XSDTYPE nType);
	/* Method to set that the return type is basic type */
	void SetReturnType(XSDTYPE nType);

	/* Method for adding complex parameters */
	void AddParameter(void* pObject, void* pSZFunct, void* pDelFunct, const char* pchName);
	/* Method for adding complex type array parameters */
	void AddParameter(Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const char* pchTypeName);
	/* Method for adding basic type array parameters */
	void AddParameter(Axis_Array* pArray, XSDTYPE nType);

	/* Methods for adding parameters of basic types */
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

	/* Method that set the remote method name */
	void SetOperation(const char* pchOperation, const char* pchNamespace);
	int SetEndpointURI(const char* pchEndpointURI);
	Call();
	virtual ~Call();
private:
	int OpenConnection();
	void CloseConnection();
	void InitializeObjects();
	int MakeArray();

private:
	ClientAxisEngine* m_pAxisEngine;
	uParamValue m_uReturnValue;
	/* 
	   Following are pointers to relevant objects of the ClientAxisEngine instance 
	   So they do not belong to this object and are not created or deleted 
	 */
	MessageData* m_pMsgData;
	SoapSerializer* m_pIWSSZ;
	SoapDeSerializer* m_pIWSDZ;
	/* 
	   Return type of the remote method being called 
	 */
	XSDTYPE m_nReturnType;
	/* 
	   m_ReturnCplxObj is populated with the relevant function pointers to manipulate
	   a custom type when the return type of a method call is a custom type or an array
	   of custom types.
	 */
	ComplexObjectHandler m_ReturnCplxObj;
	/* 
	   m_Soap contains transport related information and function pointers to manipulate
	   transport layer.
	 */
	Ax_soapstream m_Soap;
	/*
	   Transport object
	 */
	AxisTransport* m_pTransport;
	/* 
	   m_pArray will hold the Array object passed by the client application and will be 
	   populated with deserialized elements when the response arrives.
	 */
	Axis_Array* m_pArray;
	/*
	   m_nArrayType will contain the type of an array element when the called method returns
	   and array.
	 */
	XSDTYPE m_nArrayType;
};

#endif // !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
