///////////////////////////////////////////////////////////////////////
// This is the Client Stub implementation file genarated by WSDL2Ws tool.
// InteropTestPortType.cpp: implemtation for the InteropTestPortType.
//
//////////////////////////////////////////////////////////////////////

#include "InteropTestPortType.h"

#include <axis/server/AxisWrapperAPI.h>

bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;

extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(void* pObj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

InteropTestPortType::InteropTestPortType()
{
	m_pCall = new Call();
	m_pCall->SetProtocol(APTHTTP);
	m_pCall->SetEndpointURI("http://localhost/axis/baseDL");
}

InteropTestPortType::~InteropTestPortType()
{
	delete m_pCall;
}


//Methods corresponding to the web service methods

/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoString
//////////////////////////////////////////////////////////////////
AxisChar* InteropTestPortType::echoString(AxisChar* Value0)
{
	int nStatus;
	AxisChar* Ret = '\0';
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoString");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoString", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputString", XSD_STRING);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoStringResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsString("echoStringReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStringArray
//////////////////////////////////////////////////////////////////
ArrayOfstring InteropTestPortType::echoStringArray(ArrayOfstring Value0)
{
	int nStatus;
	ArrayOfstring RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoStringArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStringArray", "http://soapinterop.org/");
	m_pCall->AddBasicArrayParameter((Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoStringArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOfstring&) m_pCall->GetBasicArray(XSD_STRING,"echoStringArrayReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoInteger
//////////////////////////////////////////////////////////////////
int InteropTestPortType::echoInteger(int Value0)
{
	int nStatus;
	int Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoInteger");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoInteger", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputInteger", XSD_INT);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoIntegerResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsInt("echoIntegerReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoIntegerArray
//////////////////////////////////////////////////////////////////
ArrayOfint InteropTestPortType::echoIntegerArray(ArrayOfint Value0)
{
	int nStatus;
	ArrayOfint RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoIntegerArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoIntegerArray", "http://soapinterop.org/");
	m_pCall->AddBasicArrayParameter((Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoIntegerArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOfint&) m_pCall->GetBasicArray(XSD_INT,"echoIntegerArrayReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoFloat
//////////////////////////////////////////////////////////////////
float InteropTestPortType::echoFloat(float Value0)
{
	int nStatus;
	float Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoFloat");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoFloat", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoFloatResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsFloat("echoFloatReturn",0);
		}
		else /* probably a fault returned */ 
		{
			
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoFloatArray
//////////////////////////////////////////////////////////////////
ArrayOffloat InteropTestPortType::echoFloatArray(ArrayOffloat Value0)
{
	int nStatus;
	ArrayOffloat RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoFloatArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoFloatArray", "http://soapinterop.org/");
	m_pCall->AddBasicArrayParameter((Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoFloatArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOffloat&)m_pCall->GetBasicArray(XSD_FLOAT,"echoFloatArrayReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStruct
//////////////////////////////////////////////////////////////////
SOAPStruct* InteropTestPortType::echoStruct(SOAPStruct* Value0)
{
	int nStatus;
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return pReturn;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoStruct");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStruct", "http://soapinterop.org/");
	m_pCall->AddCmplxParameter(Value0, (void*) Axis_Serialize_SOAPStruct, (void*) Axis_Delete_SOAPStruct, "structInput", "");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoStructResponse", "http://soapinterop.org/"))
		{
			pReturn = (SOAPStruct*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, "structReturn", "");
		}
	}
	m_pCall->UnInitialize();
	return pReturn;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoStructArray
//////////////////////////////////////////////////////////////////
ArrayOfSOAPStruct InteropTestPortType::echoStructArray(ArrayOfSOAPStruct Value0)
{
	int nStatus;
	ArrayOfSOAPStruct RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return RetArray;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoStructArray");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoStructArray", "http://soapinterop.org/");
	m_pCall->AddCmplxArrayParameter((Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "structArray", "");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoStructArrayResponse", "http://soapinterop.org/"))
		{
			RetArray = (ArrayOfSOAPStruct&)m_pCall->GetCmplxArray((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "structArrayReturn", "");
		}
	}
	m_pCall->UnInitialize();
	return RetArray;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoVoid
//////////////////////////////////////////////////////////////////
void InteropTestPortType::echoVoid()
{
	int nStatus;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoVoid");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoVoid", "http://soapinterop.org/");
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS != m_pCall->CheckMessage("echoVoidResponse", "http://soapinterop.org/"))
		{
			/* not successfull */
		}
	}
	m_pCall->UnInitialize();
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoBase64
//////////////////////////////////////////////////////////////////
xsd__base64Binary InteropTestPortType::echoBase64(xsd__base64Binary Value0)
{
	int nStatus;
	xsd__base64Binary Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoBase64");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoBase64", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputBase64", XSD_BASE64BINARY);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoBase64Response", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsBase64Binary("echoBase64Return",0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoDate
//////////////////////////////////////////////////////////////////
xsd__dateTime InteropTestPortType::echoDate(xsd__dateTime Value0)
{
	int nStatus;
	xsd__dateTime Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoDate");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoDate", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputDate", XSD_DATETIME);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoDateResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsDateTime("echoDateReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoHexBinary
//////////////////////////////////////////////////////////////////
xsd__hexBinary InteropTestPortType::echoHexBinary(xsd__hexBinary Value0)
{
	int nStatus;
	xsd__hexBinary Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoHexBinary");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoHexBinary", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoHexBinaryResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsHexBinary("echoHexBinaryReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoDecimal
//////////////////////////////////////////////////////////////////
xsd__decimal InteropTestPortType::echoDecimal(xsd__decimal Value0)
{
	int nStatus;
	xsd__decimal Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoDecimal");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoDecimal", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputDecimal", XSD_DECIMAL);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoDecimalResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsDecimal("echoDecimalReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}


/////////////////////////////////////////////////////////////////
// This method wrap the service methodechoBoolean
//////////////////////////////////////////////////////////////////
xsd__boolean InteropTestPortType::echoBoolean(xsd__boolean Value0)
{
	int nStatus;
	xsd__boolean Ret;
	if (AXIS_SUCCESS != m_pCall->Initialize(CPP_DOC_PROVIDER, 0)) return Ret;
	m_pCall->SetTransportProperty(SOAPACTION_HEADER, "baseDL#echoBoolean");
	m_pCall->SetSOAPVersion(SOAP_VER_1_1);
	m_pCall->SetOperation("echoBoolean", "http://soapinterop.org/");
	m_pCall->AddParameter((void*)&Value0, "inputBoolean", XSD_BOOLEAN);
	nStatus = m_pCall->Invoke();
	if (AXIS_SUCCESS == nStatus)
	{
		if (AXIS_SUCCESS == m_pCall->CheckMessage("echoBooleanResponse", "http://soapinterop.org/"))
		{
			Ret = m_pCall->GetElementAsBoolean("echoBooleanReturn",0);
		}
	}
	m_pCall->UnInitialize();
	return Ret;
}

