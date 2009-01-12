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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <iostream>

#include <axis/GDefine.hpp>
#include <axis/BasicNode.hpp>

#include "HeaderBlock.h"
#include "SoapSerializer.h"
#include "ComplexElement.h"
#include "CharacterElement.h"
#include "Namespace.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

HeaderBlock::
HeaderBlock()
{
    logEntryEngine("HeaderBlock::HeaderBlock")

    iNoOFChildren = 0;
    m_sPrefix = "";
    
    logExit()
}

HeaderBlock::
HeaderBlock(const AxisChar *pachLocalName, const AxisChar *pachUri)
{
    logEntryEngine("HeaderBlock::HeaderBlock")

    iNoOFChildren = 0;
    m_localname = pachLocalName;
    m_uri = pachUri;
    m_sPrefix = "";

    logExit()
}

HeaderBlock::
HeaderBlock(const AxisChar *pachLocalName, const AxisChar *pachUri, const AxisChar *pachPrefix)
{
    logEntryEngine("HeaderBlock::HeaderBlock")

    iNoOFChildren = 0;
    m_localname = pachLocalName;
    m_uri = pachUri;
    m_sPrefix = pachPrefix;

    logExit()
}

HeaderBlock::
HeaderBlock(const HeaderBlock& rCopy):
IHeaderBlock(rCopy), iNoOFChildren(rCopy.iNoOFChildren), m_localname(rCopy.m_localname),
m_sPrefix(rCopy.m_sPrefix), m_uri(rCopy.m_uri)  
{
    logEntryEngine("HeaderBlock::HeaderBlock")

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

    /* TO DO: check whether we have to do this 
    *
    list<Namespace*>::const_iterator itCurrNamespace= rCopy.m_namespaceDecls.begin();
    while(itCurrNamespace != rCopy.m_namespaceDecls.end())
    {        
        this->m_namespaceDecls.push_back( (*itCurrNamespace)->clone() );
        itCurrNamespace++;        
    }
    */
    logExit()
}

IHeaderBlock* HeaderBlock::
clone()
{
    return new HeaderBlock(*this);
}

HeaderBlock::
~HeaderBlock()
{
    logEntryEngine("HeaderBlock::~HeaderBlock")

    // Clear the Attributes
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {        
        delete (*itCurrAttribute);
        itCurrAttribute++;        
    }
    m_attributes.clear();

    // Clear the Namespaces
    list<Namespace*>::iterator itCurrNamespace= m_namespaceDecls.begin();
    while(itCurrNamespace != m_namespaceDecls.end())
    {        
        delete (*itCurrNamespace);
        itCurrNamespace++;        
    }
    m_namespaceDecls.clear();

    // Clear the children
    list<BasicNode*>::iterator itCurrChild= m_children.begin();
    while(itCurrChild != m_children.end())
    {        
        delete (*itCurrChild);
        itCurrChild++;        
    }
    m_children.clear();
    
    logExit()
}

int HeaderBlock::
setLocalName(const AxisChar* localname)
{
    logEntryEngine("HeaderBlock::setLocalName")

    int Status = AXIS_FAIL;
    
    if(localname)
    {
        m_localname=localname;
        Status = AXIS_SUCCESS;
    }
    
    logExitWithReturnCode(Status)
    
    return Status;
}

const AxisChar * HeaderBlock::
getLocalName()
{
    return m_localname.c_str();
}

