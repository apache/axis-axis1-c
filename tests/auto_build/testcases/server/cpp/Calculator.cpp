// Copyright 2003-2006 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*
 *This is the Service implementation CPP file genarated by theWSDL2Ws.
 *		Calculator.cpp: implemtation for the Calculator.
 *
 */
#include "Calculator.hpp"

class CalculatorException : public std::exception
{
public:
	CalculatorException(const char *errorMessage)
	{
		m_ErrorMessage = errorMessage;
	};

	~CalculatorException() throw() {}

	virtual const char *what() throw()
	{
		return m_ErrorMessage.c_str();
	}

private:
	string m_ErrorMessage;
};

void Calculator::onFault(){}

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
	if (Value1 == 0)
	{
// This has been done to fit the existing JAVA implementations!
		throw CalculatorException( "java.lang.ArithmeticException: / by zero");
	}

	return Value0 / Value1;
}

