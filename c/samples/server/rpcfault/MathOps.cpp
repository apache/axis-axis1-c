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

int MathOps::div(int Value0, int Value1)
{
	if (Value1 == 0) return -1; /* :)) */
	return Value0/Value1;
}
