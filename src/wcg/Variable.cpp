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
string Variable::m_sAuxStr="";

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
	return (m_Type == VAR_USER);
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

string& Variable::GetCorrespondingUnionMemberName()
{
	switch (m_Type)
	{
		case VAR_INT: m_sAuxStr = "nValue"; break;
		case VAR_FLOAT: m_sAuxStr = "fValue"; break;
		case VAR_STRING: m_sAuxStr = "pStrValue"; break; //note that string too is taken as a basic type
		case VAR_LONG: m_sAuxStr = "lValue"; break;
		case VAR_SHORT: m_sAuxStr = "sValue"; break;
		case VAR_CHAR: m_sAuxStr = "cValue"; break;
		case VAR_DOUBLE: m_sAuxStr = "dValue"; break;
		case VAR_BOOL: m_sAuxStr = "bValue"; break;
		case VAR_UNSIGNEDLONG: m_sAuxStr = "ulValue"; break;
		case VAR_UNSIGNEDINT: m_sAuxStr = "unValue"; break;
		case VAR_UNSIGNEDSHORT: m_sAuxStr = "usValue"; break;
		case VAR_UNSIGNED_CHAR: m_sAuxStr = "ucValue"; break;
		case VAR_USER: m_sAuxStr = "pIBean"; break;
	}
	return m_sAuxStr;	
}

string& Variable::GetTypeEnumStr()
{
	switch (m_Type)
	{
		case VAR_INT: m_sAuxStr = "XSD_INT"; break;
		case VAR_FLOAT: m_sAuxStr = "XSD_FLOAT"; break;
		case VAR_STRING: m_sAuxStr = "XSD_STRING"; break; //note that string too is taken as a basic type
		case VAR_LONG: m_sAuxStr = "XSD_LONG"; break;
		case VAR_SHORT: m_sAuxStr = "XSD_SHORT"; break;
		case VAR_CHAR: m_sAuxStr = "XSD_CHAR"; break;
		case VAR_DOUBLE: m_sAuxStr = "XSD_DOUBLE"; break;
		case VAR_BOOL: m_sAuxStr = "XSD_BOOL"; break;
		case VAR_UNSIGNEDLONG: m_sAuxStr = "XSD_UNSIGNEDLONG"; break;
		case VAR_UNSIGNEDINT: m_sAuxStr = "XSD_UNSIGNEDINT"; break;
		case VAR_UNSIGNEDSHORT: m_sAuxStr = "XSD_UNSIGNEDSHORT"; break;
		case VAR_UNSIGNED_CHAR: m_sAuxStr = "XSD_UNSIGNED_CHAR"; break;
		case VAR_USER: m_sAuxStr = "USER_TYPE"; break;
	}
	return m_sAuxStr;
}

/*
 *When returning the return value of a web service method we have to set
 *the return value from the web service method to a uParamValue union first
 *The types in the uParamValue union is predefined. So we need to find what 
 *reference/dereference charactors should proceed the variable name.
 *	
 * Ex: if web service method returns int 
 *     value.nValue = ret; 
 *     if web service method returns int*
 *     value.nValue = *ret;
 * In case of strings this is somewhat different because in uParamValue union we 
 * have const char* for setting string value. So in this case we append ".c_str()"
 * like,
 *     value.pStrValue = ret.c_str() 
 */

//DEL string& Variable::GetAnyReferenceChars()
//DEL {
//DEL 	
//DEL }


int Variable::GenerateSerializerImpl(File &file)
{
	file << "\t"; 
	if (IsComplexType())
	{
		file << "Axis_Serialize_" << m_TypeName << "(p->" << m_VarName << ", pSZ);";		
	}
	else
	{
		file << "pSZ << " << "pSZ.SerializeBasicType(\"" << m_VarName << "\", p->" << m_VarName << ");";
	}
	file << endl;
	return 0;
}

int Variable::GenerateDeserializerImpl(File &file)
{
	if (IsComplexType())
	{
		file << "\tpDZ->GetParam(); //get head param describing the complex type and do anything with it" << endl;
		file << "\tp->" << m_VarName << "= new " << m_TypeName << ";" << endl;
		file << "\tAxis_DeSerialize_" << m_TypeName << "(p->" << m_VarName << ", pDZ);" << endl;
	}
	else
	{
		file << "\t" << "p->" << m_VarName << " = pDZ->GetParam()->" << GetParamGetMethod(m_Type).c_str() << "();";
	}
	file << endl;
	return 0;
}

string& Variable::GetParamGetMethod(int nType)
{
	//All get methods of Param class should be listed here
	switch(nType)
	{
		case VAR_INT: m_sAuxStr = "GetInt"; break;
		case VAR_FLOAT: m_sAuxStr = "GetFloat"; break;
		case VAR_STRING: m_sAuxStr = "GetString"; break;
		case VAR_LONG: m_sAuxStr = "GetLong"; break;
		case VAR_SHORT: m_sAuxStr = "GetShort"; break;
		case VAR_CHAR: m_sAuxStr = "GetChar"; break;
		case VAR_DOUBLE: m_sAuxStr = "GetDouble"; break;
		case VAR_BOOL: m_sAuxStr = "GetBool"; break;
		case VAR_UNSIGNEDLONG: m_sAuxStr = "GetUnsignedLong"; break;
		case VAR_UNSIGNEDINT: m_sAuxStr = "GetUnsignedInt"; break;
		case VAR_UNSIGNEDSHORT: m_sAuxStr = "GetUnsignedShort"; break;
		case VAR_UNSIGNED_CHAR: m_sAuxStr = "GetUnsignedChar"; break;
	}
	return m_sAuxStr;
}

int Variable::GenerateWSDLSchema(File &file)
{
	if (m_Type == VAR_UNKNOWN) return 1; //error
	file << "<element name=\"" << m_VarName << "\" type=\"";
	if (m_Type != VAR_USER) file << "xsd:" << m_TypeName << "\" />" << endl;
	else file << "xsdl:" << m_TypeName << "\" />" << endl;
}

int Variable::GenerateWSDLPartInMessage(File &file, bool bInput)
{
	if (m_Type == VAR_UNKNOWN) return 1; //error
	file << "<part name=\"";
	if (bInput) 
	{
		file << "input" << m_TypeName << m_VarName;
	}
	else
	{
		file << "return";
	}
	file << "\" type=\"";
	if (m_Type != VAR_USER) file << "xsd:" << m_TypeName << "\" />" << endl;
	else file << "xsdl:" << m_TypeName << "\" />" << endl;
}
