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
 *
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */

#include <axis/client/Stub.hpp>
#include <stdio.h>
#include "../../transport/SOAPTransport.h"
#include <axis/AxisWrapperAPI.hpp>
#include "../../soap/SoapSerializer.h"
#include "../../soap/Attribute.h"
#include "../../common/AxisUtils.h"

AXIS_CPP_NAMESPACE_USE

Stub::Stub(const char *pcEndPointUri, AXIS_PROTOCOL_TYPE eProtocol) 
{
    m_pCall = new Call();
    m_pCall->setProtocol(eProtocol);
    m_pCall->setEndpointURI(pcEndPointUri);
    m_pTransport = m_pCall->getTransport();

	// Initialise m_viCurrentSOAPMethodAttribute to something sensible 
	// in case getFirstSOAPMethodAttribute isn't called first.
    m_viCurrentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
}

Stub::~Stub()
{
    delete m_pCall;
	unsigned int j=0;
    for (j = 0; j < m_vSOAPHeaderBlocks.size(); j++)
    {
	    delete m_vSOAPHeaderBlocks[j];
    }

    for (j = 0; j < m_vSOAPMethodAttributes.size(); j++)
    {
	    delete m_vSOAPMethodAttributes[j];
    }
}

void Stub::setEndPoint(const char *pcEndPoint)
{
    m_pCall->setEndpointURI(pcEndPoint);
}

void Stub::setTransportProperty(const char *pcKey, const char *pcValue)
{
    if (m_pTransport)
        m_pTransport->setTransportProperty(pcKey, pcValue);
}


const char* Stub::getFirstTransportPropertyKey()
{
    if (m_pTransport)
        return m_pTransport->getFirstTransportPropertyKey();
    else
        return NULL;
}

const char* Stub::getNextTransportPropertyKey()
{
    if (m_pTransport)
        return m_pTransport->getNextTransportPropertyKey();
    else
        return NULL;
}

const char* Stub::getCurrentTransportPropertyKey()
{
    if (m_pTransport)
        return m_pTransport->getCurrentTransportPropertyKey();
    else
        return NULL;
}

const char* Stub::getCurrentTransportPropertyValue()
{
    if (m_pTransport)
        return m_pTransport->getCurrentTransportPropertyValue();
    else
        return NULL;
}

void Stub::deleteCurrentTransportProperty()
{
    if (m_pTransport)
        m_pTransport->deleteCurrentTransportProperty();
}

void Stub::deleteTransportProperty(char* pcKey, unsigned int uiOccurance)
{
    if (m_pTransport)
        m_pTransport->deleteTransportProperty(pcKey, uiOccurance);
}

void Stub::setHandlerProperty(AxisChar* name, void* value, int len)
{
	m_pCall->setHandlerProperty(name, value, len);
}

IHeaderBlock* Stub::createSOAPHeaderBlock(AxisChar * pachLocalName,
                                           AxisChar * pachUri)
{
   if (pachLocalName && pachUri)
   {       
       if ((AxisUtils::isStringOnlyWithSpaces(pachLocalName)) || 
           (AxisUtils::isStringOnlyWithSpaces(pachUri)) )
        {
            return NULL;
        }
        else 
        {
	        IHeaderBlock *pNewSoapheader = m_pCall->createHeaderBlock(pachLocalName, pachUri);
	        m_vSOAPHeaderBlocks.push_back(pNewSoapheader);
	        return pNewSoapheader;
        }
    }
   else {
	   return NULL;
   }
}

IHeaderBlock* Stub::getFirstSOAPHeaderBlock()
{
    m_viCurrentSOAPHeaderBlock = m_vSOAPHeaderBlocks.begin();
    if ( m_viCurrentSOAPHeaderBlock == m_vSOAPHeaderBlocks.end())
        return NULL;
    else
        return (*m_viCurrentSOAPHeaderBlock);
    
}

