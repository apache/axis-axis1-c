/////////////////////////////////////////////////////////////////////////////
// This is the Service Class genarated by the tool WSDL2Ws
//		InteropTestPortTypeWrapper.h: interface for the InteropTestPortTypeWrapperclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "InteropTestPortType.h"
#include <axis/common/WrapperClassHandler.h>
#include <axis/common/IMessageData.h>
#include <axis/common/GDefine.h>
#include <axis/common/IWrapperSoapDeSerializer.h>
#include <axis/common/IWrapperSoapSerializer.h>

class InteropTestPortTypeWrapper : public WrapperClassHandler
{
private:// Actual web service object
	InteropTestPortType *pWs;
public:
	InteropTestPortTypeWrapper();
public:
	virtual ~InteropTestPortTypeWrapper();
public://implementation of WrapperClassHandler interface
	int AXISCALL Invoke(IMessageData* mc);
	void AXISCALL OnFault(IMessageData* pMsg);
	int AXISCALL Init();
	int AXISCALL Fini();
	AXIS_BINDING_STYLE AXISCALL GetBindingStyle(){return RPC_ENCODED;};
private://Methods corresponding to the web service methods
	int echoString(IMessageData* mc);
	int echoStringArray(IMessageData* mc);
	int echoInteger(IMessageData* mc);
	int echoIntegerArray(IMessageData* mc);
	int echoFloat(IMessageData* mc);
	int echoFloatArray(IMessageData* mc);
	int echoStruct(IMessageData* mc);
	int echoStructArray(IMessageData* mc);
	int echoVoid(IMessageData* mc);
	int echoBase64(IMessageData* mc);
	int echoDate(IMessageData* mc);
	int echoHexBinary(IMessageData* mc);
	int echoDecimal(IMessageData* mc);
	int echoBoolean(IMessageData* mc);
};

#endif // !defined(__INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_)
