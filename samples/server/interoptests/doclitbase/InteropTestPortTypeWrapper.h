/////////////////////////////////////////////////////////////////////////////
// This is the Service Class genarated by the tool WSDL2Ws
//		InteropTestPortTypeWrapper.h: interface for the InteropTestPortTypeWrapperclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_

#include "InteropTestPortType.h"
#include <axis/server/WrapperClassHandler.hpp>
#include <axis/server/IMessageData.hpp>
#include <axis/server/GDefine.hpp>
#include <axis/server/IWrapperSoapDeSerializer.hpp>
#include <axis/server/IWrapperSoapSerializer.hpp>

AXIS_CPP_NAMESPACE_USE

class InteropTestPortTypeWrapper : public WrapperClassHandler
{
private:// Actual web service object
	InteropTestPortType *pWs;
public:
	InteropTestPortTypeWrapper();
public:
	virtual ~InteropTestPortTypeWrapper();
public://implementation of WrapperClassHandler interface
	int AXISCALL invoke(void* mc);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return DOC_LITERAL;};
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

#endif // !defined(__INTEROPTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
