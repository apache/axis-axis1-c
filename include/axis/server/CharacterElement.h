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


#if !defined(_CHARACTERELEMENT_H____OF_AXIS_INCLUDED_)
#define _CHARACTERELEMENT_H____OF_AXIS_INCLUDED_

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "BasicNode.h"
/*
 *   @class CharacterElement
 *   @brief interface for the CharacterElement class.
 *
 *   @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 */
class CharacterElement : public BasicNode
{
public:
    bool operator ==( const CharacterElement &objChEle);
    int setValue(const AxisChar* pachValue);
    const AxisChar* getValue() const;

    /*
     * This method is overridden to return 0 always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return 0.
     */
    int getNoOfChildren() {return 0;}

    /*
     * This method is overridden to return NULL always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return NULL to indicate unsuccessfull operation.
     */
     const BasicNode* getFirstChild() const {return NULL;}

    /*
     * This method is overridden to return NULL always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return NULL to indicate unsuccessfull operation.
     */
    const BasicNode* getLastChild() const {return NULL;}

    /*
     * This method is overridden to return NULL always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return NULL to indicate unsuccessfull operation.
     */
    const BasicNode* getChild(int iChildPosition) const {return NULL;}

    /*
     * This method is overridden to return fail(AXIS_FAIL) always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
     * operation.
     */
    int setURI(const AxisChar* sURI) {return AXIS_FAIL;}

    /*
     * This method is overridden to return fail(AXIS_FAIL) always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
     * operation.
     */
    int addChild(BasicNode* pBasicNode) {return AXIS_FAIL;}

    /*
     * This method is overridden to return fail(AXIS_FAIL) always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
     * operation.
     */
    int setLocalName(const AxisChar* sLocalName) {return AXIS_FAIL;}

    /*
     * This method is overridden to return fail(AXIS_FAIL) always because this 
     * is a CharacterElement. 
     * A user of a CharacterElement should not use this method.
     * @return Always return fail (AXIS_FAIL) to indicate unsuccessfull 
     * operation.
     */
    int setPrefix(const AxisChar* sPrefix) {return AXIS_FAIL;}

    int serialize(SoapSerializer& pSZ);
    /*
     * This method is actualy not used in this class. This method was just
     * included to adhere its interface.
     */
    int serialize(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack) {return AXIS_SUCCESS;}
    NODE_TYPE getNodeType() const;
    CharacterElement(const AxisChar* sValue);
    CharacterElement();
    virtual ~CharacterElement();
};

#endif 
