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

#if !defined(__HANDLERLOADER_H_INCLUDED__)
#define __HANDLERLOADER_H_INCLUDED__

#include "../common/MessageData.h"
#include "../common/GDefine.h"
#include "../common/WrapperClassHandler.h"
#include "SharedObject.h"

#include <map>
#include <string>

using namespace std;

#define CREATE_FUNCTION "GetClassInstance"
#define DELETE_FUNCTION "DestroyInstance"

typedef int (* CREATE_OBJECT)(BasicHandler **inst);
typedef int (* DELETE_OBJECT)(BasicHandler *inst);

#ifdef WIN32
#include <windows.h>
#define DLHandler HINSTANCE
#define RTLD_LAZY 0
#else //Linux
#include <dlfcn.h>
#define DLHandler void*
#endif

//status codes
#define HANDLER_INIT_FAIL	1
#define CREATION_FAILED		2
#define LOADLIBRARY_FAILED	3
#define LIBRARY_PATH_EMPTY	4
#define HANDLER_NOT_LOADED	5
#define HANDLER_BEING_USED	6
#define GET_HANDLER_FAILED	7
#define WRONG_HANDLER_TYPE	8
#define NO_HANDLERS_CONFIGURED	9

class HandlerLoader : protected SharedObject
{
private:
	class HandlerInformation
	{
	public:
		string m_sLib;
		int m_nLoadOptions;
		DLHandler m_Handler;
		CREATE_OBJECT m_Create;
		DELETE_OBJECT m_Delete;
		int m_nObjCount;
	public:
		HandlerInformation()
		{
			m_sLib = "";
			m_nObjCount = 0;
		}
	};

	map<int, HandlerInformation*> m_HandlerInfoList;

public:
	int CreateHandler(BasicHandler** pHandler, int nLibId);
	int DeleteHandler(BasicHandler* pHandler, int nLibId);
	HandlerLoader();
	~HandlerLoader();
private:
	int LoadLib(HandlerInformation* pHandlerInfo);
	int UnloadLib(HandlerInformation* pHandlerInfo);
};


#endif //__HANDLERLOADER_H_INCLUDED__
