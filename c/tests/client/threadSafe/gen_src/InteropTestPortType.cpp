/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortType.cpp: implemtation for the InteropTestPortType.
* Default when no parameter passed. When thrown with no parameter 
more general InteropTestPortType  is assumed.
 *
 */

#include "InteropTestPortType.h"

#include <axis/server/AxisWrapperAPI.h>

using namespace std;

 bool CallBase::bInitialized;
CallFunctions CallBase::ms_VFtable;
extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

InteropTestPortType::InteropTestPortType(const char* pchEndpointUri)
:Stub(pchEndpointUri)
{
}

InteropTestPortType::~InteropTestPortType()
{
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service method echoString
 */
xsd__string InteropTestPortType::echoString(xsd__string Value0)
{
	xsd__string Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoString");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoString", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputString", XSD_STRING);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoStringResponse", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsString("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoStringArray
 */
xsd__string_Array InteropTestPortType::echoStringArray(xsd__string_Array Value0)
{
	xsd__string_Array RetArray = {NULL, 0};
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return RetArray;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoStringArray");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoStringArray", "http://soapinterop.org/");
		applyUserPreferences();
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoStringArrayResponse", "http://soapinterop.org/"))
			{
				RetArray = (xsd__string_Array&)m_pCall->getBasicArray(XSD_STRING, "return", 0);
			}
		}
		m_pCall->unInitialize();
		return RetArray;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoInteger
 */
int InteropTestPortType::echoInteger(int Value0)
{
	int Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoInteger");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoInteger", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputInteger", XSD_INT);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoIntegerResponse", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsInt("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoIntegerArray
 */
xsd__int_Array InteropTestPortType::echoIntegerArray(xsd__int_Array Value0)
{
	xsd__int_Array RetArray = {NULL, 0};
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return RetArray;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoIntegerArray");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoIntegerArray", "http://soapinterop.org/");
		applyUserPreferences();
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoIntegerArrayResponse", "http://soapinterop.org/"))
			{
				RetArray = (xsd__int_Array&)m_pCall->getBasicArray(XSD_INT, "return", 0);
			}
		}
		m_pCall->unInitialize();
		return RetArray;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoFloat
 */
float InteropTestPortType::echoFloat(float Value0)
{
	float Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoFloat");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoFloat", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoFloatResponse", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsFloat("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoFloatArray
 */
xsd__float_Array InteropTestPortType::echoFloatArray(xsd__float_Array Value0)
{
	xsd__float_Array RetArray = {NULL, 0};
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return RetArray;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoFloatArray");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoFloatArray", "http://soapinterop.org/");
		applyUserPreferences();
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoFloatArrayResponse", "http://soapinterop.org/"))
			{
				RetArray = (xsd__float_Array&)m_pCall->getBasicArray(XSD_FLOAT, "return", 0);
			}
		}
		m_pCall->unInitialize();
		return RetArray;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoStruct
 */
SOAPStruct* InteropTestPortType::echoStruct(SOAPStruct* Value0)
{
	SOAPStruct* pReturn = NULL;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return pReturn;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoStruct");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoStruct", "http://soapinterop.org/");
		applyUserPreferences();
	m_pCall->addCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", Axis_URI_SOAPStruct);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoStructResponse", "http://soapinterop.org/"))
			{
				pReturn = (SOAPStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct,"return", 0);
		}
		}
		m_pCall->unInitialize();
		return pReturn;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoStructArray
 */
SOAPStruct_Array InteropTestPortType::echoStructArray(SOAPStruct_Array Value0)
{
	SOAPStruct_Array RetArray = {NULL, 0};
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return RetArray;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoStructArray");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoStructArray", "http://soapinterop.org/");
		applyUserPreferences();
	m_pCall->addCmplxArrayParameter((Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "inputStructArray", Axis_URI_SOAPStruct);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoStructArrayResponse", "http://soapinterop.org/"))
			{
				RetArray = (SOAPStruct_Array&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "return", Axis_URI_SOAPStruct);
			}
		}
		m_pCall->unInitialize();
		return RetArray;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoVoid
 */
void InteropTestPortType::echoVoid()
{
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return ;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoVoid");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoVoid", "http://soapinterop.org/");
		applyUserPreferences();
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoVoidResponse", "http://soapinterop.org/"))
			{
			/*not successful*/
		}
		}
		m_pCall->unInitialize();
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoBase64
 */
xsd__base64Binary InteropTestPortType::echoBase64(xsd__base64Binary Value0)
{
	xsd__base64Binary Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoBase64");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoBase64", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputBase64", XSD_BASE64BINARY);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoBase64Response", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsBase64Binary("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoDate
 */
xsd__dateTime InteropTestPortType::echoDate(xsd__dateTime Value0)
{
	xsd__dateTime Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoDate");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoDate", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputDate", XSD_DATETIME);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoDateResponse", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsDateTime("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoHexBinary
 */
xsd__hexBinary InteropTestPortType::echoHexBinary(xsd__hexBinary Value0)
{
	xsd__hexBinary Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoHexBinary");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoHexBinary", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoHexBinaryResponse", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsHexBinary("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoDecimal
 */
xsd__decimal InteropTestPortType::echoDecimal(xsd__decimal Value0)
{
	xsd__decimal Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoDecimal");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoDecimal", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputDecimal", XSD_DECIMAL);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoDecimalResponse", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsDecimal("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}


/*
 * This method wrap the service method echoBoolean
 */
xsd__boolean InteropTestPortType::echoBoolean(xsd__boolean Value0)
{
	xsd__boolean Ret;
	char* cFaultcode;
	char* cFaultstring;
	char* cFaultactor;
	char* cFaultdetail;
	try
	{
		if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) 
			return Ret;
		m_pCall->setTransportProperty(SOAPACTION_HEADER , "InteropBase#echoBoolean");
		m_pCall->setSOAPVersion(SOAP_VER_1_1);
		m_pCall->setOperation("echoBoolean", "http://soapinterop.org/");
		applyUserPreferences();
		m_pCall->addParameter((void*)&Value0, "inputBoolean", XSD_BOOLEAN);
		if (AXIS_SUCCESS == m_pCall->invoke())
		{
			if(AXIS_SUCCESS == m_pCall->checkMessage("echoBooleanResponse", "http://soapinterop.org/"))
			{
				Ret = m_pCall->getElementAsBoolean("return", 0);
			}
		}
		m_pCall->unInitialize();
		return Ret;
	}
	catch(AxisException& e)
	{
		if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/InteropBase" ))//Exception handling code goes here
		{
			cFaultcode = m_pCall->getElementAsString("faultcode", 0);
			cFaultstring = m_pCall->getElementAsString("faultstring", 0);
			cFaultactor = m_pCall->getElementAsString("faultactor", 0);
				  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
				  throw AxisException(cFaultdetail);
		}
		else throw;
	}
}

int InteropTestPortType::getStatus()
{
	if ( m_pCall==NULL ) 
		return AXIS_SUCCESS; 
	else 
		return m_pCall->getStatus();
}

int InteropTestPortType::getFaultDetail(char** ppcDetail)
{
	return m_pCall->getFaultDetail(ppcDetail);
}

