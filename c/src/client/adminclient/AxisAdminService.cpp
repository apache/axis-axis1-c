/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * AxisAdminService.cpp: implemtation for the AxisAdminService.
 *
 */

#include "AxisAdminService.h"

#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
AxisAdminService::AxisAdminService()
{
	m_pCall = new Call();
	m_pCall->SetProtocol(APTHTTP);
	m_pCall->SetEndpointURI("http://localhost/axis/AxisAdmin");
}

AxisAdminService::~AxisAdminService()
{
	delete m_pCall;
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methoddeploy
 */
xsd__boolean AxisAdminService::deploy(xsd__base64Binary Value0)
{
	xsd__boolean Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, NORMAL_CHANNEL)) return Ret;
		m_pCall->SetTransportProperty(SOAPACTION_HEADER , "AxisAdmin#deploy");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("deploy", "http://www.opensource.lk/xsd");
	m_pCall->AddParameter((void*)&Value0, "wsdd", XSD_BASE64BINARY);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("deployResponse", "http://www.opensource.lk/xsd"))
		{
			Ret = m_pCall->GetElementAsBoolean("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/*
 * This method wrap the service methodundeploy
 */
xsd__boolean AxisAdminService::undeploy(xsd__base64Binary Value0)
{
	xsd__boolean Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, NORMAL_CHANNEL)) return Ret;
		m_pCall->SetTransportProperty(SOAPACTION_HEADER , "AxisAdmin#undeploy");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("undeploy", "http://www.opensource.lk/xsd");
	m_pCall->AddParameter((void*)&Value0, "wsdd", XSD_BASE64BINARY);
	if (AXIS_SUCCESS == m_pCall->Invoke())
	{
		if(AXIS_SUCCESS == m_pCall->CheckMessage("undeployResponse", "http://www.opensource.lk/xsd"))
		{
			Ret = m_pCall->GetElementAsBoolean("return", 0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}

