/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * MathOps.h: interface for the MathOpsclass.
 *
 */
#if !defined(__MATHOPS_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
#define __MATHOPS_CLIENTSTUB_H__OF_AXIS_INCLUDED_

#include <axis/client/Call.h>
#include "SOAPStructFault.h"
#include <axis/server/AxisException.h>
#include <ctype.h>

class MathOps 
{
private:
	Call* m_pCall;
public:
	MathOps(const char* pchEndpointUri);
public:
	virtual ~MathOps();
public: 
	int div(int Value0,int Value1);
        int getFaultDetail(char** ppcDetail);
};

#endif /* !defined(__MATHOPS_CLIENTSTUB_H__OF_AXIS_INCLUDED_)*/
