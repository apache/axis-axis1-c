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
 * @author Thushantha De Alwis (thushantha@beyondm.net  ravi@opensource.lk)
 *
 */

#include "axis/test_cases/cppunit/common/AxisTraceTestCase.h"


AxisTraceTestCase::AxisTraceTestCase()
{

}

AxisTraceTestCase::~AxisTraceTestCase()
{

}

void AxisTraceTestCase::setUp()
{
    pAxisTrace = new AxisTrace();

}

void AxisTraceTestCase::tearDown()
{
    delete pAxisTrace;
    pAxisTrace = NULL;
}


void AxisTraceTestCase::testTraceOne()
{
    int ExpectedInt = 0;

    const char* s1 = "MyTestString";

    int iResult;

    iResult = pAxisTrace->trace(s1);

    CPPUNIT_ASSERT_EQUAL(ExpectedInt,iResult);

}

Test* AxisTraceTestCase::suite()
{
    TestSuite *testSuite = new TestSuite("AxisTraceTestCase");

    testSuite->addTest (new TestCaller <AxisTraceTestCase>
      ("testTraceOne", &AxisTraceTestCase::testTraceOne));

    return testSuite;

}


