/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * InteropTestPortType.h: interface for the InteropTestPortTypeclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPE_H__INCLUDED_)
#define __INTEROPTESTPORTTYPE_H__INCLUDED_

#include <axis/client/Call.h>
#include <axis/common/AxisWrapperAPI.h>
#include "SOAPStruct.h"
#include "ArrayOffloat.h"
#include "ArrayOfSOAPStruct.h"
#include "ArrayOfint.h"
#include "ArrayOfstring.h"


Call* g_pInteropTestPortType;
extern char* echoString(char* Value0);
extern ArrayOfstring echoStringArray(ArrayOfstring Value0);
extern int echoInteger(int Value0);
extern ArrayOfint echoIntegerArray(ArrayOfint Value0);
extern float echoFloat(float Value0);
extern ArrayOffloat echoFloatArray(ArrayOffloat Value0);
extern SOAPStruct* echoStruct(SOAPStruct* Value0);
extern ArrayOfSOAPStruct echoStructArray(ArrayOfSOAPStruct Value0);
extern void echoVoid();
extern Axis_Base64Binary echoBase64(Axis_Base64Binary Value0);
extern Axis_DateTime echoDate(Axis_DateTime Value0);
extern Axis_HexBinary echoHexBinary(Axis_HexBinary Value0);
extern Axis_Decimal echoDecimal(Axis_Decimal Value0);
extern Axis_Boolean echoBoolean(Axis_Boolean Value0);


#endif // !defined(__INTEROPTESTPORTTYPE_H__INCLUDED_)
