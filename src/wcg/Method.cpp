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
// Method.cpp: implementation of the Method class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#include "Method.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
	Features:
	Limitations:
		1. All basic types are passed/returned to/from web service methods by value.
		2. All user types are passed/returned to/from web service methods by reference (pointers)
		3. No arrays can be passed or returned from web service methods.
		4. 
		5.
  */
Method::Method()
{
	m_Qualifier=0;
	m_Name="";
	m_pReturnType = NULL;
}

Method::~Method()
{
	if (m_pReturnType) delete m_pReturnType;
	for (list<Variable*>::iterator it = m_Params.begin(); it != m_Params.end(); it++)
	{
		delete *it;
	}
}

void Method::AddReturnType(Variable *pVar)
{
	m_pReturnType = pVar;
}

void Method::AddParameter(Variable *pVar)
{
	m_Params.push_back(pVar);
}

void Method::SetMethodName(string &sName)
{
	m_Name = sName;
}

void Method::SetQualification(unsigned char sQualifier)
{
	m_Qualifier|=sQualifier;
}

//generates wrapper method declaration 
int Method::GenerateMethodDef(File &file)
{
	try 
	{
		file << "\tint" << " " << m_Name << "(IMessageData* mc);" << endl; 
	}
	catch(...) //any exception
	{
		return 1;
	}
	return 0; //success
}

string& Method::GetName()
{
	return m_Name;
}

int Method::GenerateMethodImpl(string& sClassName, File &file)
{
	file << "int " << sClassName << "::" << m_Name << "(IMessageData* mc)" << endl; 	
	file << "{" << endl;
	file << "\tSetResponseMethod(mc, \"" << m_Name << "\");" << endl;
	int nParam = 0;
	for (list<Variable*>::iterator it = m_Params.begin(); it != m_Params.end(); it++)
	{
		file << endl;
		file << "\tIParam *param" << nParam << " = mc->getSoapDeserializer()->GetParam();" << endl;
		if ((*it)->IsComplexType())
		{
			file << "\t" << (*it)->GetTypeName() << "* v" << nParam << " = new " << (*it)->GetTypeName() << "();" << endl;
			file << "\tparam" << nParam << "->" << "SetUserType(" << "v" << nParam << ");" << endl; 
			file <<	"\tmc->getSoapDeserializer()->Deserialize(param" << nParam << ",0);" << endl; // 0 should be changed to 1 if multiref to be used			
		}
		else if ((*it)->IsArrayType())
		{
			
		}
		else //basic types
		{
			file << "\t" << (*it)->GetTypeName() << " v" << nParam << " = " << "param" << nParam << "->" << Variable::GetParamGetMethod((*it)->GetType()) << "();" << endl;
		}
		nParam++;
	}
	file << endl;
	file << "\t//Call actual web service method with appropriate parameters" << endl;
	file << "\t" << m_pReturnType->GetTypeName();
	if (m_pReturnType->IsComplexType()) 
	{
		file << "*"; //this is because of the convention that all user types return by reference (pointer) //
	}
	file << " ret = pWs->" << m_Name << "(";
	for (int n=0; n<nParam;)
	{
		file << "v" << n++;
		if (n<nParam) file << ", ";
	}
	file << ");" << endl;
	file << endl;
	file << "\tuParamValue value;" << endl;
	file << "\tvalue." << m_pReturnType->GetCorrespondingUnionMemberName() << " = ret";
	if (m_pReturnType->GetType() == VAR_STRING)
	{
		file << ".c_str()";
	}
	file <<	";" << endl;
	file << "\tIParam* pRetParam = mc->getSoapSerializer()->setResponseParam(" << m_pReturnType->GetTypeEnumStr() << ", value);" << endl;
	file << "\tpRetParam->SetName(\"" << m_Name << "Return\");" << endl;
	file << "\treturn SUCCESS;" << endl; 
	file << "}" << endl;
	file << endl;
	return 0;
}

int Method::GenerateWSDLMessages(File &file)
{
	file << "<message name=\"" << m_Name << "Request\">" << endl;
	for (list<Variable*>::iterator it = m_Params.begin(); it != m_Params.end(); it++)
	{
		(*it)->GenerateWSDLPartInMessage(file, true);
	}
	file << "</message>" << endl;
	if (m_pReturnType)
	{
		file << "<message name=\"" << m_Name << "Response\">" << endl;
		m_pReturnType->GenerateWSDLPartInMessage(file, false);
		file << "</message>" << endl;
	}
	return 0; //success
}

int Method::GenerateWSDLOperationInPortType(File &file)
{
	file << "<operation name=\"" << m_Name << "\">" << endl;
	file << "<input message=\"impl:" << m_Name << "Request\" />" << endl; 
	file << "<output message=\"impl:" << m_Name << "Response\" />" << endl; 
	file << "</operation>" << endl;
	return 0;
}

int Method::GenerateOperationInBinding(File &file, string &sServiceName, int nBinding, int nStyle, string &sURI)
{
	file << "<operation name=\"" << m_Name << "\">" << endl;
	switch (nBinding)
	{
	case SOAP_BINDING: 
		{
			file << "<soap:operation soapAction=\"" << sServiceName << "\" style=\""; //service name should be in soapAction
			switch (nStyle)
			{
			case SOAP_RPC: 
				{	
					file << "rpc\" />" << endl;
					file << "<input>" << endl;
					file << "<soap:body use=\"encoded\" namespace=\"http://" << sURI << "/\" encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" />" << endl; 
					file << "</input>" << endl;
					file << "<output>" << endl;
					file << "<soap:body use=\"encoded\" namespace=\"http://" << sURI << "/\" encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" />" << endl; 
					file << "</output>" << endl;
				}
				break;
			case SOAP_DOCUMENT: 
				{
					file << "document\" />" << endl; 
					file << "<input>" << endl;
					file << "<soap:body use=\"literal\" />" << endl; 
					file << "</input>" << endl;
					file << "<output>" << endl;
					file << "<soap:body use=\"literal\" />" << endl; 
					file << "</output>" << endl;

				}
				break;
			default: return 1; //error
			}
		}
		break;
	case HTTP_BINDING: 
		{
			
		}
		break;
	default: return 1; //error
	}
	file << "</operation>" << endl;
	return 0;
}
