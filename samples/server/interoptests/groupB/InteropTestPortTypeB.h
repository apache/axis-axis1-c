/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * InteropTestPortTypeB.h: interface for the InteropTestPortTypeBclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPEB_SERVERSKELETON_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEB_SERVERSKELETON_H__INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include "AxisServiceException.h" 

#include "SOAPArrayStruct.h"
#include "SOAPStruct.h"
#include "SOAPStructStruct.h"

class InteropTestPortTypeB 
{
	public:
		InteropTestPortTypeB();
	public:
		virtual ~InteropTestPortTypeB();
	public: 
		void onFault();
		void init();
		void fini();
		void echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM xsd__string *OutValue0, AXIS_OUT_PARAM int *OutValue1, AXIS_OUT_PARAM float *OutValue2);
		SOAPStruct* echoSimpleTypesAsStruct(xsd__string Value0,int Value1,float Value2);
		SOAPStructStruct* echoNestedStruct(SOAPStructStruct* Value0);
		SOAPArrayStruct* echoNestedArray(SOAPArrayStruct* Value0);
};

#endif /* !defined(__INTEROPTESTPORTTYPEB_SERVERSKELETON_H__INCLUDED_)*/
