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


#if !defined(_BASICNODE_H____OF_AXIS_INCLUDED_)
#define _BASICNODE_H____OF_AXIS_INCLUDED_

#include <string>
#include <list>
#include "GDefine.h"

using namespace std;

class SoapSerializer;

enum NODE_TYPE { ELEMENT_NODE=1, CHARACTER_NODE};
/**
    @class BasicNode
    @brief interface for the BasicNode class.


    @author Roshan Weerasuriya (roshan@jkcsworld.com, roshan@opensource.lk)
*/
class BasicNode
{
public:
	/**
	 * Returns the number of child elements of this element. The return value
	 *  depends on the TYPE of the node.
	 * @return The number of child elements of this element. The return value
	 *  depends on the TYPE of the node.
	 */
	virtual int getNoOfChildren() = 0;
	virtual const BasicNode* getFirstChild() const = 0;
	virtual const BasicNode* getLastChild() const = 0;
	virtual const BasicNode* getChild(int iChildPosition) const = 0;
	//virtual bool operator ==( const BasicNode &objChEle)=0;
	virtual const AxisChar* getValue() const =0;
	virtual int setValue(const AxisChar* pachValue)=0;
	virtual NODE_TYPE getNodeType() const =0;
	virtual int setURI(const AxisChar* sURI) =0;
	virtual int addChild(BasicNode* pBasicNode) =0;
	virtual int setLocalName(const AxisChar* sLocalName) =0;
	virtual int setPrefix(const AxisChar* sPrefix) =0;
	virtual int serialize(SoapSerializer& pSZ) =0;
	virtual int serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack) =0;
	virtual ~BasicNode() {};

protected:
	NODE_TYPE m_iNodeType;
	//string m_sPrefix;
	AxisChar* m_pachValue;
};

#endif // !defined(_BASICNODE_H____OF_AXIS_INCLUDED_)
