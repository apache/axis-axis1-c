/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * Calculator.h: interface for the Calculatorclass.
 *
 */
#if !defined(__CALCULATOR_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
#define __CALCULATOR_CLIENTSTUB_H__OF_AXIS_INCLUDED_

#include <axis/client/Stub.h>
#include <ctype.h>

class Calculator 
{
private:
	Call* m_pCall;
public:
	Calculator(const char* pchEndpointUri);
public:
	virtual ~Calculator();
public: 
	int add(int Value0,int Value1);
	int sub(int Value0,int Value1);
	int mul(int Value0,int Value1);
	int div(int Value0,int Value1);
        int getFaultDetail(char** ppcDetail);
};

#endif /* !defined(__CALCULATOR_CLIENTSTUB_H__OF_AXIS_INCLUDED_)*/
