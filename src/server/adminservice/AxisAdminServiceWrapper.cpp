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
 * This is the Service implementation CPP file genarated by theWSDL2Ws.
 * AxisAdminServiceWrapper.cpp: implemtation for the AxisAdminServiceWrapper.
 * 
 */

#include "AxisAdminServiceWrapper.h"

AxisAdminServiceWrapper::AxisAdminServiceWrapper ()
{
}

AxisAdminServiceWrapper::~AxisAdminServiceWrapper ()
{
}

/* Implementation of WrapperClassHandler interface */
void AxisAdminServiceWrapper::OnFault (void* pMsg)
{
}

int AxisAdminServiceWrapper::Init ()
{
    return AXIS_SUCCESS;
}

int AxisAdminServiceWrapper::Fini ()
{
    return AXIS_SUCCESS;
}


/*
 * This method invokes the right service method 
 */
int AxisAdminServiceWrapper::Invoke (void* pMsg)
{
    IMessageData* mc = (IMessageData*) pMsg;
    const AxisChar* method = mc->GetOperationName ();
    if (0 == strcmp (method, "updateWSDD"))
        return updateWSDD (mc);
    else
        return AXIS_FAIL;
}


/* Methods corresponding to the web service methods */

/*
 * This method wrap the service method 
 */
int AxisAdminServiceWrapper::updateWSDD (void* pMsg)
{
    IMessageData* mc = (IMessageData*) pMsg;
    int nStatus;
    IWrapperSoapSerializer* pIWSSZ = NULL;
    mc->GetSoapSerializer (&pIWSSZ);
    if (!pIWSSZ)
        return AXIS_FAIL;
    IWrapperSoapDeSerializer* pIWSDZ = NULL;
    mc->GetSoapDeSerializer (&pIWSDZ);
    if (!pIWSDZ)
        return AXIS_FAIL;
    /* check whether we have got correct message */
    if (AXIS_SUCCESS !=
        pIWSDZ->CheckMessageBody ("updateWSDD", "http://www.opensource.lk/xsd"))
        return AXIS_FAIL;
    pIWSSZ->CreateSoapMethod ("updateWSDDResponse",
        "http://www.opensource.lk/xsd");
    xsd__base64Binary v0 = pIWSDZ->GetElementAsBase64Binary ("wsdd", 0);
    if (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus ()))
        return nStatus;
    xsd__boolean ret = false_;
    IAdminUtils* pAdminUtils;
    mc->GetAdminUtils (&pAdminUtils);
    if (pAdminUtils)
    {
        if (AXIS_SUCCESS == pAdminUtils->UpdateWSDD ((char*) v0.__ptr))
              ret = true_;
    }
    return pIWSSZ->AddOutputParam ("return", (void*) &ret, XSD_BOOLEAN);
}
