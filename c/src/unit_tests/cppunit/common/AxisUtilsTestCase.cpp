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

#include "axis/test_cases/cppunit/common/AxisUtilsTestCase.h"


AxisUtilsTestCase::AxisUtilsTestCase()
{

}

AxisUtilsTestCase::~AxisUtilsTestCase()
{

}

Test* AxisUtilsTestCase::suite()
{
    TestSuite *testSuite = new TestSuite("AxisUtilsTestCase");

    testSuite->addTest (new TestCaller <AxisUtilsTestCase>
      ("testClearArray", &AxisUtilsTestCase::testClearArray));

    testSuite->addTest (new TestCaller <AxisUtilsTestCase>
      ("testIsCharacterAvailable", 
      &AxisUtilsTestCase::testIsCharacterAvailable));


    testSuite->addTest (new TestCaller <AxisUtilsTestCase>
      ("isCharacterAvailableref", 
      &AxisUtilsTestCase::isCharacterAvailableref));


    testSuite->addTest (new TestCaller <AxisUtilsTestCase>
      ("testToAxisXMLCh", &AxisUtilsTestCase::testToAxisXMLCh));

    testSuite->addTest (new TestCaller <AxisUtilsTestCase>
      ("testtoLowerCase", &AxisUtilsTestCase::testtoLowerCase));

    /* testSuite->addTest (new TestCaller <AxisUtilsTestCase>
     *  ("testLowerCaseString", &AxisUtilsTestCase::testLowerCaseString));
     */

    return testSuite;    
}

void AxisUtilsTestCase::testClearArray()
{
    int iLenght = 0;
    int iExpectedLenght = 0;
    char testArr[10] = "test line";
    AxisUtils::clearArray(testArr, 10);

    iLenght = strlen(testArr);

    CPPUNIT_ASSERT_EQUAL(iExpectedLenght, iLenght);
}

void AxisUtilsTestCase::testIsCharacterAvailable()
{
    bool bResult = false;
    bool bExpectedResult = true;

    bResult = AxisUtils::isCharacterAvailable("test line", 's');

    CPPUNIT_ASSERT_EQUAL(bExpectedResult, bResult);

    bResult = false;
    bExpectedResult = false;

    bResult = AxisUtils::isCharacterAvailable("test line", 'r');

    CPPUNIT_ASSERT_EQUAL(bExpectedResult, bResult);
}

void AxisUtilsTestCase::isCharacterAvailableref()
{

    bool bResult = false;
    bool bExpectedResult = true;
    string myString = "MyTestString";

    bResult = AxisUtils::isCharacterAvailable(myString, 'S');

    CPPUNIT_ASSERT_EQUAL(bExpectedResult, bResult);
}


void AxisUtilsTestCase::testToAxisXMLCh()
{
    const AxisChar* myString = "MyTestString";
    const AxisChar* cResult;


    cResult = AxisUtils::ToAxisXMLCh(myString);

    string ExpectedString = "MyTestString";
    string actualString = cResult;

    CPPUNIT_ASSERT_EQUAL(ExpectedString, actualString);
}

void AxisUtilsTestCase::testtoLowerCase()
{
    const char* myString = "MyTestString";

    char* ExpectedString = NULL;
    char* sResult;


    sResult = AxisUtils::toLowerCase(myString);

     CPPUNIT_ASSERT_EQUAL(ExpectedString, sResult); 
}





