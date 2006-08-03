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
/**
 * @file BasicNode.hpp
 *
 */
#ifndef BASICNODE_INCLUDED
#define BASICNODE_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif


#include <axis/GDefine.h>
#include <axis/IAttribute.h>

/**
 * @enum NODE_TYPE
 *
 * Enumeration of support node types.
 */
typedef enum {
    /**
     * An XML element node
     */
    ELEMENT_NODE=1,
    /**
     * A text node
     */
    CHARACTER_NODE
    } AXISC_NODE_TYPE;

/**
 * @class BasicNode
 * @brief interface for the BasicNode class.
 *
 *
 */
/**
 * Returns the Attribute of this node, corresponding to the given
 * prefix/localname pair or the given namespace URI/localname pair.
 * The users could get the attributes with the
 * following combinations of pairs.
 *  1. by prefix and localname pair (here the namespace URI(i.e pachURI
 *      has to be a empty string)) or
 *  2. by namespace URI and localname pair (here the prefix
 *      (i.e pachPrefix has to be a empty string)).
 * The operation behavior depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetAttribute(AXISCHANDLE basicNode, AxiscChar * pachPrefix, 
	AxiscChar * pachURI, 
	AxiscChar * pachLocalname);

/**
 * Returns the first Attribute of this node. The operation
 * behavior depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetFirstAttribute(AXISCHANDLE basicNode);

/**
 * Returns the last Attribute of this node. The operation
 * behavior depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetLastAttribute(AXISCHANDLE basicNode);

/**
 * Returns the next Attribute of this node. The operation
 * behavior depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetNextAttribute(AXISCHANDLE basicNode);

/**
 * Returns the current Attribute of this node. The operation
 * behavior depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetCurrentAttribute(AXISCHANDLE basicNode);

/**
 * Creates an Attribute and adds it to this Basic Node.
 *
 * @param localname The local name of the attribute.
 * @param prefix The prefix of the attribute.
 * @param uri The namespace uri of the attribute.
 * @param value The value of the attribute.
 *
 * @return A pointer to the created Attribute will be returned.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeCreateAttribute(AXISCHANDLE basicNode, const AxiscChar * localname, 
	const AxiscChar * prefix, 
	const AxiscChar * uri, 
	const AxiscChar * value);

/**
 * Returns the local name of this node. The operation
 * behavior depends on the TYPE of the node.
 *
 * @return The localname of this element.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscBasicNodeGetLocalName(AXISCHANDLE basicNode);

/**
 * Returns the number of child elements of this element. The operation
 * behavior depends on the TYPE of the node.
 *
 * @return The number of child elements of this element. The return value
 * behavior depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
int axiscBasicNodeGetNoOfChildren(AXISCHANDLE basicNode);

/**
 * Gets the first Child Node of this Complex Element. The operation
 * behavior depends on the TYPE of the node.
 *
 * @return The first Child Node of this Element.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetFirstChildBasicNode(AXISCHANDLE basicNode);

/**
 * Gets the last Child Node of this Complex Element. The operation
 * behavior depends on the TYPE of the node.
 *
 * @return The last Child Node of this Element.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetLastChildBasicNode(AXISCHANDLE basicNode);

/**
 * Get the Child Node of the given position. The operation behavior
 * depends on the TYPE of the node.
 *
 * @param iChildPosition The child position.
 * @return The Child Node of the given position.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeGetChildBasicNode(AXISCHANDLE basicNode, int iChildPosition);

/**
 * Adds the given child node to this Element. The operation behavior
 * depends on the TYPE of the node.
 *
 * @param pBasicNode the child node to be added to this Element.
 * @return AXIS_SUCCESS to indicate successfull operation.
 */
AXISC_STORAGE_CLASS_INFO
int axiscBasicNodeAddChild(AXISCHANDLE basicNode, AXISCHANDLE pBasicNode);

/**
 * Gets the Node Type of the Element.
 *
 * @return The Node Type of the Element.
 */
AXISC_STORAGE_CLASS_INFO
AXISC_NODE_TYPE axiscBasicNodeGetNodeType(AXISCHANDLE basicNode);

/**
 * Gets and return the value of this Element. The operation behavior
 * depends on the TYPE of the node.
 *
 * @return The value of this Element.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscBasicNodeGetValue(AXISCHANDLE basicNode);

/**
 * Sets the value of this Element. The operation behavior
 * depends on the TYPE of the node.
 *
 * @param pachValue The value to be set
 * @return AXIS_SUCCESS to indicate success.
 */
AXISC_STORAGE_CLASS_INFO
int axiscBasicNodeSetValue(AXISCHANDLE basicNode, const AxiscChar * pachValue);

/**
 * Sets the namespace URI of this Element. The operation behavior
 * depends on the TYPE of the node.
 *
 * @param sURI the namespace URI of this Element.
 * @return AXIS_SUCCESS to indicate successfull operation.
 */
AXISC_STORAGE_CLASS_INFO
int axiscBasicNodeSetURI(AXISCHANDLE basicNode, const AxiscChar * sURI);

/**
 * Sets the local name of this Element. The operation behavior
 * depends on the TYPE of the node.
 *
 * @param sLocalName the local name of this Element.
 * @return AXIS_SUCCESS to indicate successfull operation.
 */
AXISC_STORAGE_CLASS_INFO
int axiscBasicNodeSetLocalName(AXISCHANDLE basicNode, const AxiscChar * sLocalName);

/**
 * Sets the prefix of this Element. The operation behavior
 * depends on the TYPE of the node.
 *
 * @param sPrefix the prefix of this Element.
 * @return AXIS_SUCCESS to indicate successfull operation.
 */
AXISC_STORAGE_CLASS_INFO
int axiscBasicNodeSetPrefix(AXISCHANDLE basicNode, const AxiscChar * sPrefix);

/**
 * Returns the namespace URI of this node.  The operation behavior
 * depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscBasicNodeGetURI(AXISCHANDLE basicNode);

/**
 * Returns the prefix  of this node.  The operation behavior
 * depends on the TYPE of the node.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscBasicNodeGetPrefix(AXISCHANDLE basicNode);

/**
 * Create a clone of the current BasicNode instance
 * @return clone of the current BasicNode instance
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscBasicNodeCloneBasicNode(AXISCHANDLE basicNode);

/**
 * Destructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscBasicNodeDestroy(AXISCHANDLE basicNode);


#ifdef __cplusplus
 }
#endif

#endif /* BASICNODE_INCLUDED */
