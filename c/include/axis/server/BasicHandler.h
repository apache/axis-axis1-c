/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#if !defined(_BASICHANDLER_H__OF_AXIS_INCLUDED_)
#define _BASICHANDLER_H__OF_AXIS_INCLUDED_

#include "IMessageData.h"
#include "GDefine.h"

enum HANDLER_TYPE { NORMAL_HANDLER, WEBSERVICE_HANDLER, CHAIN_HANDLER };

typedef struct 
{
    int (AXISCALL* invoke)(void* _object, void* pMsg);
    void (AXISCALL* onFault)(void* _object, void* pMsg);
    int (AXISCALL* init)(void* _object);
    int (AXISCALL* fini)(void* _object);
    int (AXISCALL* getType)(void* _object);
    AXIS_BINDING_STYLE (AXISCALL* getBindingStyle)(void* _object);
} BasicHandlerFunctions;

typedef struct 
{
    void* _object; 
    /* present only for interfaces passed from C to C++ (eg:BasicHandler) */
    BasicHandlerFunctions* _functions;
} BasicHandler;

#ifdef __cplusplus

class HandlerBase  
{
public:
    HandlerBase(){};
    virtual ~HandlerBase(){};
    virtual int AXISCALL invoke(void* pMsg)=0;
    virtual void AXISCALL onFault(void* mMsg)=0;
    virtual int AXISCALL init()=0;
    virtual int AXISCALL fini()=0;
    virtual int AXISCALL getType()=0;
};
#endif

#endif 


