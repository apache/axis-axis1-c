/*
 * This is the C wrapper header file genarated by the WSDL2Ws tool
 *
 */
#if !defined(__INTEROPTESTPORTTYPEBWRAPPER_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPEBWRAPPER_H__OF_AXIS_INCLUDED_

#include <axis/server/IMessageData.h>
#include <axis/server/AxisWrapperAPI.h>

/*implementation of BasicHandler interface*/
int AXISCALL InteropTestPortTypeBWrapper_Invoke(void*p, void* pMsg);
void AXISCALL InteropTestPortTypeBWrapper_OnFault(void*p, void* pMsg);
int AXISCALL InteropTestPortTypeBWrapper_Init(void*p);
int AXISCALL InteropTestPortTypeBWrapper_Fini(void*p);
int AXISCALL InteropTestPortTypeBWrapper_GetType(void*p);
AXIS_BINDING_STYLE AXISCALL InteropTestPortTypeBWrapper_GetBindingStyle(void*p);
/*Methods corresponding to the web service methods*/
int echoStructAsSimpleTypesWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoSimpleTypesAsStructWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoNestedStructWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoNestedArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);


#endif // !defined(__INTEROPTESTPORTTYPEBWRAPPER_H__OF_AXIS_INCLUDED_)
