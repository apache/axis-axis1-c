/* -*- C++ -*- */
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
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * AxisAdminService.cpp: implemtation for the AxisAdminService.
 *
 */

#include "AxisAdminService.h"

#include <axis/AxisWrapperAPI.hpp>
#include <axis/Axis.hpp>

AXIS_CPP_NAMESPACE_START

AxisAdminService::AxisAdminService(const char* pcEndpointUri, AXIS_PROTOCOL_TYPE eProtocol):Stub(pcEndpointUri, eProtocol)
{
}

AxisAdminService::AxisAdminService()
:Stub(" ", APTHTTP1_1)
{
	m_pCall->setEndpointURI("http://localhost/axis/AxisAdmin");
}

AxisAdminService::~AxisAdminService()
{
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodupdateWSDD
 */
xsd__boolean AxisAdminService::updateWSDD(xsd__base64Binary Value0)
{
	xsd__boolean Ret = false_;
	const char* pcCmplxFaultName = NULL;
	try
	{
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;

	if (NULL==m_pCall->getTransportProperty("SOAPAction",false))
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "AxisAdmin#updateWSDD");

	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("updateWSDD", "http://www.opensource.lk/xsd");

	includeSecure();
	applyUserPreferences();

	char cPrefixAndParamName0[] = "wsdd";
	m_pCall->addParameter((void*)&Value0, cPrefixAndParamName0, XSD_BASE64BINARY);

	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("updateWSDDResponse", "http://www.opensource.lk/xsd"))
		{
			xsd__boolean * pReturn = m_pCall->getElementAsBoolean("return", 0);
			if(pReturn)
			{
				Ret = *pReturn;
				Axis::AxisDelete( (void *) pReturn, XSD_BOOLEAN);
			}
		}
	}
	m_pCall->unInitialize();
	return Ret;
	}
	catch(AxisException& e)
	{
		int iExceptionCode = e.getExceptionCode();

		if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
		{
			m_pCall->unInitialize();
			throw;
		}

		ISoapFault* pSoapFault = (ISoapFault*)
			m_pCall->checkFault("Fault","http://localhost/axis/AxisAdmin" );

		if(pSoapFault)
		{
			const char *detail = pSoapFault->getSimpleFaultDetail();
			bool deleteDetail=false;

			if (NULL==detail || 0==strlen(detail))
			{
				detail=m_pCall->getFaultAsXMLString();
				if (NULL==detail)
					detail="";
				else
					deleteDetail=true;
			}

			OtherFaultException ofe(pSoapFault->getFaultcode(),
				pSoapFault->getFaultstring(), pSoapFault->getFaultactor(),
				detail, iExceptionCode);

			if (deleteDetail && NULL!=detail)
				Axis::AxisDelete( (void *) const_cast<char*>(detail), XSD_STRING);

			m_pCall->unInitialize();
			delete pSoapFault;
			throw ofe;
		}
		else
		{
			m_pCall->unInitialize();
			delete pSoapFault;
			throw;
		}
	}
}


xsd__boolean AxisAdminService::stopAxis()
{
	xsd__boolean Ret = false_;
	const char* pcCmplxFaultName = NULL;
	try
	{
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER)) return Ret;

	if (NULL==m_pCall->getTransportProperty("SOAPAction",false))
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "AxisAdmin#stopAxis");

	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("stopAxis", "http://www.opensource.lk/xsd");

	includeSecure();
	applyUserPreferences();


	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("stopAxisResponse", "http://www.opensource.lk/xsd"))
		{
			xsd__boolean * pReturn = m_pCall->getElementAsBoolean("return", 0);
			if(pReturn)
			{
				Ret = *pReturn;
				Axis::AxisDelete( (void *) pReturn, XSD_BOOLEAN);
			}
		}
	}
	m_pCall->unInitialize();
	return Ret;
	}
	catch(AxisException& e)
	{
		int iExceptionCode = e.getExceptionCode();

		if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
		{
			m_pCall->unInitialize();
			throw;
		}

		ISoapFault* pSoapFault = (ISoapFault*)
			m_pCall->checkFault("Fault","http://localhost/axis/AxisAdmin" );

		if(pSoapFault)
		{
			const char *detail = pSoapFault->getSimpleFaultDetail();
			bool deleteDetail=false;

			if (NULL==detail || 0==strlen(detail))
			{
				detail=m_pCall->getFaultAsXMLString();
				if (NULL==detail)
					detail="";
				else
					deleteDetail=true;
			}

			OtherFaultException ofe(pSoapFault->getFaultcode(),
				pSoapFault->getFaultstring(), pSoapFault->getFaultactor(),
				detail, iExceptionCode);

			if (deleteDetail && NULL!=detail)
				Axis::AxisDelete( (void *) const_cast<char*>(detail), XSD_STRING);

			m_pCall->unInitialize();
			delete pSoapFault;
			throw ofe;
		}
		else
		{
			m_pCall->unInitialize();
			delete pSoapFault;
			throw;
		}
	}
}
AXIS_CPP_NAMESPACE_END
