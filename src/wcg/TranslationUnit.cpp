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
// TranslationUnit.cpp: implementation of the TranslationUnit class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#include "TranslationUnit.h"
#include "File.h"
#include <iostream>
#include <string>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define WCID(X) "__WRAPPER_CLASS_" << X << "_INCLUDED__"

TranslationUnit::TranslationUnit()
{
	m_pWSClass = NULL;
}

TranslationUnit::~TranslationUnit()
{
	if (m_pWSClass) delete m_pWSClass;
	for (list<BeanClass*>::iterator it = m_Beans.begin(); it != m_Beans.end(); it++)
	{
		delete *it;
	}
}

int TranslationUnit::GenerateWSDL(string& sServiceFile, string& sURI)
{
	try {
		if (!m_pWSClass) {
			cout << "No web service class found" << endl;	
			return 1;
		}
		string fname = sServiceFile + ".wsdl"; 
		File file(fname);
		file << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"<< endl;
		file << "<definitions targetNamespace=\"http://" << sURI.c_str() << "/Axis/" << sServiceFile.c_str() << "\""<< endl;
		file << "xmlns=\"http://schemas.xmlsoap.org/wsdl/\""<< endl;
		file << "xmlns:soap=\"http://schemas.xmlsoap.org/wsdl/soap/\""<< endl;
		file << "xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\""<< endl;
		file << "xmlns:xsdl=\""<< sServiceFile.c_str() << "-xsd\""<< endl; //xsd local
		file << "xmlns:impl=\"http://" << sURI.c_str() << "/Axis/" << sServiceFile.c_str() << "\""<< endl; //implimentation
		file << "xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\">" << endl;
		//types section
		if (!m_Beans.empty())
		{
			file << "<types>" << endl;
			file << "<schema targetNamespace=\"" << sServiceFile.c_str() << "-xsd\" "<< "xmlns=\"http://www.w3.org/2001/XMLSchema\" " << "xmlns:wsdl=\"http://schemas.xmlsoap.org/wsdl/\">" << endl;
			//generate schema for types
			for (list<BeanClass*>::iterator it = m_Beans.begin(); it != m_Beans.end(); it++)
			{
				(*it)->GenerateWSDLSchema(file);
			}
			file << "</schema>" << endl;
			file << "</types>" << endl;
		}
		//messages section
		m_pWSClass->GenerateWSDLMessages(file);
		//porttypes section
		m_pWSClass->GenerateWSDLPortTypes(file, sServiceFile);
		//bindings section
		//create only soap - rpc - http binding for now
		GenerateWSDLBinding(file, sServiceFile, SOAP_BINDING, SOAP_RPC, HTTP_TRANSPORT, sURI);
		file << "</definitions>" << endl;
	}
	catch(...) //any exception
	{
		return 1;
	}
	return 0; //success
}

int TranslationUnit::GenerateWrapperClassDef()
{
	try {
		if (!m_pWSClass) {
			cout << "No web service class found" << endl;	
			return 1;
		}
		string fname = m_pWSClass->GetName() + ".hpp"; 
		File file(fname);
		file << "//This file is automatically generated by the Axis C++ Wrapper Class Generator" << endl;
		file << "#if !defined " << WCID(m_pWSClass->GetName().c_str()) << endl;
		file << "#define " << WCID(m_pWSClass->GetName().c_str()) << endl;
		file << endl;
		//add includes
		file << "#include \"" << m_sWsFileName.c_str() << "\"" << endl;
		file << "#include \"common/WrapperClassHandler.h\"" << endl;
		file << "#include \"common/IMessageData.h\"" << endl;
		file << "#include \"common/GDefine.h\"" << endl;
		file << "#include \"common/IAccessBean.h\"" << endl;
		file << endl;
		//generate wrapper class declaration
		m_pWSClass->GenerateClassDef(file);
		file << endl;
		file << "#endif" << endl;
	}
	catch(...) //any exception
	{
		cout << "Exception occured" << endl;
		return 1;
	}
	return 0; //success
}

int TranslationUnit::GenerateWrapperClassImpl()
{
	try {
		if (!m_pWSClass) {
			cout << "No web service class found" << endl;	
			return 1;
		}
		string fname = m_pWSClass->GetName() + ".cpp"; 
		File file(fname);
		file << "//This file is automatically generated by the Axis C++ Wrapper Class Generator" << endl;
		file << "//Web service wrapper class's implementation generated by Axis WCG" << endl;
		file << "#include \"" << m_pWSClass->GetName() << ".hpp\"" << endl;
		file << endl;
		//add includes
		file << "#include \"common/ISoapDeserializer.h\"" << endl;
		file << "#include \"common/ISoapSerializer.h\"" << endl;
		file << "#include \"common/ISoapMethod.h\"" << endl;
		file << "#include \"common/IParam.h\"" << endl;

		file << "#include <string>" << endl;
		file << "using namespace std;" << endl;
		file << endl;
		//generate serializers and deserializers for bean classes
		for (list<BeanClass*>::iterator it = m_Beans.begin(); it != m_Beans.end(); it++)
		{
			(*it)->GenerateSerializerAndDeSerializerImpl(file);
		}
		//generate wrapper class's methods
		m_pWSClass->GenerateClassImpl(file);
		//generate IAccessBean implementations for bean classes
		file << endl;
	}
	catch(...) //any exception
	{
		cout << "Exception occured" << endl;
		return 1;
	}
	return 0; //success
}

