// AxisSocketUtilsTestCase1.cpp: implementation of the AxisSocketUtilsTestCase class.
//
//////////////////////////////////////////////////////////////////////

#include "axis/test_cases/cppunit/common/AxisSocketUtilsTestCase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AxisSocketUtilsTestCase::AxisSocketUtilsTestCase()
{

}

AxisSocketUtilsTestCase::~AxisSocketUtilsTestCase()
{

}

void AxisSocketUtilsTestCase::setUp()
{
	pAxisSocketUtils = new AxisSocketUtils();
}

void AxisSocketUtilsTestCase::TearDown()
{
	delete pAxisSocketUtils;
	pAxisSocketUtils = NULL;
}

void AxisSocketUtilsTestCase::testprintSocketErrorDescription()
{
	int ExpectedSocketError =0 ;
	
	static int SocketError = pAxisSocketUtils->printSocketErrorDescription();

	int SockError = SocketError;

	CPPUNIT_ASSERT_EQUAL(ExpectedSocketError,SockError);
	
}



Test* AxisSocketUtilsTestCase::suite()
{
	TestSuite *testSuite = new TestSuite("AxisSocketUtilsTestCase");

	testSuite->addTest (new TestCaller <AxisSocketUtilsTestCase>
      ("testprintSocketErrorDescription", &AxisSocketUtilsTestCase::testprintSocketErrorDescription));


	return testSuite;
}