IHeaderBlock* Stub::getNextSOAPHeaderBlock()
{
    //already at the end?
    if ( m_viCurrentSOAPHeaderBlock == m_vSOAPHeaderBlocks.end())
        return NULL;

    m_viCurrentSOAPHeaderBlock++;
    if ( m_viCurrentSOAPHeaderBlock == m_vSOAPHeaderBlocks.end())
        return NULL;
    else
        return (*m_viCurrentSOAPHeaderBlock);
    
}

IHeaderBlock* Stub::getCurrentSOAPHeaderBlock()
{
    if(m_viCurrentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end())
    {
        return (*m_viCurrentSOAPHeaderBlock);
    }
	return NULL;
}

void Stub::deleteCurrentSOAPHeaderBlock()
{
    if(m_viCurrentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end())
    {
        delete(*m_viCurrentSOAPHeaderBlock);
        m_vSOAPHeaderBlocks.erase(m_viCurrentSOAPHeaderBlock);
    }
}

void Stub::deleteSOAPHeaderBlock(IHeaderBlock* pHeaderBlock)
{
    vector <IHeaderBlock *>::iterator currentSOAPHeaderBlock = m_vSOAPHeaderBlocks.begin();
    bool bDone = false;
    while( !bDone && currentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end())
    {
        if(pHeaderBlock == *currentSOAPHeaderBlock)
        {
            delete(*currentSOAPHeaderBlock);
            m_vSOAPHeaderBlocks.erase(currentSOAPHeaderBlock);
            bDone = true;
        }
            currentSOAPHeaderBlock++;
    }
}

void Stub::setSOAPHeaders()
{
    SoapSerializer *pSerializer = NULL;
    if (m_pCall)
	pSerializer = m_pCall->getSOAPSerializer();
    if (pSerializer)
    {
		for (unsigned int i = 0; i < m_vSOAPHeaderBlocks.size(); i++)
		{
			pSerializer->addHeaderBlock(m_vSOAPHeaderBlocks[i]);
		}
    }
}

void Stub::applyUserPreferences()
{
    setSOAPHeaders();
    setSOAPMethodAttributes();
}

void Stub::setProxy(const char* pcProxyHost, unsigned int uiProxyPort)
{
    m_pCall->setProxy(pcProxyHost, uiProxyPort);
}

void Stub::setSOAPMethodAttribute(const AxisChar *pLocalname, const AxisChar *pPrefix, const AxisChar *pValue)
{
	setSOAPMethodAttribute(pLocalname,pPrefix,NULL,pValue);
}

void Stub::setSOAPMethodAttribute(const AxisChar *pLocalname, const AxisChar *pPrefix, 
                                  const AxisChar *pUri, const AxisChar *pValue)
{
    //Check if there is an attribute with the same local name is already set
    IAttribute* pAttribute = this->getFirstSOAPMethodAttribute();
    while( pAttribute )
    {
        if( strcmp(pAttribute->getLocalName(), pLocalname) == 0 )
        {
            //found an attibute alredy set with same name
            if(strcmp(pAttribute->getPrefix(), pPrefix) == 0 ) 
            {
                this->deleteCurrentSOAPMethodAttribute();
                break;
            }
        }
        pAttribute = this->getNextSOAPMethodAttribute();
    }

	if (NULL!=pUri)
		pAttribute = new Attribute(pLocalname, pPrefix, pUri, pValue);
	else
		pAttribute = new Attribute(pLocalname, pPrefix, pValue);
	m_vSOAPMethodAttributes.push_back(pAttribute);
    m_viCurrentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
}

IAttribute* Stub::getFirstSOAPMethodAttribute()
{
    m_viCurrentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
    if (m_viCurrentSOAPMethodAttribute == m_vSOAPMethodAttributes.end())
        return NULL;
    else
        return (*m_viCurrentSOAPMethodAttribute);
}

