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

#include "HandlerLoader.h"
#include <stdio.h>
#include "../common/Debug.h"

HandlerLoader::HandlerLoader(string &sFile, int nOptions)
{
	m_sLib = sFile.c_str();
	m_nLoadOptions = nOptions;
	m_Handler = 0;
	m_pClass = NULL;
}

HandlerLoader::~HandlerLoader()
{
	if (m_pClass)
		m_Delete(m_pClass);
	if (m_Handler != 0)
		UnloadLib(); 
}

int HandlerLoader::Initialize()
{
	if (0 == m_Handler)
	{    
    DEBUG1("if (0 == m_Handler):HandlerLoader::Initialize()");
            
		if (LoadLib())
		{      
			printf("LoadLib success\n");
			m_Create = GetCreate();
			m_Delete = GetDelete();
			if (!m_Create || !m_Delete)
			{
				printf("could not get function pointers\n");
				UnloadLib();
				m_Handler = 0;
				return FAIL;
			}
			m_Create(&m_pClass);
			return SUCCESS;
		}
		else 
		{
			printf("LoadLib failed\n");
			return FAIL;
		}
	}
	return SUCCESS;
}

int HandlerLoader::Invoke(MessageData *pMsg)
{
	if (m_pClass)
	{
		return m_pClass->Invoke(pMsg);
	}
	return FAIL;
}

int HandlerLoader::Finalize()
{
	m_Delete(m_pClass);
	m_pClass = NULL;
	UnloadLib();
	m_Handler = 0;
	return SUCCESS;
}

int HandlerLoader::LoadLib()
{
  
  DEBUG2("in HandlerLoader::LoadLib(), Lib is :", m_sLib.c_str());
   	
#ifdef WIN32
	m_Handler = LoadLibrary(m_sLib.c_str());
#else //Linux
  
	m_Handler = dlopen(m_sLib.c_str(), m_nLoadOptions);
  
  DEBUG1("after m_Handler = dlopen(m_sLib.c_str(), m_nLoadOptions);");
   
  
      	if (!m_Handler)
	{
    
		printf("Error is :%s\n",dlerror());
	}
  
#endif
	return (m_Handler != 0);
}

CREATE_OBJECT HandlerLoader::GetCreate()
{
#ifdef WIN32
	return (CREATE_OBJECT)GetProcAddress(m_Handler,CREATE_FUNCTION);
#else //Linux
	return (CREATE_OBJECT)dlsym(m_Handler,CREATE_FUNCTION);
#endif
}

DELETE_OBJECT HandlerLoader::GetDelete()
{
#ifdef WIN32
	return (DELETE_OBJECT)GetProcAddress(m_Handler,DELETE_FUNCTION);
#else //Linux
	return (DELETE_OBJECT)dlsym(m_Handler,DELETE_FUNCTION);
#endif
}

int HandlerLoader::UnloadLib()
{
#ifdef WIN32
	FreeLibrary(m_Handler);
#else //Linux
	dlclose(m_Handler);
#endif
	return SUCCESS;
}

BasicHandler* HandlerLoader::GetHandler()
{
	BasicHandler* pH = m_pClass;
	return pH;
}
