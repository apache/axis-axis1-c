/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * MathOps.h: interface for the MathOpsclass.
 *
 */
#if !defined(__MATHOPS_SERVERSKELETON_H__INCLUDED_)
#define __MATHOPS_SERVERSKELETON_H__INCLUDED_

#include <axis/server/AxisUserAPI.hpp>

#include "DivByZeroStruct.h"
#include "SpecialDetailStruct.h"
#include "OutOfBoundStruct.h"


class MathOps 
{
	public:
		MathOps();
	public:
		virtual ~MathOps();
	public: 
		int div(int Value0,int Value1);
};

#endif /* !defined(__MATHOPS_SERVERSKELETON_H__INCLUDED_)*/
