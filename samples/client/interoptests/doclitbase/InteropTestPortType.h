/////////////////////////////////////////////////////////////////////////////
// This is the Client Stub Class genarated by the tool WSDL2Ws
// InteropTestPortType.h: interface for the InteropTestPortTypeclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_

#include <axis/client/Stub.h>
#include "SOAPStruct.h"
#include "ArrayOffloat.h"
#include "ArrayOfSOAPStruct.h"
#include "ArrayOfint.h"
#include "ArrayOfstring.h"

class InteropTestPortType 
{
private:
	Call* m_pCall;
public:
	InteropTestPortType(const char* pchEndPointUri);
public:
	virtual ~InteropTestPortType();
public: 
	AxisChar* echoString(AxisChar* Value0);
	ArrayOfstring echoStringArray(ArrayOfstring Value0);
	int echoInteger(int Value0);
	ArrayOfint echoIntegerArray(ArrayOfint Value0);
	float echoFloat(float Value0);
	ArrayOffloat echoFloatArray(ArrayOffloat Value0);
	SOAPStruct* echoStruct(SOAPStruct* Value0);
	ArrayOfSOAPStruct echoStructArray(ArrayOfSOAPStruct Value0);
	void echoVoid();
	xsd__base64Binary echoBase64(xsd__base64Binary Value0);
	xsd__dateTime echoDate(xsd__dateTime Value0);
	xsd__hexBinary echoHexBinary(xsd__hexBinary Value0);
	xsd__decimal echoDecimal(xsd__decimal Value0);
	xsd__boolean echoBoolean(xsd__boolean Value0);
};

#endif // !defined(__INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
