/*
 * This is the C wrapper header file genarated by the WSDL2Ws tool
 *
 */
#if !defined(__INTEROPTESTPORTTYPEWRAPPER_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEWRAPPER_H__INCLUDED_

#include <axis/common/IMessageData.h>
#include <axis/common/AxisWrapperAPI.h>

/*implementation of BasicHandler interface*/
int AXISCALL Invoke(void*p, IMessageData* mc);
void AXISCALL OnFault(void*p, IMessageData* mc);
int AXISCALL Init(void*p);
int AXISCALL Fini(void*p);
AXIS_BINDING_STYLE AXISCALL GetBindingStyle(void*p);
/*Methods corresponding to the web service methods*/
int echoStringWrapped(IMessageData* mc);
int echoStringArrayWrapped(IMessageData* mc);
int echoIntegerWrapped(IMessageData* mc);
int echoIntegerArrayWrapped(IMessageData* mc);
int echoFloatWrapped(IMessageData* mc);
int echoFloatArrayWrapped(IMessageData* mc);
int echoStructWrapped(IMessageData* mc);
int echoStructArrayWrapped(IMessageData* mc);
int echoVoidWrapped(IMessageData* mc);
int echoBase64Wrapped(IMessageData* mc);
int echoDateWrapped(IMessageData* mc);
int echoHexBinaryWrapped(IMessageData* mc);
int echoDecimalWrapped(IMessageData* mc);
int echoBooleanWrapped(IMessageData* mc);


#endif // !defined(__INTEROPTESTPORTTYPEWRAPPER_H__INCLUDED_)
