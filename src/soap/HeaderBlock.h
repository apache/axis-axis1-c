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

#include <axis/server/IHeaderBlock.hpp>
#include <string>

AXIS_CPP_NAMESPACE_START

using namespace std;
class BasicNode;
class Attribute;

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
 *  @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *  @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/26 samisa
 * Added copy constructor and clone
 */

/*
 * Revision 1.2  2004/06/13 roshan
 * Added doxygen comments to help autobuild API docs
 */



class HeaderBlock : public IHeaderBlock
{
friend class SoapHeader;

private:   
    /**
      * Used to store the current no of children count.
      */
    int iNoOFChildren;
    
    /**
      * Serializes the namespace decl.
      */
    int serializeNamespaceDecl(SoapSerializer& pSZ);

    int serializeChildren(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack);

    /**
      * Used to hold the child nodes.
      */
    list<BasicNode*> m_children;

    bool isSerializable();

    int attrSerialize(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack);

    AxisString m_localname;
    AxisString m_sPrefix;
    AxisString m_uri;
    list<Attribute*> m_attributes;
    list<Attribute*> m_namespaceDecls;

public:

    /** 
      * Creates a Attribute and adds it to this Header Block as a namespace. 
      * 
      * @param prefix The prefix of the attribute. 
      * @param uri The namespace uri of the attribute. 
      * 
      * @return A pointer to the created Attribute will be returned. 
      */
    IAttribute* createNamespaceDecl(const AxisChar *prefix, 
            const AxisChar *uri); 

    const BasicNode* getFirstChild();

