// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

#include "ElementFormDefaultTest.hpp"
#include "CommonClientTestCode.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber(const char* p);
void testDeepCopyUsingDefault();
void testDeepCopyUsingFlag();
void testShallowCopy();

int main(int argc, char* argv[])
{
    signal(SIGILL, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGSEGV, sig_handler);
    //signal(SIGQUIT, sig_handler);
    //signal(SIGBUS, sig_handler);
    signal(SIGFPE, sig_handler);
	
	testDeepCopyUsingDefault();
	testDeepCopyUsingFlag();
	testShallowCopy();

       
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
 
  return 0;
}

void PrintUsage()
{
  printf("Usage :\n Calculator <url>\n\n");
 exit(1);
}

bool IsNumber(const char* p)
{
    for (unsigned int x=0; x < strlen(p); x++)
 {
     if (!isdigit(p[x])) return false;
 }
 return true;
}

void sig_handler(int sig) {
    signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
 exit(1);
}

void testDeepCopyUsingDefault()
{
	ElementFormDefaultIsQualified * complexType = new ElementFormDefaultIsQualified();
	// Test for string based types
	complexType->setaStringType("Hello!");
	complexType->setaStringType("Goodbye!");
	xsd__string aStringType = new char[9];
	strcpy(aStringType, "Welcome!");
	complexType->setaStringType(aStringType);
	delete [] aStringType;
	complexType->setaStringType(NULL);
	

	// Test for nillable numeric types
	xsd__integer * aNillableIntegerType = new xsd__integer(123);
	complexType->setaNillableIntegerType(aNillableIntegerType);
	delete aNillableIntegerType;
	xsd__integer * aSecondNillableIntegerType = new xsd__integer(456);
	complexType->setaNillableIntegerType(aSecondNillableIntegerType);
	delete aSecondNillableIntegerType;
	complexType->setaNillableIntegerType(NULL);

	// Test for optional numeric types
	xsd__integer * anOptionalIntegerType = new xsd__integer(789);
	complexType->setanOptionalIntegerType(anOptionalIntegerType);
	delete anOptionalIntegerType;
	xsd__integer * aSecondOptionalIntegerType = new xsd__integer(54321);
	complexType->setanOptionalIntegerType(aSecondOptionalIntegerType);
	delete aSecondOptionalIntegerType;
	complexType->setanOptionalIntegerType(NULL);

	// Test correct copying (so repopulate values)
	complexType->setaStringType("Welcome!");
	xsd__integer * optionalInteger = new xsd__integer(9876);
	complexType->setanOptionalIntegerType(optionalInteger);
	delete optionalInteger;
	xsd__integer * nillableInteger = new xsd__integer(321);
	complexType->setaNillableIntegerType(nillableInteger);
	delete nillableInteger;
	ElementFormDefaultIsQualified * aSecondComplexType = new ElementFormDefaultIsQualified(*complexType);

	delete complexType;
	delete aSecondComplexType;
}

void testDeepCopyUsingFlag()
{
	ElementFormDefaultIsQualified * complexType = new ElementFormDefaultIsQualified();
	// Test for string based types
	complexType->setaStringType("Hello!", true);
	complexType->setaStringType("Goodbye!", true);
	xsd__string aStringType = new char[9];
	strcpy(aStringType, "Welcome!");
	complexType->setaStringType(aStringType, true);
	delete [] aStringType;
	complexType->setaStringType(NULL, true);
	

	// Test for nillable numeric types
	xsd__integer * aNillableIntegerType = new xsd__integer(123);
	complexType->setaNillableIntegerType(aNillableIntegerType, true);
	delete aNillableIntegerType;
	xsd__integer * aSecondNillableIntegerType = new xsd__integer(456);
	complexType->setaNillableIntegerType(aSecondNillableIntegerType, true);
	delete aSecondNillableIntegerType;
	complexType->setaNillableIntegerType(NULL, true);

	// Test for optional numeric types
	xsd__integer * anOptionalIntegerType = new xsd__integer(789);
	complexType->setanOptionalIntegerType(anOptionalIntegerType, true);
	delete anOptionalIntegerType;
	xsd__integer * aSecondOptionalIntegerType = new xsd__integer(54321);
	complexType->setanOptionalIntegerType(aSecondOptionalIntegerType, true);
	delete aSecondOptionalIntegerType;
	complexType->setanOptionalIntegerType(NULL, true);

	// Test correct copying (so repopulate values)
	complexType->setaStringType("Welcome!", true);
	xsd__integer * optionalInteger = new xsd__integer(9876);
	complexType->setanOptionalIntegerType(optionalInteger, true);
	delete optionalInteger;
	xsd__integer * nillableInteger = new xsd__integer(321);
	complexType->setaNillableIntegerType(nillableInteger, true);
	delete nillableInteger;
	ElementFormDefaultIsQualified * aSecondComplexType = new ElementFormDefaultIsQualified(*complexType);

	delete complexType;
	delete aSecondComplexType;
}


void testShallowCopy()
{
	ElementFormDefaultIsQualified * complexType = new ElementFormDefaultIsQualified();

	// Test for string based types
	complexType->setaStringType("Hello!", false);
	complexType->setaStringType("Goodbye!", false);
	xsd__string aStringType = new char[9];
	strcpy(aStringType, "Welcome!");
	complexType->setaStringType(aStringType, false);
	complexType->setaStringType(NULL, false);

	// Test for nillable numeric types
	xsd__integer * aNillableIntegerType = new xsd__integer(123);
	complexType->setaNillableIntegerType(aNillableIntegerType, false);
	xsd__integer * aSecondNillableIntegerType = new xsd__integer(456);
	complexType->setaNillableIntegerType(aSecondNillableIntegerType, false);
	complexType->setaNillableIntegerType(NULL, false);

	// Test for optional numeric types
	xsd__integer * anOptionalIntegerType = new xsd__integer(789);
	complexType->setanOptionalIntegerType(anOptionalIntegerType, false);
	xsd__integer * aSecondOptionalIntegerType = new xsd__integer(54321);
	complexType->setanOptionalIntegerType(aSecondOptionalIntegerType, false);
	complexType->setanOptionalIntegerType(NULL, false);
	
	// Test correct copying (so repopulate values)
	complexType->setaStringType("Welcome!", false);
	xsd__integer * optionalInteger = new xsd__integer(9876);
	complexType->setanOptionalIntegerType(optionalInteger, false);
	xsd__integer * nillableInteger = new xsd__integer(321);
	complexType->setaNillableIntegerType(nillableInteger, false);
	ElementFormDefaultIsQualified * aSecondComplexType = new ElementFormDefaultIsQualified(*complexType);

	delete [] aStringType;
	delete aNillableIntegerType;
	delete aSecondNillableIntegerType;
	delete anOptionalIntegerType;
	delete aSecondOptionalIntegerType;
	delete optionalInteger;
	delete nillableInteger;
	delete complexType;
	delete aSecondComplexType;
}