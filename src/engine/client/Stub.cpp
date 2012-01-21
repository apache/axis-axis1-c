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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include <stdio.h>

#include <axis/AxisWrapperAPI.hpp>
#include <axis/UnknownElementException.hpp>
#include <axis/client/Stub.hpp>
#include <axis/IAttribute.hpp>

#include "../../transport/SOAPTransport.h"
#include "../../soap/SoapSerializer.h"
#include "../../common/AxisUtils.h"
#include "../../common/AxisConfig.h"
#include "../../common/AxisGenException.h"
#include "../../soap/Attribute.h"

#include "../../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

AXIS_CPP_NAMESPACE_USE

Stub::Stub (const char *pcEndPointUri, AXIS_PROTOCOL_TYPE eProtocol):
m_proxyUsername (NULL),
m_proxyPassword (NULL), 
m_pExceptionHandler(NULL)
{
    m_pCall = new Call ();
    
    // Weird, yes, but need to do here since tracing is not enabled until after instantiation of Call class.
      logEntryEngine("Stub::Stub")

    m_pCall->setProtocol (eProtocol);
    m_pTransport = m_pCall->getTransport ();
    m_pTransport->setEndpointUri( pcEndPointUri);
    m_viCurrentSOAPHeaderBlock = m_vSOAPHeaderBlocks.end();
    
    // SSL channel related initilizations
    char * pcSSLChannelInfo = g_pConfig->getAxisConfProperty( AXCONF_SECUREINFO);
    if( pcSSLChannelInfo && strlen( pcSSLChannelInfo) > 0)
    {
        char * pszArgPtr = NULL;
        int iArgIndex = 0;

        pszArgPtr = strtok( pcSSLChannelInfo, ",");

        while( pszArgPtr != NULL && iArgIndex < 8)
        {
            m_sArguments[iArgIndex] = pszArgPtr;
            iArgIndex++;
            pszArgPtr = strtok( NULL, ",");
            while( pszArgPtr != NULL && *pszArgPtr == ' ' && *pszArgPtr != '\0')
                pszArgPtr++;
        }
    }
    
    logExit()
}

Stub::~Stub ()
{
      logEntryEngine("Stub::~Stub")

    delete m_pCall;
    m_pCall = NULL;

    unsigned int j = 0;
    for (j = 0; j < m_vSOAPHeaderBlocks.size (); j++)
    {
        delete m_vSOAPHeaderBlocks[j];
        m_vSOAPHeaderBlocks[j] = NULL;
    }
    
    logExit()
}

void
Stub::setEndPoint (const char *pcEndPoint)
{
      logEntryEngine("Stub::setEndPoint")

    if (m_pTransport)
        m_pTransport->setEndpointUri( pcEndPoint);
      
    logExit()
}

void
Stub::setTransportProperty (const char *pcKey, const char *pcValue)
{
      logEntryEngine("Stub::setTransportProperty")

    if (m_pTransport)
    {
        if(!pcKey)
        {
            m_pTransport=NULL; //this should be set to null. otherwise the previous setting can be still there.
        }
        else if (strcmp (pcKey, "SOAPAction") == 0)
        {
            // both "" missing
            if (pcValue
                    && (pcValue[0] != '"'
                    && pcValue[strlen (pcValue) - 1] != '"'))
            {
                char *tempvalue = new char[strlen (pcValue) + 3];
                sprintf (tempvalue, "\"%s\"", pcValue);
                m_pTransport->setTransportProperty (pcKey, tempvalue);
                delete[]tempvalue;
            }
            else if (pcValue && (pcValue[0] != '"'))    //starting '"' missing
            {
                char *tempvalue = new char[strlen (pcValue) + 2];
                sprintf (tempvalue, "\"%s", pcValue);
                m_pTransport->setTransportProperty (pcKey, tempvalue);
                delete[]tempvalue;
            }
            else if (pcValue && (pcValue[strlen (pcValue) - 1] != '"'))    // ending '"' missing
            {
                char *tempvalue = new char[strlen (pcValue) + 3];
                sprintf (tempvalue, "\"%s\"", pcValue);
                m_pTransport->setTransportProperty (pcKey, tempvalue);
                delete[]tempvalue;
            }
            else        // both "" present
                m_pTransport->setTransportProperty (pcKey, pcValue);
        }
        else
             m_pTransport->setTransportProperty (pcKey, pcValue);
    }
      
    logExit()
}

