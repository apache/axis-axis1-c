/*
 * This is the Service Class genarated by the tool WSDL2Ws
 *		InteropTestPortTypeBWrapper.h: interface for the InteropTestPortTypeBWrapperclass.
 *
 */
#if !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_

#include "InteropTestPortTypeB.h"
#include <axis/server/WrapperClassHandler.h>
#include <axis/server/IMessageData.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisWrapperAPI.h>

class InteropTestPortTypeBWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	InteropTestPortTypeB *pWs;
public:
	InteropTestPortTypeBWrapper();
public:
	virtual ~InteropTestPortTypeBWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL invoke(void* pMsg);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int echoStructAsSimpleTypes(void* pMsg);
	int echoSimpleTypesAsStruct(void* pMsg);
	int echoNestedStruct(void* pMsg);
	int echoNestedArray(void* pMsg);
};

#endif /* !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)*/
