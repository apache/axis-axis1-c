// allTestCase.cpp: implementation of the CallTestCase class.
//
//////////////////////////////////////////////////////////////////////

#include "axis/test_cases/cppunit/client/CallTestCase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CallTestCase::CallTestCase()
{

}

CallTestCase::~CallTestCase()
{

}

void CallTestCase::setUp()
{
	pCall = new Call();
//	pSoap = new SoapDeSerializer();


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
