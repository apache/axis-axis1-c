#ifdef WIN32
#pragma warning (disable : 4786)
#endif
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
// TranslationUnit.h: interface for the TranslationUnit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEADERFILE_H__322DAFBA_5048_4D34_9047_A93AEE351DD2__INCLUDED_)
#define AFX_HEADERFILE_H__322DAFBA_5048_4D34_9047_A93AEE351DD2__INCLUDED_

#include "WSClass.h"
#include "BeanClass.h"

#include <string>
#include <list>
using namespace std;

class TranslationUnit  
{
public:
	int GenerateWSDLBinding(File& file, string& sServiceName, int nBinding, int nStyle, int nTransport, string& sURI);
	int GenerateServiceFile(string& sServiceFile);
	void SetWsFileName(const char* sFileName);
	void AddBeanClass(BeanClass* pClass);
	void SetWSClass(WSClass* pClass);
	void AddNSDecl(string& sNSDecl);
	void AddInclude(string& sInclude);
	int GenerateWrapperClassImpl();
	int GenerateWrapperClassDef();
	int GenerateWSDL(string& sServiceFile, string& sURI);
	TranslationUnit();
	virtual ~TranslationUnit();
private:
	string m_sWsFileName;
	list<string> m_includes;
	list<string> m_nsdecls;
	WSClass *m_pWSClass; //there can be only one web service class per header file.
	list<BeanClass*> m_Beans;
};

#endif // !defined(AFX_HEADERFILE_H__322DAFBA_5048_4D34_9047_A93AEE351DD2__INCLUDED_)
