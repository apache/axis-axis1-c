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
// Variable.h: interface for the Variable class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(AFX_VARIABLE_H__F9272406_BB8F_4151_8346_E033DDDDA468__INCLUDED_)
#define AFX_VARIABLE_H__F9272406_BB8F_4151_8346_E033DDDDA468__INCLUDED_

#include "File.h"

#include <string>
#include <list>
#include <map>

using namespace std;

enum VARTYPE { VAR_UNKNOWN=0, VAR_INT=1, VAR_FLOAT, VAR_STRING, VAR_LONG, VAR_SHORT, \
			   VAR_CHAR, VAR_DOUBLE, VAR_BOOL, VAR_UNSIGNEDLONG, VAR_UNSIGNEDINT,\
			   VAR_UNSIGNEDSHORT, VAR_UNSIGNED_CHAR, VAR_USER};
enum WSDL_BINDINGS { SOAP_BINDING=1, HTTP_BINDING };
enum BINDING_STYLES { SOAP_RPC=1, SOAP_DOCUMENT, HTTP_GET, HTTP_POST};
enum WSDL_TRANSPORT { HTTP_TRANSPORT=1 };

//Qualifiers
const unsigned char Q_PRIVATE = 0x01;
const unsigned char Q_PROTECTED = 0x02;
const unsigned char Q_STATIC = 0x04;
const unsigned char Q_CONST = 0x08;
const unsigned char Q_VIRTUAL = 0x10;
const unsigned char Q_REFTYPE = 0x20;
const unsigned char Q_PTRTYPE = 0x40;
const unsigned char Q_PTRPTRTYPE = 0x80;

class Variable  
{
public:	
	int GenerateWSDLPartInMessage(File& file, bool bInput);
	int GenerateWSDLSchema(File &file);
	static string& GetParamGetMethod(int nType);
	int GenerateDeserializerImpl(File& file);
	int GenerateSerializerImpl(File& file);
	string& GetTypeEnumStr();
	string& GetCorrespondingUnionMemberName();
	void Reset();
	int GetType();
	bool IsArrayType();
	bool IsComplexType();
	string& GetVarName();
	string& GetTypeName();
	void SetVarName(string& sVarName);
	void SetType(int nType, string sType="");
	void SetQualification(unsigned char cQualifier);
	Variable();
	Variable(Variable& Var);
	virtual ~Variable();
private:
	static string m_sAuxStr;
	void SetBasicTypeName();
	int m_Type;
	string m_TypeName; //if m_Type is user type
	string m_VarName;
	list<int> m_ArrayIndexes;
	unsigned char m_Qualifier; //private=1/protected=2/public=0/static=4/const=8/reference type=16/pointer type=32/pointer to pointer type=64
};

extern map<string, string> g_ClassNamespaces;

#endif // !defined(AFX_VARIABLE_H__F9272406_BB8F_4151_8346_E033DDDDA468__INCLUDED_)