const char *
Stub::getTransportProperty (const char *key, bool response)
{
    return m_pCall->getTransportProperty (key, response);
}

const char *
Stub::getFirstTransportPropertyKey (bool response)
{
    if (m_pTransport)
        return m_pTransport->getFirstTransportPropertyKey (response);

    return NULL;
}

const char *
Stub::getNextTransportPropertyKey (bool response)
{
    if (m_pTransport)
        return m_pTransport->getNextTransportPropertyKey (response);

    return NULL;
}

const char *
Stub::getCurrentTransportPropertyKey (bool response)
{
    if (m_pTransport)
       return m_pTransport->getCurrentTransportPropertyKey (response);

    return NULL;
}

const char *
Stub::getCurrentTransportPropertyValue (bool response)
{
    if (m_pTransport)
        return m_pTransport->getCurrentTransportPropertyValue (response);

    return NULL;
}

void
Stub::deleteCurrentTransportProperty (bool response)
{
    if (m_pTransport)
        m_pTransport->deleteCurrentTransportProperty (response);
}

void
Stub::deleteTransportProperty (char *pcKey, unsigned int uiOccurance)
{
    if (m_pTransport)
        m_pTransport->deleteTransportProperty (pcKey, uiOccurance);
}

void
Stub::setHandlerProperty (AxisChar * name, void *value, int len)
{
      logEntryEngine("Stub::setHandlerProperty")

    m_pCall->setHandlerProperty (name, value, len);
      
    logExit()
}

IHeaderBlock *
Stub::createSOAPHeaderBlock (AxisChar * pachLocalName, AxisChar * pachUri)
{
    if (pachLocalName && pachUri)
    {
        if ((AxisUtils::isStringOnlyWithSpaces (pachLocalName))
                || (AxisUtils::isStringOnlyWithSpaces (pachUri)))
            return NULL;
        else
        {
            IHeaderBlock *pNewSoapheader = m_pCall->createHeaderBlock (pachLocalName, pachUri);
            m_vSOAPHeaderBlocks.push_back (pNewSoapheader);
            return pNewSoapheader;
        }
    }

    return NULL;
}

IHeaderBlock *
Stub::getFirstSOAPHeaderBlock ()
{
    m_viCurrentSOAPHeaderBlock = m_vSOAPHeaderBlocks.begin ();
    if (m_viCurrentSOAPHeaderBlock == m_vSOAPHeaderBlocks.end ())
        return NULL;
    else
        return (*m_viCurrentSOAPHeaderBlock);

}

IHeaderBlock *
Stub::getNextSOAPHeaderBlock ()
{
    //already at the end?
    if (m_viCurrentSOAPHeaderBlock == m_vSOAPHeaderBlocks.end ())
        return NULL;

    m_viCurrentSOAPHeaderBlock++;
    if (m_viCurrentSOAPHeaderBlock == m_vSOAPHeaderBlocks.end ())
        return NULL;
    else
        return (*m_viCurrentSOAPHeaderBlock);
}

IHeaderBlock *
Stub::getCurrentSOAPHeaderBlock ()
{
    if (m_viCurrentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end ())
        return (*m_viCurrentSOAPHeaderBlock);

    return NULL;
}

void
Stub::deleteCurrentSOAPHeaderBlock ()
{
      logEntryEngine("Stub::deleteCurrentSOAPHeaderBlock")

    if (m_viCurrentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end ())
    {
        delete (*m_viCurrentSOAPHeaderBlock);
        m_vSOAPHeaderBlocks.erase (m_viCurrentSOAPHeaderBlock);
    }
      
    logExit()
}

