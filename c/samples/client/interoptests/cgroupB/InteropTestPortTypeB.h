/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * InteropTestPortTypeB.h: interface for the InteropTestPortTypeBclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPEB_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEB_H__INCLUDED_

#include <axis/client/Call.h>
#include <axis/common/AxisWrapperAPI.h>
#include "SOAPArrayStruct.h"
#include "SOAPStruct.h"
#include "ArrayOffloat.h"
#include "ArrayOfSOAPStruct.h"
#include "ArrayOfint.h"
#include "ArrayOfString2D.h"
#include "SOAPStructStruct.h"
#include "ArrayOfstring.h"


Call* g_pInteropTestPortTypeB;
extern float echoStructAsSimpleTypes(SOAPStruct* Value0);
extern SOAPStruct* echoSimpleTypesAsStruct(float Value0,int Value1,char* Value2);
extern ArrayOfString2D echo2DStringArray(ArrayOfString2D Value0);
extern SOAPStructStruct* echoNestedStruct(SOAPStructStruct* Value0);
extern SOAPArrayStruct* echoNestedArray(SOAPArrayStruct* Value0);


#endif // !defined(__INTEROPTESTPORTTYPEB_H__INCLUDED_)
