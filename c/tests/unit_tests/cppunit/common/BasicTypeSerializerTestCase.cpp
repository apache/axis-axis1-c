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


#include "axis/test_cases/cppunit/common/BasicTypeSerializerTestCase.h"


BasicTypeSerializerTest::BasicTypeSerializerTest()
{

} 

BasicTypeSerializerTest::~BasicTypeSerializerTest()
{

}

void BasicTypeSerializerTest::setUp()
{
    pBasicTypeSerializer = new BasicTypeSerializer();
}


void BasicTypeSerializerTest::tearDown()
{
    delete pBasicTypeSerializer;
    pBasicTypeSerializer= NULL;
}


/*      To test Serialize() Method     */

/*void BasicTypeSerializerTest::testSerialize()
{
    const char* ExpectedmyChar  = "<mystring xsi:type=\"xsd:string\">mystring\
    </mystring>";
    const char* myChar = "mystring";
    const char*  myCharRes;
    
    myCharRes = pBasicTypeSerializer->serialize(myChar, 1 , XSD_STRING);

    string sActual = myCharRes;
    string sExpectedResult = ExpectedmyChar;
    
    CPPUNIT_ASSERT_EQUAL(sExpectedResult,sActual);    

}*/


/*     The BasicTypeSerializer Suite()     */

Test* BasicTypeSerializerTest::suite()
{
    TestSuite *testSuite = new TestSuite("BasicTypeSerializerTest");

    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testBasicTypeStr", &BasicTypeSerializerTest::testBasicTypeStr));

    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testEncodeToBase64Binary", 
      &BasicTypeSerializerTest::testEncodeToBase64Binary));

    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testEncodeToHexBinary", 
      &BasicTypeSerializerTest::testEncodeToHexBinary));

    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testGetEntityReference",
      &BasicTypeSerializerTest::testGetEntityReference));
    
    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeAsAttribute",
      &BasicTypeSerializerTest::testSerializeAsAttribute));
    
    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeAsElement",
      &BasicTypeSerializerTest::testSerializeAsElement));


/*    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeLong", &BasicTypeSerializerTest::testSerializeLong));

    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeUnsignedLong", 
      &BasicTypeSerializerTest::testSerializeUnsignedLong));

    
    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeFloat", &BasicTypeSerializerTest::testSerializeFloat));

    testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeDouble", &BasicTypeSerializerTest::testSerializeDouble));
*/

    return testSuite;
}



void BasicTypeSerializerTest::testBasicTypeStr()
{
    const AxisChar* ExpectedString = "string";
    const AxisChar* sResult;

    /* xsd__hexBinary t; */

    sResult = pBasicTypeSerializer->BasicTypeStr(XSD_STRING);

    string ExpectedString1 = ExpectedString;
    string ResultString    = sResult;

    CPPUNIT_ASSERT_EQUAL(ExpectedString1, ResultString);

}

void BasicTypeSerializerTest::testEncodeToBase64Binary()
{
    
  xsd__base64Binary*  objXSD ;
 
  const AxisChar* cResult;

    
    /* objXSD->__ptr = (xsd__unsignedByte*)200;
     * objXSD->__size= 14;
     */

    cResult = pBasicTypeSerializer->EncodeToBase64Binary(objXSD);

    string sResult = cResult;
    string ExpectedString = "";

    CPPUNIT_ASSERT_EQUAL(sResult, ExpectedString);

}



void BasicTypeSerializerTest::testEncodeToHexBinary()
{
    xsd__hexBinary* objHexBinary;

    const AxisChar* cResult;

    
    /* objXSD->__ptr = (xsd__unsignedByte*)200;
     *  objXSD->__size= 14;
     */

    cResult = pBasicTypeSerializer->EncodeToHexBinary(objHexBinary);

    string sResult = cResult;
    string ExpectedString = "";

    CPPUNIT_ASSERT_EQUAL(sResult, ExpectedString);

}


void BasicTypeSerializerTest::testGetEntityReference()
{
    AxisString sAxisString;
    AxisString sResult;

    sAxisString = "MyTestString";

    sResult = pBasicTypeSerializer->GetEntityReferenced(sAxisString);

    string expectedString = "MyTestString";
    string actualString = sResult;

    CPPUNIT_ASSERT_EQUAL(expectedString, actualString);

}

void BasicTypeSerializerTest::testSerializeAsAttribute()
{
    const AxisChar* cResult;

    const AxisChar* pPtr ="TestBool";
    const AxisChar* pPrefix ="XSD";

    xsd__boolean x = true_;

    void* pVal = &x;

    
    cResult = pBasicTypeSerializer->SerializeAsAttribute(pPtr,pPrefix, pVal, 
        XSD_BOOLEAN);

    string ExpectedString=" XSD:TestBool=\"true\"";
    string sResult = cResult;
    /* string ExpectedString = cResult; */

    CPPUNIT_ASSERT_EQUAL(ExpectedString, sResult);
}


void BasicTypeSerializerTest::testSerializeAsElement()
{
    const AxisChar* cResult;

    const AxisChar* pPtr = "TestBool";
    
    
    xsd__boolean x = true_;
    void* pVal = &x;

    cResult = pBasicTypeSerializer->SerializeAsElement(pPtr,pVal, XSD_BOOLEAN);

    string ExpectedString = "<TestBool>true</TestBool>";
    string sResult = cResult;

    CPPUNIT_ASSERT_EQUAL(ExpectedString, sResult);

}

