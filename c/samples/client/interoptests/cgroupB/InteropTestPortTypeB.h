/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * InteropTestPortTypeB.h: interface for the InteropTestPortTypeBclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPEB_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEB_H__INCLUDED_

#include <axis/client/Call.h>
#include <axis/server/AxisWrapperAPI.h>
#include "SOAPArrayStruct.h"
#include "SOAPStruct.h"
#include "SOAPStructStruct.h"

extern void* get_InteropTestPortTypeB_stub(const char* pchEndPointUri);
extern void destroy_InteropTestPortTypeB_stub(void* p);
extern void echoStructAsSimpleTypes(void* pStub, SOAPStruct* Value0, AXIS_OUT_PARAM float *OutValue0, AXIS_OUT_PARAM int *OutValue1, AXIS_OUT_PARAM xsd__string *OutValue2);
extern SOAPStruct* echoSimpleTypesAsStruct(void* pStub, float Value0, int Value1, xsd__string Value2);
extern SOAPStructStruct* echoNestedStruct(void* pStub, SOAPStructStruct* Value0);
extern SOAPArrayStruct* echoNestedArray(void* pStub, SOAPArrayStruct* Value0);


#endif // !defined(__INTEROPTESTPORTTYPEB_H__INCLUDED_)
