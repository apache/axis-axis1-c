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

/*
 * This is the client Stub base class
 * Stub.cpp: implemtation for the Stub.
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

/*
 * Revision 1.2  2004/05/31 roshan
 * Added calling conventions
 */

/*
 * Revision 1.3  2004/06/01 roshan
 * Added setSOAPMethodAttribute
 */

#include <axis/client/Stub.h>
#include <stdio.h>
#include "../../transport/SOAPTransport.h"
#include <axis/server/AxisWrapperAPI.h>
#include "../../soap/SoapSerializer.h"

StubFunctions Stub::ms_VFtable;
bool Stub::bInitialized = false;

Stub::Stub(const char *pcEndPointUri, AXIS_PROTOCOL_TYPE eProtocol) : m_lTimeoutSeconds(0)
{
    m_pCall = new Call();
    m_pCall->setProtocol(eProtocol);
    m_pCall->setEndpointURI(pcEndPointUri);
}

Stub::~Stub()
{
    delete m_pCall;
    for (unsigned int i = 0; i < m_vKeys.size(); i++)
    {
	    free(m_vKeys[i]);
	    free(m_vValues[i]);
    }

    for (unsigned int j = 0; j < m_vSOAPHeaderBlocks.size(); j++)
    {
	    delete m_vSOAPHeaderBlocks[j];
    }
}

void Stub::setEndPoint(const char *pcEndPoint)
{
    m_pCall->setEndpointURI(pcEndPoint);
}

void Stub::setTransportProperty(const char *pcKey, const char *pcValue)
{
    if (pcKey && pcValue)
    {
	    m_vKeys.push_back(strdup(pcKey));
	    m_vValues.push_back(strdup(pcValue));
    }
}

void Stub::setTransportProperties()
{
    SOAPTransport *pTrasport = NULL;
    if (m_pCall)
	    pTrasport = m_pCall->getTransport();
    if (pTrasport)
    {
	    for (unsigned int i = 0; i < m_vKeys.size(); i++)
	    {
	        pTrasport->setTransportProperty(m_vKeys[i], m_vValues[i]);
	    }
    }
}

char* Stub::getFirstTrasportPropertyKey()
{
    m_viCurrentKey = m_vKeys.begin();
    m_viCurrentValue = m_vValues.begin();

    if (m_viCurrentKey == m_vKeys.end())
        return NULL;
    else
        return (*m_viCurrentKey);
}

char* Stub::getNextTrasportPropertyKey()
{
    //already at the end?
    if (m_viCurrentKey == m_vKeys.end())
        return NULL;

    m_viCurrentKey++;
    m_viCurrentValue++;

    if (m_viCurrentKey == m_vKeys.end())
        return NULL;
    else
        return (*m_viCurrentKey);
}

char* Stub::getCurrentTrasportPropertyKey()
{
    if (m_viCurrentKey == m_vKeys.end())
        return NULL;
    else
        return (*m_viCurrentKey);
}

char* Stub::getCurrentTrasportPropertyValue()
{
    if (m_viCurrentValue == m_vValues.end())
        return NULL;
    else
        return (*m_viCurrentValue);
}

void Stub::deleteCurrentTrasportProperty()
{
    if (m_viCurrentKey != m_vKeys.end())
    {
        free(*m_viCurrentKey);
        free(*m_viCurrentValue);
        m_vKeys.erase(m_viCurrentKey);
        m_vValues.erase(m_viCurrentValue);
    }
}

void Stub::deleteTrasportProperty(char* pcKey, unsigned int uiOccurance)
{
    vector <char*>::iterator currentKey = m_vKeys.begin();
    vector <char*>::iterator currentValue = m_vValues.begin();
    unsigned int uiCount = 1;

    while(currentKey != m_vKeys.end() && uiCount <= uiOccurance)
    {
        if(strcmp(pcKey, *currentKey) == 0)
        {
             if(uiCount == uiOccurance)
             {
                 m_vKeys.erase(currentKey);
                 m_vValues.erase(currentValue);
             }
             uiCount++;
        }
        currentKey++;
        currentValue++;
    }
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
	    IHeaderBlock *pNewSoapheader = m_pCall->createHeaderBlock(pachLocalName, pachUri);
	    m_vSOAPHeaderBlocks.push_back(pNewSoapheader);
	    return pNewSoapheader;
    }
    else
	    return NULL;
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
//        if(currentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end())
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
    setTransportProperties();
    setSOAPMethodAttributes();
    setTransportTimeout();
}

