/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains definitions of the web service
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
     if (Value1 == 0) throw AxisDivByZeroException();

     if(Value0 < 0 || Value1 < 0) throw AxisOutOfBoundException();

     if(Value0 == 1000) throw AxisNormalDetailException();

     return Value0/Value1;
        
}