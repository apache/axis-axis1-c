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

#include <Stub.h>
#include <stdio.h>

#include <axis/server/AxisWrapperAPI.h>


Stub::Stub(const char* pcEndPointUri)
{
	m_pCall = new Call();
	m_pCall->setProtocol(APTHTTP);
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

	for (unsigned int i = 0; i < m_vSOAPHeaderBlocks.size(); i++)
        {
                delete m_vSOAPHeaderBlocks[i];
        }
}

int Stub::initilizeCall()
{
    if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return AXIS_FAIL;
        m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoString");
        m_pCall->setSOAPVersion(SOAP_VER_1_1);
        m_pCall->setOperation("echoString", "http://soapinterop.org/");
	setTransportProperties();
	setSOAPHeaders();
    return AXIS_SUCCESS;

}

void Stub::setEndPoint(char* pcEndPoint)
{
	m_pCall->setEndpointURI(pcEndPoint);
}


void Stub::setTransportProperty(const char* pcKey, const char* pcValue)
{
       if (pcKey && pcValue) 
	{
		m_vKeys.push_back( strdup(pcKey) );
		m_vValues.push_back( strdup(pcValue) );
	}
}

void Stub::setTransportProperties()
{
	SOAPTransport* pTrasport = NULL;
	if(m_pCall)
		pTrasport = m_pCall->getTransport();
	if (pTrasport)
	{
		for (unsigned int i = 0; i < m_vKeys.size(); i++)
	        {
			pTrasport->setTransportProperty(m_vKeys[i], m_vValues[i]);
	        }
	} 
}
	
IHeaderBlock* Stub::createHeaderBlock(AxisChar *pachLocalName, 
	AxisChar *pachPrefix, AxisChar *pachUri)
{
	if(pachLocalName && pachPrefix && pachUri)
	{
		IHeaderBlock* pNewSoapheader = new HeaderBlock(pachLocalName, pachPrefix, pachUri);
		m_vSOAPHeaderBlocks.push_back(pNewSoapheader);
		return pNewSoapheader;
	}
	else 
		return NULL;
}

void Stub::setSOAPHeaders()
{
        SoapSerializer* pSerializer = NULL;
	if(m_pCall)
		pSerializer = m_pCall->getSOAPSerializer();
	if (pSerializer)
        {
                for (unsigned int i = 0; i < m_vSOAPHeaderBlocks.size(); i++)
                {
			pSerializer->addHeaderBlock(m_vSOAPHeaderBlocks[i]->clone());
                }
        }
}

