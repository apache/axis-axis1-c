/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 * @author  Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include "AxisGenException.h"
#include <exception>

AXIS_CPP_NAMESPACE_START

//using namespace std;

AxisGenException::AxisGenException(const int iExceptionCode, const char* pcMessage):AxisException(iExceptionCode)
{
	AxisString sMessage = "";
	if (pcMessage) 
	{
		sMessage = pcMessage;
	}
	m_sMessage = getMessageForExceptionCode(m_iExceptionCode) + " " + sMessage;
}

AxisGenException::AxisGenException (const AxisGenException& e):AxisException(e)
{}

AxisGenException::~AxisGenException() throw ()
{}

const string AxisGenException::getMessageForExceptionCode (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case AXISC_SERVICE_THROWN_EXCEPTION:
            m_sMessage = "A service has thrown an exception. see detail ";
            break;
        case SERVER_TEST_EXCEPTION:
            m_sMessage = "This is a testing error ";
            break;
        case AXISC_NODE_VALUE_MISMATCH_EXCEPTION:
            m_sMessage = "Cannot deserialize the requested element ";
            break;
        default:
            m_sMessage = "";

    }
    return m_sMessage;
}



AXIS_CPP_NAMESPACE_END
