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
 */

/* allTestCase.h: interface for the CallTestCase class. */

#if !defined(AXIS_ALLTESTCASE_H__OF_AXIS_INCLUDED_)
#define AXIS_ALLTESTCASE_H__OF_AXIS_INCLUDED_

#include "cppunit\TestCase.h"
#include "cppunit\TestSuite.h"
#include "cppunit\TestCaller.h"
#include <string>
#include <list>
#include "axis/client/Call.h"
#include "axis/soap/SoapDeSerializer.h"


using namespace CppUnit;
using namespace std;


class CallTestCase  : public TestCase
{
private:
    Call* pCall;
    /* SoapDeSerializer* pSoap; */
public:
    void testGetElementAsInt();
    
    void tearDown();
    void setUp();
    CallTestCase();
    virtual ~CallTestCase();
    static Test* suite();

};

#endif
