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
// WSClass.cpp: implementation of the WSClass class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#include "WSClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WSClass::WSClass()
{
	m_Name = "";
	m_pDestructor = NULL;
}

WSClass::~WSClass()
{
	for(list<Variable*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
	{	
		delete *it;
	}
	list<Method*>::iterator it1;
	for( it1 = m_Constructors.begin(); it1 != m_Constructors.end(); it1++)
	{	
		delete *it1;
	}
	for (it1 = m_Methods.begin(); it1 != m_Methods.end(); it1++)
	{
		delete *it1;
	}
	if (m_pDestructor) delete m_pDestructor;

}

void WSClass::SetClassName(string &sName)
{
	m_AWSName = sName;
	m_Name = sName + "Wrapper";
}

void WSClass::AddVariable(Variable *pVar)
{
	m_Variables.push_back(pVar);
}

void WSClass::AddConstructor(Method *pMethod)
{
	m_Constructors.push_back(pMethod);
}

void WSClass::AddMethod(Method *pMethod)
{
	m_Methods.push_back(pMethod);
}

void WSClass::SetDestructor(Method *pMethod)
{
	m_pDestructor = pMethod;
}

const string& WSClass::GetName()
{
	return m_Name;
}

int WSClass::GenerateClassDef(File &file)
{
	try {
		//add wrapper class
		file << "class " << m_Name << " : public WrapperClassHandler" << endl << "{" << endl;
		file << "public:" << endl;
		//default constructor
		file << "\t" << m_Name << "();" << endl; 
		//destructor
		file << "\tvirtual ~" << m_Name << "();" << endl; 
		file << "public:" << "//implementation of WrapperClassHandler interface" << endl;	
		file << "\tint Invoke(IMessageData* mc);" << endl; 		
		file << "\tvoid OnFault(IMessageData* pMsg);" << endl; 		
		file << "\tint Init();" << endl; 		
		file << "\tint Fini();" << endl; 	
		file << "private:" << "//Methods corresponding to the web service methods" << endl;
		file << "\tint SetResponseMethod(IMessageData* mc, const AxisChar* name);" << endl; 			
		//wrapper methods for each webservice method
		for (list<Method*>::iterator it = m_Methods.begin(); it != m_Methods.end(); it++)
		{
			(*it)->GenerateMethodDef(file);
		}
		file << "private:" << "// Actual web service object" << endl;
		file << "\t" << m_AWSName << " *pWs;" << endl; 
		file << "};" << endl;	
	}
	catch(...) //any exception
	{
		return 1;
	}
	return 0; //success
}

int WSClass::GenerateClassImpl(File &file)
{
	try {
		//default constructor
		file << m_Name << "::" << m_Name << "()" << endl;
		file << "{" << endl;
		file << "\tpWs = new " << m_AWSName << "();" << endl;
		file << "}" << endl;
		file << endl;
		//destructor
		file << m_Name << "::~" << m_Name << "()" << endl;
		file << "{" << endl;
		file << "\tdelete pWs;" << endl; 
		file << "}" << endl;
		file << endl;

		//implementation of WrapperClassHandler interface
		file << "// Implementation of WrapperClassHandler interfaces." << endl;
		file << "int " << m_Name << "::Invoke(IMessageData* mc)" << endl; 		
		file << "{" << endl;
		file << "\tIWrapperSoapDeSerializer* pIWSDZ = NULL;" << endl;
		file << "\tmc->getSoapDeSerializer(&pIWSDZ);" << endl;
		file << "\tif (!pIWSDZ) return FAIL;" << endl;
		file << "\tconst AxisChar* method = pIWSDZ->GetMethodName();" << endl;
		bool tab = true;
		list<Method*>::iterator it;
		for (it = m_Methods.begin(); it != m_Methods.end(); it++)
		{	
			if (tab) { file << "\t"; tab = false;} 
			file << "if (0 == strcmp(method, \"" << (*it)->GetName() << "\"))" << endl;
			file << "\t\treturn " << (*it)->GetName() << "(mc);" << endl;
			file << "\telse ";
		}
		file << "return FAIL;" << endl;
		file << "}" << endl;
		file << endl;

		file << "void " << m_Name << "::OnFault(IMessageData* pMsg)" << endl; 		
		file << "{" << endl;
		file << "}" << endl;
		file << endl;

		file << "int " << m_Name << "::Init()" << endl; 		
		file << "{" << endl;
		file << "\treturn 0;" << endl; 
		file << "}" << endl;
		file << endl;

		file << "int " << m_Name << "::Fini()" << endl; 	
		file << "{" << endl;
		file << "\treturn 0;" << endl; 
		file << "}" << endl;
		file << endl;

		file << "int " << m_Name << "::SetResponseMethod(IMessageData* mc, const AxisChar* name)" << endl; 			
		file << "{" << endl;
		file << "\tAxisString method = name;" << endl;
		file << "\tIWrapperSoapSerializer* pIWSSZ = NULL;" << endl;
		file << "\tmc->getSoapSerializer(&pIWSSZ);" << endl;
		file << "\tif (!pIWSSZ) return FAIL;" << endl;
		file << "\tISoapMethod* pMethod = pIWSSZ->createSoapMethod();" << endl;
		file << "\tpMethod->setLocalName(name);" << endl;
		file << "\tpMethod->setPrefix(pIWSSZ->getNewNamespacePrefix());"<< endl; 
		file << "\tpMethod->setUri(\"" << g_ClassNamespaces[m_AWSName] << "\");"<< endl; //http://www.opensource.lk will come from wsdd
		file << "\treturn SUCCESS;" << endl; 
		file << "}" << endl;
		file << endl;

		//wrapper methods for each webservice method
		for (it = m_Methods.begin(); it != m_Methods.end(); it++)
		{
			(*it)->GenerateMethodImpl(m_Name, file);
		}
	}
	catch(...) //any exception
	{
		return 1;
	}
	return 0; //success}
}

int WSClass::GenerateWSDLMessages(File &file)
{
	for (list<Method*>::iterator it = m_Methods.begin(); it != m_Methods.end(); it++)
	{
		if ((*it)->GenerateWSDLMessages(file)) return 1; //error occured;
	}
	return 0; //success;
}

int WSClass::GenerateWSDLPortTypes(File &file, string& sServiceName)
{
	file << "<portType name=\"" << sServiceName << "PortType\">" << endl;
	for (list<Method*>::iterator it = m_Methods.begin(); it != m_Methods.end(); it++)
	{
		if ((*it)->GenerateWSDLOperationInPortType(file)) return 1; //error occured;
	}
	file << "</portType>" << endl;
	return 0; //success;
}


int WSClass::GenerateOperationsInBinding(File &file, string &sServiceName, int nBinding, int nStyle, string &sURI)
{
	for (list<Method*>::iterator it = m_Methods.begin(); it != m_Methods.end(); it++)
	{
		if ((*it)->GenerateOperationInBinding(file, sServiceName, nBinding, nStyle, sURI)) return 1; //error occured;
	}
	return 0; //success
}
