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
#ifndef IHEADERBLOCK_INCLUDED
#define IHEADERBLOCK_INCLUDED

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


#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/IAttribute.h>
#include <axis/INamespace.h>

/**
 * @file IHeaderBlock.hpp
 */
/**
 * @enum HEADER_BLOCK_STD_ATTR_TYPE
 * Enumeration of standard header block attributes.
 */
typedef enum 
{   
    /**
     * (SOAP 1.2 only) The role attribute set as next.
     * The value will be set as "http://www.w3.org/2003/05/soap-envelope/role/next"
     */
    ROLE_NEXT=1,
    
    /**
     * (SOAP 1.2 only) The role attribute set as none.
     * The value will be set as "http://www.w3.org/2003/05/soap-envelope/role/none"
     */
    ROLE_NONE=2,
    
    /**
     * (SOAP 1.2 only) The role attribute set as ultimateReceiver
     * The value will be set as "http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver"
     */
    ROLE_ULTIMATE_RECEIVER=3,
    
    /**
     * (SOAP 1.1 only) The actor attribute
     */
    ACTOR=4,

    /**
     * The mustUnderstand attribute set as true.
     * For SOAP 1.1 - the value will be set as "1".
     * For SOAP 1.2 - the value will be set as "true".
     */
    MUST_UNDERSTAND_TRUE= 5,
    /**
     * The mustUnderstand attribute set as false.
     * For SOAP 1.1 - the value will be set as "0".
     * For SOAP 1.2 - the value will be set as "false".
     */
    MUST_UNDERSTAND_FALSE=6
} AXISC_HEADER_BLOCK_STD_ATTR_TYPE;

/**
 *  @class IHeaderBlock
 *  @brief interface for the IHeaderBlock class.
 *
 *
 */
/**
 * Creates a Attribute and adds it to this Header Block as a namespace.
 *
 * @param prefix The prefix of the attribute.
 * @param uri The namespace uri of the attribute.
 *
 * @return A pointer to the created Attribute will be returned.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockCreateNamespaceDeclINamespace(AXISCHANDLE headerBlock, const AxiscChar * prefix, 
	const AxiscChar * uri);

/**
 * Retyrbs the first child element of this Header Block.
 *
 * @return A pointer to the first child element of this Header Block.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockGetFirstChildBasicNode(AXISCHANDLE headerBlock);

/**
 * Returns the number of child elements of this HeaderBlock.
 *
 * @return The number of child elements of this HeaderBlock.
 */
AXISC_STORAGE_CLASS_INFO
int axiscHeaderBlockGetNoOfChildren(AXISCHANDLE headerBlock);

