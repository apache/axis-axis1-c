/*
 * This is the Client Stub implementation file genarated by WSDL2Ws tool.
 * InteropTestPortType.cpp: implemtation for the InteropTestPortType.
 *
 */

#include "InteropTestPortType.h"

#include <axis/server/AxisWrapperAPI.h>

//bool CallBase::bInitialized;
//CallFunctions CallBase::ms_VFtable;
extern int Axis_DeSerialize_SOAPStruct(SOAPStruct* param, IWrapperSoapDeSerializer *pDZ);
extern void* Axis_Create_SOAPStruct(SOAPStruct *Obj, bool bArray = false, int nSize=0);
extern void Axis_Delete_SOAPStruct(SOAPStruct* param, bool bArray = false, int nSize=0);
extern int Axis_Serialize_SOAPStruct(SOAPStruct* param, IWrapperSoapSerializer* pSZ, bool bArray = false);
extern int Axis_GetSize_SOAPStruct();

InteropTestPortType::InteropTestPortType(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol)
:Stub(pchEndpointUri, eProtocol)
{
}

InteropTestPortType::~InteropTestPortType()
{
}


/*Methods corresponding to the web service methods*/

/*
 * This method wrap the service methodechoString
 */
xsd__string InteropTestPortType::echoString(xsd__string Value0)
{
    char* cFaultcode;
        char* cFaultstring;
        char* cFaultactor;
        char* cFaultdetail;
	xsd__string Ret;
    try
    {
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoString");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoString", "http://soapinterop.org/");
	setTransportProperties();
	setSOAPHeaders();
	m_pCall->addParameter((void*)&Value0, "inputString", XSD_STRING);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoStringResponse", ""))
		{
			Ret = m_pCall->getElementAsString("return", 0);
		}
	}
        }
        catch(AxisException& e)
        {
                int iExceptionCode = e.getExceptionCode();
                if(AXISC_NODE_VALUE_MISMATCH_EXCEPTION != iExceptionCode)
                {
                    throw;
                }
                else if (AXIS_SUCCESS == m_pCall->checkFault("Fault","http://localhost/axis/MathOps" ))//Exception handling code goes here
                {
                        cFaultcode = m_pCall->getElementAsString("faultcode", 0);
                        cFaultstring = m_pCall->getElementAsString("faultstring", 0);
                        cFaultactor = m_pCall->getElementAsString("faultactor", 0);
                   
                                  cFaultdetail = m_pCall->getElementAsString("faultdetail", 0);
                                  throw AxisException(cFaultdetail);
                      
                }
                else throw;
        }
        catch(...)
        {
            throw;
        }     
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoStringArray
 */
