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
#include <axis/server/AxisWrapperAPI.hpp>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
AxisAdminService::AxisAdminService (const char *pchUri)
{
    m_pCall = new Call ();
    m_pCall->setProtocol (APTHTTP);
    m_pCall->setEndpointURI (pchUri);
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
    if (AXIS_SUCCESS != m_pCall->initialize (CPP_DOC_PROVIDER, NORMAL_CHANNEL))
        return Ret;
    m_pCall->setTransportProperty (SOAPACTION_HEADER, "AxisAdmin#updateWSDD");
    m_pCall->setSOAPVersion (SOAP_VER_1_1);
    m_pCall->setOperation ("updateWSDD", "http://www.opensource.lk/xsd");
    m_pCall->addParameter ((void *) &Value0, "wsdd", XSD_BASE64BINARY);
    if (AXIS_SUCCESS == m_pCall->invoke ())
    {
        if (AXIS_SUCCESS == m_pCall->checkMessage ("updateWSDDResponse",
            "http://www.opensource.lk/xsd"))
        {
            Ret = m_pCall->getElementAsBoolean ("return", 0);
        }
    }
    m_pCall->unInitialize ();
    return Ret;
}
