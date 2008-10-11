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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <axis/GDefine.hpp>
#include <axis/INamespace.hpp>
#include <axis/AxisException.hpp>

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/INamespace.h>

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_USE

extern "C" {

AXISC_STORAGE_CLASS_INFO 
void axiscNamespaceDestroy(AXISCHANDLE iNamespace) 
{
    INamespace *ins = (INamespace*)iNamespace;
    
    try
    {
        delete ins;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}


AXISC_STORAGE_CLASS_INFO 
int axiscNamespaceSetURI(AXISCHANDLE iNamespace, 
                         const AxiscChar * uri) 
{
    INamespace *ins = (INamespace*)iNamespace;

    try
    {
        return ins->setURI(uri);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return AXISC_FAIL;
}


AXISC_STORAGE_CLASS_INFO 
int axiscNamespaceSetPrefix(AXISCHANDLE iNamespace, 
                             const AxiscChar * prefix) 
{
    INamespace *ins = (INamespace*)iNamespace;

    try
    {
        return ins->setPrefix(prefix);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return AXISC_FAIL;
}



AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscNamespaceGetURI(AXISCHANDLE iNamespace) 
{
    INamespace *ins = (INamespace*)iNamespace;

    try
    {
        return ins->getURI();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (const AxiscChar *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscNamespaceGetPrefix(AXISCHANDLE iNamespace) 
{
    INamespace *ins = (INamespace*)iNamespace;

    try
    {
        return ins->getPrefix();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (const AxiscChar *)NULL;    
}

}
