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
// Variable.cpp: implementation of the Variable class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#include "Variable.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Variable::Variable()
{
	m_Qualifier = 0;
	m_Type = 0;
	m_TypeName = "";
	m_VarName = "";
}

Variable::Variable(Variable& Var)
{
	m_Qualifier = Var.m_Qualifier;
	m_Type = Var.m_Type;
	m_TypeName = Var.m_TypeName;
	m_VarName = Var.m_VarName;
}

Variable::~Variable()
{

}

void Variable::SetType(int nType, string sType)
{
	m_Type = nType;
	if (nType == VAR_USER) m_TypeName = sType;
	else SetBasicTypeName();
}

void Variable::SetVarName(string &sVarName)
{
	m_VarName = sVarName;
}

void Variable::SetQualification(unsigned char cQualifier)
{
 	m_Qualifier |= cQualifier;
}

string& Variable::GetTypeName()
{
	return m_TypeName;
}

string& Variable::GetVarName()
{
	return m_VarName;
}

void Variable::SetBasicTypeName()
{	
	switch (m_Type)
	{
		case VAR_INT: m_TypeName = "int"; break;
		case VAR_FLOAT: m_TypeName = "float"; break;
		case VAR_STRING: m_TypeName = "string"; break; //note that string too is taken as a basic type
		case VAR_LONG: m_TypeName = "long"; break;
		case VAR_SHORT: m_TypeName = "short"; break;
		case VAR_CHAR: m_TypeName = "char"; break;
		case VAR_DOUBLE: m_TypeName = "double"; break;
		case VAR_BOOL: m_TypeName = "bool"; break;
		case VAR_UNSIGNEDLONG: m_TypeName = "unsigned long"; break;
		case VAR_UNSIGNEDINT: m_TypeName = "unsigned int"; break;
		case VAR_UNSIGNEDSHORT: m_TypeName = "unsigned short"; break;
		case VAR_UNSIGNED_CHAR: m_TypeName = "unsigned char"; break;
	}
}

bool Variable::IsComplexType()
{
	return false;
}

bool Variable::IsArrayType()
{
	return false;
}

int Variable::GetType()
{
	return m_Type;
}

void Variable::Reset()
{
	m_Qualifier = 0;
	m_Type = 0;
	m_TypeName = "";
	m_VarName = "";
}
