/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * Calculator.hpp: interface for the Calculatorclass.
 *
 */
#if !defined(__CALCULATOR_SERVERSKELETON_H__INCLUDED_)
#define __CALCULATOR_SERVERSKELETON_H__INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include "AxisServiceException.hpp" 


class Calculator 
{
	public:
		Calculator();
	public:
		virtual ~Calculator();
	public: 
		void onFault();
		void init();
		void fini();
		xsd__int add(xsd__int Value0,xsd__int Value1);
		xsd__int sub(xsd__int Value0,xsd__int Value1);
		xsd__int mul(xsd__int Value0,xsd__int Value1);
		xsd__int div(xsd__int Value0,xsd__int Value1);
};

#endif /* !defined(__CALCULATOR_SERVERSKELETON_H__INCLUDED_)*/