void Stub::setProxy(const char* pcProxyHost, unsigned int uiProxyPort)
{
    m_pCall->setProxy(pcProxyHost, uiProxyPort);
}

void Stub::setSOAPMethodAttribute(const AxisChar *pLocalname, const AxisChar *pPrefix, const AxisChar *pValue)
{
	Attribute* pAttribute = new Attribute(pLocalname, pPrefix, pValue);
	m_vSOAPMethodAttributes.push_back(pAttribute);
}

Attribute* Stub::getFirstSOAPMethodAttribute()
{
    m_viCurrentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
    if (m_viCurrentSOAPMethodAttribute == m_vSOAPMethodAttributes.end())
        return NULL;
    else
        return (*m_viCurrentSOAPMethodAttribute);
}

Attribute* Stub::getNextSOAPMethodAttribute()
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

Attribute* Stub::getCurrentSOAPMethodAttribute()
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
		pSerializer->setSOAPMethodAttribute(m_vSOAPMethodAttributes[i]->clone());
	}
    }	
}

void Stub::deleteCurrentSOAPMethodAttribute()
{
    if (m_viCurrentSOAPMethodAttribute != m_vSOAPMethodAttributes.end())
    {
        delete(*m_viCurrentSOAPMethodAttribute);
        m_vSOAPMethodAttributes.erase(m_viCurrentSOAPMethodAttribute);

    }
}

void Stub::deleteSOAPMethodAttribute(Attribute* pAttribute)
{
    vector <Attribute*>::iterator currentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin();
    bool bDone = false;
    while( !bDone && currentSOAPMethodAttribute != m_vSOAPMethodAttributes.end())
    {
        if(pAttribute == *currentSOAPMethodAttribute)
        {
            delete (*currentSOAPMethodAttribute);
            m_vSOAPMethodAttributes.erase(currentSOAPMethodAttribute);
            bDone = true;
        }
        currentSOAPMethodAttribute++;
    }
}


void Stub::setSOAPMethodAttribute(const AxisChar *pLocalname, const AxisChar *pPrefix, const AxisChar *pUri, const AxisChar *pValue)
{
    Attribute* pAttribute = new Attribute(pLocalname, pPrefix, pUri, pValue);
	m_vSOAPMethodAttributes.push_back(pAttribute);
}

void Stub::setTransportTimeout(const long lSeconds)
{
    m_lTimeoutSeconds = lSeconds;
}

