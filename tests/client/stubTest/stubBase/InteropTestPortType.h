/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * InteropTestPortType.h: interface for the InteropTestPortTypeclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_

#include <axis/client/Stub.hpp>
#include "SOAPStruct_Array.h"
#include "SOAPStruct.h"
#include "AxisClientException.h"

class InteropTestPortType :public Stub 
{
public:
	InteropTestPortType(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol=APTHTTP);
	virtual ~InteropTestPortType();
public: 
	xsd__string echoString(xsd__string Value0);
	xsd__string_Array echoStringArray(xsd__string_Array Value0);
	int echoInteger(int Value0);
	xsd__int_Array echoIntegerArray(xsd__int_Array Value0);
	float echoFloat(float Value0);
	xsd__float_Array echoFloatArray(xsd__float_Array Value0);
	SOAPStruct* echoStruct(SOAPStruct* Value0);
	SOAPStruct_Array echoStructArray(SOAPStruct_Array Value0);
	void echoVoid();
	xsd__base64Binary echoBase64(xsd__base64Binary Value0);
	xsd__dateTime echoDate(xsd__dateTime Value0);
	xsd__hexBinary echoHexBinary(xsd__hexBinary Value0);
	xsd__decimal echoDecimal(xsd__decimal Value0);
	xsd__boolean echoBoolean(xsd__boolean Value0);
};

#endif /* !defined(__INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_)*/
