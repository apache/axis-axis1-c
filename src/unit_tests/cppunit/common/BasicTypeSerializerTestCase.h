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


#if !defined(AFX_BASICTYPESERIALIZERTEST_H__BF91C8F9_12BA_4495_B176_F6B56CE5957A__OF_AXIS_INCLUDED_)
#define AFX_BASICTYPESERIALIZERTEST_H__BF91C8F9_12BA_4495_B176_F6B56CE5957A__OF_AXIS_INCLUDED_

#include "cppunit\TestCase.h"
#include "cppunit\TestSuite.h"
#include "cppunit\TestCaller.h"
#include <string>
#include "axis\common\AxisConfig.h"
#include "axis\common\BasicTypeSerializer.h"

using namespace CppUnit;
using namespace std;

class BasicTypeSerializerTest :public TestCase
{
private:
	BasicTypeSerializer* pBasicTypeSerializer;
public:
	void testSerializeAsElement();
	void testSerializeAsAttribute();
	void testGetEntityReference();
	void testEncodeToHexBinary();
	
	void testEncodeToBase64Binary();
	void  testBasicTypeStr();
		
	void tearDown();
	void setUp();
	
	BasicTypeSerializerTest();
	virtual ~BasicTypeSerializerTest();
	static Test* suite();

};

#endif // !defined(AFX_BASICTYPESERIALIZERTEST_H__BF91C8F9_12BA_4495_B176_F6B56CE5957A__OF_AXIS_INCLUDED_)
