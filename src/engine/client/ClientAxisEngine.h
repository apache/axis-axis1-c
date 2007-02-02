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
 */

/*
 * Revision 1.1  2004/08/26 roshan
 * Added the method "releaseHandlers(string sSessionId)" in order to release the
 *  Handlers once they are used.
 */

#if !defined(AXIS_CLIENTAXISENGINE_H__OF_AXIS_INCLUDED_)
#define AXIS_CLIENTAXISENGINE_H__OF_AXIS_INCLUDED_

#include "../AxisEngine.h"
/*
 *   @class ClientAxisEngine
 *   @brief
 *
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 */
AXIS_CPP_NAMESPACE_START
class ClientAxisEngine:public AxisEngine
{
    public:
        MessageData* getMessageData ();
        ClientAxisEngine ();
        virtual ~ ClientAxisEngine ();
        virtual int process (SOAPTransport* pSoap, bool noResponse);
        virtual int process (SOAPTransport* pSoap);
        
    protected:
        virtual int invoke (MessageData* pMsg, bool noResponse);
        virtual int invoke (MessageData* pMsg);
        virtual void onFault (MessageData* pMsg);
        
    private:
        void releaseHandlers(string sSessionId);
        SOAPTransport* m_pSoap;
};
AXIS_CPP_NAMESPACE_END
#endif 
