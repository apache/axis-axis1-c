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
 */

/*
 * This is the client Stub base class
 * Stub.cpp: implemtation for the Stub.
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

#include <axis/client/Stub.h>
#include <stdio.h>

#include <axis/server/AxisWrapperAPI.h>


Stub::Stub (const char *pcEndPointUri)
:m_strProxyHost(""), m_uiProxyPort(0), m_bUseProxy(false)
{
    m_pCall = new Call ();
    m_pCall->setProtocol (APTHTTP);
    m_pCall->setEndpointURI (pcEndPointUri);
}

Stub::~Stub ()
{
    delete m_pCall;
    for (unsigned int i = 0; i < m_vKeys.size (); i++)
    {
	free (m_vKeys[i]);
	free (m_vValues[i]);
    }

    for (unsigned int j = 0; j < m_vSOAPHeaderBlocks.size (); j++)
    {
	delete m_vSOAPHeaderBlocks[j];
    }
}

int
Stub::initilizeCall ()
{
    if (AXIS_SUCCESS !=
	m_pCall->initialize (CPP_RPC_PROVIDER, NORMAL_CHANNEL))
	return AXIS_FAIL;
    m_pCall->setTransportProperty (SOAPACTION_HEADER, "base#echoString");
    m_pCall->setSOAPVersion (SOAP_VER_1_1);
    m_pCall->setOperation ("echoString", "http://soapinterop.org/");
    setTransportProperties ();
    setSOAPHeaders ();
    return AXIS_SUCCESS;

}

void
Stub::setEndPoint (char *pcEndPoint)
{
    m_pCall->setEndpointURI (pcEndPoint);
}


void
Stub::setTransportProperty (const char *pcKey, const char *pcValue)
{
    if (pcKey && pcValue)
    {
	m_vKeys.push_back (strdup (pcKey));
	m_vValues.push_back (strdup (pcValue));
    }
}

void
Stub::setTransportProperties ()
{
    SOAPTransport *pTrasport = NULL;
    if (m_pCall)
	pTrasport = m_pCall->getTransport ();
    if (pTrasport)
    {
	for (unsigned int i = 0; i < m_vKeys.size (); i++)
	{
	    pTrasport->setTransportProperty (m_vKeys[i], m_vValues[i]);
	}
    }
}

IHeaderBlock *
Stub::createHeaderBlock (AxisChar * pachLocalName,
			 AxisChar * pachPrefix, AxisChar * pachUri)
{
    if (pachLocalName && pachPrefix && pachUri)
    {
	IHeaderBlock *pNewSoapheader =
	    new HeaderBlock (pachLocalName, pachPrefix, pachUri);
	m_vSOAPHeaderBlocks.push_back (pNewSoapheader);
	return pNewSoapheader;
    }
    else
	return NULL;
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
	    pSerializer->addHeaderBlock (m_vSOAPHeaderBlocks[i]->clone ());
	}
    }
}

void
Stub::applyUserPreferences ()
{
    setSOAPHeaders ();
    setTransportProperties ();
}

void Stub::setProxy(const char* pcProxyHost, unsigned int uiProxyPort)
{
    /*m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;    */
    m_pCall->setProxy(pcProxyHost, uiProxyPort);
}

void Stub::setProxy()
{
    /*if(m_bUseProxy)
    {
        SOAPTransport *pTrasport = NULL;
        if (m_pCall)
            pTrasport = m_pCall->getTransport ();
        if (pTrasport)
        {
            pTrasport->setProxy(m_strProxyHost, m_uiProxyPort);
        }
    }*/
}
