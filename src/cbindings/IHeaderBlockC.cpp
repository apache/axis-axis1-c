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

#include <axis/IHeaderBlock.hpp>
AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/IHeaderBlock.h>

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateNamespaceDeclINamespace(AXISCHANDLE headerBlock, const AxiscChar * prefix, 
	const AxiscChar * uri) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->createNamespaceDecl(prefix,uri));
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetFirstChildBasicNodeIHeaderBlock(AXISCHANDLE headerBlock) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->getFirstChild());
}

AXISC_STORAGE_CLASS_INFO int axiscGetNoOfChildrenIHeaderBlock(AXISCHANDLE headerBlock) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return hdr->getNoOfChildren();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateChildBasicNode(AXISCHANDLE headerBlock, AXISC_NODE_TYPE eNODE_TYPE, 
	AxiscChar * pachLocalName, AxiscChar * pachPrefix, 
	AxiscChar * pachUri, AxiscChar * pachValue) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->createChild((NODE_TYPE)eNODE_TYPE,pachLocalName,pachPrefix,pachUri,pachValue));
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateImmediateChildBasicNode(AXISCHANDLE headerBlock, AXISC_NODE_TYPE eNODE_TYPE, 
	AxiscChar * pachLocalName, AxiscChar * pachPrefix, 
	AxiscChar * pachUri, AxiscChar * pachValue) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->createImmediateChild((NODE_TYPE)eNODE_TYPE,pachLocalName,pachPrefix,pachUri,pachValue));
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateStdAttribute(AXISCHANDLE headerBlock, AXISC_HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, 
	AXISC_SOAP_VERSION eSOAP_VERSION) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->createStdAttribute((HEADER_BLOCK_STD_ATTR_TYPE)eStdAttrType, (SOAP_VERSION)eSOAP_VERSION));
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateAttributeIHeaderBlock(AXISCHANDLE headerBlock, const AxiscChar * localname, 
	const AxiscChar * prefix, const AxiscChar * uri, const AxiscChar * value) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->createAttribute(localname, prefix, uri, value));
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetAttributeValue(AXISCHANDLE headerBlock, const AxiscChar * localname, 
	const AxiscChar * prefix) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return hdr->getAttributeValue(localname, prefix);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetLastChildBasicNodeIHeaderBlock(AXISCHANDLE headerBlock) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->getLastChild());
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetChildBasicNodeIHeaderBlock(AXISCHANDLE headerBlock, int iChildPosition) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->getChild(iChildPosition));
}

AXISC_STORAGE_CLASS_INFO int axiscAddChildIHeaderBlock(AXISCHANDLE headerBlock, AXISCHANDLE pBasicNode) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return hdr->addChild((BasicNode*)pBasicNode);
}

AXISC_STORAGE_CLASS_INFO int axiscSetLocalNameIHeaderBlock(AXISCHANDLE headerBlock, const AxiscChar * localname) 
{
	if(0==localname)
	{
		return AXIS_FAIL;
	}
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	hdr->setLocalName(localname);
	return AXIS_SUCCESS;
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetLocalNameIHeaderBlock(AXISCHANDLE headerBlock) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return hdr->getLocalName();
}

AXISC_STORAGE_CLASS_INFO void axiscSetUriIHeaderBlock(AXISCHANDLE headerBlock, const AxiscChar * uri) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	hdr->setURI(uri);
}

AXISC_STORAGE_CLASS_INFO int axiscSetPrefixIHeaderBlock(AXISCHANDLE headerBlock, const AxiscChar * prefix) {
	if(0==prefix)
	{
		return AXIS_FAIL;
	}
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	hdr->setPrefix(prefix);
	return AXIS_SUCCESS;
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCloneHeaderBlockIHeaderBlock(AXISCHANDLE headerBlock) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	return (AXISCHANDLE)(hdr->clone());
}

AXISC_STORAGE_CLASS_INFO void axiscDestroyIHeaderBlock(AXISCHANDLE headerBlock) {
	IHeaderBlock *hdr = (IHeaderBlock*)headerBlock;
	delete hdr;
}

}
