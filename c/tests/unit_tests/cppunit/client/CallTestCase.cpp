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
 */

/*  allTestCase.cpp: implementation of the CallTestCase class. */


#include "axis/test_cases/cppunit/client/CallTestCase.h"


CallTestCase::CallTestCase()
{

}

CallTestCase::~CallTestCase()
{

}

void CallTestCase::setUp()
{
    pCall = new Call();
/*    pSoap = new SoapDeSerializer(); */


}

void CallTestCase::tearDown()
{
    delete pCall;
    pCall = NULL;

}


Test* CallTestCase::suite()
{
    TestSuite* testSuite = new TestSuite("CallTestCase");

    testSuite->addTest (new TestCaller <CallTestCase>
      ("testGetElementAsInt", &CallTestCase::testGetElementAsInt));

    return testSuite;

}

void CallTestCase::testGetElementAsInt()
{
    int ExpectedInt = 10;
 
    const AxisChar* myString ="TestString";
    const AxisChar* myString1 ="Test";


    int iResult = pCall->GetElementAsInt(myString, myString1);


    CPPUNIT_ASSERT_EQUAL(ExpectedInt, iResult);
}
