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

#include <axis/IAttribute.hpp>
#include <axis/AxisException.hpp>

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/IAttribute.h>

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_USE

extern "C" {

AXISC_STORAGE_CLASS_INFO 
void axiscAttributeDestroy(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;
    
    try
    {
        delete attr;
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
int axiscAttributeSetValue(AXISCHANDLE attribute, 
                            const AxiscChar * value) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setValue(value);
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
int axiscAttributeSetURI(AXISCHANDLE attribute, 
                          const AxiscChar * uri) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setURI(uri);
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
int axiscAttributeSetPrefix(AXISCHANDLE attribute, 
                             const AxiscChar * prefix) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setPrefix(prefix);
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
int axiscAttributeSetLocalName(AXISCHANDLE attribute, 
                                const AxiscChar * localname) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->setLocalName(localname);
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
const AxiscChar * axiscAttributeGetValue(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getValue();
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
const AxiscChar * axiscAttributeGetURI(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getURI();
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
const AxiscChar * axiscAttributeGetPrefix(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getPrefix();
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
const AxiscChar * axiscAttributeGetLocalName(AXISCHANDLE attribute) 
{
    IAttribute *attr = (IAttribute*)attribute;

    try
    {
        return attr->getLocalName();
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
