// Call.cpp: implementation of the Call class.
//
//////////////////////////////////////////////////////////////////////

#include "Call.h"
//#include "../../../common/IMessageData.h"
//#include "../../../common/ISoapMethod.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Call::Call()
{
	m_pAxisEngine = NULL;
}

Call::~Call()
{

}

int Call::SetEndpointURI(const char *pchEndpointURI)
{
	return SUCCESS;
}

void Call::SetOperation(const char *pchOperation, const char* pchNamespace)
{
	ISoapMethod* pMethod= m_pIWSSZ->createSoapMethod();
	pMethod->setLocalName(pchOperation);
	pMethod->setPrefix(m_pIWSSZ->getNewNamespacePrefix());
	pMethod->setUri(pchNamespace);
}

void Call::AddParameter(XSDTYPE nType, uParamValue Value, const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(nType, Value);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(IArrayBean *pArrayBean, const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pArrayBean);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(void *pObject, void *pSZFunct, void *pDelFunct, const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pObject, pSZFunct, pDelFunct);
	pRetParam->SetName(pchName);
}

void Call::SetReturnType(XSDTYPE nType)
{
	m_nReturnType = nType;
}

void Call::SetReturnType(void *pObject, void *pDZFunct, void *pDelFunct)
{
	m_nReturnType = USER_TYPE;
	m_ReturnCplxObj.pObject = pObject;
	m_ReturnCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
	m_ReturnCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
}

int Call::Invoke()
{
	int nStatus;
	if (SUCCESS == (nStatus = m_pAxisEngine->Process(&m_Soap)))
	{
		if (m_nReturnType == USER_TYPE)
		{
			m_ReturnCplxObj.pDZFunct(m_ReturnCplxObj.pObject, m_pMsgData);
		}
		else if (m_nReturnType == XSD_ARRAY)
		{
			
		}
		else //basic type
		{
			m_Param.
			m_pIWSDZ->DeSerialize(m_nReturnType, &m_uReturnValue);
		}
	}
	return nStatus;
}

const uParamValue& Call::GetResult()
{
	return m_uReturnValue;
}

int Call::Initialize()
{
	if (m_pAxisEngine) delete m_pAxisEngine;
	m_pAxisEngine = new ClientAxisEngine();
	if (!m_pAxisEngine) return FAIL;
	if (SUCCESS == m_pAxisEngine->Initialize())
	{
		m_pMsgData = m_pAxisEngine->GetMessageData();
		if (m_pMsgData)
		{
			m_pMsgData->getSoapSerializer(&m_pIWSSZ);
			m_pMsgData->getSoapDeSerializer(&m_pIWSDZ);
			if (m_pIWSSZ && m_pIWSDZ)
			{
				return SUCCESS;
			}
		}
		return SUCCESS;
	}
	return FAIL;
}

int Call::UnInitialize()
{
	if (m_pAxisEngine) 
	{
		m_pAxisEngine->UnInitialize();
		delete m_pAxisEngine;
		m_pAxisEngine = NULL;
	}
	return SUCCESS;
}
