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


#include "axis/test_cases/cppunit/common/TypeMappingTestCase.h"


TypeMappingTestCase::TypeMappingTestCase()
{

}

TypeMappingTestCase::~TypeMappingTestCase()
{

}

void TypeMappingTestCase::setUp()
{
    pTypeMapping = new TypeMapping();

}

void TypeMappingTestCase::tearDown()
{
    delete pTypeMapping;
    pTypeMapping = NULL;
}




Test* TypeMappingTestCase::suite()
{
    TestSuite *testSuite = new TestSuite("TypeMappingTestCase");

    testSuite->addTest (new TestCaller <TypeMappingTestCase>
      ("testMap", &TypeMappingTestCase::testMap));


    return testSuite;


}

void TypeMappingTestCase::testMap()
{
    XSDTYPE ExpectedType=XSD_UNKNOWN;
    const AxisXMLCh* myChar = "TestString";


    XSDTYPE xResult;

    xResult = pTypeMapping->Map(myChar);



    int x =  ExpectedType;
    int y =  xResult;

    CPPUNIT_ASSERT_EQUAL(x,y);




}
