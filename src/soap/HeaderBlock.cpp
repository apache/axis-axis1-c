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
 * @author Roshan Weerasuriya (roshanw@jkcsworld.com, roshan@opensource.lk)
 *
 */

/* HeaderBlock.cpp: implementation of the HeaderBlock class. */

/*
 * Revision 1.1  2004/07/01 roshan
 * Added code to "addChild" method to deal with a null child.
 * Added code to createImmediateChild(NODE_TYPE eNODE_TYPE,
 *                                            AxisChar *pachLocalName,
 *                                            AxisChar *pachPrefix,
 *                                            AxisChar *pachUri,
 *                                            AxisChar* pachValue)
 *  to deal with null localname and namespace uri.
 * Added code to addAttribute(Attribute* pAttr) to deal with null values.
 * Added code to createAttribute(const AxisChar *localname,
 *                                        const AxisChar *prefix,
 *                                       const AxisChar *value)
 *  to deal with null values.
 * Added code to addNamespaceDecl(Attribute *pAttribute) to deal with NULL
 *  null values.
 */


#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "HeaderBlock.h"
#include "SoapSerializer.h"
#include <axis/GDefine.hpp>
#include <axis/BasicNode.hpp>
#include "ComplexElement.h"
#include "CharacterElement.h"

AXIS_CPP_NAMESPACE_START

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

HeaderBlock::HeaderBlock()
{
    iNoOFChildren = 0;
	m_sPrefix = "";
}

HeaderBlock::HeaderBlock(const AxisChar *pachLocalName, const AxisChar *pachUri)
{
    iNoOFChildren = 0;
    m_localname = pachLocalName;
    m_uri = pachUri;
    m_sPrefix = "";
}

HeaderBlock::HeaderBlock(const HeaderBlock& rCopy):
IHeaderBlock(rCopy), iNoOFChildren(rCopy.iNoOFChildren), m_localname(rCopy.m_localname),
m_sPrefix(rCopy.m_sPrefix), m_uri(rCopy.m_uri)  
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

IHeaderBlock* HeaderBlock::clone()
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

const AxisChar * HeaderBlock::getLocalName()
{
    return m_localname.c_str();
}
/*
 *  Commented by Susantha - 21/06/2004
 * The prefix should be decided by the Serializer at runtime
 *
 * Uncommented by Mark Whitlock - 24/8/04 after discussion 
 * on the mailing list agreed to add back in this method.
 * Jira issue AXISCPP-135
 */
void HeaderBlock::setPrefix(const AxisChar* prefix)
{
    m_sPrefix= prefix;
}

void HeaderBlock::setUri(const AxisChar* uri)
{
    m_uri= uri;
}

void HeaderBlock::addAttribute(Attribute* pAttr)
{
    if (pAttr)
    {
        m_attributes.push_back(pAttr);
    }
}

int HeaderBlock::serialize(SoapSerializer& pSZ)
{
    /*
     *In the code we don't look whether the m_sPrefix is available or
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

        if(m_sPrefix.length() == 0)
        {
            m_sPrefix = pSZ.getNamespacePrefix(m_uri.c_str(),
                blnIsNewNamespace);
            if (blnIsNewNamespace)
            {
                lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
            }
        }

        pSZ.serialize(m_sPrefix.c_str(), ":", m_localname.c_str(),
            " xmlns:", m_sPrefix.c_str(), "=\"", m_uri.c_str(), "\"", NULL);

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

        pSZ.serialize("</", m_sPrefix.c_str(), ":", m_localname.c_str(), ">",
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
	m_sPrefix = "";
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
        if(m_sPrefix.length() == 0)
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
    if (pBasicNode)
    {
        m_children.push_back(pBasicNode);
        iNoOFChildren++;

        return AXIS_SUCCESS;
    }
    else
    {
        return AXIS_FAIL;
    }
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

IAttribute* HeaderBlock::createNamespaceDecl(const AxisChar *prefix,
        const AxisChar *uri) 
{
    Attribute* pAttribute = new Attribute(prefix, "xmlns", uri);
    m_namespaceDecls.push_back(pAttribute);

    return (IAttribute*)pAttribute; 
}

int HeaderBlock::addNamespaceDecl(IAttribute *pAttribute)
{
    if (pAttribute)
    {
        m_namespaceDecls.push_back((Attribute*)pAttribute);
        return AXIS_SUCCESS;
    }
    else
    {
        return AXIS_FAIL;
    }
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

#ifdef UNIT_TESTING_ON
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
#endif

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

IAttribute* HeaderBlock::createAttribute(const AxisChar *localname,
                                        const AxisChar *prefix,
                                        const AxisChar *value)
{
    Attribute* pAttribute = 0;

    if (localname)
    {
        //Attribute* pAttribute = new Attribute(localname, prefix, value); 
        pAttribute = new Attribute(localname, prefix, value); // Samisa - possible bug in line above 
        m_attributes.push_back(pAttribute);
    }

    return pAttribute;
}

IAttribute* HeaderBlock::createAttribute(const AxisChar *localname,
                                        const AxisChar *prefix,
                                        const AxisChar *uri,
                                        const AxisChar *value)
{
    Attribute* pAttribute = new Attribute(localname, prefix, uri, value);
    m_attributes.push_back(pAttribute);

    return pAttribute;
}

IAttribute* HeaderBlock::createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE 
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

const AxisChar* HeaderBlock::getAttributeValue(const AxisChar *localname,
                                         const AxisChar *prefix)
{
     list<Attribute*>::iterator itAttr = m_attributes.begin();
 	while (itAttr != m_attributes.end()) 
 	{
 		Attribute* pAttribute = *itAttr;
 		if (!strcmp(pAttribute->getLocalName(),localname) &&
 			!strcmp(pAttribute->getPrefix(),prefix)) 
 			return pAttribute->getValue();
 		itAttr++;
 	}
 
     return NULL;
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
            if ( (pachLocalName) && (pachUri) )
            {
                pBasicNode = new ComplexElement(pachLocalName, pachPrefix,
                    pachUri);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }

        if (pBasicNode)
        {
            m_children.push_back(pBasicNode);
            iNoOFChildren++;
        }
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

AXIS_CPP_NAMESPACE_END

