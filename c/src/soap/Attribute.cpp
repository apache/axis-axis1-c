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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added copy constructor
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/server/Attribute.h>
#include <axis/server/GDefine.h>
#include <axis/server/SoapSerializer.h>

Attribute::Attribute()
{
    
}

Attribute::~Attribute()
{

}

void Attribute::setLocalName(const AxisChar* localname)
{
    m_localname= localname;
}

void Attribute::setPrefix(const AxisChar* prefix)
{
    m_prefix= prefix;
}

void Attribute::setUri(const AxisChar* uri)
{
    m_uri= uri;
}

void Attribute::setValue(const AxisChar* value)
{
    m_value= value;
}

Attribute::Attribute(const AxisChar* localname, const AxisChar* prefix, 
                     const AxisChar* uri, const AxisChar* value)
{
    m_localname= localname;
    m_prefix= prefix;
    m_uri= uri;
    m_value= value;
}

Attribute::Attribute(const Attribute& rCopy)
{
    this->m_localname= rCopy.m_localname; //in casse sting is changed to char* use strdup here
    this->m_prefix= rCopy.m_prefix;
    this->m_uri= rCopy.m_uri;
    this->m_value= rCopy.m_value;
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

        pSZ.serialize(m_localname.c_str(), "=\"", m_value.c_str(), "\"", NULL);

        intStatus= AXIS_SUCCESS;
    }

    return intStatus;    
}

int Attribute::serialize(SoapSerializer& pSZ, 
                         list<AxisChar*>& lstTmpNameSpaceStack)
{    
    int intStatus= AXIS_FAIL;

    if (isSerializable())
    {        
        pSZ.serialize(" ", NULL);

        /*
         * Following code figures out the prefix to be serialized and 
         * serialize it.
         */
        if(!m_prefix.empty())
        {            
            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }
        else if (!m_uri.empty())
        {
            bool blnIsNewNamespace = false;
            m_prefix = pSZ.getNamespacePrefix(m_uri.c_str(), 
                blnIsNewNamespace);
            if (blnIsNewNamespace)
            {
                lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
            }

            pSZ.serialize(m_prefix.c_str(), ":", NULL);
        }

        pSZ.serialize(m_localname.c_str(), "=\"", m_value.c_str(), "\"", NULL);

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

int Attribute::initializeForTesting()
{
    m_prefix = "pr";
    m_localname = "age";
    m_uri = "http://myurl.com";
    m_value = "25";

    return AXIS_SUCCESS;
}


Attribute::Attribute(const AxisChar *localname, const AxisChar *prefix, 
                     const AxisChar *value)
{
    m_localname= localname;
    m_prefix= prefix;
    m_value= value;
}