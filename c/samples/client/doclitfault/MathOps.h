/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * MathOps.h: interface for the MathOpsclass.
 *
 */
#if !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)
#define __MATHOPS_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Call.h>
#include "DivByZeroFault.h"
#include "AxisDivByZeroException.h"

class MathOps 
{
private:
	Call* m_pCall;
public:
	MathOps();
public:
	virtual ~MathOps();
public: 
	int div(int Value0,int Value1);
        int getFaultDetail(char** ppcDetail);
	//int getStatus();
};

#endif /* !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)*/
