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
 *
 * @author Thushantha De Alwis (thushantha@beyondm.net  ravi@opensource.lk)
 *
 */

/* ArrayBeanTestCase.cpp: implementation of the ArrayBeanTestCase class. */


#include "axis/test_cases/cppunit/common/ArrayBeanTestCase.h"


ArrayBeanTestCase::ArrayBeanTestCase()
{

}

ArrayBeanTestCase::~ArrayBeanTestCase()
{

}

void ArrayBeanTestCase::setUp()
{
    pArrayBean = new ArrayBean();

}

void ArrayBeanTestCase::tearDown()
{
    delete pArrayBean;
    pArrayBean = NULL;
}


void ArrayBeanTestCase::testGetArraySize()
{
    pArrayBean->m_nSize = 10;

    int ExpectedSize = 10;
    int iResult;

    iResult = pArrayBean->GetArraySize();

    CPPUNIT_ASSERT_EQUAL(ExpectedSize, iResult);




}

Test* ArrayBeanTestCase::suite()
{
    TestSuite* testSuite = new TestSuite("ArrayBeanTestCase");

    testSuite->addTest (new TestCaller <ArrayBeanTestCase>
      ("testGetArraySize", &ArrayBeanTestCase::testGetArraySize));

    return testSuite;

}
