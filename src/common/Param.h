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

// Param.h: interface for the Param class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#if !defined(AFX_PARAM_H__351B13BB_5D03_40C5_93F5_56D17295A8BD__INCLUDED_)
#define AFX_PARAM_H__351B13BB_5D03_40C5_93F5_56D17295A8BD__INCLUDED_

#include "IParam.h"
#include "BasicTypeSerializer.h"
#include "AxisTime.h"

#include <string>
using namespace std;

class ArrayBean;

class Param : public IParam
{
	friend class SoapDeSerializer;
	friend class SoapSerializer;
	friend class XMLStreamHandler;
public:
	Param(){ m_Type = USER_TYPE;}; //if there is no attribute that says the type

    Param(time_t time);
    Param(struct tm timeStruct);
	Param(const Param& param);
	Param(const AxisChar* str, XSDTYPE type = XSD_STRING);
	Param(int nValue);
    Param(unsigned int unValue);   
    Param(short sValue);
    Param(unsigned short usValue);
    Param(char cValue);
    Param(unsigned char ucValue);
    Param(long lValue, XSDTYPE type=XSD_LONG);
    Param(unsigned long ulValue);
	Param(float fValue);
	Param(double dValue, XSDTYPE type=XSD_DOUBLE);
	virtual ~Param();
	void operator=(const Param &param);

private:
	uParamValue m_Value;
	AxisString m_sValue; //value in case of XSD_STRING, XSD_HEXBINARY and XSD_BASE64BINARY
	AxisString m_sName; //Name of the parameter
	XSDTYPE m_Type; //Type of the parameter

private:
	AxisString m_strPrefix; //needed in serialization only
	AxisString m_strUri; //needed in serialization only

public: //Conversion functions
	const AxisString& GetTypeName();
	int SetValue(const AxisChar* sValue);
	int SetValue(XSDTYPE nType, uParamValue Value);
	XSDTYPE GetType() const;	
	int serialize(IWrapperSoapSerializer& pSZ);

	//Following functions are used by wrapper class methods making sure of the valid type.
	int GetInt();
    unsigned int GetUnsignedInt();    
    short GetShort();
    unsigned short GetUnsignedShort();
    char GetByte();
    unsigned char GetUnsignedByte();
    long GetLong();
    long GetInteger();
    unsigned long GetUnsignedLong();
	float GetFloat();
    double GetDouble();
    double GetDecimal();
    const AxisChar* GetAnyURI();
    const AxisChar* GetQName();
    struct tm GetDateTime();
    struct tm GetDate();
    struct tm GetTime();
    long GetDuration();
	const AxisChar* GetString();
	const AxisChar* GetHexString();
	const AxisChar* GetBase64String();
	void setPrefix(const AxisChar* prefix);
	void setUri(const AxisChar* uri);
	int GetArraySize();
	int SetArrayElements(void* pElements);
	int SetArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct);
	int SetUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct);
	void SetName(const AxisChar* sName);
	uParamValue GetValue(){ return m_Value;};
private:
	BasicTypeSerializer m_BTSZ;
    AxisTime m_uAxisTime;
    //uDuration duration;
};

#endif // !defined(AFX_PARAM_H__351B13BB_5D03_40C5_93F5_56D17295A8BD__INCLUDED_)
