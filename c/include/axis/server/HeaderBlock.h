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


#if !defined(_HEADERBLOCK_H____OF_AXIS_INCLUDED_)
#define _HEADERBLOCK_H____OF_AXIS_INCLUDED_

#include "Attribute.h"
#include <string>
#include <list>

using namespace std;

class BasicNode;
#include "IHeaderBlock.h"
#include "SoapEnvVersions.h"

/*
 *  @class BasicNode
 *  @brief    The Header block of a SOAP Header according to 
 *  SOAP 1.2 specification.
 *   
 *  The Header block of a SOAP Header according to SOAP 1.2 specification.
 *
 *  Each child element information item of the SOAP Header is called a 
 *  SOAP header block. Each SOAP header block element information item:
 *    - MUST have a [namespace name] property which has a value, 
 *      that is the name of the element MUST be namespace qualified.
 *    - MAY have any number of character information item children. 
 *      Child character information items whose character code is amongst 
 *      the white space characters as defined by XML 1.0 [XML 1.0] are 
 *      considered significant.
 *    - MAY have any number of element information item children. Such element 
 *      information items MAY be namespace qualified.
 *    - MAY have zero or more attribute information items in its [attributes] 
 *       property. Among these MAY be any or all of the following, which have 
 *       special significance for SOAP processing:
 *    - encodingStyle attribute information item 
 *    - role attribute information item 
 *    - mustUnderstand attribute information item     
 *    - relay attribute information item 
 *
 *    
 *    
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *  @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/26 samisa
 * Added copy constructor and clone
 */

class HeaderBlock : public IHeaderBlock
{
friend class SoapHeader;

private:    
    /**
     * Returns the number of child elements of this HeaderBlock.
     * @return The number of child elements of this HeaderBlock.
     */
    int iNoOFChildren;
    
    int serializeNamespaceDecl(SoapSerializer& pSZ);
    int serializeChildren(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack);
    list<BasicNode*> m_children;
    bool isSerializable();
    int attrSerialize(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack);
    AxisString m_localname;
    AxisString m_prefix;
    AxisString m_uri;
    list<Attribute*> m_attributes;
    list<Attribute*> m_namespaceDecls;

public:
    const BasicNode* getFirstChild();
    int getNoOfChildren();
    BasicNode* createChild(NODE_TYPE eNODE_TYPE,  
        AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, 
        AxisChar* pachValue);

    int initializeForTesting();

  /*
   * Creates a child node depending on the given type. If the type is 
   *  CHARACTER_NODE a CharacterElement is created. If the type is 
   *  ELEMENT_NODE a ComplexElement is created. After creating the child it
   *  will be added as a immediate child to the header block.
   *  It is important to note that if the type is CHARACTER_NODE only the
   *  NODE_TYPE and value (pachValue) parameters will be usefull.If the type
   *  is ELEMENT_NODE the parameters NODE_TYPE, pachLocalName, pachPrefix, 
   *  pachUri will be usefull.
   * @param eNODE_TYPE The type of the child to be created, it should be either 
   *  CHARACTER_NODE for CharacterElements or ELEMENT_NODE for 
   *  ComplexElements.
   * @param pachLocalName The local name of the complex element to be created.
   * @param pachPrefix The prefix of the complex element to be created.
   * @param pachUri The namespace uri of the complex element to be created.
   * @param pachValue The value of the character element to be created.
   * @return The child node created will be returned if the creation is
   *  successfull. If the creation is unsccessfull it will return NULL.
   */
    BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE, 
        AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, 
        AxisChar* pachValue);

    /*
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
     * @param eStdAttrType The standard attribute to be created.
     * The current values that can be passes are: ROLE_NEXT, ROLE_NONE, 
     * ROLE_ULTIMATE_RECEIVER, ACTOR, MUST_UNDERSTAND_TRUE,
     * MUST_UNDERSTAND_FALSE.
     * @param eSOAP_VERSION The related soap version. 
     * The vallues which could be
     * passes are SOAP_VER_1_1 and SOAP_VER_1_2.
     */
    Attribute* createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, 
        SOAP_VERSION eSOAP_VERSION);

    Attribute* createAttribute(const AxisChar* localname, 
        const AxisChar* prefix, const AxisChar* uri, const AxisChar* value);
    Attribute* createAttribute(const AxisChar* localname, 
        const AxisChar* prefix, const AxisChar* value);

    /*
     * Creates a child node depending on the given type. If the type is 
     * CHARACTER_NODE a CharacterElement is created. If the type is 
     * ELEMENT_NODE a ComplexElement is created. After creating the child it
     * will be added as a immediate child to the header block.
     * @param The type of the child to be created, it should be either 
     * CHARACTER_NODE for CharacterElements or ELEMENT_NODE for 
     * ComplexElements.
     * @return The child node created will be returned if the creation is
     * successfull. If the creation is unsccessfull it will return NULL.
     */
    BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE);

    /*
     * Creates a child node depending on the given type. If the type is 
     * CHARACTER_NODE a CharacterElement is created. If the type is 
     * ELEMENT_NODE a ComplexElement is created. After creating the child it
     * will not be added as a child to the header block. The user has to add
     * the created child to the appropriate locaion as his wish.
     * @param eNODE_TYPE The type of the child to be created, 
     * it should be either 
     * CHARACTER_NODE for CharacterElements or ELEMENT_NODE for 
     * ComplexElements.
     * @return The child node created will be returned if the creation is
     * successfull. If the creation is unsccessfull it will return NULL.
     */
    BasicNode* createChild(NODE_TYPE eNODE_TYPE);

    

    /*
     * Returns the last child element. The user has to check whether the
     * method return NULL before proceding.
     * @return The last child element is returned if it exists. 
     * If the child element doesn't exsist this method returns NULL.
     */
    const BasicNode* getLastChild();

    /*
     * Returns the child element at the given postion. 
     * The user has to check whether the
     * method return NULL before proceding.
     * @param iChildPosition The positon of the required child element.
     * @return The required child element is returned if it exists. 
     * If the child element doesn't exsist this method returns NULL.
     */
    const BasicNode* getChild(int iChildPosition);
    int addChild(BasicNode* pBasicNode);

    void setLocalName(const AxisChar* localname);
    void setUri(const AxisChar* uri);
    void setPrefix(const AxisChar* prefix);

    HeaderBlock(AxisChar* pachLocalName, AxisChar* pachPrefix, 
        AxisChar* pachUri);
    HeaderBlock();
    HeaderBlock(const HeaderBlock& rCopy);
    IHeaderBlock* clone();
    virtual ~HeaderBlock();

    bool operator ==( const HeaderBlock &objHeaderBlock);
    int addNamespaceDecl(Attribute *pAttribute);
    int serialize(SoapSerializer& pSZ);
    void addAttribute(Attribute* attr);

};

#endif 

