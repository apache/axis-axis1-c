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

// BeanClass.cpp: implementation of the BeanClass class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/wcg/BeanClass.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BeanClass::BeanClass()
{

}

BeanClass::~BeanClass()
{
	for (list<Variable*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
	{
		delete *it;
	}
}

void BeanClass::AddVariable(Variable *pVar)
{
	m_Variables.push_back(pVar);
}

void BeanClass::SetClassName(string &sName)
{
	m_Name = sName;
}

int BeanClass::GenerateSerializerAndDeSerializerImpl(File &file)
{
	list<Variable*>::iterator it;
	file << "//Parameters and wrapper methos to manipulate Point" << endl;
	file << "static const AxisChar* Axis_URI_" << m_Name << " = \"http://www.opensource.lk/" << m_Name << "\";" << endl;
	file << "static const AxisChar* Axis_TypeName_" << m_Name << " = \"" << m_Name << "\";" << endl;
	file << endl;
	file << "int Axis_DeSerialize_" << m_Name << "(" << m_Name << "* p, IWrapperSoapDeSerializer *pDZ)" << endl;
	file << "{" << endl;
	for (it = m_Variables.begin(); it != m_Variables.end(); it++)
	{
		(*it)->GenerateDeserializerImpl(file);
	}	
	file << "\treturn SUCCESS;" << endl;
	file << "}" << endl;
	file << endl;

	file << "int Axis_Serialize_" << m_Name <<  "(" << m_Name << "* p, IWrapperSoapSerializer& pSZ, bool bArray = false)" << endl;
	file << "{" << endl;
	file << "\tif (bArray)" << endl;
	file << "\t{" << endl;
	file << "\tpSZ << \"<\" << Axis_TypeName_" << m_Name << " << \">\";" << endl;
	file << "\t}" << endl;
	file << "\telse" << endl;
	file << "\t{" << endl;
	file << "\t\tconst AxisChar* sPrefix = pSZ.getNewNamespacePrefix();" << endl;
//	file << "\tm_URI = \"" << g_ClassNamespaces[m_Name] << "\";" << endl;
	file << "\t\tpSZ << \"<\" << Axis_TypeName_" << m_Name << "<< \" xsi:type=\\\"\" << sPrefix <<\":\" << Axis_TypeName_" << m_Name << " << \" xmlns:\" << sPrefix << \"=\\\"\" << Axis_URI_" << m_Name << " << \"\\\">\";" << endl;
	file << "\t}" << endl;
	for (it = m_Variables.begin(); it != m_Variables.end(); it++)
	{
		(*it)->GenerateSerializerImpl(file);
	}	
	file << "\tpSZ << \"</\" << Axis_TypeName_" << m_Name << " << \">\";" << endl;
	file << "\treturn SUCCESS;" << endl;
	file << "}" << endl;
	file << endl;
	file << "int Axis_GetSize_" << m_Name << "(" << m_Name << "* p)" << endl;
	file << "{" << endl;
	file << "\treturn sizeof(" << m_Name <<");" << endl;
	file << "}" << endl;
	file << endl;
	file << "void Axis_Delete_" << m_Name << "(" << m_Name << "* p, bool bArray = false, int nSize=0)" << endl;
	file << "{" << endl;
	file << "\tif (bArray)" << endl;
	file << "\t\tdelete [] p;" << endl;
	file << "else" << endl;
	file << "delete p;" << endl;
	file << "}" << endl;
	return 0;
}

int BeanClass::GenerateWSDLSchema(File &file)
{
	file << "<complexType name=\"" << m_Name << "\">" << endl;
	file << "<all>"<< endl;
	for (list<Variable*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
	{
		(*it)->GenerateWSDLSchema(file);
	}		
	file << "</all>" << endl;
	file << "</complexType>" << endl;
	return 0;
}
