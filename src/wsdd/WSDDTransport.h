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


#if !defined(AXIS_WSDDTRANSPORT_H__OF_AXIS_INCLUDED_)
#define AXIS_WSDDTRANSPORT_H__OF_AXIS_INCLUDED_

#include "WSDDHandler.h"
#include <map>
/*
 *   @class WSDDTransport
 *   @brief interface for the WSDDTransport class.
 *   @author Susantha Kumara (skumara@virtusa.com)
 */

AXIS_CPP_NAMESPACE_START

using namespace std;

class WSDDTransport  
{
public:
    void addHandler(bool bRequestFlow, AXIS_PROTOCOL_TYPE protocol,
        WSDDHandler* pHandler);
    int removeHandler(bool bRequestFlow, AXIS_PROTOCOL_TYPE protocol,
        WSDDHandler* pHandler);
    const WSDDHandlerList* getResponseFlowHandlers
        (AXIS_PROTOCOL_TYPE Protocol);
    const WSDDHandlerList* getRequestFlowHandlers(AXIS_PROTOCOL_TYPE Protocol);
    WSDDTransport();
    virtual ~WSDDTransport();
    int updateWSDD(FILE* wsddfile, int tabcount);
private:
    map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>* m_RequestHandlers;
    map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>* m_ResponseHandlers;
};

AXIS_CPP_NAMESPACE_END

#endif 

