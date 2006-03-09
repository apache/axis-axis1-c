/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

#include <axis/ISoapFault.hpp>
#include <axis/AxisException.hpp>

#include "AxisObjectContainer.hpp"

AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/ISoapFault.h>

AXISC_STORAGE_CLASS_INFO 
void axiscDestroyISoapFault(AXISCHANDLE soapFault) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        delete sf;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar* axiscGetCmplxFaultObjectName(AXISCHANDLE soapFault) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->getCmplxFaultObjectName();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar*)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void * axiscGetCmplxFaultObject(AXISCHANDLE soapFault, 
                                void * pDZFunct, 
                                void * pCreFunct, 
                                void * pDelFunct, 
                                const AxiscChar * pName, 
                                const AxiscChar * pNamespace) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->getCmplxFaultObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (void *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar* axiscGetSimpleFaultDetail(AXISCHANDLE soapFault) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->getSimpleFaultDetail();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const AxiscChar*)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar* axiscGetFaultcode(AXISCHANDLE soapFault) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->getFaultcode();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const AxiscChar*)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar* axiscGetFaultstring(AXISCHANDLE soapFault) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->getFaultstring();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const AxiscChar*)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar* axiscGetFaultactor(AXISCHANDLE soapFault) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->getFaultactor();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const AxiscChar*)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
int axiscSetFaultcode(AXISCHANDLE soapFault, 
                      const AxisChar*  sFaultcode) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->setFaultcode(sFaultcode);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscSetFaultstring(AXISCHANDLE soapFault, 
                        const AxisChar*  sFaultstring) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->setFaultstring(sFaultstring);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscSetFaultactor(AXISCHANDLE soapFault, 
                       const AxisChar*  sFaultactor) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->setFaultactor(sFaultactor);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscSetFaultDetail(AXISCHANDLE soapFault, 
                        const AxisChar*  sFaultdetail) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->setFaultDetail(sFaultdetail);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscSetCmplxFaultObject(AXISCHANDLE soapFault, 
                             const void * pCmplxFaultObject) 
{
    ISoapFault *sf = (ISoapFault*)soapFault;

    try
    {
        return sf->setCmplxFaultObject(pCmplxFaultObject);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return AXISC_FAIL;
}

}
