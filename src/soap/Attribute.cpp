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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include "Attribute.h"
#include "SoapSerializer.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

Attribute::Attribute( list<Attribute*> attribute)
{
    if( (void *) &attribute != NULL && !attribute.empty())
    {
        list<Attribute*>::iterator itAttributeList = attribute.begin();

        while( itAttributeList != attribute.end())
        {
            m_PrefixList.push_back( (*itAttributeList)->getPrefix());

            itAttributeList++;
        }
    }
}

Attribute::~Attribute()
{
    m_PrefixList.clear();
}

int Attribute::setLocalName(const AxisChar* localname)
{
    if(NULL==localname)
    {
        localname="";
    }

    m_localname= localname;
    return AXIS_SUCCESS;
}

int Attribute::setPrefix(const AxisChar* prefix)
{
    if( NULL == prefix)
    {
        prefix = "";
    }

    if( (void *) &m_PrefixList != NULL && !m_PrefixList.empty())
    {
        list<const char*>::iterator itPrefixList = m_PrefixList.begin();

        while( itPrefixList != m_PrefixList.end())
        {
            if( !strcmp( (*itPrefixList), prefix))
            {
                return AXIS_FAIL;
            }
            else
            {
                itPrefixList++;
            }
        }
    }

    m_prefix = prefix;

    return AXIS_SUCCESS;
}

int Attribute::setURI(const AxisChar* uri)
{
    if(NULL==uri)
    {
        uri="";
    }
    
    /**
     * sets the prefix according to the URI
     */
    
    if(m_prefix != "")
    {

        
        bool bPrefixFound = false;
        list<Namespace*>::iterator    itCurrNamespaceDecl = m_namespaceDecls.begin();

        while( itCurrNamespaceDecl != m_namespaceDecls.end() && !bPrefixFound)
        {
            if( !(bPrefixFound = !strcmp( (*itCurrNamespaceDecl)->getURI(), uri)))
            {
                itCurrNamespaceDecl++;
            }
        }    

        
        if( bPrefixFound)
        {
            setPrefix((*itCurrNamespaceDecl)->getPrefix());

        }
        else
        {
            setPrefix(NULL);
        }
    }
        
    m_uri= uri;
    return AXIS_SUCCESS;
}

int Attribute::setValue(const AxisChar* value)
{
    if(NULL==value)
    {
        value="";
    }
    m_value= value;
    return AXIS_SUCCESS;
}


const AxisChar* Attribute::getLocalName()
{
    return m_localname.c_str();
}

const AxisChar* Attribute::getPrefix()
{
    return m_prefix.c_str();
}

const AxisChar* Attribute::getURI()
{
    return m_uri.c_str();
}

const AxisChar* Attribute::getValue()
{
    return m_value.c_str();
}
 



Attribute::Attribute(list<Attribute*> attribute, const AxisChar* localname, const AxisChar* prefix, 
                     const AxisChar* uri, const AxisChar* value)
{
    m_localname= localname;
    m_prefix= prefix;
    m_uri= uri;
    if (NULL==value)
        m_value = "";
    else
        m_value= value;

    if( (void *) &attribute != NULL && !attribute.empty())
    {
        list<Attribute*>::iterator itAttributeList = attribute.begin();

        while( itAttributeList != attribute.end())
        {
            m_PrefixList.push_back( (*itAttributeList)->getPrefix());

            itAttributeList++;
        }
    }

    if( prefix != NULL && strlen( prefix) > 0)
    {
        m_PrefixList.push_back( prefix);
    }
}

Attribute::Attribute(list<Attribute*> attribute, const AxisChar *localname, const AxisChar *prefix, 
                     const AxisChar *value)
{
    m_localname= localname;
    m_prefix= prefix;
    m_uri= "";
    if (NULL==value)
        m_value = "";
    else
        m_value= value;

    if( (void *) &attribute != NULL && !attribute.empty())
    {
        list<Attribute*>::iterator itAttributeList = attribute.begin();

        while( itAttributeList != attribute.end())
        {
            m_PrefixList.push_back( (*itAttributeList)->getPrefix());

            itAttributeList++;
        }
    }

    if( prefix != NULL && strlen( prefix) > 0)
    {
        m_PrefixList.push_back( prefix);
    }
}

