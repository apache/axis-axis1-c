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

#if !defined(_IHEADERBLOCK_H____OF_AXIS_INCLUDED_)
#define _IHEADERBLOCK_H____OF_AXIS_INCLUDED_

#include "BasicNode.h"
#include "SoapEnvVersions.h"
#include "Attribute.h"

enum HEADER_BLOCK_STD_ATTR_TYPE { ROLE_NEXT=1, ROLE_NONE=2, 
	ROLE_ULTIMATE_RECEIVER=3, ACTOR=4, MUST_UNDERSTAND_TRUE= 5, 
	MUST_UNDERSTAND_FALSE=6};


/**
    @class IHeaderBlock
    @brief interface for the IHeaderBlock class.


    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
class IHeaderBlock
{
public:
	virtual const BasicNode* getFirstChild() =0;
	/**
	 * Returns the number of child elements of this HeaderBlock.
	 * @return The number of child elements of this HeaderBlock.
	 */
	virtual int getNoOfChildren() =0;
	virtual BasicNode* createChild(NODE_TYPE eNODE_TYPE,  AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, AxisChar* pachValue) = 0;
	virtual BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE, AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, AxisChar* pachValue) = 0;
	virtual Attribute* createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, SOAP_VERSION eSOAP_VERSION) =0;
	virtual Attribute* createAttribute(const AxisChar* localname, const AxisChar* prefix, const AxisChar* uri, const AxisChar* value) = 0;
	virtual Attribute* createAttribute(const AxisChar *localname, const AxisChar *prefix, const AxisChar *value) = 0;

	virtual BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE) = 0;
	virtual BasicNode* createChild(NODE_TYPE eNODE_TYPE)=0;

	/**
	 * Returns the last child element. The user has to check whether the
	 *  method return NULL before proceding.
	 * @return The last child element is returned if it exists. If the child element 
	 *  doesn't exsist this method returns NULL.
	 */
	virtual const BasicNode* getLastChild() = 0;

	/**
	 * Returns the child element at the given postion. The user has to check whether the
	 *  method return NULL before proceding.
	 * @param iChildPosition The positon of the required child element.
	 * @return The required child element is returned if it exists. If the child element 
	 *  doesn't exsist this method returns NULL.
	 */
	virtual const BasicNode* getChild(int iChildPosition) = 0;

	virtual int addChild(BasicNode* pBasicNode)=0;
	virtual void setLocalName(const AxisChar* localname)=0;
	virtual void setUri(const AxisChar* uri)=0;
	virtual void setPrefix(const AxisChar* prefix)=0;
	virtual int initializeForTesting() = 0;
	virtual ~IHeaderBlock() {};
};

#endif // !defined(_IHEADERBLOCK_H____OF_AXIS_INCLUDED_)
