#include <cppunit/Asserter.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/config-auto.h>
//#include <cppunit/config-bcb5.h>
 //config-msvc6.h
#include <cppunit/Exception.h>
//#include <cppunit/NotEqualException.h>
#include <cppunit/Outputter.h>
#include <cppunit/Portability.h>
#include <cppunit/SourceLine.h>
 //SynchronizedObject.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFailure.h>
 //TestFixture.h>
#include <cppunit/Test.h>
#include <cppunit/TestListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuccessListener.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TextTestRunner.h>

#include <cppunit/ui/text/TestRunner.h>

#include "transport/axis2/Axis2TransportTest.hpp"


class TestSuite
{
public: 
static CppUnit::Test *suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "AxisCppTestSuite" );
	suiteOfTests->addTest( new CppUnit::TestCaller<Axis2TransportTest>( 
		"testGetBytes", 
		&Axis2TransportTest::testGetBytes ) );
	return suiteOfTests;
}
};

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( TestSuite::suite() );
  runner.run();
  return 0;
}