Attribute::Attribute(list<Attribute*> attribute, const Attribute& rCopy)
{
    //in case sting is changed to char* use new[] and strcpy here
    this->m_localname= rCopy.m_localname; 
    this->m_prefix= rCopy.m_prefix;
    this->m_uri= rCopy.m_uri;
    this->m_value= rCopy.m_value;

    if( (void *) &attribute != NULL && !attribute.empty())
    {
        list<Attribute*>::iterator itAttributeList = attribute.begin();

        while( itAttributeList != attribute.end())
        {
            m_PrefixList.push_back( (*itAttributeList)->getPrefix());

            itAttributeList++;
        }
    }

    if( rCopy.m_prefix.length() > 0)
    {
        m_PrefixList.push_back( rCopy.m_prefix.c_str());
    }
}

Attribute* Attribute::clone()
{
    return new Attribute(*this);
}


/*
 *
 */
int Attribute::serialize(SoapSerializer& pSZ) const
{    
    int intStatus= AXIS_FAIL;

    if (isSerializable())
    {        
        pSZ.serialize(" ", NULL);

        if(!m_prefix.empty())
        {            
            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }

        pSZ.serialize(m_localname.c_str(), "=", PLATFORM_DOUBLE_QUOTE_S, m_value.c_str(), PLATFORM_DOUBLE_QUOTE_S, NULL);

        intStatus= AXIS_SUCCESS;
    }

    return intStatus;    
}

int Attribute::serialize(SoapSerializer& pSZ, 
                         list<AxisChar*>& lstTmpNameSpaceStack,
                         const AxisChar *uri)
{    
    int intStatus= AXIS_FAIL;

    if (isSerializable() && (!pSZ.getNamespaceURL( m_prefix).empty() || NULL!=uri))
    {        
        pSZ.serialize(" ", NULL);

        /*
         * User has provided the prefix. So we just have to serialilze. We will
         *  not worry to declare the namespace at all. Because it is the users
         *  responsibiltiy to add his/her namespace declaration seperately.
         */
        if(!m_prefix.empty() || NULL!=uri)
        {            
            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }
        /*
         * User hasn't provided the prefix. So we have to do the following.
         *  - get the prefix from the Serializer
         *  - if this is a new namespace, then also declare the namespace.
         */
        else if (!m_uri.empty())
        {
            bool blnIsNewNamespace = false;
            m_prefix = pSZ.getNamespacePrefix(m_uri.c_str(), 
                blnIsNewNamespace);
            if (blnIsNewNamespace)
            {
                lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
                pSZ.serialize("xmlns:", m_prefix.c_str(), "=", PLATFORM_DOUBLE_QUOTE_S, m_uri.c_str(), PLATFORM_DOUBLE_QUOTE_S, " ", NULL);
            }

            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }

        pSZ.serialize(m_localname.c_str(), "=", PLATFORM_DOUBLE_QUOTE_S, m_value.c_str(), PLATFORM_DOUBLE_QUOTE_S, NULL);

        intStatus= AXIS_SUCCESS;
    }

    return intStatus;    
}

bool Attribute::isSerializable() const
{
    bool bStatus= true;

    if(m_localname.empty())
    {
        bStatus= false;
    }

    return bStatus;
}

#ifdef UNIT_TESTING_ON
int Attribute::initializeForTesting()
{
    m_prefix = "pr";
    m_localname = "age";
    m_uri = "http://myurl.com";
    m_value = "25";

    return AXIS_SUCCESS;
}
#endif


AXIS_CPP_NAMESPACE_END