int HeaderBlock::
setPrefix(const AxisChar* prefix)
{
    logEntryEngine("HeaderBlock::setPrefix")

    if(prefix)
        m_sPrefix= prefix;
    else
        m_sPrefix="";

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int HeaderBlock::
setURI(const AxisChar* uri)
{
    logEntryEngine("HeaderBlock::setURI")

    if(uri)
        m_uri= uri;
    else
        m_uri="";
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int HeaderBlock::
addAttribute(Attribute* pAttr)
{
    logEntryEngine("HeaderBlock::addAttribute")

    int Status = AXIS_FAIL;
    if (pAttr)
    {
        m_attributes.push_back(pAttr);
        Status = AXIS_SUCCESS;
    }

    logExitWithReturnCode(Status)

    return Status;
}

int HeaderBlock::
serialize(SoapSerializer& pSZ)
{
    logEntryEngine("HeaderBlock::serialize")

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
        // TO DO: ReWrite the following logic to deal with name spaces
        pSZ.serialize("<", NULL);

        if(m_sPrefix.length() == 0)
        {
            m_sPrefix = pSZ.getNamespacePrefix(m_uri.c_str(), blnIsNewNamespace);
            if (blnIsNewNamespace)
                lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
        } 
        else 
        {
            //  new namespace and will be declared as a namespace declaration.
            blnIsNewNamespace = true;
            /* Adding to the Serializers namespace list b'cas the child 
            elements of this HeaderBlock might use this namespace, so that they
            can get the correct corrosponding prefix from the Serializer.
             */
            pSZ.addNamespaceToNamespaceList(m_uri.c_str(), m_sPrefix.c_str());
            /* Adding this namespace to the temprory namespace list b'cas we
            have to remove this namespce from the Serializer at the end of this
            HeaderBlock serialization.
            */
            lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
        }

        pSZ.serialize(m_sPrefix.c_str(), ":", m_localname.c_str(), NULL);
        
        if (blnIsNewNamespace) 
            pSZ.serialize(" xmlns:", m_sPrefix.c_str(), "=", PLATFORM_DOUBLE_QUOTE_S, m_uri.c_str(), PLATFORM_DOUBLE_QUOTE_S, NULL);

        iStatus= attrSerialize(pSZ, lstTmpNameSpaceStack);
        if(iStatus==AXIS_FAIL)
            break;

        iStatus= serializeNamespaceDecl(pSZ, lstTmpNameSpaceStack);
        if(iStatus==AXIS_FAIL)
            break;
        
        pSZ.serialize(">", NULL);

        iStatus= serializeChildren(pSZ, lstTmpNameSpaceStack);
        if(iStatus==AXIS_FAIL)
            break;

        pSZ.serialize("</", m_sPrefix.c_str(), ":", m_localname.c_str(), ">", NULL);

        // Removing the namespace list of this headerblock from the stack.
        list<AxisChar*>::iterator itCurrentNamespace = lstTmpNameSpaceStack.begin();
        while (itCurrentNamespace != lstTmpNameSpaceStack.end())
        {
            pSZ.removeNamespacePrefix(*itCurrentNamespace);
            itCurrentNamespace++;
        }
            
    } 
    while(0);
    
    m_sPrefix = "";
    
    logExitWithReturnCode(iStatus)

    return iStatus;
}

int HeaderBlock::
attrSerialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
    logEntryEngine("HeaderBlock::attrSerialize")

    int iStatus= AXIS_SUCCESS;

    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {    
        // See if this prefix matches a namespace within this headerblock
        const AxisChar *uri = NULL;
        Attribute *attr = *itCurrAttribute;
        const AxisChar *attrPrefix = attr->getPrefix();
        if (NULL != attrPrefix)
        {
            list<Namespace*>::iterator itNs = m_namespaceDecls.begin();
            while (itNs != m_namespaceDecls.end())
            {
                if (0 == strcmp((*itNs)->getPrefix(), attrPrefix))
                {
                    uri = (*itNs)->getURI();
                    break;
                }
                itNs++;
            }
        }

        iStatus= (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack, uri);
        if(iStatus==AXIS_FAIL)
        {
            break;
        }
        itCurrAttribute++;
    }

    logExitWithReturnCode(iStatus)

    return iStatus;
}

bool HeaderBlock::
isSerializable()
{
    logEntryEngine("HeaderBlock::isSerializable")

    bool bStatus= true;

    if(m_localname.length() == 0)
        bStatus= false;
    else
    {
        if(m_sPrefix.length() == 0)
        {
            if(m_uri.length() != 0)
                bStatus= false;
        }
        else
        {
            if(m_uri.length() == 0)
                bStatus= false;
        }
    }
    
    logExitWithBoolean(bStatus)

    return bStatus;
}

int HeaderBlock::
addChild(BasicNode *pBasicNode)
{
    logEntryEngine("HeaderBlock::addChild")

    int iStatus = AXIS_FAIL;

    if (pBasicNode)
    {
        m_children.push_back(pBasicNode);
        iNoOFChildren++;

        iStatus = AXIS_SUCCESS;
    }

    logExitWithReturnCode(iStatus)

    return iStatus;
}

int HeaderBlock::
serializeChildren(SoapSerializer& pSZ, list<AxisChar *>& lstTmpNameSpaceStack)
{
    logEntryEngine("HeaderBlock::serializeChildren")

    int iStatus = AXIS_SUCCESS;

    // SOAP serialiser does not have an == operator so can't check it
    list<BasicNode*>::iterator itCurrBasicNode = m_children.begin();

    while( itCurrBasicNode != m_children.end() && iStatus == AXIS_SUCCESS)
    {
        if ((*itCurrBasicNode)->getNodeType() == ELEMENT_NODE)
        {
            // Processing for ELEMENT_NODE types
            iStatus = (*itCurrBasicNode)->serialize( pSZ, lstTmpNameSpaceStack);
        }
        else
        {
            // Processing for CHARACTER_NODE types
            iStatus = (*itCurrBasicNode)->serialize( pSZ);
        }

        itCurrBasicNode++;
    }

    logExitWithReturnCode(iStatus)

    return iStatus;
}

