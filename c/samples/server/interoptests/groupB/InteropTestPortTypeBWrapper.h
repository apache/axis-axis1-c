/////////////////////////////////////////////////////////////////////////////
// This is the Service Class genarated by the tool WSDL2Ws
//		InteropTestPortTypeBWrapper.h: interface for the InteropTestPortTypeBWrapperclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "InteropTestPortTypeB.h"
#include <axis/server/WrapperClassHandler.h>
#include <axis/server/IMessageData.h>
#include <axis/server/GDefine.h>
#include <axis/server/IWrapperSoapDeSerializer.h>
#include <axis/server/IWrapperSoapSerializer.h>

class InteropTestPortTypeBWrapper : public WrapperClassHandler
{
private:// Actual web service object
	InteropTestPortTypeB *pWs;
public:
	InteropTestPortTypeBWrapper();
public:
	virtual ~InteropTestPortTypeBWrapper();
public://implementation of WrapperClassHandler interface
	int AXISCALL Invoke(void* mc);
	void AXISCALL OnFault(void* pMsg);
	int AXISCALL Init();
	int AXISCALL Fini();
	AXIS_BINDING_STYLE AXISCALL GetBindingStyle(){return RPC_ENCODED;};
private://Methods corresponding to the web service methods
	int echoStructAsSimpleTypes(IMessageData* mc);
	int echoSimpleTypesAsStruct(IMessageData* mc);
	int echo2DStringArray(IMessageData* mc);
	int echoNestedStruct(IMessageData* mc);
	int echoNestedArray(IMessageData* mc);
};

#endif // !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__INCLUDED_)