void
Stub::deleteSOAPHeaderBlock (IHeaderBlock * pHeaderBlock)
{
      logEntryEngine("Stub::deleteSOAPHeaderBlock")

    vector < IHeaderBlock * >::iterator currentSOAPHeaderBlock =
    m_vSOAPHeaderBlocks.begin ();
    bool bDone = false;
    while (!bDone && currentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end ())
    {
        if (pHeaderBlock == *currentSOAPHeaderBlock)
        {
            delete (*currentSOAPHeaderBlock);
            m_vSOAPHeaderBlocks.erase (currentSOAPHeaderBlock);
            bDone = true;
        }
        currentSOAPHeaderBlock++;
    }
      
    logExit()
}

void
Stub::setSOAPHeaders ()
{
      logEntryEngine("Stub::setSOAPHeaders")

    SoapSerializer *pSerializer = NULL;
    if (m_pCall)
        pSerializer = m_pCall->getSOAPSerializer ();
        
    if (pSerializer)
        for (unsigned int i = 0; i < m_vSOAPHeaderBlocks.size (); i++)
            pSerializer->addHeaderBlock (m_vSOAPHeaderBlocks[i]);
      
    logExit()
}

void
Stub::addNamespaceToSOAPHeader(const AxisChar * pUri, const AxisChar * pPrefix)
{
    std::list<Attribute*> attributeList;
    Attribute * pAttribute = new Attribute( attributeList, "", pPrefix, pUri, "");

    m_vSOAPHeaderNamespaces.push_back ((IAttribute *)pAttribute);
}


void
Stub::clearSOAPHeaderNamespaces()
{
    unsigned int j = 0;
    for (j = 0; j < m_vSOAPHeaderNamespaces.size (); j++)
    {
        delete m_vSOAPHeaderNamespaces[j];
        m_vSOAPHeaderNamespaces[j] = NULL;
    }
    m_vSOAPHeaderNamespaces.clear();
}


void
Stub::addAttributeToSOAPHeader(const AxisChar * pLocalname,
                              const AxisChar * pPrefix,
                              const AxisChar * pValue)
{
    std::list<Attribute*> attributeList;
    Attribute * pAttribute = new Attribute( attributeList, pLocalname, pPrefix, pValue);

    m_vSOAPHeaderAttributes.push_back ((IAttribute *)pAttribute);
}


void
Stub::clearSOAPHeaderAttributes()
{
    unsigned int j = 0;
    for (j = 0; j < m_vSOAPHeaderAttributes.size (); j++)
    {
        delete m_vSOAPHeaderAttributes[j];
        m_vSOAPHeaderAttributes[j] = NULL;
    }
    m_vSOAPHeaderAttributes.clear();
}


void
Stub::addNamespaceToSOAPBody(const AxisChar * pUri, const AxisChar * pPrefix)
{
    std::list<Attribute*> attributeList;
    Attribute * pAttribute = new Attribute( attributeList, "", pPrefix, pUri, "");

    m_vSOAPBodyNamespaces.push_back ((IAttribute *)pAttribute);
}


void
Stub::clearSOAPBodyNamespaces()
{
    unsigned int j = 0;
    for (j = 0; j < m_vSOAPBodyNamespaces.size (); j++)
    {
        delete m_vSOAPBodyNamespaces[j];
        m_vSOAPBodyNamespaces[j] = NULL;
    }
    m_vSOAPBodyNamespaces.clear();
}


void
Stub::addAttributeToSOAPBody(const AxisChar * pLocalname,
                            const AxisChar * pPrefix,
                            const AxisChar * pValue)
{
    std::list<Attribute*> attributeList;
    Attribute * pAttribute = new Attribute( attributeList, pLocalname, pPrefix, pValue);

    m_vSOAPBodyAttributes.push_back ((IAttribute *)pAttribute);
}


void
Stub::clearSOAPBodyAttributes()
{
    unsigned int j = 0;
    for (j = 0; j < m_vSOAPBodyAttributes.size (); j++)
    {
        delete m_vSOAPBodyAttributes[j];
        m_vSOAPBodyAttributes[j] = NULL;
    }
    m_vSOAPBodyAttributes.clear();
}