INamespace* HeaderBlock::
createNamespaceDecl( const AxisChar * pPrefix, const AxisChar * pURI) 
{
    logEntryEngine("HeaderBlock::createNamespaceDecl")
    
    INamespace* returnPtr = NULL;

    // Check that the prefix and uri are valid pointers and that the string is not empty.
    if( pPrefix != NULL && strlen( pPrefix) > 0 && pURI != NULL && strlen( pURI) > 0)
    {
        // Iterate through the namespaces checking that the prefix does not already exist.
        bool bNameFound = false;
        list<Namespace*>::iterator    itCurrNamespaceDecl = m_namespaceDecls.begin();

        while( itCurrNamespaceDecl != m_namespaceDecls.end() && !bNameFound)
        {
            if( !(bNameFound = !strcmp( (*itCurrNamespaceDecl)->getPrefix(), pPrefix)))
                itCurrNamespaceDecl++;
        }    

        // If the prefix is found in the declared namespace list, then update the uri
        // for the prefix and return a pointer to that namespace.
        // If the prefix was not found, then create a new namespace for the prefix/uri
        // pair and return the pointer to the new namespace.
        if( bNameFound)
        {
            (*itCurrNamespaceDecl)->setURI( pURI);
            returnPtr = (INamespace *) *itCurrNamespaceDecl;
        }
        else
        {
            Namespace *    pNamespace = new Namespace( pPrefix, pURI);
            m_namespaceDecls.push_back( pNamespace);
            returnPtr = (INamespace *) pNamespace; 
        }
    }
    
    logExitWithPointer(returnPtr)
    
    return returnPtr;
}

