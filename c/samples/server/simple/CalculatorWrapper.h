/*
 * This is the Service Class genarated by the tool WSDL2Ws
 *		CalculatorWrapper.h: interface for the CalculatorWrapperclass.
 *
 */
#if !defined(__CALCULATORWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __CALCULATORWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "Calculator.h"
#include <axis/server/WrapperClassHandler.h>
#include <axis/server/IMessageData.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisWrapperAPI.h>

class CalculatorWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	Calculator *pWs;
public:
	CalculatorWrapper();
public:
	virtual ~CalculatorWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL Invoke(void* pMsg);
	void AXISCALL OnFault(void* pMsg);
	int AXISCALL Init();
	int AXISCALL Fini();
	AXIS_BINDING_STYLE AXISCALL GetBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int add(void* pMsg);
	int sub(void* pMsg);
	int mul(void* pMsg);
	int div(void* pMsg);
};

#endif /* !defined(__CALCULATORWRAPPER_SERVERWRAPPER_H__INCLUDED_)*/
