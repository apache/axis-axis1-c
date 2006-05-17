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

#include <axis/IHeaderBlock.hpp>
#include <axis/AxisException.hpp>

#include "AxisObjectContainer.hpp"

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/IHeaderBlock.h>

AXIS_CPP_NAMESPACE_USE

extern "C" {

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscHeaderBlockCreateNamespaceDeclINamespace(AXISCHANDLE headerBlock, 
                                               const AxiscChar * prefix, 
                                               const AxiscChar * uri) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return (AXISCHANDLE)(hdr->createNamespaceDecl(prefix,uri));
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
AXISCHANDLE axiscHeaderBlockGetFirstChildBasicNode(AXISCHANDLE headerBlock) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return (AXISCHANDLE)(hdr->getFirstChild());
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
int axiscHeaderBlockGetNoOfChildren(AXISCHANDLE headerBlock) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return hdr->getNoOfChildren();
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
AXISCHANDLE axiscHeaderBlockCreateChildBasicNode(AXISCHANDLE headerBlock, 
                                      AXISC_NODE_TYPE eNODE_TYPE, 
                                      AxiscChar * pachLocalName, 
                                      AxiscChar * pachPrefix, 
                                      AxiscChar * pachUri, 
                                      AxiscChar * pachValue) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        if (!pachLocalName && !pachPrefix && !pachUri && !pachValue)
           return (AXISCHANDLE)(hdr->createChild((NODE_TYPE)eNODE_TYPE));
        else
           return (AXISCHANDLE)(hdr->createChild((NODE_TYPE)eNODE_TYPE,pachLocalName,
                                              pachPrefix,pachUri,pachValue));
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
AXISCHANDLE axiscHeaderBlockCreateImmediateChildBasicNode(AXISCHANDLE headerBlock, 
                                               AXISC_NODE_TYPE eNODE_TYPE, 
                                               AxiscChar * pachLocalName, 
                                               AxiscChar * pachPrefix, 
                                               AxiscChar * pachUri, 
                                               AxiscChar * pachValue) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return (AXISCHANDLE)(hdr->createImmediateChild((NODE_TYPE)eNODE_TYPE,pachLocalName,
                                                        pachPrefix,pachUri,pachValue));

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
AXISCHANDLE axiscHeaderBlockCreateStdAttribute(AXISCHANDLE headerBlock, 
                                    AXISC_HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, 
                                    AXISC_SOAP_VERSION eSOAP_VERSION) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return (AXISCHANDLE)(hdr->createStdAttribute((HEADER_BLOCK_STD_ATTR_TYPE)eStdAttrType, 
                                                     (SOAP_VERSION)eSOAP_VERSION));
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
AXISCHANDLE axiscHeaderBlockCreateAttribute(AXISCHANDLE headerBlock, 
                                             const AxiscChar * localname, 
                                             const AxiscChar * prefix, 
                                             const AxiscChar * uri, 
                                             const AxiscChar * value) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        if (uri)
            return (AXISCHANDLE)(hdr->createAttribute(localname, prefix, uri, value));
        else
            return (AXISCHANDLE)(hdr->createAttribute(localname, prefix, value));
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
const AxiscChar * axiscHeaderBlockGetAttributeValue(AXISCHANDLE headerBlock, 
                                         const AxiscChar * localname, 
                                         const AxiscChar * prefix) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return hdr->getAttributeValue(localname, prefix);
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
AXISCHANDLE axiscHeaderBlockGetLastChildBasicNode(AXISCHANDLE headerBlock) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return (AXISCHANDLE)(hdr->getLastChild());
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
AXISCHANDLE axiscHeaderBlockGetChildBasicNode(AXISCHANDLE headerBlock, 
                                               int iChildPosition) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return (AXISCHANDLE)(hdr->getChild(iChildPosition));
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
int axiscHeaderBlockAddChild(AXISCHANDLE headerBlock, 
                              AXISCHANDLE pBasicNode) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return hdr->addChild((BasicNode*)pBasicNode);
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
int axiscHeaderBlockSetLocalName(AXISCHANDLE headerBlock, 
                                  const AxiscChar * localname) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return hdr->setLocalName(localname);
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
const AxiscChar * axiscHeaderBlockGetLocalName(AXISCHANDLE headerBlock) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return hdr->getLocalName();
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
int axiscHeaderBlockSetURI(AXISCHANDLE headerBlock, 
                             const AxiscChar * uri) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return hdr->setURI(uri);
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
int axiscHeaderBlockSetPrefix(AXISCHANDLE headerBlock, 
                               const AxiscChar * prefix) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return hdr->setPrefix(prefix);
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
AXISCHANDLE axiscHeaderBlockCloneHeaderBlock(AXISCHANDLE headerBlock) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        return (AXISCHANDLE)(hdr->clone());
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
void axiscHeaderBlockDestroy(AXISCHANDLE headerBlock) 
{
    IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;

    try
    {
        delete hdr;
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
