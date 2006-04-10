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
#include <axis/AxisUserAPIArrays.h>
#include <axis/BasicNode.h>

AXIS_CPP_NAMESPACE_USE

extern "C" {

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetAttribute(AXISCHANDLE basicNode, 
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
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetFirstAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;

    try
    {
        return bn->getFirstAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetLastAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getLastAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetNextAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getNextAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetCurrentAttribute(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getCurrentAttribute();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscCreateAttributeBasicNode(AXISCHANDLE basicNode, 
                                          const AxiscChar * localname, 
                                          const AxiscChar * prefix, 
                                          const AxiscChar * uri, 
                                          const AxiscChar * value) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->createAttribute(localname,prefix,uri,value);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;    
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscGetLocalNameBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getLocalName();
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
int axiscGetNoOfChildrenBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getNoOfChildren();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return -1;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetFirstChildBasicNodeBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getFirstChild();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetLastChildBasicNodeBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getLastChild();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetChildBasicNodeBasicNode(AXISCHANDLE basicNode, 
                                            int iChildPosition) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getChild(iChildPosition);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscAddChildBasicNode(AXISCHANDLE basicNode, 
                           AXISCHANDLE pBasicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->addChild((BasicNode*)pBasicNode);
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
AXISC_NODE_TYPE axiscGetNodeType(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return (AXISC_NODE_TYPE)bn->getNodeType();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    // Kind of screwed up that we need to give a real element type.
    return ::ELEMENT_NODE;
}

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscGetValueBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getValue();
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
int axiscSetValueBasicNode(AXISCHANDLE basicNode, 
                           const AxiscChar * pachValue) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setValue(pachValue);
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
int axiscSetURIBasicNode(AXISCHANDLE basicNode, 
                         const AxiscChar * sURI) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setURI(sURI);
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
int axiscSetLocalNameBasicNode(AXISCHANDLE basicNode, 
                               const AxiscChar * sLocalName) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setLocalName(sLocalName);
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
int axiscSetPrefixBasicNode(AXISCHANDLE basicNode, 
                            const AxiscChar * sPrefix) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->setPrefix(sPrefix);
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
const AxiscChar * axiscGetURIBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getURI();
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
const AxiscChar * axiscGetPrefixBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->getPrefix();
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
AXISCHANDLE axiscCloneBasicNodeBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        return bn->clone();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscDestroyBasicNode(AXISCHANDLE basicNode) 
{
    BasicNode *bn = (BasicNode*)basicNode;
    
    try
    {
        delete bn;
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

}

