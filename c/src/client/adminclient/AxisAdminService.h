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
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * AxisAdminService.h: interface for the AxisAdminServiceclass.
 *
 */

#if !defined(__AXISADMINSERVICE_CLIENTSTUB_H__INCLUDED_)
#define __AXISADMINSERVICE_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Call.h>

class AxisAdminService
{
    private:
        Call * m_pCall;
    public:
        AxisAdminService (const char *pchUri);
    public:
        virtual ~ AxisAdminService ();
    public:
        xsd__boolean updateWSDD (xsd__base64Binary Value0);
};

#endif 