/**
 * Creates a child node depending on the given node type. i.e:
 * if node type == CHARACTER_NODE then it creates a Character Element.
 * if node type == ELEMENT_NODE then it creates a Complex Element.
 * This method doesn't add the created child to this Header Block. If the
 * user needs to add this created child then he has to use the
 * addChild(BasicNode *pBasicNode) method after creating the child.
 * If the node to be created is a CHARACTER_NODE then only the parameter
 * pachValue will be usefull and for others you can provide NULL.
 * If the node to be created is a ELEMENT_NODE then the parameters
 * pachLocalName, pachPrefix, pachUri will be needed to provide and you
 * can provide NULL for the pachValue.
 *
 * @param eNODE_TYPE The node type to be created, i.e CHARACTER_NODE or
 * ELEMENT_NODE.
 * @param pachLocalName The local name of the child node. A CHARACTER_NODE
 * will ignore this.
 * @param pachPrefix The prefix of the child node. A CHARACTER_NODE
 * will ignore this.
 * @param pachUri The namespace uri of the child node. A CHARACTER_NODE
 * will ignore this.
 * @param pachValue The value of the child node. A ELEMENT_NODE
 * will ignore this.
 *
 * @return The child node created will be returned if the creation is
 * successfull. If the creation is unsccessfull it will return NULL.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockCreateChildBasicNode(AXISCHANDLE headerBlock, AXISC_NODE_TYPE eNODE_TYPE, 
	AxiscChar * pachLocalName, 
	AxiscChar * pachPrefix, 
	AxiscChar * pachUri, 
	AxiscChar * pachValue);

/**
 * Creates a child node depending on the given type. If the type is
 *  CHARACTER_NODE a CharacterElement is created. If the type is
 *  ELEMENT_NODE a ComplexElement is created. After creating the child it
 *  will be added as a immediate child to the header block.
 *  It is important to note that if the type is CHARACTER_NODE only the
 *  NODE_TYPE and value (pachValue) parameters will be usefull.If the type
 *  is ELEMENT_NODE the parameters NODE_TYPE, pachLocalName, pachPrefix,
 *  pachUri will be usefull.
 *
 * @param eNODE_TYPE The type of the child to be created, it should be either
 *  CHARACTER_NODE for CharacterElements or ELEMENT_NODE for
 *  ComplexElements.
 * @param pachLocalName The local name of the complex element to be created.
 * @param pachPrefix The prefix of the complex element to be created.
 * @param pachUri The namespace uri of the complex element to be created.
 * @param pachValue The value of the character element to be created.
 *
 * @return The child node created will be returned if the creation is
 *  successfull. If the creation is unsccessfull it will return NULL.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockCreateImmediateChildBasicNode(AXISCHANDLE headerBlock, AXISC_NODE_TYPE eNODE_TYPE, 
	AxiscChar * pachLocalName, 
	AxiscChar * pachPrefix, 
	AxiscChar * pachUri, 
	AxiscChar * pachValue);

/**
 * A user can use this method to create a standard HeaderBlock attribute.
 * The types of HEADER_BLOCK_STD_ATTR_TYPE are:
 * ROLE_NEXT : To create the role attribute to point to next.
 * ROLE_NONE : To create the role attribute to point to none.
 * ROLE_ULTIMATE_RECEIVER : To create the role attribute to point to
 * ultimate receiver.
 * ACTOR : To create the actor attribute to point to next.
 * MUST_UNDERSTAND_TRUE : To create the mustUnderstand attribute to
 * point to true.
 * MUST_UNDERSTAND_FALSE : To create the mustUnderstand attribute to
 * point to false.
 * To use ROLE_NEXT,
 * ROLE_NONE, ROLE_ULTIMATE_RECEIVER, MUST_UNDERSTAND_TRUE,
 * MUST_UNDERSTAND_FALSE the user has to pass SOAP_VER_1_2 as the
 * SOAP_VERSION.
 * To use ACTOR, MUST_UNDERSTAND_TRUE, MUST_UNDERSTAND_FALSE the user has
 * to pass SOAP_VER_1_1 as the SOAP_VERSION.
 * NOTE: No checking is done to see if the attributs being created on the header are correct for SOAP.
 * e.g. if two MUST_UNDERSTAND_TRUE headers are created then the SOAP message is invalid but it will still
 * get sent across to the server. In such instances we expect most servers to respond with a server fault.
 *
 * @param eStdAttrType The standard attribute to be created.
 * The current values that can be passes are: ROLE_NEXT, ROLE_NONE,
 * ROLE_ULTIMATE_RECEIVER, ACTOR, MUST_UNDERSTAND_TRUE,
 * MUST_UNDERSTAND_FALSE.
 * @param eSOAP_VERSION The related soap version.
 * The vallues which could be
 * passes are SOAP_VER_1_1 and SOAP_VER_1_2.
 *
 * @return A pointer to the created standard Attribute will be returned.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockCreateStdAttribute(AXISCHANDLE headerBlock, AXISC_HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, 
	AXISC_SOAP_VERSION eSOAP_VERSION);

/**
 * Creates a Attribute and adds it to this Header Block.
 * NOTE: No checking is done to see if this attribute creation applies to the xsd rules.
 * We expect that the server side will fail.
 * e.g. If creating more than one attribute with the same name the outcome is undefined
 *
 * @param localname The local name of the attribute. (mandatory)
 * @param prefix The prefix of the attribute. (optional)
 * @param uri The namespace uri of the attribute. (optional)
 * @param value The value of the attribute. (optional)
 *
 * @return A pointer to the created Attribute will be returned.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockCreateAttribute(AXISCHANDLE headerBlock, const AxiscChar * localname, 
	const AxiscChar * prefix, 
	const AxiscChar * uri, 
	const AxiscChar * value);

/**
 * Gets an Attribute from the HeaderBlock.
 *
 * @param localname The local name of the attribute.
 * @param prefix The prefix of the attribute.
 *
 * @return the value of the attribute is returned.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscHeaderBlockGetAttributeValue(AXISCHANDLE headerBlock, const AxiscChar * localname, 
	const AxiscChar * prefix);

/**
 * Gets and Attribute URI from the Header Block.
 *
 * @param localname The local name of the attribute.
 * @param prefix The prefix of the attribute.
 *
 * @return the uri of the attribute is returned.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscHeaderBlockGetAttributeUri(AXISCHANDLE headerBlock, const AxiscChar * localname, 
	const AxiscChar * prefix);

/**
 * Returns the last child element. The user has to check whether the
 * method return NULL before proceding.
 *
 * @return The last child element is returned if it exists.
 * If the child element doesn't exsist this method returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockGetLastChildBasicNode(AXISCHANDLE headerBlock);

/**
 * Returns the child element at the given postion.
 * The user has to check whether the method return NULL before proceding.
 *
 * @param iChildPosition The positon of the required child element.
 * @return The required child element is returned if it exists.
 * If the child element doesn't exsist this method returns NULL.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockGetChildBasicNode(AXISCHANDLE headerBlock, int iChildPosition);

/**
 * Adds a child node to the Header Block.
 *
 * @param pBasicNode The child node pointer which is to be added
 * NOTE: This cannot be a pointer to a child that has already been added> If you want to add the same data twice then create a new basic node.
 * @return AXIS_SUCCESS to indicate successfull operation.AXIS_FAIL otherwise
 */