int HeaderBlock::
serializeNamespaceDecl(SoapSerializer &pSZ, std::list<AxisChar*>& lstTmpNameSpaceStack)
{
    logEntryEngine("HeaderBlock::serializeNamespaceDecl")

    list<Namespace*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

    while(itCurrNamespaceDecl != m_namespaceDecls.end())
    {        
        (*itCurrNamespaceDecl)->serialize(pSZ, lstTmpNameSpaceStack);
        itCurrNamespaceDecl++;        
    }    

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

BasicNode* HeaderBlock::
getLastChild()
{
    logEntryEngine("HeaderBlock::getLastChild")

    BasicNode* returnPtr = NULL;
    
    list<BasicNode*>::reverse_iterator ritCurrBasicNode= m_children.rbegin();

    if (ritCurrBasicNode != m_children.rend())       
        returnPtr = *ritCurrBasicNode;    

    logExitWithPointer(returnPtr)

    return returnPtr;
}

BasicNode* HeaderBlock::
getChild(int iChildPosition)
{
    logEntryEngine("HeaderBlock::getChild")

    BasicNode* returnPtr = NULL;

    if ( (iChildPosition<=0) || (iChildPosition > iNoOFChildren) )
        returnPtr = NULL;
    else
    {
        list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
        // following is done since the previous line already takes the iterator one step forward
        iChildPosition--;

        /* Takes the iterator to the relavent positon */
        for (int i=0; i<iChildPosition; i++)
        {
            itCurrBasicNode++;
        }

        if (itCurrBasicNode != m_children.end())
            returnPtr = *itCurrBasicNode;
    }
    
    logExitWithPointer(returnPtr)

    return returnPtr;
}

BasicNode* HeaderBlock::
createChild(NODE_TYPE eNODE_TYPE)
{
    logEntryEngine("HeaderBlock::createChild")

    BasicNode* pBasicNode = NULL;

    if(eNODE_TYPE==CHARACTER_NODE)
        pBasicNode = new CharacterElement();
    else if (eNODE_TYPE==ELEMENT_NODE)
        pBasicNode = new ComplexElement();

    logExitWithPointer(pBasicNode)

    return pBasicNode;
}

bool HeaderBlock::
operator ==( const HeaderBlock &objHeaderBlock)
{
    /*
     * TODO : the logic
     */
    return true;
}

BasicNode* HeaderBlock::createImmediateChild(NODE_TYPE eNODE_TYPE)
{
    return createImmediateChild(eNODE_TYPE, "", "", "", "");
}

/**
 * The localname must be specified, but all other input parameters are optional.
 */
IAttribute* HeaderBlock::createAttribute(const AxisChar *localname,
                                        const AxisChar *prefix,
                                        const AxisChar *value)
{
    return createAttribute(localname, prefix, NULL, value);
}

/**
 * The localname must be specified, but all other input parameters are optional.
 */
IAttribute* HeaderBlock::createAttribute(const AxisChar * pLocalName,
                                         const AxisChar * pPrefix,
                                         const AxisChar * pURI,
                                         const AxisChar * pValue)
{
    logEntryEngine("HeaderBlock::createAttribute")

    // Check that the contents of the passed parameters are valid.
    if( NULL == pLocalName || 0 == strlen( pLocalName))
    {
        logExitWithPointer(NULL)

        return NULL;
    }

    if( !pPrefix)
        pPrefix = "";

    if( !pURI)
        pURI = "";

    if( !pValue)
        pValue = "";

    // Check that the local name and prefix have not already been defined.  If
    // they have, then return NULL indicating that the prefix/localname pair have
    // already been defined.
    list<Attribute*>::iterator    itCurrAttribute= m_attributes.begin();

    while( itCurrAttribute != m_attributes.end())
    {        
        if( (strcmp( (*itCurrAttribute)->getLocalName(), pLocalName) == 0) && 
            (strcmp( (*itCurrAttribute)->getPrefix(), pPrefix) == 0))
        {
            logExitWithPointer(NULL)

            return NULL;
        }
        else
        {
            itCurrAttribute++;
        }
    }    

    // Check that the prefix has not already been defined in the namespace
    // declarations.  If it has, then return NULL indicating that the
    // prefix/localname pair has already been defined and 'copy down' the
    // namespace decl into the attribute list as this will help in the
    // serialisation.
    list<Namespace*>::iterator    itCurrNamespaceDecls = m_namespaceDecls.begin();

    while( itCurrNamespaceDecls != m_namespaceDecls.end())
    {        
        if( !strcmp( (*itCurrNamespaceDecls)->getPrefix(), pPrefix))
        {
            Attribute *    pAttribute = new Attribute( m_attributes, pLocalName,
                                                    pPrefix,
                                                    (*itCurrNamespaceDecls)->getURI(),
                                                    pValue);

            m_attributes.push_back( pAttribute);

            logExitWithPointer(pAttribute)

            return pAttribute;
        }
        else
        {
            itCurrNamespaceDecls++;
        }
    }    

    // If the prefix/localname pair have not previously been defined, then create
    // and return the attribute.
    Attribute *    pAttribute = new Attribute( m_attributes, pLocalName, pPrefix, pURI, pValue);

    m_attributes.push_back( pAttribute);

    logExitWithPointer(pAttribute)
    
    return pAttribute;
}

IAttribute* HeaderBlock::
createStdAttribute(HEADER_BLOCK_STD_ATTR_TYPE eStdAttrType, SOAP_VERSION eSOAP_VERSION)
{
    logEntryEngine("HeaderBlock::createStdAttribute")

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
                        pAttribute = new Attribute(m_attributes, "actor",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_1].pchPrefix,
                            "","http://schemas.xmlsoap.org/soap/actor/next");
                        break;
                    case MUST_UNDERSTAND_TRUE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
                            gs_SoapEnvVersionsStruct
                            [SOAP_VER_1_1].pchPrefix,"","1");
                        break;
                    case MUST_UNDERSTAND_FALSE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
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
                        pAttribute = new Attribute(m_attributes, "role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "", "http://www.w3.org/2003/05/soap-envelope/role/next");
                        break;
                    case ROLE_NONE:
                        pAttribute = new Attribute(m_attributes, "role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "", "http://www.w3.org/2003/05/soap-envelope/role/none");
                        break;
                    case ROLE_ULTIMATE_RECEIVER:
                        pAttribute = new Attribute(m_attributes, "role",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "", "http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver");
                        break;
                    case MUST_UNDERSTAND_TRUE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
                            gs_SoapEnvVersionsStruct[SOAP_VER_1_2].pchPrefix,
                            "","true");
                        break;
                    case MUST_UNDERSTAND_FALSE:
                        pAttribute = new Attribute(m_attributes, "mustUnderstand",
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
        // got to check for duplicate attributes
        list<Attribute*>::iterator itAttr = m_attributes.begin();
        while (itAttr != m_attributes.end())
        {
                Attribute* pCurrentAttribute = *itAttr;
                if (!strcmp(pCurrentAttribute->getLocalName(),pAttribute->getLocalName() ) &&
                        !strcmp(pCurrentAttribute->getPrefix(), pAttribute->getPrefix() ) )
                {
                    // we have the attribute set already, so only change the value
                    pCurrentAttribute->setValue( pAttribute->getValue() );
                    delete pAttribute;
                    
                    logExitWithPointer(pCurrentAttribute)

                    return pCurrentAttribute; 
                }
                
                itAttr++;
        }

        // we do not have the attribute set already, hence add it
        m_attributes.push_back(pAttribute);
        
        logExitWithPointer(pAttribute)
        
        return pAttribute;
    }
    else
    {
        logExitWithPointer(NULL)

        return NULL;
    }
}

