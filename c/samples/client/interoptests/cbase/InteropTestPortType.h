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


Call* g_pInteropTestPortType;
extern xsd__string echoString(xsd__string Value0);
extern xsd__string_Array echoStringArray(xsd__string_Array Value0);
extern int echoInteger(int Value0);
extern xsd__int_Array echoIntegerArray(xsd__int_Array Value0);
extern float echoFloat(float Value0);
extern xsd__float_Array echoFloatArray(xsd__float_Array Value0);
extern SOAPStruct* echoStruct(SOAPStruct* Value0);
extern SOAPStruct_Array echoStructArray(SOAPStruct_Array Value0);
extern void echoVoid();
extern xsd__base64Binary echoBase64(xsd__base64Binary Value0);
extern xsd__dateTime echoDate(xsd__dateTime Value0);
extern xsd__hexBinary echoHexBinary(xsd__hexBinary Value0);
extern xsd__decimal echoDecimal(xsd__decimal Value0);
extern xsd__boolean echoBoolean(xsd__boolean Value0);


#endif // !defined(__INTEROPTESTPORTTYPE_H__INCLUDED_)