IAttribute* Stub::getNextSOAPMethodAttribute()
{
    //already at the end?
    if (m_viCurrentSOAPMethodAttribute == m_vSOAPMethodAttributes.end())
        return NULL;

    m_viCurrentSOAPMethodAttribute++;
    
    if (m_viCurrentSOAPMethodAttribute == m_vSOAPMethodAttributes.end())
        return NULL;
    else
        return (*m_viCurrentSOAPMethodAttribute);
}

IAttribute* Stub::getCurrentSOAPMethodAttribute()
{
    if (m_viCurrentSOAPMethodAttribute == m_vSOAPMethodAttributes.end())
        return NULL;
    else
        return (*m_viCurrentSOAPMethodAttribute);
}


void Stub::setSOAPMethodAttributes()
{
    SoapSerializer *pSerializer = NULL;
    if (m_pCall)
	pSerializer = m_pCall->getSOAPSerializer();
    if (pSerializer)
    {
       for (unsigned int i = 0; i < m_vSOAPMethodAttributes.size(); i++)
	   {
           pSerializer->setSOAPMethodAttribute(((Attribute*)m_vSOAPMethodAttributes[i])->clone());
	   }
    }	
}

void Stub::deleteCurrentSOAPMethodAttribute()
{
    if (m_viCurrentSOAPMethodAttribute != m_vSOAPMethodAttributes.end())
    {
        delete(*m_viCurrentSOAPMethodAttribute);
        m_vSOAPMethodAttributes.erase(m_viCurrentSOAPMethodAttribute);
        m_viCurrentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
    }
}

void Stub::deleteSOAPMethodAttribute(IAttribute* pAttribute)
{
    vector <IAttribute*>::iterator currentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
    bool bDone = false;
    while( !bDone && currentSOAPMethodAttribute != m_vSOAPMethodAttributes.end())
    {
        if(pAttribute == *currentSOAPMethodAttribute)
        {
            delete (*currentSOAPMethodAttribute);
            m_vSOAPMethodAttributes.erase(currentSOAPMethodAttribute);
            m_viCurrentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
            bDone = true;
        }
        currentSOAPMethodAttribute++;
    }
}

void Stub::setTransportTimeout(const long lSeconds)
{
    if (m_pTransport)
    {
        m_pTransport->setTimeout(lSeconds);
    }
}

int Stub::getStatus()
{
    if ( m_pCall==NULL )
        return AXIS_SUCCESS;
    else
        return m_pCall->getStatus();
}

const AxisChar* Stub::getNamespacePrefix(const AxisChar* pNamespace)
{
    return m_pCall->getNamespacePrefix(pNamespace);
}


void Stub::setMaintainSession(bool bSession)
{
    if (m_pTransport)
    {
        m_pTransport->setMaintainSession(bSession);
    }
}


void Stub::setTransportProtocol(AXIS_PROTOCOL_TYPE eProtocol)
{
    if (m_pCall)
        m_pCall->setProtocol(eProtocol);
}

AXIS_PROTOCOL_TYPE Stub::getTransportProtocol()
{
    if (m_pCall)
        return m_pCall->getProtocol();
    else
       return APT_UNKNOWN;
}

IHeaderBlock* Stub::createSOAPHeaderBlock(AxisChar *pachLocalName, AxisChar *pachUri, AxisChar *pachPrefix)
{
    if (pachLocalName && pachUri && pachPrefix)
    {
        if (AxisUtils::isStringOnlyWithSpaces(pachLocalName) || 
                AxisUtils::isStringOnlyWithSpaces(pachUri) )
        {
            return NULL;
        }
        else 
        {
	        IHeaderBlock *pNewSoapheader = m_pCall->createHeaderBlock(pachLocalName, pachUri, pachPrefix);
	        m_vSOAPHeaderBlocks.push_back(pNewSoapheader);
	        return pNewSoapheader;
        }
    }
    else {
	    return NULL;
    }
}
