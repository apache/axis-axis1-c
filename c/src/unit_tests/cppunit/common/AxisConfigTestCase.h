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

#if !defined(AFX_AXISCONFIGTESTCASE_H__599874FA_EF16_454E_B45D_3C74F0280D5C__OF_AXIS_INCLUDED_)
#define AFX_AXISCONFIGTESTCASE_H__599874FA_EF16_454E_B45D_3C74F0280D5C__OF_AXIS_INCLUDED_

#include "cppunit\TestCase.h"
#include "cppunit\TestSuite.h"
#include "cppunit\TestCaller.h"
#include <string>
#include <list>
#include "axis\common\AxisConfig.h"

using namespace CppUnit;
using namespace std;



class AxisConfigTestCase  : public TestCase
{
private:
	AxisConfig* pAxisConfig;
public:
	void testGetWsddFilePath();
	void testGetAxisLogPath();
	void tearDown();
	void setUp();
	
	AxisConfigTestCase();

	AxisConfigTestCase(string sName) : TestCase(sName) {}
	
	virtual ~AxisConfigTestCase();
	static Test* suite();
};


#endif // !defined(AFX_AXISCONFIGTESTCASE_H__599874FA_EF16_454E_B45D_3C74F0280D5C__OF_AXIS_INCLUDED_)
