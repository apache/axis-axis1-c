/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Thushantha De Alwis (thushantha@beyondm.net  ravi@opensource.lk)
 *
 */
//////////////////////////////////////////////////////////////////////



// AxisConfigTestCase3.cpp: implementation of the AxisConfigTestCase class.
//
//////////////////////////////////////////////////////////////////////

#include "axis/test_cases/cppunit/common/AxisConfigTestCase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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


