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

/*
 * @class BasicNode
 * @brief interface for the BasicNode class.
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added constructors, copy constructure and pure virtual clone for copy constructing derived classes
 */

/*
 * Revision 1.2  2004/06/13 roshan
 * Added doxygen comments to help autobuild API docs
 */

class BasicNode
{
public:
    /**
      * Returns the number of child elements of this element. The operation
      * behavior depends on the TYPE of the node.
	  *
      * @return The number of child elements of this element. The return value
      * behavior depends on the TYPE of the node.
      */
    virtual int getNoOfChildren() = 0;

    /**
      * Gets the first Child Node of this Complex Element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The first Child Node of this Element.
      */
    virtual const BasicNode* getFirstChild() const = 0;

    /**
      * Gets the last Child Node of this Complex Element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The last Child Node of this Element.
      */
    virtual const BasicNode* getLastChild() const = 0;

    /**
      * Get the Child Node of the given position. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param iChildPosition The child position.
      * @return The Child Node of the given position.
      */
    virtual const BasicNode* getChild(int iChildPosition) const = 0;

    /**
      * Adds the given child node to this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pBasicNode the child node to be added to this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int addChild(BasicNode* pBasicNode) =0;

    /**
      * Gets the Node Type of the Element.
      *
      * @return The Node Type of the Element.
      */
    virtual NODE_TYPE getNodeType() const =0;

    /**
      * Gets and return the value of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @return The value of this Element.
      */    
    virtual const AxisChar* getValue() const =0;

    /**
      * Sets the value of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachValue The value to be set
      * @return AXIS_SUCCESS to indicate success.
      */   
    virtual int setValue(const AxisChar* pachValue)=0;
    
    /**
      * Sets the namespace URI of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachURI the namespace URI of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int setURI(const AxisChar* sURI) =0;

    /**
      * Sets the local name of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachLocalName the local name of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int setLocalName(const AxisChar* sLocalName) =0;

    /**
      * Sets the prefix of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachPrefix the prefix of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int setPrefix(const AxisChar* sPrefix) =0;

    virtual int serialize(SoapSerializer& pSZ) =0;
    virtual int serialize(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack) =0;
    BasicNode();
    BasicNode(const AxisChar* pachValue, NODE_TYPE eNodeType = ELEMENT_NODE);
    BasicNode(const BasicNode& rCopy);
    virtual BasicNode* clone() = 0;
    virtual ~BasicNode();

protected:
    /**
      * Used to store the Node Type, which is either ELEMENT_NODE or 
      * CHARACTER_NODE.
      */
    NODE_TYPE m_iNodeType;

    /**
      * Used to store the value. The usage of this variable depends on the TYPE
      * of the node.
      */
    AxisChar* m_pachValue;
};

#endif 

