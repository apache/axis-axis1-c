/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * MathOps.h: interface for the MathOps class.
 *
 */
#if !defined(__MATHOPS_SERVERSKELETON_H__OF_AXIS_INCLUDED_)
#define __MATHOPS_SERVERSKELETON_H__OF_AXIS_INCLUDED_

#include <axis/server/AxisUserAPI.h>


class MathOps 
{
	public:
		MathOps();
	public:
		virtual ~MathOps();
	public: 
		int add(int Value0,int Value1);
		int sub(int Value0,int Value1);
		int mul(int Value0,int Value1);
		int div(int Value0,int Value1);
};

#endif /* !defined(__CALCULATOR_SERVERSKELETON_H__OF_AXIS_INCLUDED_)*/
