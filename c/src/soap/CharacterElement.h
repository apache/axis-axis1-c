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
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added copy constructure and clone for copy constructing derived classes
 */

/*
 * Revision 1.2  2004/06/13 roshan
 * Added doxygen comments to help autobuild API docs
 */


#if !defined(_CHARACTERELEMENT_H____OF_AXIS_INCLUDED_)
#define _CHARACTERELEMENT_H____OF_AXIS_INCLUDED_

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/server/BasicNode.h>

/**
 * @class CharacterElement
 * @brief interface for the CharacterElement class.
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */
class CharacterElement : public BasicNode
{
public:
    bool operator ==( const CharacterElement &objChEle);

    /**
      * Sets the value of this Character Element
      *
      * @param pachValue The value to be set
      * @return AXIS_SUCCESS to indicate success.
      */    
    int setValue(const AxisChar* pachValue);

    /**
      * Gets and return the value of this Character Element
      *
      * @return The value of this Character Element.
      */    
    const AxisChar* getValue() const;

    /**
      * This method is overridden to return 0 always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @return Always return 0.
      */
    int getNoOfChildren() {return 0;}

    /**
      * This method is overridden to return NULL always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @return Always return NULL to indicate unsuccessfull operation.
      */
     const BasicNode* getFirstChild() const {return NULL;}

    /**
      * This method is overridden to return NULL always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @return Always return NULL to indicate unsuccessfull operation.
      */
    const BasicNode* getLastChild() const {return NULL;}

    /**
      * This method is overridden to return NULL always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param iChildPosition The child position.
      * @return Always return NULL to indicate unsuccessfull operation.
      */
    const BasicNode* getChild(int iChildPosition) const {return NULL;}

    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param sURI The namespace URI.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int setURI(const AxisChar* sURI) {return AXIS_FAIL;}

    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param pBasicNode The child to be added.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int addChild(BasicNode* pBasicNode) {return AXIS_FAIL;}

    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param sLocalName The localname.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int setLocalName(const AxisChar* sLocalName) {return AXIS_FAIL;}

    /**
      * This method is overridden to return fail(AXIS_FAIL) always because this 
      * is a CharacterElement. 
      * A user of a CharacterElement should not use this method.
      *
      * @param sPrefix The prefix.
      * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
      * operation.
      */
    int setPrefix(const AxisChar* sPrefix) {return AXIS_FAIL;}

    int serialize(SoapSerializer& pSZ);

    /**
      * This method is actualy not used in this class. This method was just
      * included to adhere its interface.
      */
    int serialize(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack) {return AXIS_SUCCESS;}

    /**
      * Returns the Node Type of this Character Element, which is 
      * CHARACTER_NODE.
      *
      * @return The Node Type of this Character Element, which is 
      * CHARACTER_NODE
      */
    NODE_TYPE getNodeType() const;

    /**
      * The Constructor.
      *
      * @param sValue The value of the Character Element.
      */
    CharacterElement(const AxisChar* sValue);

    /**
      * The Constructor.
      */
    CharacterElement();

    CharacterElement(const CharacterElement& rCopy); 
    BasicNode* clone();   

    /**
      * The Destructor.
      */
    virtual ~CharacterElement();
};

#endif 