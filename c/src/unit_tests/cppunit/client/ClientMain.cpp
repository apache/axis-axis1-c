#include "cppunit\ui\text\TestRunner.h"
#include "axis/test_cases/cppunit/client/CallTestCase.h"


using namespace CppUnit::TextUi;

int main(int argc, char* argv[])
 {

	TestRunner runner;

	runner.addTest(CallTestCase::suite());
	runner.run("CallTestCase");




	//runner.addTest(TypeMappingTestCase::suite());
	//runner.run("TypeMappingTestCase");


	//runner.addTest(AxisUtilsTestCase::suite());
	//runner.run("AxisUtilsTestCase");

////////////// Runner for AxisArrayBeanTest //////////////////
	//runner.addTest(ArrayBeanTestCase::suite());
	//runner.run("ArrayBeanTestCase");


///////////// Runner for AxisConfigTestCase  /////////////////
	//runner.addTest(AxisConfigTestCase::suite());
	//runner.run("AxisConfigTestCase");

/////////////  OK Runner for BasicTypeSerializer ////////////////

	//runner.addTest(BasicTypeSerializerTest::suite());
	//runner.run("BasicTypeSerializerTest");

///////////// Runner for AxisSocketUtilsTestCase /////////////
	//runner.addTest(AxisSocketUtilsTestCase::suite());
	//runner.run("AxisSocketUtilsTestCase");
	
////////////// OK Runner for ParamTestCase /////////////////

	//runner.addTest(ParamTestCase::suite());
	//runner.run("ParamTestCase");


	return 0;
}