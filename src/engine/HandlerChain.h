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
 */


#if !defined(_HANDLERCHAIN_H____OF_AXIS_INCLUDED_)
#define _HANDLERCHAIN_H____OF_AXIS_INCLUDED_

#include <axis/server/Handler.hpp>

/*
 *  @class HandlerChain
 *  @brief interface for the HandlerChain class.
 *  @author Susantha Kumara (skumara@virtusa.com)
 */

AXIS_CPP_NAMESPACE_START

class HandlerChain : public HandlerBase  
{
    friend class HandlerPool;
private:
    typedef struct ChainItem
    {
        BasicHandler* m_pHandler;
        int m_nScope;
        int m_nLibId;
    } ChainItem;
public:
    int addHandler(BasicHandler* pHandler, int nScope, int nLibId);
    HandlerChain();
    virtual ~HandlerChain();
    int AXISCALL invoke(void* pMsg);
    void AXISCALL onFault(void* pMsg);
    int AXISCALL getType(){return CHAIN_HANDLER;};
    int AXISCALL init();
    int AXISCALL fini();
    AXIS_BINDING_STYLE AXISCALL getBindingStyle(){ return RPC_ENCODED;}; 
    /* this is never called */

private:
    list<ChainItem> m_HandlerList;
    list<ChainItem>::iterator m_itCurrHandler;
};

AXIS_CPP_NAMESPACE_END

#endif 

