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

/*
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 */

#if !defined(AXIS_COMPLEXELEMENT_H__INCLUDED_)
#define AXIS_COMPLEXELEMENT_H__INCLUDED_

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <list>
#include <axis/server/BasicNode.h>

using namespace std;
/*
 * @class ComplexElement
 * @brief interface for the ComplexElement class.
 *
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
class ComplexElement : public BasicNode
{
public:
    ComplexElement(AxisChar* pachLocalName, AxisChar* pachPrefix, AxisChar* pachUri);
    /*
     * Returns the number of child elements of this ComplexElement.
     * @return The number of child elements of this ComplexElement.
     */
    int getNoOfChildren();
    const BasicNode* getChild(int iChildPosition) const;
    const BasicNode* getLastChild() const;
    const BasicNode* getFirstChild() const;
    NODE_TYPE getNodeType() const;
    int setURI(const AxisChar* pachURI);
    int addChild(BasicNode* pBasicNode);
    int setLocalName(const AxisChar* pachLocalName);
    int setPrefix(const AxisChar* pachPrefix);
    int serialize(SoapSerializer& pSZ);
    int serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);
    ComplexElement();
    virtual ~ComplexElement();

    /*
     * This method is overridden to do nothing always because this is 
     *  a Complex Element. Instead of using this method, a user of a 
     *  ComplexElement must get the childeren of this ComplexElement and
     *  has to traverse through the childrean in a appropriate manner
     *  in order to set there values.
     *  A user of a ComplexElement should not use this method.
     * @param
     * @return Always return fail (AXIS_FAIL).
     */
    int setValue(const AxisChar* pachValue) {return AXIS_FAIL;}

    /*
     * This method is overridden to return NULL always because this is 
     *  a Complex Element. Instead of using this method, a user of a 
     *  ComplexElement must get the childeren of this ComplexElement and
     *  has to traverse through the childrean in a appropriate manner
     *  in order to get there values.
     *  A user of a ComplexElement should not use this method.
     * @param
     * @return Always return NULL to indicate unsuccessful.
     */
    const AxisChar* getValue() const {return NULL;}

private:
    int iNoOfChildren;
    int serializeChildren(SoapSerializer& pSZ);
    int serializeChildren(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);
    bool isSerializable();
    list<BasicNode*> m_children;
    AxisChar* m_pachPrefix;
    AxisChar* m_pachLocalName;
    AxisChar* m_pachURI;
};

#endif
