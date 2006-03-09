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

#include <axis/IAttribute.hpp>
#include <axis/AxisException.hpp>

#include "AxisObjectContainer.hpp"

AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/IAttribute.h>

AXISC_STORAGE_CLASS_INFO 
void axiscDestroyIAttribute(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;
    
    try
    {
        delete attr;
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
int axiscSetValueIAttribute(AXISCHANDLE attribute, 
                            const AxiscChar * value) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setValue(value);
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
int axiscSetUriIAttribute(AXISCHANDLE attribute, 
                          const AxiscChar * uri) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setURI(uri);
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
int axiscSetPrefixIAttribute(AXISCHANDLE attribute, 
                             const AxiscChar * prefix) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setPrefix(prefix);
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
int axiscSetLocalNameIAttribute(AXISCHANDLE attribute, 
                                const AxiscChar * localname) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setLocalName(localname);
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
const AxiscChar * axiscGetValueIAttribute(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getValue();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscGetUri(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getURI();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const AxiscChar *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscGetPrefixIAttribute(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getPrefix();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const AxiscChar *)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscGetLocalNameIAttribute(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getLocalName();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const AxiscChar *)NULL;    
}

}
