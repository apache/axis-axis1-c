/*
 *This is the Service implementation CPP file genarated by theWSDL2Ws.
 *		Calculator.cpp: implemtation for the Calculator.
 *
 */
#include "Calculator.h"


Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

int Calculator::add(int Value0, int Value1)
{
	return Value0+Value1;
}
int Calculator::sub(int Value0, int Value1)
{
	return Value0-Value1;
}
int Calculator::mul(int Value0, int Value1)
{
	return Value0*Value1;
}
int Calculator::div(int Value0, int Value1)
{
	if (Value1 == 0) return -1; /* :)) */
	return Value0/Value1;
}
