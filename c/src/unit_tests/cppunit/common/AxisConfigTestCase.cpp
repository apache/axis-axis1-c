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

#include "axis/test_cases/cppunit/common/AxisConfigTestCase.h"


AxisConfigTestCase::AxisConfigTestCase()
{

}

AxisConfigTestCase::~AxisConfigTestCase()
{ 

}

void AxisConfigTestCase::setUp()
{
	pAxisConfig = new AxisConfig();

}

void AxisConfigTestCase::tearDown()
{
	delete pAxisConfig;
	pAxisConfig = NULL;
}


void AxisConfigTestCase::testGetAxisLogPath()
{
	char* Expectedpath="Axis\\logs\\";
	char* LogPath;

	LogPath = pAxisConfig->GetAxisLogPath();
	Expectedpath = LogPath;

	CPPUNIT_ASSERT_EQUAL(Expectedpath, LogPath);

}



Test* AxisConfigTestCase::suite()
{
	TestSuite *testSuite = new TestSuite("AxisConfigTestCase");

	testSuite->addTest (new TestCaller <AxisConfigTestCase>
      ("testGetAxisLogPath", &AxisConfigTestCase::testGetAxisLogPath));

	testSuite->addTest (new TestCaller <AxisConfigTestCase>
      ("testGetWsddFilePath", &AxisConfigTestCase::testGetWsddFilePath));


	return testSuite;
}

void AxisConfigTestCase::testGetWsddFilePath()
{
	char* ExpectedWsddLogPath ="Axis\\conf\\server.wsdd";
	char* WsddLogPath;
	WsddLogPath = pAxisConfig->GetWsddFilePath();


	string sResult = WsddLogPath;
	string ExpectedResult = ExpectedWsddLogPath;

	CPPUNIT_ASSERT_EQUAL(ExpectedResult,sResult);

}


