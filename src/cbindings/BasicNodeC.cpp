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
#include <axis/BasicNode.hpp>
AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetAttribute(AXISCHANDLE basicNode, AxiscChar * pachPrefix, 
	AxiscChar * pachURI, AxiscChar * pachLocalname) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getAttribute(pachPrefix,pachURI,pachLocalname);
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetFirstAttribute(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getFirstAttribute();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetLastAttribute(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getLastAttribute();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetNextAttribute(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getNextAttribute();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetCurrentAttribute(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getCurrentAttribute();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateAttributeBasicNode(AXISCHANDLE basicNode, const AxiscChar * localname, 
	const AxiscChar * prefix, const AxiscChar * uri, const AxiscChar * value) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->createAttribute(localname,prefix,uri,value);
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetLocalNameBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getLocalName();
}

AXISC_STORAGE_CLASS_INFO int axiscGetNoOfChildrenBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getNoOfChildren();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetFirstChildBasicNodeBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getFirstChild();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetLastChildBasicNodeBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getLastChild();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetChildBasicNodeBasicNode(AXISCHANDLE basicNode, int iChildPosition) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getChild(iChildPosition);
}

AXISC_STORAGE_CLASS_INFO int axiscAddChildBasicNode(AXISCHANDLE basicNode, AXISCHANDLE pBasicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->addChild((BasicNode*)pBasicNode);
}

AXISC_STORAGE_CLASS_INFO AXISC_NODE_TYPE axiscGetNodeType(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return (AXISC_NODE_TYPE)bn->getNodeType();
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetValueBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getValue();
}

AXISC_STORAGE_CLASS_INFO int axiscSetValueBasicNode(AXISCHANDLE basicNode, const AxiscChar * pachValue) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->setValue(pachValue);
}

AXISC_STORAGE_CLASS_INFO int axiscSetURIBasicNode(AXISCHANDLE basicNode, const AxiscChar * sURI) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->setURI(sURI);
}

AXISC_STORAGE_CLASS_INFO int axiscSetLocalNameBasicNode(AXISCHANDLE basicNode, const AxiscChar * sLocalName) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->setLocalName(sLocalName);
}

AXISC_STORAGE_CLASS_INFO int axiscSetPrefixBasicNode(AXISCHANDLE basicNode, const AxiscChar * sPrefix) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->setPrefix(sPrefix);
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetURIBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getURI();
}

AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetPrefixBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->getPrefix();
}

AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCloneBasicNodeBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	return bn->clone();
}

AXISC_STORAGE_CLASS_INFO void axiscDestroyBasicNode(AXISCHANDLE basicNode) {
	BasicNode *bn = (BasicNode*)basicNode;
	delete bn;
}

}

