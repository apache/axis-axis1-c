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

#if !defined(AFX_AXISUTILSTESTCASE_H__66F92899_F038_457B_8122_08196CA935C6__OF_AXIS_INCLUDED_)
#define AFX_AXISUTILSTESTCASE_H__66F92899_F038_457B_8122_08196CA935C6__OF_AXIS_INCLUDED_

#include "cppunit\TestCase.h"
#include "cppunit\TestSuite.h"
#include "cppunit\TestCaller.h"
#include <string>
#include "axis\common\AxisUtils.h"
#include "axis\common\IArrayBean.h"
#include "axis\common\IParam.h"
#include "axis\common\BasicTypeSerializer.h"

#include <list>


using namespace CppUnit;
using namespace std;

class AxisUtilsTestCase : public TestCase
{
public:
	void testLowerCaseString();
	void testtoLowerCase();
	void testToAxisXMLCh();
	void isCharacterAvailableref();
	void testIsCharacterAvailable();
	static Test* suite();
	void testClearArray();
	AxisUtilsTestCase();
	AxisUtilsTestCase(string sName): TestCase(sName) {}
	virtual ~AxisUtilsTestCase();
};

#endif // !defined(AFX_AXISUTILSTESTCASE_H__66F92899_F038_457B_8122_08196CA935C6__OF_AXIS_INCLUDED_)
