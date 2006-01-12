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
#include "../../common/AxisUtils.h"
#include "../../soap/apr_base64.h"
#include "../../common/AxisConfig.h"
#include "../../common/AxisGenException.h"

extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

AXIS_CPP_NAMESPACE_USE
    Stub::Stub (const char *pcEndPointUri, AXIS_PROTOCOL_TYPE eProtocol):
m_pcUsername (NULL),
m_pcPassword (NULL),
m_proxyUsername (NULL),
m_proxyPassword (NULL)
{
    m_pCall = new Call ();
    m_pCall->setProtocol (eProtocol);
    m_pTransport = m_pCall->getTransport ();
    m_pTransport->setEndpointUri( pcEndPointUri);
    
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
            {
                pszArgPtr++;
            }
        }
    }
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

    if (m_pcUsername)
	delete[]m_pcUsername;
    if (m_pcPassword)
	delete[]m_pcPassword;
}

void
Stub::setEndPoint (const char *pcEndPoint)
{
    if (m_pTransport)
    {
        m_pTransport->setEndpointUri( pcEndPoint);
    }
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
Stub::getFirstTransportPropertyKey (bool response)
{
    if (m_pTransport)
	return m_pTransport->getFirstTransportPropertyKey (response);
    else
	return NULL;
}

const char *
Stub::getNextTransportPropertyKey (bool response)
{
    if (m_pTransport)
	return m_pTransport->getNextTransportPropertyKey (response);
    else
	return NULL;
}

const char *
Stub::getCurrentTransportPropertyKey (bool response)
{
    if (m_pTransport)
	   return m_pTransport->getCurrentTransportPropertyKey (response);
    else
	   return NULL;
}

const char *
Stub::getCurrentTransportPropertyValue (bool response)
{
    if (m_pTransport)
	return m_pTransport->getCurrentTransportPropertyValue (response);
    else
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
    if (m_pTransport)
    {
        m_pTransport->setProxy (pcProxyHost, uiProxyPort);
    }
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
Stub::setProxyUsername (const char *pcProxyUsername)
{
    if (m_proxyUsername)
    {
	delete[]m_proxyUsername;
	m_proxyUsername = NULL;
    }

    if (!pcProxyUsername)
	return;

    m_proxyUsername = new char[strlen (pcProxyUsername) + 1];
    strcpy (m_proxyUsername, pcProxyUsername);

    if (m_proxyPassword)
    {
	setProxyAuthorizationHeader ();
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

void
Stub::setProxyPassword (const char *pcProxyPassword)
{
    if (m_proxyPassword)
    {
	delete[]m_proxyPassword;
	m_proxyPassword = NULL;
    }

    if (!pcProxyPassword)
	return;

    m_proxyPassword = new char[strlen (pcProxyPassword) + 1];
    strcpy (m_proxyPassword, pcProxyPassword);

    if (m_proxyUsername)
    {
	setProxyAuthorizationHeader ();
    }
}

const char *
Stub::getUsername ()
{
    return m_pcUsername;
}

const char *
Stub::getProxyUsername ()
{
    return m_proxyUsername;
}

const char *
Stub::getPassword ()
{
    return m_pcPassword;
}

const char *
Stub::getProxyPassword ()
{
    return m_proxyPassword;
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

void 
Stub::setProxyAuthorizationHeader ()
{
    char* cpUsernamePassword = new char[strlen( m_proxyUsername) + strlen( m_proxyPassword ) + 2];
    strcpy( cpUsernamePassword, m_proxyUsername );
    strcat( cpUsernamePassword, ":" );
    strcat( cpUsernamePassword, m_proxyPassword );
    int len = apr_base64_encode_len (strlen(cpUsernamePassword));
     
	AxisChar* base64Value = new AxisChar[len + 1];
    len = apr_base64_encode_binary ( base64Value, (const unsigned char*)cpUsernamePassword, strlen
                                                                                   (cpUsernamePassword));
  
	std::string strValue = "Basic ";
    strValue += base64Value;
  
	this->setTransportProperty( "Proxy-Authorization", strValue.c_str());
    delete [] cpUsernamePassword;
    delete [] base64Value;

}

ISoapAttachment* Stub::createSoapAttachment()
{
	return m_pCall->createSoapAttachment();
}

/*Methods for supporting SecureChannel*/
void Stub::SetSecure( char * pszArguments, ...)
{
    int iArgIndex = 0;
    va_list args;
    char *  pszArg = NULL;
    
    va_start( args, pszArguments);
    
    if( (pszArg = pszArguments) != NULL)
    {
        do
        {
            if( pszArg == (char *) 1)
            {
                m_sArguments[iArgIndex] = "true";
            }
            else
            {
                m_sArguments[iArgIndex] = pszArg;
            }

            iArgIndex++;
        } while( (pszArg = va_arg( args, char *)) != NULL && iArgIndex < 8);

        if( iArgIndex == 6)
        {
            m_sArguments[iArgIndex] = "false";
        }
    }

    va_end( args);
}

void Stub::includeSecure()
{
    m_pCall->setTransportProperty( SECURE_PROPERTIES, (const char *) &m_sArguments);
}
