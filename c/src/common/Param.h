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

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "../soap/TypeMapping.h"

using namespace std;

class AccessBean;
class ArrayBean;
class SoapSerializer;

class Param  
{
public:
	Param(){ m_Type = USER_TYPE;}; //if there is no attribute that says the type
	Param(Param& param);
	Param(string &str, XSDTYPE type=XSD_STRING);
	Param(int nValue);
	Param(float fValue);
	Param(double dValue);
	virtual ~Param();
	void operator=(Param &param);

public:
	union uValue
	{
		int n;
		float f;
		double d;
		//all basic types should come here
		ArrayBean* a; //holds array types
		AccessBean* o; //this is used to hold user types 
	} m_Value;

	string m_sValue; //value in case of XSD_STRING 
	string m_sName; //Name of the parameter
	XSDTYPE m_Type; //Type of the parameter

	static string m_sSZ; //Used for serialization
	static char m_Buf[64]; //Used for conversions using sprintf

private:
	string m_strPrefix; //needed in serialization only
	string m_strUri; //needed in serialization only

public: //Conversion functions
	int SetValue(string& sValue);
	XSDTYPE GetType() const;
	const string& ToString();
	int serialize(string& sSerialized);

	//Following functions are used by wrapper class methods making sure of the valid type.
	int GetInt();
	float GetFloat();
	const string& GetString();
	const AccessBean* GetUserType() const;
	void setPrefix(const string &prefix);
	void setUri(const string &uri);
};

#endif // !defined(AFX_PARAM_H__351B13BB_5D03_40C5_93F5_56D17295A8BD__INCLUDED_)
