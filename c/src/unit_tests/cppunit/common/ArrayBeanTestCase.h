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

/* ArrayBeanTestCase.h: interface for the ArrayBeanTestCase class. */



#if !defined(AXIS_ARRAYBEANTESTCASE_H_OF_AXIS_INCLUDED_)
#define AXIS_ARRAYBEANTESTCASE_H_OF_AXIS_INCLUDED_

#include "cppunit\TestCase.h"
#include "cppunit\TestSuite.h"
#include "cppunit\TestCaller.h"
#include <string>
#include <list>
#include "axis/common/ArrayBean.h"

using namespace CppUnit;
using namespace std;

class ArrayBeanTestCase : public TestCase
{
private:
    ArrayBean* pArrayBean;
public:
    void testAxisConfig();
    void testSetItemName(const AxisChar* name);
    
    
    void tearDown();
    void setUp();
    void testGetArraySize();
    
    static Test* suite();
    ArrayBeanTestCase();
    ArrayBeanTestCase(string sName) : TestCase(sName) {}
    virtual ~ArrayBeanTestCase();

};

#endif
