/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * InteropTestPortType.h: interface for the InteropTestPortTypeclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPE_H__INCLUDED_)
#define __INTEROPTESTPORTTYPE_H__INCLUDED_

#include <axis/client/Call.h>
#include <axis/common/AxisWrapperAPI.h>
#include "SOAPStruct_Array.h"
#include "SOAPStruct.h"

extern void* get_InteropBase_stub();
extern void destroy_InteropBase_stub(void* p);

extern xsd__string echoString(void* pStub, xsd__string Value0);
extern xsd__string_Array echoStringArray(void* pStub, xsd__string_Array Value0);
extern int echoInteger(void* pStub, int Value0);
extern xsd__int_Array echoIntegerArray(void* pStub, xsd__int_Array Value0);
extern float echoFloat(void* pStub, float Value0);
extern xsd__float_Array echoFloatArray(void* pStub, xsd__float_Array Value0);
extern SOAPStruct* echoStruct(void* pStub, SOAPStruct* Value0);
extern SOAPStruct_Array echoStructArray(void* pStub, SOAPStruct_Array Value0);
extern void echoVoid(void* pStub);
extern xsd__base64Binary echoBase64(void* pStub, xsd__base64Binary Value0);
extern xsd__dateTime echoDate(void* pStub, xsd__dateTime Value0);
extern xsd__hexBinary echoHexBinary(void* pStub, xsd__hexBinary Value0);
extern xsd__decimal echoDecimal(void* pStub, xsd__decimal Value0);
extern xsd__boolean echoBoolean(void* pStub, xsd__boolean Value0);


#endif // !defined(__INTEROPTESTPORTTYPE_H__INCLUDED_)
