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
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * AxisAdminService.cpp: implemtation for the AxisAdminService.
 *
 */

#include "AxisAdminService.h"
#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
AxisAdminService::AxisAdminService (const char *pchUri)
{
    m_pCall = new Call ();
    m_pCall->SetProtocol (APTHTTP);
    m_pCall->SetEndpointURI (pchUri);
}

AxisAdminService::~AxisAdminService ()
{
    delete m_pCall;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodupdateWSDD
 */
xsd__boolean AxisAdminService::updateWSDD (xsd__base64Binary Value0)
{
    xsd__boolean Ret;
    if (AXIS_SUCCESS != m_pCall->Initialize (CPP_DOC_PROVIDER, NORMAL_CHANNEL))
        return Ret;
    m_pCall->SetTransportProperty (SOAPACTION_HEADER, "AxisAdmin#updateWSDD");
    m_pCall->SetSOAPVersion (SOAP_VER_1_1);
    m_pCall->SetOperation ("updateWSDD", "http://www.opensource.lk/xsd");
    m_pCall->AddParameter ((void *) &Value0, "wsdd", XSD_BASE64BINARY);
    if (AXIS_SUCCESS == m_pCall->Invoke ())
    {
        if (AXIS_SUCCESS == m_pCall->CheckMessage ("updateWSDDResponse",
            "http://www.opensource.lk/xsd"))
        {
            Ret = m_pCall->GetElementAsBoolean ("return", 0);
        }
    }
    m_pCall->UnInitialize ();
    return Ret;
}
