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
// HeaderFile.cpp: implementation of the HeaderFile class.
//
//////////////////////////////////////////////////////////////////////

#include "HeaderFile.h"
#include "File.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define WCID(X) "__WRAPPER_CLASS_" << X << "_INCLUDED__"

HeaderFile::HeaderFile()
{
	m_pWSClass = NULL;
}

HeaderFile::~HeaderFile()
{
	if (m_pWSClass) delete m_pWSClass;
	for (list<BeanClass*>::iterator it = m_Beans.begin(); it != m_Beans.end(); it++)
	{
		delete *it;
	}
}

int HeaderFile::GenerateWSDL()
{
	try {

	
	}
	catch(...) //any exception
	{
		return 1;
	}
	return 0; //success
}

int HeaderFile::GenerateWrapperClassDef()
{
	try {
		if (!m_pWSClass) return 1;
		string fname = m_pWSClass->GetName() + "Wrapper.hpp"; 
		File file(fname);
		file << "#if !defined " << WCID(m_pWSClass->GetName().c_str()) << endl;
		file << "#define " << WCID(m_pWSClass->GetName().c_str()) << endl;
		//add includes
		m_pWSClass->GenerateClassDef(file);
		file << "#endif" << endl;
	}
	catch(...) //any exception
	{
		return 1;
	}
	return 0; //success
}

int HeaderFile::GenerateWrapperClassImpl()
{
	try {

	
	}
	catch(...) //any exception
	{
		return 1;
	}
	return 0; //success
}

void HeaderFile::AddInclude(string &sInclude)
{
	m_includes.push_back(sInclude);
}

void HeaderFile::AddNSDecl(string &sNSDecl)
{
	m_nsdecls.push_back(sNSDecl);
}

void HeaderFile::SetWSClass(WSClass *pClass)
{
	m_pWSClass = pClass;
}

void HeaderFile::AddBeanClass(BeanClass *pClass)
{
	m_Beans.push_back(pClass);
}
