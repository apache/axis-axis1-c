/*
 * This is the Service Class genarated by the tool WSDL2Ws
 *		MathOpsWrapper.h: interface for the MathOpsWrapperclass.
 *
 */
#if !defined(__MATHOPSWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __MATHOPSWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "MathOps.h"
#include <axis/server/WrapperClassHandler.h>
#include <axis/server/IMessageData.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisWrapperAPI.h>
#include "AxisDivByZeroException.h"

class MathOpsWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	MathOps *pWs;
public:
	MathOpsWrapper();
public:
	virtual ~MathOpsWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL invoke(void* pMsg);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int div(void* pMsg);
};

#endif /* !defined(__MATHOPSWRAPPER_SERVERWRAPPER_H__INCLUDED_)*/
