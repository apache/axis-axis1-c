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


#if !defined(_HEADERBLOCK_H____OF_AXIS_INCLUDED_)
#define _HEADERBLOCK_H____OF_AXIS_INCLUDED_

#include <axis/IHeaderBlock.hpp>
#include <string>

AXIS_CPP_NAMESPACE_START

using namespace std;
class BasicNode;
class Attribute;
class Namespace;


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
 *  @see IHeaderBlock
 *  @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *  @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
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
    int serializeNamespaceDecl(SoapSerializer& pSZ,
            std::list<AxisChar*>& lstTmpNameSpaceStack);

    int serializeChildren(SoapSerializer& pSZ, 
        std::list<AxisChar*>& lstTmpNameSpaceStack);

    /**
      * Used to hold the child nodes.
      */
    std::list<BasicNode*> m_children;

    bool isSerializable();

    int attrSerialize(SoapSerializer& pSZ, 
        std::list<AxisChar*>& lstTmpNameSpaceStack);

    AxisString m_localname;
    AxisString m_sPrefix;
    AxisString m_uri;
    std::list<Attribute*> m_attributes;    
    std::list<Namespace*> m_namespaceDecls;    

public:    

    INamespace* createNamespaceDecl(const AxisChar *prefix, 
            const AxisChar *uri); 
    BasicNode* getFirstChild();
    int getNoOfChildren();

    BasicNode* createChild(NODE_TYPE eNODE_TYPE,  
        AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, 
        AxisChar* pachValue);

    BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE, 
        AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, 
        AxisChar* pachValue);

    int addAttribute(Attribute* attr);
    IAttribute* createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, 
        SOAP_VERSION eSOAP_VERSION);

    IAttribute* createAttribute(const AxisChar* localname, 
        const AxisChar* prefix, const AxisChar* uri, const AxisChar* value);

    IAttribute* createAttribute(const AxisChar* localname, 
        const AxisChar* prefix, const AxisChar* value);

    virtual const AxisChar* getAttributeValue(const AxisChar* localname,
         const AxisChar* prefix);
    virtual const AxisChar* getAttributeUri( const AxisChar * localname,
         const AxisChar* prefix);
    BasicNode* createImmediateChild(NODE_TYPE eNODE_TYPE);
    BasicNode* createChild(NODE_TYPE eNODE_TYPE);
    BasicNode* getLastChild();
    BasicNode* getChild(int iChildPosition);
    int addChild(BasicNode* pBasicNode);
    int setLocalName(const AxisChar* localname);
    const AxisChar * getLocalName();
    int setURI(const AxisChar* uri);
    int setPrefix(const AxisChar* prefix);


    /**
      * The Constructor.
      *
      * @param pachLocalName The local name of this Header Block.
      * @param pachPrefix The prefix of this Header Block.
      * @param pachUri The namespace uri of this Header Block.
      */
    HeaderBlock(const AxisChar *pachLocalName, const AxisChar *pachUri, const AxisChar *pachPrefix);

    /**
      * The Constructor.
      *
      * @param pachLocalName The local name of this Header Block.      
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