AXISC_STORAGE_CLASS_INFO
int axiscHeaderBlockAddChild(AXISCHANDLE headerBlock, AXISCHANDLE pBasicNode);

/**
 * Sets the local name of this Header Block.
 *
 * @param localname The localname to set in.
 * @return AXIS_SUCCESS if successful AXIS_FAIL otherwise
 */
AXISC_STORAGE_CLASS_INFO
int axiscHeaderBlockSetLocalName(AXISCHANDLE headerBlock, const AxiscChar * localname);

/**
 * Gets the local name of this Header Block.
 *
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscHeaderBlockGetLocalName(AXISCHANDLE headerBlock);

/**
 * Sets the namespace uri of this Header Block.
 *
 * @param uri The namespace uri to set in. IF NULL is passed in then URI is set to ""
 * @return AXIS_SUCCESS if successful AXIS_FAIL otherwise
 *
 */
AXISC_STORAGE_CLASS_INFO
int axiscHeaderBlockSetURI(AXISCHANDLE headerBlock, const AxiscChar * uri);

/**
 * Sets the prefix of this Header Block.
 *
 * @param prefix The prefix to set in.IF NULL is passed in the prefix is set to ""
 * @return AXIS_SUCCESS if successful AXIS_FAIL otherwise
 */
AXISC_STORAGE_CLASS_INFO
int axiscHeaderBlockSetPrefix(AXISCHANDLE headerBlock, const AxiscChar * prefix);


/**
 * Initialized the Header Block for testing.
 */
AXISC_STORAGE_CLASS_INFO
int axiscHeaderBlockInitializeForTesting(AXISCHANDLE headerBlock);

/**
 * Creates and returns a clone of this Header Block.
 *
 * @return A clone of this Header Block.
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscHeaderBlockCloneHeaderBlock(AXISCHANDLE headerBlock);

/**
 * The Destructor.
 */
AXISC_STORAGE_CLASS_INFO
void axiscHeaderBlockDestroy(AXISCHANDLE headerBlock);


#ifdef __cplusplus
 }
#endif

#endif /* IHEADERBLOCK_INCLUDED */
