/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
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
