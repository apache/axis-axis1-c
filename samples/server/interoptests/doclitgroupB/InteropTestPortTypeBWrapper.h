/////////////////////////////////////////////////////////////////////////////
// This is the Service Class genarated by the tool WSDL2Ws
//		InteropTestPortTypeBWrapper.h: interface for the InteropTestPortTypeBWrapperclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_

#include "InteropTestPortTypeB.h"
#include <axis/server/WrapperClassHandler.hpp>
#include <axis/IMessageData.hpp>
#include <axis/GDefine.hpp>
#include <axis/IWrapperSoapDeSerializer.hpp>
#include <axis/IWrapperSoapSerializer.hpp>

AXIS_CPP_NAMESPACE_USE

class InteropTestPortTypeBWrapper : public WrapperClassHandler
{
private:// Actual web service object
	InteropTestPortTypeB *pWs;
public:
	InteropTestPortTypeBWrapper();
public:
	virtual ~InteropTestPortTypeBWrapper();
public://implementation of WrapperClassHandler interface
	int AXISCALL invoke(void* mc);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return DOC_LITERAL;};
private://Methods corresponding to the web service methods
	int echoStructAsSimpleTypes(IMessageData* mc);
	int echoSimpleTypesAsStruct(IMessageData* mc);
	int echo2DStringArray(IMessageData* mc);
	int echoNestedStruct(IMessageData* mc);
	int echoNestedArray(IMessageData* mc);
};

#endif // !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
