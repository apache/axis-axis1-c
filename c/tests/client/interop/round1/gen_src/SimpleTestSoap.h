/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * SimpleTestSoap.h: interface for the SimpleTestSoapclass.
 *
 */
#if !defined(__SIMPLETESTSOAP_CLIENTSTUB_H__INCLUDED_)
#define __SIMPLETESTSOAP_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Stub.h>
#include "SOAPStruct_Array.h"
#include "SOAPStruct.h"

class SimpleTestSoap :public Stub
{
public:
	SimpleTestSoap(const char* pcEndpointUri);
public:
	virtual ~SimpleTestSoap();
public: 
	void echoVoid();
	int echoInteger(int Value0);
	float echoFloat(float Value0);
	xsd__string echoString(xsd__string Value0);
	xsd__base64Binary echoBase64(xsd__base64Binary Value0);
	xsd__dateTime echoDate(xsd__dateTime Value0);
	SOAPStruct* echoStruct(SOAPStruct* Value0);
	xsd__int_Array echoIntegerArray(xsd__int_Array Value0);
	xsd__float_Array echoFloatArray(xsd__float_Array Value0);
	xsd__string_Array echoStringArray(xsd__string_Array Value0);
	SOAPStruct_Array echoStructArray(SOAPStruct_Array Value0);
	xsd__decimal echoDecimal(xsd__decimal Value0);
	xsd__boolean echoBoolean(xsd__boolean Value0);
	xsd__hexBinary echoHexBinary(xsd__hexBinary Value0);
	int getStatus();
};

#endif /* !defined(__SIMPLETESTSOAP_CLIENTSTUB_H__INCLUDED_)*/
