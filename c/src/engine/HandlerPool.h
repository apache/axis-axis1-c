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

#if !defined(AXIS_HANDLERPOOL_H__INCLUDED_)
#define AXIS_HANDLERPOOL_H__INCLUDED_

#include <axis/server/WSDDHandler.h>
#include <axis/server/WSDDService.h>
#include <axis/server/BasicHandler.h>
#include "HandlerLoader.h"
#include <axis/server/HandlerChain.h>
#include "SharedObject.h"

#include <list>
#include <string>

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
        int GetHandler (BasicHandler** ppHandler, string &sSessionId,
            int nScope, int nLibId);
        int PoolHandler (string &sSessionId, BasicHandler* pHandler, int nScope,
            int nLibId);
        int GetHandlerChain (string &sSessionId, HandlerChain** pChain,
            const WSDDHandlerList* pHandlerList);
    public:
        int GetGlobalRequestFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId);
        int GetGlobalResponseFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId);
        int GetTransportRequestFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, AXIS_PROTOCOL_TYPE Protocol);
        int GetTransportResponseFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, AXIS_PROTOCOL_TYPE Protocol);
        int GetRequestFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, const WSDDService* pService);
        int GetResponseFlowHandlerChain (HandlerChain** ppChain,
            string &sSessionId, const WSDDService* pService);
        void PoolHandlerChain (HandlerChain* pChain, string &sSessionId);
        int GetWebService (BasicHandler** ppHandler, string &sSessionId,
            const WSDDHandler* pService);
        void PoolWebService (string &sSessionId, BasicHandler* pHandler,
            const WSDDHandler* pHandlerInfo);

        HandlerPool ();
        virtual ~ HandlerPool ();
    private:
        list <HandlerChain*>m_ChainStore;
};

#endif 
