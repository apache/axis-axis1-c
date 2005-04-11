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

#include <axis/client/Stub.hpp>
#include <stdio.h>
#include "../../transport/SOAPTransport.h"
#include <axis/AxisWrapperAPI.hpp>
#include "../../soap/SoapSerializer.h"
#include "../../soap/Attribute.h"
#include "../../common/AxisUtils.h"
#include "../../soap/apr_base64.h"

AXIS_CPP_NAMESPACE_USE
    Stub::Stub (const char *pcEndPointUri, AXIS_PROTOCOL_TYPE eProtocol):
m_pcUsername (NULL),
m_pcPassword (NULL)
{
    m_pCall = new Call ();
    m_pCall->setProtocol (eProtocol);
    m_pCall->setEndpointURI (pcEndPointUri);
    m_pTransport = m_pCall->getTransport ();

    // Initialise m_viCurrentSOAPMethodAttribute to something sensible 
    // in case getFirstSOAPMethodAttribute isn't called first.
    m_viCurrentSOAPMethodAttribute = m_vSOAPMethodAttributes.begin ();
}

Stub::~Stub ()
{
    delete m_pCall;
    m_pCall = NULL;

    unsigned int j = 0;
    for (j = 0; j < m_vSOAPHeaderBlocks.size (); j++)
    {
	delete m_vSOAPHeaderBlocks[j];
	m_vSOAPHeaderBlocks[j] = NULL;
    }

    for (j = 0; j < m_vSOAPMethodAttributes.size (); j++)
    {
	delete m_vSOAPMethodAttributes[j];
	m_vSOAPMethodAttributes[j] = NULL;
    }

    if (m_pcUsername)
	delete[]m_pcUsername;
    if (m_pcPassword)
	delete[]m_pcPassword;
}

void
Stub::setEndPoint (const char *pcEndPoint)
{
    m_pCall->setEndpointURI (pcEndPoint);
}

void
Stub::setTransportProperty (const char *pcKey, const char *pcValue)
{
    if (m_pTransport)
    {
		if(!pcKey)
		{
			m_pTransport=NULL; //this should be set to null. otherwise the previous setting can be still there.
			return;// if the pcKey is set to null, the method returns
		}

		else if (strcmp (pcKey, "SOAPAction") == 0)	//Samisa: Setting SOAPAction, 
	    //may need to add '"' to value - AXISCPP-531
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
			else if (pcValue && (pcValue[0] != '"'))	//starting '"' missing
			{
				char *tempvalue = new char[strlen (pcValue) + 2];
				sprintf (tempvalue, "\"%s", pcValue);
				m_pTransport->setTransportProperty (pcKey, tempvalue);
				delete[]tempvalue;
			}
			else if (pcValue && (pcValue[strlen (pcValue) - 1] != '"'))	// ending '"' missing
			{
				char *tempvalue = new char[strlen (pcValue) + 3];
				sprintf (tempvalue, "\"%s\"", pcValue);
				m_pTransport->setTransportProperty (pcKey, tempvalue);
				delete[]tempvalue;
			}
			else		// both "" present
				m_pTransport->setTransportProperty (pcKey, pcValue);
		}
	
		else
		{
			 m_pTransport->setTransportProperty (pcKey, pcValue);
		}
    }
}

const char *
Stub::getTransportProperty (const char *key, bool response)
{
    return m_pCall->getTransportProperty (key, response);
}

const char *
Stub::getFirstTransportPropertyKey ()
{
    if (m_pTransport)
	return m_pTransport->getFirstTransportPropertyKey ();
    else
	return NULL;
}

const char *
Stub::getNextTransportPropertyKey ()
{
    if (m_pTransport)
	return m_pTransport->getNextTransportPropertyKey ();
    else
	return NULL;
}

const char *
Stub::getCurrentTransportPropertyKey ()
{
    if (m_pTransport)
	return m_pTransport->getCurrentTransportPropertyKey ();
    else
	return NULL;
}

const char *
Stub::getCurrentTransportPropertyValue ()
{
    if (m_pTransport)
	return m_pTransport->getCurrentTransportPropertyValue ();
    else
	return NULL;
}

void
Stub::deleteCurrentTransportProperty ()
{
    if (m_pTransport)
	m_pTransport->deleteCurrentTransportProperty ();
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
    m_pCall->setHandlerProperty (name, value, len);
}