void Stub::setTransportTimeout()
{
    if(m_lTimeoutSeconds)
    {
        SOAPTransport *pTrasport = NULL;
        if (m_pCall)
            pTrasport = m_pCall->getTransport();
        if (pTrasport)
        {
            pTrasport->setTimeout(m_lTimeoutSeconds);
        }
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

/* global function to be used in C stubs */
extern "C" void* getStubObject (AXIS_PROTOCOL_TYPE nProtocol, 
    AxisChar* pchEndpointURI)
{
    Call_C* pCall = (Call_C*) malloc (sizeof (Call_C));
    pCall->_object = new Call ();
    pCall->_functions = &Call::ms_VFtable;
    ((Call*) pCall->_object)->setProtocol (nProtocol);
    ((Call*) pCall->_object)->setEndpointURI (pchEndpointURI);
    return pCall;
}

extern "C" void destroyStubObject (void* pCall)
{
    Call* pObject = (Call*) ((Call_C*)pCall)->_object;
    delete pObject;
    free (pCall);
}

HeaderBlock_C Stub::s_createSOAPHeaderBlock(void* pObj, 
    AxisChar * pachLocalName, AxisChar * pachUri)
{
	HeaderBlock_C blk;
	blk._functions = &(IHeaderBlock::ms_VFtable);
	blk._object = ((Stub*)pObj)->createSOAPHeaderBlock(pachLocalName, pachUri);
	return blk;
}

HeaderBlock_C Stub::s_getFirstSOAPHeaderBlock(void* pObj)
{
	HeaderBlock_C blk;
	blk._functions = &(IHeaderBlock::ms_VFtable);
	blk._object = ((Stub*)pObj)->getFirstSOAPHeaderBlock();
	return blk;
}

HeaderBlock_C Stub::s_getNextSOAPHeaderBlock(void* pObj)
{
	HeaderBlock_C blk;
	blk._functions = &(IHeaderBlock::ms_VFtable);
	blk._object = ((Stub*)pObj)->getNextSOAPHeaderBlock();
	return blk;
}

HeaderBlock_C Stub::s_getCurrentSOAPHeaderBlock(void* pObj)
{
	HeaderBlock_C blk;
	blk._functions = &(IHeaderBlock::ms_VFtable);
	blk._object = ((Stub*)pObj)->getCurrentSOAPHeaderBlock();
	return blk;
}

Attribute_C Stub::s_getFirstSOAPMethodAttribute(void* pObj)
{
	Attribute_C attr;
	attr._functions = &(Attribute::ms_VFtable);
	attr._object = ((Stub*)pObj)->getFirstSOAPMethodAttribute();
	return attr;
}

Attribute_C Stub::s_getNextSOAPMethodAttribute(void* pObj)
{
	Attribute_C attr;
	attr._functions = &(Attribute::ms_VFtable);
	attr._object = ((Stub*)pObj)->getNextSOAPMethodAttribute();
	return attr;
}

Attribute_C Stub::s_getCurrentSOAPMethodAttribute(void* pObj)
{
	Attribute_C attr;
	attr._functions = &(Attribute::ms_VFtable);
	attr._object = ((Stub*)pObj)->getCurrentSOAPMethodAttribute();
	return attr;
}

void Stub::s_Initialize()
{	
	if (bInitialized) return;
	bInitialized = true;
	ms_VFtable.setEndpoint = s_setEndpoint;
	ms_VFtable.setTransportProperty = s_setTransportProperty;
	ms_VFtable.getFirstTrasportPropertyKey = s_getFirstTrasportPropertyKey;
	ms_VFtable.getNextTrasportPropertyKey = s_getNextTrasportPropertyKey;
	ms_VFtable.getCurrentTrasportPropertyKey = s_getCurrentTrasportPropertyKey;
	ms_VFtable.getCurrentTrasportPropertyValue = s_getCurrentTrasportPropertyValue;
	ms_VFtable.deleteCurrentTrasportProperty = s_deleteCurrentTrasportProperty;
	ms_VFtable.deleteTrasportProperty = s_deleteTrasportProperty;
	ms_VFtable.setHandlerProperty = s_setHandlerProperty;
	ms_VFtable.createSOAPHeaderBlock = s_createSOAPHeaderBlock;
	ms_VFtable.getFirstSOAPHeaderBlock = s_getFirstSOAPHeaderBlock;
	ms_VFtable.getNextSOAPHeaderBlock = s_getNextSOAPHeaderBlock;
	ms_VFtable.getCurrentSOAPHeaderBlock = s_getCurrentSOAPHeaderBlock;
	ms_VFtable.deleteCurrentSOAPHeaderBlock = s_deleteCurrentSOAPHeaderBlock;
	ms_VFtable.deleteSOAPHeaderBlock = s_deleteSOAPHeaderBlock;
	ms_VFtable.setProxy = s_setProxy;
	ms_VFtable.setSOAPMethodAttribute = s_setSOAPMethodAttribute;
	ms_VFtable.getFirstSOAPMethodAttribute = s_getFirstSOAPMethodAttribute;
	ms_VFtable.getNextSOAPMethodAttribute = s_getNextSOAPMethodAttribute;
	ms_VFtable.getCurrentSOAPMethodAttribute = s_getCurrentSOAPMethodAttribute;
	ms_VFtable.deleteCurrentSOAPMethodAttribute = s_deleteCurrentSOAPMethodAttribute;
	ms_VFtable.deleteSOAPMethodAttribute = s_deleteSOAPMethodAttribute;
	ms_VFtable.setTransportTimeout = s_setTransportTimeout;
	ms_VFtable.getStatus = s_getStatus;
	ms_VFtable.getNamespacePrefix = s_getNamespacePrefix;
}