const AxisChar* HeaderBlock::
getAttributeValue(const AxisChar *localname, const AxisChar *prefix)
{
    logEntryEngine("HeaderBlock::getAttributeValue")

    const AxisChar* returnValue = NULL;

     if(!localname)
        localname="";

     if(!prefix)
        prefix="";
 
       list<Attribute*>::iterator itAttr = m_attributes.begin();
     while (itAttr != m_attributes.end()) 
     {
         Attribute* pAttribute = *itAttr;
         if (!strcmp(pAttribute->getLocalName(),localname) &&
             !strcmp(pAttribute->getPrefix(),prefix)) 
             {
                 returnValue = pAttribute->getValue();
                 break;
             }
         itAttr++;
     }
     
    logExitWithString(returnValue)

    return returnValue;
}
 
const AxisChar * HeaderBlock::
getAttributeUri( const AxisChar * localname,  const AxisChar * prefix)
{
    logEntryEngine("HeaderBlock::getAttributeUri")

    const AxisChar* returnValue = NULL;
    
    list<Attribute*>::iterator itAttr = m_attributes.begin();

    while( itAttr != m_attributes.end()) 
    {
        Attribute * pAttribute = *itAttr;

        if( !strcmp( pAttribute->getLocalName(),localname) &&
            !strcmp( pAttribute->getPrefix(),prefix)) 
        {
            returnValue = pAttribute->getURI();
            break;
        }
        
        if( strlen( localname) == 0 && !strcmp( pAttribute->getPrefix(), prefix)) 
        {
            returnValue = pAttribute->getURI();
            break;
        }

        itAttr++;
    }

    logExitWithString(returnValue)

    return returnValue;
}

BasicNode* HeaderBlock::
createImmediateChild(NODE_TYPE eNODE_TYPE, AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri, AxisChar* pachValue)
{
    logEntryEngine("HeaderBlock::createImmediateChild")

    BasicNode* pBasicNode = NULL;
    if(!pachLocalName)
     pachLocalName="";

    if(!pachPrefix)
     pachPrefix="";

    if(!pachUri)
     pachUri="";

    if(!pachValue)
     pachValue="";
    
    do
    {
        if(eNODE_TYPE==CHARACTER_NODE)
            pBasicNode = new CharacterElement(pachValue);
        else if (eNODE_TYPE==ELEMENT_NODE)
        {
            if ( (pachLocalName) && (pachUri) )
                pBasicNode = new ComplexElement(pachLocalName, pachPrefix, pachUri);
            else
                break;
        }
        else
            break;

        if (pBasicNode)
        {
            m_children.push_back(pBasicNode);
            iNoOFChildren++;
        }
    } 
    while (0);

    logExitWithPointer(pBasicNode)
    
    return pBasicNode;
}

BasicNode* HeaderBlock::
createChild(NODE_TYPE eNODE_TYPE, AxisChar *pachLocalName,
            AxisChar *pachPrefix, AxisChar *pachUri, AxisChar *pachValue)
{
    logEntryEngine("HeaderBlock::createChild")

    BasicNode* pBasicNode = NULL;
    if(!pachLocalName)
     pachLocalName="";

    if(!pachPrefix)
     pachPrefix="";

    if(!pachUri)
     pachUri="";
    
    if(!pachValue)
     pachValue="";

    do
    {
        if(eNODE_TYPE==CHARACTER_NODE)
            pBasicNode = new CharacterElement(pachValue);
        else if (eNODE_TYPE==ELEMENT_NODE)
            pBasicNode = new ComplexElement(pachLocalName, pachPrefix, pachUri);
        else
            break;
    } 
    while (0);

    logExitWithPointer(pBasicNode)

    return pBasicNode;
}

int HeaderBlock::getNoOfChildren()
{
    return iNoOFChildren;
}

BasicNode* HeaderBlock::
getFirstChild()
{
    logEntryEngine("HeaderBlock::getFirstChild")

    BasicNode* returnValue = NULL;
    
    list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();
    
    if (itCurrBasicNode != m_children.end())
    {        
        returnValue = (*itCurrBasicNode);
    }

    logExitWithPointer(returnValue)

    return returnValue;
}



AXIS_CPP_NAMESPACE_END
