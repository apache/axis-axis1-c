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
 *
 *
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

/* HeaderBlock.cpp: implementation of the HeaderBlock class. */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/server/HeaderBlock.h>
#include <axis/server/SoapSerializer.h>
#include <axis/server/GDefine.h>
#include <axis/server/BasicNode.h>
#include "ComplexElement.h"
#include <axis/server/CharacterElement.h>

HeaderBlock::HeaderBlock()
{
    iNoOFChildren = 0;
}

HeaderBlock::HeaderBlock(AxisChar *pachLocalName, AxisChar *pachPrefix,
                         AxisChar *pachUri)
{
    iNoOFChildren = 0;

    m_localname = pachLocalName;
    m_prefix = pachPrefix;
    m_uri = pachUri;
}

HeaderBlock::HeaderBlock(const HeaderBlock& rCopy):
IHeaderBlock(rCopy), iNoOFChildren(rCopy.iNoOFChildren), m_localname(rCopy.m_localname),
m_prefix(rCopy.m_prefix), m_uri(rCopy.m_uri)  
{

    list<BasicNode*>::const_iterator itCurrChild= rCopy.m_children.begin();
    while(itCurrChild != rCopy.m_children.end())
    {        
        this->m_children.push_back( (*itCurrChild)->clone() );
        itCurrChild++;        
    }

    list<Attribute*>::const_iterator itCurrAttribute= rCopy.m_attributes.begin();
    while(itCurrAttribute != rCopy.m_attributes.end())
    {        
        this->m_attributes.push_back( (*itCurrAttribute)->clone() );
        itCurrAttribute++;        
    }
    
    list<Attribute*>::const_iterator itCurrNamespace= rCopy.m_namespaceDecls.begin();
    while(itCurrNamespace != rCopy.m_namespaceDecls.end())
    {        
        this->m_namespaceDecls.push_back( (*itCurrNamespace)->clone() );
        itCurrNamespace++;        
    }
}

HeaderBlock* HeaderBlock::clone()
{
    return new HeaderBlock(*this);
}

HeaderBlock::~HeaderBlock()
{
    /*
     *Clear the Attributes
     */
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {        
        delete (*itCurrAttribute);
        itCurrAttribute++;        
    }
    m_attributes.clear();

    /*
     *Clear the Namespaces
     */
    list<Attribute*>::iterator itCurrNamespace= m_namespaceDecls.begin();
    while(itCurrNamespace != m_namespaceDecls.end())
    {        
        delete (*itCurrNamespace);
        itCurrNamespace++;        
    }
    m_namespaceDecls.clear();

    /*
     *Clear the children
     */
    list<BasicNode*>::iterator itCurrChild= m_children.begin();
    while(itCurrChild != m_children.end())
    {        
        delete (*itCurrChild);
        itCurrChild++;        
    }
    m_children.clear();
}

void HeaderBlock::setLocalName(const AxisChar* localname)
{
    m_localname= localname;
}

void HeaderBlock::setPrefix(const AxisChar* prefix)
{
    m_prefix= prefix;
}

void HeaderBlock::setUri(const AxisChar* uri)
{
    m_uri= uri;
}

void HeaderBlock::addAttribute(Attribute* attr)
{
    m_attributes.push_back(attr);
}

int HeaderBlock::serialize(SoapSerializer& pSZ)
{
    /*
     *In the code we don't look whether the m_prefix is available or
     *    not. Instead directly insert it. The reason is that the SOAP
     *  1.1 spec says that "All immediate child elements of the SOAP 
     *  Header element MUST be namespace-qualified".
     */

    int iStatus= AXIS_SUCCESS;

    list<AxisChar*> lstTmpNameSpaceStack;
    bool blnIsNewNamespace = false;

    do
    {
        /*
         * TO DO: ReWrite the following logic to deal with name spaces
         */

        pSZ.serialize("<", NULL);

        if(m_prefix.length() == 0)
        {
            m_prefix = pSZ.getNamespacePrefix(m_uri.c_str(),
                blnIsNewNamespace);
            if (blnIsNewNamespace)
            {
                lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
            }
        }

        pSZ.serialize(m_prefix.c_str(), ":", m_localname.c_str(),
            " xmlns:", m_prefix.c_str(), "=\"", m_uri.c_str(), "\"", NULL);

        iStatus= attrSerialize(pSZ, lstTmpNameSpaceStack);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }

        iStatus= serializeNamespaceDecl(pSZ);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        
        pSZ.serialize(">", NULL);

        iStatus= serializeChildren(pSZ, lstTmpNameSpaceStack);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }

        pSZ.serialize("</", m_prefix.c_str(), ":", m_localname.c_str(), ">",
            NULL);

        /*
         * Removing the namespace list of this headerblock from the stack.
         */
        list<AxisChar*>::iterator itCurrentNamespace = 
            lstTmpNameSpaceStack.begin();
        while (itCurrentNamespace != lstTmpNameSpaceStack.end())
        {
            pSZ.removeNamespacePrefix(*itCurrentNamespace);
            itCurrentNamespace++;
        }
            
    } while(0);

    return iStatus;
}