IHeaderBlock *
Stub::createSOAPHeaderBlock (AxisChar * pachLocalName, AxisChar * pachUri)
{
    if (pachLocalName && pachUri)
    {
	if ((AxisUtils::isStringOnlyWithSpaces (pachLocalName)) ||
	    (AxisUtils::isStringOnlyWithSpaces (pachUri)))
	{
	    return NULL;
	}
	else
	{
	    IHeaderBlock *pNewSoapheader =
		m_pCall->createHeaderBlock (pachLocalName, pachUri);
	    m_vSOAPHeaderBlocks.push_back (pNewSoapheader);
	    return pNewSoapheader;
	}
    }
    else
    {
	return NULL;
    }
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
    {
	return (*m_viCurrentSOAPHeaderBlock);
    }
    return NULL;
}

void
Stub::deleteCurrentSOAPHeaderBlock ()
{
    if (m_viCurrentSOAPHeaderBlock != m_vSOAPHeaderBlocks.end ())
    {
	delete (*m_viCurrentSOAPHeaderBlock);
	m_vSOAPHeaderBlocks.erase (m_viCurrentSOAPHeaderBlock);
    }
}

void
Stub::deleteSOAPHeaderBlock (IHeaderBlock * pHeaderBlock)
{
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
}

void
Stub::setSOAPHeaders ()
{
    SoapSerializer *pSerializer = NULL;
    if (m_pCall)
	pSerializer = m_pCall->getSOAPSerializer ();
    if (pSerializer)
    {
	for (unsigned int i = 0; i < m_vSOAPHeaderBlocks.size (); i++)
	{
	    pSerializer->addHeaderBlock (m_vSOAPHeaderBlocks[i]);
	}
    }
}

void
Stub::applyUserPreferences ()
{
    setSOAPHeaders ();
}

void
Stub::setProxy (const char *pcProxyHost, unsigned int uiProxyPort)
{
    m_pCall->setProxy (pcProxyHost, uiProxyPort);
}

void
Stub::setTransportTimeout (const long lSeconds)
{
    if (m_pTransport)
    {
	m_pTransport->setTimeout (lSeconds);
    }
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
    {
	m_pTransport->setMaintainSession (bSession);
    }
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
    else
	return APT_UNKNOWN;
}

IHeaderBlock *
Stub::createSOAPHeaderBlock (AxisChar * pachLocalName, AxisChar * pachUri,
			     AxisChar * pachPrefix)
{
    if (pachLocalName && pachUri && pachPrefix)
    {
	if (AxisUtils::isStringOnlyWithSpaces (pachLocalName) ||
	    AxisUtils::isStringOnlyWithSpaces (pachUri))
	{
	    return NULL;
	}
	else
	{
	    IHeaderBlock *pNewSoapheader =
		m_pCall->createHeaderBlock (pachLocalName, pachUri,
					    pachPrefix);
	    m_vSOAPHeaderBlocks.push_back (pNewSoapheader);
	    return pNewSoapheader;
	}
    }
    else
    {
	return NULL;
    }
}

void
Stub::setUsername (const char *pcUsername)
{
    if (m_pcUsername)
    {
	delete[]m_pcUsername;
	m_pcUsername = NULL;
    }

    if (!pcUsername)
	return;

    m_pcUsername = new char[strlen (pcUsername) + 1];
    strcpy (m_pcUsername, pcUsername);

    if (m_pcPassword)
    {
	setAuthorizationHeader ();
    }
}

void
Stub::setPassword (const char *pcPassword)
{
    if (m_pcPassword)
    {
	delete[]m_pcPassword;
	m_pcPassword = NULL;
    }

    if (!pcPassword)
	return;

    m_pcPassword = new char[strlen (pcPassword) + 1];
    strcpy (m_pcPassword, pcPassword);

    if (m_pcUsername)
    {
	setAuthorizationHeader ();
    }
}

const char *
Stub::getUsername ()
{
    return m_pcUsername;
}

const char *
Stub::getPassword ()
{
    return m_pcPassword;
}

void
Stub::setAuthorizationHeader ()
{
    char *cpUsernamePassword =
	new char[strlen (m_pcUsername) + strlen (m_pcPassword) + 2];
    strcpy (cpUsernamePassword, m_pcUsername);
    strcat (cpUsernamePassword, ":");
    strcat (cpUsernamePassword, m_pcPassword);

    int len = apr_base64_encode_len (strlen (cpUsernamePassword));
    AxisChar *base64Value = new AxisChar[len + 1];
    len =
	apr_base64_encode_binary (base64Value,
				  (const unsigned char *) cpUsernamePassword,
				  strlen (cpUsernamePassword));

    std::string strValue = "Basic ";
    strValue += base64Value;

    if (m_pTransport)
	m_pTransport->setTransportProperty ("Authorization",
					    strValue.c_str ());

    delete[]cpUsernamePassword;
    delete[]base64Value;
}
