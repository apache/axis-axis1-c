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

#if !defined(AFX_AXISSOCKETUTILSTESTCASE1_H__2C8D2D1A_CCB5_433F_A2F3_2E3ABE5A1ECB__OF_AXIS_INCLUDED_)
#define AFX_AXISSOCKETUTILSTESTCASE1_H__2C8D2D1A_CCB5_433F_A2F3_2E3ABE5A1ECB__OF_AXIS_INCLUDED_

#include "cppunit\TestCase.h"
#include "cppunit\TestSuite.h"
#include "cppunit\TestCaller.h"
#include <string>
#include <list>
#include "axis/common/AxisSocketUtils.h"


using namespace CppUnit;
using namespace std;

class AxisSocketUtilsTestCase : public TestCase
{
private:

	AxisSocketUtils* pAxisSocketUtils;

public:
	
	static Test* suite();
	void testprintSocketErrorDescription();
	void TearDown();
	void setUp();
	AxisSocketUtilsTestCase();
	AxisSocketUtilsTestCase(string sName) : TestCase(sName) {}
	virtual ~AxisSocketUtilsTestCase();

};

#endif // !defined(AFX_AXISSOCKETUTILSTESTCASE1_H__2C8D2D1A_CCB5_433F_A2F3_2E3ABE5A1ECB__OF_AXIS_INCLUDED_)