void
Stub::applyUserPreferences ()
{
      logEntryEngine("Stub::applyUserPreferences")

    setSOAPHeaders ();
      
    // Set SOAP body and SOAP header attributes
    SoapSerializer *pSerializer = NULL;
    if (m_pCall)
        pSerializer = m_pCall->getSOAPSerializer ();

    if (pSerializer)
    {
        unsigned int i;

        // add user-specified namespaces to SOAP header
        for (i = 0; i < m_vSOAPHeaderNamespaces.size (); i++)
            pSerializer->addNamespaceToSOAPHeader(m_vSOAPHeaderNamespaces[i]->getURI(),
                                                  m_vSOAPHeaderNamespaces[i]->getPrefix());

        // Add user-specified attributes to SOAP header
        for (i = 0; i < m_vSOAPHeaderAttributes.size (); i++)
            pSerializer->addAttributeToSOAPHeader(m_vSOAPHeaderAttributes[i]->getLocalName(),
                                                  m_vSOAPHeaderAttributes[i]->getPrefix(),
                                                  m_vSOAPHeaderAttributes[i]->getValue());

        // add user-specified namespaces to SOAP body
        for (i = 0; i < m_vSOAPBodyNamespaces.size (); i++)
            pSerializer->addNamespaceToSOAPBody(m_vSOAPBodyNamespaces[i]->getURI(),
                                                m_vSOAPBodyNamespaces[i]->getPrefix());

        // Add user-specified attributes to SOAP body
        for (i = 0; i < m_vSOAPBodyAttributes.size (); i++)
            pSerializer->addAttributeToSOAPBody(m_vSOAPBodyAttributes[i]->getLocalName(),
                                                m_vSOAPBodyAttributes[i]->getPrefix(),
                                                m_vSOAPBodyAttributes[i]->getValue());
    }

    logExit()
}

void
Stub::setProxy (const char *pcProxyHost, unsigned int uiProxyPort)
{
      logEntryEngine("Stub::setProxy")

    if (m_pTransport)
        m_pTransport->setProxy (pcProxyHost, uiProxyPort);
      
    logExit()
}

void
Stub::setTransportTimeout (long lSeconds)
{
      logEntryEngine("Stub::setTransportTimeout")

    if (m_pTransport)
        m_pTransport->setTimeout (lSeconds);
      
    logExit()
}

int
Stub::getStatus ()
{
    if (m_pCall == NULL)
        return AXIS_SUCCESS;
    else
        return m_pCall->getStatus ();
}

void
Stub::setMaintainSession (bool bSession)
{
    if (m_pTransport)
        m_pTransport->setMaintainSession (bSession);
}


void
Stub::setTransportProtocol (AXIS_PROTOCOL_TYPE eProtocol)
{
    if (m_pCall)
        m_pCall->setProtocol (eProtocol);
}

AXIS_PROTOCOL_TYPE
Stub::getTransportProtocol ()
{
    if (m_pCall)
        return m_pCall->getProtocol ();

    return APT_UNKNOWN;
}

IHeaderBlock *
Stub::createSOAPHeaderBlock (AxisChar * pachLocalName, AxisChar * pachUri,
                 AxisChar * pachPrefix)
{
    if (pachLocalName && pachUri && pachPrefix)
    {
        if (AxisUtils::isStringOnlyWithSpaces (pachLocalName) 
                || AxisUtils::isStringOnlyWithSpaces (pachUri))
            return NULL;
        else
        {
            IHeaderBlock *pNewSoapheader =
            m_pCall->createHeaderBlock (pachLocalName, pachUri, pachPrefix);
            m_vSOAPHeaderBlocks.push_back (pNewSoapheader);
            return pNewSoapheader;
        }
    }

    return NULL;
}

void
Stub::setUsername (const char *pcUsername)
{
     if (m_pTransport)
        m_pTransport->setUsername(pcUsername);
}

