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
 * @author Thushantha De Alwis (thushantha@beyondm.net  ravi@opensource.lk)
 *
 */


#include "cppunit\ui\text\TestRunner.h"
//#include "ParamTestCase.h"
#include "axis/test_cases/cppunit/common/MessageDataTestCase.h"


using namespace CppUnit::TextUi;

int main(int argc, char* argv[]) {

	TestRunner runner;

	//runner.addTest(ArrayBeanTestCase::suite());
	//runner.run("ArrayBeanTestCase");

////////////Runner for MessageDataTestCase //////////////////

	runner.addTest(MessageDataTestCase::suite());
	runner.run("MessageDataTestCase");
	

/////////////////////////////////////////////////////////////
	
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