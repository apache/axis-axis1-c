/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * InteropTestPortTypeB.h: interface for the InteropTestPortTypeBclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPEB_CLIENTSTUB_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEB_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Call.h>
#include "SOAPArrayStruct.h"
#include "SOAPStruct.h"
#include "SOAPStructStruct.h"

class InteropTestPortTypeB 
{
private:
	Call* m_pCall;
public:
	InteropTestPortTypeB();
public:
	virtual ~InteropTestPortTypeB();
public: 
	void echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM float *OutValue0, AXIS_OUT_PARAM int *OutValue1, AXIS_OUT_PARAM xsd__string *OutValue2);
	SOAPStruct* echoSimpleTypesAsStruct(float Value0,int Value1,xsd__string Value2);
	SOAPStructStruct* echoNestedStruct(SOAPStructStruct* Value0);
	SOAPArrayStruct* echoNestedArray(SOAPArrayStruct* Value0);
};

#endif /* !defined(__INTEROPTESTPORTTYPEB_CLIENTSTUB_H__INCLUDED_)*/