xsd__string_Array InteropTestPortType::echoStringArray(xsd__string_Array Value0)
{
	xsd__string_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoStringArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStringArray", "http://soapinterop.org/");
	setTransportProperties();
	setSOAPHeaders();
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_STRING, "inputStringArray");
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoStringArrayResponse", ""))
		{
			RetArray = (xsd__string_Array&)m_pCall->getBasicArray(XSD_STRING, "return", 0);
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoInteger
 */
int InteropTestPortType::echoInteger(int Value0)
{
	int Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoInteger");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoInteger", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputInteger", XSD_INT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoIntegerResponse", ""))
		{
			Ret = m_pCall->getElementAsInt("return", 0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoIntegerArray
 */
xsd__int_Array InteropTestPortType::echoIntegerArray(xsd__int_Array Value0)
{
	xsd__int_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoIntegerArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoIntegerArray", "http://soapinterop.org/");
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_INT, "inputIntegerArray");
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoIntegerArrayResponse", ""))
		{
			RetArray = (xsd__int_Array&)m_pCall->getBasicArray(XSD_INT, "return", 0);
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoFloat
 */
float InteropTestPortType::echoFloat(float Value0)
{
	float Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoFloat");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoFloat", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputFloat", XSD_FLOAT);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoFloatResponse", ""))
		{
			Ret = m_pCall->getElementAsFloat("return", 0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoFloatArray
 */
xsd__float_Array InteropTestPortType::echoFloatArray(xsd__float_Array Value0)
{
	xsd__float_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoFloatArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoFloatArray", "http://soapinterop.org/");
	m_pCall->addBasicArrayParameter((Axis_Array*)(&Value0), XSD_FLOAT, "inputFloatArray");
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoFloatArrayResponse", ""))
		{
			RetArray = (xsd__float_Array&)m_pCall->getBasicArray(XSD_FLOAT, "return", 0);
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoStruct
 */
SOAPStruct* InteropTestPortType::echoStruct(SOAPStruct* Value0)
{
	SOAPStruct* pReturn = NULL;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return pReturn;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoStruct");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStruct", "http://soapinterop.org/");
	m_pCall->addCmplxParameter(Value0, (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, "inputStruct", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoStructResponse", ""))
		{
			pReturn = (SOAPStruct*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct,"return", 0);
		}
	}
	m_pCall->unInitialize();
	return pReturn;
}


/*
 * This method wrap the service methodechoStructArray
 */
SOAPStruct_Array InteropTestPortType::echoStructArray(SOAPStruct_Array Value0)
{
	SOAPStruct_Array RetArray = {NULL, 0};
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return RetArray;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoStructArray");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoStructArray", "http://soapinterop.org/");
	m_pCall->addCmplxArrayParameter((Axis_Array*)(&Value0), (void*)Axis_Serialize_SOAPStruct, (void*)Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "inputStructArray", Axis_URI_SOAPStruct);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoStructArrayResponse", ""))
		{
			RetArray = (SOAPStruct_Array&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_SOAPStruct, (void*) Axis_Create_SOAPStruct, (void*) Axis_Delete_SOAPStruct, (void*) Axis_GetSize_SOAPStruct, "return", Axis_URI_SOAPStruct);
		}
	}
	m_pCall->unInitialize();
	return RetArray;
}


/*
 * This method wrap the service methodechoVoid
 */
void InteropTestPortType::echoVoid()
{
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return ;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoVoid");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoVoid", "http://soapinterop.org/");
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoVoidResponse", ""))
		{
			/*not successful*/
		}
	}
	m_pCall->unInitialize();
}


/*
 * This method wrap the service methodechoBase64
 */
xsd__base64Binary InteropTestPortType::echoBase64(xsd__base64Binary Value0)
{
	xsd__base64Binary Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoBase64");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoBase64", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputBase64", XSD_BASE64BINARY);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoBase64Response", ""))
		{
			Ret = m_pCall->getElementAsBase64Binary("return", 0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoDate
 */
xsd__dateTime InteropTestPortType::echoDate(xsd__dateTime Value0)
{
	xsd__dateTime Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoDate");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoDate", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputDate", XSD_DATETIME);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoDateResponse", ""))
		{
			Ret = m_pCall->getElementAsDateTime("return", 0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoHexBinary
 */
xsd__hexBinary InteropTestPortType::echoHexBinary(xsd__hexBinary Value0)
{
	xsd__hexBinary Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoHexBinary");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoHexBinary", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputHexBinary", XSD_HEXBINARY);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoHexBinaryResponse", ""))
		{
			Ret = m_pCall->getElementAsHexBinary("return", 0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoDecimal
 */
xsd__decimal InteropTestPortType::echoDecimal(xsd__decimal Value0)
{
	xsd__decimal Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoDecimal");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoDecimal", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputDecimal", XSD_DECIMAL);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoDecimalResponse", ""))
		{
			Ret = m_pCall->getElementAsDecimal("return", 0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}


/*
 * This method wrap the service methodechoBoolean
 */
xsd__boolean InteropTestPortType::echoBoolean(xsd__boolean Value0)
{
	xsd__boolean Ret;
	if (AXIS_SUCCESS != m_pCall->initialize(CPP_RPC_PROVIDER, NORMAL_CHANNEL)) return Ret;
	m_pCall->setTransportProperty(SOAPACTION_HEADER , "base#echoBoolean");
	m_pCall->setSOAPVersion(SOAP_VER_1_1);
	m_pCall->setOperation("echoBoolean", "http://soapinterop.org/");
	m_pCall->addParameter((void*)&Value0, "inputBoolean", XSD_BOOLEAN);
	if (AXIS_SUCCESS == m_pCall->invoke())
	{
		if(AXIS_SUCCESS == m_pCall->checkMessage("echoBooleanResponse", ""))
		{
			Ret = m_pCall->getElementAsBoolean("return", 0);
		}
	}
	m_pCall->unInitialize();
	return Ret;
}