    /**
     * Returns the number of child elements of this HeaderBlock.
     *
     * @return The number of child elements of this HeaderBlock.
     */
    int getNoOfChildren();

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
    BasicNode* createChild(NODE_TYPE eNODE_TYPE,  
        AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, 
        AxisChar* pachValue);

#ifdef UNIT_TESTING_ON
    int initializeForTesting();
#endif
  /**
   * Creates a child node depending on the given type. If the type is 
   *  CHARACTER_NODE a CharacterElement is created. If the type is 
   *  ELEMENT_NODE a ComplexElement is created. After creating the child it
   *  will be added as a immediate child to the header block.
   *  It is important to note that if the type is CHARACTER_NODE only the
   *  NODE_TYPE and value (pachValue) parameters will be usefull.If the type
   *  is ELEMENT_NODE the parameters NODE_TYPE, pachLocalName, pachPrefix, 
   *  pachUri will be usefull.
   * The caller of this method has to check the return value and if it is NULL
   *  then the operation is not successfull.
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
    BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE, 
        AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, 
        AxisChar* pachValue);

    /**
      * Adds a Attribute to this Header Block.
      *
      * @param attr The Attribute to be added.
      */
    void addAttribute(Attribute* attr);

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
    IAttribute* createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, 
        SOAP_VERSION eSOAP_VERSION);

    /**
      * Creates a Attribute and adds it to this Header Block. This method might
      *  null to indicate unsuccessfull operation. The caller of this method 
      *  should check for the return NULL value.
      *
      * @param localname The local name of the attribute.
      * @param prefix The prefix of the attribute.
      * @param uri The namespace uri of the attribute.
      * @param value The value of the attribute.
      *
      * @return A pointer to the created Attribute will be returned. If the
      *  operation is unsuccessfull it will return NULL.
      */
    IAttribute* createAttribute(const AxisChar* localname, 
        const AxisChar* prefix, const AxisChar* uri, const AxisChar* value);

    /**
      * Creates a Attribute and adds it to this Header Block.
      *
      * @param localname The local name of the attribute.
      * @param prefix The prefix of the attribute.
      * @param value The value of the attribute.
      *
      * @return A pointer to the created Attribute will be returned.
      */
    IAttribute* createAttribute(const AxisChar* localname, 
        const AxisChar* prefix, const AxisChar* value);

		
	/**
      * Gets an Attribute from the HeaderBlock.
      *
      * @param localname The local name of the attribute.
      * @param prefix The prefix of the attribute.
      *
      * @return the value of the attribute
      */
     virtual const AxisChar* getAttributeValue(const AxisChar* localname,
         const AxisChar* prefix);
 

    /**
     * Creates a child node depending on the given type. If the type is 
     * CHARACTER_NODE a CharacterElement is created. If the type is 
     * ELEMENT_NODE a ComplexElement is created. After creating the child it
     * will be added as a immediate child to the header block.
     *
     * @param The type of the child to be created, it should be either 
     * CHARACTER_NODE for CharacterElements or ELEMENT_NODE for 
     * ComplexElements.
     * @return The child node created will be returned if the creation is
     * successfull. If the creation is unsccessfull it will return NULL.
     */
    BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE);

    /**
     * Creates a child node depending on the given type. If the type is 
     * CHARACTER_NODE a CharacterElement is created. If the type is 
     * ELEMENT_NODE a ComplexElement is created. After creating the child it
     * will not be added as a child to the header block. The user has to add
     * the created child to the appropriate locaion as his wish.
     *
     * @param eNODE_TYPE The type of the child to be created, 
     * it should be either 
     * CHARACTER_NODE for CharacterElements or ELEMENT_NODE for 
     * ComplexElements.
     * @return The child node created will be returned if the creation is
     * successfull. If the creation is unsccessfull it will return NULL.
     */
    BasicNode* createChild(NODE_TYPE eNODE_TYPE);

    /**
     * Returns the last child element. The user has to check whether the
     * method return NULL before proceding.
     *
     * @return The last child element is returned if it exists. 
     * If the child element doesn't exsist this method returns NULL.
     */
    const BasicNode* getLastChild();

    /**
     * Returns the child element at the given postion. 
     * The user has to check whether the
     * method return NULL before proceding.
     *
     * @param iChildPosition The positon of the required child element.
     * @return The required child element is returned if it exists. 
     * If the child element doesn't exsist this method returns NULL.
     */
    const BasicNode* getChild(int iChildPosition);

    /**
      * Adds a child node to the Header Block.
      *
      * @param pBasicNode The child node pointer which is to be added.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    int addChild(BasicNode* pBasicNode);

    /**
      * Sets the local name of this Header Block.
      *
      * @param localname The localname to set in.
      */
    void setLocalName(const AxisChar* localname);

    /**
      * Sets the namespace uri of this Header Block.
      *
      * @param uri The namespace uri to set in.
      */
    void setUri(const AxisChar* uri);

	/* 
	 * Commented by Susantha - 21/06/2004
	 * The prefix should be decided by the Serializer at runtime
	 *
	 * Uncommented by Mark Whitlock - 24/8/04 after discussion 
	 * on the mailing list agreed to add back in this method.
	 * Jira issue AXISCPP-135
	 */
    /**
      * Sets the prefix of this Header Block.
      *
      * @param prefix The prefix to set in.
      */
    void setPrefix(const AxisChar* prefix);

    /**
      * Sets the namespace declaration of the Header Block.
      *
      * @param pAttribute The Attribute pointer which points to a valid 
      * namespace declartion Attribute.
      * @return AXIS_SUCCESS to indicate successfull operation. AXIS_FAIL to
      *  to indicate unsuccessfull operation.
      */
    int addNamespaceDecl(IAttribute *pAttribute);

    /**
      * The Constructor.
      *
      * @param pachLocalName The local name of this Header Block.
      * @param pachPrefix The prefix of this Header Block.
      * @param pachUri The namespace uri of this Header Block.
      */
    HeaderBlock(const AxisChar* pachLocalName, const AxisChar* pachUri);

    /**
      * The Constructor.
      */
    HeaderBlock();

    /**
      * The Copy Constructor.
      *
      * @param rCopy A Header Block.
      */
    HeaderBlock(const HeaderBlock& rCopy);

    /**
      * Creates and returns a clone of this Header Block.
      *
      * @return A clone of this Header Block.
      */
    IHeaderBlock* clone();

    /**
      * The Destructor.
      */
    virtual ~HeaderBlock();

    bool operator ==( const HeaderBlock &objHeaderBlock);

    int serialize(SoapSerializer& pSZ);    

};

AXIS_CPP_NAMESPACE_END

#endif 