int HeaderBlock::attrSerialize(SoapSerializer& pSZ,
                               list<AxisChar*>& lstTmpNameSpaceStack)
{
    int iStatus= AXIS_SUCCESS;

    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {        
        iStatus= (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        itCurrAttribute++;
    }

    return iStatus;
}

bool HeaderBlock::isSerializable()
{
    bool bStatus= true;    

    if(m_localname.length() == 0)
    {
        bStatus= false;
    }
    else
    {
        if(m_prefix.length() == 0)
        {
            if(m_uri.length() != 0)
            {
                bStatus= false;
            }
        }
        else
        {
            if(m_uri.length() == 0)
            {
                bStatus= false;
            }
        }
    }

    return bStatus;
}

int HeaderBlock::addChild(BasicNode *pBasicNode)
{
    m_children.push_back(pBasicNode);
    iNoOFChildren++;

    return AXIS_SUCCESS;
}

int HeaderBlock::serializeChildren(SoapSerializer& pSZ,
                                   list<AxisChar*>& lstTmpNameSpaceStack)
{
    list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();

    while(itCurrBasicNode != m_children.end())
    {
        if ((*itCurrBasicNode)->getNodeType() == ELEMENT_NODE)
        {
            (*itCurrBasicNode)->serialize(pSZ, lstTmpNameSpaceStack);
        }
        else
        {
            /* for CHARACTER_NODE types */
            (*itCurrBasicNode)->serialize(pSZ);
        }
        itCurrBasicNode++;
    }

    return AXIS_SUCCESS;
}

int HeaderBlock::addNamespaceDecl(Attribute *pAttribute)
{
    m_namespaceDecls.push_back(pAttribute);

    return AXIS_SUCCESS;
}

int HeaderBlock::serializeNamespaceDecl(SoapSerializer &pSZ)
{
    list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

    while(itCurrNamespaceDecl != m_namespaceDecls.end())
    {        
        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    

    return AXIS_SUCCESS;
}

const BasicNode* HeaderBlock::getLastChild()
{
    list<BasicNode*>::reverse_iterator ritCurrBasicNode= m_children.rbegin();

    if (ritCurrBasicNode != m_children.rend())
    {        
        return (*ritCurrBasicNode);
    }    

    return NULL;
}

const BasicNode* HeaderBlock::getChild(int iChildPosition)
{
    if (iChildPosition > iNoOFChildren)
    {
        return NULL;
    }
    else
    {
        list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
        /* The following is done since the previous line already takes the
         * iterator one step forward
         */
        iChildPosition--;

        /* Takes the iterator to the relavent positon */
        for (int i=0; i<iChildPosition; i++)
        {
            itCurrBasicNode++;
        }

        if (itCurrBasicNode != m_children.end())
        {
            return *itCurrBasicNode;
        }
        else
        {
            return NULL;
        }
    }
}

BasicNode* HeaderBlock::createChild(NODE_TYPE eNODE_TYPE)
{
    BasicNode* pBasicNode = NULL;

    if(eNODE_TYPE==CHARACTER_NODE)
    {
        pBasicNode = new CharacterElement();
    }
    else if (eNODE_TYPE==ELEMENT_NODE)
    {
        pBasicNode = new ComplexElement();
    }

    return pBasicNode;
}

int HeaderBlock::initializeForTesting()
{
    setPrefix("m");
    setLocalName("reservation");
    setUri("http://travelcompany.example.org/reservation");

    Attribute* pAttribute2 = new Attribute();
    pAttribute2->setPrefix("SOAP-ENV");
    pAttribute2->setLocalName("role");
    pAttribute2->setValue("http://www.w3.org/2003/05/soap-envelope/role/next");

    Attribute* pAttribute3 = new Attribute();
    pAttribute3->setPrefix("SOAP-ENV");
    pAttribute3->setLocalName("mustUnderstand");
    pAttribute3->setValue("true");

    addAttribute(pAttribute2);
    addAttribute(pAttribute3);

    ComplexElement* pComplexElement = new ComplexElement();
    pComplexElement->setPrefix("m");
    pComplexElement->setLocalName("reference");
    pComplexElement->addChild(new CharacterElement("abcdefgh"));

    ComplexElement* pComplexElement2 = new ComplexElement();
    pComplexElement2->setPrefix("m");
    pComplexElement2->setLocalName("dateAndTime");
    pComplexElement2->addChild(new 
        CharacterElement("2001-11-29T13:20:00.000-05:00"));

    addChild(pComplexElement);
    addChild(pComplexElement2);

    return AXIS_SUCCESS;    
}

bool HeaderBlock::operator ==( const HeaderBlock &objHeaderBlock)
{
    /*
     * TODO : the logic
     */
    return true;
}

BasicNode* HeaderBlock::createImmediateChild(NODE_TYPE eNODE_TYPE)
{
    BasicNode* pBasicNode = NULL;

    do
    {
        if(eNODE_TYPE==CHARACTER_NODE)
        {
            pBasicNode = new CharacterElement();
        }
        else if (eNODE_TYPE==ELEMENT_NODE)
        {
            pBasicNode = new ComplexElement();
        }
        else
        {
            break;
        }

        m_children.push_back(pBasicNode);
        iNoOFChildren++;
    } while (0);

    return pBasicNode;
}

Attribute* HeaderBlock::createAttribute(const AxisChar *localname,
                                        const AxisChar *prefix,
                                        const AxisChar *value)
{
    Attribute* pAttribute = new Attribute(localname, prefix, value);
    m_attributes.push_back(pAttribute);

    return pAttribute;
}

Attribute* HeaderBlock::createAttribute(const AxisChar *localname,
                                        const AxisChar *prefix,
                                        const AxisChar *uri,
                                        const AxisChar *value)
{
    Attribute* pAttribute = new Attribute(localname, prefix, uri, value);
    m_attributes.push_back(pAttribute);

    return pAttribute;
}

Attribute* HeaderBlock::createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE 
                                           eStdAttrType, 
                                           SOAP_VERSION eSOAP_VERSION)
{
    Attribute* pAttribute = NULL;
    bool blnStatus = true;

    do
    {
        switch(eSOAP_VERSION)
        {
            case VERSION_LAST:
                blnStatus = false;
                break;
            case SOAP_VER_1_1:
                switch(eStdAttrType)
                {
                    case ACTOR:
                        pAttribute = new Attribute("actor",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix,
                            "","http://schemas.xmlsoap.org/soap/actor/next");
                        break;
                    case MUST_UNDERSTAND_TRUE:
                        pAttribute = new Attribute("mustUnderstand",
                            gs_SoapEnvVersionsStruct
                            [SOAP_VER_1_1].pchPrefix,"","1");
                        break;
                    case MUST_UNDERSTAND_FALSE:
                        pAttribute = new Attribute("mustUnderstand",
                            gs_SoapEnvVersionsStruct
                            [SOAP_VER_1_1].pchPrefix,"","0");
                        break;
                    default:
                        blnStatus = false;
                        break;
                }
                break;

            case SOAP_VER_1_2:
                switch(eStdAttrType)
                {
                    case ROLE_NEXT:
                        pAttribute = new Attribute("role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","http://www.w3.org/2003/05/soap-envelope \
                            /role/next");
                        break;
                    case ROLE_NONE:
                        pAttribute = new Attribute("role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","http://www.w3.org/2003/05/soap-envelope\
                            /role/none");
                        break;
                    case ROLE_ULTIMATE_RECEIVER:
                        pAttribute = new Attribute("role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","http://www.w3.org/2003/05/soap-envelope/role\
                            /ultimateReceiver");
                        break;
                    case MUST_UNDERSTAND_TRUE:
                        pAttribute = new Attribute("mustUnderstand",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","true");
                        break;
                    case MUST_UNDERSTAND_FALSE:
                        pAttribute = new Attribute("mustUnderstand",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","false");
                        break;
                    default:
                        blnStatus = false;
                        break;
                }
                break;

            default:
                blnStatus = false;
                break;
        }
    } while (0);
    

    if (blnStatus)
    {
        m_attributes.push_back(pAttribute);
        return pAttribute;
    }
    else
    {
        return NULL;
    }
}

BasicNode* HeaderBlock::createImmediateChild(NODE_TYPE eNODE_TYPE,
                                             AxisChar *pachLocalName,
                                             AxisChar *pachPrefix,
                                             AxisChar *pachUri,
                                             AxisChar* pachValue)
{
    BasicNode* pBasicNode = NULL;

    do
    {

        if(eNODE_TYPE==CHARACTER_NODE)
        {
            pBasicNode = new CharacterElement(pachValue);
        }
        else if (eNODE_TYPE==ELEMENT_NODE)
        {
            pBasicNode = new ComplexElement(pachLocalName, pachPrefix,
                pachUri);
        }
        else
        {
            break;
        }

        m_children.push_back(pBasicNode);
        iNoOFChildren++;
    } while (0);

    return pBasicNode;
}

BasicNode* HeaderBlock::createChild(NODE_TYPE eNODE_TYPE,
                                    AxisChar *pachLocalName,
                                    AxisChar *pachPrefix, AxisChar *pachUri,
                                    AxisChar *pachValue)
{
    BasicNode* pBasicNode = NULL;

    do
    {
        if(eNODE_TYPE==CHARACTER_NODE)
        {
            pBasicNode = new CharacterElement(pachValue);
        }
        else if (eNODE_TYPE==ELEMENT_NODE)
        {
            pBasicNode = new ComplexElement(pachLocalName, pachPrefix,
                pachUri);
        }
        else
        {
            break;
        }
    } while (0);

    return pBasicNode;
}

int HeaderBlock::getNoOfChildren()
{
    return iNoOFChildren;
}

const BasicNode* HeaderBlock::getFirstChild()
{
    list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
    
    if (itCurrBasicNode != m_children.end())
    {        
        return (*itCurrBasicNode);
    }

    return NULL;
}
