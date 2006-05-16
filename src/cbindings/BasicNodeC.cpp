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
#include <axis/BasicNode.hpp>
#include <axis/AxisException.hpp>

#include "AxisObjectContainer.hpp"

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>

AXIS_CPP_NAMESPACE_USE

extern "C" {

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetAttribute(AXISCHANDLE basicNode, 
                              AxiscChar * pachPrefix, 
                              AxiscChar * pachURI, 
                              AxiscChar * pachLocalname) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getAttribute(pachPrefix,pachURI,pachLocalname);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetFirstAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;

    try
    {
        return bn->getFirstAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetLastAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getLastAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetNextAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getNextAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetCurrentAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getCurrentAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeCreateAttribute(AXISCHANDLE basicNode, 
                                          const AxiscChar * localname, 
                                          const AxiscChar * prefix, 
                                          const AxiscChar * uri, 
                                          const AxiscChar * value) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        if (uri == NULL && prefix == NULL)
           return bn->createAttribute(localname,value);
        else if (uri == NULL)
           return bn->createAttribute(localname,prefix, value);
        else
           return bn->createAttribute(localname,prefix, uri, value);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscBasicNodeGetLocalName(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getLocalName();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar *)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
int axiscBasicNodeGetNoOfChildren(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getNoOfChildren();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return -1;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetFirstChild(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getFirstChild();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetLastChild(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getLastChild();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeGetChild(AXISCHANDLE basicNode, 
                                            int iChildPosition) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getChild(iChildPosition);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscBasicNodeAddChild(AXISCHANDLE basicNode, 
                           AXISCHANDLE pBasicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->addChild((BasicNode*)pBasicNode);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
AXISC_NODE_TYPE axiscBasicNodeGetNodeType(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return (AXISC_NODE_TYPE)bn->getNodeType();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    // Kind of screwed up that we need to give a real element type.
    return ::ELEMENT_NODE;
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscBasicNodeGetValue(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getValue();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscBasicNodeSetValue(AXISCHANDLE basicNode, 
                           const AxiscChar * pachValue) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setValue(pachValue);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscBasicNodeSetURI(AXISCHANDLE basicNode, 
                         const AxiscChar * sURI) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setURI(sURI);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;    
}

AXISC_STORAGE_CLASS_INFO 
int axiscBasicNodeSetLocalName(AXISCHANDLE basicNode, 
                               const AxiscChar * sLocalName) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setLocalName(sLocalName);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;           
}

AXISC_STORAGE_CLASS_INFO 
int axiscBasicNodeSetPrefix(AXISCHANDLE basicNode, 
                            const AxiscChar * sPrefix) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setPrefix(sPrefix);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;    
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscBasicNodeGetURI(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getURI();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscBasicNodeGetPrefix(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getPrefix();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscBasicNodeClone(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->clone();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscBasicNodeDestroy(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        delete bn;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }    
}

}