void TranslationUnit::AddInclude(string &sInclude)
{
	m_includes.push_back(sInclude);
}

void TranslationUnit::AddNSDecl(string &sNSDecl)
{
	m_nsdecls.push_back(sNSDecl);
}

void TranslationUnit::SetWSClass(WSClass *pClass)
{
	m_pWSClass = pClass;
}

void TranslationUnit::AddBeanClass(BeanClass *pClass)
{
	m_Beans.push_back(pClass);
}

void TranslationUnit::SetWsFileName(const char *sFileName)
{
	m_sWsFileName = sFileName;
}

int TranslationUnit::GenerateServiceFile(string& sServiceFile)
{
	try {
		if (!m_pWSClass) {
			cout << "No web service class found" << endl;	
			return 1;
		}
		string fname = sServiceFile + ".cpp"; 
		File file(fname);
		file << "//This file is automatically generated by the Axis C++ Wrapper Class Generator" << endl;
		file << "//Service file containing the two export functions of the Web service Library" << endl;
		file << "#ifdef WIN32" << endl;
		file << "#define STORAGE_CLASS_INFO __declspec(dllexport)" << endl;
		file << "#else" << endl;
		file << "#define STORAGE_CLASS_INFO " << endl;
		file << "#endif" << endl;
		file << endl;
		file << "#include \"" << m_pWSClass->GetName() << ".hpp\"" << endl;
		file << endl;
		file << "extern \"C\" {" << endl;
		file << endl;
		file << "STORAGE_CLASS_INFO" << endl;
		file << "int GetClassInstance(BasicHandler **inst)" << endl;
		file << "{" << endl;
		file << "\tWrapperClassHandler* pWCH = new " << m_pWSClass->GetName() << "();" << endl;
		file << "\tif (pWCH) " << endl;
		file << "\t{" << endl;
		file << "\t\tpWCH->Init();" << endl;
		file << "\t\t*inst = pWCH;" << endl;
		file << "\t\treturn SUCCESS;" << endl;
		file << "\t}" << endl;
		file << "\treturn FAIL;" << endl;
		file << "}" << endl;
		file << "STORAGE_CLASS_INFO " << endl;
		file << "int DestroyInstance(BasicHandler *inst)" << endl;
		file << "{" << endl;
		file << "\tif (inst) " << endl;
		file << "\t{" << endl;
		file << "\t\tWrapperClassHandler* pWCH = reinterpret_cast<WrapperClassHandler*>(inst);" << endl;
		file << "\t\tpWCH->Fini();" << endl;
		file << "\t\tdelete pWCH;" << endl;
		file << "\t\treturn SUCCESS;" << endl;
		file << "\t}" << endl;
		file << "\treturn FAIL;" << endl;
		file << "}" << endl;
		file << "}" << endl;
	}
	catch(...) //any exception" << endl;
	{
		cout << "Exception occured" << endl;
		return 1;
	}
	return 0; //success
}

int TranslationUnit::GenerateWSDLBinding(File &file, string& sServiceName, int nBinding, int nStyle, int nTransport, string& sURI)
{
	file << "<binding name=\"" << sServiceName;
	switch (nBinding)
	{
	case SOAP_BINDING: file << "Soap"; break;
	case HTTP_BINDING: file << "Http"; break;
	default: return 1; //error
	}
	file << "Binding\" type=\"impl:" << sServiceName << "PortType\">" << endl;
	switch (nBinding)
	{
	case SOAP_BINDING: 
		{
			file << "<soap:binding style=\"";
			switch (nStyle)
			{
			case SOAP_RPC: file << "rpc"; break;
			case SOAP_DOCUMENT: file << "document"; break;
			default: return 1; //error
			}
			file << "\" transport=\"";
			switch (nTransport)
			{
			case HTTP_TRANSPORT: file << "http://schemas.xmlsoap.org/soap/http"; break;
			default: return 1; //error
			}
			file << "\" />" << endl;
		}
		break;
	case HTTP_BINDING: 
		{
			
		}
		break;
	default: return 1; //error
	}
	m_pWSClass->GenerateOperationsInBinding(file, sServiceName, nBinding, nStyle, sURI); 
	file << "</binding>" << endl;
}
