/*
 *This is the Service implementation CPP file genarated by theWSDL2Ws.
 *		MathOps.cpp: implemtation for the MathOps.
 *
 */
#include "MathOps.h"


MathOps::MathOps()
{
}

MathOps::~MathOps()
{
}

int MathOps::div(int Value0, int Value1) throw(AxisDivByZeroException)
{
    if (Value1 == 0) throw AxisDivByZeroException();
    return Value0/Value1;
}
