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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "SoapEnvelope.h"
#include <axis/GDefine.hpp>
#include "SoapSerializer.h"
#include <stdio.h>
#include "../common/AxisTrace.h"
#include "Attribute.h"

AXIS_CPP_NAMESPACE_START

extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

SoapEnvelope::SoapEnvelope()
{
    m_pSoapHeader= NULL;
    m_pSoapBody= NULL;
}

SoapEnvelope::~SoapEnvelope()
{
    /* deletion of attributes */
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while (itCurrAttribute != m_attributes.end())
    {        
        delete *itCurrAttribute;
        itCurrAttribute++;
    }

    m_attributes.clear();

    /* deletion of namespace declerations */
    list<Attribute*>::iterator itCurrNamespaceDecls= m_namespaceDecls.begin();

    while (itCurrNamespaceDecls != m_namespaceDecls.end())
    {        
        delete *itCurrNamespaceDecls;
        itCurrNamespaceDecls++;
    }

    m_namespaceDecls.clear();

    /* deletion of soap header */
    if (m_pSoapHeader)
    {
        delete m_pSoapHeader;
    }

    /* deletion of soap body */
    if (m_pSoapBody)
    {
        delete m_pSoapBody;
    }
}

void SoapEnvelope::setSoapHeader(SoapHeader* soapHeader)
{
    m_pSoapHeader= soapHeader;
}

void SoapEnvelope::setSoapBody(SoapBody* soapBody)
{
    m_pSoapBody= soapBody;
}

int SoapEnvelope::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{    
    int iStatus= AXIS_SUCCESS;
    do
    {            
        pSZ.serialize("\n<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE],
            NULL);    
        serializeStandardNamespaceDecl(pSZ);
        serializeNamespaceDecl(pSZ);
        serializeAttributes(pSZ);
        pSZ.serialize(">\n", NULL);
        if (m_pSoapHeader!=NULL)
        {
            iStatus= m_pSoapHeader->serialize(pSZ, eSoapVersion);
            if (iStatus == AXIS_FAIL)
            {
                break;
            }
        }
        if (m_pSoapBody!=NULL)
        {
            iStatus= m_pSoapBody->serialize(pSZ, eSoapVersion);
            if (iStatus == AXIS_FAIL)
            {
                break;
            }
        }
        else
        {
            /* throw exception
             * iStatus = AXIS_FAIL;
             */
        }
                
        pSZ.serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix,
            ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE],
            ">\n\n", NULL);
    } while (0);

    return iStatus;
}

/*
commented on 10Jul2003
int SoapEnvelope::serialize(string &sSerialized, SOAP_VERSION eSoapVersion)
{    
    
    int iStatus= AXIS_SUCCESS;

    do
    {
        sSerialized= "<"+ string(gs_SoapEnvVersionsStruct
        [eSoapVersion].pchPrefix) + ":"+ gs_SoapEnvVersionsStruct
        [eSoapVersion].pchWords[SKW_ENVELOPE];

        serializeNamespaceDecl(sSerialized);
        serializeAttributes(sSerialized);

        sSerialized= sSerialized + ">"+ "\n";

        if (m_pSoapHeader!=NULL)
        {
            iStatus= m_pSoapHeader->serialize(sSerialized, eSoapVersion);
            if(iStatus == AXIS_FAIL)
            {
                break;
            }
        }

        if (m_pSoapBody!=NULL)
        {
            iStatus= m_pSoapBody->serialize(sSerialized, eSoapVersion);
            if(iStatus == AXIS_FAIL)
            {
                break;
            }
        }
        else
        {
            //throw exception
            //iStatus = AXIS_FAIL;
        }
        
        sSerialized+= "</"+ string(gs_SoapEnvVersionsStruct
        [eSoapVersion].pchPrefix) + ":"+ gs_SoapEnvVersionsStruct
        [eSoapVersion].pchWords[SKW_ENVELOPE]+ ">";    
    } while (0);

    return iStatus;
}*/

/*
 * The added attrubute will be deleted by the destructor of this 
 * SoapEnvelope.
 */
int SoapEnvelope::addAttribute(Attribute *pAttribute)
{
    m_attributes.push_back(pAttribute);

    return AXIS_SUCCESS;
}

/*
 * The added NamespaceDecl will be deleted by the destructor of this 
 * SoapEnvelope.
 */
int SoapEnvelope::addNamespaceDecl(Attribute *pAttribute)
{
    m_namespaceDecls.push_back(pAttribute);

    return AXIS_SUCCESS;
}

int SoapEnvelope::serializeAttributes(SoapSerializer& pSZ)
{    
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while (itCurrAttribute != m_attributes.end())
    {
        (*itCurrAttribute)->serialize(pSZ);
        itCurrAttribute++;        
    }    

    return AXIS_SUCCESS;    
}

/*
commented on 10Jul2003 3.30 pm
int SoapEnvelope::serializeAttributes(string& sSerialized)
{    
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while (itCurrAttribute != m_attributes.end())
    {        
        (*itCurrAttribute)->serialize(sSerialized);
        itCurrAttribute++;        
    }    

    return AXIS_SUCCESS;    
}
*/

int SoapEnvelope::serializeNamespaceDecl(SoapSerializer& pSZ)
{    

    list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

    while (itCurrNamespaceDecl != m_namespaceDecls.end())
    {            

        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    

    return AXIS_SUCCESS;
}

/*
commented on 10Jul2003 3.30 pm
int SoapEnvelope::serializeNamespaceDecl(string& sSerialized)
{    

    list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

    while (itCurrNamespaceDecl != m_namespaceDecls.end())
    {            
        (*itCurrNamespaceDecl)->serialize(sSerialized);
        itCurrNamespaceDecl++;        
    }    

    return AXIS_SUCCESS;
}
*/

/*
 * This method is needed in the situation where we create and fill a 
 * SoapEnvelope object when deserializing a incoming soap request.
 * But this method is not needed in serializing a soap request, because
 * the version specific prefix is taken from the SoapEnvVersions.h at 
 * that time.
 */
int SoapEnvelope::setPrefix(const AxisChar* prefix)
{
    m_sPrefix= prefix;

    return AXIS_SUCCESS;
}

int SoapEnvelope::addStandardNamespaceDecl(const Attribute *pAttribute)
{
    m_StandardNamespaceDecls.push_back(pAttribute);
    return AXIS_SUCCESS;
}

int SoapEnvelope::serializeStandardNamespaceDecl(SoapSerializer &pSZ)
{
    list<const Attribute*>::iterator itCurrNamespaceDecl= 
        m_StandardNamespaceDecls.begin();
    while (itCurrNamespaceDecl != m_StandardNamespaceDecls.end()) 
    {            
        (*itCurrNamespaceDecl)->serialize(pSZ);
        itCurrNamespaceDecl++;        
    }    
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END

#ifdef UNIT_TESTING_ON
int SoapEnvelope::initializeForTesting(SOAP_VERSION eSoapVersion)
{
    if (eSoapVersion == SOAP_VER_1_2)
    {
        setPrefix("env");

        Attribute* pAttribute = new Attribute();
        pAttribute->setPrefix("xmlns");
        pAttribute->setLocalName("env");
        pAttribute->setUri("http://www.w3.org/2003/05/soap-envelope");
        addNamespaceDecl(pAttribute);

        SoapBody* pSoapBody = new SoapBody();
        pSoapBody->initializeForTesting();

        setSoapBody(pSoapBody);
    }

    return AXIS_SUCCESS;
}
#endif
