/*
 * This is the C wrapper header file genarated by the WSDL2Ws tool
 *
 */
#if !defined(__INTEROPTESTPORTTYPEWRAPPER_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEWRAPPER_H__INCLUDED_

#include <axis/server/IMessageData.h>
#include <axis/server/AxisWrapperAPI.h>

/*implementation of BasicHandler interface*/
int AXISCALL InteropTestPortTypeWrapper_Invoke(void*p, void* pMsg);
void AXISCALL InteropTestPortTypeWrapper_OnFault(void*p, void* pMsg);
int AXISCALL InteropTestPortTypeWrapper_Init(void*p);
int AXISCALL InteropTestPortTypeWrapper_Fini(void*p);
int AXISCALL InteropTestPortTypeWrapper_GetType(void*p);
AXIS_BINDING_STYLE AXISCALL InteropTestPortTypeWrapper_GetBindingStyle(void*p);
/*Methods corresponding to the web service methods*/
int echoStringWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoStringArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoIntegerWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoIntegerArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoFloatWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoFloatArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoStructWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoStructArrayWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoVoidWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoBase64Wrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoDateWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoHexBinaryWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoDecimalWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);
int echoBooleanWrapped(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ);


#endif // !defined(__INTEROPTESTPORTTYPEWRAPPER_H__INCLUDED_)
