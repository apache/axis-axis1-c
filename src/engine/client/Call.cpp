// Call.cpp: implementation of the Call class.
//
//////////////////////////////////////////////////////////////////////

#include "Call.h"
//#include "../../../common/IMessageData.h"
//#include "../../../common/ISoapMethod.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern "C" int initialize_module(int bServer);

extern "C" int send_response_bytes(const char* res, const void* opstream);
extern "C" int get_request_bytes(char* req, int reqsize, int* retsize, const void* ipstream);
extern "C" int send_transport_information(void *str);
extern "C" int receive_transport_information(void *str);

Call::Call()
{
	m_pAxisEngine = NULL;
	m_pMsgData = NULL;
	m_pIWSSZ = NULL;
	m_pIWSDZ = NULL;
	m_Soap.so.http.ip_headercount = 0;
	m_Soap.so.http.ip_headers = NULL;
	initialize_module(0);
}

Call::~Call()
{

}

int Call::SetEndpointURI(const char *pchEndpointURI)
{
	m_Soap.so.http.uri_path = pchEndpointURI;
	return SUCCESS;
}

void Call::SetOperation(const char *pchOperation, const char* pchNamespace)
{
	ISoapMethod* pMethod= m_pIWSSZ->createSoapMethod();
	pMethod->setLocalName(pchOperation);
	pMethod->setPrefix(m_pIWSSZ->getNewNamespacePrefix());
	pMethod->setUri(pchNamespace);
}

void Call::AddParameter(int nValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(nValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned int unValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(unValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(short sValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(sValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned short usValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(usValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(long lValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(lValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned long ulValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(ulValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(char cValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(cValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(unsigned char ucValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(ucValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(float fValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(fValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(double dValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(dValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(struct tm tValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(tValue);
	pRetParam->SetName(pchName);
}

void Call::AddParameter(const AxisChar* pStrValue,const char* pchName)
{
	IParam* pRetParam = m_pIWSSZ->AddOutputParam(pStrValue);
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

void Call::SetReturnType(void *pObject, void *pDZFunct, void *pDelFunct, const char* pchTypeName, const char * pchUri)
{
	m_nReturnType = USER_TYPE;
	m_ReturnCplxObj.pObject = pObject;
	m_ReturnCplxObj.pDZFunct = (AXIS_DESERIALIZE_FUNCT)pDZFunct;
	m_ReturnCplxObj.pDelFunct = (AXIS_OBJECT_DELETE_FUNCT)pDelFunct;
	m_ReturnCplxObj.m_TypeName = pchTypeName;
	m_ReturnCplxObj.m_URI = pchUri;
}

int Call::Invoke()
{
	int nStatus;
	Param *pParam = NULL;
	if (SUCCESS == (nStatus = m_pAxisEngine->Process(&m_Soap)))
	{
		if (m_nReturnType == USER_TYPE)
		{
			/*
			The first element of the soap message (after the soap			
			body element) is taken as a parameter itself so that
			the return type can be checked. So need to call GetParam
			on the deserializer before getting the actual params
			*/
			pParam = (Param*)m_pIWSDZ->GetParam();

			if (pParam && (m_ReturnCplxObj.m_TypeName == pParam->GetTypeName()))
			{
				m_ReturnCplxObj.pDZFunct(m_ReturnCplxObj.pObject, m_pMsgData->m_pDZ);
			}
			else
			{
				return FAIL;
			}

		}
		else if (m_nReturnType == XSD_ARRAY)
		{
			
		}
		else //basic type
		{
			pParam = (Param*)m_pIWSDZ->GetParam();
			if (pParam) m_uReturnValue = pParam->GetValue();
		}
	}
	return nStatus;
}

uParamValue Call::GetResult()
{
	return m_uReturnValue;
}

int Call::Initialize()
{
	m_Soap.sessionid = "somesessionid1234";
	if (SUCCESS != OpenConnection()) return FAIL;
	if (m_pAxisEngine) delete m_pAxisEngine;
	m_pAxisEngine = new ClientAxisEngine();
	if (!m_pAxisEngine) return FAIL;
	if (SUCCESS == m_pAxisEngine->Initialize())
	{
		m_pMsgData = m_pAxisEngine->GetMessageData();
		if (m_pMsgData)
		{
			m_pMsgData->getSoapSerializer((IWrapperSoapSerializer**)(&m_pIWSSZ));
			m_pMsgData->getSoapDeSerializer((IWrapperSoapDeSerializer**)(&m_pIWSDZ));
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
	CloseConnection();
	return SUCCESS;
}

int Call::SetProtocol(AXIS_PROTOCOL_TYPE protocol)
{
	m_Soap.trtype = protocol;
	return 0;
}

int Call::SetHeader(char *key, char *value)
{
	set_header(&m_Soap, key, value);
	return 0;
}

/**
 * This method takes a look at the m_Soap structure and open 
 * transport layer connection to the server. Then this adds the 
 * relevant function pointers and streams to the m_Soap structure, 
 * which is given to the AxisEngine. AxisEngine can use those 
 * functions with those streams at any time it wants to send/receive
 * bytes to/from the server.
 */
int Call::OpenConnection()
{
	//Step 1 - Open Transport layer connection taking into account protocol and endpoint URI in m_Soap
	//Step 2 - Set Created streams to m_Soap.str.ip_stream and m_Soap.str.op_stream
	//Step 3 - Add function pointers to the m_Soap structure
	m_Soap.transport.pGetFunct = get_request_bytes;
	m_Soap.transport.pSendFunct = send_response_bytes;
	m_Soap.transport.pGetTrtFunct = receive_transport_information;
	m_Soap.transport.pSendTrtFunct = send_transport_information;
	return SUCCESS;
}

/**
 * This method closes the connection of this object to the server
 */
void Call::CloseConnection()
{
	//Step 1 - Close 2 streams
	//Step 2 - Possibly delete the streams
	//Step 3 - Set function pointers in the m_Soap structure to NULL;
	m_Soap.transport.pGetFunct = NULL;
	m_Soap.transport.pSendFunct = NULL;
	m_Soap.transport.pGetTrtFunct = NULL;
	m_Soap.transport.pSendTrtFunct = NULL;
}

void Call::SetSOAPVersion(SOAP_VERSION version)
{
	m_pIWSSZ->setSoapVersion(version);
}
