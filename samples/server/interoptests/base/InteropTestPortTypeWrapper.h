/*
 * This is the Service Class genarated by the tool WSDL2Ws
 *		InteropTestPortTypeWrapper.h: interface for the InteropTestPortTypeWrapperclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "InteropTestPortType.h"
#include <axis/server/WrapperClassHandler.h>
#include <axis/server/IMessageData.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisWrapperAPI.h>

class InteropTestPortTypeWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	InteropTestPortType *pWs;
public:
	InteropTestPortTypeWrapper();
public:
	virtual ~InteropTestPortTypeWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL Invoke(void* pMsg);
	void AXISCALL OnFault(void* pMsg);
	int AXISCALL Init();
	int AXISCALL Fini();
	AXIS_BINDING_STYLE AXISCALL GetBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int echoString(void* pMsg);
	int echoStringArray(void* pMsg);
	int echoInteger(void* pMsg);
	int echoIntegerArray(void* pMsg);
	int echoFloat(void* pMsg);
	int echoFloatArray(void* pMsg);
	int echoStruct(void* pMsg);
	int echoStructArray(void* pMsg);
	int echoVoid(void* pMsg);
	int echoBase64(void* pMsg);
	int echoDate(void* pMsg);
	int echoHexBinary(void* pMsg);
	int echoDecimal(void* pMsg);
	int echoBoolean(void* pMsg);
};

#endif /* !defined(__INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_)*/
