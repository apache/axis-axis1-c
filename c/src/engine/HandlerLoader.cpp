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
#include "../common/AxisTrace.h"
#include "../common/AxisUtils.h"
#include "../wsdd/WSDDDeployment.h"

extern WSDDDeployment* g_pWSDDDeployment;

HandlerLoader::HandlerLoader()
{
}

HandlerLoader::~HandlerLoader()
{
	lock();
	HandlerInformation* pHandlerInfo = NULL;
	for (map<int, HandlerInformation*>::iterator it = m_HandlerInfoList.begin(); it != m_HandlerInfoList.end(); it++)
	{
		pHandlerInfo = (*it).second;
		if (pHandlerInfo->m_nObjCount != 0); //it seems that some objects created have not been deleted - unexpected
		UnloadLib(pHandlerInfo);
		delete pHandlerInfo;
	}
	unlock();
}

int HandlerLoader::DeleteHandler(BasicHandler* pHandler, int nLibId)
{
	lock();
	if (m_HandlerInfoList.find(nLibId) != m_HandlerInfoList.end())
	{
		HandlerInformation* pHandlerInfo = m_HandlerInfoList[nLibId];
		pHandlerInfo->m_nObjCount--;
		pHandlerInfo->m_Delete(pHandler);
		if (pHandlerInfo->m_nObjCount == 0); //time to unload the DLL
		unlock();
		return SUCCESS;
	}
	else
	{
		unlock();
		return HANDLER_NOT_LOADED;
	}
}

int HandlerLoader::LoadLib(HandlerInformation* pHandlerInfo)
{
	AXISTRACE2("in HandlerLoader::LoadLib(), Lib is :", pHandlerInfo->m_sLib.c_str());
#ifdef WIN32
	pHandlerInfo->m_Handler = LoadLibrary(pHandlerInfo->m_sLib.c_str());
#else //Linux
	pHandlerInfo->m_Handler = dlopen(pHandlerInfo->m_sLib.c_str(), pHandlerInfo->m_nLoadOptions);
	AXISTRACE1("after m_Handler = dlopen(pHandlerInfo->m_sLib.c_str(), pHandlerInfo->m_nLoadOptions);");  
#endif
	return (pHandlerInfo->m_Handler != 0)?SUCCESS:FAIL;
}

int HandlerLoader::UnloadLib(HandlerInformation* pHandlerInfo)
{
#ifdef WIN32
	FreeLibrary(pHandlerInfo->m_Handler);
#else //Linux
	dlclose(pHandlerInfo->m_Handler);
#endif
	return SUCCESS;
}

int HandlerLoader::CreateHandler(BasicHandler** pHandler, int nLibId)
{
	AXISTRACE1("inside CreateHandler\n");
	lock();
	*pHandler = NULL;
	HandlerInformation* pHandlerInfo = NULL;
	if (m_HandlerInfoList.find(nLibId) == m_HandlerInfoList.end())
	{
		pHandlerInfo = new HandlerInformation();
		pHandlerInfo->m_sLib = g_pWSDDDeployment->GetLibName(nLibId);
		if (pHandlerInfo->m_sLib.empty())
		{
			delete pHandlerInfo;
			unlock();
			return LIBRARY_PATH_EMPTY;
		}
		pHandlerInfo->m_nLoadOptions = RTLD_LAZY;
		if (SUCCESS == LoadLib(pHandlerInfo))
		{  
			#ifdef WIN32
			pHandlerInfo->m_Create = (CREATE_OBJECT)GetProcAddress(pHandlerInfo->m_Handler,CREATE_FUNCTION);
			pHandlerInfo->m_Delete = (DELETE_OBJECT)GetProcAddress(pHandlerInfo->m_Handler,DELETE_FUNCTION);
			#else //Linux
			pHandlerInfo->m_Create = (CREATE_OBJECT)dlsym(pHandlerInfo->m_Handler,CREATE_FUNCTION);
			pHandlerInfo->m_Delete = (DELETE_OBJECT)dlsym(pHandlerInfo->m_Handler,DELETE_FUNCTION);
			#endif		
			if (!pHandlerInfo->m_Create || !pHandlerInfo->m_Delete)
			{
				UnloadLib(pHandlerInfo);
				delete pHandlerInfo;
				unlock();
				return LOADLIBRARY_FAILED;
			}
			else //success
			{
                AXISTRACE1("handler create success");
				m_HandlerInfoList[nLibId] = pHandlerInfo;
			}
		}
		else 
		{
			unlock();
			return LOADLIBRARY_FAILED;
		}
	}
	
	pHandlerInfo = m_HandlerInfoList[nLibId];
	BasicHandler* pBH = NULL;
	pHandlerInfo->m_Create(&pBH);
    AXISTRACE1("pHandlerInfo->m_Create(&pBH);");
	if (pBH)
	{
		if (SUCCESS == pBH->Init())
		{
			pHandlerInfo->m_nObjCount++;
			*pHandler = pBH;
            AXISTRACE1("*pHandler = pBH;");
			unlock();
			return SUCCESS;
		}
		else
		{
			pBH->Fini();
			delete pBH;
			unlock();
			return HANDLER_INIT_FAIL;
		}
	}
	else
	{
		unlock();
		return CREATION_FAILED;
	}
}
