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
 *
 *
 */

#if !defined(AXIS_COMPLEXELEMENT_H__OF_AXIS_INCLUDED_)
#define AXIS_COMPLEXELEMENT_H__OF_AXIS_INCLUDED_

#include <list>
#include <axis/BasicNode.hpp>
#include "Attribute.h"

AXIS_CPP_NAMESPACE_START

using namespace std;

/**
 * @class ComplexElement
 * @brief interface for the ComplexElement class.
 *
 */

class ComplexElement : public BasicNode
{
public:
    ComplexElement(AxisChar* pachLocalName, AxisChar* pachPrefix, AxisChar* pachUri);

    /**
      * Returns the Attribute of this node, corresponding to the given
      * prefix/localname pair or the given namespace URI/localname pair.
      * The users could get the attributes with the
      * following combinations of pairs.
      *  1. by prefix and localname pair (here the namespace URI(i.e pachURI
      *      has to be a empty string)) or
      *  2. by namespace URI and localname pair (here the prefix
      *      (i.e pachPrefix has to be a empty string)).
      * 
      * If not found returns NULL.
      */
    IAttribute* getAttribute(AxisChar* pachPrefix, AxisChar* pachURI,  AxisChar* pachLocalname);
                                                                                                                                                                            
    /**
      * Returns the first Attribute of this node. NOTE: When traversing the 
      *  attributes this has to be called first, before calling the 
      *  getNextAttribute() mthod.
      */
    IAttribute* getFirstAttribute();
                                                                                                                                                                            
    /**
      * Returns the last Attribute of this node.
      */
    IAttribute* getLastAttribute();
                                                                                                                                                                            
    /**
      * Returns the next Attribute of this node. NOTE: When traversing the
      *  attributes getFirstAttribute() has to be called first, before calling this
      *  mthod, otherwise the behavior is undefined.
      */
    IAttribute* getNextAttribute();

    /**
      * Returns the current Attribute of this node. NOTE: When traversing the
      *  attributes getFirstAttribute() has to be called first, before calling this
      *  mthod, otherwise the behavior is undefined.
      */
    IAttribute* getCurrentAttribute();

    /** 
   � * Creates an Attribute and adds it to this Complex Element.
    �*
     * @param localname The local name of the attribute.
   � * @param prefix The prefix of the attribute.
   � * @param uri The namespace uri of the attribute.
   � * @param value The value of the attribute.
   � *
   � * @return A pointer to the created Attribute will be returned.
   � */
    IAttribute* createAttribute(const AxisChar* localname,
        const AxisChar* prefix, const AxisChar* uri, const AxisChar* value);

    /** 
   � * Creates an Attribute and adds it to this Complex Element.
   � *
   � * @param localname The local name of the attribute.
   � * @param prefix The prefix of the attribute.
   � * @param value The value of the attribute.
   � *
   � * @return A pointer to the created Attribute will be returned.
   � */
    IAttribute* createAttribute(const AxisChar* localname,
            const AxisChar* prefix, const AxisChar* value);

    /**
   � * Creates an Attribute and adds it to this Complex Element.
   � *
   � * @param localname The local name of the attribute.
   � * @param value The value of the attribute.
   � *
   � * @return A pointer to the created Attribute will be returned.
   � */
    IAttribute* createAttribute(const AxisChar* localname,
            const AxisChar* value);

    /**
      * Returns the number of child elements of this ComplexElement.
      *
      * @return The number of child elements of this ComplexElement.
      */
    int getNoOfChildren();

    /**
      * Get the Child Node of the given position.
      *
      * @param iChildPosition The child position.
      * @return The Child Node of the given position.
      */
    BasicNode* getChild(int iChildPosition);

    /**
      * Gets the last Child Node of this Complex Element.
      *
      * @return The last Child Node of this Complex Element.
      */
    BasicNode* getLastChild();

    /**
      * Gets the first Child Node of this Complex Element.
      *
      * @return The first Child Node of this Complex Element.
      */
    BasicNode* getFirstChild();

    /**
      * Adds the given child node to this Complex Element.
      *
      * @param pBasicNode the child node to be added to this Complex Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    int addChild(BasicNode* pBasicNode);

    /**
      * Gets the Node Type of the Complex Element which is ELEMENT_NODE.
      *
      * @return The Node Type of the Complex Element which is ELEMENT_NODE.
      */
    NODE_TYPE getNodeType() const;

    /**
      * Sets the namespace URI of this Complex Element.
      *
      * @param pachURI the namespace URI of this Complex Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    int setURI(const AxisChar* pachURI);

    /**
      * Sets the local name of this Complex Element.
      *
      * @param pachLocalName the local name of this Complex Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    int setLocalName(const AxisChar* pachLocalName);

    /**
      * Sets the prefix of this Complex Element.
      *
      * @param pachPrefix the prefix of this Complex Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    int setPrefix(const AxisChar* pachPrefix);

    int serialize(SoapSerializer& pSZ);

    int serialize(SoapSerializer& pSZ, std::list<AxisChar*>& lstTmpNameSpaceStack);

    /**
      * The Constructor.
      */
    ComplexElement();
    ComplexElement(const ComplexElement& rCopy);
    BasicNode* clone();

    /**
      * The Destructor.
      */
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

    /**
      * Returns the local name of this node.
      *
      * @return The localname of this element.
      */
    const AxisChar* getLocalName();

    /**
      * Returns the namespace URI of this node.
      *
      * @return The namespace URI of this element.
      */
    const AxisChar* getURI();
                                                                                                                                                                            
    /**
      * Returns the prefix  of this node.
      *
      * @return The prefix of this element.
      */
    const AxisChar* getPrefix();

    /**
     * Set a pointer to the parent node.
     */
    void setParent(ComplexElement *parent);

private:
    int iNoOfChildren;
    int serializeChildren(SoapSerializer& pSZ);
    int serializeChildren(SoapSerializer& pSZ, std::list<AxisChar*>& lstTmpNameSpaceStack);
    int serializeNamespaceDecl(SoapSerializer &pSZ); 
    int attrSerialize(SoapSerializer& pSZ, std::list<AxisChar*>& lstTmpNameSpaceStack);
    bool isSerializable();
    std::list<BasicNode*> m_children;
    std::list<Attribute*> m_namespaceDecls;
    std::list<Attribute*> m_attributes;
    AxisChar* m_pachPrefix;
    AxisChar* m_pachLocalName;
    AxisChar* m_pachURI;

    /**
      * Attributes iterator
      */
    std::list <Attribute *>::iterator m_viCurrentAttribute;

    ComplexElement * m_pParent;

};

AXIS_CPP_NAMESPACE_END

#endif
