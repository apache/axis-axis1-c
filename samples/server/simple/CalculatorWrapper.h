/*
 * This is the Service Class genarated by the tool WSDL2Ws
 *		CalculatorWrapper.h: interface for the CalculatorWrapperclass.
 *
 */
#if !defined(__CALCULATORWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
#define __CALCULATORWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_

#include "Calculator.h"
#include <axis/server/WrapperClassHandler.hpp>
#include <axis/IMessageData.hpp>
#include <axis/GDefine.hpp>
#include <axis/AxisWrapperAPI.hpp>
AXIS_CPP_NAMESPACE_USE

class CalculatorWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	Calculator *pWs;
public:
	CalculatorWrapper();
public:
	virtual ~CalculatorWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL invoke(void* pMsg);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int add(void* pMsg);
	int sub(void* pMsg);
	int mul(void* pMsg);
	int div(void* pMsg);
};

#endif /* !defined(__CALCULATORWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)*/
