/* -*- C++ -*- */
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
 */

#ifdef WIN32
#pragma warning (disable : 4503)
#endif

#if !defined(AXIS_HANDLERPOOL_H__OF_AXIS_INCLUDED_)
#define AXIS_HANDLERPOOL_H__OF_AXIS_INCLUDED_

#include "../wsdd/WSDDHandler.h"
#include "../wsdd/WSDDService.h"
#include <axis/BasicHandler.hpp>
#include "HandlerLoader.h"
#include "HandlerChain.h"
#include "SharedObject.h"

#include <list>
#include <string>

AXIS_CPP_NAMESPACE_START

using namespace std;
/*
 *   @class HandlerPool
 *   @brief interface for the HandlerPool class.
 *
 *   HandlerPool loads, keeps and destroys all the handlers
 *
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
*/
class HandlerPool:protected SharedObject
{
    private:
        int getHandler (BasicHandler** ppHandler, string &sSessionId,
            int nScope, int nLibId);
        int poolHandler (string &sSessionId, BasicHandler* pHandler, int nScope,
            int nLibId);
        int getHandlerChain (string &sSessionId, HandlerChain** pChain,
            const WSDDHandlerList* pHandlerList);
    public:
        int getGlobalRequestFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId);
        int getGlobalResponseFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId);
        int getTransportRequestFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, AXIS_PROTOCOL_TYPE Protocol);
        int getTransportResponseFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, AXIS_PROTOCOL_TYPE Protocol);
        int getRequestFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, const WSDDService* pService);
        int getResponseFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, const WSDDService* pService);
        void poolHandlerChain (HandlerChain* pChain, string &sSessionId);
        int getWebService (BasicHandler** ppHandler, string &sSessionId,
            const WSDDHandler* pService);
        void poolWebService (string &sSessionId, BasicHandler* pHandler,
            const WSDDHandler* pHandlerInfo);

        HandlerPool ();
        virtual ~ HandlerPool ();
    private:
        list <HandlerChain*>m_ChainStore;
};

AXIS_CPP_NAMESPACE_END

#endif 