void
Stub::setProxyUsername (const char *pcProxyUsername)
{
      logEntryEngine("Stub::setProxyUsername")

    if (m_proxyUsername)
    {
        delete[]m_proxyUsername;
        m_proxyUsername = NULL;
    }

    if (pcProxyUsername)
    {
        m_proxyUsername = new char[strlen (pcProxyUsername) + 1];
        strcpy (m_proxyUsername, pcProxyUsername);
    
        if (m_proxyPassword)
            setProxyAuthorizationHeader ();
    }
    
    logExit()
}

void
Stub::setPassword (const char *pcPassword)
{
      if (m_pTransport)
        m_pTransport->setPassword(pcPassword);
}

void
Stub::setProxyPassword (const char *pcProxyPassword)
{
    if (m_proxyPassword)
    {
        delete[]m_proxyPassword;
        m_proxyPassword = NULL;
    }

    if (pcProxyPassword)
    {
        m_proxyPassword = new char[strlen (pcProxyPassword) + 1];
        strcpy (m_proxyPassword, pcProxyPassword);
    
        if (m_proxyUsername)
            setProxyAuthorizationHeader ();
    }
}


const char *
Stub::getProxyUsername ()
{
    return m_proxyUsername;
}


const char *
Stub::getProxyPassword ()
{
    return m_proxyPassword;
}


void 
Stub::setProxyAuthorizationHeader ()
{
      logEntryEngine("Stub::setProxyAuthorizationHeader")

    char* cpUsernamePassword = new char[strlen( m_proxyUsername) + strlen( m_proxyPassword ) + 2];
    strcpy( cpUsernamePassword, m_proxyUsername );
    strcat( cpUsernamePassword, ":" );
    strcat( cpUsernamePassword, m_proxyPassword );
    
    int len = apr_base64_encode_len (strlen(cpUsernamePassword));
    AxisChar* base64Value = new AxisChar[len + 1];
    len = apr_base64_encode (base64Value, (const char*)cpUsernamePassword);
  
    std::string strValue = "Basic ";
    strValue += base64Value;
  
    this->setTransportProperty( "Proxy-Authorization", strValue.c_str());
    delete [] cpUsernamePassword;
    delete [] base64Value;
      
    logExit()
}

ISoapAttachment* Stub::createSoapAttachment()
{
      logEntryEngine("Stub::createSoapAttachment")

    return m_pCall->createSoapAttachment();
      
    logExit()
}

/*Methods for supporting SecureChannel*/
void Stub::SetSecure( char * pszArguments, ...)
{
      logEntryEngine("Stub::SetSecure")

    va_list args;
    
    va_start( args, pszArguments);    
    SetSecure(pszArguments, args);
    va_end( args);
      
    logExit()
}

/*Methods for supporting SecureChannel*/
void Stub::SetSecure( char * pszArguments, va_list args)
{
      logEntryEngine("Stub::SetSecure")

    int iArgIndex = 0;
    char * pszArg = pszArguments;
    
    if (pszArg != NULL)
    {
        do
        {
            m_sArguments[iArgIndex] = pszArg;
            iArgIndex++;
        } 
        while( (pszArg = va_arg( args, char *)) != NULL && iArgIndex < 8);
        
        // Leave for now, but remove in future. 
        if( iArgIndex == 6)
            m_sArguments[iArgIndex] = "false";
    }
      
    logExit()
}

void Stub::includeSecure()
{
    m_pCall->setTransportProperty( SECURE_PROPERTIES, (const char *) &m_sArguments);
}

void 
Stub::checkForExtraneousElements ()
{     
      logEntryEngine("Stub::checkForExtraneousElements")

    IWrapperSoapDeSerializer *pDeSerializer = m_pCall->getSOAPDeSerializer();
    if (pDeSerializer && m_pTransport->isThereResponseData())
    {
        const char *peekedElementName = pDeSerializer->peekNextElementName();
        if (0x00 != *peekedElementName)
        {
            logThrowExceptionWithData("UnknownElementException", peekedElementName)

            throw UnknownElementException(peekedElementName);
        }
    }
    
    logExit()
}
