/*
 * This is the Service Class genarated by the tool WSDL2Ws
 *		MathOpsWrapper.h: interface for the MathOpsWrapper class.
 *
 */
#if !defined(__MATHOPSWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
#define __MATHOPSWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_

#include "MathOps.h"
#include "SOAPStructFault.h"
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
	int div(void* pMsg) throw(AxisDivByZeroException);
};

#endif /* !defined(__CALCULATORWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)*/
