/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Thushantha De Alwis (thushantha@beyondm.net  ravi@opensource.lk)
 *
 */
//////////////////////////////////////////////////////////////////////




// BasicTypeSerializerTest.cpp: implementation of the BasicTypeSerializerTest class.
//
//////////////////////////////////////////////////////////////////////

#include "axis/test_cases/cppunit/common/BasicTypeSerializerTestCase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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


//////////////// To test Serialize() Method ////////////////////////

/*void BasicTypeSerializerTest::testSerialize()
{
	const char* ExpectedmyChar  = "<mystring xsi:type=\"xsd:string\">mystring</mystring>";
	const char* myChar = "mystring";
	const char*  myCharRes;
	
	myCharRes = pBasicTypeSerializer->serialize(myChar, 1 , XSD_STRING);

	string sActual = myCharRes;
	string sExpectedResult = ExpectedmyChar;
	
	CPPUNIT_ASSERT_EQUAL(sExpectedResult,sActual);	

}*/


//////////////// The BasicTypeSerializer Suite()  ////////////////////////

Test* BasicTypeSerializerTest::suite()
{
	TestSuite *testSuite = new TestSuite("BasicTypeSerializerTest");

	testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testBasicTypeStr", &BasicTypeSerializerTest::testBasicTypeStr));

	testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testEncodeToBase64Binary", &BasicTypeSerializerTest::testEncodeToBase64Binary));

	testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testEncodeToHexBinary", &BasicTypeSerializerTest::testEncodeToHexBinary));

	testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testGetEntityReference", &BasicTypeSerializerTest::testGetEntityReference));
	
	testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeAsAttribute", &BasicTypeSerializerTest::testSerializeAsAttribute));
	
	testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      ("testSerializeAsElement", &BasicTypeSerializerTest::testSerializeAsElement));


	//testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
     // ("testSerializeLong", &BasicTypeSerializerTest::testSerializeLong));

	//testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      //("testSerializeUnsignedLong", &BasicTypeSerializerTest::testSerializeUnsignedLong));

	
	//testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      //("testSerializeFloat", &BasicTypeSerializerTest::testSerializeFloat));

	//testSuite->addTest (new TestCaller <BasicTypeSerializerTest>
      //("testSerializeDouble", &BasicTypeSerializerTest::testSerializeDouble));


	return testSuite;
}



void BasicTypeSerializerTest::testBasicTypeStr()
{
	const AxisChar* ExpectedString = "string";
	const AxisChar* sResult;

	//xsd__hexBinary t;

	sResult = pBasicTypeSerializer->BasicTypeStr(XSD_STRING);

	string ExpectedString1 = ExpectedString;
	string ResultString    = sResult;

	CPPUNIT_ASSERT_EQUAL(ExpectedString1, ResultString);

}

void BasicTypeSerializerTest::testEncodeToBase64Binary()
{
	
  xsd__base64Binary*  objXSD ;
 
  const AxisChar* cResult;

	
	//objXSD->__ptr = (xsd__unsignedByte*)200;
    //objXSD->__size= 14;

	cResult = pBasicTypeSerializer->EncodeToBase64Binary(objXSD);

	string sResult = cResult;
	string ExpectedString = "";

	CPPUNIT_ASSERT_EQUAL(sResult, ExpectedString);

}



void BasicTypeSerializerTest::testEncodeToHexBinary()
{
	xsd__hexBinary* objHexBinary;

	const AxisChar* cResult;

	
	//objXSD->__ptr = (xsd__unsignedByte*)200;
    //objXSD->__size= 14;

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

	
	cResult = pBasicTypeSerializer->SerializeAsAttribute(pPtr,pPrefix, pVal, XSD_BOOLEAN);

	string ExpectedString=" XSD:TestBool=\"true\"";
	string sResult = cResult;
	//string ExpectedString = cResult;

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

