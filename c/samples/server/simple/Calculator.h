/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * Calculator.h: interface for the Calculatorclass.
 *
 */
#if !defined(__CALCULATOR_SERVERSKELETON_H__INCLUDED_)
#define __CALCULATOR_SERVERSKELETON_H__INCLUDED_

#include <axis/server/AxisUserAPI.h>


class Calculator 
{
	public:
		Calculator();
	public:
		virtual ~Calculator();
	public: 
		int add(int Value0,int Value1);
		int sub(int Value0,int Value1);
		int mul(int Value0,int Value1);
		int div(int Value0,int Value1);
};

#endif /* !defined(__CALCULATOR_SERVERSKELETON_H__INCLUDED_)*/
