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

#if !defined(AXIS_CLIENTAXISENGINE_H__INCLUDED_)
#define AXIS_CLIENTAXISENGINE_H__INCLUDED_

#include <axis/server/AxisEngine.h>
/*
 *   @class ClientAxisEngine
 *   @brief
 *
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 */
class ClientAxisEngine:public AxisEngine
{
    public:
        MessageData* GetMessageData ();
        ClientAxisEngine ();
        virtual ~ ClientAxisEngine ();
        virtual int Process (Ax_soapstream* pSoap);
    protected:
        virtual int Invoke (MessageData* pMsg);
        virtual void OnFault (MessageData* pMsg);
    private:
        Ax_soapstream* m_pSoap;
        char* get_service_name (const char* pch_uri_path);
};

#endif 
