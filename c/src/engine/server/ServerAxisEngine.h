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

#if !defined(AXIS_SERVERAXISENGINE_H__INCLUDED_)
#define AXIS_SERVERAXISENGINE_H__INCLUDED_

#include <axis/server/AxisEngine.h>
/*
 *  @class ServerAxisEngine
 *  @brief interface for the ServerAxisEngine class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com)
 */
class ServerAxisEngine:public AxisEngine
{
    private:
        BasicHandler* m_pWebService;
    public:
        ServerAxisEngine ();
        virtual ~ ServerAxisEngine ();
    public:
        int Process (Ax_soapstream* soap);
    protected:
        virtual int Invoke (MessageData* pMsg);
        virtual void OnFault (MessageData* pMsg);
};

#endif 
